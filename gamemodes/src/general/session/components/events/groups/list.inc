
            // Definers
static const    MAX_GROUP_LIST = 15;

static enum {
    E_INTERACTION_CREATE_GROUP = -999,
    E_INTERACTION_NEXT,
    E_INTERACTION_PREVIOUS
};

static enum E_DATA {
    E_DATA_CALLBACK[30 + 1],
    E_DATA_PAGE,
    E_DATA_PAGES
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

stock SessionEventGroupList_Show(playerid, const callback[]) {
    
    SessionEventGroupList_SetCallback(playerid, callback);

    new uniqueId = Session_GetId();
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS `count` FROM groups WHERE project_id = %i", uniqueId);

    if(cache)
    {
        new count = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);

        SessionEventGroupList_SetPages(playerid, Util_GetPages(count, MAX_GROUP_LIST));
        SessionEventGroupList_Page(playerid, 0);
    }
}

static stock SessionEventGroupList_Page(playerid, page) {

    new uniqueId = Session_GetId();
    new pages = SessionEventGroupList_GetPages(playerid);

    if(page >= pages) page = pages - 1;
    if(page < 0 || pages <= 0) page = 0;

    SessionEventGroupList_SetPage(playerid, page);

    inline OnSessionGroupListShow() {

        new 
            idGroup,
            indexGroup
        ;

        DialogMod_Add(playerid, L(playerid, E_LANG_GRP_HDR_ID));

        DialogMod_Add(playerid, L(playerid, E_LANG_GRP_CREATE), E_INTERACTION_CREATE_GROUP);

        if(pages > 1 && page < (pages - 1)) DialogMod_Add(playerid, ">>", E_INTERACTION_NEXT);
        if(page) DialogMod_Add(playerid, "<<", E_INTERACTION_PREVIOUS);

        new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            indexGroup \
                                                        FROM groups \
                                                        WHERE project_id = %i \
                                                        LIMIT %i OFFSET %i", 

                                                        uniqueId,
                                                        MAX_GROUP_LIST,
                                                        page * MAX_GROUP_LIST
                                                    );

        if(cache)
        {
            if(DB_GetRowCount(cache))
            {
                do
                {
                    new name[30 + 1];

                    // Ints
                    indexGroup = DB_GetFieldIntByName(cache, "indexGroup");
                    idGroup = SessionGroup_GetUniqueId(indexGroup);

                    // Strings
                    SessionGroup_GetString(indexGroup, name);

                    // Sets
                    DialogMod_Add(playerid, "%d\t{"#HEX_DEFAULT"}%s", indexGroup, idGroup, name);
                }
                while(DB_SelectNextRow(cache));
            }
            
            DB_FreeResultSet(cache);
        }
    }

    new groupTitle[32];
    LangF(playerid, groupTitle, sizeof groupTitle, E_LANG_GRP_HDR, page + 1, pages);
    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, groupTitle, L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CLOSE), "D_GROUP_LIST", using inline OnSessionGroupListShow);
}

static stock SessionEventGroupList_Callback(playerid, index) {

    new callback[30 + 1];
    SessionEventGroupList_GetCallback(playerid, callback);
    CallLocalFunction(va_return("gp_%s", callback), "ii", playerid, index);
}

stock SessionEventGroupList_SamePage(playerid)
    SessionEventGroupList_Page(playerid, SessionEventGroupList_GetPage(playerid));

static stock SessionEventGroupList_SetPage(playerid, value)
    e_Data[playerid][E_DATA_PAGE] = value;

static stock SessionEventGroupList_SetPages(playerid, value)
    e_Data[playerid][E_DATA_PAGES] = value;

static stock SessionEventGroupList_SetCallback(playerid, const callback[])
    strcopy(e_Data[playerid][E_DATA_CALLBACK], callback);

static stock SessionEventGroupList_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock SessionEventGroupList_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock SessionEventGroupList_GetCallback(playerid, dest[], maxlength = sizeof dest)
    strcat(dest, e_Data[playerid][E_DATA_CALLBACK], maxlength);



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_GROUP_CREATE(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new uniqueId = Session_GetId();

        if(SessionGroup_Exists(uniqueId, inputtext)) {
            SendLang(playerid, -1, E_LANG_ERR_GROUP_EXISTS);
            return true;
        }

        new indexGroup = SessionGroup_Create(uniqueId, inputtext);
        if(indexGroup == -1) {
            SendLang(playerid, -1, E_LANG_ERR_GROUP_LIMIT);
            return true;
        }

        SessionEventGroupList_Callback(playerid, indexGroup);
        return true;
    }

    SessionEventGroupList_SamePage(playerid);
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

DialogMod:D_GROUP_LIST(playerid, response, inputtext[], index) {

    if(response) {

        switch(index) {
            case -1: SessionEventGroupList_SamePage(playerid);
            case E_INTERACTION_CREATE_GROUP: Dialog_Show(playerid, D_GROUP_CREATE, DIALOG_STYLE_INPUT, L(playerid, E_LANG_NAME), L(playerid, E_LANG_GRP_NAME_BODY), L(playerid, E_LANG_BTN_CREATE), L(playerid, E_LANG_BTN_PREVIOUS));
            case E_INTERACTION_NEXT: SessionEventGroupList_Page(playerid, SessionEventGroupList_GetPage(playerid) + 1);
            case E_INTERACTION_PREVIOUS: SessionEventGroupList_Page(playerid, SessionEventGroupList_GetPage(playerid) - 1);
            default: SessionEventGroupList_Callback(playerid, index);
        }
    }
    return true;
}