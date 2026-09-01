
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    switch(type) {
        case E_TYPETASKBUTTON_POSITION: {TaskBarKey_Set(playerid, E_TYPEKEY_POSITION); return Y_HOOKS_BREAK_RETURN_1;}
        case E_TYPETASKBUTTON_SIZE: {TaskBarKey_Set(playerid, E_TYPEKEY_SIZE); return Y_HOOKS_BREAK_RETURN_1;}
        case E_TYPETASKBUTTON_LETTERSIZE: {TaskBarKey_Set(playerid, E_TYPEKEY_LETTER_SIZE); return Y_HOOKS_BREAK_RETURN_1;}
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}