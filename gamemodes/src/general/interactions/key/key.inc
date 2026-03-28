
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys) {

    switch(newkeys) {
        case KEY_CTRL_BACK: {   // H
            TaskBar_Cursor(playerid, !TaskBar_GetCursor(playerid));
        }
    }

    printf("OnPlayerKeyStateChange: playerid=%d, newkeys=%d, oldkeys=%d", playerid, newkeys, oldkeys);
    return Y_HOOKS_BREAK_RETURN_1;
}