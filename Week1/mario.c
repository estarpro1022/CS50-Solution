#include <cs50.h>
#include <stdio.h>

void printHash(int n);
int main(void)
{
    int height;
    do {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    printHash(height);
    return 0;


}

void printHash(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }
}