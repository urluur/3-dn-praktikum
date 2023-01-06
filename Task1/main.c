#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_FLOORS 9
#define MAX_PASSENGERS 10

void printAvailableFloors(int* current_floor, char all_floors[NUM_OF_FLOORS][3]);
void getDesiredFloor(int* current_floor, char all_floors[NUM_OF_FLOORS][3], char target_floor[3]);
void elevatorRide(int* current_floor, char all_floors[NUM_OF_FLOORS][3], char target_floor[3], int* num_passengers);
bool getRandomBool();

/**
 * Main menu for the simulator
 * Waits for user to input one available floor
 * or 'e' to exit the program.
*/
int main()
{
    printf("Elevator simulator!\n");
    srand(time(NULL));

    char all_floors[][3] = {{"B3"},{"B2"},{"B1"},{"P"},{"1"},{"2"},{"3"},{"4"},{"5"}};
    int passengers = 1;

    char target_floor[3];
    int current_floor = 3; // "P" in all_floors array
    while (true) // Gets desired floor until user wants to exit
    {
        getDesiredFloor(&current_floor, all_floors, target_floor);
        if (target_floor[0] == 'e')
        {
            printf("Come again!\n");
            return 0;
        }
        elevatorRide(&current_floor, all_floors, target_floor, &passengers); 
    }
}

/**
 * Gets a floor number user want to go to
*/
void getDesiredFloor(int* current_floor, char all_floors[NUM_OF_FLOORS][3], char target_floor[3]){
    do
    {    
        printAvailableFloors(current_floor, all_floors);
        printf("Enter desired floor number: ");
        scanf("%s", target_floor);

    } while // Asks for input until it's a valid floor number
    (
        (
            strcmp("e", target_floor) != 0 &&
            strcmp("P", target_floor) != 0
        )
        &&
        (
            strcmp("1", target_floor) > 0 ||
            strcmp("5", target_floor) < 0
        )
        &&
        (
            strcmp("B1", target_floor) > 0 ||
            strcmp("B3", target_floor) < 0
        )
    );
}

/**
 * Prints all floors except the current floor
*/
void printAvailableFloors(int* current_floor, char all_floors[NUM_OF_FLOORS][3]) {
    
    printf("Available floors: ");
    for (int i = 0; i < NUM_OF_FLOORS; i++)
    {
        if (i == *current_floor)
        {
            continue;
        }
        printf("%s ", all_floors[i]);
    }
    printf("\ne - exit\n");
}

/**
 * Moves the elevator towards target floor
 * User can decide to get out early
 * Random passengers can join or leave the elevator
 * Maximum number of passengers is MAX_PASSENGERS
*/
void elevatorRide(int* current_floor, char all_floors[NUM_OF_FLOORS][3], char target_floor[3], int* num_passengers) {
    if (strcmp(target_floor, all_floors[*current_floor]) == 0)
    {
        printf("You are already on your desired floor!\n");
        return;
    }

    printf("Your journey to floor %s begins!\n", target_floor);

    // Find index of desired floor
    int target_index = 0;
    for (int i = 0; i < NUM_OF_FLOORS; i++)
    {
        if (strcmp(target_floor, all_floors[i]) == 0)
        {
            target_index = i;
        }
    }

    char direction;
    if (target_index > *current_floor)
    {
        printf("Elevator starts moving up...\n");
        direction = '+';
    }
    else if (target_index < *current_floor)
    {
        printf("Elevator starts moving down...\n");
        direction = '-';
    }
    else // Isn't necessary, gets rid of one xcode generated warning
    {
        printf("Unexpected error!");
        return;
    }

    while (*current_floor != target_index) {
        printf("---------------\n");

        switch (direction)
        {
        case '+':
            *current_floor += 1;
            break;
        case '-':
            *current_floor -= 1;
            break;
        }

        // User arrived to their destination
        if (*current_floor == target_index)
        {
            break;
        }

        // Chance of someone leaving the elevator
        if (getRandomBool() && *num_passengers > 1)
        {
            printf("A passenger riding with you leaves the elevator on the %s. floor.\n", all_floors[*current_floor]);
            *num_passengers -= 1;
        }

        // Chance of someone getting on the elevator
        if (getRandomBool() && *num_passengers < MAX_PASSENGERS)
        {
            printf("New passenger from the %s. floor gets on the elevator.\n", all_floors[*current_floor]);
            *num_passengers += 1;
        }

        if (*num_passengers == 1)
        {
            printf("You are the only passenger on the elevator.\n");
        }
        else
        {
            printf("There are %i passengers on the elevator.\n", *num_passengers);
        }

        /**
         * Asks user if they want to leave
         * Press key 'y' to stop
         * Press any other character to continue the ride
         * */
        char stop;
        printf("Do you want to stop at floor %s? y/n\n", all_floors[*current_floor]);
        scanf(" %c", &stop);
        fflush(stdin);
        if (stop == 'y')
        {
            break;
        }
    }
    printf("Doors open. You are at your destination. (floor: %s)\n", all_floors[*current_floor]);
}

/**
 * Returns random true or false
*/
bool getRandomBool(){
    return (rand() % 2) > 0;
}