
            // Definers
static const MAX_TASKBAR_TRASH_VIEW = 10;

            // Includes
#include <YSI_Coding\y_hooks>

static enum {
    E_INTERACTION_TRASH_NEXT = -1100,
    E_INTERACTION_TRASH_PREVIOUS,
    E_INTERACTION_TRASH_GOTO_PAGE
};

static enum E_DATA {
    E_DATA_PAGE,
    E_DATA_PAGES
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnUserLogout(playerid) {

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_TRASH)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEventTrash_Page(playerid, TaskBarEventTrash_GetPage(playerid));
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

static stock TaskBarEventTrash_Page(playerid, page) {

    if(!Session_Has())
        return;

    new count = SessionTrash_Count();
    if(!count) {
        SendLang(playerid, -1, E_LANG_TRASH_EMPTY);
        return;
    }

    new pages = Util_GetPages(count, MAX_TASKBAR_TRASH_VIEW);

    if(page >= pages) page = pages - 1;
    if(page < 0 || pages <= 0) page = 0;

    TaskBarEventTrash_SetPage(playerid, page);
    TaskBarEventTrash_SetPages(playerid, pages);

    new trashTitle[32];
    LangF(playerid, trashTitle, sizeof trashTitle, E_LANG_TRASH_TITLE, page + 1, pages);

    inline TaskBarEvent_TrashItems() {

        DialogMod_Add(playerid, L(playerid, E_LANG_LIST_HDR));

        if(pages > 1 && page < (pages - 1)) DialogMod_Add(playerid, ">>", E_INTERACTION_TRASH_NEXT);
        if(page) DialogMod_Add(playerid, "<<", E_INTERACTION_TRASH_PREVIOUS);
        if(pages > 1) DialogMod_Add(playerid, L(playerid, E_LANG_LIST_GOTO_TITLE), E_INTERACTION_TRASH_GOTO_PAGE);
        DialogMod_Add(playerid, " ");

        new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                id, \
                                                                `text`, \
                                                                variable, \
                                                                mode \
                                                            FROM trash \
                                                            WHERE project_id = %i \
                                                            ORDER BY id DESC \
                                                            LIMIT %i OFFSET %i",

                                                            Session_GetId(),
                                                            MAX_TASKBAR_TRASH_VIEW,
                                                            page * MAX_TASKBAR_TRASH_VIEW
                                                        );

        if(cache)
        {
            if(DB_GetRowCount(cache))
            {
                new
                    id,
                    E_TYPEMODE:mode,
                    text[1024 + 1],
                    dest[30 + 1]
                ;

                do
                {
                    id = DB_GetFieldIntByName(cache, "id");
                    mode = E_TYPEMODE:DB_GetFieldIntByName(cache, "mode");

                    DB_GetFieldStringByName(cache, "text", text);
                    Util_CutString(text, 28);

                    DB_GetFieldStringByName(cache, "variable", dest);

                    DialogMod_Add(playerid, "%d\t{CCCCCC}%s\t{CCCCCC}%s\t%s", id, id, dest, text, L(playerid, mode == E_TYPEMODE_PLAYER ? E_LANG_MODE_PLAYER : E_LANG_MODE_GLOBAL));
                }
                while(DB_SelectNextRow(cache));
            }

            DB_FreeResultSet(cache);
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, trashTitle, L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CLOSE), "D_TASKBAR_TRASH", using inline TaskBarEvent_TrashItems);
}

static stock TaskBarEventTrash_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock TaskBarEventTrash_SetPage(playerid, page)
    e_Data[playerid][E_DATA_PAGE] = page;

static stock TaskBarEventTrash_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock TaskBarEventTrash_SetPages(playerid, pages)
    e_Data[playerid][E_DATA_PAGES] = pages;

static stock TaskBarEventTrash_SamePage(playerid)
    TaskBarEventTrash_Page(playerid, TaskBarEventTrash_GetPage(playerid));



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

DialogMod:D_TASKBAR_TRASH(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case E_INTERACTION_TRASH_NEXT: TaskBarEventTrash_Page(playerid, TaskBarEventTrash_GetPage(playerid) + 1);
            case E_INTERACTION_TRASH_PREVIOUS: TaskBarEventTrash_Page(playerid, TaskBarEventTrash_GetPage(playerid) - 1);
            case E_INTERACTION_TRASH_GOTO_PAGE: Dialog_Show(playerid, D_TASKBAR_TRASHGOTO, DIALOG_STYLE_INPUT, L(playerid, E_LANG_LIST_GOTO_TITLE), L(playerid, E_LANG_LIST_GOTO_BODY), L(playerid, E_LANG_BTN_CONFIRM), L(playerid, E_LANG_BTN_PREVIOUS));
            default: {
                if(params > 0 && SessionTrash_Restore(playerid, params))
                    TaskBarEventTrash_SamePage(playerid);
            }
        }
    }
    return true;
}

Dialog:D_TASKBAR_TRASHGOTO(playerid, response, listitem, inputtext[]) {

    if(response) {

        new page;
        if(sscanf(inputtext, "d", page))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_NUMBERS));

        new pages = TaskBarEventTrash_GetPages(playerid);
        if(page < 1 || page > pages)
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_PAGE));

        TaskBarEventTrash_Page(playerid, page - 1);
        return true;
    }

    TaskBarEventTrash_SamePage(playerid);
    return true;
}
