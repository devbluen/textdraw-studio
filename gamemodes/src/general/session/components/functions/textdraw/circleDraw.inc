#define MAX_CIRCLE_POINTS (120)
new Text:CircleDraw[MAX_TEXTDRAWS_STUDIO][MAX_CIRCLE_POINTS];
new CircleDrawCount[MAX_TEXTDRAWS_STUDIO];
stock bool:SessionCircle_IsCircle(index)
{
    if(index < 0 || index >= MAX_TEXTDRAWS_STUDIO) return false;
    switch(e_SessionDraw[index][E_SESSIONDRAW_FONT]) {
        case E_TYPEFONT_CIRCLE, E_TYPEFONT_HEXAGON, E_TYPEFONT_DIAMOND, E_TYPEFONT_SQUARE, E_TYPEFONT_TRIANGLE, E_TYPEFONT_PARENS, E_TYPEFONT_ARC: return true;
    }
    return false;
}
stock SessionCircle_GetValue(index)
{
    return e_SessionDraw[index][E_SESSIONDRAW_MODEL];
}
stock SessionCircle_GetMax(index)
{
    new m = floatround(e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1]);
    if(m < 1) m = 100;
    return m;
}
stock Float:SessionCircle_GetPolygons(index)
{
    new Float:p = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
    if(p < 3.0) p = 15.0;
    return p;
}
stock SessionCircle_Pos(Float:angle, Float:distance, Float:sx, Float:sy, &Float:x, &Float:y)
{
    x = sx + (distance * floatsin(-angle, degrees));
    y = sy + (distance * floatcos(angle, degrees));
    return 1;
}
stock SessionCircle_Destroy(index)
{
    for(new i = 0; i < CircleDrawCount[index]; i++)
    {
        TextDrawDestroy(CircleDraw[index][i]);
        CircleDraw[index][i] = Text:INVALID_TEXT_DRAW;
    }
    CircleDrawCount[index] = 0;
    return 1;
}
stock SessionCircle_Create(index)
{
    new Float:px = e_SessionDraw[index][E_SESSIONDRAW_POSITION][0];
    new Float:py = e_SessionDraw[index][E_SESSIONDRAW_POSITION][1];
    new Float:size = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
    new Float:thick = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
    new Float:poly = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
    new Float:maxf = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1];
    new value = e_SessionDraw[index][E_SESSIONDRAW_MODEL];
    new color = e_SessionDraw[index][E_SESSIONDRAW_COLOR];
    new bg = e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND];
    if(size < 2.0) size = 2.0;
    if(size > 50.0) size = 50.0;
    if(thick < 0.1) thick = 0.1;
    if(thick > 3.0) thick = 3.0;
    if(poly < 3.0) poly = 3.0;
    if(poly > 45.0) poly = 45.0;
    new maxv = floatround(maxf);
    if(maxv < 1) maxv = 100;
    if(value < 0) value = 0;
    if(value > maxv) value = maxv;
    SessionCircle_Destroy(index);
    new total = 0;
    switch(e_SessionDraw[index][E_SESSIONDRAW_FONT]) {
        case E_TYPEFONT_CIRCLE: {
            for(new Float:v = 0.0; v < 360.0; v += poly) total++;
            // distribute points around the circle
        }
        case E_TYPEFONT_HEXAGON: {
            new Float:ppe = 60.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 6; e++)
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) total++;
            if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
        }
        case E_TYPEFONT_DIAMOND: {
            new Float:ppe = 90.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 4; e++)
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) total++;
            if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
        }
        case E_TYPEFONT_SQUARE: {
            new Float:ppe = 90.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 4; e++)
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) total++;
            if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
        }
        case E_TYPEFONT_TRIANGLE: {
            new Float:ppe = 120.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            total = floatround(ppe * 3.0);
            if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
        }
        case E_TYPEFONT_PARENS: {
            total = floatround(180.0 / poly) + 1;
            if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
        }
        case E_TYPEFONT_ARC: {
            total = floatround(180.0 / poly) + 1;
            if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
        }
    }
    if(total > MAX_CIRCLE_POINTS) total = MAX_CIRCLE_POINTS;
    if(total <= 0) total = 1;
    new percent = (total * value) / maxv;
    new Float:x;
    new Float:y;
    new idx = 0;
    switch(e_SessionDraw[index][E_SESSIONDRAW_FONT]) {
        case E_TYPEFONT_CIRCLE: {
            for(new Float:v = 0.0; v < 360.0; v += poly)
            {
                if(idx >= MAX_CIRCLE_POINTS) break;
                SessionCircle_Pos(v + 180.0, size, px, py, x, y);
                CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                TextDrawSetShadow(CircleDraw[index][idx], 0);
                TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                TextDrawSetSelectable(CircleDraw[index][idx], false);
                idx++;
            }
        }
        case E_TYPEFONT_HEXAGON: {
            new Float:coords[6][2];
            for(new Float:i = 0.0; i < 360.0; i += 60.0) {
                SessionCircle_Pos(i + 180.0, size, px, py, coords[floatround(i / 60.0)][0], coords[floatround(i / 60.0)][1]);
            }
            new Float:ppe = 60.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 6; e++) {
                new Float:sx = coords[e][0];
                new Float:sy = coords[e][1];
                new Float:ex = coords[(e+1)%6][0];
                new Float:ey = coords[(e+1)%6][1];
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) {
                    if(idx >= MAX_CIRCLE_POINTS) break;
                    x = sx + (ex - sx) * t;
                    y = sy + (ey - sy) * t;
                    CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                    TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                    TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                    TextDrawSetShadow(CircleDraw[index][idx], 0);
                    TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                    TextDrawSetSelectable(CircleDraw[index][idx], false);
                    idx++;
                }
            }
        }
        case E_TYPEFONT_DIAMOND: {
            new Float:coords[4][2];
            for(new Float:i = 0.0; i < 360.0; i += 90.0) {
                SessionCircle_Pos(i + 180.0, size, px, py, coords[floatround(i / 90.0)][0], coords[floatround(i / 90.0)][1]);
            }
            new Float:ppe = 90.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 4; e++) {
                new Float:sx = coords[e][0];
                new Float:sy = coords[e][1];
                new Float:ex = coords[(e+1)%4][0];
                new Float:ey = coords[(e+1)%4][1];
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) {
                    if(idx >= MAX_CIRCLE_POINTS) break;
                    x = sx + (ex - sx) * t;
                    y = sy + (ey - sy) * t;
                    CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                    TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                    TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                    TextDrawSetShadow(CircleDraw[index][idx], 0);
                    TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                    TextDrawSetSelectable(CircleDraw[index][idx], false);
                    idx++;
                }
            }
        }
        case E_TYPEFONT_TRIANGLE: {
            new Float:coords[3][2];
            if(e_SessionDraw[index][E_SESSIONDRAW_INVERT]) {
                coords[0][0] = px; coords[0][1] = py + size;
                coords[1][0] = px + size; coords[1][1] = py - size;
                coords[2][0] = px - size; coords[2][1] = py - size;
            } else {
                coords[0][0] = px; coords[0][1] = py - size;
                coords[1][0] = px + size; coords[1][1] = py + size;
                coords[2][0] = px - size; coords[2][1] = py + size;
            }
            new Float:ppe = 120.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 3; e++) {
                new Float:sx = coords[e][0];
                new Float:sy = coords[e][1];
                new Float:ex = coords[(e+1)%3][0];
                new Float:ey = coords[(e+1)%3][1];
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) {
                    if(idx >= MAX_CIRCLE_POINTS) break;
                    x = sx + (ex - sx) * t;
                    y = sy + (ey - sy) * t;
                    CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                    TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                    TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                    TextDrawSetShadow(CircleDraw[index][idx], 0);
                    TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                    TextDrawSetSelectable(CircleDraw[index][idx], false);
                    idx++;
                }
            }
        }
        case E_TYPEFONT_PARENS: {
            new Float:start, Float:finish;
            if(e_SessionDraw[index][E_SESSIONDRAW_INVERT]) {
                start = 180.0;
                finish = 360.0;
            } else {
                start = 0.0;
                finish = 180.0;
            }
            for(new Float:v = start; v <= finish; v += poly)
            {
                if(idx >= MAX_CIRCLE_POINTS) break;
                SessionCircle_Pos(v + 180.0, size, px, py, x, y);
                CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                TextDrawSetShadow(CircleDraw[index][idx], 0);
                TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                TextDrawSetSelectable(CircleDraw[index][idx], false);
                idx++;
            }
        }
        case E_TYPEFONT_ARC: {
            for(new Float:v = 270.0; v <= 450.0; v += poly)
            {
                if(idx >= MAX_CIRCLE_POINTS) break;
                SessionCircle_Pos(v + 180.0, size, px, py, x, y);
                CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                TextDrawSetShadow(CircleDraw[index][idx], 0);
                TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                TextDrawSetSelectable(CircleDraw[index][idx], false);
                idx++;
            }
        }
        case E_TYPEFONT_SQUARE: {
            new Float:sx = px - size;
            new Float:sy = py - size;
            new Float:ex = px + size;
            new Float:ey = py + size;
            new Float:coords[4][2];
            coords[0][0] = sx; coords[0][1] = sy;
            coords[1][0] = ex; coords[1][1] = sy;
            coords[2][0] = ex; coords[2][1] = ey;
            coords[3][0] = sx; coords[3][1] = ey;
            new Float:ppe = 90.0 / poly;
            if(ppe < 1.0) ppe = 1.0;
            for(new e = 0; e < 4; e++) {
                new Float:sx2 = coords[e][0];
                new Float:sy2 = coords[e][1];
                new Float:ex2 = coords[(e+1)%4][0];
                new Float:ey2 = coords[(e+1)%4][1];
                for(new Float:t = 0.0; t < 1.0; t += 1.0 / ppe) {
                    if(idx >= MAX_CIRCLE_POINTS) break;
                    x = sx2 + (ex2 - sx2) * t;
                    y = sy2 + (ey2 - sy2) * t;
                    CircleDraw[index][idx] = TextDrawCreate(x, y, ".");
                    TextDrawAlignment(CircleDraw[index][idx], TEXT_DRAW_ALIGN_CENTER);
                    TextDrawLetterSize(CircleDraw[index][idx], thick, thick * 3.0);
                    TextDrawSetShadow(CircleDraw[index][idx], 0);
                    TextDrawColour(CircleDraw[index][idx], percent <= idx ? bg : color);
                    TextDrawSetSelectable(CircleDraw[index][idx], false);
                    idx++;
                }
            }
        }

    }
    CircleDrawCount[index] = idx;
    e_SessionDraw[index][E_SESSIONDRAW_DRAW] = Text:INVALID_TEXT_DRAW;
    foreach(new i: Users)
    {
        if(SpriteBrowser_Created(i)) continue;
        for(new c = 0; c < idx; c++) TextDrawShowForPlayer(i, CircleDraw[index][c]);
    }
    return 1;
}
stock SessionCircle_Refresh(index)
{
    return SessionCircle_Create(index);
}
stock SessionCircle_Show(index)
{
    e_SessionDraw[index][E_SESSIONDRAW_SHOW] = true;
    foreach(new i: Users)
    {
        if(SpriteBrowser_Created(i)) continue;
        for(new c = 0; c < CircleDrawCount[index]; c++) TextDrawShowForPlayer(i, CircleDraw[index][c]);
    }
    return 1;
}
stock SessionCircle_ShowForPlayer(playerid, index)
{
    for(new c = 0; c < CircleDrawCount[index]; c++) TextDrawShowForPlayer(playerid, CircleDraw[index][c]);
    return 1;
}
stock SessionCircle_HideForPlayer(playerid, index)
{
    for(new c = 0; c < CircleDrawCount[index]; c++) TextDrawHideForPlayer(playerid, CircleDraw[index][c]);
    return 1;
}
stock SessionCircle_FindByDraw(Text:draw)
{
    foreach(new i: SessionDraws)
    {
        if(e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_CIRCLE && e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_HEXAGON && e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_DIAMOND && e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_SQUARE && e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_TRIANGLE && e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_PARENS && e_SessionDraw[i][E_SESSIONDRAW_FONT] != E_TYPEFONT_ARC) continue;
        for(new c = 0; c < CircleDrawCount[i]; c++)
        {
            if(CircleDraw[i][c] == draw) return i;
        }
    }
    return -1;
}
stock SessionCircle_SetVisualColor(playerid, index)
{
    for(new c = 0; c < CircleDrawCount[index]; c++)
    {
        TextDrawColour(CircleDraw[index][c], TEXTDRAW_FEEDBACK);
        TextDrawShowForPlayer(playerid, CircleDraw[index][c]);
    }
    return 1;
}
stock SessionCircle_RestoreVisualColor(playerid, index)
{
    new value = e_SessionDraw[index][E_SESSIONDRAW_MODEL];
    new maxv = SessionCircle_GetMax(index);
    new color = e_SessionDraw[index][E_SESSIONDRAW_COLOR];
    new bg = e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND];
    if(value < 0) value = 0;
    if(value > maxv) value = maxv;
    new percent = (CircleDrawCount[index] * value) / maxv;
    for(new c = 0; c < CircleDrawCount[index]; c++)
    {
        TextDrawColour(CircleDraw[index][c], percent <= c ? bg : color);
        TextDrawShowForPlayer(playerid, CircleDraw[index][c]);
    }
    return 1;
}
