#include <stdio.h>
// char to illustrate a legitmate use of char for storing small non-char ints
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* set day of year from month & day */
int day_of_year(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 1)
        return -1;

    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    char *p = daytab[leap];

    if (day > daytab[leap][month])
        return -1;
    while (--month)
        day += *++p;

    return day;
}

/* set month, day fromday of year */
void month_day(int year, int yearday, char *pmonth, int *pday) {
    if (yearday < 1) {
        *pmonth = -1;
        *pday = -1;
        printf("month_day error: bad input\n");
        return;
    }
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    char *p = daytab[leap];

    while (yearday > *++p)
        yearday -= *p;

    if (p - *(daytab + leap) > 12 && yearday > daytab[leap][12]) {
        *pmonth = -1;
        *pday = -1;
    } else {
        *pmonth = p - *(daytab + leap);
        *pday = yearday;
    }
}

int main() {
    int year = 1970;
    int yearday = day_of_year(year, 5, 1);
    int day;
    char month;
    month_day(year, yearday, &month, &day);
    printf("day: %d, month: %d\n", day, month);
    return 0;
}
