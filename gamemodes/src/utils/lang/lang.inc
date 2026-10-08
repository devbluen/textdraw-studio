#include "src/utils/lang/keys.inc"
#include <YSI_Coding\y_hooks>

#define L(%0,%1) LangText[Lang_Get(%0)][%1]

#if !defined DEFAULT_LANGUAGE
    #define DEFAULT_LANGUAGE E_LANGUAGE_PT
#endif

static
    E_LANGUAGE:e_PlayerLang[MAX_PLAYERS] = {DEFAULT_LANGUAGE, ...}
;

new const
    LangText[E_LANGUAGE][E_LANG][LANG_STRING_SIZE] = {
        {
            #include "src/utils/lang/en.inc"
        },
        {
            #include "src/utils/lang/pt.inc"
        },
        {
            #include "src/utils/lang/es.inc"
        },
        {
            #include "src/utils/lang/fr.inc"
        }
    }
;

hook OnUserLogin(playerid) {
    Lang_Load(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnUserLogout(playerid) {
    e_PlayerLang[playerid] = DEFAULT_LANGUAGE;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

stock E_LANGUAGE:Lang_Get(playerid) {
    if(playerid < 0 || playerid >= MAX_PLAYERS)
        return DEFAULT_LANGUAGE;

    return e_PlayerLang[playerid];
}

stock E_LANG:Lang_NameKey(E_LANGUAGE:lang) {
    switch(lang) {
        case E_LANGUAGE_PT: return E_LANG_LANGUAGE_PT;
        case E_LANGUAGE_ES: return E_LANG_LANGUAGE_ES;
        case E_LANGUAGE_FR: return E_LANG_LANGUAGE_FR;
    }
    return E_LANG_LANGUAGE_EN;
}

stock Lang_Set(playerid, E_LANGUAGE:lang, bool:save = true) {
    if(_:lang < 0 || _:lang >= _:E_LANGUAGE)
        lang = DEFAULT_LANGUAGE;

    e_PlayerLang[playerid] = lang;

    if(save)
        Lang_Save(playerid);

    Lang_ApplyUI(playerid);
}

stock Lang_GetName(playerid, dest[], maxlength = sizeof dest) {
    strcat(dest, L(playerid, Lang_NameKey(e_PlayerLang[playerid])), maxlength);
}

stock LangF(playerid, dest[], size, E_LANG:key, {Float, _}:...) {
    format(dest, size, LangText[Lang_Get(playerid)][key], ___(4));
}

stock SendLang(playerid, color, E_LANG:key, {Float, _}:...) {
    new message_buff[148 + 1];

    if(playerid == INVALID_PLAYER_ID) {
        foreach(new i: Users) {
            format(message_buff, sizeof message_buff, LangText[Lang_Get(i)][key], ___(3));
            Util_ClearChat(i);
            SendClientMessage(i, color, message_buff);
        }
    } else {
        format(message_buff, sizeof message_buff, LangText[Lang_Get(playerid)][key], ___(3));
        Util_ClearChat(playerid);
        SendClientMessage(playerid, color, message_buff);
    }
    return true;
}

static
    bool:e_LangFromSettings[MAX_PLAYERS]
;

stock Lang_ShowPicker(playerid, bool:fromSettings = false) {
    e_LangFromSettings[playerid] = fromSettings;
    Dialog_Show(playerid, D_LANGUAGE_PICK, DIALOG_STYLE_LIST, L(playerid, E_LANG_PICK_TITLE), L(playerid, E_LANG_PICK_BODY), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CLOSE));
}

stock Lang_ApplyUI(playerid) {
    TaskBarView_ApplyLang(playerid);
}

static stock Lang_Load(playerid) {
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name);

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT language FROM user_language WHERE name = '%s' LIMIT 1", name);
    if(cache) {
        if(DB_GetRowCount(cache)) {
            new loaded = DB_GetFieldIntByName(cache, "language");
            if(loaded < 0 || loaded >= _:E_LANGUAGE)
                e_PlayerLang[playerid] = DEFAULT_LANGUAGE;
            else
                e_PlayerLang[playerid] = E_LANGUAGE:loaded;
        } else
            e_PlayerLang[playerid] = DEFAULT_LANGUAGE;

        DB_FreeResultSet(cache);
        return;
    }

    e_PlayerLang[playerid] = DEFAULT_LANGUAGE;
}

static stock Lang_Save(playerid) {
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name);

    DB_FreeResultSet(
        DB_ExecuteQuery(IDConnection, "INSERT OR REPLACE INTO user_language (name, language) VALUES ('%s', %i)", name, _:e_PlayerLang[playerid])
    );
}

Dialog:D_LANGUAGE_PICK(playerid, response, listitem) {
    if(response) {
        Lang_Set(playerid, E_LANGUAGE:listitem);
        SendLang(playerid, -1, E_LANG_SET_LANGUAGE_CHANGED, L(playerid, Lang_NameKey(e_PlayerLang[playerid])));
    }

    if(e_LangFromSettings[playerid])
        TaskBarEventSettings_Show(playerid);

    e_LangFromSettings[playerid] = false;
    return true;
}

CMD:lang(playerid) {
    Lang_ShowPicker(playerid);
    return true;
}

CMD:language(playerid) {
    Lang_ShowPicker(playerid);
    return true;
}
