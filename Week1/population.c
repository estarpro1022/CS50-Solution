#include <cs50.h>
#include <stdio.h>

int get_start_size();

int get_end_size(int start);
int main(void)
{
    // TODO: Prompt for start size
    int start = get_start_size();

    // TODO: Prompt for end size
    int end = get_end_size(start);

    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    while (end > start)
    {
        start += (start / 3 - start / 4);
        year++;
    }
    // TODO: Print number of years
    printf("%i\n", year);
}

int get_start_size() {
    int n = 0;
    do
    {
        n = get_int("Start Size: ");
    }
    while (n < 9);
    return n;
}

int get_end_size(int start) {
    int n = 0;
    do
    {
        n = get_int("End Size: ");
    }
    while (n < start);
    return n;
}
