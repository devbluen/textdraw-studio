
            // Tables
#include "src/connections/tables.inc"

            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnConnectionGithub(index, response_code, data[]);

hook OnGameModeInit() {

    // Database
    IDConnection = DB_Open("textdrawStudio.db");
    if(IDConnection) Logger("Connection established successfully");
    else
    {
        Logger("Connection to database.db failed. Create this file in scriptfiles.");
        SendRconCommand("exit");
        return Y_HOOKS_BREAK_RETURN_1;
    }

    // Check Version
    HTTP(0, HTTP_GET, "raw.githubusercontent.com/devbluen/textdraws-studio/main/version.txt", "", "OnConnectionGithub");

    // Visuals
    SendRconCommand("name %s", "Textdraw Studio - "#STUDIO_VERSION"");

    // Prepare Tables
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "PRAGMA foreign_keys = ON;"));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableProjects));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableTextdraws));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableGroups));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableGroupsTextDraws));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableSprites));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableSpritesFavorites));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTablesColors));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableUserLanguage));
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnConnectionGithub(index, response_code, data[]) {

    switch(response_code) {
        case 200: {
            if(strfind(data, STUDIO_VERSION, true) != -1) Logger("You are on the latest version.");
            else if(strfind(data, "404: Not Found", true) != -1) Logger("It was not possible to verify the version directly in the repository.");
            else
            {
                Logger("New version found -> %s", data);
                Logger("Download: https://github.com/devbluen/textdraws-studio/releases");
            }
        }
        default: Logger("There was a failure communicating with GitHub.");
    }
}