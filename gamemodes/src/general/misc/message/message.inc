


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SendMessage(playerid, color, const message[], {Float, _}:...) {

    new message_buff[148 + 1];
    format(message_buff, sizeof message_buff, message, ___(3));

    if(playerid == INVALID_PLAYER_ID) {
        foreach(new i: Users) {
            Util_ClearChat(i);
            SendClientMessage(i, color, message_buff);
        }
    } else {
        Util_ClearChat(playerid);
        SendClientMessage(playerid, color, message_buff);
    }
    return true;
}