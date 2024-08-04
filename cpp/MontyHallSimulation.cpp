#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;
int main()
{
    int no_of_doors = 3;
    int wins = 0, total_test = 100000, set = 5;
    int *door = new int[no_of_doors];

    cout << "\nMONTY HALL PROBLEM SIMULATION\n"
         << endl;

    cout << "No of tests in one batch : " << total_test << endl;

    srand(time(NULL));

    for (int j = 1; j <= set; j++)
    {
        cout << "\n";
        cout << "Batch " << j << ":" << endl;
        for (int i = 0; i < total_test; i++)
        {
            int doorChoice, botChoosenDoor, newBotChoosenDoor, eliminatedDoor;
            bool eliminated_a_door = false;

            memset(door, 0, no_of_doors * sizeof(int));

            doorChoice = rand() % no_of_doors;
            door[doorChoice] = 1;

            botChoosenDoor = rand() % no_of_doors;

            while (!eliminated_a_door)
            {
                int randomElimination = rand() % no_of_doors;
                if (randomElimination != botChoosenDoor && door[randomElimination] != 1)
                {
                    eliminatedDoor = randomElimination;
                    eliminated_a_door = true;
                }
            }
            for (int i = 0; i < no_of_doors; i++)
                if (i != botChoosenDoor && i != eliminatedDoor)
                    newBotChoosenDoor = i;

            if (door[newBotChoosenDoor] == 1)
                wins++;
        }
        double percentage = ((double)wins / total_test) * 100;
        cout << "Number of wins : " << wins << " out of " << total_test << endl;
        cout << "Win rate : " << (double)percentage << "%" << endl;
        wins = 0;
    }
    cout << "\n";
    delete[] door;
    return 0;
}