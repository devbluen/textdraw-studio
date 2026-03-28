


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextdraw_Load(playerid) {

    foreach(new i: SessionDraws)
        SessionTextdraw_Create(playerid, i);
}

stock SessionTextdraw_Unload(playerid) {

    foreach(new i: SessionDraws)
        SessionTextdraw_Destroy(playerid, i);  
}

stock SessionTextdraw_Create(playerid, index) {

    new
        E_TYPEITEM:type,
        string[1024 + 1],
        Float:position[2],
        Float:size[2],
        Float:letterSize[2],
        align,
        font,
        outline,
        shadow,
        color,
        colorBackground,
        colorBox,
        bool:proportional,
        bool:box,
        model,
        model_colors[2],
        Float:model_rotation[4]
    ;

    // Get Data
    SessionTextdrawData_GetString(index, string);
    SessionTextdrawData_GetPosition(index, position[0], position[1]);
    SessionTextdrawData_GetSize(index, size[0], size[1]);
    SessionTextdrawData_GetLettSize(index, letterSize[0], letterSize[1]);

    // Get Data Models
    model = SessionTextdrawData_GetModel(index);
    SessionTextdrawData_GetModelRot(index, model_rotation[0], model_rotation[1], model_rotation[2], model_rotation[3]);
    SessionTextdrawData_GetModelCol(index, model_colors[0], model_colors[1]);

    // Get Data Misc
    type = SessionTextdrawData_GetType(index);
    align = _:SessionTextdrawData_GetAlign(index);
    color = SessionTextdrawData_GetColor(index);
    shadow = SessionTextdrawData_GetShadow(index);
    outline = SessionTextdrawData_GetOutline(index);
    colorBackground = SessionTextdrawData_GetColorBG(index);
    colorBox = SessionTextdrawData_GetColorBox(index);
    font = _:SessionTextdrawData_GetFont(index);
    proportional = SessionTextdrawData_GetPropor(index);
    box = SessionTextdrawData_GetBox(index);

    // Creation
    new PlayerText:drawId = CreatePlayerTextDraw(playerid, position[0], position[1], string);
    PlayerTextDrawTextSize(playerid, drawId, size[0], size[1]);
    PlayerTextDrawAlignment(playerid, drawId, TEXT_DRAW_ALIGN:align);
    PlayerTextDrawColour(playerid, drawId, color);
    PlayerTextDrawSetShadow(playerid, drawId, shadow);
    PlayerTextDrawSetOutline(playerid, drawId, outline);
    PlayerTextDrawBackgroundColour(playerid, drawId, colorBackground);
    PlayerTextDrawFont(playerid, drawId, TEXT_DRAW_FONT:font);
    PlayerTextDrawSetProportional(playerid, drawId, proportional);

    switch(type) {
        case E_TYPEITEM_TEXT: {
            PlayerTextDrawLetterSize(playerid, drawId, letterSize[0], letterSize[1]);
            PlayerTextDrawUseBox(playerid, drawId, box);
            PlayerTextDrawBoxColour(playerid, drawId, colorBox);
        }

        case E_TYPEITEM_MODEL: {
            PlayerTextDrawSetPreviewModel(playerid, drawId, model);
            PlayerTextDrawSetPreviewRot(playerid, drawId, model_rotation[0], model_rotation[1], model_rotation[2], model_rotation[3]);
            PlayerTextDrawSetPreviewVehicleColours(playerid, drawId, model_colors[0], model_colors[1]); 
        }
    }

    // Set Player Informations
    e_SessionPlayer[playerid][E_SESSIONPLAYER_DRAW][index] = drawId;
}

stock SessionTextdraw_Destroy(playerid, index) {

    PlayerTextDrawDestroy(playerid, e_SessionPlayer[playerid][E_SESSIONPLAYER_DRAW][index]);
    e_SessionPlayer[playerid][E_SESSIONPLAYER_DRAW][index] = INVALID_PLAYER_TEXT_DRAW; 
}

stock SessionTextdraw_Update(playerid, index) {

    SessionTextdraw_Destroy(playerid, index);
    SessionTextdraw_Create(playerid, index);
}

stock SessionTextdraw_UpdateAll(index) {

    foreach(new i: Users)
        SessionTextdraw_Update(i, index);
}

stock SessionTextdraw_DestroyAll(index) {

    foreach(new i: Users)
        SessionTextdraw_Destroy(i, index);
}