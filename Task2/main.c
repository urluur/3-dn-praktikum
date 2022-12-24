#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 11
#define SECRET "luknjac"
#define MAX_FAILS 10

void game(void);
bool checkWin(bool correct[MAX_LEN], int word_len);
void printGuess(bool correct[MAX_LEN], int word_len);
bool checkHit(bool correct[MAX_LEN], int word_len, char guess);

int main()
{
    bool exit = false;
    char menu_choice;
    
    do { // main menu
        do {
            printf("--- Hangman ---\n's' - start\n'e' - exit\n");
            scanf(" %c", &menu_choice);
            fflush(stdin);
        } while (menu_choice != 's' && menu_choice != 'e');
        
        switch (menu_choice)
        {
            case 's':
                game();
                break;
            case 'e':
                exit = true;
            default:
                break;
        }
        
    } while (!exit);
    
    printf("Goodbye!\n");
    
    return 0;
}

void game(void)
{
    int fails = 0;
    bool correct[MAX_LEN];
    int word_len = 0;
    for (int i = 0; i < sizeof(SECRET); i++)
    {
        correct[i] = false;
        word_len++;
    }
    word_len -= 1; // eos character does not count
    char guess;
    
    while (true)
    {
        printGuess(correct, word_len);
        printf("Guess a letter! ");
        do {
            guess = getchar();
        } while (guess < 'a' || guess > 'z');
        fails += (checkHit(correct, word_len, guess)) ? 0 : 1;
        printf("Fails: %i/%i\n", fails, MAX_FAILS);
        
        if (checkWin(correct, word_len))
        {
            printf("YOU WIN!\n");
            break;
        }
        if (fails >= MAX_FAILS)
        {
            printf("YOU LOSE!\n");
            break;
        }
    }
    
}

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

void printGuess(bool correct[MAX_LEN], int word_len)
{
    for (int i = 0; i < word_len; i++)
    {
        if (correct[i])
        {
            printf("%c ", SECRET[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

bool checkHit(bool correct[MAX_LEN], int word_len, char guess)
{
    bool hit = false;
    for (int i = 0; i < word_len; i++)
    {
        if (SECRET[i] == guess)
        {
            correct[i] = true;
            hit = true;
        }
    }
    return hit;
}
