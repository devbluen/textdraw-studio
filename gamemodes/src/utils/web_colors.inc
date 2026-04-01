
            // Definers
#define WebColor:%0(%1) \
    forward wcb_%0(%1); \
    public wcb_%0(%1)

enum E_WEBCOLORS {
    E_WEBCOLORS_COLOR,
    E_WEBCOLORS_NAME[32 + 1],
    bool:E_WEBCOLORS_BLOCK_PREVIEW
};

new const 
    e_WebColors[][E_WEBCOLORS] = {
        {RGB::RGBAToHex(255, 255, 255, 0), "Transparent", true},
        {0xFFFFFFFF, "White", true},
        {0x000000FF, "Black", true},

        {0x212121FF, "Deep Graphite"},    // [0] Backgrounds
        {0x424242FF, "Medium Grey"},      // [1] Borders
        {0x9E9E9EFF, "Silver"},           // [2] Disabled elements
        {0xE0E0E0FF, "Ice White"},        // [3] Primary Text
        {0xF5F5F5FF, "Soft White"},       // [4] High Contrast Text

        {0x0D47A1FF, "Navy Blue"},        // [5] Professional
        {0x1976D2FF, "Ocean Blue"},       // [6] Information
        {0x2196F3FF, "Dodger Blue"},      // [7] Primary Buttons
        {0x03A9F4FF, "Sky Blue"},         // [8] Links/Tags
        {0x00BCD4FF, "Cyan Aqua"},        // [9] Fresh Water
        {0x00E5FFFF, "Electric Cyan"},    // [10] Neon Tech
        {0xB2EBF2FF, "Pale Blue"},        // [11] Soft UI

        {0x1B5E20FF, "Forest Green"},     // [12] Dark Mode Success
        {0x4CAF50FF, "Success Green"},    // [13] Confirmations
        {0x8BC34AFF, "Lime Green"},       // [14] Vibrant/Modern
        {0x00C853FF, "Hyper Green"},      // [15] Strong Positive
        {0xA5D6A7FF, "Mint Pastel"},      // [16] Fresh Mint
        {0x26A69AFF, "Teal Green"},       // [17] Modern Corporate

        {0xFFEB3BFF, "Canary Yellow"},    // [18] Attention
        {0xFFC107FF, "Amber Gold"},       // [19] Warning/VIP
        {0xFF9800FF, "Vibrant Orange"},   // [20] High Alert
        {0xFF5722FF, "Deep Orange"},      // [21] Hot/Danger
        {0xFFF59DFF, "Lemon Silk"},       // [22] Soft Warning

        {0xB71C1CFF, "Blood Red"},        // [23] Damage/Health
        {0xF44336FF, "Error Red"},        // [24] Deletions/Danger
        {0xE91E63FF, "Paradise Pink"},    // [25] Creative/Unique
        {0xFF4081FF, "Neon Pink"},        // [26] Trendy/Club
        {0x880E4FFF, "Dark Wine"},        // [27] Classy Red

        {0x4A148CFF, "Royal Purple"},     // [28] Special Status
        {0x9C27B0FF, "Amethyst Purple"},  // [29] Magic/Rare
        {0x673AB7FF, "Deep Indigo"},      // [30] Branding
        {0xD1C4E9FF, "Lavender Mist"},    // [31] Soft Magic
        {0x311B92FF, "Midnight Violet"},  // [32] Deep Tech

        {0x1DE9B6FF, "Turquoise Neon"},   // [33] Ultra Fresh
        {0xC6FF00FF, "Toxic Lime"},       // [34] Vibrant Strong
        {0xFFAB40FF, "Mango Sorbet"},     // [35] Fresh Orange
        {0x2979FFFF, "Ultramarine"},      // [36] Strong Digital Blue
        {0x76FF03FF, "Bright Poison"},    // [37] Neon Health
        {0x006064FF, "Deep Petrol"},      // [38] Elegant Dark Blue
        {0xCFD8DCFF, "Blue Grey"}        // [39] Clean Metal
    }
;

static 
    bool:e_WithChoose[MAX_PLAYERS],
    e_Callback[MAX_PLAYERS][30 + 1]
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

stock Util_WebColorCreate(playerid, const callback[], bool:with_arrows = true) {

    strcopy(e_Callback[playerid], callback);
    e_WithChoose[playerid] = with_arrows;

    Util_WebColorShow(playerid);
}

static stock Util_WebColorShow(playerid) {

    inline WebColorsInternal() {

        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, "Choose Color", -2);

        if(e_WithChoose[playerid])
            DialogMod_Add(playerid, "Edit Manual Color", -3);

        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, DIALOG_LINE);
        DialogMod_Add(playerid, " ");

        for(new i = 0; i < sizeof e_WebColors; i++)
            DialogMod_Add(playerid, "{%06x}%d. %s", i, (e_WebColors[i][E_WEBCOLORS_BLOCK_PREVIEW] ? (0xFFFFFFFF) : (e_WebColors[i][E_WEBCOLORS_COLOR])) >>> 8, i + 1, e_WebColors[i][E_WEBCOLORS_NAME]);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Colors", "Select", "Close", "WEBCOLORS", using inline WebColorsInternal);
}

static stock Util_WebColorCall(playerid, color)
    CallLocalFunction(va_return("wcb_%s", e_Callback[playerid]), "ii", playerid, color);



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

DialogMod:WEBCOLORS(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case -1: Util_WebColorShow(playerid);
            case -2: 
            {
                new dialog[356 + 1];
                format(dialog, sizeof dialog, "{FFFFFF}Define the colors of your project as desired.\n \
                                                You can choose one of the formats below to select the color.\n\n \
                                                \
                                                Formats:\n \
                                                {hex}\n \
                                                - 0xFFFFFFFF\n \
                                                - #FFFFFF\n \
                                                - rgba(255, 255, 255, 255)\n \
                                                - rgb(255, 255, 255)\n \
                                                - 255, 255, 255, 255\n \
                                                - 255, 255, 255\n \
                                                - 255 255 255 255\n \
                                                - 255 255 255\n \
                                                - Numbers"
                                            );

                Dialog_Show(playerid, D_WEBCOLOR, DIALOG_STYLE_INPUT, "Colors", dialog, "Confirm", "Previous");
            }

            case -3: Util_WebColorCall(playerid, -2);
            default: Util_WebColorCall(playerid, e_WebColors[params][E_WEBCOLORS_COLOR]);
        }
        
        return true;
    }

    Util_WebColorCall(playerid, -3);
    return true;
}

Dialog:D_WEBCOLOR(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext))
        Util_WebColorCall(playerid, Util_ParseColor(inputtext));
    else
        Util_WebColorCall(playerid, -3);

    return true;
}