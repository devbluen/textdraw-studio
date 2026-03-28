
            // Components
#include "src/general/session/components/header.inc"

            // Includes
#include <YSI_Coding\y_hooks>

hook OnUserLogin(playerid) {

    if(Session_Has())
        Session_Enter(playerid);

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

stock Session_SetId(uniqueId) {
    e_Session[E_SESSION_ID] = uniqueId;

    Session_LoadDraws();
    Session_EnterAll();
}

stock Session_GetId()
    return e_Session[E_SESSION_ID];

stock bool:Session_Has()
    return Session_GetId() > 0;

stock Session_Close() {
    e_Session[E_SESSION_ID] = 0;
    Session_LeaveAll();
}

stock Session_LoadDraws() {

    new uniqueId = Session_GetId();
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            id, \
                                                            project_id, \
                                                            position, \
                                                            size, \
                                                            letter_size, \
                                                            `text`, \
                                                            font, \
                                                            align, \
                                                            proportion, \
                                                            outline, \
                                                            shadow, \
                                                            color, \
                                                            colorBackground, \
                                                            colorBox, \
                                                            selectable, \
                                                            mode, \
                                                            itemType, \
                                                            `indexDraw` \
                                                        FROM textdraws  \
                                                        WHERE project_id = %i \
                                                        ORDER BY `indexDraw` DESC", 

                                                        uniqueId
                                                    );

    if(cache) {

        new 
            index,
            buffGeneral[64 + 1]
        ;

        do
        {
            // Get Index
            index = DB_GetFieldIntByName(cache, "indexDraw");

            // Ints
            e_SessionDraw[index][E_SESSIONDRAW_UNIQUE_ID] = DB_GetFieldIntByName(cache, "id");
            e_SessionDraw[index][E_SESSIONDRAW_FONT] = _:DB_GetFieldIntByName(cache, "font");
            e_SessionDraw[index][E_SESSIONDRAW_ALIGN] = _:DB_GetFieldIntByName(cache, "align");
            e_SessionDraw[index][E_SESSIONDRAW_PROPORTION] = DB_GetFieldIntByName(cache, "proportion");
            e_SessionDraw[index][E_SESSIONDRAW_OUTLINE] = DB_GetFieldIntByName(cache, "outline");
            e_SessionDraw[index][E_SESSIONDRAW_SHADOW] = DB_GetFieldIntByName(cache, "shadow");
            e_SessionDraw[index][E_SESSIONDRAW_COLOR] = DB_GetFieldIntByName(cache, "color");
            e_SessionDraw[index][E_SESSIONDRAW_COLOR_BACKGROUND] = DB_GetFieldIntByName(cache, "colorBackground");
            e_SessionDraw[index][E_SESSIONDRAW_COLOR_BOX] = DB_GetFieldIntByName(cache, "colorBox");
            e_SessionDraw[index][E_SESSIONDRAW_SELECTABLE] = DB_GetFieldIntByName(cache, "selectable");
            e_SessionDraw[index][E_SESSIONDRAW_MODE] = _:DB_GetFieldIntByName(cache, "mode");
            e_SessionDraw[index][E_SESSIONDRAW_TYPE] = _:DB_GetFieldIntByName(cache, "itemType");
            e_SessionDraw[index][E_SESSIONDRAW_MODEL] = _:DB_GetFieldIntByName(cache, "model");
            e_SessionDraw[index][E_SESSIONDRAW_BOX] = _:DB_GetFieldIntByName(cache, "box");

            // Strings
            DB_GetFieldStringByName(cache, "text", e_SessionDraw[index][E_SESSIONDRAW_TEXT]);

            // Floats
            DB_GetFieldStringByName(cache, "position", buffGeneral);
            sscanf(buffGeneral, "p<,>a<f>[2]", e_SessionDraw[index][E_SESSIONDRAW_POSITION]);

            DB_GetFieldStringByName(cache, "size", buffGeneral);
            sscanf(buffGeneral, "p<,>a<f>[2]", e_SessionDraw[index][E_SESSIONDRAW_SIZE]);

            DB_GetFieldStringByName(cache, "letter_size", buffGeneral);
            sscanf(buffGeneral, "p<,>a<f>[2]", e_SessionDraw[index][E_SESSIONDRAW_LETTER_SIZE]);

            DB_GetFieldStringByName(cache, "model_rotation", buffGeneral);
            sscanf(buffGeneral, "p<,>a<f>[4]", e_SessionDraw[index][E_SESSIONDRAW_MODEL_ROTATION]);

            DB_GetFieldStringByName(cache, "model_colors", buffGeneral);
            sscanf(buffGeneral, "p<,>a<i>[2]", e_SessionDraw[index][E_SESSIONDRAW_MODEL_COLORS]);

            Iter_Add(SessionDraws, index);
        }
        while(DB_SelectNextRow(cache));

        DB_FreeResultSet(cache);
    }
}

stock Session_Enter(playerid) {
    SessionTextdraw_Load(playerid);
}

stock Session_Leave(playerid) {
    SessionTextdraw_Unload(playerid);
}

stock Session_EnterAll() {
    foreach(new i: Users)
        Session_Enter(i);
}

stock Session_LeaveAll() {
    foreach(new i: Users)
        Session_Leave(i);
}



            // Components
                // Functions
#include "src/general/session/components/functions/textdraw.inc"
#include "src/general/session/components/functions/textdrawData.inc"