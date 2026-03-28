


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

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
    return e_SessionDraw[index][E_SESSIONDRAW_];

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