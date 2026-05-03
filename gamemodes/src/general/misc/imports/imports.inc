
            // Definers
#define         PATTERN_PLAYER       "{s[32]}{s[32]}"
#define         PATTERN_GLOBAL       "{s[32]}"


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Import_Get(playerid, const name[]) {

    new fileStream[164 + 1];
    format(fileStream, sizeof fileStream, ""#STUDIO_FOLDER"/"#STUDIO_IMPORT"/%s.txt", name);

    if(!fexist(fileStream)) {
        SendMessage(playerid, -1, ""#MESSAGE_RED"This project does not exist");
        return;
    }

    new 
        File:handle = fopen(fileStream, io_read),
        string[1024 + 1],
        intBuff,
        intsBuff[2],
        stringBuff[32 + 1],
        Float:position[2],
        Float:positionBuff[4],
        index = -1,
        buff[sizeof string + 32 + 1]
    ;

    SessionPlayer_ResetLocalGroup(playerid);

    while(fread(handle, buff)) {

        if(isnull(buff)) continue;
        Util_DeleteCharacters(buff, 2);   // Remove \n

        if(!sscanf(buff, "'CreatePlayerTextDraw('p<,>{s[15]}a<f>[2]p<)>s[1024]", position, string) 
        || !sscanf(buff, "'TextDrawCreate('p<,>a<f>[2]p<)>s[1024]", position, string) 
        || !sscanf(buff, "'CreateDynamicPlayerTextDraw('p<,>a<f>[2]p<)>s[1024]", position, string) 
        || !sscanf(buff, "'CreateDynamicTextDraw('p<,>a<f>[2]p<)>s[1024]", position, string)) {
            
            Util_DeleteCharacters(string, 3);
            Util_DeleteCharacters(string, 1, true);

            index = SessionTextDrawData_Create(E_TYPEITEM_TEXT);
            SessionTextDrawData_SetString(index, string);
            SessionTextDrawData_SetPosition(index, position[0], position[1]);

            if(strfind(buff, "CreatePlayerTextDraw", true) != -1 || strfind(buff, "CreateDynamicPlayerTextDraw", true) != -1)
                SessionTextDrawData_SetMode(index, E_TYPEMODE_PLAYER);

            SessionPlayer_AddDraw(playerid, index);
        }
        else if(index >= 0) 
        {
            // Text-Size
            if(!sscanf(buff, "P<(,)>'PlayerTextDrawTextSize'"#PATTERN_PLAYER"a<f>[2]", position) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawTextSize'"#PATTERN_PLAYER"a<f>[2]", position)
            || !sscanf(buff, "P<(,)>'TextDrawTextSize'"#PATTERN_GLOBAL"a<f>[2]", position)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawTextSize'"#PATTERN_GLOBAL"a<f>[2]", position)) 
                SessionTextDrawData_SetSize(index, position[0], position[1]);

            // Alignment
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawAlignment'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawAlignment'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawAlignment'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawAlignment'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetAlign(index, E_TYPEALIGNMENT:intBuff);

            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawAlignment'"#PATTERN_PLAYER"s[32]", stringBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawAlignment'"#PATTERN_GLOBAL"s[32]", stringBuff)) {
                Util_DeleteCharacters(stringBuff, 2);
                SessionTextDrawData_SetAlign(index, TaskBarTypeAlign_GetType(stringBuff));
            }
            
            // Color
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawColour'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'PlayerTextDrawColor'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawColour'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawColor'"#PATTERN_GLOBAL"i", intBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawColour'"#PATTERN_GLOBAL"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicTextDrawColour'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetColor(index, intBuff);

            // Background Color
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawBackgroundColour'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'PlayerTextDrawBackgroundColor'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawBGColour'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawBGColor'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawBackgroundColour'"#PATTERN_GLOBAL"i", intBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawBackgroundColor'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawBackgroundColor'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawBackgroundColour'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetColorBG(index, intBuff);

            // Box Color
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawBoxColour'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'PlayerTextDrawBoxColor'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawBoxColor'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawBoxColour'"#PATTERN_GLOBAL"i", intBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawBoxColor'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawBoxColour'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetColorBox(index, intBuff);

            // Font
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawFont'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawFont'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawFont'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawFont'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetFont(index, E_TYPEFONT:intBuff);

            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawFont'"#PATTERN_PLAYER"s[32]", stringBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawFont'"#PATTERN_GLOBAL"s[32]", stringBuff)) {
                Util_DeleteCharacters(stringBuff, 2);
                SessionTextDrawData_SetFont(index, TaskBarTypeFont_GetType(stringBuff));
            }

            // Shadow
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetShadow'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawSetShadow'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetShadow'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetShadow'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetShadow(index, intBuff);

            // Outline
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetOutline'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawSetOutline'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetOutline'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetOutline'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetOutline(index, intBuff);

            // Proportional
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetProportional'"#PATTERN_PLAYER"s[10]", stringBuff) 
            || !sscanf(buff, "P<(,)>'DynPlayerTextSetProportional'"#PATTERN_PLAYER"s[10]", stringBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetProportional'"#PATTERN_GLOBAL"s[10]", stringBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetProportional'"#PATTERN_GLOBAL"s[10]", stringBuff)) {

                new bool:status;
                if(strfind(stringBuff, "true", true) != -1 || strfind(stringBuff, "1", true) != -1)
                    status = true;

                SessionTextDrawData_SetPropor(index, status);
            }

            // Selectable
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetSelectable'"#PATTERN_PLAYER"s[10]", stringBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawSelectable'"#PATTERN_PLAYER"s[10]", stringBuff) 
            || !sscanf(buff, "P<(,)>'TextDrawSetSelectable'"#PATTERN_GLOBAL"s[10]", stringBuff) 
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetSelectable'"#PATTERN_GLOBAL"s[10]", stringBuff)) {

                new bool:status;
                if(strfind(stringBuff, "true", true) != -1 || strfind(stringBuff, "1", true) != -1)
                    status = true;

                SessionTextDrawData_SetSelect(index, status);
            }

            // Letter Size
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawLetterSize'"#PATTERN_PLAYER"a<f>[2]", position) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawLetterSize'"#PATTERN_PLAYER"a<f>[2]", position)
            || !sscanf(buff, "P<(,)>'TextDrawLetterSize'"#PATTERN_GLOBAL"a<f>[2]", position)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawLetterSize'"#PATTERN_GLOBAL"a<f>[2]", position))
                SessionTextDrawData_SetLettSize(index, position[0], position[1]);

            // Use Box
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawUseBox'"#PATTERN_PLAYER"s[10]", stringBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawUseBox'"#PATTERN_PLAYER"s[10]", stringBuff)
            || !sscanf(buff, "P<(,)>'TextDrawUseBox'"#PATTERN_GLOBAL"s[10]", stringBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawUseBox'"#PATTERN_GLOBAL"s[10]", stringBuff)) {

                new bool:status;
                if(strfind(stringBuff, "true", true) != -1 || strfind(stringBuff, "1", true) != -1)
                    status = true;

                SessionTextDrawData_SetBox(index, status);
            }

            // Preview Model
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetPreviewModel'"#PATTERN_PLAYER"i", intBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawSetPrevMdl'"#PATTERN_PLAYER"i", intBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetPreviewModel'"#PATTERN_GLOBAL"i", intBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetPreviewModel'"#PATTERN_GLOBAL"i", intBuff))
                SessionTextDrawData_SetModel(index, intBuff);
            
            // Preview Model - Colors
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetPreviewVehicleColours'"#PATTERN_PLAYER"a<i>[2]", intsBuff) 
            || !sscanf(buff, "P<(,)>'PlayerTextDrawSetPreviewVehicleColors'"#PATTERN_PLAYER"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'PlayerTextDrawSetPreviewVehCol'"#PATTERN_PLAYER"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawPrevVehCol'"#PATTERN_PLAYER"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetPreviewVehicleColours'"#PATTERN_GLOBAL"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetPreviewVehicleColors'"#PATTERN_GLOBAL"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetPreviewVehCol'"#PATTERN_GLOBAL"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetPreviewVehCol'"#PATTERN_GLOBAL"a<i>[2]", intsBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetPreviewVehCol'"#PATTERN_GLOBAL"a<i>[2]", intsBuff))
                SessionTextDrawData_SetModelCol(index, intsBuff[0], intsBuff[1]);

            // Preview Model - Rotation
            else if(!sscanf(buff, "P<(,)>'PlayerTextDrawSetPreviewRot'"#PATTERN_PLAYER"a<f>[4]", positionBuff) 
            || !sscanf(buff, "P<(,)>'DynamicPlayerTextDrawSetPrevRot'"#PATTERN_PLAYER"a<f>[4]", positionBuff)
            || !sscanf(buff, "P<(,)>'TextDrawSetPreviewRot'"#PATTERN_GLOBAL"a<f>[4]", positionBuff)
            || !sscanf(buff, "P<(,)>'DynamicTextDrawSetPreviewRot'"#PATTERN_GLOBAL"a<f>[4]", positionBuff))
                SessionTextDrawData_SetModelRot(index, positionBuff[0], positionBuff[1], positionBuff[2], positionBuff[3]);
        }
    }

    fclose(handle);
}