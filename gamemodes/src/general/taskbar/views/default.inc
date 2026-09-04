
new PlayerText:taskBarView[MAX_PLAYERS][27];

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

    taskBarView[playerid][1] = CreatePlayerTextDraw(playerid, 9.000, 415.000, "textdrawStudio:project");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][1], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][1], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][1], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][1], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][1], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][1], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][1], true);

    taskBarView[playerid][2] = CreatePlayerTextDraw(playerid, 35.000, 415.000, "textdrawStudio:config");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][2], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][2], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][2], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][2], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][2], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][2], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][2], true);

    taskBarView[playerid][3] = CreatePlayerTextDraw(playerid, 61.000, 415.000, "textdrawStudio:itens");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][3], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][3], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][3], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][3], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][3], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][3], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][3], true);

    taskBarView[playerid][4] = CreatePlayerTextDraw(playerid, 87.000, 415.000, "textdrawStudio:group");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][4], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][4], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][4], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][4], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][4], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][4], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][4], true);

    taskBarView[playerid][5] = CreatePlayerTextDraw(playerid, 113.000, 415.000, "textdrawStudio:create");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][5], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][5], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][5], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][5], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][5], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][5], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][5], true);

    taskBarView[playerid][6] = CreatePlayerTextDraw(playerid, 139.000, 415.000, "textdrawStudio:copy");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][6], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][6], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][6], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][6], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][6], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][6], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][6], true);

    taskBarView[playerid][7] = CreatePlayerTextDraw(playerid, 165.000, 415.000, "textdrawStudio:delete");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][7], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][7], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][7], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][7], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][7], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][7], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][7], true);

    taskBarView[playerid][8] = CreatePlayerTextDraw(playerid, 191.000, 415.000, "textdrawStudio:position");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][8], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][8], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][8], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][8], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][8], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][8], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][8], true);

    taskBarView[playerid][9] = CreatePlayerTextDraw(playerid, 217.000, 415.000, "textdrawStudio:size");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][9], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][9], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][9], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][9], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][9], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][9], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][9], true);

    taskBarView[playerid][10] = CreatePlayerTextDraw(playerid, 243.000, 415.000, "textdrawStudio:letterSize");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][10], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][10], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][10], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][10], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][10], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][10], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][10], true);

    taskBarView[playerid][11] = CreatePlayerTextDraw(playerid, 269.000, 415.000, "textdrawStudio:text");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][11], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][11], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][11], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][11], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][11], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][11], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][11], true);

    taskBarView[playerid][12] = CreatePlayerTextDraw(playerid, 295.000, 415.000, "textdrawStudio:font1");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][12], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][12], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][12], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][12], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][12], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][12], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][12], true);

    taskBarView[playerid][13] = CreatePlayerTextDraw(playerid, 321.000, 415.000, "textdrawStudio:alignLeft");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][13], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][13], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][13], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][13], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][13], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][13], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][13], true);

    taskBarView[playerid][14] = CreatePlayerTextDraw(playerid, 347.000, 415.000, "textdrawStudio:proportionChecked");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][14], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][14], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][14], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][14], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][14], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][14], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][14], true);

    taskBarView[playerid][15] = CreatePlayerTextDraw(playerid, 373.000, 415.000, "textdrawStudio:outline");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][15], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][15], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][15], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][15], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][15], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][15], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][15], true);

    taskBarView[playerid][16] = CreatePlayerTextDraw(playerid, 399.000, 415.000, "textdrawStudio:shadow");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][16], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][16], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][16], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][16], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][16], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][16], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][16], true);

    taskBarView[playerid][17] = CreatePlayerTextDraw(playerid, 425.000, 415.000, "textdrawStudio:color");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][17], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][17], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][17], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][17], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][17], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][17], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][17], true);

    taskBarView[playerid][18] = CreatePlayerTextDraw(playerid, 451.000, 415.000, "textdrawStudio:colorBg");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][18], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][18], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][18], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][18], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][18], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][18], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][18], true);

    taskBarView[playerid][19] = CreatePlayerTextDraw(playerid, 477.000, 415.000, "textdrawStudio:colorBox");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][19], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][19], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][19], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][19], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][19], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][19], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][19], true);

    taskBarView[playerid][20] = CreatePlayerTextDraw(playerid, 529.000, 415.000, "textdrawStudio:selectableUnabled");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][20], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][20], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][20], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][20], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][20], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][20], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][20], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][20], true);

    taskBarView[playerid][21] = CreatePlayerTextDraw(playerid, 555.000, 415.000, "textdrawStudio:models");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][21], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][21], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][21], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][21], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][21], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][21], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][21], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][21], true);

    taskBarView[playerid][22] = CreatePlayerTextDraw(playerid, 581.000, 415.000, "textdrawStudio:global");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][22], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][22], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][22], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][22], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][22], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][22], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][22], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][22], true);

    taskBarView[playerid][23] = CreatePlayerTextDraw(playerid, 607.000, 415.000, "textdrawStudio:rollback");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][23], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][23], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][23], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][23], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][23], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][23], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][23], true);

    taskBarView[playerid][24] = CreatePlayerTextDraw(playerid, 503.000, 415.000, "textdrawStudio:boxChecked");
    PlayerTextDrawTextSize(playerid, taskBarView[playerid][24], 25.000, 30.000);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][24], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][24], 0);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][24], 255);
    PlayerTextDrawFont(playerid, taskBarView[playerid][24], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][24], true);
    PlayerTextDrawSetSelectable(playerid, taskBarView[playerid][24], true);

    taskBarView[playerid][25] = CreatePlayerTextDraw(playerid, 263.000, 375.000, "~y~X:~w~ 0.00     ~y~Y:~w~ 0.00     ~r~Speed:~w~ 1.0");
    PlayerTextDrawLetterSize(playerid, taskBarView[playerid][25], 0.200, 1.099);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][25], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][25], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][25], 1);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][25], 150);
    PlayerTextDrawFont(playerid, taskBarView[playerid][25], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][25], true);

    taskBarView[playerid][26] = CreatePlayerTextDraw(playerid, 627.000, 404.000, "~y~[ARROWS]~w~ - Move Textdraw   ~y~[N]~w~ - Edit Data   ~y~[H]~w~ - Change Speed   ~y~[Y]~w~ - Show/Hide Tips   ~y~[ENTER]~w~ - Save");
    PlayerTextDrawLetterSize(playerid, taskBarView[playerid][26], 0.150, 0.699);
    PlayerTextDrawAlignment(playerid, taskBarView[playerid][26], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColour(playerid, taskBarView[playerid][26], -1);
    PlayerTextDrawSetShadow(playerid, taskBarView[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, taskBarView[playerid][26], 1);
    PlayerTextDrawBackgroundColour(playerid, taskBarView[playerid][26], 150);
    PlayerTextDrawFont(playerid, taskBarView[playerid][26], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, taskBarView[playerid][26], true);

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
    TaskBarButton_Create(playerid, E_TYPETASKBUTTON_BOX, taskBarView[playerid][24]);

    for(new i = 0; i < sizeof taskBarView[]; i++)
        PlayerTextDrawShow(playerid, taskBarView[playerid][i]);

    TaskBarView_ApplyLang(playerid);
    TaskBarView_HideInfo(playerid);
    TaskBarView_HideTips(playerid);
}

stock TaskBarView_ApplyLang(playerid) {
    PlayerTextDrawSetString(playerid, taskBarView[playerid][26], L(playerid, E_LANG_TIPS_MOVE));
}

stock TaskBarView_Show(playerid)
    PlayerTextDrawShow(playerid, taskBarView[playerid][0]);

stock TaskBarView_Hide(playerid)
    PlayerTextDrawHide(playerid, taskBarView[playerid][0]);

stock TaskBarView_ShowInfo(playerid)
    PlayerTextDrawShow(playerid, taskBarView[playerid][25]);

stock TaskBarView_HideInfo(playerid)
    PlayerTextDrawHide(playerid, taskBarView[playerid][25]);

stock TaskBarView_SetInfo(playerid, const string[])
    PlayerTextDrawSetString(playerid, taskBarView[playerid][25], string);

stock TaskBarView_ShowTips(playerid)
    PlayerTextDrawShow(playerid, taskBarView[playerid][26]);

stock TaskBarView_HideTips(playerid)
    PlayerTextDrawHide(playerid, taskBarView[playerid][26]);

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