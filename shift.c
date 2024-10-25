#include <stdio.h>
#include <stdlib.h>

// function prototypes
int get_day_of_year(int day, int month, int year, int calendar[], int *year_total);

int main(void) {

    int calendar[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
    int day, month, year, ref_year, year_total, ref_year_total, days_since_ref, ref_day_of_year, sched;

    printf("Enter first day shift of current cycle (dd/mm/yy): ");
    scanf("%d/%d/%d", &day, &month, &ref_year);
    ref_day_of_year = get_day_of_year(day, month, ref_year, calendar, &ref_year_total);

    printf("Enter a future date:    ");
    scanf("%d/%d/%d", &day, &month, &year);
    
    if (ref_year == year) {
        days_since_ref = get_day_of_year(day, month, year, calendar, &year_total) - ref_day_of_year;
    } else {
        days_since_ref = (ref_year_total - ref_day_of_year) + get_day_of_year(day, month, year, calendar, &year_total);
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

    return 0;
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