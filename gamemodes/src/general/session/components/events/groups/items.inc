
            // Definers
static const        MAX_GROUP_ITEMS_VIEW = 20;

static enum E_DATA {
    E_DATA_PAGE,
    E_DATA_PAGES,
    E_DATA_INDEX_DRAW,
    E_DATA_INDEX_GROUP,
    E_DATA_ENUM_ID
};

static enum {
    E_INTERACTION_EXPORT_ALL,
    E_INTERACTION_DESTROY_ALL,
    E_INTERACTION_POSITION,
    E_INTERACTION_SIZE,
    E_INTERACTION_LETTER_SIZE,
    E_INTERACTION_COLOR,
    E_INTERACTION_COLOR_BACKGROUND,
    E_INTERACTION_COLOR_BOX,
    E_INTERACTION_TEXT,
    E_INTERACTION_TO_PLAYER,
    E_INTERACTION_TO_GLOBAL,
    E_INTERACTION_ENABLE_BOX,
    E_INTERACTION_DISABLE_BOX,
    E_INTERACTION_ENABLE_SELECTION,
    E_INTERACTION_DISABLE_SELECTION
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionEventGroupItem_Show(playerid, indexGroup) {

    new groupId = SessionGroup_GetUniqueId(indexGroup);
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS `count` FROM groups_textdraws WHERE group_id = %i", groupId);

    if(cache)
    {
        new count = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);

        SessionEventGroupItem_SetPages(playerid, Util_GetPages(count, MAX_GROUP_ITEMS_VIEW));
        SessionEventGroupItem_Page(playerid, 0);        
    }
}

static stock SessionEventGroupItem_Page(playerid, page) {

    new pages = SessionEventGroupItem_GetPages(playerid);

    if(page < 0) page = 0;
    if(page >= pages) page = pages - 1;

    SessionEventGroupItem_SetPage(playerid, page);

    inline OnSessionGroupItemsShow() {

        new 
            indeGroup = SessionEventGroupItem_GetGroupIndex(playerid),
            groupId = SessionGroup_GetUniqueId(indeGroup) 
        ;

        DialogMod_Add(playerid, "ID\tName");
        DialogMod_Add(playerid, "Add Item", -1321);
        DialogMod_Add(playerid, "Destroy Group", -1311);

        if((page && pages) &&  (pages - 1)) DialogMod_Add(playerid, ">>", -1338);
        if(page >= 1) DialogMod_Add(playerid, "<<", -1337);

        new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                t.text, \
                                                                t.indexDraw \
                                                            FROM groups_textdraws gt \
                                                            JOIN textdraws t ON t.id = gt.draw_id \
                                                            WHERE gt.group_id = %i \
                                                            LIMIT %i OFFSET %i",
                                                            
                                                            groupId,
                                                            MAX_GROUP_ITEMS_VIEW,
                                                            page * MAX_GROUP_ITEMS_VIEW
                                                        );
    
        if(cache)
        {
            if(DB_GetRowCount(cache)) 
            {
                DialogMod_Add(playerid, "Options {CCCCCC}(Add Item, Moviment, Texts and Others)", -1322);

                new 
                    string[1024 + 1],
                    indexDraw
                ;

                do
                {
                    indexDraw = DB_GetFieldIntByName(cache, "indexDraw");
                    DB_GetFieldStringByName(cache, "text", string);

                    Util_CutString(string, 28);
                    DialogMod_Add(playerid, "%d\t{CCCCCC}%s", indexDraw, indexDraw, string);
                }
                while(DB_SelectNextRow(cache));
            }
            
            DB_FreeResultSet(cache);
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, va_return("Itens (%d/%d)", page + 1, pages), "Select", "Back", "D_GROUP_ITEMS", using inline OnSessionGroupItemsShow);
}

static stock SessionEventGroupItem_SetPage(playerid, value)
    e_Data[playerid][E_DATA_PAGE] = value;

static stock SessionEventGroupItem_SetPages(playerid, value)
    e_Data[playerid][E_DATA_PAGES] = value;

static stock SessionEventGroupItem_SetIndex(playerid, index)
    e_Data[playerid][E_DATA_INDEX_GROUP] = index;

static stock SessionEventGroupItem_SetDrawIndex(playerid, index)
    e_Data[playerid][E_DATA_INDEX_DRAW] = index;

stock SessionEventGroupItem_SamePage(playerid)
    SessionEventGroupItem_Page(playerid, SessionEventGroupItem_GetPage(playerid));

static stock SessionEventGroupItem_SetEnumId(playerid, value)
    e_Data[playerid][E_DATA_ENUM_ID] = value;

static stock SessionEventGroupItem_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock SessionEventGroupItem_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock SessionEventGroupItem_GetGroupIndex(playerid)
    return e_Data[playerid][E_DATA_INDEX_GROUP];

static stock SessionEventGroupItem_GetDrawIndex(playerid)
    return e_Data[playerid][E_DATA_INDEX_DRAW];

static stock SessionEventGroupItem_GetEnumId(playerid)
    return e_Data[playerid][E_DATA_ENUM_ID];

static stock SessionEventGroupItem_Options(playerid) {

    inline OnSessionGroupItemsOptions() {

        DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Management:");
        DialogMod_Add(playerid, "- Export all Textdraws", E_INTERACTION_EXPORT_ALL);
        DialogMod_Add(playerid, "- Destroy all Textdraws [!]", E_INTERACTION_DESTROY_ALL);
        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Resizing:");
        DialogMod_Add(playerid, "- Modify Position", E_INTERACTION_POSITION);
        DialogMod_Add(playerid, "- Modify Size", E_INTERACTION_SIZE);
        DialogMod_Add(playerid, "- Modify Letter-Size", E_INTERACTION_LETTER_SIZE);
        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Colors:");
        DialogMod_Add(playerid, "- Change Color", E_INTERACTION_COLOR);
        DialogMod_Add(playerid, "- Change Background Color", E_INTERACTION_COLOR_BACKGROUND);
        DialogMod_Add(playerid, "- Change Box Color", E_INTERACTION_COLOR_BOX);
        DialogMod_Add(playerid, "- Enable Box", E_INTERACTION_ENABLE_BOX);
        DialogMod_Add(playerid, "- Disable Box", E_INTERACTION_DISABLE_BOX);
        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Fonts:");
        DialogMod_Add(playerid, "- Font 1");
        DialogMod_Add(playerid, "- Font 2");
        DialogMod_Add(playerid, "- Font 3");
        DialogMod_Add(playerid, "- Font 4");
        DialogMod_Add(playerid, "- Left Alignment");
        DialogMod_Add(playerid, "- Center Alignment");
        DialogMod_Add(playerid, "- Right Alignment");
        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Text:");
        DialogMod_Add(playerid, "- Change Text", E_INTERACTION_TEXT);
        DialogMod_Add(playerid, "- Change Outline");
        DialogMod_Add(playerid, "- Change Shadow");
        DialogMod_Add(playerid, "- Enable Text Proportion");
        DialogMod_Add(playerid, "- Disable Text Proportion");
        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Misc:");
        DialogMod_Add(playerid, "- Enable Selection", E_INTERACTION_ENABLE_SELECTION);
        DialogMod_Add(playerid, "- Disable Selection", E_INTERACTION_DISABLE_SELECTION);
        DialogMod_Add(playerid, "- Define grouped textdraws as Player", E_INTERACTION_TO_PLAYER);
        DialogMod_Add(playerid, "- Define grouped textdraws as Global", E_INTERACTION_TO_GLOBAL);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Options", "Select", "Back", "D_GROUP_OPTIONS", using inline OnSessionGroupItemsOptions);
}

static stock SessionEventGroupItem_Color(playerid)
    Util_WebColorCreate(playerid, "GROUPCOLOR", false);

stock SessionEventGroupItem_SetOffset(playerid, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new indexGroup = SessionEventGroupItem_GetGroupIndex(playerid);

    switch(SessionEventGroupItem_GetEnumId(playerid)) {
        case E_INTERACTION_POSITION: SessionGroupDataDraw_SetPosition(indexGroup, offsetX, offsetY, execute_query, onlySave);
        case E_INTERACTION_SIZE: SessionGroupDataDraw_SetSize(indexGroup, offsetX, offsetY, execute_query, onlySave);
        case E_INTERACTION_LETTER_SIZE: SessionGroupDataDraw_SetLettSize(indexGroup, offsetX, offsetY, execute_query, onlySave);
    }

    if(onlySave && Session_Has())
        SessionEventGroupItem_Options(playerid);
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

WebColor:GROUPCOLOR(playerid, color) {

    if(color != -3) {

        new indexGroup = SessionEventGroupItem_GetGroupIndex(playerid);

        switch(SessionEventGroupItem_GetEnumId(playerid)) {
            case E_INTERACTION_COLOR: SessionGroupDataDraw_SetColor(indexGroup, color);
            case E_INTERACTION_COLOR_BACKGROUND: SessionGroupDataDraw_SetColorBG(indexGroup, color);
            case E_INTERACTION_COLOR_BOX: SessionGroupDataDraw_SetColorBox(indexGroup, color);
        }

    }

    SessionEventGroupItem_Options(playerid);
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

Dialog:D_GROUP_ITEMS_REMOVE(playerid, response) {

    if(response) {

        new 
            indexDraw = SessionEventGroupItem_GetDrawIndex(playerid),
            indexGroup = SessionEventGroupItem_GetGroupIndex(playerid)
        ;
    
        SessionGroup_RemoveDraw(indexGroup, indexDraw);
        SendMessage(playerid, -1, ""#MESSAGE_GREEN"Textdraw was successfully removed from the group.");
    }

    SessionEventGroupItem_SamePage(playerid);
    return true;
}

Dialog:D_GROUP_SET_TEXT(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {
        new indexGroup = SessionEventGroupItem_GetGroupIndex(playerid);
        SessionGroupDataDraw_SetText(indexGroup, inputtext);
    }

    SessionEventGroupItem_Options(playerid);
    return true;
}

Dialog:D_GROUP_DESTROY(playerid, response) {

    if(response) {
        new indexGroup = SessionEventGroupItem_GetGroupIndex(playerid);
        SessionGroup_Destroy(indexGroup);

        SendMessage(playerid, -1, ""#MESSAGE_GREEN"Group successfully destroyed.");
        return true;
    }

    SessionEventGroupItem_SamePage(playerid);
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

DialogMod:D_GROUP_ITEMS(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case -1: SessionEventGroupItem_SamePage(playerid);
            case -1321: SessionEventGroupDraws_Show(playerid, SessionEventGroupItem_GetGroupIndex(playerid));
            case -1322: SessionEventGroupItem_Options(playerid);
            case -1311: Dialog_Show(playerid, D_GROUP_DESTROY, DIALOG_STYLE_MSGBOX, "Confirmation", "Are you sure?", "Yes", "Cancel");
            case -1338: SessionEventGroupItem_Page(playerid, SessionEventGroupItem_GetPage(playerid) + 1);
            case -1337: SessionEventGroupItem_Page(playerid, SessionEventGroupItem_GetPage(playerid) - 1);
            default:
            {
                SessionEventGroupItem_SetDrawIndex(playerid, params);
                Dialog_Show(playerid, D_GROUP_ITEMS_REMOVE, DIALOG_STYLE_MSGBOX, "Confirmation", "Do you want to remove this textdraw from the group?", "Yes", "Cancel");
            }
        }
        return true;
    }

    SessionEventGroupList_SamePage(playerid);
    return true;
}

DialogMod:D_GROUP_OPTIONS(playerid, response, inputtext[], enumId) {

    if(response) {

        new indexGroup = SessionEventGroupItem_GetGroupIndex(playerid);
        SessionEventGroupItem_SetEnumId(playerid, enumId);

        switch(enumId) {
            case -1: SessionEventGroupItem_Options(playerid);
            // case E_INTERACTION_EXPORT_ALL:   // IMPORTANT Back Here
            case E_INTERACTION_DESTROY_ALL: {SessionGroup_RemoveAll(indexGroup); SessionEventGroupItem_Show(playerid, indexGroup);}
            case E_INTERACTION_POSITION: TaskBarKey_Set(playerid, E_TYPEKEY_GROUP_POSITION);
            case E_INTERACTION_SIZE: TaskBarKey_Set(playerid, E_TYPEKEY_GROUP_SIZE);
            case E_INTERACTION_LETTER_SIZE: TaskBarKey_Set(playerid, E_TYPEKEY_GROUP_LETTER_SIZE);
            case E_INTERACTION_COLOR: SessionEventGroupItem_Color(playerid);
            case E_INTERACTION_COLOR_BACKGROUND: SessionEventGroupItem_Color(playerid);
            case E_INTERACTION_COLOR_BOX: SessionEventGroupItem_Color(playerid);
            case E_INTERACTION_TEXT: Dialog_Show(playerid, D_GROUP_SET_TEXT, DIALOG_STYLE_INPUT, "Text", "Enter the text you want to change for the entire group below.", "Change", "Back");
            case E_INTERACTION_TO_PLAYER: {SessionGroupDataDraw_SetMode(indexGroup, E_TYPEMODE_PLAYER); SessionEventGroupItem_Options(playerid);}
            case E_INTERACTION_TO_GLOBAL: {SessionGroupDataDraw_SetMode(indexGroup, E_TYPEMODE_GLOBAL); SessionEventGroupItem_Options(playerid);}
            case E_INTERACTION_ENABLE_BOX: {SessionGroupDataDraw_SetBox(indexGroup, true); SessionEventGroupItem_Options(playerid);}
            case E_INTERACTION_DISABLE_BOX: {SessionGroupDataDraw_SetBox(indexGroup, false); SessionEventGroupItem_Options(playerid);}
            case E_INTERACTION_ENABLE_SELECTION: {SessionGroupDataDraw_SetSelect(indexGroup, true); SessionEventGroupItem_Options(playerid);}
            case E_INTERACTION_DISABLE_SELECTION: {SessionGroupDataDraw_SetSelect(indexGroup, false); SessionEventGroupItem_Options(playerid);}
        }
        return true;
    }

    SessionEventGroupList_SamePage(playerid);
    return true;    
}