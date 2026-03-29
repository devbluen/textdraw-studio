


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextdrawData_LoadAll() {

    new uniqueId = Session_GetId();
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT indexDraw, id FROM textdraws WHERE project_id = %i ORDER BY `indexDraw` ASC", uniqueId);

    if(cache && DB_GetRowCount(cache)) {
        new index, drawId;
        do
        {
            index = DB_GetFieldIntByName(cache, "indexDraw");
            drawId = DB_GetFieldIntByName(cache, "id");

            SessionTextdrawData_Load(index, drawId);
        }
        while(DB_SelectNextRow(cache));
    }
}

stock SessionTextdrawData_Load(index, id) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            position, \
                                                            size, \
                                                            letter_size, \
                                                            `text`, \
                                                            font, \
                                                            align, \
                                                            proportion, \
                                                            outline, \
                                                            shadow, \
                                                            color, \
                                                            colorBackground, \
                                                            colorBox, \
                                                            selectable, \
                                                            mode, \
                                                            itemType \
                                                        FROM textdraws  \
                                                        WHERE id = %i",

                                                        id
                                                    );

    if(cache) {

        new buffGeneral[64 + 1];

        // Ints
        e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID] = id;
        e_SessionDraw[index][E_SESSIONDRAW_FONT] = _:DB_GetFieldIntByName(cache, "font");
        e_SessionDraw[index][E_SESSIONDRAW_ALIGN] = _:DB_GetFieldIntByName(cache, "align");
        e_SessionDraw[index][E_SESSIONDRAW_PROPORTION] = DB_GetFieldIntByName(cache, "proportion");
        e_SessionDraw[index][E_SESSIONDRAW_OUTLINE] = DB_GetFieldIntByName(cache, "outline");
        e_SessionDraw[index][E_SESSIONDRAW_SHADOW] = DB_GetFieldIntByName(cache, "shadow");
        e_SessionDraw[index][E_SESSIONDRAW_COLOR] = DB_GetFieldIntByName(cache, "color");
        e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND] = DB_GetFieldIntByName(cache, "colorBackground");
        e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX] = DB_GetFieldIntByName(cache, "colorBox");
        e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE] = DB_GetFieldIntByName(cache, "selectable");
        e_SessionDraw[index][E_SESSIONDRAW_MODE] = _:DB_GetFieldIntByName(cache, "mode");
        e_SessionDraw[index][E_SESSIONDRAW_TYPE] = _:DB_GetFieldIntByName(cache, "itemType");
        e_SessionDraw[index][E_SESSIONDRAW_MODEL] = _:DB_GetFieldIntByName(cache, "model");
        e_SessionDraw[index][E_SESSIONDRAW_BOX] = _:DB_GetFieldIntByName(cache, "box");

        // Strings
        DB_GetFieldStringByName(cache, "text", e_SessionDraw[index][E_SESSIONDRAW_TEXT]);

        // Floats
        DB_GetFieldStringByName(cache, "position", buffGeneral);
        sscanf(buffGeneral, "p<,>a<f>[2]", e_SessionDraw[index][E_SESSIONDRAW_POSITION]);

        DB_GetFieldStringByName(cache, "size", buffGeneral);
        sscanf(buffGeneral, "p<,>a<f>[2]", e_SessionDraw[index][E_SESSIONDRAW_SIZE]);

        DB_GetFieldStringByName(cache, "letter_size", buffGeneral);
        sscanf(buffGeneral, "p<,>a<f>[2]", e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE]);

        DB_GetFieldStringByName(cache, "model_rotation", buffGeneral);
        sscanf(buffGeneral, "p<,>a<f>[4]", e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION]);

        DB_GetFieldStringByName(cache, "model_colors", buffGeneral);
        sscanf(buffGeneral, "p<,>a<i>[2]", e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS]);

        // Sets
        Iter_Add(SessionDraws, index);
        SessionTextdraw_Create(index);

        // 
        DB_FreeResultSet(cache);
    }
}

stock SessionTextdrawData_Destroy(index) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "DELETE FROM textdraws WHERE id = %i", SessionTextdrawData_GetUniqueId(index));

    if(cache)
        DB_FreeResultSet(cache);
    
    SessionTextdraw_Destroy(index);
}

stock SessionTextdrawData_Create(E_TYPEITEM:type) {

    new index = Iter_Free(SessionDraws);
    if(index == ITER_NONE)
        return -1;

    new project_id = Session_GetId();

    switch(type) {
        case E_TYPEITEM_TEXT: {

            SessionTextdrawData_Insert(
                .project_id = project_id, 
                .index = index, 
                .itemType = type, 
                .text = "DEFAULT", 
                .position = Float:{270.0, 170.0}, 
                .size = Float:{640.0, 0.0},
                .letterSize = Float:{0.3, 1.5}, 
                .font = E_TYPEFONT_1, 
                .align = E_TYPEALIGNMENT_LEFT, 
                .proportion = true, 
                .outline = 0, 
                .shadow = 0, 
                .color = 0xFFFFFFFF, 
                .colorBackground = 0, 
                .colorBox = 0, 
                .selectable = false, 
                .mode = E_TYPEMODE_GLOBAL, 
                .box = false, 
                .model = 0, 
                .modelRotation = Float:{0.0, 0.0, 0.0, 1.0}, 
                .modelColors = {0, 0}
            );
        }
        
        case E_TYPEITEM_SPRITE:
        {
            SessionTextdrawData_Insert(
                .project_id = project_id, 
                .index = index, 
                .itemType = type, 
                .text = "LD_SPAC:white", 
                .position = Float:{250.0, 150.0}, 
                .size = Float:{90.0, 90.0},
                .letterSize = Float:{0.0, 0.0}, 
                .font = E_TYPEFONT_SPRITE, 
                .align = E_TYPEALIGNMENT_LEFT, 
                .proportion = true, 
                .outline = 0, 
                .shadow = 0, 
                .color = 0xFFFFFFFF, 
                .colorBackground = 0, 
                .colorBox = 0, 
                .selectable = false, 
                .mode = E_TYPEMODE_GLOBAL, 
                .box = false, 
                .model = 0, 
                .modelRotation = Float:{0.0, 0.0, 0.0, 1.0}, 
                .modelColors = {0, 0}
            );
        }
        
        case E_TYPEITEM_MODEL:
        {
            SessionTextdrawData_Insert(
                .project_id = project_id, 
                .index = index, 
                .itemType = type, 
                .text = "_", 
                .position = Float:{250.0, 150.0}, 
                .size = Float:{90.0, 90.0},
                .letterSize = Float:{0.0, 0.0}, 
                .font = E_TYPEFONT_MODEL, 
                .align = E_TYPEALIGNMENT_LEFT, 
                .proportion = true, 
                .outline = 0, 
                .shadow = 0, 
                .color = 0xFFFFFFFF, 
                .colorBackground = 0, 
                .colorBox = 0, 
                .selectable = false, 
                .mode = E_TYPEMODE_GLOBAL, 
                .box = false, 
                .model = 0, 
                .modelRotation = Float:{0.0, 0.0, 0.0, 1.0}, 
                .modelColors = {0, 0}
            );
        }
    }
    return index;
}

stock SessionTextdrawData_Insert(project_id, index, E_TYPEITEM:itemType, const text[], const Float:position[2], const Float:size[2], const Float:letterSize[2], E_TYPEFONT:font, E_TYPEALIGNMENT:align, bool:proportion, outline, shadow, color, colorBackground, colorBox, bool:selectable, E_TYPEMODE:mode, bool:box, model, const Float:modelRotation[4], const modelColors[2]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "INSERT INTO textdraws (project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, itemType, model, model_colors, model_rotation, box) VALUES (%i, '%f, %f', '%f, %f', '%f, %f', '%s', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i,%i', '%f,%f,%f,%f', '%i')", 
        project_id,
        position[0], position[1],
        size[0], size[1],
        letterSize[0], letterSize[1],
        text,
        _:font,
        _:align,
        proportion,
        outline,
        shadow,
        color,
        colorBackground,
        colorBox,
        selectable,
        _:mode,
        index,
        _:itemType,
        model,
        modelColors[0], modelColors[1],
        modelRotation[0], modelRotation[1], modelRotation[2], modelRotation[3],
        box
    );

    if(cache) 
        DB_FreeResultSet(cache);

    cache = DB_ExecuteQuery(IDConnection, "SELECT  \
                                            id \
                                        FROM textdraws \
                                        WHERE project_id = %i \
                                        ORDER BY id DESC \
                                        LIMIT 1",
                                        
                                        project_id
                                    );

    if(cache) {
        new lastInsert = DB_GetFieldIntByName(cache, "id");
        if(lastInsert)
            SessionTextdrawData_Load(index, lastInsert);

        DB_FreeResultSet(cache);
    }
}

stock SessionTextdrawData_GetUniqueId(index)
    return e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID];

stock SessionTextdrawData_GetString(index, dest[], maxlength = sizeof dest) {
    strcat(dest, e_SessionDraw[index][E_SESSIONDRAW_TEXT], maxlength);
}

stock SessionTextdrawData_GetPosition(index, &Float:x, &Float:y) {
    x = e_SessionDraw[index][E_SESSIONDRAW_POSITION][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_POSITION][1];
}

stock SessionTextdrawData_GetSize(index, &Float:x, &Float:y) {
    x = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
}

stock SessionTextdrawData_GetLettSize(index, &Float:x, &Float:y) {
    x = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1];
}

stock SessionTextdrawData_GetModelRot(index, &Float:x, &Float:y, &Float:z, &Float:zoom) {
    x = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][1];
    z = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][2];
    zoom = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][3];
}

stock SessionTextdrawData_GetModelCol(index, &Float:color1, &Float:color2) {
    color1 = e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][0];
    color2 = e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][1];
}

stock E_TYPEALIGNMENT:SessionTextdrawData_GetAlign(index)
    return e_SessionDraw[index][E_SESSIONDRAW_ALIGN];

stock E_TYPEITEM:SessionTextdrawData_GetType(index)
    return e_SessionDraw[index][E_SESSIONDRAW_TYPE];

stock SessionTextdrawData_GetColor(index)
    return e_SessionDraw[index][E_SESSIONDRAW_COLOR];

stock SessionTextdrawData_GetShadow(index)
    return e_SessionDraw[index][E_SESSIONDRAW_SHADOW];

stock SessionTextdrawData_GetOutline(index)
    return e_SessionDraw[index][E_SESSIONDRAW_OUTLINE];

stock SessionTextdrawData_GetColorBG(index)
    return e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND];

stock SessionTextdrawData_GetColorBox(index)
    return e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX];

stock E_TYPEFONT:SessionTextdrawData_GetFont(index)
    return e_SessionDraw[index][E_SESSIONDRAW_FONT];

stock bool:SessionTextdrawData_GetPropor(index)
    return e_SessionDraw[index][E_SESSIONDRAW_PROPORTION];

stock bool:SessionTextdrawData_GetBox(index)
    return e_SessionDraw[index][E_SESSIONDRAW_BOX];

stock SessionTextdrawData_GetModel(index)
    return e_SessionDraw[index][E_SESSIONDRAW_MODEL];

stock E_TYPEMODE:SessionTextdrawData_GetMode(index)
    return e_SessionDraw[index][E_SESSIONDRAW_MODE];

stock Text:SessionTextdrawData_GetDraw(index)
    return e_SessionDraw[index][E_SESSIONDRAW_DRAW];

stock bool:SessionTextdrawData_GetSelect(index)
    return e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE];

//

stock SessionTextdrawData_SetUniqueId(index, uniqueId)
    e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID] = uniqueId;

stock SessionTextdrawData_SetModelCol(index, &Float:color1, &Float:color2, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][0] = color1;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][1] = color2;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET model_colors = '%i,%i' WHERE id = %i", color1, color2, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPreviewVehicleColours(SessionTextdrawData_GetDraw(index), color1, color2);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetAlign(index, E_TYPEALIGNMENT:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_ALIGN] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET align = %i WHERE id = %i", _:type, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawAlignment(SessionTextdrawData_GetDraw(index), _:type);
    SessionTextDrawData_Update(index);

    SessionTextdraw_UpdateButton(index);
}

stock SessionTextdrawData_SetType(index, E_TYPEITEM:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_TYPE] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET itemType = %i WHERE id = %i", _:type, SessionTextdrawData_GetUniqueId(index))
        );
    }
}

stock SessionTextdrawData_SetColor(index, color, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_COLOR] = color;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET color = %i WHERE id = %i", color, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawColour(SessionTextdrawData_GetDraw(index), color);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetShadow(index, value, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_SHADOW] = value;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET shadow = %i WHERE id = %i", value, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetShadow(SessionTextdrawData_GetDraw(index), value);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetOutline(index, value, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_OUTLINE] = value;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET outline = %i WHERE id = %i", value, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetOutline(SessionTextdrawData_GetDraw(index), value);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetColorBG(index, color, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND] = color;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET colorBackground = %i WHERE id = %i", color, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawBackgroundColour(SessionTextdrawData_GetDraw(index), color);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetColorBox(index, color, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX] = color;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET colorBox = %i WHERE id = %i", color, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawBoxColour(SessionTextdrawData_GetDraw(index), color);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetFont(index, E_TYPEFONT:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_FONT] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET font = %i WHERE id = %i", _:type, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawFont(SessionTextdrawData_GetDraw(index), _:type);
    SessionTextDrawData_Update(index);

    SessionTextdraw_UpdateButton(index);
}

stock SessionTextdrawData_SetPropor(index, bool:status, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_PROPORTION] = status;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET proportion = %i WHERE id = %i", status, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetProportional(SessionTextdrawData_GetDraw(index), status);
    SessionTextDrawData_Update(index);

    SessionTextdraw_UpdateButton(index);
}

stock SessionTextdrawData_SetBox(index, bool:status, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_BOX] = status;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET box = %i WHERE id = %i", status, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawUseBox(SessionTextdrawData_GetDraw(index), status);
    SessionTextDrawData_Update(index);

    SessionTextdraw_UpdateButton(index);
}

stock SessionTextdrawData_SetModel(index, model, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODEL] = model;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET model = %i WHERE id = %i", model, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPreviewModel(SessionTextdrawData_GetDraw(index), model);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetModelRot(index, &Float:x, &Float:y, &Float:z, &Float:zoom, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][1] = y;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][2] = z;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][3] = zoom;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET model_rotation = '%f,%f,%f,%f' WHERE id = %i", x, y, z, zoom, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPreviewRot(SessionTextdrawData_GetDraw(index), x, y, z, zoom);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetLettSize(index, &Float:x, &Float:y, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1] = y;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET letter_size = '%f,%f' WHERE id = %i", x, y, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawLetterSize(SessionTextdrawData_GetDraw(index), x, y);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetSize(index, &Float:x, &Float:y, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_SIZE][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_SIZE][1] = y;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET size = '%f,%f' WHERE id = %i", x, y, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawTextSize(SessionTextdrawData_GetDraw(index), x, y);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetPosition(index, &Float:x, &Float:y, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_POSITION][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_POSITION][1] = y;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET position = '%f,%f' WHERE id = %i", x, y, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPos(SessionTextdrawData_GetDraw(index), x, y);
    SessionTextDrawData_Update(index);
}

stock SessionTextdrawData_SetString(index, const string[], bool:execute_query = true) {

    strcopy(e_SessionDraw[index][E_SESSIONDRAW_TEXT], string);

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET text = '%s' WHERE id = %i", string, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetString(SessionTextdrawData_GetDraw(index), string);
}

stock SessionTextdrawData_SetMode(index, E_TYPEMODE:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODE] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET mode = %i WHERE id = %i", _:type, SessionTextdrawData_GetUniqueId(index))
        );
    }

    SessionTextdraw_UpdateButton(index);
}

stock SessionTextdrawData_SetSelect(index, bool:status, bool:execute_query) {

    e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE] = status;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET selectable = %i WHERE id = %i", status, SessionTextdrawData_GetUniqueId(index))
        );
    }

    TextDrawSetSelectable(SessionTextdrawData_GetDraw(index), status);
    SessionTextDrawData_Update(index);

    SessionTextdraw_UpdateButton(index);
}

stock SessionTextdrawData_Show(index) {
    e_SessionDraw[index][E_SESSIONDRAW_SHOW] = true;
    TextDrawShowForAll(SessionTextdrawData_GetDraw(index));
}

static stock SessionTextDrawData_Update(index) {
    if(!e_SessionDraw[index][E_SESSIONDRAW_SHOW]) return;
    TextDrawShowForAll(SessionTextdrawData_GetDraw(index));
}