/*
 *     Assignment 1b, Bulls and cows
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// ----------- Declare functions used in main ----------

int get_player_guess();

int n_digits(int number);

int get_digit_at_position(int number, int position);

bool digit_is_in(int number, int digit);

bool is_unique_digits(int number);

int get_random_digits(int n);

int n_exact_digit_matches(int number1, int number2);

int n_digit_matches(int number1, int number2);

//------------- Program starts here --------------------
int main(void)
{
    // TODO Use functions declared above (and more) to implement the game
    // TODO Try to sketch one round, then surround with a loop.

    printf("Welcome to Bulls and Cows\n");
    printf("Try to guess a 4 digit number with digits 1-9\n");
    printf("and no repeating digits (-1 to abort).\n\n");
    printf("Bulls = correct digit(s) in correct positions.\n");
    printf("Cows = correct digit(s).\n\n");

    bool aborted = false;
    int n_guess = 0;
    int guess = 0;
    int bulls = 0;
    int cows = 0;
    int play = 1;
    int answer;
    int k = 0;
    bool unique = true;
    bool contain = true;

    // ----- The game loop ------

    while(play == 1){
        srand((unsigned int) time(NULL));
        answer = get_random_digits(4);
        printf("The correct answer is: %d\n", answer);
        bulls = 0;
        cows = 0;
        while(bulls<4){
            guess = get_player_guess();
            if (guess == -1)
            {
                aborted = true;
                printf("Game aborted\n");
                return 0;
            }

            k = n_digits(guess);
            unique = is_unique_digits(guess);
            contain = digit_is_in(guess, 0);
            cows = n_digit_matches(guess, answer);
            bulls = n_exact_digit_matches(guess, answer);

            if (!(k == 4) || contain || !unique)
            {
                printf("Bad Guess\n");
            }
            
            if ((k == 4) && !contain && unique)
            {
            n_guess++;
            printf("Cows: %d, Bulls: %d.\n" , (cows-bulls), bulls);
            }
            
            
        }
        if (aborted)
        {
            printf("Game aborted\n");
        }
        else
        {
            printf("Correct answer!\n");
            printf("Done, number was %d and you needed %d guesses\n", answer, n_guess);
        }
        
        printf("Do you want to play again? Enter 1 to play and 0 to finish: \n");
        scanf("%d", &play);
    }
    return 0;
    
}

// ------- Function definitions --------------------------------

int n_digits(int number) {
    int n_digits = 1;
    while (number > 9)
        {
            number /= 10;
            n_digits++;
        }
        return n_digits;
    } 


int get_digit_at_position(int number, int position) {

    int initialPosition = 0;

    while (number > 0) {

        if (initialPosition == position) //Initial position = desired position/Right most position
        {
            return number % 10; // Returns rightmost position
        }

        // Move to the next digit by dividing the number by 10
        number /= 10;

        // Increase the current position
        initialPosition++;
    }

    // If the loop finishes without reaching the desired position, return -1
    return -1;
}


bool digit_is_in(int number, int digit) 
{
    while (number > 0)
    {
        int n = number % 10;
        if (n == digit)
        {
            return true;
        }
        number /= 10;
    }
    return false;
}  


bool is_unique_digits(int number) {
    
    while (number > 0) // Goes through each digit of the input
    {
        int currentDigit = number % 10;
        int remainingDigits = number / 10;

        while (remainingDigits > 0) // Compare the current digit with the remaining digits
        {
            if (remainingDigits % 10 == currentDigit) {
                return false; // Digit repeated hence not unique
            }
            remainingDigits /= 10;
        }
        number /= 10; // Move to the next digit in the input number
    }

    return true;
}

int get_random_digits(int n)
{
    int y = n_digits(n);
    if (y > 1)
    {
        return 0;
    }

    int range = 1;
    int i = 1;
    while (i <= n)
    {
        range *= 10;
        i++;
    }

    bool unique = false;
    int output;
    bool nonZero;
    bool right_digits;

    while (!unique || nonZero || !right_digits)
    {
        output = rand() % range;
        unique = is_unique_digits(output);
        nonZero = digit_is_in(output, 0);
        right_digits = n_digits(output) == n;
    }

    return output;
}

int n_exact_digit_matches(int number1, int number2) {
    if (number1 < 1 || number2 < 1)
    {
        return 0;
    }

    int matches = 0;
    int position = 1; 

    while (number1 > 0 && number2 > 0) {
        int digit1 = number1 % 10;
        int digit2 = number2 % 10;

        if (digit1 == digit2) {
            matches++;
        }

        number1 /= 10;
        number2 /= 10;
        position *= 10;
    }

    return matches;
}  

int n_digit_matches(int number1, int number2) {
     int matches = 0;

    while (number1 > 0) {
        int digit1 = number1 % 10;
        int temp2 = number2;

        while (temp2 > 0) {
            int digit2 = temp2 % 10;

            if (digit1 == digit2) {
                matches++;
                break; // Because 1 match is enough
            }

            temp2 /= 10;
        }

        number1 /= 10;
    }

    return matches;
}

// TODO implement the function 'get_player_guess'

int get_player_guess()
{
    int user_input;
    printf("Guess >  ");
    scanf("%d", &user_input);
    return user_input;
};
