

            // Definers
static const MAX_TASKBAR_PROJECT_VIEW = 20;

static enum {
    E_INTERACTION_NEXT = -999,
    E_INTERACTION_PREVIOUS,
    E_INTERACTION_GOTO_PAGE,
    E_INTERACTION_LOAD_ITEMS,
    E_INTERACTION_DESTROY,
    E_INTERACTION_RENAME
};

static enum E_DATA {
    E_DATA_UNIQUE_ID,
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

stock TaskBarEventProjectList_Show(playerid) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS `count` FROM projects");

    if(cache) {
        new count = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);

        TaskBarEventProjectList_SetPages(playerid, Util_GetPages(count, MAX_TASKBAR_PROJECT_VIEW));
        TaskBarEventProjectList_Page(playerid, 0);
    }
}

static stock TaskBarEventProjectList_Page(playerid, page) {

    new pages = TaskBarEventProjectList_GetPages(playerid);

    if(page >= pages) page = pages - 1;
    if(page < 0 || pages <= 0) page = 0;
    
    TaskBarEventProjectList_SetPage(playerid, page);

    inline TaskBarEventProjectListing() {

        new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                id, \
                                                                name, \
                                                                `date` \
                                                            FROM projects \
                                                            ORDER BY id DESC \
                                                            LIMIT %i OFFSET %i",
                                                        
                                                            MAX_TASKBAR_PROJECT_VIEW,
                                                            page * MAX_TASKBAR_PROJECT_VIEW
                                                        );

        DialogMod_Add(playerid, "ID\tName\tCreated At", -1);

        if(cache) 
        {
            if(DB_GetRowCount(cache))
            {
                if(pages > 1 && page < (pages - 1)) DialogMod_Add(playerid, ">>", E_INTERACTION_NEXT);
                if(page) DialogMod_Add(playerid, "<<", E_INTERACTION_PREVIOUS);
                if(pages > 1) DialogMod_Add(playerid, "Goto Page", E_INTERACTION_GOTO_PAGE);

                new 
                    id,
                    name[45 + 1],
                    createdAt[25 + 1]
                ;

                do
                {
                    // Ints
                    id = DB_GetFieldIntByName(cache, "id");
                    
                    // Strings
                    DB_GetFieldStringByName(cache, "name", name, sizeof name);
                    DB_GetFieldStringByName(cache, "date", createdAt, sizeof createdAt);

                    DialogMod_Add(playerid, "%d\t%s\t{CCCCCC}%s", id, id, name, createdAt);
                }
                while(DB_SelectNextRow(cache));
            }

            DB_FreeResultSet(cache);
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, va_return("Page (%d/%d)", page + 1, pages), "Select", "Close", "D_TASKBAR_PROJECTLIST", using inline TaskBarEventProjectListing);
}

static stock TaskBarEventProjectList_Options(playerid, uniqueId) {

    TaskBarEventProjectList_SetUniqueId(playerid, uniqueId);

    inline TaskBarEventProjectOptions() {
        DialogMod_Add(playerid, "Load Items", E_INTERACTION_LOAD_ITEMS);
        DialogMod_Add(playerid, "Delete Project", E_INTERACTION_DESTROY);
        DialogMod_Add(playerid, "Rename this Project", E_INTERACTION_RENAME);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Project", "Select", "Previous", "D_TASKBAR_OPTION", using inline TaskBarEventProjectOptions);
}

static stock TaskBarEventProjectList_SamePage(playerid)
    TaskBarEventProjectList_Page(playerid, TaskBarEventProjectList_GetPage(playerid));

static stock TaskBarEventProjectList_SetPage(playerid, value)
    e_Data[playerid][E_DATA_PAGE] = value;

static stock TaskBarEventProjectList_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock TaskBarEventProjectList_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock TaskBarEventProjectList_SetPages(playerid, value)
    e_Data[playerid][E_DATA_PAGES] = value;

static stock TaskBarEventProjectList_SetUniqueId(playerid, id)
    e_Data[playerid][E_DATA_UNIQUE_ID] = id;

static stock TaskBarEventProjectList_GetUniqueId(playerid)
    return e_Data[playerid][E_DATA_UNIQUE_ID];



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_TASKBAR_PROJECTPAGE(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new page;
        if(sscanf(inputtext, "d", page))
            return Dialog_ReShow(playerid, "Only put numbers");

        if(page < 1 || page > TaskBarEventProjectList_GetPages(playerid)) return Dialog_ReShow(playerid, "This page does not exist");
        if(page == TaskBarEventProjectList_GetPage(playerid)) return Dialog_ReShow(playerid, "You are already on this page.");

        TaskBarEventProjectList_Page(playerid, page - 1);
        return true;
    }

    TaskBarEventProjectList_SamePage(playerid);
    return true;
}

Dialog:D_TASKBAR_RENAME(playerid, response, listitem, inputtext[]) {

    new uniqueId = TaskBarEventProjectList_GetUniqueId(playerid);

    if(response && !isnull(inputtext)) {
        if(TaskBarEventProjectLoad_RenameProject(uniqueId, inputtext))
            SendMessage(playerid, -1, ""#MESSAGE_GREEN"Project renamed to {CCCCCC}\"%s\"", inputtext);
        else
            SendMessage(playerid, -1, ""#MESSAGE_RED"There is another project with that name");
    }

    TaskBarEventProjectList_Options(playerid, uniqueId);
    return true;
}

Dialog:D_TASKBAR_DESTROY(playerid, response) {

    if(response && !Session_Has()) {
        new uniqueId = TaskBarEventProjectList_GetUniqueId(playerid);

        TaskBarEventProjectLoad_DeleteProject(uniqueId);
        SendMessage(INVALID_PLAYER_ID, -1, ""#MESSAGE_GREEN"Project ID (%d) was successfully destroyed.", uniqueId);
    }

    TaskBarEventProjectList_SamePage(playerid);
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
                                                                                                            
                    ooo        ooooo   .oooooo.   oooooooooo.                                               
                    `88.       .888'  d8P'  `Y8b  `888'   `Y8b                                              
                    888b     d'888  888      888  888      888                                             
                    8 Y88. .P  888  888      888  888      888                                             
                    8  `888'   888  888      888  888      888                                             
                    8    Y     888  `88b    d88'  888     d88'                                             
                    o8o        o888o  `Y8bood8P'  o888bood8P'                                               

*/

DialogMod:D_TASKBAR_PROJECTLIST(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case E_INTERACTION_PREVIOUS: TaskBarEventProjectList_Page(playerid, TaskBarEventProjectList_GetPage(playerid) - 1);
            case E_INTERACTION_NEXT: TaskBarEventProjectList_Page(playerid, TaskBarEventProjectList_GetPage(playerid) + 1);
            case E_INTERACTION_GOTO_PAGE: Dialog_Show(playerid, D_TASKBAR_PROJECTPAGE, DIALOG_STYLE_INPUT, "Page", "Which page do you want to go to?", "Goto", "Cancel");
            default: TaskBarEventProjectList_Options(playerid, params);
        }
    }
    return true;
}

DialogMod:D_TASKBAR_OPTION(playerid, response, inputtext[], params) {

    if(Session_Has()) return true;  // protect

    if(response) {

        new uniqueId = TaskBarEventProjectList_GetUniqueId(playerid);

        switch(params) 
        {
            case E_INTERACTION_LOAD_ITEMS: {
                TaskBarEventProjectLoad_OpenProject(uniqueId);
                SendMessage(INVALID_PLAYER_ID, -1, ""#MESSAGE_GREEN"Project ID (%d) was successfully loaded.", uniqueId);
            }

            case E_INTERACTION_DESTROY: Dialog_Show(playerid, D_TASKBAR_DESTROY, DIALOG_STYLE_MSGBOX, "Confirmation", "Are you sure you want to delete this project? There's no going back.", "Yes", "Cancel");
            case E_INTERACTION_RENAME:  Dialog_Show(playerid, D_TASKBAR_RENAME, DIALOG_STYLE_INPUT, "Rename", "What name would you like to give this project?", "Confirm", "Previous");
        }
        return true;
    }

    TaskBarEventProjectList_SamePage(playerid);
    return true;
}