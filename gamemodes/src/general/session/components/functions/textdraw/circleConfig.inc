#include <YSI_Coding\y_hooks>
hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type)
{
    if(type != E_TYPETASKBUTTON_MODELS) return Y_HOOKS_CONTINUE_RETURN_1;
    new index = TaskBarTextDraw_GetSelected(playerid);
    if(!SessionCircle_IsCircle(index)) return Y_HOOKS_CONTINUE_RETURN_1;
    SessionCircle_ShowConfig(playerid);
    return Y_HOOKS_BREAK_RETURN_1;
}
hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == INVALID_TEXT_DRAW) return Y_HOOKS_CONTINUE_RETURN_1;
    if(!Session_Has()) return Y_HOOKS_CONTINUE_RETURN_1;
    new index = SessionCircle_FindByDraw(clickedid);
    if(index == -1) return Y_HOOKS_CONTINUE_RETURN_1;
    TaskBarTextDraw_Select(playerid, index, false);
    SessionCircle_ShowConfig(playerid);
    return Y_HOOKS_BREAK_RETURN_1;
}
stock SessionCircle_ShowConfig(playerid)
{
    new index = TaskBarTextDraw_GetSelected(playerid);
    if(!SessionCircle_IsCircle(index)) return 0;
    new value = SessionCircle_GetValue(index);
    new maxv = SessionCircle_GetMax(index);
    new Float:size = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
    new Float:thick = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
    new Float:poly = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
    inline CircleOpt()
    {
        DialogMod_Add(playerid, L(playerid, E_LANG_CIRCLE_VALUE), 0, value);
        DialogMod_Add(playerid, L(playerid, E_LANG_CIRCLE_SIZE), 1, size);
        DialogMod_Add(playerid, L(playerid, E_LANG_CIRCLE_THICK), 2, thick);
        DialogMod_Add(playerid, L(playerid, E_LANG_CIRCLE_POLY), 3, poly);
        DialogMod_Add(playerid, L(playerid, E_LANG_CIRCLE_MAX), 4, maxv);

        new E_TYPEFONT:f = e_SessionDraw[index][E_SESSIONDRAW_FONT];
        if(f == E_TYPEFONT_TRIANGLE || f == E_TYPEFONT_PARENS) {
            new string[20 + 1];
            format(string, sizeof string, "Inverter: %s", e_SessionDraw[index][E_SESSIONDRAW_INVERT] ? "ON" : "OFF");
            DialogMod_Add(playerid, string, 5, e_SessionDraw[index][E_SESSIONDRAW_INVERT]);
        }
    }
    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, e_SessionDraw[index][E_SESSIONDRAW_TEXT], L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CANCEL), "D_CIRCLE_CFG", using inline CircleOpt);
    return 1;
}
DialogMod:D_CIRCLE_CFG(playerid, response, inputtext[], params)
{
    if(response)
    {
        new index = TaskBarTextDraw_GetSelected(playerid);
        if(!SessionCircle_IsCircle(index)) return 1;
        if(params == 0)
        {
            new d[160 + 1];
            LangF(playerid, d, sizeof d, E_LANG_CIRCLE_VALUE_BODY, SessionCircle_GetValue(index), SessionCircle_GetMax(index));
            Dialog_Show(playerid, D_CIRCLE_VALUE, DIALOG_STYLE_INPUT, e_SessionDraw[index][E_SESSIONDRAW_TEXT], d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        else if(params == 1)
        {
            new d[220 + 1];
            new Float:curSize = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
            new Float:curThick = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
            new Float:curPoly = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
            format(d, sizeof d, "{FFFFFF}Tamanho: %0.2f{FFFFFF}\nEspessura: %0.2f{FFFFFF}\nPoligonos: %0.1f{FFFFFF}", curSize, curThick, curPoly);
            Dialog_Show(playerid, D_CIRCLE_SIZE, DIALOG_STYLE_INPUT, e_SessionDraw[index][E_SESSIONDRAW_TEXT], d, L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_BACK));
        }
        else if(params == 2)
        {
            new d[160 + 1];
            LangF(playerid, d, sizeof d, E_LANG_CIRCLE_THICK_BODY, e_SessionDraw[index][E_SESSIONDRAW_SIZE][1]);
            Dialog_Show(playerid, D_CIRCLE_THICK, DIALOG_STYLE_INPUT, e_SessionDraw[index][E_SESSIONDRAW_TEXT], d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        else if(params == 3)
        {
            new d[220 + 1];
            LangF(playerid, d, sizeof d, E_LANG_CIRCLE_POLY_BODY, e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0]);
            strcat(d, "\n\n{BADC58}Atenção: quanto menor o valor, maior a qualidade, mas pode bater o limite de textdraws!");
            Dialog_Show(playerid, D_CIRCLE_POLY, DIALOG_STYLE_INPUT, e_SessionDraw[index][E_SESSIONDRAW_TEXT], d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        else if(params == 4)
        {
            new d[160 + 1];
            LangF(playerid, d, sizeof d, E_LANG_CIRCLE_MAX_BODY, SessionCircle_GetMax(index));
            Dialog_Show(playerid, D_CIRCLE_MAX, DIALOG_STYLE_INPUT, e_SessionDraw[index][E_SESSIONDRAW_TEXT], d, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_BACK));
        }
        else if(params == 5)
        {
            if(!SessionCircle_IsCircle(index)) return 1;
            e_SessionDraw[index][E_SESSIONDRAW_INVERT] = !e_SessionDraw[index][E_SESSIONDRAW_INVERT];
            SessionCircle_Refresh(index);
            SessionCircle_ShowConfig(playerid);
            return 1;
        }
    }
    return 1;
}
Dialog:D_CIRCLE_VALUE(playerid, response, listitem, inputtext[])
{
    if(response && !isnull(inputtext))
    {
        new value;
        if(sscanf(inputtext, "d", value) || value < 0) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));
        new index = TaskBarTextDraw_GetSelected(playerid);
        new maxv = SessionCircle_GetMax(index);
        if(value > maxv) value = maxv;
        e_SessionDraw[index][E_SESSIONDRAW_MODEL] = value;
    }
    SessionCircle_ShowConfig(playerid);
    return 1;
}
Dialog:D_CIRCLE_SIZE(playerid, response, listitem, inputtext[])
{
    if(response && !isnull(inputtext))
    {
        new Float:size;
        if(sscanf(inputtext, "f", size)) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));
        if(size < 2.0 || size > 50.0) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));
        new index = TaskBarTextDraw_GetSelected(playerid);
        new Float:thick = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
        SessionTextDrawData_SetSize(index, size, thick);
    }
    SessionCircle_ShowConfig(playerid);
    return 1;
}
Dialog:D_CIRCLE_THICK(playerid, response, listitem, inputtext[])
{
    if(response && !isnull(inputtext))
    {
        new Float:thick;
        if(sscanf(inputtext, "f", thick)) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));
        if(thick < 0.1 || thick > 3.0) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));
        new index = TaskBarTextDraw_GetSelected(playerid);
        new Float:size = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
        SessionTextDrawData_SetSize(index, size, thick);
    }
    SessionCircle_ShowConfig(playerid);
    return 1;
}
Dialog:D_CIRCLE_POLY(playerid, response, listitem, inputtext[])
{
    if(response && !isnull(inputtext))
    {
        new Float:poly;
        if(sscanf(inputtext, "f", poly)) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));
        if(poly < 3.0 || poly > 45.0) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));
        new index = TaskBarTextDraw_GetSelected(playerid);
        new Float:maxf = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1];
        SessionTextDrawData_SetLettSize(index, poly, maxf);
    }
    SessionCircle_ShowConfig(playerid);
    return 1;
}
Dialog:D_CIRCLE_MAX(playerid, response, listitem, inputtext[])
{
    if(response && !isnull(inputtext))
    {
        new maxv;
        if(sscanf(inputtext, "d", maxv) || maxv < 1) return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_INVALID_VALUE));
        if(maxv > 1000) maxv = 1000;
        new index = TaskBarTextDraw_GetSelected(playerid);
        new Float:poly = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
        SessionTextDrawData_SetLettSize(index, poly, float(maxv));
        new value = SessionCircle_GetValue(index);
        if(value > maxv)
        {
            e_SessionDraw[index][E_SESSIONDRAW_MODEL] = maxv;
        }
    }
    SessionCircle_ShowConfig(playerid);
    return 1;
}

