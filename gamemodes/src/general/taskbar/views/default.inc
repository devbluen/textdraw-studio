
new PlayerText:taskBarView[MAX_PLAYERS][24];

stock TextBarView_Create(playerid) {

    taskBarView[playerid][0] = CreatePlayerTextDraw(playerid, 20.000, 414.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][0], 599.000, 32.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][0], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][0], 505290495);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][0], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][0], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][0], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][0], true);

    taskBarView[playerid][1] = CreatePlayerTextDraw(playerid, 21.000, 415.000, "textdrawStudio:project");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][1], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][1], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][1], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][1], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][1], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][1], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][1], true);

    taskBarView[playerid][2] = CreatePlayerTextDraw(playerid, 47.000, 415.000, "textdrawStudio:config");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][2], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][2], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][2], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][2], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][2], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][2], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][2], true);

    taskBarView[playerid][3] = CreatePlayerTextDraw(playerid, 73.000, 415.000, "textdrawStudio:itens");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][3], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][3], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][3], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][3], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][3], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][3], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][3], true);

    taskBarView[playerid][4] = CreatePlayerTextDraw(playerid, 99.000, 415.000, "textdrawStudio:group");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][4], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][4], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][4], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][4], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][4], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][4], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][4], true);

    taskBarView[playerid][5] = CreatePlayerTextDraw(playerid, 125.000, 415.000, "textdrawStudio:create");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][5], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][5], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][5], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][5], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][5], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][5], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][5], true);

    taskBarView[playerid][6] = CreatePlayerTextDraw(playerid, 151.000, 415.000, "textdrawStudio:copy");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][6], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][6], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][6], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][6], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][6], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][6], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][6], true);

    taskBarView[playerid][7] = CreatePlayerTextDraw(playerid, 177.000, 415.000, "textdrawStudio:delete");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][7], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][7], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][7], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][7], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][7], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][7], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][7], true);

    taskBarView[playerid][8] = CreatePlayerTextDraw(playerid, 203.000, 415.000, "textdrawStudio:position");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][8], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][8], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][8], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][8], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][8], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][8], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][8], true);

    taskBarView[playerid][9] = CreatePlayerTextDraw(playerid, 229.000, 415.000, "textdrawStudio:size");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][9], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][9], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][9], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][9], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][9], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][9], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][9], true);

    taskBarView[playerid][10] = CreatePlayerTextDraw(playerid, 255.000, 415.000, "textdrawStudio:letterSize");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][10], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][10], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][10], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][10], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][10], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][10], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][10], true);

    taskBarView[playerid][11] = CreatePlayerTextDraw(playerid, 281.000, 415.000, "textdrawStudio:text");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][11], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][11], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][11], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][11], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][11], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][11], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][11], true);

    taskBarView[playerid][12] = CreatePlayerTextDraw(playerid, 307.000, 415.000, "textdrawStudio:font1");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][12], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][12], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][12], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][12], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][12], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][12], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][12], true);

    taskBarView[playerid][13] = CreatePlayerTextDraw(playerid, 333.000, 415.000, "textdrawStudio:alignLeft");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][13], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][13], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][13], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][13], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][13], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][13], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][13], true);

    taskBarView[playerid][14] = CreatePlayerTextDraw(playerid, 359.000, 415.000, "textdrawStudio:proportionChecked");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][14], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][14], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][14], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][14], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][14], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][14], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][14], true);

    taskBarView[playerid][15] = CreatePlayerTextDraw(playerid, 385.000, 415.000, "textdrawStudio:outline");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][15], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][15], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][15], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][15], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][15], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][15], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][15], true);

    taskBarView[playerid][16] = CreatePlayerTextDraw(playerid, 411.000, 415.000, "textdrawStudio:shadow");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][16], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][16], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][16], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][16], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][16], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][16], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][16], true);

    taskBarView[playerid][17] = CreatePlayerTextDraw(playerid, 437.000, 415.000, "textdrawStudio:color");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][17], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][17], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][17], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][17], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][17], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][17], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][17], true);

    taskBarView[playerid][18] = CreatePlayerTextDraw(playerid, 463.000, 415.000, "textdrawStudio:colorBg");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][18], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][18], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][18], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][18], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][18], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][18], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][18], true);

    taskBarView[playerid][19] = CreatePlayerTextDraw(playerid, 489.000, 415.000, "textdrawStudio:colorBox");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][19], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][19], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][19], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][19], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][19], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][19], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][19], true);

    taskBarView[playerid][20] = CreatePlayerTextDraw(playerid, 515.000, 415.000, "textdrawStudio:selectableUnabled");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][20], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][20], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][20], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][20], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][20], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][20], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][20], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][20], true);

    taskBarView[playerid][21] = CreatePlayerTextDraw(playerid, 541.000, 415.000, "textdrawStudio:models");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][21], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][21], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][21], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][21], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][21], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][21], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][21], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][21], true);

    taskBarView[playerid][22] = CreatePlayerTextDraw(playerid, 567.000, 415.000, "textdrawStudio:global");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][22], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][22], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][22], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][22], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][22], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][22], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][22], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][22], true);

    taskBarView[playerid][23] = CreatePlayerTextDraw(playerid, 593.000, 415.000, "textdrawStudio:rollback");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][23], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][23], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][23], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][23], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][23], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][23], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][23], true);

    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_PROJECT, taskBarView[playerid][1]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_CONFIG, taskBarView[playerid][2]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_ITENS, taskBarView[playerid][3]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_GROUP, taskBarView[playerid][4]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_CREATE, taskBarView[playerid][5]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_COPY, taskBarView[playerid][6]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_DELETE, taskBarView[playerid][7]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_POSITION, taskBarView[playerid][8]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_SIZE, taskBarView[playerid][9]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_LETTERSIZE, taskBarView[playerid][10]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_TEXT, taskBarView[playerid][11]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_FONT, taskBarView[playerid][12]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_ALIGN, taskBarView[playerid][13]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_PROPORTION, taskBarView[playerid][14]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_OUTLINE, taskBarView[playerid][15]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_SHADOW, taskBarView[playerid][16]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_COLOR, taskBarView[playerid][17]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_COLOR_BG, taskBarView[playerid][18]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_COLOR_BOX, taskBarView[playerid][19]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_SELECTABLE, taskBarView[playerid][20]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_MODELS, taskBarView[playerid][21]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_MODE, taskBarView[playerid][22]);
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_ROLLBACK, taskBarView[playerid][23]);

    for(new i = 0; i < sizeof taskBarView[]; i++)
        PlayerTextDrawShow(playerid, taskBarView[playerid][i]);
}

stock TextBarView_Show(playerid) {
    PlayerTextDrawShow(playerid, taskBarView[playerid][0]);
}

stock TextBarView_Hide(playerid) {
    PlayerTextDrawHide(playerid, taskBarView[playerid][0]);
}

stock TextBarView_Destroy(playerid) {

    for(new i = 0; i < sizeof taskBarView[]; i++) {
        PlayerTextDrawDestroy(playerid, taskBarView[playerid][i]);
        taskBarView[playerid][i] = INVALID_PLAYER_TEXT_DRAW;
    }
}