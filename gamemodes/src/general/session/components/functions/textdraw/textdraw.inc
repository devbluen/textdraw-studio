


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextDraw_Create(index) {

    // Creation
    new 
        string[1024 + 1],
        Float:position[2],
        Float:size[2]
    ;

    SessionTextDrawData_GetString(index, string);
    Util_ConverterTextdrawText(string);
    
    SessionTextDrawData_GetPosition(index, position[0], position[1]);
    e_SessionDraw[index][E_SESSIONDRAW_DRAW] = TextDrawCreate(position[0], position[1], string);

    // Set Informations
    SessionTextDrawData_GetSize(index, size[0], size[1]);
    SessionTextDrawData_SetSize(index, size[0], size[1], false);
    SessionTextDrawData_SetAlign(index, SessionTextDrawData_GetAlign(index), false);
    SessionTextDrawData_SetColor(index, SessionTextDrawData_GetColor(index), false);
    SessionTextDrawData_SetShadow(index, SessionTextDrawData_GetShadow(index), false);
    SessionTextDrawData_SetOutline(index, SessionTextDrawData_GetOutline(index), false);
    SessionTextDrawData_SetColorBG(index, SessionTextDrawData_GetColorBG(index), false);
    SessionTextDrawData_SetFont(index, SessionTextDrawData_GetFont(index), false);
    SessionTextDrawData_SetPropor(index, SessionTextDrawData_GetPropor(index), false);
    SessionTextDrawData_SetSelect(index, SessionTextDrawData_GetSelect(index), false);
    
    switch(SessionTextDrawData_GetFont(index)) {
        case E_TYPEFONT_SPRITE: {}
        case E_TYPEFONT_MODEL: 
        {
            new 
                Float:model_rotation[4], 
                model_colors[2]
            ;

            SessionTextDrawData_SetModel(index, SessionTextDrawData_GetModel(index), false);

            SessionTextDrawData_GetModelRot(index, model_rotation[0], model_rotation[1], model_rotation[2], model_rotation[3]);
            SessionTextDrawData_SetModelRot(index, model_rotation[0], model_rotation[1], model_rotation[2], model_rotation[3], false);

            SessionTextDrawData_GetModelCol(index, model_colors[0], model_colors[1]);
            SessionTextDrawData_SetModelCol(index, model_colors[0], model_colors[1], false);
        }
        default: 
        {
            new Float:letterSize[2];
            SessionTextDrawData_GetLettSize(index, letterSize[0], letterSize[1]);
            SessionTextDrawData_SetLettSize(index, letterSize[0], letterSize[1], false);
            SessionTextDrawData_SetBox(index, SessionTextDrawData_GetBox(index), false);
            SessionTextDrawData_SetColorBox(index, SessionTextDrawData_GetColorBox(index), false);
        }
    }
    
    SessionTextDrawData_Show(index);
}

stock SessionTextDraw_Destroy(index, bool:resetHeader = true) {

    TextDrawDestroy(e_SessionDraw[index][E_SESSIONDRAW_DRAW]);
    e_SessionDraw[index][E_SESSIONDRAW_DRAW] = INVALID_TEXT_DRAW;

    if(resetHeader) {

        foreach(new i: SessionDrawsPlayers[index])
            TaskBarTextDraw_UnSelect(i);

        foreach(new i: Users)
            SessionPlayer_RemoveDraw(i, index);

        SessionGroup_RemoveAllByDrawIndex(index, false);

        Iter_Clear(SessionDrawsPlayers[index]);
        Iter_Remove(SessionDraws, index);

        static const e_Clear[E_SESSIONDRAW];
        e_SessionDraw[index] = e_Clear;
    }
}

stock SessionTextDraw_DestroyAll() { 

    foreach(new i: SessionDraws)
        SessionTextDraw_Destroy(i);
    
    foreach(new i: Users)
        TaskBarEventUpdate_Buttons(i);
}

stock SessionTextDraw_UpdateButton(index) {

    foreach(new i: SessionDrawsPlayers[index])
        TaskBarEventUpdate_Sprite(i, index);
}

stock SessionTextDraw_UpdateButtonAll() {

    foreach(new i: Users)
        TaskBarEventUpdate_Buttons(i);
}

stock SessionTextDraw_ShowAllForPlayer(playerid) {

    foreach(new i: SessionDraws)
        TextDrawShowForPlayer(playerid, SessionTextDrawData_GetDraw(i));
}

stock SessionTextDraw_HideAllForPlayer(playerid) {

    foreach(new i: SessionDraws)
        TextDrawHideForPlayer(playerid, SessionTextDrawData_GetDraw(i));
}

stock bool:SessionTextDraw_IsEmpty()
    return Iter_IsEmpty(SessionDraws);

stock SessionTextDraw_SetSelect(playerid, index)
    Iter_Add(SessionDrawsPlayers[index], playerid);

stock SessionTextDraw_RemoveSelect(playerid, index)
    Iter_Remove(SessionDrawsPlayers[index], playerid);

stock SessionTextDraw_GetPrevious(byIndex)
    return Iter_Prev(SessionDraws, byIndex);

stock SessionTextDraw_GetNext(byIndex)
    return Iter_Next(SessionDraws, byIndex);

stock SessionTextDraw_GetCount()
    return Iter_Count(SessionDraws);

stock SessionTextDraw_GetLast()
    return Iter_Last(SessionDraws);

stock SessionTextDraw_GetMax()
    return MAX_TEXTDRAWS_STUDIO;