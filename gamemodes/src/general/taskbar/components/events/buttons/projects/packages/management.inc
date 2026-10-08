
            // Includes
#include <YSI_Coding\y_hooks>

static enum {
    E_BUTTON_EXPORT,
    E_BUTTON_IMPORT,
    E_BUTTON_EXIT,
    E_BUTTON_NEW,
    E_BUTTON_OPEN
};

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_PROJECT)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEventProjectLoad_Show(playerid);
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

stock TaskBarEventProjectLoad_Show(playerid) {

    inline TaskBarEventProjectShowed() {

        switch(Session_Has())
        {
            case true: {
                DialogMod_Add(playerid, L(playerid, E_LANG_PRJ_EXPORT), E_BUTTON_EXPORT);
                DialogMod_Add(playerid, L(playerid, E_LANG_PRJ_IMPORT), E_BUTTON_IMPORT);
                DialogMod_Add(playerid, L(playerid, E_LANG_PRJ_EXIT), E_BUTTON_EXIT);
            }

            case false: {
                DialogMod_Add(playerid, L(playerid, E_LANG_PRJ_NEW), E_BUTTON_NEW);
                DialogMod_Add(playerid, L(playerid, E_LANG_PRJ_OPEN), E_BUTTON_OPEN);
            }
        }
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_PROJECT), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CLOSE), "D_TASKBAR_PROJECTS", using inline TaskBarEventProjectShowed);
}

stock TaskBarEventProjectLoad_OpenProjectName(playerid, const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM `projects` WHERE `name` = '%s'", name);
    if(cache) {

        new uniqueId;

        if(!DB_GetRowCount(cache)) {
            TaskBarEventProjectLoad_CreateProject(playerid, name);
            return;
        }
        else uniqueId = DB_GetFieldIntByName(cache, "id");

        DB_FreeResultSet(cache);
        TaskBarEventProjectLoad_OpenProject(uniqueId);
    }
}

static stock TaskBarEventProjectLoad_CreateProject(playerid, const name[]) {

    new date[34 + 1];
    Util_ConvertTimestamp(gettime(), date, 0);

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "INSERT INTO projects (name, `date`) VALUES ('%s', '%s')", name, date);
    if(cache) {
        DB_FreeResultSet(cache);
        TaskBarEventProjectLoad_OpenProjectName(playerid, name);
        SendLang(playerid, -1, E_LANG_MSG_PRJ_CREATED, name);
        return;
    }

    SendLang(playerid, -1, E_LANG_MSG_PRJ_CREATE_FAIL, name);
}

stock bool:TaskBarEventProjectLoad_RenameProject(uniqueId, const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM projects WHERE name = '%s'", name);
    if(cache) {
        DB_FreeResultSet(cache);
        cache = DB_ExecuteQuery(IDConnection, "UPDATE projects SET name = '%s' WHERE id = %i", name, uniqueId);
        if(cache) {
            DB_FreeResultSet(cache);
            return true;
        }
    }
    return false;
}

stock TaskBarEventProjectLoad_DeleteProject(uniqueId) {

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection, 
            "DELETE FROM projects WHERE id = %i", 
                uniqueId
        )
    );
}

stock TaskBarEventProjectLoad_OpenProject(uniqueId)
    Session_Create(uniqueId);



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

DialogMod:D_TASKBAR_PROJECTS(playerid, response, inputtext[], listitem) {

    if(response) {
        switch(listitem) {

            case -1: TaskBarEventProjectLoad_Show(playerid);

            case E_BUTTON_NEW: {
                if(Session_Has()) 
                    return SendLang(playerid, -1, E_LANG_ERR_PROJECT_OPEN);

                TaskBarEventProjectCreate_Show(playerid);
            }

            case E_BUTTON_OPEN: {
                if(Session_Has()) 
                    return SendLang(playerid, -1, E_LANG_ERR_PROJECT_OPEN);

                TaskBarEventProjectList_Show(playerid);
            }

            case E_BUTTON_EXIT: {
                if(!Session_Has()) 
                    return SendLang(playerid, -1, E_LANG_ERR_NO_PROJECT);
                
                Session_Destroy();
                TaskBarEventProjectLoad_Show(playerid);

                SendLang(INVALID_PLAYER_ID, -1, E_LANG_MSG_PRJ_CLOSED);
            }

            case E_BUTTON_EXPORT: TaskBarEventProjectExport_Show(playerid);
            case E_BUTTON_IMPORT: TaskBarEventProjectImport_Show(playerid);
        }
    }
    return true;
}