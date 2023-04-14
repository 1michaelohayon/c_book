#include <stdio.h>

/* print Celsius-Fahrenheit table
        for celsius = -10, -0, ..., 70 */
void print_table(int lower, int upper, int step);
float fehrenheit(int celsius);

/* lower limit of temperature table */
/* upper limit */
/* step size */
int main() {
    printf("Celsius Fahr\n");
    print_table(-10, 70, 7);
    return 0;
}
float fehrenheit(int celsius) { return celsius * 9.0 / 5.0 + 32.0; }

char x = 'A';
void print_table(int l, int u, int s) {

    float celsius = l;
    while (celsius <= u) {
        printf("%3.0f\t%6.1f\n", celsius, fehrenheit(celsius));
        celsius += s;
    }
}
