
            // Tables
#include "src/connections/tables.inc"

            // Includes
#include <YSI_Coding\y_hooks>

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
    return Y_HOOKS_CONTINUE_RETURN_1;
}