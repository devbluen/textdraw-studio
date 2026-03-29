
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_SELECTABLE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new index = TaskBarTextdraw_GetSelected(playerid);
    SessionTextdrawData_SetSelect(index, !SessionTextdrawData_GetSelect(index));
    return Y_HOOKS_BREAK_RETURN_1;
}