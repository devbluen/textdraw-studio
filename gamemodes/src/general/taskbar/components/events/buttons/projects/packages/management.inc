
            // Includes
#include <YSI_Coding\y_hooks>

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

    new dialog[15 * 3];
    strcat(dialog, "New Workspace\n");
    strcat(dialog, "Open Project\n");
    strcat(dialog, "Exit Studio");

    Dialog_Show(playerid, D_TASKBAR_PROJECTS, DIALOG_STYLE_TABLIST, "Project", dialog, "Select", "Close");
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

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "INSERT INTO projects (name, `date`) VALUES ('%s', '%s')", name, "00/00/0000 00:00");
    if(cache) {
        DB_FreeResultSet(cache);
        TaskBarEventProjectLoad_OpenProjectName(playerid, name);
        SendMessage(playerid, -1, ""#MESSAGE_GREEN"The {CCCCCC}\"%s\"{FFFFFF} project was successfully created.", name);
        return;
    }

    SendMessage(playerid, -1, ""#MESSAGE_RED"It was not possible to create the {CCCCCC}\"%s\"{FFFFFF} project.", name);
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

*/

Dialog:D_TASKBAR_PROJECTS(playerid, response, listitem) {

    if(response) {
        switch(listitem) {

            case 0: {
                if(Session_Has()) return SendMessage(playerid, -1, ""#MESSAGE_RED"There is an open project currently.");
                TaskBarEventProjectCreate_Show(playerid);
            }

            case 1: {
                if(Session_Has()) return SendMessage(playerid, -1, ""#MESSAGE_RED"There is an open project currently.");
                TaskBarEventProjectList_Show(playerid);
            }

            case 2: {
                if(!Session_Has()) return SendMessage(playerid, -1, ""#MESSAGE_RED"There are no open projects.");
                
                Session_Destroy();
                TaskBarEventProjectLoad_Show(playerid);

                SendMessage(INVALID_PLAYER_ID, -1, ""#MESSAGE_GREEN"Project was successfully completed.");
            }
        }
    }
    return true;
}