
            // Definers
static const        MAX_GROUP_ITEMS_VIEW = 20;

static enum E_DATA {
    E_DATA_PAGE,
    E_DATA_PAGES,
    E_DATA_INDEX_GROUP
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

stock SessionEventGroupDraws_Show(playerid, indexGroup) {
    e_Data[playerid][E_DATA_INDEX_GROUP] = indexGroup;

    new uniqueId = Session_GetId();
    new DBResult:cache = DBResult:DB_ExecuteQuery(IDConnection, "SELECT count(*) AS `count` FROM textdraws WHERE project_id = %i", uniqueId);
    
    if(cache)
    {
        new count = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);

        SessionEventGroupDraws_SetPages(playerid, Util_GetPages(count, MAX_GROUP_ITEMS_VIEW));
        SessionEventGroupDraws_Page(playerid, 0);
    }
}

static stock SessionEventGroupDraws_Page(playerid, page) {

    new pages = SessionEventGroupDraws_GetPages(playerid);

    if(page < 0) page = 0;
    if(page >= pages) page = pages - 1;

    SessionEventGroupDraws_SetPage(playerid, page);

    inline OnSessionGroupDrawsShow() {

        new uniqueId = Session_GetId();

        DialogMod_Add(playerid, "ID\tName\tStatus");

        new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                text, \
                                                                indexDraw \
                                                            FROM textdraws \
                                                            WHERE project_id = %i \
                                                            ORDER BY indexDraw ASC \
                                                            LIMIT %i OFFSET %i",

                                                            uniqueId,
                                                            MAX_GROUP_ITEMS_VIEW,
                                                            page * MAX_GROUP_ITEMS_VIEW
                                                        );

        if(cache) 
        {
            if(DB_GetRowCount(cache)) 
            {
                DialogMod_Add(playerid, "Add all", -2);
                DialogMod_Add(playerid, "Remove all", -3);

                new 
                    string[1024 + 1],
                    indexDraw,
                    indexGroup = SessionEventGroupDraws_GetIndexGroup(playerid)
                ;

                do
                {
                    indexDraw = DB_GetFieldIntByName(cache, "indexDraw");
                    DB_GetFieldStringByName(cache, "text", string);
                    Util_CutString(string, 24);

                    DialogMod_Add(playerid, "%d\t%s\t%s", indexDraw, indexDraw, string, SessionGroup_HasDrawId(indexGroup, indexDraw) ? "{"#HEX_INFO"}[ADDED]" : "");
                }
                while(DB_SelectNextRow(cache));
            }

            DB_FreeResultSet(cache);
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, "Textdraws", "Add", "Back", "D_GROUP_DRAWLIST", using inline OnSessionGroupDrawsShow);
}

static stock SessionEventGroupDraw_Status(playerid, bool:status) {

    new uniqueId = Session_GetId();
    new page = SessionEventGroupDraws_GetPage(playerid);

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            t.indexDraw, \
                                                            gt.group_id IS NOT NULL AS hasGroup \
                                                        FROM textdraws t \
                                                        LEFT JOIN groups_textdraws gt ON gt.draw_id = t.id \
                                                        WHERE t.project_id = %i \
                                                        ORDER BY indexDraw ASC \
                                                        LIMIT %i OFFSET %i",

                                                        uniqueId,
                                                        MAX_GROUP_ITEMS_VIEW,
                                                        page * MAX_GROUP_ITEMS_VIEW
                                                    );

    if(cache)
    {
        if(DB_GetRowCount(cache))
        {
            new
                indexDraw,
                indexGroup = SessionEventGroupDraws_GetIndexGroup(playerid),
                bool:hasGroup
            ;

            do
            {
                indexDraw = DB_GetFieldIntByName(cache, "indexDraw");
                hasGroup = DB_GetFieldIntByName(cache, "hasGroup");

                if(status && !hasGroup)
                    SessionGroup_AddDraw(indexGroup, indexDraw);
                else if(!status && hasGroup)
                    SessionGroup_RemoveDraw(indexGroup, indexDraw);

            }
            while(DB_SelectNextRow(cache));

            SessionEventGroupDraws_SamePage(playerid);
        }

        DB_FreeResultSet(cache);
    }
}

static stock SessionEventGroupDraws_SetPage(playerid, value)
    e_Data[playerid][E_DATA_PAGE] = value;

static stock SessionEventGroupDraws_SetPages(playerid, value)
    e_Data[playerid][E_DATA_PAGES] = value;

static stock SessionEventGroupDraws_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock SessionEventGroupDraws_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock SessionEventGroupDraws_GetIndexGroup(playerid)
    return e_Data[playerid][E_DATA_INDEX_GROUP];

static stock SessionEventGroupDraws_SamePage(playerid)
    SessionEventGroupDraws_Page(playerid, SessionEventGroupDraws_GetPage(playerid));



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

DialogMod:D_GROUP_DRAWLIST(playerid, response, inputtext[], params) {

    if(response) {
        
        switch(params) {
            case -1: SessionEventGroupDraws_SamePage(playerid);
            case -2: SessionEventGroupDraw_Status(playerid, true);
            case -3: SessionEventGroupDraw_Status(playerid, false);
            default:
            {
                new indexGroup = SessionEventGroupDraws_GetIndexGroup(playerid);

                if(SessionGroup_HasDrawId(indexGroup, params))
                    SessionGroup_RemoveDraw(indexGroup, params);
                else
                    SessionGroup_AddDraw(indexGroup, params);

                SessionEventGroupDraws_SamePage(playerid);
            }
        }
        return true;
    }

    SessionEventGroupItem_SamePage(playerid);
    return true;
}