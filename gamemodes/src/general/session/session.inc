
            // Components
#include "src/general/session/components/header.inc"

            // Includes
#include <YSI_Coding\y_hooks>

hook OnUserLogin(playerid) {

    SessionTextDraw_ShowAlLForPlayer(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

            // Components
                // Functions
#include "src/general/session/components/functions/general.inc"
#include "src/general/session/components/functions/textdraw.inc"
#include "src/general/session/components/functions/textdrawData.inc"
#include "src/general/session/components/functions/textdrawExport.inc"
#include "src/general/session/components/functions/groups.inc"
#include "src/general/session/components/functions/groupsDataDraws.inc"
                // Events
#include "src/general/session/components/events/groups/list.inc"
#include "src/general/session/components/events/groups/items.inc"
#include "src/general/session/components/events/groups/draws.inc"