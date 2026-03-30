


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarTextDrawUpdate_SetPos(E_TYPETASKBUTTON:type, index, Float:x, Float:y, bool:execute_query = true) {
    switch(type) {
        case E_TYPETASKBUTTON_SIZE: SessionTextDrawData_SetSize(index, x, y, execute_query);
        case E_TYPETASKBUTTON_POSITION: SessionTextDrawData_SetPosition(index, x, y, execute_query);
        case E_TYPETASKBUTTON_LETTERSIZE: SessionTextDrawData_SetLettSize(index, x, y, execute_query);
    }
}

stock TaskBarTextDrawUpdate_SetColor(E_TYPETASKBUTTON:type, index, value, bool:execute_query = true) {
    switch(type) {
        case E_TYPETASKBUTTON_COLOR: SessionTextDrawData_SetColor(index, value, execute_query);
        case E_TYPETASKBUTTON_COLOR_BG: SessionTextDrawData_SetColorBG(index, value, execute_query);
        case E_TYPETASKBUTTON_COLOR_BOX: SessionTextDrawData_SetColorBox(index, value, execute_query);
    }
}

stock TaskBarTextDrawUpdate_GetPos(E_TYPETASKBUTTON:type, index, &Float:x, &Float:y) {
    switch(type) {
        case E_TYPETASKBUTTON_SIZE: SessionTextDrawData_GetSize(index, x, y);
        case E_TYPETASKBUTTON_POSITION: SessionTextDrawData_GetPosition(index, x, y);
        case E_TYPETASKBUTTON_LETTERSIZE: SessionTextDrawData_GetLettSize(index, x, y);
    }
}

stock TaskBarTextDrawUpdate_GetColor(E_TYPETASKBUTTON:type, index) {
    switch(type) {
        case E_TYPETASKBUTTON_COLOR: return SessionTextDrawData_GetColor(index);
        case E_TYPETASKBUTTON_COLOR_BG: return SessionTextDrawData_GetColorBG(index);
        case E_TYPETASKBUTTON_COLOR_BOX: return SessionTextDrawData_GetColorBox(index);
    }
    return -1;
}

stock E_TYPETASKBUTTON:TaskBarTextDrawUpdate_GetButtonByKey(E_TYPEKEY:key)
    return TaskBarTypeKey_GetButton(key);

stock E_TYPEKEY:TaskBarTextDrawUpdate_GetKeyByButton(E_TYPETASKBUTTON:button)
    return TaskBarTypeKey_GetKey(button);