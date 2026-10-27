
new PlayerText:taskBarView[MAX_PLAYERS][28];

static const e_TaskBarSprites[][] = {
    "project",
    "config",
    "itens",
    "trash",
    "group",
    "create",
    "copy",
    "delete",
    "position",
    "size",
    "letterSize",
    "text",
    "font1",
    "alignLeft",
    "proportionChecked",
    "outline",
    "shadow",
    "color",
    "colorBg",
    "colorBox",
    "boxChecked",
    "selectableUnabled",
    "models",
    "global",
    "rollback"
};

stock TaskBarView_Create(playerid) {

    taskBarView[playerid][0] = CreatePlayerTextDraw(playerid, 8.000, 414.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][0], 625.000, 32.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][0], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][0], 505290495);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][0], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][0], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][0], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][0], true);

    new string[64];

    for(new i = 0; i < _:E_TYPETASKBUTTON_MAX; i++) {

        new slot = i + 1;

        format(string, sizeof string, "textdrawStudio:%s", e_TaskBarSprites[i]);

        taskBarView[playerid][slot] = CreatePlayerTextDraw(playerid, 9.000 + (float(i) * 25.000), 415.000, string);
        PlayerTextDrawTextSize(playerid, taskBarView[playerid][slot], 24.000, 30.000);
        PlayerTextDrawAlignment(playerid, taskBarView[playerid][slot], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColour(playerid, taskBarView[playerid][slot], -1);
        PlayerTextDrawSetShadow(playerid, taskBarView[playerid][slot], 0);
        PlayerTextDrawSetOutline(playerid, taskBarView[playerid][slot], 0);
        PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][slot], 255);
        PlayerTextDrawFont(playerid, taskBarView[playerid][slot], TEXT_DRAW_FONT_SPRITE_DRAW);
        PlayerTextDrawSetProportional(playerid, taskBarView[playerid][slot], true);
        PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][slot], true);

        TaskBarButton_Create(playerid, E_TYPETASKBUTTON:i, taskBarView[playerid][slot]);
    }

    taskBarView[playerid][26] = CreatePlayerTextDraw(playerid, 263.000, 375.000, "~y~X:~w~ 0.00     ~y~Y:~w~ 0.00     ~r~Speed:~w~ 1.0");
    PlayerTextDrawLetterSize(playerid, taskBarView[playerid][26], 0.200, 1.099);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][26], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][26], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][26], 1);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][26], 150);
    PlayerTextDrawFont(playerid, taskBarView[playerid][26], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][26], true);

    taskBarView[playerid][27] = CreatePlayerTextDraw(playerid, 627.000, 404.000, "~y~[ARROWS]~w~ - Move Textdraw   ~y~[N]~w~ - Edit Data   ~y~[H]~w~ - Change Speed   ~y~[Y]~w~ - Show/Hide Tips   ~y~[ENTER]~w~ - Save");
    PlayerTextDrawLetterSize(playerid, taskBarView[playerid][27], 0.150, 0.699);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][27], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][27], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][27], 1);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][27], 150);
    PlayerTextDrawFont(playerid, taskBarView[playerid][27], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][27], true);

    for(new i = 0; i < sizeof taskBarView[]; i++)
        PlayerTextDrawShow(playerid, taskBarView[playerid][i]);

    TaskBarView_ApplyLang(playerid);
    TaskBarView_HideInfo(playerid);
    TaskBarView_HideTips(playerid);
}

stock TaskBarView_ApplyLang(playerid) {
    PlayerTextDrawSetString(playerid, taskBarView[playerid][27], L(playerid, E_LANG_TIPS_MOVE));
}

stock TaskBarView_Show(playerid)
    PlayerTextDrawShow(playerid, taskBarView[playerid][0]);

stock TaskBarView_Hide(playerid)
    PlayerTextDrawHide(playerid, taskBarView[playerid][0]);

stock TaskBarView_ShowInfo(playerid)
    PlayerTextDrawShow(playerid, taskBarView[playerid][26]);

stock TaskBarView_HideInfo(playerid)
    PlayerTextDrawHide(playerid, taskBarView[playerid][26]);

stock TaskBarView_SetInfo(playerid, const string[])
    PlayerTextDrawSetString(playerid, taskBarView[playerid][26], string);

stock TaskBarView_ShowTips(playerid)
    PlayerTextDrawShow(playerid, taskBarView[playerid][27]);

stock TaskBarView_HideTips(playerid)
    PlayerTextDrawHide(playerid, taskBarView[playerid][27]);

stock TaskBarView_SetPosition(playerid, offset) {

    new Float:position[2];
    
    if(IsPlayerTextDrawVisible(playerid, taskBarView[playerid][0])) {
        PlayerTextDrawSetPos(playerid, taskBarView[playerid][0], 8.000, 414.000 - offset);
        PlayerTextDrawShow(playerid, taskBarView[playerid][0]);
    }

    foreach(new i: TaskBarButtons[playerid]) {
        TaskBarButton_GetPos(playerid, E_TYPETASKBUTTON:i, position[0], position[1]);
        TaskBarButton_SetPos(playerid, E_TYPETASKBUTTON:i, position[0], position[1] - offset);
    }
}

stock TaskBarView_Destroy(playerid) {

    for(new i = 0; i < sizeof taskBarView[]; i++) 
        PlayerTextDrawHide(playerid, taskBarView[playerid][i]);
}
