
            // Definers
static const MAX_TASKBAR_LIST_VIEW = 10;

            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    E_DATA_PAGE_UNIQUE_ID,
    E_DATA_PAGE,
    E_DATA_SELECTED_INDEX
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

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS amount FROM textdraws");

    if(cache)
    {
        new amount = DB_GetFieldIntByName(cache, "amount");
        DB_FreeResultSet(cache);

        new pages = Util_GetPages(count, MAX_TASKBAR_LIST_VIEW);

        if(page < 0) page = 0;
        if(page >= pages) pages = pages - 1;

        TaskBarEvent_SetPage(playerid, page);

        using inline TaskBarEvent_ListItems() {

            DialogMod_Add(playerid, "ID\tVariable\tName\tType");

            cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                    indexDraw, \
                                                    `text`, \
                                                    mode \
                                                FROM textdraws \
                                                LIMIT %i OFFSET %i"

                                                MAX_TASKBAR_LIST_VIEW,
                                                page * MAX_TASKBAR_LIST_VIEW
                                            );

            if(cache)
            {
                if(page && page <= (pages - 1)) DialogMod_Add(playerid, ">>", -1338);
                if(page >= 1) DialogMod_Add(playerid, "<<", -1337);

                new
                    index,
                    text[1024],
                    E_TYPEMODE:mode,
                    currentIndex = TaskBarEvent_GetIndex(playerid)
                ;

                do
                {
                    index = DB_GetFieldIntByName(IDConnection, "index");
                    mode = _:DB_GetFieldIntByName(IDConnection, "mode");
                    DB_GetFieldStringByName(IDConnection, "text", text);

                    DialogMod_Add(playerid, "%d\t%s\t{%s}%s\t%s", index, index, "...", currentIndex == index ? "FF0000" : "CCCCCC" , name, "...");
                }
                while(DB_SelectNextRow(cache));

                DB_FreeResultSet(cache);
            }
        }

        DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, va_return("%d/%d", page + 1, pages), "Select", "Close", "D_TASKBAR_LIST", using inline TaskBarEvent_ListItems);
    }
}

static stock TaskBarEvent_SelectIndex(playerid, index) {
    e_Data[playerid][E_DATA_SELECTED_INDEX] = index;

    
}

static stock TaskBarEvent_GetIndex(playerid)
    return e_Data[playerid][E_DATA_SELECTED_INDEX];

static stock TaskBarEvent_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock TaskBarEvent_SetPage(playerid, page)
    e_Data[playerid][E_DATA_PAGE] = page;

static stock TaskBarEvent_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock TaskBarEvent_SetPages(playerid, pages)
    e_Data[playerid][E_DATA_PAGES] = pages;



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

DialogMod:D_TASKBAR_LIST(playerid, response, inputtext[], index) {

    if(response) {

        switch(index) {
            case -1337: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) - 1);
            case -1338: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) + 1);
            default: TaskBarEvent_SelectIndex(playerid, index);
        }
    }
    return true;
}