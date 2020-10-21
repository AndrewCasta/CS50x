#include <stdio.h>
#include <cs50.h>


int main(void)
{

    // prompt for credit card number

    // check sum for valid/not

    // check if VISA, AMEX or MC

    // print result

    // =========== //

    // prompt for credit card number
    long cardNum = get_long("Please enter your credit card number: ");


    // Card validation

    // set all card numbers (max 16)
    int cardNum1 = (cardNum % 10);
    int cardNum2 = (cardNum % 100) / 10;
    int cardNum3 = (cardNum % 1000) / 100;
    int cardNum4 = (cardNum % 10000) / 1000;
    int cardNum5 = (cardNum % 100000) / 10000;
    int cardNum6 = (cardNum % 1000000) / 100000;
    int cardNum7 = (cardNum % 10000000) / 1000000;
    int cardNum8 = (cardNum % 100000000) / 10000000;
    int cardNum9 = (cardNum % 1000000000) / 100000000;
    int cardNum10 = (cardNum % 10000000000) / 1000000000;
    int cardNum11 = (cardNum % 100000000000) / 10000000000;
    int cardNum12 = (cardNum % 1000000000000) / 100000000000;
    int cardNum13 = (cardNum % 10000000000000) / 1000000000000;
    int cardNum14 = (cardNum % 100000000000000) / 10000000000000;
    int cardNum15 = (cardNum % 1000000000000000) / 100000000000000;
    int cardNum16 = (cardNum % 10000000000000000) / 1000000000000000;

    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    int check1 =
        (cardNum2 * 2 % 10) + (cardNum2 * 2 % 100) / 10 +
        (cardNum4 * 2 % 10) + (cardNum4 * 2 % 100) / 10 +
        (cardNum6 * 2 % 10) + (cardNum6 * 2 % 100) / 10 +
        (cardNum8 * 2 % 10) + (cardNum8 * 2 % 100) / 10 +
        (cardNum10 * 2 % 10) + (cardNum10 * 2 % 100) / 10 +
        (cardNum12 * 2 % 10) + (cardNum12 * 2 % 100) / 10 +
        (cardNum14 * 2 % 10) + (cardNum14 * 2 % 100) / 10 +
        (cardNum16 * 2 % 10) + (cardNum16 * 2 % 100) / 10;

    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    int check2 = cardNum1 + cardNum3 + cardNum5 + cardNum7 + cardNum9 + cardNum11 + cardNum13 + cardNum15;
    int checkSum = check1 + check2;

    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!


    // determine credit card provider

    // American Express - 15-digit - start with 34 or 37
    int amCard15 = (cardNum % 1000000000000000) / 10000000000000;
    // MasterCard - 16-digit - start with 51, 52, 53, 54, or 55
    int mCard16 = (cardNum % 10000000000000000) / 100000000000000;
    // Visa - 13 & 16-digit - start with 4
    int vCard13 = cardNum13;
    int vCard16 = cardNum16;


    // Final check & output

    // check if card is valid
    if ((checkSum % 10 == 0))
    {
        // if valid, determine card type & print
        if (amCard15 == 34 || amCard15 == 37)
        {
            printf("AMEX\n");
        }
        else if (mCard16 == 51 || mCard16 == 52 || mCard16 == 53 || mCard16 == 54 || mCard16 == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (vCard13 == 4 || vCard16 == 4)
        {
            printf("VISA\n");
        }
        // if not valid card prefix, print invalid
        else
        {
            printf("INVALID\n");
        }
    }
    // if not valid checksum, print invalid
    else
    {
        printf("INVALID\n");
    }


}
