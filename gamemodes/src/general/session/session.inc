
            // Components
#include "src/general/session/components/header.inc"



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Session_Create(uniqueId) {
    e_Session[E_SESSION_ID] = uniqueId;

    SessionTextdrawData_LoadAll();
    SessionTextdraw_UpdateButtonAll();
}

stock Session_Destroy() {
    e_Session[E_SESSION_ID] = 0;

    SessionTextdraw_DestroyAll();
}

stock Session_GetId()
    return e_Session[E_SESSION_ID];

stock bool:Session_Has()
    return Session_GetId() > 0;



            // Components
                // Functions
#include "src/general/session/components/functions/textdraw.inc"
#include "src/general/session/components/functions/textdrawData.inc"