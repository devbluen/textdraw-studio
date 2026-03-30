
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_COPY)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new 
        currentIndex = TaskBarTextDraw_GetSelected(playerid),
        index = SessionTextDrawData_Copy(currentIndex)
    ;

    TaskBarTextDraw_Select(playerid, index);
    SendMessage(playerid, -1, ""#MESSAGE_GREEN"Textdraw copied successfully.");
    return Y_HOOKS_BREAK_RETURN_1;
}