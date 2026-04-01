
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_MODELS)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEventModels_Show(playerid);
    return Y_HOOKS_BREAK_RETURN_1;
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

static stock TaskBarEventModels_Show(playerid) {

    new 
        index = TaskBarTextDraw_GetSelected(playerid),
        modelId,
        colors[2],
        Float:rotation[4]
    ;

    modelId = SessionTextDrawData_GetModel(index);
    SessionTextDrawData_GetModelCol(index, colors[0], colors[1]);
    SessionTextDrawData_GetModelRot(index, rotation[0], rotation[1], rotation[2], rotation[3]);

    inline TaskBarEventModelOption() {

        DialogMod_Add(playerid, "Model: {"#HEX_DEFAULT"}%d", 0, modelId);

        if(modelId >= 400 && modelId <= 611) {
            DialogMod_Add(playerid, "Color 1: {"#HEX_DEFAULT"}%d", 1, colors[0]);
            DialogMod_Add(playerid, "Color 2: {"#HEX_DEFAULT"}%d", 2, colors[1]);
        }

        DialogMod_Add(playerid, "Rotation: {CCCCCC}X: %0.2f  Y: %0.2f  Z: %0.2f  Zoom: %0.2f", 3, rotation[0], rotation[1], rotation[2], rotation[3]);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Models", "Select", "Cancel", "D_ITEM_MODEL", using inline TaskBarEventModelOption);
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

Dialog:D_ITEMMODEL_OBJ(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new value;
        if(sscanf(inputtext, "d", value) || value < 0)
            return Dialog_ReShow(playerid, "Invalid value");
            
        new index = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDrawData_SetModel(index, value);
    }

    TaskBarEventModels_Show(playerid);
    return true;
}

Dialog:D_ITEMMODEL_COLOR1(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new value;
        if(sscanf(inputtext, "d", value) || value < 0)
            return Dialog_ReShow(playerid, "Invalid value");
        
        new 
            index = TaskBarTextDraw_GetSelected(playerid), 
            colors[2]
        ;

        SessionTextDrawData_GetModelCol(index, colors[0], colors[1]);
        colors[0] = value;

        SessionTextDrawData_SetModelCol(index, colors[0], colors[1]);
    }

    TaskBarEventModels_Show(playerid);
    return true;
}

Dialog:D_ITEMMODEL_COLOR2(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new value;
        if(sscanf(inputtext, "d", value) || value < 0)
            return Dialog_ReShow(playerid, "Invalid value");
        
        new 
            index = TaskBarTextDraw_GetSelected(playerid), 
            colors[2]
        ;

        SessionTextDrawData_GetModelCol(index, colors[0], colors[1]);
        colors[1] = value;
        
        SessionTextDrawData_SetModelCol(index, colors[0], colors[1]);
    }

    TaskBarEventModels_Show(playerid);
    return true;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  
                                                                                                            
                                                    .o8                                                   
                                                    "888                                                   
                    ooo. .oo.  .oo.    .ooooo.   .oooo888                                                   
                    `888P"Y88bP"Y88b  d88' `88b d88' `888                                                   
                    888   888   888  888   888 888   888                                                   
                    888   888   888  888   888 888   888                                                   
                    o888o o888o o888o `Y8bod8P' `Y8bod88P"                                                  

*/

DialogMod:D_ITEM_MODEL(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case 0: Dialog_Show(playerid, D_ITEMMODEL_OBJ, DIALOG_STYLE_INPUT, "ModelId", "Which model do you want to change to?", "Change", "Previous");
            case 1: Dialog_Show(playerid, D_ITEMMODEL_COLOR1, DIALOG_STYLE_INPUT, "Color", "Enter the vehicle's primary color below to change it.", "Change", "Previous");
            case 2: Dialog_Show(playerid, D_ITEMMODEL_COLOR2, DIALOG_STYLE_INPUT, "Color", "Enter the vehicle's secondary color below to change it.", "Change", "Previous");
            case 3: TaskBarKey_Set(playerid, E_TYPEKEY_MODEL_ROTATION);
        }
    }
    return true;
}