
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_BOX)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new index = TaskBarTextDraw_GetSelected(playerid);
    SessionTextDrawData_SetBox(index, !SessionTextDrawData_GetBox(index));
    return Y_HOOKS_BREAK_RETURN_1;
}