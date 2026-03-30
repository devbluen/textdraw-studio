
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_MODE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    static const 
        E_TYPEMODE:typeAvailable[] = {
            E_TYPEMODE_PLAYER,
            E_TYPEMODE_GLOBAL
        };

    new 
        index = TaskBarTextDraw_GetSelected(playerid),
        E_TYPEMODE:currentType = SessionTextDrawData_GetMode(index)
    ;

    for(new i = 0; i < sizeof typeAvailable; i++) {
        if(typeAvailable[i] != currentType)
            continue;
        
        new 
            previsionIndex = i + 1,
            nextIndex = previsionIndex >= sizeof typeAvailable ? 0 : previsionIndex
        ;

        SessionTextDrawData_SetMode(index, typeAvailable[nextIndex]);
        break;
    }
    return Y_HOOKS_BREAK_RETURN_1;
}