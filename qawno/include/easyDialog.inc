
			// Includes
#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>
#include <YSI_Coding\y_hooks>

#if defined _easyDialog_included
	#endinput
#endif
#define _easyDialog_included

#if !defined isnull
	#define isnull(%1) \
		((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined stringclear
	#define stringclear(%0) \
		%0[0] = '\0'
#endif

#define Dialog:%0(%1) \
	forward dlg_%0(%1); public dlg_%0(%1)

#define Dialog_Show(%0,%1, \
	Dialog_Open(%0, #%1,

static enum E_EASY_DIALOG {
	bool:E_EASY_DIALOG_OPEN,

	E_EASY_DIALOG_CALL[30 + 1],
	DIALOG_STYLE:E_EASY_DIALOG_TYPE,
	E_EASY_DIALOG_LISTITENS,
	E_EASY_DIALOG_TITLE[64 + 1],
	E_EASY_DIALOG_CAPTION[1024 * 4],
	E_EASY_DIALOG_BUTTON1[30 + 1],
	E_EASY_DIALOG_BUTTON2[30 + 1]
};

static e_EasyDialog[MAX_PLAYERS][E_EASY_DIALOG];

hook OnPlayerDisconnect(playerid, reason) {

	static e_Clear[E_EASY_DIALOG];
	e_EasyDialog[playerid] = e_Clear;
	return true;
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

stock Dialog_Opened(playerid)
	return (e_EasyDialog[playerid][E_EASY_DIALOG_OPEN]);

stock Dialog_Close(playerid) {
	stringclear(e_EasyDialog[playerid][E_EASY_DIALOG_CALL]);
	e_EasyDialog[playerid][E_EASY_DIALOG_OPEN] = false;
	return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", "");
}

stock Dialog_ReShow(playerid, const error[] = "*") {
	Dialog_Open(playerid, e_EasyDialog[playerid][E_EASY_DIALOG_CALL], e_EasyDialog[playerid][E_EASY_DIALOG_TYPE], e_EasyDialog[playerid][E_EASY_DIALOG_TITLE], e_EasyDialog[playerid][E_EASY_DIALOG_CAPTION], e_EasyDialog[playerid][E_EASY_DIALOG_BUTTON1], e_EasyDialog[playerid][E_EASY_DIALOG_BUTTON2], error);
	return true;
}

stock Dialog_Open(playerid, const function[], DIALOG_STYLE:style, const title[], const caption[], const button1[], const button2[], const error[] = "*") {
	if(!strlen(caption) || !IsPlayerConnected(playerid)) return false;

	new string[4095 + 1];

	e_EasyDialog[playerid][E_EASY_DIALOG_OPEN] = true;
	e_EasyDialog[playerid][E_EASY_DIALOG_LISTITENS] = -1;
	strcat(string, caption);

	if(style == DIALOG_STYLE_TABLIST || style == DIALOG_STYLE_TABLIST_HEADERS) {
		strcat(string, "\n");
		e_EasyDialog[playerid][E_EASY_DIALOG_LISTITENS] = strcount_easy(string, "\n");
		
		if(strfind(string, "\n\n") != -1)
			e_EasyDialog[playerid][E_EASY_DIALOG_LISTITENS]--;
	}

	/*
		Configure for reopen dialog
	*/

	format(e_EasyDialog[playerid][E_EASY_DIALOG_CALL], 30 + 1, function);
	format(e_EasyDialog[playerid][E_EASY_DIALOG_TITLE], 64 + 1, title);
	format(e_EasyDialog[playerid][E_EASY_DIALOG_CAPTION], 1024 * 4, caption);
	format(e_EasyDialog[playerid][E_EASY_DIALOG_BUTTON1], 30 + 1, button1);
	format(e_EasyDialog[playerid][E_EASY_DIALOG_BUTTON2], 30 + 1, button2);
	e_EasyDialog[playerid][E_EASY_DIALOG_TYPE] = style;

	if(strcmp(error, "*", true))
		strcat(string, va_return("\n\n{CD5C5C}ERRO: {C9C9C9}%s", error));

	// Response
	inline const EASY_DIALOG(pid, dialogid, response, listitem, string:inputtext[]) {

		#pragma unused dialogid

		// Prevent possible problems
		if(!Dialog_Opened(pid)) return false;
		if(isnull(e_EasyDialog[pid][E_EASY_DIALOG_CALL])) return false;

		// Fix crash server
		for(new i = 0, l = strlen(inputtext); i < l; i ++) 
			if (inputtext[i] == '%') 
				inputtext[i] = '#';
		
		// Protect listitem response
		new listitem_protected = e_EasyDialog[pid][E_EASY_DIALOG_LISTITENS];
		if((listitem_protected != -1 && listitem != -1) && listitem >= listitem_protected) 
			listitem = 0;

		new easyDialog_String[30 + 1];
		strcat(easyDialog_String, "dlg_");
		strcat(easyDialog_String, e_EasyDialog[pid][E_EASY_DIALOG_CALL]);

		stringclear(e_EasyDialog[pid][E_EASY_DIALOG_CALL]);
		e_EasyDialog[pid][E_EASY_DIALOG_OPEN] = false;

		CallLocalFunction(easyDialog_String, "ddds", pid, response, listitem, (isnull(inputtext)) ? ("\1") : (inputtext));
	}

	Dialog_ShowCallback(playerid, using inline EASY_DIALOG, style, title, string, button1, button2);
	return true;
}

static stock strcount_easy(const string[], const sub[], bool:ignorecase = false, bool:count_overlapped = false) {
	new
		increment = count_overlapped ? 1 : strlen(sub),
		pos = -increment,
		count = 0;
	
	while (-1 != (pos = strfind(string, sub, ignorecase, pos + increment)))
		count++;
	
	return count;
}