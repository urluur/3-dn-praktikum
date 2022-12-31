#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void printAvailableFloors(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3]);
void getDesiredFloor(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3], char target_floor[3]);
void elevatorRide(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3], char target_floor[3], int* num_passengers);
bool getRandomBool();

int main()
{
    printf("Elevator simulator!\n");
    srand(time(NULL));

    const int NUM_OF_FLOORS = 9;
    char all_floors[NUM_OF_FLOORS][3] = {{"B3"},{"B2"},{"B1"},{"P"},{"1"},{"2"},{"3"},{"4"},{"5"}};
    int passengers = 1;

    char target_floor[3];
    int current_floor = 3;
    while (true)
    {
        getDesiredFloor(&current_floor, NUM_OF_FLOORS, all_floors, target_floor);
        if (target_floor[0] == 'e')
        {
            printf("Come again!\n");
            return 0;
        }
        elevatorRide(&current_floor, NUM_OF_FLOORS, all_floors, target_floor, &passengers);
    }
}

void getDesiredFloor(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3], char target_floor[3]){
    do
    {    
        printAvailableFloors(current_floor, NUM_OF_FLOORS, all_floors);
        printf("Enter desired floor number: ");
        scanf("%s", target_floor);

    } while 
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

void printAvailableFloors(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3]) {
    
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

void elevatorRide(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3], char target_floor[3], int* num_passengers) {
    if (strcmp(target_floor, all_floors[*current_floor]) == 0)
    {
        printf("You are already on your desired floor!\n");
        return;
    }

    printf("Your journey to floor %s begins!\n", target_floor);

    // find index of desired floor
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
    else // isn't necessary, gets rid of one xcode generated warning
    {
        printf("Unexpected error!");
        return;
    }

    while (*current_floor != target_index) {
        switch (direction)
        {
        case '+':
            *current_floor += 1;
            break;
        case '-':
            *current_floor -= 1;
            break;
        }

        if (*current_floor == target_index)
        {
            break;
        }

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

bool getRandomBool(){
    return (rand() % 2) > 0;
}