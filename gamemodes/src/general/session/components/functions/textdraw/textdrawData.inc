


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextDrawData_LoadAll() {

    new uniqueId = Session_GetId();
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT indexDraw, id FROM textdraws WHERE project_id = %i ORDER BY `indexDraw` ASC", uniqueId);

    if(cache) 
    {
        if(DB_GetRowCount(cache))
        {
            new index, drawId;
            do
            {
                index = DB_GetFieldIntByName(cache, "indexDraw");
                drawId = DB_GetFieldIntByName(cache, "id");

                SessionTextDrawData_Load(index, drawId);
            }
            while(DB_SelectNextRow(cache));
        }

        DB_FreeResultSet(cache);
    }
}

stock SessionTextDrawData_Load(index, id) {

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
                                                            box, \
                                                            model, \
                                                            model_rotation, \
                                                            model_colors, \
                                                            itemType, \
                                                            variable \
                                                        FROM textdraws  \
                                                        WHERE id = %i",

                                                        id
                                                    );

    if(cache) 
    {
        if(DB_GetRowCount(cache))
        {
            new buffGeneral[84 + 1];

            // Ints
            e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID] = id;
            e_SessionDraw[index][E_SESSIONDRAW_FONT] = E_TYPEFONT:DB_GetFieldIntByName(cache, "font");
            e_SessionDraw[index][E_SESSIONDRAW_ALIGN] = E_TYPEALIGNMENT:DB_GetFieldIntByName(cache, "align");
            e_SessionDraw[index][E_SESSIONDRAW_PROPORTION] = bool:DB_GetFieldIntByName(cache, "proportion");
            e_SessionDraw[index][E_SESSIONDRAW_OUTLINE] = DB_GetFieldIntByName(cache, "outline");
            e_SessionDraw[index][E_SESSIONDRAW_SHADOW] = DB_GetFieldIntByName(cache, "shadow");
            e_SessionDraw[index][E_SESSIONDRAW_COLOR] = DB_GetFieldIntByName(cache, "color");
            e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND] = DB_GetFieldIntByName(cache, "colorBackground");
            e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX] = DB_GetFieldIntByName(cache, "colorBox");
            e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE] = bool:DB_GetFieldIntByName(cache, "selectable");
            e_SessionDraw[index][E_SESSIONDRAW_MODE] = E_TYPEMODE:DB_GetFieldIntByName(cache, "mode");
            // e_SessionDraw[index][E_SESSIONDRAW_TYPE] = _:DB_GetFieldIntByName(cache, "itemType");
            e_SessionDraw[index][E_SESSIONDRAW_MODEL] = DB_GetFieldIntByName(cache, "model");
            e_SessionDraw[index][E_SESSIONDRAW_BOX] = bool:DB_GetFieldIntByName(cache, "box");

            // Strings
            DB_GetFieldStringByName(cache, "text", e_SessionDraw[index][E_SESSIONDRAW_TEXT]);
            DB_GetFieldStringByName(cache, "variable", e_SessionDraw[index][E_SESSIONDRAW_VARIABLE]);

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
            SessionTextDraw_Create(index);
        }

        DB_FreeResultSet(cache);
    }
}

stock SessionTextDrawData_Destroy(index, bool:execute_query = true) {

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "DELETE FROM textdraws WHERE id = %i", SessionTextDrawData_GetUniqueId(index))
        );
    }
    
    SessionTextDraw_Destroy(index);
}

stock SessionTextDrawData_Create(E_TYPEITEM:type) {

    new index = Iter_Free(SessionDraws);
    if(index == ITER_NONE)
        return -1;

    new project_id = Session_GetId();

    switch(type) {
        case E_TYPEITEM_TEXT: {

            SessionTextDrawData_Insert(
                .project_id = project_id, 
                .index = index, 
                .text = "DEFAULT", 
                .position = Float:{270.0, 170.0}, 
                .size = Float:{640.0, 640.0},
                .letterSize = Float:{0.3, 1.5}, 
                .font = E_TYPEFONT_1, 
                .align = E_TYPEALIGNMENT_LEFT, 
                .proportion = true, 
                .outline = 0, 
                .shadow = 0, 
                .color = RGB::RGBAToHex(255, 255, 255, 255), 
                .colorBackground = RGB::RGBAToHex(0, 0, 0, 150), 
                .colorBox = RGB::RGBAToHex(0, 0, 0, 150), 
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
            SessionTextDrawData_Insert(
                .project_id = project_id, 
                .index = index, 
                .text = "LD_SPAC:white", 
                .position = Float:{250.0, 150.0}, 
                .size = Float:{90.0, 90.0},
                .letterSize = Float:{0.0, 0.0}, 
                .font = E_TYPEFONT_SPRITE, 
                .align = E_TYPEALIGNMENT_LEFT, 
                .proportion = true, 
                .outline = 0, 
                .shadow = 0, 
                .color = RGB::RGBAToHex(255, 255, 255, 255), 
                .colorBackground = RGB::RGBAToHex(0, 0, 0, 0), 
                .colorBox = RGB::RGBAToHex(0, 0, 0, 0), 
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
            SessionTextDrawData_Insert(
                .project_id = project_id, 
                .index = index, 
                .text = "_", 
                .position = Float:{250.0, 150.0}, 
                .size = Float:{90.0, 90.0},
                .letterSize = Float:{0.0, 0.0}, 
                .font = E_TYPEFONT_MODEL, 
                .align = E_TYPEALIGNMENT_LEFT, 
                .proportion = true, 
                .outline = 0, 
                .shadow = 0, 
                .color = RGB::RGBAToHex(255, 255, 255, 255), 
                .colorBackground = RGB::RGBAToHex(0, 0, 0, 85), 
                .colorBox = RGB::RGBAToHex(0, 0, 0, 0), 
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

stock SessionTextDrawData_Copy(index) {

    new indexIter = Iter_Free(SessionDraws);
    if(indexIter == ITER_NONE)
        return -1;

    new uniqueId = SessionTextDrawData_GetUniqueId(index);

    // Copy Table
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "CREATE TEMPORARY TABLE t_copy AS SELECT * FROM textdraws WHERE id = %d;", uniqueId));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "UPDATE t_copy SET indexDraw = %i, id = NULL;", indexIter));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "INSERT INTO textdraws SELECT * FROM t_copy;"));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "DROP TABLE t_copy;"));

    new lastInsert = SessionTextDrawData_GetGenId(Session_GetId());
    if(lastInsert)
        SessionTextDrawData_Load(indexIter, lastInsert);

    // Iter_Add(SessionDraws, indexIter);
    return indexIter;
}

stock SessionTextDrawData_Insert(project_id, index, const text[], const Float:position[2], const Float:size[2], const Float:letterSize[2], E_TYPEFONT:font, E_TYPEALIGNMENT:align, bool:proportion, outline, shadow, color, colorBackground, colorBox, bool:selectable, E_TYPEMODE:mode, bool:box, model, const Float:modelRotation[4], const modelColors[2]) {

    new 
        DBResult:cache = DB_ExecuteQuery(IDConnection, "INSERT INTO textdraws (project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, model, model_colors, model_rotation, box) VALUES (%i, '%f, %f', '%f, %f', '%f, %f', '%s', %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, '%i,%i', '%f,%f,%f,%f', %i)", 
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
            model,
            modelColors[0], modelColors[1],
            modelRotation[0], modelRotation[1], modelRotation[2], modelRotation[3],
            box
        )
    ;

    if(cache) 
        DB_FreeResultSet(cache);

    new lastInsert = SessionTextDrawData_GetGenId(project_id);
    if(lastInsert)
        SessionTextDrawData_Load(index, lastInsert);
}

static stock SessionTextDrawData_GetGenId(uniqueId) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT  \
                                                            id \
                                                        FROM textdraws \
                                                        WHERE project_id = %i \
                                                        ORDER BY id DESC \
                                                        LIMIT 1",
                                                        
                                                        uniqueId
                                                    );

    if(cache)
        return DB_GetFieldIntByName(cache, "id");

    return -1;
}

stock bool:SessionTextDrawData_Has(index)
    return Iter_Contains(SessionDraws, index);

stock SessionTextDrawData_GetUniqueId(index)
    return e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID];

stock SessionTextDrawData_GetString(index, dest[], maxlength = sizeof dest)
    strcat(dest, e_SessionDraw[index][E_SESSIONDRAW_TEXT], maxlength);

stock SessionTextDrawData_GetPosition(index, &Float:x, &Float:y) {
    x = e_SessionDraw[index][E_SESSIONDRAW_POSITION][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_POSITION][1];
}

stock SessionTextDrawData_GetSize(index, &Float:x, &Float:y) {
    x = e_SessionDraw[index][E_SESSIONDRAW_SIZE][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_SIZE][1];
}

stock SessionTextDrawData_GetLettSize(index, &Float:x, &Float:y) {
    x = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1];
}

stock SessionTextDrawData_GetModelRot(index, &Float:x, &Float:y, &Float:z, &Float:zoom) {
    x = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][0];
    y = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][1];
    z = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][2];
    zoom = e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][3];
}

stock SessionTextDrawData_GetModelCol(index, &color1, &color2) {
    color1 = e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][0];
    color2 = e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][1];
}

stock E_TYPEALIGNMENT:SessionTextDrawData_GetAlign(index)
    return e_SessionDraw[index][E_SESSIONDRAW_ALIGN];

// stock E_TYPEITEM:SessionTextDrawData_GetType(index)
//     return e_SessionDraw[index][E_SESSIONDRAW_TYPE];

stock SessionTextDrawData_GetColor(index)
    return e_SessionDraw[index][E_SESSIONDRAW_COLOR];

stock SessionTextDrawData_GetShadow(index)
    return e_SessionDraw[index][E_SESSIONDRAW_SHADOW];

stock SessionTextDrawData_GetOutline(index)
    return e_SessionDraw[index][E_SESSIONDRAW_OUTLINE];

stock SessionTextDrawData_GetColorBG(index)
    return e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND];

stock SessionTextDrawData_GetColorBox(index)
    return e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX];

stock E_TYPEFONT:SessionTextDrawData_GetFont(index)
    return e_SessionDraw[index][E_SESSIONDRAW_FONT];

stock bool:SessionTextDrawData_GetPropor(index)
    return e_SessionDraw[index][E_SESSIONDRAW_PROPORTION];

stock bool:SessionTextDrawData_GetBox(index)
    return e_SessionDraw[index][E_SESSIONDRAW_BOX];

stock SessionTextDrawData_GetModel(index)
    return e_SessionDraw[index][E_SESSIONDRAW_MODEL];

stock E_TYPEMODE:SessionTextDrawData_GetMode(index)
    return e_SessionDraw[index][E_SESSIONDRAW_MODE];

stock Text:SessionTextDrawData_GetDraw(index)
    return e_SessionDraw[index][E_SESSIONDRAW_DRAW];

stock bool:SessionTextDrawData_GetSelect(index)
    return e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE];

stock SessionTextDrawData_GetVariable(index, dest[], maxlength = sizeof dest) {
    
    if(isnull(e_SessionDraw[index][E_SESSIONDRAW_VARIABLE])) {
        switch(SessionTextDrawData_GetMode(index)) {
            case E_TYPEMODE_PLAYER: Session_GetPlayerVariable(dest, maxlength);
            case E_TYPEMODE_GLOBAL: Session_GetGlobalVariable(dest, maxlength);
        }
        return;
    }
    
    strcat(dest, e_SessionDraw[index][E_SESSIONDRAW_VARIABLE], maxlength);
}

//

stock SessionTextDrawData_SetUniqueId(index, uniqueId)
    e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID] = uniqueId;

stock SessionTextDrawData_SetModelCol(index, color1, color2, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][0] = color1;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS][1] = color2;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET model_colors = '%i,%i' WHERE id = %i", color1, color2, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPreviewVehicleColours(SessionTextDrawData_GetDraw(index), color1, color2);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetAlign(index, E_TYPEALIGNMENT:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_ALIGN] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET align = %i WHERE id = %i", _:type, SessionTextDrawData_GetUniqueId(index))
        );
    }

    new typeBuff = _:type;
    TextDrawAlignment(SessionTextDrawData_GetDraw(index), TEXT_DRAW_ALIGN:typeBuff);
    SessionTextDrawData_Update(index);

    SessionTextDraw_UpdateButton(index);
}

// stock SessionTextDrawData_SetType(index, E_TYPEITEM:type, bool:execute_query = true) {

//     e_SessionDraw[index][E_SESSIONDRAW_TYPE] = type;

//     if(execute_query) {
//         DB_FreeResultSet(
//             DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET itemType = %i WHERE id = %i", _:type, SessionTextDrawData_GetUniqueId(index))
//         );
//     }
// }

stock SessionTextDrawData_SetColor(index, color, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_COLOR] = color;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET color = %i WHERE id = %i", color, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawColour(SessionTextDrawData_GetDraw(index), color);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetShadow(index, value, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_SHADOW] = value;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET shadow = %i WHERE id = %i", value, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetShadow(SessionTextDrawData_GetDraw(index), value);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetOutline(index, value, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_OUTLINE] = value;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET outline = %i WHERE id = %i", value, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetOutline(SessionTextDrawData_GetDraw(index), value);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetColorBG(index, color, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND] = color;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET colorBackground = %i WHERE id = %i", color, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawBackgroundColour(SessionTextDrawData_GetDraw(index), color);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetColorBox(index, color, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX] = color;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET colorBox = %i WHERE id = %i", color, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawBoxColour(SessionTextDrawData_GetDraw(index), color);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetFont(index, E_TYPEFONT:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_FONT] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET font = %i WHERE id = %i", _:type, SessionTextDrawData_GetUniqueId(index))
        );
    }

    new typeBuff = _:type;
    TextDrawFont(SessionTextDrawData_GetDraw(index), TEXT_DRAW_FONT:typeBuff);
    SessionTextDrawData_Update(index);

    SessionTextDraw_UpdateButton(index);
}

stock SessionTextDrawData_SetPropor(index, bool:status, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_PROPORTION] = status;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET proportion = %i WHERE id = %i", status, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetProportional(SessionTextDrawData_GetDraw(index), status);
    SessionTextDrawData_Update(index);

    SessionTextDraw_UpdateButton(index);
}

stock SessionTextDrawData_SetBox(index, bool:status, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_BOX] = status;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET box = %i WHERE id = %i", status, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawUseBox(SessionTextDrawData_GetDraw(index), status);
    SessionTextDrawData_Update(index);

    SessionTextDraw_UpdateButton(index);
}

stock SessionTextDrawData_SetModel(index, model, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODEL] = model;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET model = %i WHERE id = %i", model, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPreviewModel(SessionTextDrawData_GetDraw(index), model);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetModelRot(index, Float:x, Float:y, Float:z, Float:zoom, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][1] = y;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][2] = z;
    e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION][3] = zoom;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET model_rotation = '%f,%f,%f,%f' WHERE id = %i", x, y, z, zoom, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPreviewRot(SessionTextDrawData_GetDraw(index), x, y, z, zoom);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetLettSize(index, Float:x, Float:y, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE][1] = y;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET letter_size = '%f,%f' WHERE id = %i", x, y, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawLetterSize(SessionTextDrawData_GetDraw(index), x, y);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetSize(index, Float:x, Float:y, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_SIZE][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_SIZE][1] = y;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET size = '%f,%f' WHERE id = %i", x, y, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawTextSize(SessionTextDrawData_GetDraw(index), x, y);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetPosition(index, Float:x, Float:y, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_POSITION][0] = x;
    e_SessionDraw[index][E_SESSIONDRAW_POSITION][1] = y;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET position = '%f,%f' WHERE id = %i", x, y, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetPos(SessionTextDrawData_GetDraw(index), x, y);
    SessionTextDrawData_Update(index);
}

stock SessionTextDrawData_SetString(index, const string[], bool:execute_query = true) {

    strcopy(e_SessionDraw[index][E_SESSIONDRAW_TEXT], string);

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET text = '%s' WHERE id = %i", string, SessionTextDrawData_GetUniqueId(index))
        );
    }

    new stringBuff[1024 + 1];
    strcat(stringBuff, string);

    Util_ConverterTextdrawText(stringBuff);
    TextDrawSetString(SessionTextDrawData_GetDraw(index), stringBuff);
}

stock SessionTextDrawData_SetMode(index, E_TYPEMODE:type, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_MODE] = type;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET mode = %i WHERE id = %i", _:type, SessionTextDrawData_GetUniqueId(index))
        );
    }

    SessionTextDraw_UpdateButton(index);
}

stock SessionTextDrawData_SetSelect(index, bool:status, bool:execute_query = true) {

    e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE] = status;

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET selectable = %i WHERE id = %i", status, SessionTextDrawData_GetUniqueId(index))
        );
    }

    TextDrawSetSelectable(SessionTextDrawData_GetDraw(index), status);
    SessionTextDrawData_Update(index);

    SessionTextDraw_UpdateButton(index);
}

stock SessionTextDrawData_SetVariable(index, const string[], bool:execute_query = true) {

    if(isnull(string))
        stringclear(e_SessionDraw[index][E_SESSIONDRAW_VARIABLE]);
    else
        strcopy(e_SessionDraw[index][E_SESSIONDRAW_VARIABLE], string);

    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET variable = %s WHERE id = %i", isnull(string) ? "NULL" : va_return("'%s'", string), SessionTextDrawData_GetUniqueId(index))
        );
    }
}

stock SessionTextDrawData_Show(index) {
    e_SessionDraw[index][E_SESSIONDRAW_SHOW] = true;
    SessionTextDrawData_ShowInternal(index);
}

static stock SessionTextDrawData_Update(index) {
    if(!e_SessionDraw[index][E_SESSIONDRAW_SHOW]) return;
    SessionTextDrawData_ShowInternal(index);
}

static stock SessionTextDrawData_ShowInternal(index) {

    foreach(new i: Users)
        if(!SpriteBrowser_Created(i))
            TextDrawShowForPlayer(i, SessionTextDrawData_GetDraw(index));
}

stock SessionTextDrawData_ReorganizeIndexs(project_id) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET indexDraw = ( \
                                                            SELECT  \
                                                                (newIndex - 1) \
                                                            FROM ( \
                                                                SELECT  \
                                                                    id,  \
                                                                    row_number() OVER (ORDER BY indexDraw) AS newIndex  \
                                                                FROM textdraws \
                                                                WHERE project_id = %i \
                                                            ) AS mapping \
                                                            WHERE mapping.id = textdraws.id \
                                                        ) \
                                                        WHERE project_id = %i",

                                                        project_id,
                                                        project_id
                                                    );

    if(cache)
    {
        DB_FreeResultSet(cache);
        SessionTextDrawData_Refresh();
    }
}

stock SessionTextDrawData_SetIndex(index, newIndex) {

    if(SessionTextDrawData_Has(newIndex)) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET indexDraw = %i WHERE id = %i", index, SessionTextDrawData_GetUniqueId(newIndex))
        );
    }

    DB_FreeResultSet(
        DB_ExecuteQuery(IDConnection, "UPDATE textdraws SET indexDraw = %i WHERE id = %i", newIndex, SessionTextDrawData_GetUniqueId(index))
    );

    SessionTextDrawData_Refresh();
}

stock SessionTextDrawData_Refresh() {
    SessionTextDraw_DestroyAll();
    SessionTextDrawData_LoadAll();
}