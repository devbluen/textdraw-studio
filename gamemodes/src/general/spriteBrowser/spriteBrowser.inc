
            // Definers
#define     MAX_SPRITEBROWSER_PAGES     (24)

            // Views
#include "src/general/spriteBrowser/views/default.inc"

            // Components
#include "src/general/spriteBrowser/components/types.inc"

            // Includes
#include <YSI_Coding\y_hooks>

static enum {
    E_INTERACTION_CREATE,
    E_INTERACTION_ADD_FAVORITE,
    E_INTERACTION_REMOVE_FAVORITE
};

static enum E_DATA {
    bool:E_DATA_CREATED,
    E_DATA_DELAY,
    E_DATA_SIDEBAR_PAGE,
    E_DATA_IDS[MAX_SPRITEBROWSER_PAGES],
    bool:E_DATA_FAVORITE[MAX_SPRITEBROWSER_PAGES],
    E_DATA_SELECTED_INDEX,
    E_TYPESPRITE:E_DATA_SELECTED_SIDEBAR,
    E_DATA_PAGE,
    E_DATA_PAGES,
    E_DATA_FILTER_ITEM[30 + 1],
    E_DATA_FILTER[64 + 1]
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

static const
    e_Sprite[MAX_SPRITEBROWSER_PAGES][3] = {

        /*
            [0] - Background and Click
            [1] - Sprite
            [2] - Text
        */

        {50, 51, 52},
        {53, 54, 55},
        {56, 57, 58},
        {59, 60, 61},
        {62, 63, 64},
        {65, 66, 67},
        {68, 69, 70},
        {71, 72, 73},
        {74, 75, 76},
        {77, 78, 79},
        {80, 81, 82},
        {83, 84, 85},
        {86, 87, 88},
        {89, 90, 91},
        {92, 93, 94},
        {95, 96, 97},
        {98, 99, 100},
        {101, 102, 103},
        {104, 105, 106},
        {107, 108, 109},
        {110, 111, 112},
        {113, 114, 115},
        {116, 117, 118},
        {119, 120, 121}
    },

    e_SpriteSideBar[13][3] = {

        /*
            [0] - Background
            [1] - Text
            [2] - SideBar Colo (-1) (-2 actived)
        */

        {2, 3, 32},
        {4, 5, 33},
        {6, 7, 34},
        {8, 9, 35},
        {10, 11, 36},
        {12, 13, 37},
        {14, 15, 38},
        {16, 17, 39},
        {18, 19, 40},
        {20, 21, 41},
        {22, 23, 42},
        {24, 25, 43},
        {26, 27, 44}        
    }
;

hook OnUserLogout(playerid) {

    SpriteBrowser_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    .oooooo.   ooooo        ooooo   .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'  `Y8b  `888'        `888'  d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    888           888          888  888           888  d8'    Y88bo.      
                    888           888          888  888           88888[       `"Y8888o.  
                    888           888          888  888           888`88b.         `"Y88b 
                    `88b    ooo   888       o  888  `88b    ooo   888  `88b.  oo     .d8P 
                    `Y8bood8P'  o888ooooood8 o888o  `Y8bood8P'  o888o  o888o 8""88888P'  

*/

PlayerTextDrawClick:SPRITEBROWSER(playerid, index) {

    if(e_Data[playerid][E_DATA_DELAY] > GetTickCount())
        return;

    if(Dialog_Opened(playerid))
        return;

    e_Data[playerid][E_DATA_SELECTED_INDEX] = index;

    inline SpriteBrowserOptions() {

        DialogMod_Add(playerid, "Create Sprite", E_INTERACTION_CREATE);

        if(!e_Data[playerid][E_DATA_FAVORITE][index])
            DialogMod_Add(playerid, "{"#HEX_DEFAULT"}Add to Favorite", E_INTERACTION_ADD_FAVORITE);
        else
            DialogMod_Add(playerid, "{"#HEX_INFO"}Remove to Favorite", E_INTERACTION_REMOVE_FAVORITE);
    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, "Options", "Select", "Close", "D_SPRITEBROWSEROPTIONS", using inline SpriteBrowserOptions);
}

PlayerTextDrawClick:SPRITEBROWSER_SIDEBAR(playerid, index)
    SpriteBrowser_LoadFilter(playerid, e_SpriteArray[index][E_SPRITEARRAY_TYPE]);

PlayerTextDrawClick:SPRITEBROWSER_NEXT(playerid)
    SpriteBrowser_Page(playerid, SpriteBrowser_GetPage(playerid) + 1);

PlayerTextDrawClick:SPRITEBROWSER_PREVIOUS(playerid)
    SpriteBrowser_Page(playerid, SpriteBrowser_GetPage(playerid) - 1);

PlayerTextDrawClick:SPRITEBROWSER_NEXTSIDE(playerid)
    SpriteBrowser_SideBarPage(playerid, SpriteBrowser_GetSideBarPage(playerid) + 1);

PlayerTextDrawClick:SPRITEBROWSER_PREVIOUSSIDE(playerid)
    SpriteBrowser_SideBarPage(playerid, SpriteBrowser_GetSideBarPage(playerid) - 1);

PlayerTextDrawClick:SPRITEBROWSER_SEARCH(playerid)
    Dialog_Show(playerid, D_SPRITEBROWSER_SEARCH, DIALOG_STYLE_INPUT, "Search", "Please specify what you want to search for below. If you wish to remove the filter, leave no information.", "Search", "Close");

PlayerTextDrawClick:SPRITEBROWSER_CLOSE(playerid)
    SpriteBrowser_Close(playerid);



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SpriteBrowser_Show(playerid) {

    e_Data[playerid][E_DATA_CREATED] = true;
    e_Data[playerid][E_DATA_DELAY] = GetTickCount() + 500;
    
    TaskBarButton_HideAll(playerid);
    SessionTextDraw_HideAllForPlayer(playerid);
    SpriteBrowserView_Show(playerid);

    SpriteBrowser_SideBarPage(playerid, 0);
    SpriteBrowser_LoadFilter(playerid, E_TYPESPRITE_ALL);
    return true;
}

static stock SpriteBrowser_Close(playerid) {

    SpriteBrowser_Reset(playerid);
    TaskBarButton_ShowAll(playerid);
    SessionTextDraw_ShowAllForPlayer(playerid);
}

static stock SpriteBrowser_SetPage(playerid, page)
    e_Data[playerid][E_DATA_PAGE] = page;

static stock SpriteBrowser_GetPage(playerid)
    return e_Data[playerid][E_DATA_PAGE];

static stock SpriteBrowser_SetPages(playerid, page)
    e_Data[playerid][E_DATA_PAGES] = page;

static stock SpriteBrowser_GetPages(playerid)
    return e_Data[playerid][E_DATA_PAGES];

static stock SpriteBrowser_SetSideBarPage(playerid, page)
    e_Data[playerid][E_DATA_SIDEBAR_PAGE] = page;

static stock SpriteBrowser_GetSideBarPage(playerid)
    return e_Data[playerid][E_DATA_SIDEBAR_PAGE];

stock bool:SpriteBrowser_Created(playerid)
    return e_Data[playerid][E_DATA_CREATED];

static stock SpriteBrowser_SetFilter(playerid, const filter[])
    strcopy(e_Data[playerid][E_DATA_FILTER], filter);

static stock SpriteBrowser_GetFilter(playerid, dest[], maxlength = sizeof dest)
    strcopy(dest, e_Data[playerid][E_DATA_FILTER], maxlength);

static stock SpriteBrowser_UpdatePageSelfSideBar(playerid)
    SpriteBrowser_SideBarPage(playerid, SpriteBrowser_GetSideBarPage(playerid));    // Update Self

static stock SpriteBrowser_UpdatePageSelf(playerid)
    SpriteBrowser_Page(playerid, SpriteBrowser_GetPage(playerid));    // Update Self

static stock SpriteBrowser_SetFilterItem(playerid, const search[]) {
    strcopy(e_Data[playerid][E_DATA_FILTER_ITEM], search);
    SpriteBrowserView_SetString(playerid, 123, search);
}

static stock SpriteBrwoser_RemoveFilterItem(playerid) {
    stringclear(e_Data[playerid][E_DATA_FILTER_ITEM]);
    SpriteBrowserView_SetString(playerid, 123, "Search");
}

static stock SpriteBrowser_Reset(playerid) {

    SpriteBrowserView_Hide(playerid);

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;  
}

static stock SpriteBrowser_LoadFilter(playerid, E_TYPESPRITE:sprite, bool:force = false) {
    
    if(!force && e_Data[playerid][E_DATA_SELECTED_SIDEBAR] == sprite)
        return;

    new filter[64 + 1];
    if(sprite == E_TYPESPRITE_FAVORITES) strcat(filter, "WHERE hasStar <> -1");
    else if(sprite != E_TYPESPRITE_ALL) strcatEx(filter, "WHERE s.type = %i", _:sprite);

    if(!isnull(e_Data[playerid][E_DATA_FILTER_ITEM])) {
        if(isnull(filter)) strcat(filter, "WHERE ");
        else strcat(filter, " AND ");

        strcatEx(filter, "s.sprite LIKE '%%%s%%'", e_Data[playerid][E_DATA_FILTER_ITEM]); 
    }

    SpriteBrowser_SetFilter(playerid, filter);
    e_Data[playerid][E_DATA_SELECTED_SIDEBAR] = sprite;

    SpriteBrowser_UpdatePageSelfSideBar(playerid);

    new DBResult:cache;

    if(sprite == E_TYPESPRITE_FAVORITES) {
        cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                COUNT(*) AS count \
                                            FROM sprites s \
                                            JOIN sprites_favorites sf ON sf.sprite_id = s.id \
                                            WHERE sf.user = '%s'", 
                                            
                                            Auth_GetName(playerid)                                            
                                        );
    }
    else cache = DB_ExecuteQuery(IDConnection, "SELECT count(*) AS count FROM sprites s %s", filter);

    if(cache) {

        new count = DB_GetFieldIntByName(cache, "count");
        SpriteBrowser_SetPages(playerid, Util_GetPages(count, MAX_SPRITEBROWSER_PAGES));
        DB_FreeResultSet(cache);

        SpriteBrowser_Page(playerid, 0);
    }
}

static stock SpriteBrowser_Page(playerid, page) {

    new 
        pages = SpriteBrowser_GetPages(playerid),
        filter[64 + 1],
        count
    ;

    if(page >= pages) page = pages - 1;
    if(page < 0 || pages <= 0) page = 0;

    SpriteBrowser_GetFilter(playerid, filter);
    SpriteBrowser_SetPage(playerid, page);

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            s.id, \
                                                            s.sprite, \
                                                            COALESCE(sf.sprite_id, -1) AS hasStar \
                                                        FROM sprites s \
                                                        LEFT JOIN sprites_favorites sf ON sf.user = '%s' AND sf.sprite_id = s.id \
                                                        %s \
                                                        LIMIT %i OFFSET %i", 

                                                        Auth_GetName(playerid),
                                                        filter,
                                                        MAX_SPRITEBROWSER_PAGES,
                                                        page * MAX_SPRITEBROWSER_PAGES
                                                    );

    if(cache) {

        if(DB_GetRowCount(cache))
        {
            new 
                sprite[64 + 1],
                favId
            ;
            do
            {
                favId = DB_GetFieldIntByName(cache, "hasStar");
                e_Data[playerid][E_DATA_IDS][count] = DB_GetFieldIntByName(cache, "id");
                e_Data[playerid][E_DATA_FAVORITE][count] = favId != -1;
                DB_GetFieldStringByName(cache, "sprite", sprite);

                for(new i = 0; i < sizeof e_Sprite[]; i++)
                    SpriteBrowserView_ShowItem(playerid, e_Sprite[count][i]);

                SpriteBrowserView_SetClick(playerid, e_Sprite[count][0], "SPRITEBROWSER", count);
                SpriteBrowserView_SetColor(playerid, e_Sprite[count][0], favId == -1 ? 505290495 : RGB::RGBAToHex(222, 206, 67, 90));
                SpriteBrowserView_SetString(playerid, e_Sprite[count][1], sprite);
                SpriteBrowserView_SetString(playerid, e_Sprite[count][2], sprite);

                count++;
            }
            while(DB_SelectNextRow(cache));
        }

        DB_FreeResultSet(cache);
    }

    for(new c = count; c < sizeof e_Sprite; c++)
        for(new i = 0; i < sizeof e_Sprite[]; i++)
            SpriteBrowserView_HideItem(playerid, e_Sprite[c][i]);

}

static stock SpriteBrowser_SideBarPage(playerid, page) {
    
    new pages = Util_GetPages(sizeof e_SpriteArray, sizeof e_SpriteSideBar);
    
    if(page >= pages) page = pages - 1;
    if(page < 0 || pages <= 0) page = 0;

    SpriteBrowser_SetSideBarPage(playerid, page);

    new 
        start = page * sizeof e_SpriteSideBar,
        end = start + sizeof e_SpriteSideBar,
        count
    ;

    for(new i = start; i < end; i++) {

        if(i >= sizeof e_SpriteArray) break;

        for(new c = 0; c < sizeof e_SpriteSideBar[]; c++)
            SpriteBrowserView_ShowItem(playerid, e_SpriteSideBar[count][c]);

        SpriteBrowserView_SetClick(playerid, e_SpriteSideBar[count][0], "SPRITEBROWSER_SIDEBAR", i);
        SpriteBrowserView_SetString(playerid, e_SpriteSideBar[count][1], e_SpriteArray[i][E_SPRITEARRAY_NAME]);
        SpriteBrowserView_SetSize(playerid, e_SpriteSideBar[count][2], e_Data[playerid][E_DATA_SELECTED_SIDEBAR] != e_SpriteArray[i][E_SPRITEARRAY_TYPE] ? -1.0 : -2.0);
        SpriteBrowserView_SetColor(playerid, e_SpriteSideBar[count][2], e_Data[playerid][E_DATA_SELECTED_SIDEBAR] != e_SpriteArray[i][E_SPRITEARRAY_TYPE] ? 0x673AB740 : 0x673AB7FF);

        count++;
    }

    for(new c = count; c < sizeof e_SpriteSideBar; c++)
        for(new i = 0; i < sizeof e_SpriteSideBar[]; i++)
            SpriteBrowserView_HideItem(playerid, e_SpriteSideBar[c][i]);
}

static stock SpriteBrowser_AddFavorite(playerid, spriteId) {

    DB_FreeResultSet(
        DB_ExecuteQuery(IDConnection, "INSERT INTO sprites_favorites (user, sprite_id) VALUES ('%s', %i)", Auth_GetName(playerid), spriteId)
    );

    SpriteBrowser_UpdatePageSelf(playerid);
}

static stock SpriteBrowser_RemoveFavorite(playerid, spriteId) {

    DB_FreeResultSet(
        DB_ExecuteQuery(IDConnection, "DELETE FROM sprites_favorites WHERE sprite_id = %i AND user = '%s'", spriteId, Auth_GetName(playerid))
    );

    SpriteBrowser_UpdatePageSelf(playerid);
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

Dialog:D_SPRITEBROWSER(playerid, response) {

    if(response) {

        
    }
    return true;
}

Dialog:D_SPRITEBROWSER_SEARCH(playerid, response, listitem, inputtext[]) {

    if(response) {
        if(isnull(inputtext)) 
            SpriteBrwoser_RemoveFilterItem(playerid);
        else 
            SpriteBrowser_SetFilterItem(playerid, inputtext);
    
        SpriteBrowser_LoadFilter(playerid, e_Data[playerid][E_DATA_SELECTED_SIDEBAR], true);   // Update Self
    }
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

DialogMod:D_SPRITEBROWSEROPTIONS(playerid, response, inputtext[], listitem) {

    if(response) {

        new 
            indexSelected = e_Data[playerid][E_DATA_SELECTED_INDEX],
            uniqueId = e_Data[playerid][E_DATA_IDS][indexSelected]
        ;

        switch(listitem) {
            case E_INTERACTION_CREATE: {

                new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                        sprite \
                                                                    FROM sprites \
                                                                    WHERE id = %i", 

                                                                    uniqueId    
                                                                );

                if(cache)
                {
                    new sprite[64 + 1];
                    DB_GetFieldStringByName(cache, "sprite", sprite);
                    DB_FreeResultSet(cache);

                    SpriteBrowser_Close(playerid);

                    new index = SessionTextDrawData_Create(E_TYPEITEM_SPRITE);
                    SessionTextDrawData_SetString(index, sprite);
                    TaskBarTextDraw_Select(playerid, index, false);
                }
            }

            case E_INTERACTION_ADD_FAVORITE: SpriteBrowser_AddFavorite(playerid, uniqueId);
            case E_INTERACTION_REMOVE_FAVORITE: SpriteBrowser_RemoveFavorite(playerid, uniqueId);
        }
    }
}



            // Core
#include "src/general/spriteBrowser/core/instance.inc"