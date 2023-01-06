#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 26
#define MAX_FAILS 10

void game(void);
bool checkWin(bool correct[MAX_LEN], int word_len);
void printGuess(bool correct[MAX_LEN], int word_len, char secret[MAX_LEN]);
bool checkHit(bool correct[MAX_LEN], int word_len, char guess, char secret[MAX_LEN]);
void getSecret(char secret[MAX_LEN]);
void drawFigure(int fails);
void printAllGuesses(char allGuesses[30]);
void addGuess(char allGuesses[30], char *guess);

/**
 * Main menu for Hangman game
 * Start game by typing 's'
 * Exit by typing 'e'
*/
int main()
{
    srand(time(NULL));
    bool exit = false;
    char menu_choice;
    
    do { // main menu
        do { // waiting correct input
            printf("\n==== Hangman ====\n");
            printf("= 's' - start   =\n");
            printf("= 'e' - exit    =\n");
            printf("=================\n\n");
            
            printf("Choice: ");
            scanf(" %c", &menu_choice);
            fflush(stdin);
        } while (menu_choice != 's' && menu_choice != 'e');
        
        switch (menu_choice)
        {
            case 's':
                printf("Press ctrl-c midgame to force exit.\n\n");
                game();
                break;
            case 'e':
                exit = true;
            default:
                break;
        }
        
    } while (!exit);
    
    printf("Goodbye!\n\n");
    
    return 0;
}

/**
 * Has main game loop
 * Exits when user wins or exceeds maximum fails (MAX_FAILS)
*/
void game(void)
{
    char secret[MAX_LEN]; // secret word user tries to guess
    getSecret(secret);
    int fails = 0;

    bool correct[MAX_LEN];
    int word_len = 0;
    for (int i = 0; secret[i] != '\0'; i++) // creates a bool array for correct guesses
    {
        correct[i] = false;
        word_len++; // counts the lenght of secret word
    }
    char guess;
    char allGuesses[30] = "\0";
    
    while (true) // main game loop
    {
        printGuess(correct, word_len, secret);
        printf("Guess a letter! ");
        do {
            guess = getchar();
        } while (guess < 'a' || guess > 'z'); // user can guess only lowercase letters
        
        // if user didn't guess a letter, number of fails increases by 1
        fails += (checkHit(correct, word_len, guess, secret)) ? 0 : 1;
        
        printf("----------------------------------------\n");

        // adds guessed letter to a list and prints it out
        addGuess(allGuesses, &guess);
        printAllGuesses(allGuesses);
        drawFigure(fails);
        
        if (checkWin(correct, word_len))
        {
            printf("\n==============\n");
            printf("=  YOU WIN!  =\n");
            printf("==============\n\n");
            break;
        }
        if (fails >= MAX_FAILS)
        {
            printf("\n===============\n");
            printf("=  YOU LOSE!  =\n");
            printf("===============\n\n");
            break;
        }
        printf("\n");
    }
    
}

/**
 * Checks the array of correct guesses
 * User won if all guesses are correct
*/
bool checkWin(bool correct[MAX_LEN], int word_len)
{
    for (int i = 0; i < word_len; i++)
    {
        if (!correct[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * Prints only guessed letters in secret word
*/
void printGuess(bool correct[MAX_LEN], int word_len, char secret[MAX_LEN])
{
    for (int i = 0; i < word_len; i++)
    {
        if (correct[i])
        {
            printf("%c ", secret[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}


/**
 * Checks if guessed letter is in the secret word
 * Updates the array of indexes with correctly guessed letters (variable "correct")
*/
bool checkHit(bool correct[MAX_LEN], int word_len, char guess, char secret[MAX_LEN])
{
    bool hit = false;
    for (int i = 0; i < word_len; i++)
    {
        if (secret[i] == guess)
        {
            correct[i] = true;
            hit = true;
        }
    }
    return hit;
}

/**
 * Sets the secret word to one of strings in secrets array
*/
void getSecret(char secret[MAX_LEN])
{
    const int num_of_secrets = 10;
    char secrets[][MAX_LEN] =
    {
        {"luka"},
        {"programiranje"},
        {"praktikum"},
        {"bozic"},
        {"pocitnice"},
        {"dvatisoctriindvajset"},
        {"novoleto"},
        {"veselepraznike"},
        {"vislice"},
        {"skrivnost"}
    };
    int lucky = rand() % num_of_secrets;
    strcpy(secret, secrets[lucky]);
}

/**
 * Draws a stickman figure that corresponds to number of fails
 * When the stickman is hanged, it's game over.
 * Program prints ASCII art from file that is named after number of fails.
*/
void drawFigure(int fails)
{
    char filename[16];
    sprintf(filename, "stickman/%i.txt", fails);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open file: %s!\n", filename);
        return;
    }
    char line[30];
    while(fgets(line, sizeof(line), file) != NULL) { // reads ascii stickman from file
        printf("%s", line);
    }
    printf("\n");
    fclose(file);
}

/**
 * Prints a list of all guesses; correct and incorrect
*/
void printAllGuesses(char allGuesses[30])
{
    printf("Previous tries: ");
    for (int i = 0; allGuesses[i] != '\0'; i++)
    {
        printf("%c ", allGuesses[i]);
    }
    printf("\n");    
}

/**
 * Adds a guess to the list of all guesses
*/
void addGuess(char allGuesses[30], char *guess)
{
    for (int i = 0; ; i++)
    {
        if(allGuesses[i] == *guess)
        {
            break;
        }
        if(allGuesses[i] == '\0')
        {
            allGuesses[i] = *guess;
            allGuesses[i + 1] = '\0';
            break;
        }
    }
}