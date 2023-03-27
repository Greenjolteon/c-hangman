/*********************
Fixed: the issue with the first guess always being wrong
Added: Round system, each one getting harder
Bugs: None that I am aware of
*********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_WORD_LENGTH 20 //this is always 20
#define NUM_WORDS 25 //this is always 25

// List of words to be used in the game
char *ewords[NUM_WORDS] = {"swim", "pie", "aid", "move", "like", "mask", "bear", "herd", "sick", "lamp", "cage",
                        "kill", "tie", "ring", "law", "whip", "air", "fly", "coal", "thin", "ruin", "toss", "owl",
                        "pan", "spy"};
char *mwords[NUM_WORDS] = {"part", "quaint", "egg", "blast", "plant", "bed", "likely", "lock", "grant", "defeat",
                        "robot", "unlike", "rotten", "writer", "season", "joint", "penny", "stake", "hero", "drop",
                        "center", "menu", "cross", "guilt", "jest"};
char *hwords[NUM_WORDS] = {"approach", "triangle", "remunerate", "ambiguity", "replacement", "voucher", "address",
                        "stunning", "plastic", "undress", "consumption", "capital", "strategic", "product", "nightmare",
                        "embrace", "capture", "auditor", "ambiguous", "artificial", "leaflet", "assessment", "brainstorm",
                        "discrimination", "syndrome"};
char *xwords[NUM_WORDS] = {"deoxyribonucleic", "entertainment", "relationship", "spokesperson", "consultation", "constituency",
                        "contradiction", "conventional", "preoccupation", "understanding", "compensation", "satisfaction",
                        "infrastructure", "characteristic", "identification", "recommendation", "concatenation", "introduction",
                        "qualification", "intelligence", "intervention", "conservative", "continuation", "concentration", "registration"};
int main() {
    char word[MAX_WORD_LENGTH];
    char guess[MAX_WORD_LENGTH];
    char diff, c;
    int num_wrong = 0;
    int word_length, i, j, max_tries, found, level;
    char hangman[8][8] = {
        {' ', '_', '_', '_', '_', '_', ' ', ' '},
        {'|', ' ', ' ', ' ', ' ', ' ', '|', ' '},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'|', '_', '_', '_', '_', '_', '|', ' '},
    }; // Hangman picture

    for (level = 1; level <= 4; level++)
    {
       
        printf("Level %d!", level);
        switch (level) {
            case 1:
                printf(" Easy: 10 wrong guesses and short words\n");
                diff = 'e';
                max_tries = 11;
                srand(time(NULL)); //starts the random selection
                strcpy(word, ewords[rand() % NUM_WORDS]); // Copies a randomly selected word from the words list to word
                word_length = strlen(word); // Gets the length of the chosen word
                break;
            case 2:
                printf(" Medium: 8 wrong guesses and medium words\n");
                diff = 'm';
                max_tries = 9;
                srand(time(NULL)); //starts the random selection
                strcpy(word, mwords[rand() % NUM_WORDS]); // Copies a randomly selected word from the words list to word
                word_length = strlen(word); // Gets the length of the chosen word
                break;
            case 3:
                printf(" Hard: 6 wrong guesses and long words\n");
                diff = 'h';
                max_tries = 7;
                srand(time(NULL)); //starts the random selection
                strcpy(word, hwords[rand() % NUM_WORDS]); // Copies a randomly selected word from the words list to word
                word_length = strlen(word); // Gets the length of the chosen word
                break;
            case 4:
                printf(" Extreme: 3 wrong guesses and very long words\n");
                diff = 'x';
                max_tries = 4;
                srand(time(NULL)); //starts the random selection
                strcpy(word, xwords[rand() % NUM_WORDS]); // Copies a randomly selected word from the words list to word
                word_length = strlen(word); // Gets the length of the chosen word
                break;
        }

        for (i = 0; i < word_length; i++)
        {
            guess[i] = '_'; // Changes each letter of the word to an underscore
        }
        guess[word_length] = '\0'; // Adds a null terminator to the end of the underscores
   
        sleep(2);
        printf("\nThis man is about to get hanged! Figure out the word to let him live:\n");
            for (i = 0; i < 7; i++) { // Displays the hangman
                for (j = 0; j < 7; j++) {
                    printf("%c", hangman[i][j]);
                }
                printf("\n");
            }
        sleep(2);

        while (num_wrong < max_tries && strcmp(word, guess) != 0) { // Loop until the word is guessed or too many wrong guesses
            printf("\nCurrent word: "); printf("%s\n", word); //Uncomment this to see the word when debugging
            for (i = 0; i < word_length; i++)
            {
                printf("%c ", guess[i]); // Display the current guessed letters
            }

            printf("\nGuess a letter: ");
            scanf(" %c", &c); //User inputs a letter

            found = 0;
            for (i = 0; i < word_length; i++)
            {
                if (word[i] == c) // If the guessed letter matches a letter in the word
                {
                    guess[i] = c; // Replaces the corresponding underscore in guess with the guessed letter
                    found = 1; // Sets found to true
                }
            }

            if (!found)
            { // If the guessed letter was not found in the word
                num_wrong++; // Increment the number of wrong guesses by 1
                printf("Wrong guess! You have %d tries left.\n", max_tries - num_wrong); // Display the number of tries remaining
                switch (num_wrong)
                {
                    case 1:
                        if (diff == 'x')
                        {
                            hangman[2][5] = 'O'; // Draw the head AND the body
                            hangman[3][5] = '|';
                        }
                        else
                        {
                            hangman[2][5] = 'O'; // Draw the head
                        }
                        break;
                    case 2:
                        if (diff == 'x')
                        {
                            hangman[3][4] = '/'; // Draw the left AND right arms
                            hangman[3][6] = '\\';
                        }
                        else
                        {
                            hangman[3][5] = '|'; // Draw the body
                        }
                        break;
                    case 3:
                        if (diff == 'x')
                        {
                            hangman[4][6] = '\\'; // Draw the right AND right legs
                            hangman[4][4] = '/';
                            printf("You lose! The word was %s.\n", word); // Display the correct word
                        }
                        else
                        {
                            hangman[3][4] = '/'; // Draw the left arm
                        }  
                        break;
                    case 4:
                        hangman[3][6] = '\\'; // Draw the right arm
                        break;
                    case 5:
                        hangman[4][6] = '\\'; // Draw the right leg
                        break;
                    case 6:
                        hangman[4][4] = '/'; // Draw the left leg
                        if (diff == 'h')
                        {
                            printf("You lose! The word was %s.\n", word); // Display the correct word
                        }
                        break;
                    case 7:
                        hangman[3][3] = '_'; //Draws the right hand
                        break;
                    case 8:
                        hangman[3][7] = '_'; //Draws the left hand
                        if (diff == 'm')
                        {
                            printf("You lose! The word was %s.\n", word); // Display the correct word
                        }
                        break;
                    case 9:
                        hangman[4][3] = '_'; //Draws the right foot
                        break;
                    case 10:
                        hangman[4][7] = '_'; //Draws the left foot
                        printf("You lose! The word was %s.\n", word); // Display the correct word
                        break;
                }
            }
            else
            {
                printf("Correct guess!\n"); // Display that the guess was correct
            }
            for (i = 0; i < 7; i++) { //Displays the hangman
                for (j = 0; j < 7; j++)
                {
                    printf("%c", hangman[i][j]);
                }
                printf("\n");
            }
        }
        if (num_wrong < max_tries)
        { // If the word was guessed before too many wrong guesses
            printf("You win! The word was %s.\n\n", word); // Display the correct word
        }
    }
    printf("Congrats! You beat the game!\n");
    return 0;
}
