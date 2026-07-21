


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Util_ClearChat(playerid, lines = 50) {
    for(new i = 0; i < lines; i++)
        SendClientMessage(playerid, -1, " "); 
}

stock Util_GetPages(count, maxPerPage)
    return ((count / maxPerPage) + (count % maxPerPage > 0 ? (1) : (0)));

stock Util_ParseColor(const input[]) { 

    new 
        r, 
        g, 
        b, 
        a = 255, 
        hex
    ;
    
    if(!sscanf(input, "'rgba'P<, ()>dddD(255)", r, g, b, a)) return RGB::RGBAToHex(r, g, b, a);                     // Format: rgba(r,g,b,a)
    else if(!sscanf(input, "'rgb'P<, ()>ddd", r, g, b)) return RGB::RGBAToHex(r, g, b, a);                          // Format: rgb(r,g,b)
    else if(!sscanf(input, "'#'x", hex) || !sscanf(input, "'0x'x", hex) || !sscanf(input, "'{'x'}'", hex)) {        // Format: 0xFFFFFFFF or #FFFFFF or {FFFFFF}
        if (hex >= 0 && hex <= 0xFFFFFF)
            return (hex << 8 | 0xFF);

        return hex;
    }
    else if(!sscanf(input, "p<,>dddD(255)", r, g, b, a)) return RGB::RGBAToHex(r, g, b, a);                         // Format: [r,g,b,a] or [r g b]
    else if(!sscanf(input, "dddD(255)", r, g, b, a)) return RGB::RGBAToHex(r, g, b, a);                             // Format: [r g b a] or [r g b]
    else if(!sscanf(input, "d", hex)) return hex;
    return 0xFFFFFFFF;
}

stock Util_CutString(dest[], maxlength, maxSize = sizeof dest) {

    if(strlen(dest) > maxlength) {
        dest[maxlength - 3] = '\0';
        strcat(dest, "...", maxSize);
    }
}

stock Util_GetForwardAngle(&Float:x, &Float:y, Float:angle, Float:distance) {
    x += (distance * floatsin(-angle, degrees));
    y += (distance * floatcos(-angle, degrees));
}

stock Util_ConverterTextdrawText(string[]) {

    new len = strlen(string);
    if(!len)
        return;

    for(new i; i < len; i++) {
        if(string[i] < 0x80) 
            continue;

        switch(string[i]) {
            case 0xC0 .. 0xC3: string[i] -= 0x40;
            case 0xC7 .. 0xC9: string[i] -= 0x42;
            case 0xD2 .. 0xD5: string[i] -= 0x44;
            case 0xD9 .. 0xDC: string[i] -= 0x47;
            case 0xE0 .. 0xE3: string[i] -= 0x49;
            case 0xE7 .. 0xEF: string[i] -= 0x4B;
            case 0xF2 .. 0xF5: string[i] -= 0x4D;
            case 0xF9 .. 0xFC: string[i] -= 0x50;
            case 0xC4, 0xE4:   string[i] = 0x83;
            case 0xC6, 0xE6:   string[i] = 0x84;
            case 0xD6, 0xF6:   string[i] = 0x91;
            case 0xD1, 0xF1:   string[i] = 0xEC;
            case 0xDF:         string[i] = 0x96;
            case 0xBF:         string[i] = 0xAF;
        }
    }

    if(len > 0 && string[len - 1] == ' ') 
        string[len - 1] = '\0';
}

stock Util_DeleteCharacters(dest[], amount, bool:start = false) {
    if(!start)
        strdel(dest, strlen(dest) - amount, strlen(dest));
    else
        strdel(dest, 0, amount);
}