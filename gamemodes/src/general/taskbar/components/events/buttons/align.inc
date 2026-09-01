
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_ALIGN)
        return Y_HOOKS_CONTINUE_RETURN_1;

    static const 
        E_TYPEALIGNMENT:typeAvailable[] = {
            E_TYPEALIGNMENT_LEFT,
            E_TYPEALIGNMENT_CENTER,
            E_TYPEALIGNMENT_RIGHT
        };

    new 
        index = TaskBarTextDraw_GetSelected(playerid),
        E_TYPEALIGNMENT:currentType = SessionTextDrawData_GetAlign(index)
    ;

    for(new i = 0; i < sizeof typeAvailable; i++) {
        if(typeAvailable[i] != currentType)
            continue;
        
        new 
            previsionIndex = i + 1,
            nextIndex = previsionIndex >= sizeof typeAvailable ? 0 : previsionIndex
        ;

        SessionTextDrawData_SetAlign(index, typeAvailable[nextIndex]);
        break;
    }
    return Y_HOOKS_BREAK_RETURN_1;
}