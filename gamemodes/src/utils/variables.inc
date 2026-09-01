
    // Informations
#define     STUDIO_VERSION       "v1.6.0"
#define     STUDIO_FOLDER        "textdrawStudio"
#define     STUDIO_EXPORT        "exports"
#define     STUDIO_IMPORT        "imports"

    // Custom Tags
        // Messages
#define     MESSAGE_RED         "{f72d2d}[X]: {FFFFFF}"
#define     MESSAGE_GREEN       "{52b8f2}[!]: {FFFFFF}"

        // Colors
#define     TEXTDRAW_HOVER      0x303030FF
#define     TEXTDRAW_FEEDBACK   0x9428c9FF
#define     HEX_DEFAULT         "badc58"    // d4af37
#define     HEX_INFO            "f24f1d"

        // Custons
#define     DIALOG_LINE         "==============================="

new
    DB:IDConnection,
    strcatString[1024 * 4]
;

new
    Iterator:Users<MAX_PLAYERS>
;

    // Macros
#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define strcatEx(%0,%1,%2) \
    format(strcatString, sizeof strcatString, %1, %2), strcat(%0, strcatString)