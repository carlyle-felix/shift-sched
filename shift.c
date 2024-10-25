/***********************************************************************************************************
 * Track continental shift pattern:    Use a given date as a reference to display schedule for given dates *
 *                                   or display a monthly calendar populated with shift pattern.           *                       
 * Author:  Carlyle Felix                                                                                  *
 ***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// function prototypes
int get_day_of_year(int day, int month, int year, int calendar[], int *year_total);
void check_date(int ref_year, int ref_day_of_year, int ref_year_total, int calendar[], int ref_day_of_week);
void view_month(int ref_year, int ref_day_of_year, int ref_year_total, int calendar[], int ref_day_of_week);

int main(void) {

    int calendar[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
    int day, month, year, year_total, day_of_year, day_of_week;
    char c, choice;

    // get reference date
    printf("Enter first day shift of current cycle (dd/mm/yy): ");
    scanf("%d/%d/%d", &day, &month, &year);
    printf("Enter day of week for first day shift (Sun: 1 — Sat: 7): ");
    scanf("%d", &day_of_week);

    day_of_year = get_day_of_year(day, month, year, calendar, &year_total);
    
    for (;;) {

        printf("\nCheck date, View month or Quit?\n(C/V/Q): ");
        while ((c = toupper(getchar())) != 'C' && c != 'Q' && c != 'V');
        if (c == 'C')   check_date(year, day_of_year, year_total, calendar, day_of_week - 1);
        if (c == 'V')   view_month(year, day_of_year, year_total, calendar, day_of_week - 1);
        if (c == 'Q')   break;
    }
    return 0;
}

// display monthly calendar for a given month populated with shift pattern
void view_month(int ref_year, int ref_day_of_year, int ref_year_total, int calendar[], int ref_day_of_week) {

    int i, day = 1, month, year, year_total, days_since_ref, sched, day_of_week;
    char c, shift_pattern[8] = {'D', 'D', 'N', 'N', 'O', 'O', 'O', 'O'};
    
    printf("Enter future month(mm/yy): ");
    scanf("%d/%d", &month, &year);

    for (;;) {
        if (ref_year == year) {
            days_since_ref = get_day_of_year(day, month, year, calendar, &year_total) - ref_day_of_year;
        } else {
            days_since_ref = (ref_year_total - ref_day_of_year) + get_day_of_year(day, month, year, calendar, &year_total);
        }
        int calendar_month[calendar[month - 1]];
        
        day_of_week = (days_since_ref - ref_day_of_week) % 7;

        printf("\n%d/%d\n", month, year);
        printf(" Sun   Mon   Tue   Wed   Thu   Fri   Sat\n");
        for (i = 0; i < calendar[month - 1] + day_of_week; i++) {
            if (i < day_of_week) {
                printf("      ");
            } else {
                calendar_month[i - day_of_week] = i + 1 - day_of_week;
                sched = days_since_ref++ % 8;
                printf("%2d.%-3c", calendar_month[i - day_of_week], shift_pattern[sched]);
            }
            if (i == 6) {
                printf("\n");
            } else if (i > 7 && (i + 1) % 7 == 0) {
                printf("\n");
            }
        }

        printf("\nView following month, Return or Quit?\n(V/R/Q): ");
        while ((c = toupper(getchar())) != 'V' && c != 'R' && c != 'Q');

        if (c == 'V') {
            if (month < 12) {
                month++;
            } else {
                year++;
                month = 1;
            }
            continue;
        } 
        else if (c == 'R')  break;
        else if (c == 'Q')  exit(EXIT_SUCCESS);
    
    }
    
}

// display shift schedule for a given date
void check_date(int ref_year, int ref_day_of_year, int ref_year_total, int calendar[], int ref_day_of_week) {

    int day, month, year, year_total, days_since_ref, sched, day_of_week;

    printf("Enter a future date (dd/mm/yy):    ");
    scanf("%d/%d/%d", &day, &month, &year);
    
    if (ref_year == year) {
        days_since_ref = get_day_of_year(day, month, year, calendar, &year_total) - ref_day_of_year;
    } else {
        days_since_ref = (ref_year_total - ref_day_of_year) + get_day_of_year(day, month, year, calendar, &year_total);
    }

    day_of_week = (days_since_ref - ref_day_of_week) % 7;
    switch (day_of_week) {
        case 0:     printf("\nSunday, ");
                    break;
        case 1:     printf("\nMonday, ");
                    break;
        case 2:     printf("\nTuesday, ");
                    break;
        case 3:     printf("\nWednesday, ");
                    break;
        case 4:     printf("\nThursday, ");
                    break;
        case 5:     printf("\nFriday, ");
                    break;
        case 6:     printf("\nSaturday, ");
                    break;
    }

    sched = days_since_ref % 8;
    switch (sched) {
        case 0:     printf("First day shift\n");
                    break;
        case 1:     printf("Second day shift\n");
                    break;
        case 2:     printf("First night shift\n");
                    break;
        case 3:     printf("Second night shift\n");
                    break;
        case 4:     printf("First off day\n");
                    break;
        case 5:     printf("Second off day\n");
                    break;
        case 6:     printf("Third off day");
                    break;
        case 7:     printf("forth off day");
                    break;
    }
}

// find number of days since the first day of the year
int get_day_of_year(int day, int month, int year, int calendar[], int *year_total) {

    int i, day_of_year;

    // garbage in, garbage out
    if (day == 0 || month == 0) {
        printf("Invalid date.\n");
        exit(EXIT_FAILURE);
    }

    // check leap year
    if (year % 24 == 0) {
        *year_total = 366;
        calendar[1] = 29;
    } else {
        *year_total = 365;
        calendar[1] = 28;
    }

    day_of_year = day;
    for (i = 0; i < month - 1; i++) {
        day_of_year += calendar[i];
    }

    return day_of_year;
}