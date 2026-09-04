
            // Definers
#define     MAX_WEBCOLORS_PAGES     15

            // Macros
#define WebColor:%0(%1) \
    forward wcb_%0(%1); \
    public wcb_%0(%1)

static enum {
    E_INTERACTION_CHOOSE = -999,
    E_INTERACTION_SAVED,
    E_INTERACTION_MANUAL,
    E_INTERACTION_PREVIOUS,
    E_INTERACTION_NEXT,
    E_INTERACTION_SAVE,
    E_INTERACTION_REMOVE,
    E_INTERACTION_ADD,
    E_INTERACTION_COPY
};

static enum E_WEBCOLORS {
    E_WEBCOLORS_COLOR,
    E_WEBCOLORS_NAME[32],
    bool:E_WEBCOLORS_BLOCK_PREVIEW
};

static enum E_WEBCOLORSPLAYER {
    E_WEBCOLORSPLAYER_PAGE,
    E_WEBCOLORSPLAYER_PAGES,
    E_WEBCOLORSPLAYER_COLOR,
    bool:E_WEBCOLORSPLAYER_WITHCOLOR,
    E_WEBCOLORSPLAYER_CALLBACK[32]
};

static 
    e_WebColorsPlayer[MAX_PLAYERS][E_WEBCOLORSPLAYER]
;

static const 
    e_WebColors[][E_WEBCOLORS] = {
        {RGB::RGBAToHex(255, 255, 255, 0), "Transparent", true},
        {0xFFFFFFFF, "White", true},
        {0x000000FF, "Black"},

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

    e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_WITHCOLOR] = with_arrows;
    strcopy(e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_CALLBACK], callback);

    Util_WebColorShow(playerid);
}

static stock Util_WebColorShow(playerid) {

    inline WebColorsInternal() {

        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, L(playerid, E_LANG_COL_CHOOSE), E_INTERACTION_CHOOSE);
        DialogMod_Add(playerid, L(playerid, E_LANG_COL_SAVED), E_INTERACTION_SAVED);
        DialogMod_Add(playerid, L(playerid, E_LANG_COL_COPY), E_INTERACTION_COPY);

        if(e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_WITHCOLOR])
            DialogMod_Add(playerid, L(playerid, E_LANG_COL_MANUAL), E_INTERACTION_MANUAL);

        DialogMod_Add(playerid, " ");
        DialogMod_Add(playerid, DIALOG_LINE);
        DialogMod_Add(playerid, " ");

        for(new i = 0; i < sizeof e_WebColors; i++)
            DialogMod_Add(playerid, "{%06x}%d. %s", i, (e_WebColors[i][E_WEBCOLORS_BLOCK_PREVIEW] ? (0xFFFFFFFF) : (e_WebColors[i][E_WEBCOLORS_COLOR])) >>> 8, i + 1, e_WebColors[i][E_WEBCOLORS_NAME]);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_COLORS), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CLOSE), "D_WEBCOLORS", using inline WebColorsInternal);
}

static stock Util_WebColorSetPage(playerid, page)
    e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_PAGE] = page;

static stock Util_WebColorGetPage(playerid)
    return e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_PAGE];

static stock Util_WebColorSetPages(playerid, page)
    e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_PAGES] = page;

static stock Util_WebColorGetPages(playerid)
    return e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_PAGES];

static stock Util_WebColorFavorites(playerid) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT COUNT(*) AS count FROM colors");
    if(cache)
    {
        Util_WebColorSetPages(playerid, Util_GetPages(DB_GetFieldIntByName(cache, "count"), MAX_WEBCOLORS_PAGES));
        Util_WebColorPage(playerid, 0);

        DB_FreeResultSet(cache);
    }
}

static stock Util_WebColorSamePage(playerid)
    Util_WebColorPage(playerid, Util_WebColorGetPage(playerid));

static stock Util_SetWebColor(playerid, color)
    e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_COLOR] = color;

static stock Util_GetWebColor(playerid)
    return e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_COLOR];

static stock Util_WebColorPage(playerid, page) {

    new pages = Util_WebColorGetPages(playerid);

    if(page >= pages) page = pages - 1; 
    if(page < 0) pages = 0;

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            name, \
                                                            color \
                                                        FROM colors \
                                                        LIMIT %i OFFSET %i",

                                                        MAX_WEBCOLORS_PAGES,
                                                        page * MAX_WEBCOLORS_PAGES
                                                    );

    if(cache)
    {
        inline WebColorFavorites() {

            new
                name[30 + 1],
                color
            ;

            if(pages > 1 && page < (pages - 1)) DialogMod_Add(playerid, ">>", E_INTERACTION_NEXT);
            if(page) DialogMod_Add(playerid, "<<", E_INTERACTION_PREVIOUS);
            DialogMod_Add(playerid, L(playerid, E_LANG_COL_SAVE), E_INTERACTION_SAVE);

            do
            {
                color = DB_GetFieldIntByName(cache, "color");
                DB_GetFieldStringByName(cache, "name", name);

                DialogMod_Add(playerid, "%s%s", color, RGB::GetColorRGBA(color), name);
            }
            while(DB_SelectNextRow(cache));
            DB_FreeResultSet(cache);
        }

        DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_COLORS), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CANCEL), "D_WEBCOLORS_FAV", using inline WebColorFavorites);
    }
}

stock Util_WebColorCall(playerid, color)
    CallLocalFunction(va_return("wcb_%s",e_WebColorsPlayer[playerid][E_WEBCOLORSPLAYER_CALLBACK]), "ii", playerid, color);

static stock Util_WebDeleteColor(playerid)
    DB_FreeResultSet(
        DB_ExecuteQuery(IDConnection, "DELETE FROM colors WHERE color = %i", Util_GetWebColor(playerid))
    );

static stock Util_WebChoose(playerid, const callback[]) {

    new dialog[356 + 1];
    format(dialog, sizeof dialog, "%s", L(playerid, E_LANG_COL_FORMATS));

    Dialog_Open(playerid, callback, DIALOG_STYLE_INPUT, L(playerid, E_LANG_COLORS), dialog, L(playerid, E_LANG_BTN_CONFIRM), L(playerid, E_LANG_BTN_PREVIOUS));
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

Dialog:D_WEBCOLOR(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext))
        Util_WebColorCall(playerid, Util_ParseColor(inputtext));
    else
        Util_WebColorSamePage(playerid);

    return true;
}

DialogMod:D_WEBCOLORS_FAV(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case E_INTERACTION_NEXT: Util_WebColorPage(playerid, Util_WebColorGetPage(playerid) + 1);
            case E_INTERACTION_PREVIOUS: Util_WebColorPage(playerid, Util_WebColorGetPage(playerid) - 1);
            case E_INTERACTION_SAVE: Util_WebChoose(playerid, "D_WEBCOLORS_FAVSEL");
            default:
            {
                Util_SetWebColor(playerid, params);
                
                inline WebColorOption() {

                    DialogMod_Add(playerid, L(playerid, E_LANG_COL_ADD), E_INTERACTION_ADD);
                    DialogMod_Add(playerid, L(playerid, E_LANG_COL_REMOVE_FAV), E_INTERACTION_REMOVE);
                }

                DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_OPTIONS), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_BACK), "D_WEBCOLORS_FAVOPTION", using inline WebColorOption);
            }
        }
    }
    return true;
}

DialogMod:D_WEBCOLORS_FAVOPTION(playerid, response, inputtext[], params) {

    if(response) {
        switch(params) {
            case E_INTERACTION_ADD: Util_WebColorCall(playerid, Util_GetWebColor(playerid));
            case E_INTERACTION_REMOVE: 
            {
                Util_WebDeleteColor(playerid);
                Util_WebColorPage(playerid, 0);
                SendLang(INVALID_PLAYER_ID, -1, E_LANG_MSG_COL_DELETED, Auth_GetName(playerid));
            }
        }
        return true;
    }
    
    Util_WebColorSamePage(playerid);
    return true;
}

DialogMod:D_WEBCOLORS(playerid, response, inputtext[], params) {

    if(response) {

        switch(params) {
            case -1: Util_WebColorShow(playerid);
            case E_INTERACTION_CHOOSE: Util_WebChoose(playerid, "D_WEBCOLOR");
            case E_INTERACTION_SAVED: Util_WebColorFavorites(playerid);
            case E_INTERACTION_MANUAL: Util_WebColorCall(playerid, -2);
            case E_INTERACTION_COPY: SessionTextDrawColor_Show(playerid);
            default: Util_WebColorCall(playerid, e_WebColors[params][E_WEBCOLORS_COLOR]);
        }
        return true;
    }

    Util_WebColorCall(playerid, -3);
    return true;
}

Dialog:D_WEBCOLORS_FAVSEL(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {
        Util_SetWebColor(playerid, Util_ParseColor(inputtext));
        Dialog_Show(playerid, D_WEBCOLORS_FAVNAME, DIALOG_STYLE_INPUT, L(playerid, E_LANG_COL_NAME_TITLE), L(playerid, E_LANG_COL_NAME_BODY), L(playerid, E_LANG_BTN_CREATE), L(playerid, E_LANG_BTN_CANCEL));
        return true;
    }

    Util_WebColorCall(playerid, -3);
    return true;
}

Dialog:D_WEBCOLORS_FAVNAME(playerid, response, listitem, inputtext[]) {

    if(response) {

        if(isnull(inputtext))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_EMPTY));

        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "INSERT INTO colors (name, color) VALUES ('%s', %i)", inputtext, Util_GetWebColor(playerid))
        );

        SendLang(INVALID_PLAYER_ID, -1, E_LANG_MSG_COL_CREATED, Auth_GetName(playerid), inputtext);
    }
    return true;
}