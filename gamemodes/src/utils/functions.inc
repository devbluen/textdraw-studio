


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
    
    if(!sscanf(input, "'rgba'p<, ()>dddd", r, g, b, a)) return RGB::RGBAToHex(r, g, b, a);                         // Format: rgba(r,g,b,a)
    else if(!sscanf(input, "'rgb'p<, ()>ddd", r, g, b)) return RGB::RGBAToHex(r, g, b, a);                         // Format: rgb(r,g,b)
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