
            // Definers
#define     QUERY_EXPORT_DEFAULT    "SELECT \
                                        t.text, \
                                        t.position, \
                                        t.size, \
                                        t.letter_size, \
                                        t.font, \
                                        t.align, \
                                        t.proportion, \
                                        t.shadow, \
                                        t.outline, \
                                        t.color, \
                                        t.colorBackground, \
                                        t.colorBox, \
                                        t.selectable, \
                                        t.box, \
                                        t.model, \
                                        t.model_colors, \
                                        t.model_rotation, \
                                        p.playerVariable, \
                                        p.globalVariable \
                                    FROM textdraws t"

#define     QUERY_EXPORT_PROJECT    " \
                                        "#QUERY_EXPORT_DEFAULT" \
                                        JOIN projects p ON p.id = t.project_id \
                                        WHERE t.project_id = %i AND t.mode = %i \
                                        ORDER BY t.indexDraw ASC \
                                    "

#define     QUERY_EXPORT_GROUP      " \
                                        "#QUERY_EXPORT_DEFAULT" \
                                        JOIN projects p ON p.id = t.project_id \
                                        JOIN groups_textdraws gt ON gt.draw_id = t.id \
                                        WHERE gt.group_id = %i \
                                        ORDER BY t.indexDraw ASC \
                                    "


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionTextDrawExport_Create(project_id, const name[], maxPlayer, maxGlobal) {

    inline ProcessExportTaskBar(index) {

        new DBResult:cache;

        // Player
        cache = DB_ExecuteQuery(IDConnection, QUERY_EXPORT_PROJECT, project_id, _:E_TYPEMODE_PLAYER);
        if(cache) {
            if(DB_GetRowCount(cache)) 
                SessionTextDrawExport_Player(index, cache);

            DB_FreeResultSet(cache);
        }

        // Global
        cache = DB_ExecuteQuery(IDConnection, QUERY_EXPORT_PROJECT, project_id, _:E_TYPEMODE_GLOBAL);
        if(cache) {
            if(DB_GetRowCount(cache))
                SessionTextDrawExport_Global(index, cache);

            DB_FreeResultSet(cache);
        }
    }

    Export_CreateFile(name, ""#STUDIO_EXPORT"//", using inline ProcessExportTaskBar, maxPlayer, maxGlobal);
}

static stock SessionTextDrawExport_Player(index, DBResult:cache) {

    new
        count,
<<<<<<< HEAD
=======
        circle,
>>>>>>> f8c702ac0dc8667aea488afa3ff526e6c208f9cb
        createBuff[1024 + 56 + 45 + 5 + 1],
        variableBuff[30 + 8 + 1],
        stringBuff[76 + 1],
        variable[30 + 1],
        text[1024 + 1],
        colors[2],
        bool:selectable,
        Float:rotation[4],
        Float:sizeBuff[2]
    ;

    do
    {
<<<<<<< HEAD
=======
        if(E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_CIRCLE || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_HEXAGON || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_DIAMOND || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_TRIANGLE || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_PARENS || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_ARC) {
            new Float:cpos[2], Float:csize[2], Float:clett[2], cvalue, cmax, ccolor, cbg;
            DB_GetFieldStringByName(cache, "position", stringBuff);
            sscanf(stringBuff, "p<,>a<f>[2]", cpos);
            DB_GetFieldStringByName(cache, "size", stringBuff);
            sscanf(stringBuff, "p<,>a<f>[2]", csize);
            DB_GetFieldStringByName(cache, "letter_size", stringBuff);
            sscanf(stringBuff, "p<,>a<f>[2]", clett);
            DB_GetFieldStringByName(cache, "text", text);
            cvalue = strval(text);
            cmax = floatround(clett[1]);
            if(cmax < 1) cmax = 100;
            if(cvalue < 0) cvalue = 0;
            if(cvalue > cmax) cvalue = cmax;
            ccolor = DB_GetFieldIntByName(cache, "color");
            cbg = DB_GetFieldIntByName(cache, "colorBackground");
            Export_Add(index, E_TYPEEXPORT_TEXT, " ");
            switch(E_TYPEFONT:DB_GetFieldIntByName(cache, "font")) {
                case E_TYPEFONT_CIRCLE: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Circle Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerCircleProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerCircleProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_HEXAGON: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Hexagon Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerHexagonProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerHexagonProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_DIAMOND: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Diamond Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerDiamondProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerDiamondProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_SQUARE: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Square Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerSquareProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerSquareProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_TRIANGLE: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Triangle Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerTriangleProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f, false);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerTriangleProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_PARENS: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Pares Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerParensProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f, false);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerParensProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_ARC: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Arc Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerArcProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerArcProgress(playerid, %d, %d);", circle, cvalue));
                }
            }
            circle++;
            continue;
        }
>>>>>>> f8c702ac0dc8667aea488afa3ff526e6c208f9cb
        Export_Add(index, E_TYPEEXPORT_TEXT, " ");

        DB_GetFieldStringByName(cache, "playerVariable", variable);
        DB_GetFieldStringByName(cache, "text", text);
        DB_GetFieldStringByName(cache, "position", stringBuff);
        sscanf(stringBuff, "p<,>a<f>[2]", sizeBuff);

        format(variableBuff, sizeof variableBuff, "%s[playerid][%d]", variable, count);
        format(createBuff, sizeof createBuff, "CreatePlayerTextDraw(%s, %f, %f, %s)", variableBuff, sizeBuff[0], sizeBuff[1], text);
        Export_Add(index, E_TYPEEXPORT_CREATE, createBuff);

        DB_GetFieldStringByName(cache, "size", stringBuff);
        sscanf(stringBuff, "p<,>a<f>[2]", sizeBuff);
        Export_Add(index, E_TYPEEXPORT_TEXT_SIZE, va_return("PlayerTextDrawTextSize(%s, %f, %f)", variableBuff, sizeBuff[0], sizeBuff[1]));

        Export_Add(index, E_TYPEEXPORT_ALIGNMENT, va_return("PlayerTextDrawAlignment(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "align")));
        Export_Add(index, E_TYPEEXPORT_COLOR, va_return("PlayerTextDrawColor(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "color")));
        Export_Add(index, E_TYPEEXPORT_BACKGROUND_COLOR, va_return("PlayerTextDrawBackgroundColor(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "colorBackground")));
        Export_Add(index, E_TYPEEXPORT_FONT, va_return("PlayerTextDrawFont(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "font")));
        Export_Add(index, E_TYPEEXPORT_SHADOW, va_return("PlayerTextDrawSetShadow(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "shadow")));
        Export_Add(index, E_TYPEEXPORT_OUTLINE, va_return("PlayerTextDrawSetOutline(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "outline")));
        Export_Add(index, E_TYPEEXPORT_PROPORTIONAL, va_return("PlayerTextDrawSetProportional(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "proportion")));
        
        switch(E_TYPEFONT:DB_GetFieldIntByName(cache, "font")) 
        {
            case E_TYPEFONT_0, E_TYPEFONT_1, E_TYPEFONT_2, E_TYPEFONT_3:
            {
                DB_GetFieldStringByName(cache, "letter_size", stringBuff);
                sscanf(stringBuff, "p<,>a<f>[2]", sizeBuff);
                Export_Add(index, E_TYPEEXPORT_LETTER_SIZE, va_return("PlayerTextDrawLetterSize(%s, %f, %f)", variableBuff, sizeBuff[0], sizeBuff[1]));

                Export_Add(index, E_TYPEEXPORT_USE_BOX, va_return("PlayerTextDrawUseBox(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "box")));
                Export_Add(index, E_TYPEEXPORT_BOX_COLOR, va_return("PlayerTextDrawBoxColor(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "colorBox")));
            }
<<<<<<< HEAD

=======
>>>>>>> f8c702ac0dc8667aea488afa3ff526e6c208f9cb
            case E_TYPEFONT_MODEL:
            {
                Export_Add(index, E_TYPEEXPORT_MODEL_ID, va_return("PlayerTextDrawSetPreviewModel(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "model")));

                DB_GetFieldStringByName(cache, "model_colors", stringBuff);
                sscanf(stringBuff, "p<,>a<i>[2]", colors);
                Export_Add(index, E_TYPEEXPORT_MODEL_COLOR, va_return("PlayerTextDrawSetPreviewVehCol(%s, %i, %i)", variableBuff, colors[0], colors[1]));

                DB_GetFieldStringByName(cache, "model_rotation", stringBuff);
                sscanf(stringBuff, "p<,>a<f>[4]", rotation);
                Export_Add(index, E_TYPEEXPORT_MODEL_ROTATION, va_return("PlayerTextDrawSetPreviewRot(%s, %f, %f, %f, %f)", variableBuff, rotation[0], rotation[1], rotation[2], rotation[3]));
            }
        }

        if((selectable = bool:DB_GetFieldIntByName(cache, "selectable")))
            Export_Add(index, E_TYPEEXPORT_SELECTABLE, va_return("PlayerTextDrawSetSelectable(%s, %i)", variableBuff, selectable));
        
        count++;
    }
    while(DB_SelectNextRow(cache));
}

static stock SessionTextDrawExport_Global(index, DBResult:cache) {

    new
        count,
<<<<<<< HEAD
=======
        circle,
>>>>>>> f8c702ac0dc8667aea488afa3ff526e6c208f9cb
        createBuff[1024 + 56 + 45 + 5 + 1],
        variableBuff[30 + 8 + 1],
        stringBuff[76 + 1],
        variable[30 + 1],
        text[1024 + 1],
        colors[2],
        Float:rotation[4],
        Float:sizeBuff[2]
    ;

    do
    {
<<<<<<< HEAD
=======
        if(E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_CIRCLE || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_HEXAGON || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_DIAMOND || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_TRIANGLE || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_PARENS || E_TYPEFONT:DB_GetFieldIntByName(cache, "font") == E_TYPEFONT_ARC) {
            new Float:cpos[2], Float:csize[2], Float:clett[2], cvalue, cmax, ccolor, cbg;
            DB_GetFieldStringByName(cache, "position", stringBuff);
            sscanf(stringBuff, "p<,>a<f>[2]", cpos);
            DB_GetFieldStringByName(cache, "size", stringBuff);
            sscanf(stringBuff, "p<,>a<f>[2]", csize);
            DB_GetFieldStringByName(cache, "letter_size", stringBuff);
            sscanf(stringBuff, "p<,>a<f>[2]", clett);
            DB_GetFieldStringByName(cache, "text", text);
            cvalue = strval(text);
            cmax = floatround(clett[1]);
            if(cmax < 1) cmax = 100;
            if(cvalue < 0) cvalue = 0;
            if(cvalue > cmax) cvalue = cmax;
            ccolor = DB_GetFieldIntByName(cache, "color");
            cbg = DB_GetFieldIntByName(cache, "colorBackground");
            Export_Add(index, E_TYPEEXPORT_TEXT, " ");
            switch(E_TYPEFONT:DB_GetFieldIntByName(cache, "font")) {
                case E_TYPEFONT_CIRCLE: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Circle Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerCircleProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerCircleProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_HEXAGON: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Hexagon Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerHexagonProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerHexagonProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_DIAMOND: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Diamond Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerDiamondProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerDiamondProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_SQUARE: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Square Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerSquareProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerSquareProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_TRIANGLE: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Triangle Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerTriangleProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f, false);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerTriangleProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_PARENS: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Pares Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerParensProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f, false);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerParensProgress(playerid, %d, %d);", circle, cvalue));
                }
                case E_TYPEFONT_ARC: {
                    Export_Add(index, E_TYPEEXPORT_TEXT, "// Arc Progress");
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("CreatePlayerArcProgress(playerid, %f, %f, %d, %d, %d, %f, %f, %f);", cpos[0], cpos[1], cmax, ccolor, cbg, csize[0], csize[1], clett[0]));
                    Export_Add(index, E_TYPEEXPORT_TEXT, va_return("UpdatePlayerArcProgress(playerid, %d, %d);", circle, cvalue));
                }
            }
            circle++;
            continue;
        }
>>>>>>> f8c702ac0dc8667aea488afa3ff526e6c208f9cb
        Export_Add(index, E_TYPEEXPORT_TEXT, " ");

        DB_GetFieldStringByName(cache, "globalVariable", variable);
        DB_GetFieldStringByName(cache, "text", text);
        DB_GetFieldStringByName(cache, "position", stringBuff);
        sscanf(stringBuff, "p<,>a<f>[2]", sizeBuff);

        format(variableBuff, sizeof variableBuff, "%s[%d]", variable, count);
        format(createBuff, sizeof createBuff, "TextDrawCreate(%s, %f, %f, %s)", variableBuff, sizeBuff[0], sizeBuff[1], text);
        Export_Add(index, E_TYPEEXPORT_CREATE, createBuff);

        DB_GetFieldStringByName(cache, "size", stringBuff);
        sscanf(stringBuff, "p<,>a<f>[2]", sizeBuff);
        Export_Add(index, E_TYPEEXPORT_TEXT_SIZE, va_return("TextDrawTextSize(%s, %f, %f)", variableBuff, sizeBuff[0], sizeBuff[1]));

        Export_Add(index, E_TYPEEXPORT_ALIGNMENT, va_return("TextDrawAlignment(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "align")));
        Export_Add(index, E_TYPEEXPORT_COLOR, va_return("TextDrawColor(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "color")));
        Export_Add(index, E_TYPEEXPORT_BACKGROUND_COLOR, va_return("TextDrawBackgroundColor(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "colorBackground")));
        Export_Add(index, E_TYPEEXPORT_FONT, va_return("TextDrawFont(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "font")));
        Export_Add(index, E_TYPEEXPORT_SHADOW, va_return("TextDrawSetShadow(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "shadow")));
        Export_Add(index, E_TYPEEXPORT_OUTLINE, va_return("TextDrawSetOutline(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "outline")));
        Export_Add(index, E_TYPEEXPORT_PROPORTIONAL, va_return("TextDrawSetProportional(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "proportion")));
        
        switch(E_TYPEFONT:DB_GetFieldIntByName(cache, "font")) 
        {
            case E_TYPEFONT_0, E_TYPEFONT_1, E_TYPEFONT_2, E_TYPEFONT_3:
            {
                DB_GetFieldStringByName(cache, "letter_size", stringBuff);
                sscanf(stringBuff, "p<,>a<f>[2]", sizeBuff);
                Export_Add(index, E_TYPEEXPORT_LETTER_SIZE, va_return("TextDrawLetterSize(%s, %f, %f)", variableBuff, sizeBuff[0], sizeBuff[1]));

                Export_Add(index, E_TYPEEXPORT_USE_BOX, va_return("TextDrawUseBox(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "box")));
                Export_Add(index, E_TYPEEXPORT_BOX_COLOR, va_return("TextDrawBoxColor(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "colorBox")));
            }
<<<<<<< HEAD

=======
>>>>>>> f8c702ac0dc8667aea488afa3ff526e6c208f9cb
            case E_TYPEFONT_MODEL:
            {
                Export_Add(index, E_TYPEEXPORT_MODEL_ID, va_return("TextDrawSetPreviewModel(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "model")));

                DB_GetFieldStringByName(cache, "model_colors", stringBuff);
                sscanf(stringBuff, "p<,>a<i>[2]", colors);
                Export_Add(index, E_TYPEEXPORT_MODEL_COLOR, va_return("TextDrawSetPreviewVehCol(%s, %i, %i)", variableBuff, colors[0], colors[1]));

                DB_GetFieldStringByName(cache, "model_rotation", stringBuff);
                sscanf(stringBuff, "p<,>a<f>[4]", rotation);
                Export_Add(index, E_TYPEEXPORT_MODEL_ROTATION, va_return("TextDrawSetPreviewRot(%s, %f, %f, %f, %f)", variableBuff, rotation[0], rotation[1], rotation[2], rotation[3]));
            }
        }

        Export_Add(index, E_TYPEEXPORT_SELECTABLE, va_return("TextDrawSetSelectable(%s, %i)", variableBuff, DB_GetFieldIntByName(cache, "selectable")));
        count++;
    }
    while(DB_SelectNextRow(cache));
}