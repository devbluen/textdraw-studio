
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnUserLogin(playerid);
forward OnUserLogout(playerid);

hook OnPlayerSpawn(playerid) {

    SetPlayerSkin(playerid, 60);
    
    Camera_Set(playerid, E_TYPECAMERA_PLAYER);
    TogglePlayerControllable(playerid, true);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid) {

    Iter_Add(Users, playerid);
    Util_ClearChat(playerid);

    SetPlayerVirtualWorld(playerid, random(999999));
    SpawnPlayer(playerid);

    CallLocalFunction("OnUserLogin", "i", playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    
    Iter_Remove(Users, playerid);
    CallLocalFunction("OnUserLogout", "i", playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
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

stock Auth_GetName(playerid) {
    new string[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, string);
    return string;
}