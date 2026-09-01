
            // Includes
#include <YSI_Coding\y_hooks>

hook OnUserLogin(playerid) {
    TaskBarEventUpdate_Buttons(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerTaskBarDrawSelected(playerid) {
    TaskBarEventUpdate_Buttons(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerTaskBarDrawUnSelected(playerid) {
    TaskBarEventUpdate_Buttons(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
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

stock TaskBarEventUpdate_Buttons(playerid) {

    new index = TaskBarTextDraw_GetSelected(playerid);
    
    TaskBarButton_DisableAll(playerid);                         // disable all buttons
    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_PROJECT);   // aways enabled
    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_CONFIG);    // aways enabled

    switch(Session_Has())
    {
        case true:
        {
            
            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_GROUP);
            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_ITENS);
            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_CREATE);

            switch(TaskBarTextDraw_Selected(playerid))
            {
                case true:
                {
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_COPY);
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_DELETE);
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_MODE);
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_SIZE);
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_COLOR);
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_SELECTABLE);
                    // TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_ROLLBACK);
                    TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_POSITION);

                    switch(SessionTextDrawData_GetFont(index)) 
                    {
                        case E_TYPEFONT_SPRITE: 
                        {
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_TEXT);
                        }
                        case E_TYPEFONT_MODEL: 
                        {
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_COLOR_BG);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_MODELS);
                        }
                        default: 
                        {
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_TEXT);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_LETTERSIZE);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_FONT);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_ALIGN);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_PROPORTION);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_OUTLINE);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_SHADOW);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_COLOR_BG);
                            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_BOX);
                        }
                    }
                }
            }
        }

        case false:
        {
            SessionPlayer_ResetLocalGroup(playerid);
        }
    }

    TaskBarEventUpdate_Sprite(playerid, index);
}

stock TaskBarEventUpdate_Sprite(playerid, index) {

    if(index >= 0 && (SessionTextDrawData_GetFont(index) >= E_TYPEFONT_0 && SessionTextDrawData_GetFont(index) <= E_TYPEFONT_3)) {
        if(SessionTextDrawData_GetBox(index))
            TaskBarButton_Enable(playerid, E_TYPETASKBUTTON_COLOR_BOX);
        else
            TaskBarButton_Disable(playerid, E_TYPETASKBUTTON_COLOR_BOX);
    }

    TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON_BOX, 
        index >= 0 && SessionTextDrawData_GetBox(index) ? "boxChecked" : "boxUnchecked"
    );

    TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON_ALIGN, 
        TaskBarTypeAlign_GetSprite(
            index >= 0 && SessionTextDrawData_GetAlign(index) != E_TYPEALIGNMENT_INVALID ? SessionTextDrawData_GetAlign(index) : E_TYPEALIGNMENT_LEFT
        )
    );

    TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON_FONT, 
        TaskBarTypeFont_GetSprite(
            index >= 0 ? SessionTextDrawData_GetFont(index) : E_TYPEFONT_0
        )
    );

    TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON_PROPORTION, 
        index >= 0 && SessionTextDrawData_GetPropor(index) ? "proportionChecked" : "proportionUnchecked"
    );

    TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON_MODE, 
        TaskBarTypeMode_GetSprite(
            index >= 0 ? SessionTextDrawData_GetMode(index) : E_TYPEMODE_PLAYER
        )
    );

    TaskBarButton_SetImage(playerid, E_TYPETASKBUTTON_SELECTABLE, 
        index >= 0 && SessionTextDrawData_GetSelect(index) ? "selectable" : "selectableUnabled"
    );
}