
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnUserLogin(playerid);
forward OnUserLogout(playerid);

hook OnPlayerSpawn(playerid) {

    SetPlayerSkin(playerid, 60);
    SetPlayerPos(playerid, 1923.5066, -2547.8245, 14.0469);
    SetPlayerFacingAngle(playerid, 89.9278);
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid) {

    Iter_Add(Users, playerid);
    Util_ClearChat(playerid);
    SpawnPlayer(playerid);

    CallLocalFunction("OnUserLogin", "i", playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    
    Iter_Remove(Users, playerid);
    CallLocalFunction("OnUserLogout", "i", playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}