
        // Pragmas
#pragma option          -d3 	    // Used for more accurate debugging
#pragma warning disable 208		    // temporary, tag result used before definition forcing reparse
#pragma warning disable 244		    // temporary, switch warning (open-mp)
#pragma warning disable 213		    // temporary, tag mismatch: expected tags
#pragma warning disable 229         // temporary, index tag mismatch
// #pragma warning disable 234		// temporary, deprecated functions (open-mp) - Remove after change auth to googleAuth
// #pragma warning disable 239		// temporary, literal array/string passed to a non-const parameter

        // Main
#include <open.mp>
#include <sscanf2>

        // Definers
#define  CGEN_MEMORY  60000

        // YSI Library
#include <YSI_Data\y_iterate>
#include <YSI_Data\y_foreach>
#include <YSI_Coding\y_va>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_inline>

        // Misc
#include <easyDialog>
#include <textdraw-simple-click>
#include <zcmd>

        // Source Code
            // Utils
#include "src/utils/variables.inc"
#include "src/utils/functions.inc"

            // Connections
#include "src/connections/connection.inc"

            // Exception
#include "src/general/misc/dialog/dialog.inc"

            // General
#include "src/general/auth/auth.inc"
#include "src/general/taskbar/taskbar.inc"
#include "src/general/session/session.inc"
                // Misc
#include "src/general/misc/logger/logger.inc"
#include "src/general/misc/message/message.inc"

main() {
    print(" ");
    print("Textdraw Studio - "#STUDIO_VERSION"");
    print(" ");
}