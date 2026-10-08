
/*
	Dialog Response

	API:
	- Dialog_Create(playerid, const callback[], DIALOG_STYLE:style, const title[], body[], const button1[], const button2[], {Float, _}:...);	// Create Protected Dialog
	- Dialog_Show(playerid, const callback[], DIALOG_STYLE:style, const title[], body[], const button1[], const button2[], {Float, _}:...); // Same Dialog_Open
	- Dialog_Close(playerid);
	- Dialog_ReShow(playerid, const error[] = ""); // Reopen the same dialog with additional message or not
	- bool:Dialog_Created(playerid);

		Created by https://github.com/devbluen/easyDialog
*/


#if defined _easyDialog_included
	#endinput
#endif
#define _easyDialog_included

			// Macros
#define Dialog:%0(%1) \
	forward edialog%0(%1); \
	public edialog%0(%1)

#define Dialog_Show(%0,%1, \
	Dialog_Create(%0, #%1,

#if !defined isnull
	#define isnull(%1) \
		((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

			// Includes
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_va>

static enum E_DIALOG {
	bool:E_DIALOG_CREATED,
	E_DIALOG_BODY[4096],
	E_DIALOG_TITLE[64],
	E_DIALOG_BUTTON1[32],
	E_DIALOG_BUTTON2[32],
	E_DIALOG_CALLBACK[32],
	E_DIALOG_BODY_ERROR[192],
	DIALOG_STYLE:E_DIALOG_STYLE,
	
	// Data Protections
	E_DIALOG_LISTS
};

static
	e_Dialog[MAX_PLAYERS][E_DIALOG]
;

static const
	DIALOG_PROTECTED_ID = 32762
;

hook OnPlayerDisconnect(playerid, reason) {

	Dialog_Reset(playerid);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	if(dialogid != DIALOG_PROTECTED_ID)
		return Y_HOOKS_CONTINUE_RETURN_1;

	if(!Dialog_Created(playerid))
    	return Y_HOOKS_BREAK_RETURN_1;

	// Mod Current Dialog
	new callback[32];
	Dialog_GetCallback(playerid, callback);
	Dialog_SetCreated(playerid, false);			// Close Status Dialog
	Dialog_SetError(playerid, "");				// Invalid Error

	// Character Crash Server (protection)
	for(new i = 0, l = strlen(inputtext); i < l; i++) 
		if(inputtext[i] == '%') 
			inputtext[i] = '#';
	
	// Listitem Response Protection
	new max_listitem;
	if((max_listitem = Dialog_GetLists(playerid)) > 0) {
		if(listitem != -1 && listitem >= max_listitem) listitem = (max_listitem - 1);	// normalize listitem response
		if(listitem < 0 && response) listitem = 0;
	}

	// Response Dialog
	CallLocalFunction(
		va_return(
			"edialog%s", 
			callback
		), 
		"iiis", 
		playerid, response, listitem, isnull(inputtext) ? "\1" : inputtext
	);
    return Y_HOOKS_BREAK_RETURN_1;
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
 
stock Dialog_Create(playerid, const callback[], DIALOG_STYLE:style, const title[], const body[], const button1[], const button2[], {Float, _}:...) {

	new 
		error[192],
		bodyBuff[4096]
	;

	format(bodyBuff, sizeof bodyBuff, body, ___(7));

	// Protections
	switch(style) {
		case 
			DIALOG_STYLE_LIST,
			DIALOG_STYLE_TABLIST, 
			DIALOG_STYLE_TABLIST_HEADERS:
			{
				new len = strlen(bodyBuff);
				while(len > 0 && (bodyBuff[len - 1] == '\n' || bodyBuff[len - 1] == '\r'))
					bodyBuff[--len] = EOS;

				new items = (len == 0) ? 0 : (Dialog_CountChars(bodyBuff, "\n") + 1);
				if(style == DIALOG_STYLE_TABLIST_HEADERS && items > 0)
					items--;

				Dialog_SetLists(playerid, items);
			}
	}

	Dialog_SetBody(playerid, bodyBuff);
	Dialog_SetTitle(playerid, title);
	Dialog_SetStyle(playerid, style);
	Dialog_SetCallback(playerid, callback);
	Dialog_SetButton1(playerid, button1);
	Dialog_SetButton2(playerid, button2);
	Dialog_SetCreated(playerid, true);

	Dialog_GetError(playerid, error);
	if(!isnull(error))
		strcat(bodyBuff, error);

	return ShowPlayerDialog(playerid, DIALOG_PROTECTED_ID, style, title, bodyBuff, button1, button2);
}

stock Dialog_ReShow(playerid, const error[] = "", {Float, _}:...) {

	new
		body[4096],
		title[64],
		button1[32],
		button2[32],
		DIALOG_STYLE:style,
		callback[32],
		errorBuff[192]
	;

	format(errorBuff, sizeof errorBuff, error, ___(2));
	strins(errorBuff, "\n\n", 0);

	// Get
	style = Dialog_GetStyle(playerid);
	Dialog_GetTitle(playerid, title);
	Dialog_GetBody(playerid, body);
	Dialog_GetButton1(playerid, button1);
	Dialog_GetButton2(playerid, button2);
	Dialog_GetCallback(playerid, callback);

	// Set
	Dialog_SetError(playerid, errorBuff);

	return 
		Dialog_Create(
			.playerid = playerid, 
			.callback = callback, 
			.style = style, 
			.title = title, 
			.body = body, 
			.button1 = button1, 
			.button2 = button2
		)
	;
}

stock Dialog_Close(playerid) {
	Dialog_Reset(playerid);
	ShowPlayerDialog(playerid, DIALOG_PROTECTED_ID - 1, DIALOG_STYLE_MSGBOX, " ", " ", " ", "");
}

static stock Dialog_GetTitle(playerid, dest[], maxlength = sizeof dest)
	strcopy(dest, e_Dialog[playerid][E_DIALOG_TITLE], maxlength);

static stock Dialog_SetTitle(playerid, const title[])
	strcopy(e_Dialog[playerid][E_DIALOG_TITLE], title);

static stock Dialog_GetBody(playerid, dest[], maxlength = sizeof dest)
	strcopy(dest, e_Dialog[playerid][E_DIALOG_BODY], maxlength);

static stock Dialog_SetBody(playerid, const body[])
	strcopy(e_Dialog[playerid][E_DIALOG_BODY], body);

static stock Dialog_GetButton1(playerid, dest[], maxlength = sizeof dest)
	strcopy(dest, e_Dialog[playerid][E_DIALOG_BUTTON1], maxlength);

static stock Dialog_SetButton1(playerid, const text[])
	strcopy(e_Dialog[playerid][E_DIALOG_BUTTON1], text);

static stock Dialog_GetButton2(playerid, dest[], maxlength = sizeof dest)
	strcopy(dest, e_Dialog[playerid][E_DIALOG_BUTTON2], maxlength);

static stock Dialog_SetButton2(playerid, const text[])
	strcopy(e_Dialog[playerid][E_DIALOG_BUTTON2], text);

static stock Dialog_GetCallback(playerid, dest[], maxlength = sizeof dest)
	strcopy(dest, e_Dialog[playerid][E_DIALOG_CALLBACK], maxlength);

static stock Dialog_SetCallback(playerid, const callback[])
	strcopy(e_Dialog[playerid][E_DIALOG_CALLBACK], callback);

static stock Dialog_GetError(playerid, dest[], maxlength = sizeof dest)
	strcopy(dest, e_Dialog[playerid][E_DIALOG_BODY_ERROR], maxlength);

static stock Dialog_SetError(playerid, const text[])
	strcopy(e_Dialog[playerid][E_DIALOG_BODY_ERROR], text);

static stock DIALOG_STYLE:Dialog_GetStyle(playerid)
	return e_Dialog[playerid][E_DIALOG_STYLE];

static stock Dialog_SetStyle(playerid, DIALOG_STYLE:style)
	e_Dialog[playerid][E_DIALOG_STYLE] = style;

static stock Dialog_GetLists(playerid)
	return e_Dialog[playerid][E_DIALOG_LISTS];

static stock Dialog_SetLists(playerid, value)
	e_Dialog[playerid][E_DIALOG_LISTS] = value;

stock bool:Dialog_Created(playerid)
	return e_Dialog[playerid][E_DIALOG_CREATED];

static stock Dialog_SetCreated(playerid, bool:status)
	e_Dialog[playerid][E_DIALOG_CREATED] = status;

static stock Dialog_CountChars(const string[], const sub[], bool:ignorecase = false, bool:count_overlapped = false) {
	new
		increment = count_overlapped ? 1 : strlen(sub),
		pos = -increment,
		count = 0;
	
	while (-1 != (pos = strfind(string, sub, ignorecase, pos + increment)))
		count++;
	
	return count;
}

static stock Dialog_Reset(playerid) {

	static const e_Clear[E_DIALOG];
	e_Dialog[playerid] = e_Clear;
}
