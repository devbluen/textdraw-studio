
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_FONT)
        return Y_HOOKS_CONTINUE_RETURN_1;

    static const 
        E_TYPEFONT:typeAvailable[] = {
            E_TYPEFONT_0,
            E_TYPEFONT_1,
            E_TYPEFONT_2,
            E_TYPEFONT_3
        };

    new 
        index = TaskBarTextDraw_GetSelected(playerid),
        E_TYPEFONT:currentType = SessionTextDrawData_GetFont(index)
    ;

    for(new i = 0; i < sizeof typeAvailable; i++) {
        if(typeAvailable[i] != currentType)
            continue;
        
        new 
            previsionIndex = i + 1,
            nextIndex = previsionIndex >= sizeof typeAvailable ? 0 : previsionIndex
        ;

        SessionTextDrawData_SetFont(index, typeAvailable[nextIndex]);
        break;
    }
    return Y_HOOKS_BREAK_RETURN_1;
}