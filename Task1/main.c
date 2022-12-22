#include <stdio.h>
#include <string.h>

void printAvailableFloors(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3]);
void getDesiredFloor(int* current_floor, const int NUM_OF_FLOORS, char all_floors[NUM_OF_FLOORS][3], char target_floor[3]);

int main()
{
    printf("Elevator simulator!\n");

    const int NUM_OF_FLOORS = 6;
    char all_floors[NUM_OF_FLOORS][3] = {{"P"},{"1"},{"2"},{"3"},{"4"},{"5"}};

    char target_floor[3];
    int current_floor = 0;
    while (1)
    {
        getDesiredFloor(&current_floor, NUM_OF_FLOORS, all_floors, target_floor);
        if (target_floor[0] == 'e')
        {
            printf("Come again!\n");
            return 0;
        }
        printf("Your journey to %s begins!\n", target_floor);

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