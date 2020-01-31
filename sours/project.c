#include "funcproject.h"

int main()
{

    struct cell *head = NULL;
    struct cell *head2 = NULL;
    srand(time(NULL));
    struct energyblocks energyarr[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            energyarr[i][j].n = 0;
            energyarr[i][j].energy = 0;
        }
    }
    int n;
    playgame2(&head,&head2,n,energyarr);
}
