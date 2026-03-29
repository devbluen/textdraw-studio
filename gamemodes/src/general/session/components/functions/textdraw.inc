


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextdraw_Create(index) {

    // Creation
    new 
        string[1024 + 1],
        Float:position[2],
        Float:size[2]
    ;

    SessionTextdrawData_GetString(index, string);
    SessionTextdrawData_GetPosition(index, position[0], position[1]);
    e_SessionDraw[index][E_SESSIONDRAW_DRAW] = TextDrawCreate(position[0], position[1], string);

    // Set Informations
    SessionTextdrawData_GetSize(index, size[0], size[1]);
    SessionTextdrawData_SetSize     (index,      size[0], size[1],                        false);
    SessionTextdrawData_SetAlign    (index,      SessionTextdrawData_GetAlign(index),     false);
    SessionTextdrawData_SetColor    (index,      SessionTextdrawData_GetColor(index),     false);
    SessionTextdrawData_SetShadow   (index,      SessionTextdrawData_GetShadow(index),    false);
    SessionTextdrawData_SetOutline  (index,      SessionTextdrawData_GetOutline(index),   false);
    SessionTextdrawData_SetColorBG  (index,      SessionTextdrawData_GetColorBG(index),   false);
    SessionTextdrawData_SetFont     (index,      SessionTextdrawData_GetFont(index),      false);
    SessionTextdrawData_SetPropor   (index,      SessionTextdrawData_GetPropor(index),    false);
    SessionTextdrawData_SetSelect   (index,      SessionTextdrawData_GetSelect(index),    false);
    
    switch(SessionTextdrawData_GetType(index)) {
        case E_TYPEITEM_TEXT: {

            new Float:letterSize[2];

            SessionTextdrawData_GetLettSize(index, letterSize[0], letterSize[1]);
            SessionTextdrawData_SetLettSize (index,     letterSize[0], letterSize[1],               false);
            SessionTextdrawData_SetBox      (index,     SessionTextdrawData_GetBox(index),          false);
            SessionTextdrawData_SetColorBox (index,     SessionTextdrawData_GetColorBox(index),     false);
        }

        case E_TYPEITEM_MODEL: {

            new 
                Float:model_rotation[4], 
                model_colors[2]
            ;

            SessionTextdrawData_SetModel    (index,     SessionTextdrawData_GetModel(index),                                            false);

            SessionTextdrawData_GetModelRot(index, model_rotation[0], model_rotation[1], model_rotation[2], model_rotation[3]);
            SessionTextdrawData_SetModelRot (index,     model_rotation[0], model_rotation[1], model_rotation[2], model_rotation[3],     false);

            SessionTextdrawData_GetModelCol(index, model_colors[0], model_colors[1]);
            SessionTextdrawData_SetModelCol (index,     model_colors[0], model_colors[1],                                               false);
        }
    }
    
    SessionTextdrawData_Show(index);
}

stock SessionTextdraw_Destroy(index, bool:resetHeader = true) {

    TextDrawDestroy(e_SessionDraw[index][E_SESSIONDRAW_DRAW]);
    e_SessionDraw[index][E_SESSIONDRAW_DRAW] = INVALID_TEXT_DRAW;

    if(resetHeader) {

        static const e_Clear[E_SESSIONDRAW];
        e_SessionDraw[index] = e_Clear;

        foreach(new i: SessionDrawsPlayers[index])
            TaskBarTextdraw_UnSelect(i);

        Iter_Clear(SessionDrawsPlayers[index]);
        Iter_Remove(SessionDraws, index);
    }
}

stock SessionTextdraw_DestroyAll() {

    foreach(new i: SessionDraws)
        SessionTextdraw_Destroy(i);
}

stock SessionTextdraw_UpdateButton(index) {

    foreach(new i: SessionDrawsPlayers[index])
        TaskBarEventUpdate_Sprite(i, index);
}

stock SessionTextdraw_UpdateButtonAll() {

    foreach(new i: Users)
        TaskBarEventUpdate_Buttons(i);
}

stock SessionTextdraw_SetSelect(playerid, index)
    Iter_Add(SessionDrawsPlayers[index], playerid);

stock SessionTextdraw_RemoveSelect(playerid, index)
    Iter_Remove(SessionDrawsPlayers[index], playerid);