
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_GROUP)
        return Y_HOOKS_CONTINUE_RETURN_1;

    SessionPlayer_OpenListGroups(playerid);
    return Y_HOOKS_BREAK_RETURN_1;
}