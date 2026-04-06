
                // Definers
#define         MAX_EXPORTS_QUEUE       (3)
#define         PATTERN_EXPORT_SSCANF   "P<(),>s[45]s[32]"

enum E_TYPEEXPORT {
    E_TYPEEXPORT_TEXT,
    E_TYPEEXPORT_CREATE,
    E_TYPEEXPORT_COLOR,
    E_TYPEEXPORT_BOX_COLOR,
    E_TYPEEXPORT_BACKGROUND_COLOR,
    E_TYPEEXPORT_ALIGNMENT,
    E_TYPEEXPORT_FONT,
    E_TYPEEXPORT_LETTER_SIZE,
    E_TYPEEXPORT_TEXT_SIZE,
    E_TYPEEXPORT_OUTLINE,
    E_TYPEEXPORT_SHADOW,
    E_TYPEEXPORT_PROPORTIONAL,
    E_TYPEEXPORT_USE_BOX,
    E_TYPEEXPORT_SELECTABLE,
    E_TYPEEXPORT_MODEL_ID,
    E_TYPEEXPORT_MODEL_COLOR,
    E_TYPEEXPORT_MODEL_ROTATION
};

static enum E_QUEUE {
    File:E_QUEUE_LEGACY,
    File:E_QUEUE_OPENMP,
};

static
    Iterator:Queue<MAX_EXPORTS_QUEUE>,
    e_Queue[MAX_EXPORTS_QUEUE][E_QUEUE]
;



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Export_CreateFile(const name[], const path[], Func:callback<i>, maxPlayer, maxGlobal) {

    new index = Iter_Free(Queue);
    if(index == ITER_NONE)
        return;
     
    e_Queue[index][E_QUEUE_LEGACY] = fopen(va_return(""#STUDIO_FOLDER"/%s%s.txt", path, name), io_write);
    e_Queue[index][E_QUEUE_OPENMP] = fopen(va_return(""#STUDIO_FOLDER"/%s%s-openmp.txt", path, name), io_write);

    Iter_Add(Queue, index);

    if(e_Queue[index][E_QUEUE_LEGACY] && e_Queue[index][E_QUEUE_OPENMP]) {

        new date[30 + 1];
        Util_ConvertTimestamp(gettime(), date, 1);

        Export_AddInFile(index, "/*");
        Export_AddInFile(index, "- Textdraw Studio - "#STUDIO_VERSION"");
        Export_AddInFile(index, va_return("- Exported on %s", date));
        Export_AddInFile(index, "*/");
        Export_AddInFile(index, " ");
        Export_AddInFile(index, " ");

        if(maxPlayer) {
            new variablePlayer[30 + 1];
            Session_GetPlayerVariable(variablePlayer);
            Export_AddInFile(index, va_return("new PlayerText:%s[MAX_PLAYERS][%i];", variablePlayer, maxPlayer));
        }

        if(maxGlobal) {
            new variableGlobal[30 + 1];
            Session_GetGlobalVariable(variableGlobal);
            Export_AddInFile(index, va_return("new Text:%s[%i];", variableGlobal, maxGlobal));
        }

        Indirect_Claim(callback);
        @.callback(index);
        Indirect_Release(callback);
    }

    Export_Destroy(index);
}

stock Export_Add(index, E_TYPEEXPORT:type, const input[]) {

    new 
        File:legacyApi = e_Queue[index][E_QUEUE_LEGACY],
        File:openmpApi = e_Queue[index][E_QUEUE_OPENMP],
        variable[45 + 1],
        findMode[45 + 1]
    ;

    switch(type) 
    {
        case E_TYPEEXPORT_TEXT: Export_AddInFile(index, input);

        case E_TYPEEXPORT_CREATE: // TextDrawCreate or CreatePlayerTextDraw(variable, x, y, string)
        {
            new 
                Float:position[2],
                string[1024 + 1]
            ;

            sscanf(input, ""#PATTERN_EXPORT_SSCANF"a<f>[2]s[1024]", findMode, variable, position, string);

            new len = strlen(string);
            if(len && string[len - 1] == ')')
                string[len - 1] = '\0';

            if(isequal(findMode, "CreatePlayerTextDraw", true))
                Export_AddInFile(index, va_return("%s = CreatePlayerTextDraw(playerid, %f, %f, \"%s\");", variable, position[0], position[1], string));
            else if(isequal(findMode, "TextDrawCreate", true))
                Export_AddInFile(index, va_return("%s = TextDrawCreate(%f, %f, \"%s\");", variable, position[0], position[1], string));
        }

        case E_TYPEEXPORT_COLOR: // TextDrawColor or PlayerTextDrawColor(variable, color)
        {
            new color;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, color);

            if(isequal(findMode, "PlayerTextDrawColor", true)) {
                Export_AddInFile(-1, va_return("PlayerTextDrawColor(playerid, %s, %d);", variable, color), legacyApi);
                Export_AddInFile(-1, va_return("PlayerTextDrawColour(playerid, %s, %d);", variable, color), openmpApi);    
            }
            else if(isequal(findMode, "TextDrawColor", true)) {
                Export_AddInFile(-1, va_return("TextDrawColor(%s, %d);", variable, color), legacyApi);
                Export_AddInFile(-1, va_return("TextDrawColour(%s, %d);", variable, color), openmpApi);
            }
        }

        case E_TYPEEXPORT_BOX_COLOR: // TextDrawBoxColor or PlayerTextDrawBoxColor(variable, color)
        {
            new color;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, color);

            if(isequal(findMode, "PlayerTextDrawBoxColor", true)) {
                Export_AddInFile(-1, va_return("PlayerTextDrawBoxColor(playerid, %s, %d);", variable, color), legacyApi);
                Export_AddInFile(-1, va_return("PlayerTextDrawBoxColour(playerid, %s, %d);", variable, color), openmpApi);    
            }
            else if(isequal(findMode, "TextDrawBoxColor", true)) {
                Export_AddInFile(-1, va_return("TextDrawBoxColor(%s, %d);", variable, color), legacyApi);
                Export_AddInFile(-1, va_return("TextDrawBoxColour(%s, %d);", variable, color), openmpApi);    
            }
        }

        case E_TYPEEXPORT_BACKGROUND_COLOR: // TextDrawBackgroundColor or PlayerTextDrawBackgroundColor(variable, color)
        {
            new color;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, color);

            if(isequal(findMode, "PlayerTextDrawBackgroundColor", true)) {
                Export_AddInFile(-1, va_return("PlayerTextDrawBackgroundColor(playerid, %s, %d);", variable, color), legacyApi);
                Export_AddInFile(-1, va_return("PlayerTextDrawBackgroundColour(playerid, %s, %d);", variable, color), openmpApi);    
            }
            else if(isequal(findMode, "TextDrawBackgroundColor", true)) {
                Export_AddInFile(-1, va_return("TextDrawBackgroundColor(%s, %d);", variable, color), legacyApi);
                Export_AddInFile(-1, va_return("TextDrawBackgroundColour(%s, %d);", variable, color), openmpApi);    
            }
        }

        case E_TYPEEXPORT_ALIGNMENT: // TextDrawAlignment or PlayerTextDrawAlignment(variable, value)
        {
            new alignment;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, alignment);

            if(isequal(findMode, "PlayerTextDrawAlignment", true)) {
                Export_AddInFile(-1, va_return("PlayerTextDrawAlignment(playerid, %s, %d);", variable, alignment), legacyApi);
                Export_AddInFile(-1, va_return("PlayerTextDrawAlignment(playerid, %s, %s);", variable, TaskBarTypeAlign_GetName(alignment)), openmpApi);    
            }
            else if(isequal(findMode, "TextDrawAlignment", true)) {
                Export_AddInFile(-1, va_return("TextDrawAlignment(%s, %d);", variable, alignment), legacyApi);
                Export_AddInFile(-1, va_return("TextDrawAlignment(%s, %s);", variable, TaskBarTypeAlign_GetName(alignment)), openmpApi);    
            }
        }

        case E_TYPEEXPORT_FONT: // TextDrawFont or PlayerTextDrawFont(variable, value)
        {
            new font;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, font);

            if(isequal(findMode, "PlayerTextDrawFont", true)) {
                Export_AddInFile(-1, va_return("PlayerTextDrawFont(playerid, %s, %d);", variable, font), legacyApi);
                Export_AddInFile(-1, va_return("PlayerTextDrawFont(playerid, %s, %s);", variable, TaskBarTypeFont_GetName(font)), openmpApi);    
            }
            else if(isequal(findMode, "TextDrawFont", true)) {
                Export_AddInFile(-1, va_return("TextDrawFont(%s, %d);", variable, font), legacyApi);
                Export_AddInFile(-1, va_return("TextDrawFont(%s, %s);", variable, TaskBarTypeFont_GetName(font)), openmpApi);    
            }
        }

        case E_TYPEEXPORT_LETTER_SIZE: // TextDrawLetterSize or PlayerTextDrawLetterSize(variable, x, y)
        {
            new Float:size[2];
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"a<f>[2]", findMode, variable, size);

            if(isequal(findMode, "PlayerTextDrawLetterSize", true))
                Export_AddInFile(index, va_return("PlayerTextDrawLetterSize(playerid, %s, %f, %f);", variable, size[0], size[1]));
            else if(isequal(findMode, "TextDrawLetterSize", true))
                Export_AddInFile(index, va_return("TextDrawLetterSize(%s, %f, %f);", variable, size[0], size[1]));
        }

        case E_TYPEEXPORT_TEXT_SIZE: // TextDrawTextSize or PlayerTextDrawTextSize(variable, x, y)
        {
            new Float:size[2];
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"a<f>[2]", findMode, variable, size);

            if(isequal(findMode, "PlayerTextDrawTextSize", true))
                Export_AddInFile(index, va_return("PlayerTextDrawTextSize(playerid, %s, %f, %f);", variable, size[0], size[1]));
            else if(isequal(findMode, "TextDrawTextSize", true))
                Export_AddInFile(index, va_return("TextDrawTextSize(%s, %f, %f);", variable, size[0], size[1]));
        }

        case E_TYPEEXPORT_OUTLINE:  // TextDrawSetOutline or PlayerTextDrawSetOutline(variable, value)
        {
            new value;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, value);

            if(isequal(findMode, "PlayerTextDrawSetOutline", true))
                Export_AddInFile(index, va_return("PlayerTextDrawSetOutline(playerid, %s, %i);", variable, value));
            else if(isequal(findMode, "TextDrawSetOutline", true))
                Export_AddInFile(index, va_return("TextDrawSetOutline(%s, %i);", variable, value));    
        }

        case E_TYPEEXPORT_SHADOW:  // TextDrawSetShadow or PlayerTextDrawSetShadow(variable, value)
        {
            new value;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, value);

            if(isequal(findMode, "PlayerTextDrawSetShadow", true))
                Export_AddInFile(index, va_return("PlayerTextDrawSetShadow(playerid, %s, %i);", variable, value));
            else if(isequal(findMode, "TextDrawSetShadow", true))
                Export_AddInFile(index, va_return("TextDrawSetShadow(%s, %i);", variable, value));    
        }

        case E_TYPEEXPORT_PROPORTIONAL:  // TextDrawSetProportional or PlayerTextDrawSetProportional(variable, value)
        {
            new value;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, value);

            if(isequal(findMode, "PlayerTextDrawSetProportional", true))
                Export_AddInFile(index, va_return("PlayerTextDrawSetProportional(playerid, %s, %s);", variable, value ? "true" : "false"));
            else if(isequal(findMode, "TextDrawSetProportional", true))
                Export_AddInFile(index, va_return("TextDrawSetProportional(%s, %s);", variable, value ? "true" : "false"));    
        }

        case E_TYPEEXPORT_USE_BOX: // TextDrawUseBox or PlayerTextDrawUseBox(variable, value)
        {
            new value;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, value);

            if(isequal(findMode, "PlayerTextDrawUseBox", true))
                Export_AddInFile(index, va_return("PlayerTextDrawUseBox(playerid, %s, %s);", variable, value ? "true" : "false"));
            else if(isequal(findMode, "TextDrawUseBox", true))
                Export_AddInFile(index, va_return("TextDrawUseBox(%s, %s);", variable, value ? "true" : "false"));    
        }

        case E_TYPEEXPORT_SELECTABLE: // TextDrawSetSelectable or PlayerTextDrawSetSelectable(variable, value)
        {
            new value;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, value);

            if(isequal(findMode, "PlayerTextDrawSetSelectable", true))
                Export_AddInFile(index, va_return("PlayerTextDrawSetSelectable(playerid, %s, %s);", variable, value ? "true" : "false"));
            else if(isequal(findMode, "TextDrawSetSelectable", true))
                Export_AddInFile(index, va_return("TextDrawSetSelectable(%s, %s);", variable, value ? "true" : "false"));    
        }

        case E_TYPEEXPORT_MODEL_ID: // TextDrawSetPreviewModel or PlayerTextDrawSetPreviewModel(variable, value)
        {
            new value;
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"i", findMode, variable, value);

            if(isequal(findMode, "PlayerTextDrawSetPreviewModel", true))
                Export_AddInFile(index, va_return("PlayerTextDrawSetPreviewModel(playerid, %s, %i);", variable, value));
            else if(isequal(findMode, "TextDrawSetPreviewModel", true))
                Export_AddInFile(index, va_return("TextDrawSetPreviewModel(%s, %i);", variable, value));    
        }

        case E_TYPEEXPORT_MODEL_COLOR: // TextDrawSetPreviewVehCol or PlayerTextDrawSetPreviewVehCol(variable, color1, color2)
        {
            new colors[2];
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"a<i>[2]", findMode, variable, colors);

            if(isequal(findMode, "PlayerTextDrawSetPreviewVehCol", true)) {
                Export_AddInFile(-1, va_return("PlayerTextDrawSetPreviewVehCol(playerid, %s, %i, %i);", variable, colors[0], colors[1]), legacyApi);
                Export_AddInFile(-1, va_return("PlayerTextDrawSetPreviewVehicleColours(playerid, %s, %i, %i);", variable, colors[0], colors[1]), openmpApi);
            }
            else if(isequal(findMode, "TextDrawSetPreviewVehCol", true)) {
                Export_AddInFile(-1, va_return("TextDrawSetPreviewVehCol(%s, %i, %i);", variable, colors[0], colors[1]), legacyApi);
                Export_AddInFile(-1, va_return("TextDrawSetPreviewVehicleColours(%s, %i, %i);", variable, colors[0], colors[1]), openmpApi);
            }
        }

        case E_TYPEEXPORT_MODEL_ROTATION: // TextDrawSetPreviewRot or PlayerTextDrawSetPreviewRot(variable, x, y, z, zoom)
        {
            new Float:rotation[4];
            sscanf(input, ""#PATTERN_EXPORT_SSCANF"a<f>[4]", findMode, variable, rotation);

            if(isequal(findMode, "PlayerTextDrawSetPreviewRot", true))
                Export_AddInFile(index, va_return("PlayerTextDrawSetPreviewRot(playerid, %s, %f, %f, %f, %f);", variable, rotation[0], rotation[1], rotation[2], rotation[3]));
            else if(isequal(findMode, "TextDrawSetPreviewRot", true))
                Export_AddInFile(index, va_return("TextDrawSetPreviewRot(%s, %f, %f, %f, %f);", variable, rotation[0], rotation[1], rotation[2], rotation[3]));  
        }
    }
}

static stock Export_AddInFile(index, const string[], File:file = File:-1) {

    if(file != File:-1) {
        fwrite(file, string);
        fwrite(file, "\r\n");
        return;
    }
    
    new 
        File:legacyApi = e_Queue[index][E_QUEUE_LEGACY],
        File:openmpApi = e_Queue[index][E_QUEUE_OPENMP]
    ;

    fwrite(legacyApi, string);
    fwrite(legacyApi, "\r\n");

    fwrite(openmpApi, string);
    fwrite(openmpApi, "\r\n");
}

static stock Export_Destroy(index) {

    if(e_Queue[index][E_QUEUE_OPENMP])
        fclose(e_Queue[index][E_QUEUE_OPENMP]);

    if(e_Queue[index][E_QUEUE_LEGACY])
        fclose(e_Queue[index][E_QUEUE_LEGACY]);

    Iter_Remove(Queue, index);

    static const e_Clear[E_QUEUE];
    e_Queue[index] = e_Clear;
}