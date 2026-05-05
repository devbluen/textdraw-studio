
            // Definers
static const MAX_TASKBAR_LIST_VIEW = 10;

            // Includes
#include <YSI_Coding\y_hooks>

static enum {
    E_INTERACTION_NEXT = -999,
    E_INTERACTION_PREVIOUS,
    E_INTERACTION_GOTO_PAGE,
    E_INTERACTION_SELECT_ALL,
    E_INTERACTION_SELECT_ALL_PAGE,
    E_INTERACTION_DESELECT_ALL_PAGE,
    E_INTERACTION_DESELECT_ALL,
    E_INTERACTION_SELECT,
    E_INTERACTION_DELETE,
    E_INTERACTION_SELECT_TO_ALL,
    E_INTERACTION_UNSELECT_TO_ALL,
    E_INTERACTION_GROUP_FROM_SELECTED,
    E_INTERACTION_MULTIPLE_SELECTION,
    E_INTERACTION_CLONE,
    E_INTERACTION_CLONE_CHOOSE,
    E_INTERACTION_DESTROY_ALL,
    E_INTERACTION_POSITION,
    E_INTERACTION_SIZE,
    E_INTERACTION_LETTER_SIZE,
    E_INTERACTION_COLOR,
    E_INTERACTION_COLOR_BACKGROUND,
    E_INTERACTION_COLOR_BOX,
    E_INTERACTION_ENABLE_BOX,
    E_INTERACTION_DISABLE_BOX,
    E_INTERACTION_FONT0,
    E_INTERACTION_FONT1,
    E_INTERACTION_FONT2,
    E_INTERACTION_FONT3,
    E_INTERACTION_ALIGN_LEFT,
    E_INTERACTION_ALIGN_CENTER,
    E_INTERACTION_ALIGN_RIGHT,
    E_INTERACTION_ENABLE_PROPOR,
    E_INTERACTION_DISABLE_PROPOR,
    E_INTERACTION_PLAYER,
    E_INTERACTION_GLOBAL,
    E_INTERACTION_TEXT,
    E_INTERACTION_OUTLINE,
    E_INTERACTION_SHADOW,
    E_INTERACTION_REORGANIZE,
    E_INTERACTION_MOVE_INDEX,
    E_INTERACTION_SELECT_ARROWS
};

static enum E_DATA {
    E_DATA_PAGE_UNIQUE_ID,
    E_DATA_PAGES,
    E_DATA_PAGE,
    E_DATA_INDEX_DRAW
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

    if(type != E_TYPETASKBUTTON_ITENS)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid));
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

        if(page >= pages) page = pages - 1;
        if(page < 0 || pages <= 0) page = 0;

        TaskBarEvent_SetPage(playerid, page);
        TaskBarEvent_SetPages(playerid, pages);

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
                    if(pages > 1 && page < (pages - 1)) DialogMod_Add(playerid, ">>", E_INTERACTION_NEXT);
                    if(page) DialogMod_Add(playerid, "<<", E_INTERACTION_PREVIOUS);
                    if(pages > 1) DialogMod_Add(playerid, "Goto Page", E_INTERACTION_GOTO_PAGE);

                    if(!SessionTextDraw_IsEmpty()) {
                        DialogMod_Add(playerid, "Reorganize Index", E_INTERACTION_REORGANIZE);
                        if(TaskBarTextDraw_Selected(playerid))
                            DialogMod_Add(playerid, "Select Index [Arrows]", E_INTERACTION_SELECT_ARROWS);
                    }

                    DialogMod_Add(playerid, "Options {CCCCCC}(Select, Multiple Move and Others)", E_INTERACTION_MULTIPLE_SELECTION);
                    DialogMod_Add(playerid, " ");

                    new
                        index,
                        text[1024 + 1],
                        E_TYPEMODE:mode,
                        color[40 + 1],
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
                        stringclear(color);

                        if(SessionPlayer_Has(playerid, index)) strcat(color, "{FFFF00}");
                        else if(currentIndex == index) color = "{"#HEX_DEFAULT"}";
                        else color = "{CCCCCC}";

                        if(currentIndex == index) strcat(color, ">> ");

                        // Dialog
                        DialogMod_Add(playerid, "%d\t{CCCCCC}%s\t%s%s\t%s", index, index, dest, color, text, TaskBarTypeMode_GetName(mode));
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

static stock TaskBarEvent_SamePageOptions(playerid)
    TaskBarEvent_ShowOptions(playerid, TaskBarEvent_GetIndex(playerid));

static stock TaskBarEvent_GetIndex(playerid)
    return e_Data[playerid][E_DATA_INDEX_DRAW];

static stock TaskBarEvent_SetIndex(playerid, index)
    e_Data[playerid][E_DATA_INDEX_DRAW] = index;

static stock TaskBarEvent_ShowOptions(playerid, index) {

    TaskBarEvent_SetIndex(playerid, index);
    
    inline TaskBarEventListOptionShow() {

        DialogMod_Add(playerid, "Select Textdraw", E_INTERACTION_SELECT);
        DialogMod_Add(playerid, "Delete Textdraw", E_INTERACTION_DELETE);
        if(!SessionPlayer_Has(playerid, index))
            DialogMod_Add(playerid, "{CCCCCC}Add to multi-select", E_INTERACTION_SELECT_TO_ALL);
        else
            DialogMod_Add(playerid, "{"HEX_INFO"}Remove to multi-select", E_INTERACTION_UNSELECT_TO_ALL);
        DialogMod_Add(playerid, "Move Index", E_INTERACTION_MOVE_INDEX);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Textdraw", "Select", "Previous", "D_TASKBAR_LISTOPTIONS", using inline TaskBarEventListOptionShow);
}

static stock TaskBarEvent_SelectAllFromPage(playerid, page, bool:status) {

    new sessionId = Session_GetId();
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            indexDraw \
                                                        FROM textdraws \
                                                        WHERE project_id = %i \
                                                        ORDER BY indexDraw ASC \
                                                        LIMIT %i OFFSET %i",

                                                        sessionId,
                                                        MAX_TASKBAR_LIST_VIEW,
                                                        page * MAX_TASKBAR_LIST_VIEW
                                                    );

    if(cache)
    {
        if(DB_GetRowCount(cache)) {

            new indexDraw;

            do
            {
                indexDraw = DB_GetFieldIntByName(cache, "indexDraw");

                if(status)
                    SessionPlayer_AddDraw(playerid, indexDraw);
                else
                    SessionPlayer_RemoveDraw(playerid, indexDraw);

            }
            while(DB_SelectNextRow(cache));
        }

        DB_FreeResultSet(cache);
    }
}

stock TaskBarEvent_MultipleOptions(playerid) {

    inline OnTaskBarEventListMultiple() {

        DialogMod_Add(playerid, "{"HEX_DEFAULT"}Selections:");
        DialogMod_Add(playerid, "- Select Page", E_INTERACTION_SELECT_ALL_PAGE);
        DialogMod_Add(playerid, "- Deselect Page", E_INTERACTION_DESELECT_ALL_PAGE);
        DialogMod_Add(playerid, "- Select All Pages", E_INTERACTION_SELECT_ALL);
        DialogMod_Add(playerid, "{"#HEX_INFO"}- Reset Selections", E_INTERACTION_DESELECT_ALL);
        
        if(SessionPlayer_HasAny(playerid)) {
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"HEX_DEFAULT"}Groups:");
            DialogMod_Add(playerid, "- Create Group from Selection", E_INTERACTION_GROUP_FROM_SELECTED);
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"HEX_DEFAULT"}Resizing:");
            DialogMod_Add(playerid, "- Modify Position", E_INTERACTION_POSITION);
            DialogMod_Add(playerid, "- Modify Size", E_INTERACTION_SIZE);
            DialogMod_Add(playerid, "- Modify Letter-Size", E_INTERACTION_LETTER_SIZE);
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"HEX_DEFAULT"}Colors:");
            DialogMod_Add(playerid, "- Change Color", E_INTERACTION_COLOR);
            DialogMod_Add(playerid, "- Change Background Color", E_INTERACTION_COLOR_BACKGROUND);
            DialogMod_Add(playerid, "- Change Box Color", E_INTERACTION_COLOR_BOX);
            DialogMod_Add(playerid, "- Enable Box", E_INTERACTION_ENABLE_BOX);
            DialogMod_Add(playerid, "- Disable Box", E_INTERACTION_DISABLE_BOX);
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"HEX_DEFAULT"}Clonings:");
            DialogMod_Add(playerid, "- Clone All", E_INTERACTION_CLONE);
            DialogMod_Add(playerid, "- Clone All and Choose", E_INTERACTION_CLONE_CHOOSE);
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Fonts:");
            DialogMod_Add(playerid, "- Font 0", E_INTERACTION_FONT0);
            DialogMod_Add(playerid, "- Font 1", E_INTERACTION_FONT1);
            DialogMod_Add(playerid, "- Font 2", E_INTERACTION_FONT2);
            DialogMod_Add(playerid, "- Font 3", E_INTERACTION_FONT3);
            DialogMod_Add(playerid, "- Left Alignment", E_INTERACTION_ALIGN_LEFT);
            DialogMod_Add(playerid, "- Center Alignment", E_INTERACTION_ALIGN_CENTER);
            DialogMod_Add(playerid, "- Right Alignment", E_INTERACTION_ALIGN_RIGHT);
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"HEX_DEFAULT"}Text:");
            DialogMod_Add(playerid, "- Change Text", E_INTERACTION_TEXT);
            DialogMod_Add(playerid, "- Edit Outline", E_INTERACTION_OUTLINE);
            DialogMod_Add(playerid, "- Edit Shadow", E_INTERACTION_SHADOW);
            DialogMod_Add(playerid, "- Enable Proportional", E_INTERACTION_ENABLE_PROPOR);
            DialogMod_Add(playerid, "- Disable Proportional", E_INTERACTION_DISABLE_PROPOR);
            DialogMod_Add(playerid, " ");
            DialogMod_Add(playerid, "{"HEX_DEFAULT"}Management:");
            DialogMod_Add(playerid, "- Destroy All", E_INTERACTION_DESTROY_ALL);
            DialogMod_Add(playerid, "- Define textdraws as Player", E_INTERACTION_PLAYER);
            DialogMod_Add(playerid, "- Define textdraws as Global", E_INTERACTION_GLOBAL);
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Multiple Selection", "Select", "Previous", "D_TASKBAR_MULTIPLE", using inline OnTaskBarEventListMultiple);
}



/*

                    .oooooo.     .oooooo.   ooooo          .oooooo.   ooooooooo.    .oooooo..o 
                    d8P'  `Y8b   d8P'  `Y8b  `888'         d8P'  `Y8b  `888   `Y88. d8P'    `Y8 
                    888          888      888  888         888      888  888   .d88' Y88bo.      
                    888          888      888  888         888      888  888ooo88P'   `"Y8888o.  
                    888          888      888  888         888      888  888`88b.         `"Y88b 
                    `88b    ooo  `88b    d88'  888       o `88b    d88'  888  `88b.  oo     .d8P 
                    `Y8bood8P'   `Y8bood8P'  o888ooooood8  `Y8bood8P'  o888o  o888o 8""88888P'  

*/

WebColor:TaskBarList_Color(playerid, color) {

    if(color != -3)
        SessionPlayerData_SetColor(playerid, color);

    TaskBarEvent_MultipleOptions(playerid);
}

WebColor:TaskBarList_ColorBG(playerid, color) {

    if(color != -3)
        SessionPlayerData_SetColorBG(playerid, color);

    TaskBarEvent_MultipleOptions(playerid);
}

WebColor:TaskBarList_ColorBox(playerid, color) {

    if(color != -3)
        SessionPlayerData_SetColorBox(playerid, color);

    TaskBarEvent_MultipleOptions(playerid);
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

Dialog:D_TASKBAR_VARIABLE(playerid, response, listitem, inputtext[]) {

    new index = TaskBarEvent_GetIndex(playerid);

    if(response) 
        SessionTextDrawData_SetVariable(index, inputtext);

    TaskBarEvent_ShowOptions(playerid, index);
    return true;
}

Dialog:D_TASKBAR_GOTOPAGE(playerid, response, listitem, inputtext[]) {

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

DialogMod:D_TASKBAR_LIST(playerid, response, inputtext[], index) {

    if(response) {

        switch(index) {
            case -1: TaskBarEvent_SamePage(playerid);
            case E_INTERACTION_REORGANIZE: SessionTextDrawData_ReorganizeIndexs(Session_GetId());
            case E_INTERACTION_PREVIOUS: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) - 1);
            case E_INTERACTION_NEXT: TaskBarEvent_Page(playerid, TaskBarEvent_GetPage(playerid) + 1);
            case E_INTERACTION_GOTO_PAGE: Dialog_Show(playerid, D_TASKBAR_GOTOPAGE, DIALOG_STYLE_INPUT, "Goto Page", "Which page do you want to go to?", "Confirm", "Previous");
            case E_INTERACTION_MULTIPLE_SELECTION: TaskBarEvent_MultipleOptions(playerid);
            case E_INTERACTION_SELECT_ARROWS: TaskBarKey_Set(playerid, E_TYPEKEY_SELECT_INDEX);
            default: TaskBarEvent_ShowOptions(playerid, index);
        }
    }
    return true;
}

Dialog:D_TASKBAR_LISTDESTROY(playerid, response) {

    if(response) {
        new index = TaskBarEvent_GetIndex(playerid);
        SessionTextDrawData_Destroy(index);
        TaskBarEvent_SamePage(playerid);
        return true;
    }

    TaskBarEvent_SamePageOptions(playerid);
    return true;
}

DialogMod:D_TASKBAR_LISTOPTIONS(playerid, response, inputtext[], listitem) {

    if(response) {
        new index = TaskBarEvent_GetIndex(playerid);

        switch(listitem) {
            case E_INTERACTION_SELECT: TaskBarTextDraw_Select(playerid, index);
            case E_INTERACTION_DELETE: Dialog_Show(playerid, D_TASKBAR_LISTDESTROY, DIALOG_STYLE_MSGBOX, "Confirmation", "Do you really want to delete it?", "Yes", "Back");
            case E_INTERACTION_SELECT_TO_ALL: {
                SessionPlayer_AddDraw(playerid, index);
                TaskBarEvent_SamePageOptions(playerid);
            }
            case E_INTERACTION_UNSELECT_TO_ALL: {
                SessionPlayer_RemoveDraw(playerid, index);
                TaskBarEvent_SamePageOptions(playerid);
            }
            case E_INTERACTION_MOVE_INDEX: SessionPlayer_MoveIndexInit(playerid, index);
        }
        return true;
    }

    TaskBarEvent_SamePage(playerid);
    return true;
}

DialogMod:D_TASKBAR_MULTIPLE(playerid, response, inputtext[], listitem) {

    if(response) {
        switch(listitem) {
            case E_INTERACTION_SELECT_ALL: {SessionPlayer_SelectAll(playerid); TaskBarEvent_SamePage(playerid); return true;}
            case E_INTERACTION_SELECT_ALL_PAGE: {TaskBarEvent_SelectAllFromPage(playerid, TaskBarEvent_GetPage(playerid), true); TaskBarEvent_SamePage(playerid); return true;}
            case E_INTERACTION_DESELECT_ALL_PAGE: {TaskBarEvent_SelectAllFromPage(playerid, TaskBarEvent_GetPage(playerid), false); TaskBarEvent_SamePage(playerid); return true;}
            case E_INTERACTION_DESELECT_ALL: {SessionPlayer_ResetLocalGroup(playerid); TaskBarEvent_SamePage(playerid); return true;}
            case E_INTERACTION_GROUP_FROM_SELECTED: {SessionPlayer_AddWithSelected(playerid); return true;}
            case E_INTERACTION_CLONE: SessionPlayer_CloneAll(playerid);
            case E_INTERACTION_CLONE_CHOOSE: SessionPlayer_CloneAll(playerid, true);
            case E_INTERACTION_DESTROY_ALL: {SessionPlayer_DestroyAll(playerid); return true;}
            case E_INTERACTION_POSITION: {TaskBarKey_Set(playerid, E_TYPEKEY_GROUP_LOCAL_POSITION); return true;}
            case E_INTERACTION_SIZE: {TaskBarKey_Set(playerid, E_TYPEKEY_GROUP_LOCAL_SIZE); return true;}
            case E_INTERACTION_LETTER_SIZE: {TaskBarKey_Set(playerid, E_TYPEKEY_GROUP_LOCAL_LETTER_SIZE); return true;}
            case E_INTERACTION_COLOR: {Util_WebColorCreate(playerid, "TaskBarList_Color", false); return true;}
            case E_INTERACTION_COLOR_BACKGROUND: {Util_WebColorCreate(playerid, "TaskBarList_ColorBG", false); return true;}
            case E_INTERACTION_COLOR_BOX: {Util_WebColorCreate(playerid, "TaskBarList_ColorBox", false); return true;}
            case E_INTERACTION_ENABLE_BOX: SessionPlayerData_SetBox(playerid, true);
            case E_INTERACTION_DISABLE_BOX: SessionPlayerData_SetBox(playerid, false);
            case E_INTERACTION_FONT0: SessionPlayerData_SetFont(playerid, E_TYPEFONT_0);
            case E_INTERACTION_FONT1: SessionPlayerData_SetFont(playerid, E_TYPEFONT_1);
            case E_INTERACTION_FONT2: SessionPlayerData_SetFont(playerid, E_TYPEFONT_2);
            case E_INTERACTION_FONT3: SessionPlayerData_SetFont(playerid, E_TYPEFONT_3);
            case E_INTERACTION_ALIGN_LEFT: SessionPlayerData_SetAlign(playerid, E_TYPEALIGNMENT_LEFT);
            case E_INTERACTION_ALIGN_CENTER: SessionPlayerData_SetAlign(playerid, E_TYPEALIGNMENT_CENTER);
            case E_INTERACTION_ALIGN_RIGHT: SessionPlayerData_SetAlign(playerid, E_TYPEALIGNMENT_RIGHT);
            case E_INTERACTION_ENABLE_PROPOR: SessionPlayerData_SetPropor(playerid, true);
            case E_INTERACTION_DISABLE_PROPOR: SessionPlayerData_SetPropor(playerid, false);
            case E_INTERACTION_PLAYER: SessionPlayerData_SetMode(playerid, E_TYPEMODE_PLAYER);
            case E_INTERACTION_GLOBAL: SessionPlayerData_SetMode(playerid, E_TYPEMODE_GLOBAL);
            case E_INTERACTION_TEXT: {
                Dialog_Show(playerid, D_TASKBAR_TEXT, DIALOG_STYLE_INPUT, "Change Text", "Enter the text for the group below", "Change", "Previous");
                return true;
            }
            case E_INTERACTION_OUTLINE: {
                Dialog_Show(playerid, D_TASKBAR_OUTLINE, DIALOG_STYLE_INPUT, "Outline", "{FFFFFF}Input the outline value below\n\nSet to {"#HEX_INFO"}0{FFFFFF} to disable", "Change", "Previous");
                return true;
            }
            case E_INTERACTION_SHADOW: {
                Dialog_Show(playerid, D_TASKBAR_SHADOW, DIALOG_STYLE_INPUT, "Shadow", "{FFFFFF}Input the shadow value below\n\nSet to {"#HEX_INFO"}0{FFFFFF} to disable", "Change", "Previous");
                return true;
            }
        }

        TaskBarEvent_MultipleOptions(playerid);
        return true;
    }

    TaskBarEvent_SamePage(playerid);
    return true;
}

Dialog:D_TASKBAR_TEXT(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext))
        SessionPlayerData_SetString(playerid, inputtext);

    TaskBarEvent_MultipleOptions(playerid);
    return true;
}

Dialog:D_TASKBAR_OUTLINE(playerid, response, listitem, inputtext[]) {

    if(response) {

        new value;
        if(sscanf(inputtext, "d", value) || value < 0)
            return Dialog_ReShow(playerid, "Invalid input");

        SessionPlayerData_SetOutline(playerid, value);
    }
    
    TaskBarEvent_MultipleOptions(playerid);
    return true;
}

Dialog:D_TASKBAR_SHADOW(playerid, response, listitem, inputtext[]) {

    if(response) {

        new value;
        if(sscanf(inputtext, "d", value) || value < 0)
            return Dialog_ReShow(playerid, "Invalid input");

        SessionPlayerData_SetShadow(playerid, value);
    }
    
    TaskBarEvent_MultipleOptions(playerid);
    return true;
}