#include <cs50.h>
#include <stdio.h>

int add_digit(int digit[], int count);
int main(void)
{

    long n = get_long("Number: ");
    long n1 = n;
    long n2 = n;
    int count = 0;
    do
    {
        n1 /= 10;
        count++;
    } while (n1 > 0);

    int digit[count];
    for (int i = 0; i < count; i++)
    {
        digit[i] = n2 % 10;
        n2 /= 10;
    }
    int sum = 1;
    if (count == 15)
    {
        // American Express
        if ((digit[14] == 3 && digit[13] == 4) || (digit[14] == 3 && digit[13] == 7))
        {
            sum = add_digit(digit, count);
            if (sum % 10 == 0)
            {
                printf("AMEX\n");
                return 0;
            }
        }
    }
    else if (count == 16)
    {
        // MasterCard || Visa
        if (digit[15] == 5)
        {
            if (1 <= digit[14] && digit[14] <= 5)
            {
                sum = add_digit(digit, count);
                if (sum % 10 == 0)
                {
                    printf("MASTERCARD\n");
                    return 0;
                }
            }
        }

        if (digit[15] == 4) {
            sum = add_digit(digit, count);
            if (sum % 10 == 0) {
                printf("VISA\n");
                return 0;
            }
        }
    }
    else if (count == 13)
    {
        // Visa
        if (digit[12] == 4)
        {
            sum = add_digit(digit, count);
            if (sum % 10 == 0)
            {
                printf("VISA\n");
                return 0;
            }
        }
    }
    printf("INVALID\n");
    return 0;
}

int add_digit(int digit[], int count)
{
    int sum = 0;
    for (int i = 0; i < count; i += 2)
    {
        sum += digit[i];
    }
    for (int i = 1; i < count; i += 2)
    {
        int tmp = digit[i] * 2;
        if (tmp >= 10) {
            sum += tmp % 10;
            sum += tmp / 10;
        } else {
            sum += tmp;
        }

    }
    return sum;
}