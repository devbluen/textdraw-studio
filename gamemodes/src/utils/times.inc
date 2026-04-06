


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Util_ConvertUnixToFullDate(timestamp, &day = 0, &month = 0, &year = 0, &hour = 0, &minute = 0, &second = 0, &weekday = 0) {
    new 
        remaining_seconds = timestamp,
        days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    ;
    
    // Calculate time components
    remaining_seconds -= (3 * 3600);
    second = remaining_seconds % 60;
    new total_minutes = remaining_seconds / 60;
    
    minute = total_minutes % 60;
    new total_hours = total_minutes / 60;
    
    hour = total_hours % 24;
    new total_days = total_hours / 24;

    // Calculate Weekday (Unix Epoch 01/01/1970 was a Thursday = 4)
    weekday = (total_days + 4) % 7;

    // Calculate Year
    year = 1970;
    while (total_days >= (Util_IsLeapYear(year) ? 366 : 365)) {
        total_days -= (Util_IsLeapYear(year) ? 366 : 365);
        year++;
    }

    // Adjust February for Leap Year
    days_in_month[1] = (Util_IsLeapYear(year) ? 29 : 28);

    // Calculate Month and Day
    month = 0;
    while (month < 12 && total_days >= days_in_month[month]) {
        total_days -= days_in_month[month];
        month++;
    }
    
    month++;           // Adjust from 0-11 to 1-12 range
    day = total_days + 1; // Adjust from 0-based to 1-based day
}

stock Util_GetWeekdayWithNumber(weekday, dest[], maxlength = sizeof dest) {

    static 
        const weekdayName[][] = {
            "Domingo", "Segunda-feira", "Terca-feira", 
            "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sabado"
        };
    
    strcat(dest, weekdayName[weekday], maxlength);
}

stock Util_GetWeekday(timestamp, dest[], maxlength = sizeof dest) {

    new weekday;

    Util_ConvertUnixToFullDate(
        .timestamp = timestamp, 
        .weekday = weekday
    );

    Util_GetWeekdayWithNumber(weekday, dest, maxlength);
}

stock Util_ConvertTimestamp(timestamp, dest[], type = -1, maxlength = sizeof dest) {

    new 
        day, 
        month, 
        year, 
        hour, 
        minute, 
        second, 
        weekday,
        weekdayName[15 + 1]
    ;

    Util_ConvertUnixToFullDate(
        .timestamp = timestamp, 
        .day = day, 
        .month = month, 
        .year = year, 
        .hour = hour, 
        .minute = minute, 
        .second = second, 
        .weekday = weekday
    );

    Util_GetWeekdayWithNumber(weekday, weekdayName);

    switch(type) {
        case 0: format(dest, maxlength, "%02d/%02d/%04d %02d:%02d", day, month, year, hour, minute);                            // return -> 00/00/0000 00:00
        case 1: format(dest, maxlength, "%02d/%02d/%04d %02d:%02d:%02d", day, month, year, hour, minute, second);               // return -> 00/00/0000 00:00:00
        case 2: format(dest, maxlength, "%02d/%02d/%04d às %02d:%02d", day, month, year, hour, minute);                         // return -> 00/00/0000 às 00:00
        case 3: format(dest, maxlength, "%02d/%02d/%04d às %02d:%02d:%02d", day, month, year, hour, minute, second);            // return -> 00/00/0000 às 00:00:00
        case 4: format(dest, maxlength, "%02d:%02d", hour, minute);                                                             // return -> 00:00
        case 5: format(dest, maxlength, "%02d:%02d:%02d", hour, minute, second);                                                // return -> 00:00:00
        case 6: format(dest, maxlength, "%02d de %s", day, weekdayName);                                                        // return -> 00 de Janeiro
        case 7: format(dest, maxlength, "%02d de %s às %02d:%02d", day, weekdayName, hour, minute);                             // return -> 00 de Janeiro às 00:00
        case 8: format(dest, maxlength, "%02d de %s às %02d:%02d:%02d", day, weekdayName, hour, minute, second);                // return -> 00 de Janeiro às 00:00:00
        case 9: format(dest, maxlength, "%02d de %s de %04d às %02d:%02d", day, weekdayName, year, hour, minute);               // return -> 00 de Janeiro de 0000 às 00:00
        case 10: format(dest, maxlength, "%02d de %s de %04d às %02d:%02d:%02d", day, weekdayName, year, hour, minute, second); // return -> 00 de Janeiro de 0000 às 00:00:00
        case 11: format(dest, maxlength, "%02d de %s de %04d", day, weekdayName, year);                                         // return -> 00 de Janeiro de 0000
        case 12: format(dest, maxlength, "Dia %02d de %04d às %02d:%02d", day, year, hour, minute);                             // return -> Dia 00 de 0000 às 00:00
        default: format(dest, maxlength, "%02d/%02d/%04d", day, month, year);                                                   // return -> 00/00/0000
    }
}

// Checks if a given year is a leap year.
static stock Util_IsLeapYear(year)
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));