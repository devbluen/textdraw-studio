
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_PROPORTION)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new index = TaskBarTextDraw_GetSelected(playerid);
    SessionTextDrawData_SetPropor(index, !SessionTextDrawData_GetPropor(index));
    return Y_HOOKS_BREAK_RETURN_1;
}