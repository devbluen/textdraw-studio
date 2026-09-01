
            // Definers
static const MAX_TASKBAR_LIST_VIEW = 10;

            // Includes
#include <YSI_Coding\y_hooks>

static enum {
    E_INTERACTION_NEXT = -999,
    E_INTERACTION_PREVIOUS,
    E_INTERACTION_GOTO_PAGE
};

static enum E_DATA {
    E_DATA_PAGES,
    E_DATA_PAGE,
    E_DATA_INDEX
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnUserLogout(playerid) {

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextDrawColor_Show(playerid)
    TaskBarEvent_Page(playerid, 0);

static stock TaskBarEvent_Page(playerid, page) {

    new sessionId = Session_GetId();
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS count FROM textdraws WHERE project_id = %i", sessionId);

    if(cache)
    {
        new count = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);

        if(!count) {
            SendMessage(playerid, -1, ""#MESSAGE_RED"No items created to be displayed.");
            return;
        }

        new pages = Util_GetPages(count, MAX_TASKBAR_LIST_VIEW);

        if(page >= pages) page = pages - 1;
        if(page < 0 || pages <= 0) page = 0;

        TaskBarEvent_SetPage(playerid, page);
        TaskBarEvent_SetPages(playerid, pages);

        inline TaskBarEvent_ListItems() {

            DialogMod_Add(playerid, "ID\tVariable\tName");

            new DBResult:cacheInside = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                        indexDraw, \
                                                                        text \
                                                                    FROM textdraws \
                                                                    WHERE project_id = %i \
                                                                    ORDER BY indexDraw ASC \
                                                                    LIMIT %i OFFSET %i",

                                                                    sessionId,
                                                                    MAX_TASKBAR_LIST_VIEW,
                                                                    page * MAX_TASKBAR_LIST_VIEW
                                                                );

            if(cacheInside)
            {
                if(DB_GetRowCount(cacheInside))
                {
                    if(pages > 1 && page < (pages - 1)) DialogMod_Add(playerid, ">>", E_INTERACTION_NEXT);
                    if(page) DialogMod_Add(playerid, "<<", E_INTERACTION_PREVIOUS);
                    if(pages > 1) DialogMod_Add(playerid, "Goto Page", E_INTERACTION_GOTO_PAGE);

                    DialogMod_Add(playerid, " ");

                    new
                        index,
                        text[1024 + 1]
                    ;

                    do
                    {
                        new dest[30 + 1];

                        // Ints
                        index = DB_GetFieldIntByName(cache, "indexDraw");
                        
                        // Strings
                        DB_GetFieldStringByName(cache, "text", text);
                        Util_CutString(text, 28);

                        SessionTextDrawData_GetVariable(index, dest);

                        // Dialog
                        DialogMod_Add(playerid, "%d\t{CCCCCC}%s\t%s", index, index, dest, text);
                    }
                    while(DB_SelectNextRow(cacheInside));
                }
                
                DB_FreeResultSet(cacheInside);
            }
        }

        DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, va_return("%d/%d", page + 1, pages), "Select", "Close", "D_TASKBAR_LISTDRAW", using inline TaskBarEvent_ListItems);
    }
}

static stock TaskBarEvent_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock TaskBarEvent_SetPage(playerid, page)
    e_Data[playerid][E_DATA_PAGE] = page;

static stock TaskBarEvent_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock TaskBarEvent_SetPages(playerid, pages)
    e_Data[playerid][E_DATA_PAGES] = pages;

static stock TaskBarEvent_SamePage(playerid)
    TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid));



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_TASKBAR_GOTOPAGETP(playerid, response, listitem, inputtext[]) {

    if(response) {

        new page;
        if(sscanf(inputtext, "d", page))
            return Dialog_ReShow(playerid, "Only put numbers");

        new pages = TaskBarEvent_GetPages(playerid);
        if(page < 0 || page > pages)
            return Dialog_ReShow(playerid, "Invalid page");

        TaskBarEvent_Page(playerid, page - 1);
        return true;
    }

    TaskBarEvent_SamePage(playerid);
    return true;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  
                                                                                                            
                                                    .o8                                                   
                                                    "888                                                   
                    ooo. .oo.  .oo.    .ooooo.   .oooo888                                                   
                    `888P"Y88bP"Y88b  d88' `88b d88' `888                                                   
                    888   888   888  888   888 888   888                                                   
                    888   888   888  888   888 888   888                                                   
                    o888o o888o o888o `Y8bod8P' `Y8bod88P"                                                  

*/

DialogMod:D_TASKBAR_LISTDRAW(playerid, response, inputtext[], index) {

    if(response) {

        switch(index) {
            case -1: TaskBarEvent_SamePage(playerid);
            case E_INTERACTION_PREVIOUS: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) - 1);
            case E_INTERACTION_NEXT: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) + 1);
            case E_INTERACTION_GOTO_PAGE: Dialog_Show(playerid, D_TASKBAR_GOTOPAGETP, DIALOG_STYLE_INPUT, "Goto Page", "Which page do you want to go to?", "Confirm", "Previous");
            default: 
            {
                e_Data[playerid][E_DATA_INDEX] = index;

                inline ColorsMode() {

                    DialogMod_Add(playerid, "Color", 0);
                    DialogMod_Add(playerid, "Box Color", 1);
                    DialogMod_Add(playerid, "Background Color", 2);
                }

                DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Options", "Select", "Previous", "D_TASKBAR_LISTDRAWOP", using inline ColorsMode);
            }
        }
    }
    return true;
}

DialogMod:D_TASKBAR_LISTDRAWOP(playerid, response, inputtext[], index) {

    if(response) {
        new drawSelected = e_Data[playerid][E_DATA_INDEX];

        if(index == 0) Util_WebColorCall(playerid, SessionTextDrawData_GetColor(drawSelected));
        else if(index == 1) Util_WebColorCall(playerid, SessionTextDrawData_GetColorBox(drawSelected));
        else if(index == 2) Util_WebColorCall(playerid, SessionTextDrawData_GetColorBG(drawSelected));
        return;
    }

    TaskBarEvent_SamePage(playerid);
}