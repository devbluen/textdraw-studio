
            // Components
#include "src/general/session/components/header.inc"

            // Includes
#include <YSI_Coding\y_hooks>

hook OnUserLogin(playerid) {

    SessionTextDraw_ShowAllForPlayer(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

            // Components
                // Functions
#include "src/general/session/components/functions/general.inc"
                    // Textdraws
#include "src/general/session/components/functions/textdraw/textdraw.inc"
#include "src/general/session/components/functions/textdraw/textdrawData.inc"
#include "src/general/session/components/functions/textdraw/textdrawExport.inc"
#include "src/general/session/components/functions/textdraw/textdrawColorPick.inc"
                    // Groups
#include "src/general/session/components/functions/groups/groups.inc"
#include "src/general/session/components/functions/groups/groupsData.inc"
                    // Players
#include "src/general/session/components/functions/player/player.inc"
#include "src/general/session/components/functions/player/playerData.inc"
                // Events
#include "src/general/session/components/events/groups/list.inc"
#include "src/general/session/components/events/groups/items.inc"
#include "src/general/session/components/events/groups/draws.inc"