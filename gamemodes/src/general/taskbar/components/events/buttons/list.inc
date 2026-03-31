
            // Definers
static const MAX_TASKBAR_LIST_VIEW = 10;

            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    E_DATA_PAGE_UNIQUE_ID,
    E_DATA_PAGE,
    E_DATA_INDEX_DRAW
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_ITENS)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEvent_Page(playerid, 0);
    return Y_HOOKS_BREAK_RETURN_1;
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

        if(page < 0) page = 0;
        if(page >= pages) pages = pages - 1;

        TaskBarEvent_SetPage(playerid, page);

        inline TaskBarEvent_ListItems() {

            DialogMod_Add(playerid, "ID\tVariable\tName\tType");

            new DBResult:cacheInside = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                        indexDraw, \
                                                                        text, \
                                                                        mode \
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
                    if((page && pages) &&  (pages - 1)) DialogMod_Add(playerid, ">>", -1338);
                    if(page >= 1) DialogMod_Add(playerid, "<<", -1337);

                    if(page >= 1)
                        DialogMod_Add(playerid, "Goto Page", -1368);

                    new
                        index,
                        text[1024 + 1],
                        E_TYPEMODE:mode,
                        currentIndex = TaskBarTextDraw_GetSelected(playerid)
                    ;

                    do
                    {
                        new dest[30 + 1];

                        // Ints
                        index = DB_GetFieldIntByName(cache, "indexDraw");
                        mode = E_TYPEMODE:DB_GetFieldIntByName(cache, "mode");
                        
                        // Strings
                        DB_GetFieldStringByName(cache, "text", text);
                        Util_CutString(text, 28);

                        SessionTextDrawData_GetVariable(index, dest);

                        // Dialog
                        DialogMod_Add(playerid, "%d\t{CCCCCC}%s\t{%s}%s\t%s", index, index, dest, currentIndex == index ? HEX_DEFAULT : "CCCCCC", text, TaskBarTypeMode_GetName(mode));
                    }
                    while(DB_SelectNextRow(cacheInside));
                }
                
                DB_FreeResultSet(cacheInside);
            }
        }

        DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, va_return("%d/%d", page + 1, pages), "Select", "Close", "D_TASKBAR_LIST", using inline TaskBarEvent_ListItems);
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

static stock TaskBarEvent_GetIndex(playerid)
    return e_Data[playerid][E_DATA_INDEX_DRAW];

static stock TaskBarEvent_SetIndex(playerid, index)
    e_Data[playerid][E_DATA_INDEX_DRAW] = index;

static stock TaskBarEvent_ShowOptions(playerid, index) {

    new 
        dialog[(18 + 30) * 5],
        dest[30 + 1]
    ;

    TaskBarEvent_SetIndex(playerid, index);
    SessionTextDrawData_GetVariable(index, dest);

    strcat(dialog, "Option\tOptional\n");
    strcat(dialog, "Select Textdraw\n");
    strcat(dialog, "Delete Textdraw\n");
    // strcatEx(dialog, "Change Variable\t{"#HEX_DEFAULT"}%s", dest);
    Dialog_Show(playerid, D_TASKBAR_LIST, DIALOG_STYLE_TABLIST_HEADERS, "Textdraw", dialog, "Select", "Back");
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_TASKBAR_LIST(playerid, response, listitem) {

    if(response) {
        new index = TaskBarEvent_GetIndex(playerid);

        switch(listitem) {
            case 0: TaskBarTextDraw_Select(playerid, index);
            case 1: {
                SessionTextDrawData_Destroy(index);
                TaskBarEvent_SamePage(playerid);
            }
            case 2: Dialog_Show(playerid, D_TASKBAR_VARIABLE, DIALOG_STYLE_INPUT, "Variable", "Define the name you want for the variable below.\n\n \
                                                                                            \
                                                                                            If you don't enter anything, its default will be set.", "Change", "Back");
        }
        return true;
    }

    TaskBarEvent_SamePage(playerid);
    return true;
}

Dialog:D_TASKBAR_VARIABLE(playerid, response, listitem, inputtext[]) {

    new index = TaskBarEvent_GetIndex(playerid);

    if(response) 
        SessionTextDrawData_SetVariable(index, inputtext);

    TaskBarEvent_ShowOptions(playerid, index);
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

DialogMod:D_TASKBAR_LIST(playerid, response, inputtext[], index) {

    if(response) {

        switch(index) {
            case -1333: TaskBarEvent_SamePage(playerid);
            case -1337: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) - 1);
            case -1338: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) + 1);
            default: TaskBarEvent_ShowOptions(playerid, index);
        }
    }
    return true;
}