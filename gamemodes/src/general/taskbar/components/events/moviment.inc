
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnTaskBarMovimentUpdate(playerid);
forward OnTaskBarMovimentKillInfo(playerid);

static enum E_DATA {
    E_DATA_TIMER,
    E_DATA_TIMER_KEY,
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

    TaskBarEventMoviment_Close(playerid);
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

    if(!keys && !updown && !leftright) return;

    if(keys & KEY_SECONDARY_ATTACK) TaskBarEventMoviment_Close(playerid);
    else if(keys & KEY_YES) TaskBarEventMoviment_SetTips(playerid, !TaskBarEventMoviment_GetTips(playerid));

    else if(keys & KEY_CTRL_BACK) {

        new dialog[186 + 1];
        format(dialog, sizeof dialog, "{FFFFFF}The current speed is {f52746}%0.1f{FFFFFF}\n\n \
                                        \
                                        [!] Enter the desired new speed below.\n \
                                        Remember that you can use small values like {d4af37}0.03{FFFFFF} or {d4af37}0.3", 

                                        TaskBarEventMoviment_GetSpeed(playerid)
                                    );

        Dialog_Show(playerid, D_MOVIMENT_SPEED, DIALOG_STYLE_INPUT, "Change Speed", dialog, "Change", "Cancel");
    }
    
    else if(keys & KEY_NO) {
        
        new 
            Float:position[2],
            E_TYPEKEY:type = TaskBarKey_GetType(playerid),
            index = TaskBarTextdraw_GetSelected(playerid)
        ;

        if(type == E_TYPEKEY_SIZE) SessionTextdrawData_GetSize(index, position[0], position[1]);
        else if(type == E_TYPEKEY_POSITION) SessionTextdrawData_GetPosition(index, position[0], position[1]);
        else if(type == E_TYPEKEY_LETTER_SIZE) SessionTextdrawData_GetLettSize(index, position[0], position[1]);
        else return;

        new dialog[256 + 1];
        format(dialog, sizeof dialog, "{FFFFFF}Enter the values below to set:\n\n \
                                        X: {d4af37}%0.3f{FFFFFF}\n \
                                        Y: {d4af37}%0.3f{FFFFFF}\n\n \
                                        \
                                        For {CCCCCC}X-axis{FFFFFF} editing use\n \
                                        value {d4af37}0.0{FFFFFF}\n\n \
                                        \
                                        For {CCCCCC}Y-axis{FFFFFF} editing use\n \
                                        {d4af37}0.0{FFFFFF} value", 

                                        position[0], 
                                        position[1]
                                    );

        Dialog_Show(playerid, D_MOVIMENT_EDIT, DIALOG_STYLE_INPUT, "Edit Data", dialog, "Confirm", "Cancel");
    }

    else if(updown != 0.0 || leftright != 0.0) {
        new 
            Float:position[4],
            Float:speed = TaskBarEventMoviment_GetSpeed(playerid),
            index = TaskBarTextdraw_GetSelected(playerid)
        ;

        switch(TaskBarKey_GetType(playerid)) 
        {
            case E_TYPEKEY_SIZE: {
                SessionTextdrawData_GetSize(index, position[0], position[1]);

                if(leftright == KEY_LEFT) position[0] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                if(leftright == KEY_RIGHT) position[0] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                if(updown == KEY_UP) position[1] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                if(updown == KEY_DOWN) position[1] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);

                SessionTextdrawData_SetSize(index, position[0], position[1], false);
            }

            case E_TYPEKEY_POSITION: {
                SessionTextdrawData_GetPosition(index, position[0], position[1]);

                if(leftright == KEY_LEFT) position[0] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                if(leftright == KEY_RIGHT) position[0] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                if(updown == KEY_UP) position[1] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);
                if(updown == KEY_DOWN) position[1] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH) : (speed);

                SessionTextdrawData_SetPosition(index, position[0], position[1], false);
            }

            case E_TYPEKEY_LETTER_SIZE: {
                SessionTextdrawData_GetLettSize(index, position[0], position[1]);
                
                if(leftright == KEY_LEFT) position[0] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH / 100) : (speed / 10);
                if(leftright == KEY_RIGHT) position[0] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH / 100) : (speed / 100);
                if(updown == KEY_UP) position[1] -= (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH / 100) : (speed / 100);
                if(updown == KEY_DOWN) position[1] += (keys == KEY_SPRINT) ? (MAX_SPEED_HIGH / 100) : (speed / 100);

                SessionTextdrawData_SetLettSize(index, position[0], position[1], false);
            }

            case E_TYPEKEY_COLOR: {


            }
        }

        TaskBarEventMoviment_InfoTimer(playerid, va_return("~y~X:~w~ %0.3f     ~y~Y:~w~ %0.3f     ~r~Speed:~w~ %0.1f", position[0], position[1], keys == KEY_SPRINT ? MAX_SPEED_HIGH : speed), 4);
    }
}

public OnTaskBarMovimentKillInfo(playerid) {
    TaskBarEventMoviment_KillInfo(playerid);
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

    TaskBarEventMoviment_KillTimer(playerid);
    TaskBarEventMoviment_Tips(playerid, TaskBarEventMoviment_GetTips(playerid));

    e_Data[playerid][E_DATA_TIMER_KEY] = SetTimerEx("OnTaskBarMovimentUpdate", 50, true, "i", playerid);
}

stock TaskBarEventMoviment_Unload(playerid) {

    TaskBarEventMoviment_KillTimer(playerid);
    TaskBarEventMoviment_Tips(playerid, false);
}

stock TaskBarEventMoviment_Close(playerid, bool:reCheck = true) {
    new 
        Float:position[2],
        index = TaskBarTextdraw_GetSelected(playerid)
    ;

    if(index != -1) {
        switch(TaskBarKey_GetType(playerid)) {

            case E_TYPEKEY_SIZE: {
                SessionTextdrawData_GetSize(index, position[0], position[1]);
                SessionTextdrawData_SetSize(index, position[0], position[1]);
            }
            case E_TYPEKEY_POSITION: {
                SessionTextdrawData_GetPosition(index, position[0], position[1]);
                SessionTextdrawData_SetPosition(index, position[0], position[1]); 
            }
            case E_TYPEKEY_LETTER_SIZE: {
                SessionTextdrawData_GetLettSize(index, position[0], position[1]);
                SessionTextdrawData_SetLettSize(index, position[0], position[1]);
            }
        }
    }

    if(reCheck)
        TaskBarKey_Set(playerid, E_TYPEKEY_DISABLED);
}

static stock TaskBarEventMoviment_InfoTimer(playerid, const string[], seconds) {

    if(TaskBarEventMoviment_HasInfo(playerid))
        TaskBarEventMoviment_KillInfo(playerid, false);
    else
        TaskBarView_ShowInfo(playerid);

    TaskBarView_SetInfo(playerid, string);
    e_Data[playerid][E_DATA_TIMER] = SetTimerEx("OnTaskBarMovimentKillInfo", 1000 * seconds, false, "i", playerid);
}

static stock TaskBarEventMoviment_KillInfo(playerid, bool:hideDraw = true) {
    
    if(TaskBarEventMoviment_HasInfo(playerid)) {
        KillTimer(e_Data[playerid][E_DATA_TIMER]);
    
        if(hideDraw)
            TaskBarView_HideInfo(playerid);
    }

    e_Data[playerid][E_DATA_TIMER] = 0;
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

static stock bool:TaskBarEventMoviment_GetTips(playerid)
    return e_Data[playerid][E_DATA_SHOW_TIPS];

static stock bool:TaskBarEventMoviment_HasInfo(playerid)
    return e_Data[playerid][E_DATA_TIMER] > 0;

static stock TaskBarEventMoviment_SetSpeed(playerid, Float:speed)
    e_Data[playerid][E_DATA_SPEED] = speed;

static stock Float:TaskBarEventMoviment_GetSpeed(playerid)
    return e_Data[playerid][E_DATA_SPEED];

static stock TaskBarEventMoviment_Reset(playerid) {

    TaskBarEventMoviment_KillInfo(playerid);
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
            return Dialog_ReShow(playerid, "Only put floats (Example: 0.0 0.0)");

        new 
            Float:positionItem[2],
            E_TYPEKEY:typeKey = TaskBarKey_GetType(playerid),
            index = TaskBarTextdraw_GetSelected(playerid)
        ;

        switch(typeKey) {
            case E_TYPEKEY_SIZE: SessionTextdrawData_GetSize(index, positionItem[0], positionItem[1]);
            case E_TYPEKEY_POSITION: SessionTextdrawData_GetPosition(index, positionItem[0], positionItem[1]);
            case E_TYPEKEY_LETTER_SIZE: SessionTextdrawData_GetLettSize(index, positionItem[0], positionItem[1]);
        }

        if(position[0] != 0.0 || position[1] != 0.0) {
            if(position[0] == 0.0) position[0] = positionItem[0];
            if(position[1] == 0.0) position[1] = positionItem[1];
        }

        switch(typeKey) {
            case E_TYPEKEY_SIZE: SessionTextdrawData_SetSize(index, position[0], position[1]);
            case E_TYPEKEY_POSITION: SessionTextdrawData_SetPosition(index, position[0], position[1]);
            case E_TYPEKEY_LETTER_SIZE: SessionTextdrawData_SetLettSize(index, position[0], position[1]);
        }
    }
    return true;
}

Dialog:D_MOVIMENT_SPEED(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new Float:speed;
        if(sscanf(inputtext, "f", speed)) 
            return Dialog_ReShow(playerid, "Only put floats");

        TaskBarEventMoviment_SetSpeed(playerid, speed);
        TaskBarEventMoviment_InfoTimer(playerid, va_return("~r~New Speed:~w~ %0.1f", speed), 2);
    }
    return true;
}