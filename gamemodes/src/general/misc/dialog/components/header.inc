
            // Definers
#define         MAX_DIALOGMOD_ITENS         (128)

#define DialogMod:%0(%1) \
    forward dlmo_%0(%1); public dlmo_%0(%1)

enum E_DIALOGMOD {
    E_DIALOGMOD_CALLBACK[30 + 1],
    DIALOG_STYLE:E_DIALOGMOD_STYLE
};

enum E_DIALOGMODITEM {
    E_DIALOGMODITEM_STRING[256 + 1],
    E_DIALOGMODITEM_PARAMS
};

new
    Iterator:DialogModItens[MAX_PLAYERS]<MAX_DIALOGMOD_ITENS>,
    e_DialogMod[MAX_PLAYERS][E_DIALOGMOD],
    e_DialogModItem[MAX_PLAYERS][MAX_DIALOGMOD_ITENS][E_DIALOGMODITEM]
;