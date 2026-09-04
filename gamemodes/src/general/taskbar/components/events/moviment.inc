
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnTaskBarMovimentUpdate(playerid);

static enum E_DATA {
    E_DATA_TIMER_KEY,
    E_DATA_DELAY,
    E_DATA_COLUMN,
    E_DATA_COLUMN_MAX,
    Float:E_DATA_OFFSET[2],
    bool:E_DATA_SHOW_TIPS,
    Float:E_DATA_SPEED
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

static const
    Float:MAX_SPEED_HIGH = 10.0
;

hook OnUserLogin(playerid) {

    TaskBarEventMoviment_SetSpeed(playerid, 1.0);
    TaskBarEventMoviment_SetTips(playerid, true, false);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnUserLogout(playerid) {

    TaskBarEventMoviment_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerTaskBarDrawUnSelected(playerid) {

    TaskBarKey_Set(playerid, E_TYPEKEY_DISABLED);
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnTaskBarMovimentUpdate(playerid) {

    new 
        KEY:keys, 
        updown, 
        leftright
    ;

    GetPlayerKeys(playerid, keys, updown, leftright);

    if(keys & KEY_SECONDARY_ATTACK) TaskBarKey_Set(playerid, E_TYPEKEY_DISABLED);
    else if(keys & KEY_YES && !TaskBarEventMoviment_HasDelay(playerid)) {
        TaskBarEventMoviment_SetTips(playerid, !TaskBarEventMoviment_GetTips(playerid));
        TaskBarEventMoviment_SetDelay(playerid, 500);
    }
    else if(keys & KEY_CTRL_BACK) {

        new dialog[186 + 1];
        LangF(playerid, dialog, sizeof dialog, E_LANG_MOV_SPEED_BODY, TaskBarEventMoviment_GetSpeed(playerid));

        Dialog_Show(playerid, D_MOVIMENT_SPEED, DIALOG_STYLE_INPUT, L(playerid, E_LANG_MOV_SPEED_TITLE), dialog, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_CANCEL));
    }
    
    else if(keys & KEY_NO) {
        
        new 
            E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid),
            index = TaskBarTextDraw_GetSelected(playerid)
        ;

        if(typeKey == E_TYPEKEY_SIZE || typeKey == E_TYPEKEY_POSITION || typeKey == E_TYPEKEY_LETTER_SIZE) {

            new 
                dialog[256 + 1],
                Float:position[2],
                E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey)
            ;

            TaskBarTextDrawUpdate_GetPos(typeButton, index, position[0], position[1]);

            LangF(playerid, dialog, sizeof dialog, E_LANG_MOV_EDIT_BODY, position[0], position[1]);

            Dialog_Show(playerid, D_MOVIMENT_EDIT, DIALOG_STYLE_INPUT, L(playerid, E_LANG_MOV_EDIT_TITLE), dialog, L(playerid, E_LANG_BTN_CONFIRM), L(playerid, E_LANG_BTN_CANCEL));
        }

        else if(typeKey == E_TYPEKEY_COLOR || typeKey == E_TYPEKEY_COLOR_BACKGROUND || typeKey == E_TYPEKEY_COLOR_BOX) {

            new 
                dialog[164 + 1],
                colorRGBA[4],
                E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey),
                color = TaskBarTextDrawUpdate_GetColor(typeButton, index),
                currentColumn = TaskBarEventMoviment_GetColumn(playerid)
            ;

            RGB::HexToRGBA(color, colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);

            LangF(playerid, dialog, sizeof dialog, E_LANG_MOV_COLOR_BODY, colorRGBA[currentColumn]);

            Dialog_Show(playerid, D_MOVIMENT_COLOR, DIALOG_STYLE_INPUT, L(playerid, E_LANG_MOV_COLOR_TITLE), dialog, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_CANCEL));
        }

        else if(typeKey == E_TYPEKEY_MODEL_ROTATION) {

            new 
                dialog[109 * 3],
                Float:rotation[4],
                currentColumn = TaskBarEventMoviment_GetColumn(playerid)
            ;

            SessionTextDrawData_GetModelRot(index, rotation[0], rotation[1], rotation[2], rotation[3]);
            new E_LANG:axisKey = E_LANG_AXIS_X;
            axisKey = E_LANG:(_:axisKey + currentColumn);
            LangF(playerid, dialog, sizeof dialog, E_LANG_MOV_MODEL_BODY, L(playerid, axisKey), rotation[currentColumn]);

            Dialog_Show(playerid, D_MOVIMENT_MODEL_ROT, DIALOG_STYLE_INPUT, L(playerid, E_LANG_MOV_MODEL_TITLE), dialog, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_CANCEL));
        }
    }
    else
    {
        new
            index = TaskBarTextDraw_GetSelected(playerid),
            E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid)
        ;

        if((typeKey == E_TYPEKEY_SIZE || typeKey == E_TYPEKEY_POSITION || typeKey == E_TYPEKEY_LETTER_SIZE) && (updown != 0 || leftright != 0)) {

            new 
                Float:position[2],
                Float:defSpeed = TaskBarEventMoviment_GetSpeed(playerid),
                E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey)
            ;

            defSpeed = keys == KEY_SPRINT ? MAX_SPEED_HIGH : defSpeed;
            if(typeKey == E_TYPEKEY_LETTER_SIZE)
                defSpeed = defSpeed / 100;

            TaskBarTextDrawUpdate_GetPos(typeButton, index, position[0], position[1]);

            if(leftright == KEY_LEFT) position[0] -= defSpeed;
            if(leftright == KEY_RIGHT) position[0] += defSpeed;
            if(updown == KEY_UP) position[1] -= defSpeed;
            if(updown == KEY_DOWN) position[1] += defSpeed;

            TaskBarTextDrawUpdate_SetPos(typeButton, index, position[0], position[1], false);
            TaskBarMessage_Create(playerid, va_return("~y~X:~w~ %0.2f     ~y~Y:~w~ %0.2f     ~r~Speed:~w~ %0.1f", position[0], position[1], defSpeed), 4);
        }

        else if(typeKey == E_TYPEKEY_COLOR || typeKey == E_TYPEKEY_COLOR_BACKGROUND || typeKey == E_TYPEKEY_COLOR_BOX) {

            new 
                column = TaskBarEventMoviment_GetColumn(playerid),
                maxColumn = TaskBarEventMoviment_GetColumnMax(playerid),
                E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey),
                color,
                colorRGBA[4]
            ;

            color = TaskBarTextDrawUpdate_GetColor(typeButton, index);
            RGB::HexToRGBA(color, colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);

            if(updown != 0.0 || leftright != 0.0 || leftright == KEY_LEFT || leftright == KEY_RIGHT) {
                if(leftright == KEY_LEFT && !TaskBarEventMoviment_HasDelay(playerid)) column = (column - 1) < 0 ? (maxColumn - 1) : (column - 1);
                else if(leftright == KEY_RIGHT && !TaskBarEventMoviment_HasDelay(playerid)) column = (column + 1) >= maxColumn ? 0 : (column + 1);
                else if(updown == KEY_UP) colorRGBA[column] = (colorRGBA[column] + 1) > 255 ? 0 : (colorRGBA[column] + 1);
                else if(updown == KEY_DOWN) colorRGBA[column] = (colorRGBA[column] - 1) < 0 ? 255 : (colorRGBA[column] - 1);
                
                color = RGB::RGBAToHex(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
                TaskBarTextDrawUpdate_SetColor(typeButton, index, color, false);

                if(TaskBarEventMoviment_GetColumn(playerid) != column) {
                    TaskBarEventMoviment_SetDelay(playerid, 500);
                    TaskBarEventMoviment_SetColumn(playerid, column);
                }
            }

            TaskBarMessage_Create(
                playerid, 
                va_return(
                    "~%s~R:%d  ~%s~G: %d  ~%s~B: %d  ~%s~A: %d", 
                    column == 0 ? "r" : "w", colorRGBA[0], 
                    column == 1 ? "r" : "w", colorRGBA[1], 
                    column == 2 ? "r" : "w", colorRGBA[2], 
                    column == 3 ? "r" : "w", colorRGBA[3]
                ), 
                4
            );
        }

        else if((typeKey == E_TYPEKEY_GROUP_POSITION || typeKey == E_TYPEKEY_GROUP_SIZE || typeKey == E_TYPEKEY_GROUP_LETTER_SIZE) && (updown != 0 || leftright != 0)) {

            new
                Float:offset[2],
                Float:offsetSet[2],
                Float:defSpeed = TaskBarEventMoviment_GetSpeed(playerid)
            ;

            defSpeed = keys == KEY_SPRINT ? MAX_SPEED_HIGH : defSpeed;
            if(typeKey == E_TYPEKEY_GROUP_LETTER_SIZE)
                defSpeed = defSpeed / 100;

            if(leftright == KEY_LEFT) offset[0] = -defSpeed;
            if(leftright == KEY_RIGHT) offset[0] = defSpeed;
            if(updown == KEY_UP) offset[1] = -defSpeed;
            if(updown == KEY_DOWN) offset[1] = defSpeed;

            SessionEventGroupItem_SetOffset(playerid, offset[0], offset[1], false);

            TaskBarEventMoviment_GetOffset(playerid, offsetSet[0], offsetSet[1]);
            offsetSet[0] += offset[0];
            offsetSet[1] += offset[1];
            TaskBarEventMoviment_SetOffset(playerid, offsetSet[0], offsetSet[1]);
            TaskBarMessage_Create(playerid, va_return("~y~OffsetX:~w~ %0.2f     ~y~OffsetY:~w~ %0.2f     ~r~Speed:~w~ %0.1f", offsetSet[0], offsetSet[1], defSpeed), 4);
        }

        else if(typeKey == E_TYPEKEY_MODEL_ROTATION) {

            new 
                Float:rotation[4],
                Float:speed = TaskBarEventMoviment_GetSpeed(playerid),
                column = TaskBarEventMoviment_GetColumn(playerid),
                maxColumn = TaskBarEventMoviment_GetColumnMax(playerid)
            ;

            SessionTextDrawData_GetModelRot(index, rotation[0], rotation[1], rotation[2], rotation[3]);

            if(updown != 0 || leftright != 0 || leftright == KEY_LEFT || leftright == KEY_RIGHT) {

                if(updown != 0) {
                    if(updown == KEY_UP) rotation[column] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                    if(updown == KEY_DOWN) rotation[column] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);

                    SessionTextDrawData_SetModelRot(index, rotation[0], rotation[1], rotation[2], rotation[3], false);
                }

                if(leftright == KEY_LEFT && !TaskBarEventMoviment_HasDelay(playerid)) column = (column - 1) < 0 ? (maxColumn - 1) : (column - 1);
                else if(leftright == KEY_RIGHT && !TaskBarEventMoviment_HasDelay(playerid)) column = (column + 1) >= maxColumn ? 0 : (column + 1);

                if(TaskBarEventMoviment_GetColumn(playerid) != column) {
                    TaskBarEventMoviment_SetDelay(playerid, 500);
                    TaskBarEventMoviment_SetColumn(playerid, column);
                }
            }

            TaskBarMessage_Create(
                playerid, 
                va_return(
                    "~%s~X:%0.2f  ~%s~Y: %0.2f  ~%s~Z: %0.2f  ~%s~Zoom: %0.2f  ~w~- Speed: ~r~%0.1f", 
                    column == 0 ? "y" : "w", rotation[0], 
                    column == 1 ? "y" : "w", rotation[1], 
                    column == 2 ? "y" : "w", rotation[2], 
                    column == 3 ? "y" : "w", rotation[3],
                    keys == KEY_SPRINT ? MAX_SPEED_HIGH : speed
                ), 
                4
            );
        }

        else if(typeKey == E_TYPEKEY_TASKBAR && updown != 0) {

            new offset = TaskBarEventSettings_GetY(playerid);
            
            if(updown == KEY_UP) offset += (keys == KEY_SPRINT) ? (10) : (1);
            else if(updown == KEY_DOWN) offset -= (keys == KEY_SPRINT) ? (10) : (1);

            TaskBarEventSettings_SetY(playerid, offset);
            TaskBarMessage_Create(playerid, va_return("Offset: ~g~%d", TaskBarEventSettings_GetY(playerid)), 4);
        }

        else if((typeKey == E_TYPEKEY_GROUP_LOCAL_POSITION || typeKey == E_TYPEKEY_GROUP_LOCAL_SIZE || typeKey == E_TYPEKEY_GROUP_LOCAL_LETTER_SIZE) && (updown != 0 || leftright != 0)) {

            new
                Float:offset[2],
                Float:offsetSet[2],
                Float:defSpeed = TaskBarEventMoviment_GetSpeed(playerid)
            ;

            defSpeed = keys == KEY_SPRINT ? MAX_SPEED_HIGH : defSpeed;
            if(typeKey == E_TYPEKEY_GROUP_LOCAL_LETTER_SIZE)
                defSpeed = defSpeed / 100;

            if(leftright == KEY_LEFT) offset[0] = -defSpeed;
            if(leftright == KEY_RIGHT) offset[0] = defSpeed;
            if(updown == KEY_UP) offset[1] = -defSpeed;
            if(updown == KEY_DOWN) offset[1] = defSpeed;

            if(typeKey == E_TYPEKEY_GROUP_LOCAL_POSITION)
                SessionPlayerData_SetPosition(playerid, offset[0], offset[1], false);
            else if(typeKey == E_TYPEKEY_GROUP_LOCAL_SIZE)
                SessionPlayerData_SetSize(playerid, offset[0], offset[1], false);
            else if(typeKey == E_TYPEKEY_GROUP_LOCAL_LETTER_SIZE)
                SessionPlayerData_SetLetterSize(playerid, offset[0], offset[1], false);

            TaskBarEventMoviment_GetOffset(playerid, offsetSet[0], offsetSet[1]);
            offsetSet[0] += offset[0];
            offsetSet[1] += offset[1];
            TaskBarEventMoviment_SetOffset(playerid, offsetSet[0], offsetSet[1]);
            TaskBarMessage_Create(playerid, va_return("~y~OffsetX:~w~ %0.2f     ~y~OffsetY:~w~ %0.2f     ~r~Speed:~w~ %0.1f", offsetSet[0], offsetSet[1], defSpeed), 4);
        }

        else if(typeKey == E_TYPEKEY_MOVE_INDEX) {

            new 
                maxIndex = SessionPlayer_GetMaxIndex(playerid),
                nextIndex = SessionPlayer_GetNextIndex(playerid),
                currentIndex = SessionPlayer_GetIndex(playerid)
            ;

            if(leftright != 0 && !TaskBarEventMoviment_HasDelay(playerid)) {
                
                if(leftright == KEY_RIGHT)
                    nextIndex++;
                else if(leftright == KEY_LEFT)
                    nextIndex--;

                if(nextIndex > maxIndex) nextIndex = maxIndex - 1;
                if(nextIndex < 0) nextIndex = 0;

                SessionTextDrawData_SetIndex(currentIndex, nextIndex);
                TaskBarTextDraw_Select(playerid, nextIndex);
                SessionPlayer_MoveIndexInit(playerid, nextIndex);
                TaskBarEventMoviment_SetDelay(playerid, 500);
            }

            TaskBarMessage_Create(playerid, va_return("Index: ~y~%d/%d", nextIndex, maxIndex), 4);
        }

        else if(typeKey == E_TYPEKEY_SELECT_INDEX && (leftright != 0) && !TaskBarEventMoviment_HasDelay(playerid)) {

            new 
                currentIndex = TaskBarTextDraw_GetSelected(playerid),
                nextIndex
            ;

            if(leftright == KEY_LEFT) nextIndex = SessionTextDraw_GetPrevious(currentIndex);
            else if(leftright == KEY_RIGHT) nextIndex = SessionTextDraw_GetNext(currentIndex);

            if(nextIndex == SessionTextDraw_GetMax() || nextIndex == ITER_NONE)
                return;
            
            TaskBarTextDraw_Select(playerid, nextIndex);
            TaskBarMessage_Create(playerid, va_return("Index: ~y~%d/%d", nextIndex, SessionTextDraw_GetCount() - 1), 4);

            TaskBarEventMoviment_SetDelay(playerid, 500);
        }
    }
}



/*

                .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                    `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarEventMoviment_Init(playerid) {

    new E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid);

    TaskBarEventMoviment_KillTimer(playerid);
    TaskBarEventMoviment_SetColumn(playerid, 0);                                        // Default
    TaskBarEventMoviment_SetColumnMax(playerid, 0);                                     // Default
    TaskBarEventMoviment_SetOffset(playerid, 0.0, 0.0);                                 // Default

    if(typeKey != E_TYPEKEY_TASKBAR) {
        TaskBarButton_HideAll(playerid);
        TaskBarEventMoviment_Tips(playerid, TaskBarEventMoviment_GetTips(playerid));    // Set Tips
    }

    if(typeKey == E_TYPEKEY_COLOR 
        || typeKey == E_TYPEKEY_COLOR_BACKGROUND 
        || typeKey == E_TYPEKEY_COLOR_BOX 
        || typeKey == E_TYPEKEY_MODEL_ROTATION) TaskBarEventMoviment_SetColumnMax(playerid, 4);

    e_Data[playerid][E_DATA_TIMER_KEY] = SetTimerEx("OnTaskBarMovimentUpdate", 50, true, "i", playerid);
}

stock TaskBarEventMoviment_Unload(playerid) {

    TaskBarButton_ShowAll(playerid);
    TaskBarEventMoviment_KillTimer(playerid);
    TaskBarMessage_Destroy(playerid);
    TaskBarEventMoviment_Tips(playerid, false);
}

stock TaskBarEventMoviment_Close(playerid) {
    
    new 
        index = TaskBarTextDraw_GetSelected(playerid),
        E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid),
        E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey)
    ;

    switch(typeKey) 
    {
        case E_TYPEKEY_SIZE, E_TYPEKEY_POSITION, E_TYPEKEY_LETTER_SIZE: {
            if(index != -1) {
                new Float:position[2];
                TaskBarTextDrawUpdate_GetPos(typeButton, index, position[0], position[1]);
                TaskBarTextDrawUpdate_SetPos(typeButton, index, position[0], position[1]);
            }
        }

        case E_TYPEKEY_MODEL_ROTATION: {
            if(index != -1) {
                new Float:rotation[4];
                SessionTextDrawData_GetModelRot(index, rotation[0], rotation[1], rotation[2], rotation[3]);
                SessionTextDrawData_SetModelRot(index, rotation[0], rotation[1], rotation[2], rotation[3]);
            }
        }

        case E_TYPEKEY_GROUP_POSITION, E_TYPEKEY_GROUP_SIZE, E_TYPEKEY_GROUP_LETTER_SIZE: {
            SessionEventGroupItem_SetOffset(playerid, 0.0, 0.0, true, true);
        }

        case E_TYPEKEY_COLOR, E_TYPEKEY_COLOR_BACKGROUND, E_TYPEKEY_COLOR_BOX: {
            if(index != -1)
                TaskBarTextDrawUpdate_SetColor(typeButton, index, TaskBarTextDrawUpdate_GetColor(typeButton, index));
        }

        case E_TYPEKEY_GROUP_LOCAL_POSITION: {
            SessionPlayerData_SetPosition(playerid, 0.0, 0.0, true, true);
        }

        case E_TYPEKEY_GROUP_LOCAL_SIZE: {
            SessionPlayerData_SetSize(playerid, 0.0, 0.0, true, true);
        }

        case E_TYPEKEY_GROUP_LOCAL_LETTER_SIZE: {
            SessionPlayerData_SetLetterSize(playerid, 0.0, 0.0, true, true);
        }

        case E_TYPEKEY_MOVE_INDEX: {
            SessionPlayer_MoveIndex(playerid);
        }
    }
}

static stock TaskBarEventMoviment_KillTimer(playerid) {

    if(e_Data[playerid][E_DATA_TIMER_KEY])
        KillTimer(e_Data[playerid][E_DATA_TIMER_KEY]);
    
    e_Data[playerid][E_DATA_TIMER_KEY] = 0;
}

static stock TaskBarEventMoviment_Tips(playerid, bool:status) {

    if(status) 
        TaskBarView_ShowTips(playerid);
    else 
        TaskBarView_HideTips(playerid);
}

static stock TaskBarEventMoviment_SetTips(playerid, bool:status, bool:showNow = true) {

    if(showNow)
        TaskBarEventMoviment_Tips(playerid, status);

    e_Data[playerid][E_DATA_SHOW_TIPS] = status;
}

static stock TaskBarEventMoviment_SetOffset(playerid, Float:x, Float:y) {
    e_Data[playerid][E_DATA_OFFSET][0] = x;
    e_Data[playerid][E_DATA_OFFSET][1] = y;
}

static stock TaskBarEventMoviment_SetColumn(playerid, value)
    e_Data[playerid][E_DATA_COLUMN] = value;

static stock TaskBarEventMoviment_SetColumnMax(playerid, value)
    e_Data[playerid][E_DATA_COLUMN_MAX] = value;

static stock TaskBarEventMoviment_GetColumn(playerid)
    return e_Data[playerid][E_DATA_COLUMN];

static stock TaskBarEventMoviment_GetColumnMax(playerid)
    return e_Data[playerid][E_DATA_COLUMN_MAX];

static stock bool:TaskBarEventMoviment_GetTips(playerid)
    return e_Data[playerid][E_DATA_SHOW_TIPS];

static stock TaskBarEventMoviment_SetSpeed(playerid, Float:speed)
    e_Data[playerid][E_DATA_SPEED] = speed;

static stock Float:TaskBarEventMoviment_GetSpeed(playerid)
    return e_Data[playerid][E_DATA_SPEED];

static stock bool:TaskBarEventMoviment_HasDelay(playerid)
    return e_Data[playerid][E_DATA_DELAY] >= GetTickCount();

static stock TaskBarEventMoviment_SetDelay(playerid, seconds)
    e_Data[playerid][E_DATA_DELAY] = (GetTickCount() + seconds);

static stock TaskBarEventMoviment_GetOffset(playerid, &Float:x, &Float:y) {
    x = e_Data[playerid][E_DATA_OFFSET][0];
    y = e_Data[playerid][E_DATA_OFFSET][1];
}

static stock TaskBarEventMoviment_Reset(playerid) {

    TaskBarMessage_Destroy(playerid);
    TaskBarEventMoviment_KillTimer(playerid);

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_MOVIMENT_EDIT(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new Float:position[2];

        if(sscanf(inputtext, "ff", position[0], position[1])) 
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS_EX));

        new 
            Float:positionItem[2],
            E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid),
            E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey),
            index = TaskBarTextDraw_GetSelected(playerid)
        ;

        TaskBarTextDrawUpdate_GetPos(typeButton, index, positionItem[0], positionItem[1]);

        if(position[0] != 0.0 || position[1] != 0.0) {
            if(position[0] == 0.0) position[0] = positionItem[0];
            if(position[1] == 0.0) position[1] = positionItem[1];
        }

        TaskBarTextDrawUpdate_SetPos(typeButton, index, position[0], position[1]);
    }
    return true;
}

Dialog:D_MOVIMENT_SPEED(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new Float:speed;

        if(sscanf(inputtext, "f", speed)) 
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));

        TaskBarEventMoviment_SetSpeed(playerid, speed);
        TaskBarMessage_Create(playerid, va_return("~r~New Speed:~w~ %0.1f", speed), 2);
    }
    return true;
}

Dialog:D_MOVIMENT_COLOR(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new newColor;
        
        if(sscanf(inputtext, "i", newColor))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_NUMBERS));

        if(newColor < 0 || newColor > 255)
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_COLOR_RANGE));

        new 
            E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid),
            E_TYPETASKBUTTON:typeButton = TaskBarTextDrawUpdate_GetButtonByKey(typeKey),
            index = TaskBarTextDraw_GetSelected(playerid),
            color = TaskBarTextDrawUpdate_GetColor(typeButton, index),
            currentColumn = TaskBarEventMoviment_GetColumn(playerid),
            colorRGBA[4]
        ;

        RGB::HexToRGBA(color, colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);

        colorRGBA[currentColumn] = newColor;
        color = RGB::RGBAToHex(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);

        TaskBarTextDrawUpdate_SetColor(typeButton, index, color);
    }
    return true;
}

Dialog:D_MOVIMENT_MODEL_ROT(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new Float:rotation;
        if(sscanf(inputtext, "f", rotation))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_FLOATS));

        new 
            index = TaskBarTextDraw_GetSelected(playerid),
            currentColumn = TaskBarEventMoviment_GetColumn(playerid),
            Float:currentRotation[4]
        ;

        SessionTextDrawData_GetModelRot(index, currentRotation[0], currentRotation[1], currentRotation[2], currentRotation[3]);
        currentRotation[currentColumn] = rotation;

        SessionTextDrawData_SetModelRot(index, currentRotation[0], currentRotation[1], currentRotation[2], currentRotation[3], false);
    }
    return true;
}