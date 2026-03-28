
#define     STUDIO_VERSION     "v1.0.0"

    // Custom Tags
#define     MESSAGE_RED     "{f72d2d}[!]: {FFFFFF}"
#define     MESSAGE_GREEN   "{52b8f2}[!]: {FFFFFF}"
#define     TEXTDRAW_HOVER  0x303030FF

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