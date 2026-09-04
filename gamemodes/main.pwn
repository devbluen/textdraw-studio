/*

    - Add Export no Grupo
    - Add Export no Grupo para Prefabs
    - Add Import de Prefabs
    - Add Rollback

*/

        // Pragmas
#pragma option          -d3 	    // Used for more accurate debugging
#pragma warning disable 208         // temporary, tag result used before definition forcing reparse
#pragma warning disable 244         // temporary, switch warning (open-mp)
#pragma warning disable 229         // temporary, index tag mismatch
// #pragma warning disable 213		    // temporary, tag mismatch: expected tags

        // Main
#include <crashdetect>
#include <open.mp>
#include <sscanf2>
#include <strlib>

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
#include <rgb>

        // Source Code
            // Utils
#include "src/utils/variables.inc"
#include "src/utils/functions.inc"
#include "src/utils/lang/lang.inc"
#include "src/utils/times.inc"

            // Libs
#include "src/libs/textdraws/interaction.inc"

            // Connections
#include "src/connections/connection.inc"

            // Exception
#include "src/general/misc/dialog/dialog.inc"
#include "src/utils/web_colors.inc"

            // General
                // Misc
#include "src/general/misc/camera/camera.inc"
#include "src/general/misc/logger/logger.inc"
#include "src/general/misc/message/message.inc"
#include "src/general/misc/exports/exports.inc"
                //
#include "src/general/auth/auth.inc"
#include "src/general/taskbar/taskbar.inc"
#include "src/general/session/session.inc"
#include "src/general/spriteBrowser/spriteBrowser.inc"
                // Misc
#include "src/general/misc/imports/imports.inc"

main() {
    print(" ");
    print("Textdraw Studio - "#STUDIO_VERSION"");
    print(" ");
}