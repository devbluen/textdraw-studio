


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarButton_Create(playerid, E_TYPETASKBUTTON:type, PlayerText:draw) {

    new index = _:type;

    e_TaskBarButton[playerid][index][E_TASKBARBUTTON_DRAWID] = draw;
    
    // Get Default Informations
    PlayerTextDrawGetPos(playerid, draw, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_POSITION][0], e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_POSITION][1]);

    // Set Default Informations
    TaskBarButton_Show(playerid, type);
    TaskBarButton_Enable(playerid, type);

    PlayerTextDrawCreateClick(playerid, "TaskBar_Buttons", draw, index);
    Iter_Add(TaskBarButtons[playerid], index);
}

stock bool:TaskBarButton_IsValid(playerid, E_TYPETASKBUTTON:type)
    return Iter_Contains(TaskBarButtons[playerid], _:type);

stock bool:TaskBarButton_IsDisplayed(playerid, E_TYPETASKBUTTON:type)
    return e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_VISIBILITY];

stock TaskBarButton_Show(playerid, E_TYPETASKBUTTON:type) {
    e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_VISIBILITY] = true;
    PlayerTextDrawShow(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID]);
}

stock TaskBarButton_Hide(playerid, E_TYPETASKBUTTON:type) {
    e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_VISIBILITY] = false;
    PlayerTextDrawHide(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID]);
}

stock TaskBarButton_Disable(playerid, E_TYPETASKBUTTON:type) {
    e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_STATUS] = false;
    PlayerTextDrawColour(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID], 0x303030CC);
    PlayerTextDrawSetSelectable(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID], false);

    if(TaskBarButton_IsDisplayed(playerid, type))
        TaskBarButton_Show(playerid, type);
}

stock TaskBarButton_Enable(playerid, E_TYPETASKBUTTON:type) {

    e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_STATUS] = true;
    PlayerTextDrawColour(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID], -1);
    PlayerTextDrawSetSelectable(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID], true);

    if(TaskBarButton_IsDisplayed(playerid, type))
        TaskBarButton_Show(playerid, type);
}

stock bool:TaskBarButton_Enabled(playerid, E_TYPETASKBUTTON:type)
    return e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_STATUS];

stock TaskBarButton_HideAll(playerid) {
    
    foreach(new i: TaskBarButtons[playerid])
        TaskBarButton_Hide(playerid, E_TYPETASKBUTTON:i);

    TaskBarView_Hide(playerid);
}

stock TaskBarButton_ShowAll(playerid) {
    foreach(new i: TaskBarButtons[playerid])
        TaskBarButton_Show(playerid, E_TYPETASKBUTTON:i);

    TaskBarView_Show(playerid);

    TaskBarButton_DisableAll(playerid);
    TaskBarEventUpdate_Buttons(playerid);
}

stock TaskBarButton_DisableAll(playerid) {
    foreach(new i: TaskBarButtons[playerid])
        TaskBarButton_Disable(playerid, E_TYPETASKBUTTON:i);
}

stock TaskBarButton_EnableAll(playerid) {
    foreach(new i: TaskBarButtons[playerid])
        TaskBarButton_Enable(playerid, E_TYPETASKBUTTON:i);
}

stock TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON:type, const sprite[]) {
    PlayerTextDrawSetString(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID], "textdrawStudio:%s", sprite);
}

stock TaskBarButton_GetPos(playerid, E_TYPETASKBUTTON:type, &Float:x, &Float:y) {
    x = e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_POSITION][0];
    y = e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_POSITION][1];
}

stock TaskBarButton_SetPos(playerid, E_TYPETASKBUTTON:type, Float:x, Float:y) {

    PlayerTextDrawSetPos(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID], x, y);

    if(TaskBarButton_IsDisplayed(playerid, type))
        PlayerTextDrawShow(playerid, e_TaskBarButton[playerid][_:type][E_TASKBARBUTTON_DRAWID]);
}