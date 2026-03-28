
            // Definers
static const MAX_TASKBAR_PROJECT_VIEW = 10;

            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    E_DATA_PAGE_UNIQUE_ID,
    E_DATA_PAGE,
    E_DATA_PAGES
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_PROJECT)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEvent_Show(playerid);
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

static stock TaskBarEvent_Show(playerid) {

    new dialog[15 * 3];
    strcat(dialog, "New Workspace\n");
    strcat(dialog, "Open Project\n");
    strcat(dialog, "Exit Studio");

    Dialog_Show(playerid, D_TASKBAR_PROJECTS, DIALOG_STYLE_TABLIST, "Project", dialog, "Select", "Close");
}

static stock TaskBarEvent_Projects(playerid) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS `count` FROM projects");

    if(cache) {
        new count = DB_GetRowCount(cache);
        DB_FreeResultSet(cache);

        TaskBarEvent_SetPages(playerid, Util_GetPages(count, MAX_TASKBAR_PROJECT_VIEW));
        TaskBarEvent_ProjectPage(playerid, 0);
    }
}

static stock TaskBarEvent_ProjectPage(playerid, page) {

    new pages = TaskBarEvent_GetPages(playerid);

    if(page < 0) page = 0;
    if(page >= pages) page = pages - 1;
    
    TaskBarEvent_SetPage(playerid, page);

    inline TaskBarEvent_ProjectDialog() {

        new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            id, \
                                                            name, \
                                                            `date` \
                                                        FROM projects \
                                                        LIMIT %i OFFSET %i",
                                                    
                                                        MAX_TASKBAR_PROJECT_VIEW,
                                                        page * MAX_TASKBAR_PROJECT_VIEW
                                                    );

        DialogMod_Add(playerid, "ID\tName\tCreated At", -1);

        if(cache && DB_GetRowCount(cache)) {

            if(page && page <= (pages - 1)) DialogMod_Add(playerid, ">>", -1338);
            if(page >= 1) DialogMod_Add(playerid, "<<", -1337);

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

            DB_FreeResultSet(cache);
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST_HEADERS, va_return("Page (%d/%d)", page + 1, pages), "Select", "Close", "D_TASKBAR_PROJECTS", using inline TaskBarEvent_ProjectDialog);
}

static stock TaskBarEvent_ProjectSamePage(playerid) {
    TaskBarEvent_ProjectPage(playerid, TaskBarEvent_GetPage(playerid));
}

static stock TaskBarEvent_Create(playerid) {
    Dialog_Show(playerid, D_TASKBAR_CREATE, DIALOG_STYLE_INPUT, "Project Name", "Write your project name below", "Create", "Back");
}

static stock TaskBarEvent_OpenProject(uniqueId) {
    Session_SetId(uniqueId);
}

static stock TaskBarEvent_ProjectOptions(playerid, uniqueId) {

    TaskBarEvent_SetUniqueId(playerid, uniqueId);

    inline TaskBarEvent_ProjectOption() {
        DialogMod_Add(playerid, "Open Project", 0);
        DialogMod_Add(playerid, "Delete Project", 1);
        DialogMod_Add(playerid, "Rename this Project", 2);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Project", "Select", "Back", "D_TASKBAR_PROJECT", using inline TaskBarEvent_ProjectOption);
}

static stock TaskBarEvent_OpenProjectName(playerid, const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM `projects` WHERE `name` = '%s'", name);
    if(cache) {

        new uniqueId;

        if(!DB_GetRowCount(cache)) {
            TaskBarEvent_CreateProject(playerid, name);
            return;
        }
        else uniqueId = DB_GetFieldIntByName(cache, "id");

        DB_FreeResultSet(cache);
        TaskBarEvent_OpenProject(uniqueId);
    }
}

static stock TaskBarEvent_CreateProject(playerid, const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "INSERT INTO `projects` (`name`, `date`) VALUES ('%s', '%s')", name, "00/00/0000 00:00");
    if(cache) {
        DB_FreeResultSet(cache);
        TaskBarEvent_OpenProjectName(playerid, name);
        SendMessage(playerid, -1, ""#MESSAGE_GREEN"The {CCCCCC}\"%s\"{FFFFFF} project was successfully created.", name);
        return;
    }

    SendMessage(playerid, -1, ""#MESSAGE_RED"It was not possible to create the {CCCCCC}\"%s\"{FFFFFF} project.", name);
}

static stock TaskBarEvent_DeleteProject(uniqueId) {

}

static stock bool:TaskBarEvent_RenameProject(uniqueId, const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM `projects` WHERE `name` = '%s'", name);
    if(cache) {
        DB_FreeResultSet(cache);
        new DBResult:cacheTwo = DB_ExecuteQuery(IDConnection, "UPDATE `projects` SET `name` = '%s' WHERE `id` = %i", name, uniqueId);
        if(cacheTwo) {
            DB_FreeResultSet(cacheTwo);
            return true;
        }
    }
    return false;
}

static stock TaskBarEvent_SetUniqueId(playerid, id)
    e_Data[playerid][E_DATA_UNIQUE_ID] = id;

static stock TaskBarEvent_GetUniqueId(playerid)
    return e_Data[playerid][E_DATA_UNIQUE_ID];

static stock TaskBarEvent_SetPage(playerid, value)
    e_Data[playerid][E_DATA_PAGE] = value;

static stock TaskBarEvent_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock TaskBarEvent_SetPages(playerid, value)
    e_Data[playerid][E_DATA_PAGES] = value;

static stock TaskBarEvent_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_TASKBAR_PROJECTS(playerid, response, listitem) {

    if(response) {

        switch(listitem) {
            case 0: {
                if(Session_Has())
                    return SendMessage(playerid, -1, ""#MESSAGE_RED"There is an open project currently.");

                TaskBarEvent_Create(playerid);
            }

            case 1: {
                if(Session_Has())
                    return SendMessage(playerid, -1, ""#MESSAGE_RED"There is an open project currently.");
                
                TaskBarEvent_Projects(playerid);
            }

            case 2: {
                if(!Session_Has())
                    return SendMessage(playerid, -1, ""#MESSAGE_RED"There are no open projects.");

                Session_Close();
            }
        }
    }
    return true;
}

Dialog:D_TASKBAR_CREATE(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {
        TaskBarEvent_OpenProjectName(playerid, inputtext);
        return true;
    }

    TaskBarEvent_Show(playerid);
    return true;
}

DialogMod:D_TASKBAR_PROJECTS(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case -1337: TaskBarEvent_ProjectPage(playerid, TaskBarEvent_GetPage(playerid) - 1);
            case -1338: TaskBarEvent_ProjectPage(playerid, TaskBarEvent_GetPage(playerid) + 1);
            default: TaskBarEvent_ProjectOptions(playerid, params);
        }
    }
    return true;
}

DialogMod:D_TASKBAR_PROJECT(playerid, response, inputtext[], params) {

    if(response) {

        new uniqueId = TaskBarEvent_GetUniqueId(playerid);

        switch(params) {
            case 0: {
                TaskBarEvent_OpenProject(uniqueId);
                SendMessage(INVALID_PLAYER_ID, -1, ""#MESSAGE_GREEN"Project ID (%d) was successfully loaded.", uniqueId);
                return true;
            }
            case 1: {
                TaskBarEvent_DeleteProject(uniqueId);
                SendMessage(INVALID_PLAYER_ID, -1, ""#MESSAGE_GREEN"Project ID (%d) was successfully destroyed.", uniqueId);
            }
            case 2: {
                Dialog_Show(playerid, D_TASKBAR_RENAME, DIALOG_STYLE_INPUT, "Rename", "What name would you like to give this project?", "Confirm", "Back");
                return true;
            }
        }
    }

    TaskBarEvent_ProjectSamePage(playerid);
    return true;
}

Dialog:D_TASKBAR_RENAME(playerid, response, listitem, inputtext[]) {

    new uniqueId = TaskBarEvent_GetUniqueId(playerid);

    if(response && !isnull(inputtext)) {
        if(TaskBarEvent_RenameProject(uniqueId, inputtext))
            SendMessage(playerid, -1, ""#MESSAGE_GREEN"Project renamed to {CCCCCC}\"%s\"", inputtext);
        else
            SendMessage(playerid, -1, ""#MESSAGE_RED"There is another project with that name");
    }

    TaskBarEvent_ProjectOptions(playerid, uniqueId);
    return true;
}