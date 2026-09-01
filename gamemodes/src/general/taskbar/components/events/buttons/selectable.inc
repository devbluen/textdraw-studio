
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_SELECTABLE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new index = TaskBarTextDraw_GetSelected(playerid);
    SessionTextDrawData_SetSelect(index, !SessionTextDrawData_GetSelect(index));
    return Y_HOOKS_BREAK_RETURN_1;
}