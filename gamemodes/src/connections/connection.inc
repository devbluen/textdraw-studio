
#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {

    IDConnection = DB_Open("textdrawStudio.db");

    if(IDConnection) Logger("Connection established successfully");
    else
    {
        Logger("Connection to database.db failed. Create this file in scriptfiles.");
        SendRconCommand("exit");
        return Y_HOOKS_BREAK_RETURN_1;
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}