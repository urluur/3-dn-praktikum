#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 11
#define SECRET "Luknjac"

void game(void);
bool checkWin(bool correct[MAX_LEN], int word_len);
void printGuess(bool corrwct[MAX_LEN], int word_len);

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
    
    while (!checkWin(correct, word_len) && fails < 10)
    {
        printGuess(correct, word_len);
        break; // prevents infinite loop
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
