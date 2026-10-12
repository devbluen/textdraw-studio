/*
    Rounded Box (background com bordas arredondadas)

    Mapeamento dos dados do item:
        E_SESSIONDRAW_POSITION      -> X, Y (canto superior esquerdo)
        E_SESSIONDRAW_SIZE          -> largura, altura
        E_SESSIONDRAW_LETTER_SIZE[0]-> border radius
        E_SESSIONDRAW_COLOR         -> cor do background

    Montagem (igual ao border-radius do CSS, o raio e limitado a metade do menor lado):
        0: retangulo vertical    LD_SPAC:white  (x + r, y,     w - 2r, h)
        1: retangulo horizontal  LD_SPAC:white  (x,     y + r, w,      h - 2r)
        2..5: cantos             LD_BEAT:chit   (2r x 2r) TL, TR, BL, BR
*/

            // Definers
#define     ROUNDED_MAX_PIECES      (6)
#define     ROUNDED_SPRITE_BG       "LD_SPAC:white"
#define     ROUNDED_SPRITE_CORNER   "LD_BEAT:chit"
#define     ROUNDED_MIN_SIZE        (1.0)

// Margem transparente do LD_BEAT:chit em cada lado (fracao da textura).
// O circulo nao e centralizado na textura: fica um pouco mais para cima.
#define     ROUNDED_CHIT_MARGIN_LEFT    (0.164)
#define     ROUNDED_CHIT_MARGIN_RIGHT   (0.164)
#define     ROUNDED_CHIT_MARGIN_TOP     (0.158)
#define     ROUNDED_CHIT_MARGIN_BOTTOM  (0.17)



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'

*/

stock bool:SessionRounded_IsRounded(index)
{
    if (index < 0 || index >= MAX_TEXTDRAWS_STUDIO) return false;
    return e_SessionDraw[index][E_SESSIONDRAW_FONT] == E_TYPEFONT_ROUNDED;
}

stock Float:SessionRounded_GetMaxRadius(Float:width, Float:height)
    return (width < height ? width : height) / 2.0;

stock Float:SessionRounded_ClampRadius(Float:width, Float:height, Float:radius)
{
    new Float:maxRadius = SessionRounded_GetMaxRadius(width, height);

    if (radius < 0.0) radius = 0.0;
    if (radius > maxRadius) radius = maxRadius;
    return radius;
}

// Calcula uma peca do rounded box. Retorna false se a peca nao existe (tamanho zero).
stock bool:SessionRounded_GetPiece(piece, Float:x, Float:y, Float:width, Float:height, Float:radius, &Float:pieceX, &Float:pieceY, &Float:pieceW, &Float:pieceH, sprite[], maxlength = sizeof sprite)
{
    if (width < ROUNDED_MIN_SIZE) width = ROUNDED_MIN_SIZE;
    if (height < ROUNDED_MIN_SIZE) height = ROUNDED_MIN_SIZE;
    radius = SessionRounded_ClampRadius(width, height, radius);

    new Float:diameter = radius * 2.0;

    // Sem borda: um unico retangulo
    if (radius <= 0.0)
    {
        if (piece != 0) return false;

        pieceX = x; pieceY = y;
        pieceW = width; pieceH = height;
        sprite[0] = EOS;
        strcat(sprite, ROUNDED_SPRITE_BG, maxlength);
        return true;
    }

    switch (piece)
    {
        case 0: { pieceX = x + radius; pieceY = y;          pieceW = width - diameter; pieceH = height; }
        case 1: { pieceX = x;          pieceY = y + radius; pieceW = width;            pieceH = height - diameter; }
        case 2: { pieceX = x;                    pieceY = y;                     pieceW = diameter; pieceH = diameter; }
        case 3: { pieceX = x + width - diameter; pieceY = y;                     pieceW = diameter; pieceH = diameter; }
        case 4: { pieceX = x;                    pieceY = y + height - diameter; pieceW = diameter; pieceH = diameter; }
        case 5: { pieceX = x + width - diameter; pieceY = y + height - diameter; pieceW = diameter; pieceH = diameter; }
        default: return false;
    }

    if (pieceW <= 0.0 || pieceH <= 0.0)
        return false;

    // O circulo do LD_BEAT:chit nao ocupa a textura inteira (tem margem transparente).
    // Aumenta o sprite e puxa para fora para o circulo visivel encostar no canto.
    if (piece >= 2)
    {
        pieceW = diameter / (1.0 - ROUNDED_CHIT_MARGIN_LEFT - ROUNDED_CHIT_MARGIN_RIGHT);
        pieceH = diameter / (1.0 - ROUNDED_CHIT_MARGIN_TOP - ROUNDED_CHIT_MARGIN_BOTTOM);
        pieceX -= pieceW * ROUNDED_CHIT_MARGIN_LEFT;
        pieceY -= pieceH * ROUNDED_CHIT_MARGIN_TOP;
    }

    sprite[0] = EOS;
    if (piece <= 1)
        strcat(sprite, ROUNDED_SPRITE_BG, maxlength);
    else
        strcat(sprite, ROUNDED_SPRITE_CORNER, maxlength);
    return true;
}

stock SessionRounded_Create(index)
{
    new
        Float:x = e_SessionDraw[index][E_SESSIONDRAW_POSITION][0],
        Float:y = e_SessionDraw[index][E_SESSIONDRAW_POSITION][1],
        Float:width = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0],
        Float:height = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1],
        Float:radius = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0],
        color = e_SessionDraw[index][E_SESSIONDRAW_COLOR],
        Float:piece[4],
        sprite[32],
        idx
    ;

    SessionCircle_Destroy(index);

    for (new p = 0; p < ROUNDED_MAX_PIECES; p++)
    {
        if (!SessionRounded_GetPiece(p, x, y, width, height, radius, piece[0], piece[1], piece[2], piece[3], sprite))
            continue;

        CircleDraw[index][idx] = TextDrawCreate(piece[0], piece[1], sprite);
        TextDrawFont(CircleDraw[index][idx], TEXT_DRAW_FONT_SPRITE_DRAW);
        TextDrawTextSize(CircleDraw[index][idx], piece[2], piece[3]);
        TextDrawColour(CircleDraw[index][idx], color);
        TextDrawSetShadow(CircleDraw[index][idx], 0);
        TextDrawSetSelectable(CircleDraw[index][idx], false);
        idx++;
    }

    CircleDrawCount[index] = idx;
    e_SessionDraw[index][E_SESSIONDRAW_DRAW] = Text:INVALID_TEXT_DRAW;

    if (!e_SessionDraw[index][E_SESSIONDRAW_SHOW])
        return 1;

    foreach (new i: Users)
    {
        if (SpriteBrowser_Created(i)) continue;
        for (new c = 0; c < idx; c++) TextDrawShowForPlayer(i, CircleDraw[index][c]);
    }
    return 1;
}

stock SessionRounded_RestoreVisualColor(playerid, index)
{
    new color = e_SessionDraw[index][E_SESSIONDRAW_COLOR];
    for (new c = 0; c < CircleDrawCount[index]; c++)
    {
        TextDrawColour(CircleDraw[index][c], color);
        TextDrawShowForPlayer(playerid, CircleDraw[index][c]);
    }
    return 1;
}

stock SessionRounded_ShowConfig(playerid)
{
    new index = TaskBarTextDraw_GetSelected(playerid);
    if (!SessionRounded_IsRounded(index)) return 0;

    new
        Float:width = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0],
        Float:height = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1],
        Float:radius = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0]
    ;

    inline RoundedOpt()
    {
        DialogMod_Add(playerid, L(playerid, E_LANG_ROUNDED_WIDTH), 0, width);
        DialogMod_Add(playerid, L(playerid, E_LANG_ROUNDED_HEIGHT), 1, height);
        DialogMod_Add(playerid, L(playerid, E_LANG_ROUNDED_RADIUS), 2, radius, SessionRounded_ClampRadius(width, height, radius));
        DialogMod_Add(playerid, L(playerid, E_LANG_ROUNDED_RESIZE_KEYS), 3);
    }
    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_ROUNDED_TITLE), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CANCEL), "D_ROUNDED_CFG", using inline RoundedOpt);
    return 1;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8
                    888      888  888      .8"888.      888         888      888 888           Y88bo.
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'

*/

DialogMod:D_ROUNDED_CFG(playerid, response, inputtext[], params)
{
    if (!response) return 1;

    new index = TaskBarTextDraw_GetSelected(playerid);
    if (!SessionRounded_IsRounded(index)) return 1;

    new d[LANG_STRING_SIZE];
    switch (params)
    {
        case 0:
        {
            LangF(playerid, d, sizeof d, E_LANG_ROUNDED_WIDTH_BODY, e_SessionDraw[index][E_SESSIONDRAW_SIZE][0]);
            Dialog_Show(playerid, D_ROUNDED_WIDTH, DIALOG_STYLE_INPUT, L(playerid, E_LANG_ROUNDED_TITLE), d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        case 1:
        {
            LangF(playerid, d, sizeof d, E_LANG_ROUNDED_HEIGHT_BODY, e_SessionDraw[index][E_SESSIONDRAW_SIZE][1]);
            Dialog_Show(playerid, D_ROUNDED_HEIGHT, DIALOG_STYLE_INPUT, L(playerid, E_LANG_ROUNDED_TITLE), d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        case 2:
        {
            new Float:width = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
            new Float:height = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
            LangF(playerid, d, sizeof d, E_LANG_ROUNDED_RADIUS_BODY, e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0], SessionRounded_GetMaxRadius(width, height));
            Dialog_Show(playerid, D_ROUNDED_RADIUS, DIALOG_STYLE_INPUT, L(playerid, E_LANG_ROUNDED_TITLE), d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        case 3: TaskBarKey_Set(playerid, E_TYPEKEY_SIZE);
    }
    return 1;
}

Dialog:D_ROUNDED_WIDTH(playerid, response, listitem, inputtext[])
{
    if (response && !isnull(inputtext))
    {
        new Float:width;
        if (sscanf(inputtext, "f", width)) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));
        if (width < ROUNDED_MIN_SIZE) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));

        new index = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDrawData_SetSize(index, width, e_SessionDraw[index][E_SESSIONDRAW_SIZE][1]);
    }
    SessionRounded_ShowConfig(playerid);
    return 1;
}

Dialog:D_ROUNDED_HEIGHT(playerid, response, listitem, inputtext[])
{
    if (response && !isnull(inputtext))
    {
        new Float:height;
        if (sscanf(inputtext, "f", height)) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));
        if (height < ROUNDED_MIN_SIZE) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));

        new index = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDrawData_SetSize(index, e_SessionDraw[index][E_SESSIONDRAW_SIZE][0], height);
    }
    SessionRounded_ShowConfig(playerid);
    return 1;
}

Dialog:D_ROUNDED_RADIUS(playerid, response, listitem, inputtext[])
{
    if (response && !isnull(inputtext))
    {
        new Float:radius;
        if (sscanf(inputtext, "f", radius)) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));
        if (radius < 0.0) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));

        new index = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDrawData_SetLettSize(index, radius, e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1]);
    }
    SessionRounded_ShowConfig(playerid);
    return 1;
}
