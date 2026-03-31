
            // Definers
#define     MAX_TASKBAR_MAX_BUTTONS     _:E_TYPETASKBUTTON_MAX

            // Forwards
forward OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type);
forward OnPlayerTaskBarDrawSelected(playerid, index);
forward OnPlayerTaskBarDrawUnSelected(playerid);

enum E_TASKBAR {
    E_TASKBAR_CREATED,
    bool:E_TASKBAR_CURSOR
};

enum E_TASKBARBUTTON {
    bool:E_TASKBARBUTTON_STATUS,
    bool:E_TASKBARBUTTON_VISIBILITY,
    PlayerText:E_TASKBARBUTTON_DRAWID,
    Float:E_TASKBARBUTTON_POSITION[2]
};

new
    Iterator:TaskBarButtons[MAX_PLAYERS]<MAX_TASKBAR_MAX_BUTTONS>,
    e_TaskBar[MAX_PLAYERS][E_TASKBAR],
    e_TaskBarButton[MAX_PLAYERS][MAX_TASKBAR_MAX_BUTTONS][E_TASKBARBUTTON]
;