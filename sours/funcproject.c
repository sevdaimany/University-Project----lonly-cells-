#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
struct energyblocks
{
    int n;
    int energy;
};

int map[12][12];
struct cell
{
    char name[20];
    int x, y;
    int energy;
    struct cell *next;
};

struct cell *Newnode(int x, int y, int energy)
{
    struct cell *newnode = (struct cell *)malloc(sizeof(struct cell));
    newnode->x = x;
    newnode->y = y;
    newnode->energy = energy;
    newnode->next = NULL;
    return newnode;
}

void pushback(int x, int y, int energy, struct cell **head)
{
    if (*head == NULL)
    {
        *head = Newnode(x, y, energy);
        return;
    }
    struct cell *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = Newnode(x, y, energy);
}

void deletnode(int x, int y, struct cell **head)
{
    if (*head == NULL)
        return;
    if (((*head)->x == x) && ((*head)->y == y))
    {
        *head = (*head)->next;
        return;
    }
    struct cell *current = *head;
    struct cell *list = NULL;
    while (current != NULL)
    {
        if ((current->x == x) && (current->y == y))
        {
            list->next = current->next;
            free(current);
            return;
        }
        list = current;
        current = current->next;
    }
}

// check is there any cell or not
int check(int x, int y, struct cell *head)
{
    struct cell *current = head;
    while (current != NULL)
    {
        if ((current->x == x) && (current->y == y))
            return -1;
        current = current->next;
    }
    return 0;
}

//check for empty place
/*int check_empty_place(int x, int y) {
    struct cell * current = head;
    for (int i = -2; i <= 0; i++) {
        for (int j = -2; j <= 0; j++) {
                while(current != NULL){
                    if((current -> x == (x + i) ) && (current ->y == (y + j)))
                     continue;
                  current = current -> next;   
                }

        }

    }
    */

int move(int x, int y, int n, struct cell *head)
{

    printf("\t\t\t\t\t[1] North\n\t\t\t\t\t[2] South\n\t\t\t\t\t[3] Northeast\n\t\t\t\t\t[4] Northwest\n\t\t\t\t\t[5] Southeast\n\t\t\t\t\t[6] Southwest\n");
    int l;
    scanf("%d", &l);
    int i, j;
    i = x;
    j = y;
    if (l == 1)
        j--;

    else if (l == 2)
        j++;
    else if (l == 3)
    {
        if (x % 2 == 0)
        {
            i++;
            j--;
        }
        else if (x % 2 == 1)
        {
            i++;
        }
    }
    else if (l == 4)
    {
        if (x % 2 == 0)
        {
            i--;
            j--;
        }
        else if (x % 2 == 1)
        {
            i--;
        }
    }
    else if (l == 5)
    {
        if (x % 2 == 0)
        {
            i++;
        }
        else if (x % 2 == 1)
        {
            i++;
            j++;
        }
    }
    else if (l == 6)
    {
        if (x % 2 == 0)
        {
            i--;
        }
        else if (x % 2 == 1)
        {
            i--;
            j++;
        }
    }

    int k = check(i, j, head);

    if ((i >= 0) && (j >= 0) && (i < n) && (j < n) && (map[j][i] != 3) && (k == 0))
    {
        struct cell *current = head;
        while (current != NULL)
        {
            if ((current->x == x) && (current->y == y))
            {
                current->x = i;
                current->y = j;
                return 0;
            }
            current = current->next;
        }
    }

    return -1;
}

int energy(int x, int y, struct cell *head, struct energyblocks energyarr[10][10])
{
    if (map[y][x] == 1)
    {
        struct cell *current = head;
        while (current != NULL)
        {
            if ((current->x == x) && (current->y == y))

            {

                if (energyarr[y][x].energy >= 15)
                {
                    current->energy += 15;
                    energyarr[y][x].energy -= 15;
                    return 0;
                }
                else if (energyarr[y][x].energy <= 0)
                    return -1;
                else if ((energyarr[y][x].energy < 15) && (energyarr[y][x].energy > 0))
                {
                    current->energy = current->energy + energyarr[y][x].energy;
                    energyarr[y][x].energy = 0;
                    return 0;
                }
            }
            current = current->next;
        }
    }
    return -1;
}

int check2(int x, int y, int n, struct cell **head)
{
    int count;
    count = check(x, y, *head);
    if ((x >= 0) && (y >= 0) && (x < n) && (y < n) && (map[y][x] != 3) && (count == 0))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int spilit(int x, int y, int r, struct cell **head)
{
    // r teedad satr ya sutun
    struct cell *current = *head;
    int n, m;
    if (map[y][x] == 2)
    {
        while (current != NULL)
        {
            if ((current->x == x) && (current->y == y))
            {
                if (current->energy >= 80)
                {
                    int u;

                    if (x % 2 == 0)
                    {
                        printf("im here1\n");
                        n = x;
                        m = y + 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            printf("im here2\n");
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        printf("im here3\n");
                        n = x;
                        m = y - 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            printf("im here4\n");
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        printf("im here5\n");
                        n = x + 1;
                        m = y;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            printf("im here6\n");
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        printf("im here7\n");
                        n = x + 1;
                        m = y + 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            printf("im here8\n");
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        printf("im here9\n");
                        n = x - 1;
                        m = y + 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            printf("im here10\n");
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        printf("im here11\n");
                        n = x - 1;
                        m = y;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            printf("im here12\n");
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }

                        return -1;
                    }

                    if (x % 2 == 1)
                    {
                        n = x;
                        m = y + 1;

                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        n = x;
                        m = y - 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }

                        n = x + 1;
                        m = y;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }

                        n = x + 1;
                        m = y - 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }

                        n = x - 1;
                        m = y - 1;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }
                        n = x - 1;
                        m = y;
                        u = check2(n, m, r, head);
                        if (u == 0)
                        {
                            deletnode(x, y, head);
                            pushback(x, y, 40, head);
                            pushback(n, m, 40, head);
                            return 0;
                        }

                        return -1;
                    }
                }
                else
                    return -1;
            }
            current = current->next;
        }
    }
    else
        return -1;
}

void MAP(struct cell *head, struct cell *head2, int n)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char *a[25] = {" /     \\      ", "/       \\_____", "\\       /     ", " \\_____/      ", "_____         ", "  ", "\\ ", " \\", " /", "/ ", "/       \\", "_____", "     ", " /     \\  *-* ", " /     \\  ^-^ ", "\\  *-*  /     ", "\\  ^-^  /     ", " \\_____/   T  ", "/   T   \\_____", " \\_____/   E  ", "/   E   \\_____", " \\_____/  XX  ", "/  XX   \\_____"};
    char *b[n * n][n];
    b[0][0] = a[5];
    if (n % 2 == 1)
    {
        for (int i = 1; i <= n / 2 + 1; i++)
        {
            b[0][i] = a[4];
        }
    }
    if (n % 2 == 0)
    {
        for (int i = 1; i <= n / 2; i++)
        {
            b[0][i] = a[4];
        }
    }
    printf("\n");
    for (int i = 1; i < 4 * n + 3; i++)
    {
        if (n % 2 == 1)
        {
            for (int j = 0; j < n / 2 + 1; j++)
            {
                if (i % 4 == 1)
                {
                    b[i][j] = a[0];
                }
                else if (i % 4 == 2)
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (j % 2 == 0)
                            b[i][j] = a[10];
                        if (j % 2 == 1)
                            b[i][j] = a[11];
                        j++;
                    }
                    b[i][j] = a[12];
                    j++;
                }
                else if (i % 4 == 3)
                {
                    b[i][j] = a[2];
                }
                else if (i % 4 == 0)
                {
                    b[i][j] = a[3];
                }
            }
        }

        else
        {
            for (int j = 0; j < n / 2; j++)
            {
                if (i % 4 == 1)
                {
                    b[i][j] = a[0];
                }
                else if (i % 4 == 2)
                {
                    b[i][j] = a[1];
                }
                else if (i % 4 == 3)
                {
                    b[i][j] = a[2];
                }
                else if (i % 4 == 0)
                {
                    b[i][j] = a[3];
                }
                if (j == n / 2 - 1)
                {
                    if (i % 4 == 3)
                    {
                        b[i][j + 1] = a[6];
                    }
                    else if (i % 4 == 0)
                    {
                        b[i][j + 1] = a[7];
                    }
                    else if ((i % 4 == 1) && (i != 1))
                    {
                        b[i][j + 1] = a[8];
                    }
                    else if ((i % 4 == 2) && (i != 2))
                    {
                        b[i][j + 1] = a[9];
                    }
                    else if (i == 1)
                    {
                        b[i][j + 1] = a[5];
                    }
                    else if (i == 2)
                    {
                        b[i][j + 1] = a[5];
                    }
                }
            }
        }
    }

    int i, j;
    //taghsim
    for (int h = 0; h < n; h++)
    {
        for (int k = 0; k < n; k++)
        {
            if (map[k][h] == 2)
            {
                if (h % 2 == 0)
                {
                    i = k * 4 + 2;
                    j = h / 2;
                    b[i][j] = a[18];
                }
                else if (h % 2 == 1)
                {
                    i = k * 4 + 4;
                    j = h / 2;
                    b[i][j] = a[17];
                }
            }
        }
    }
    // energy
    for (int h = 0; h < n; h++)
    {
        for (int k = 0; k < n; k++)
        {
            if (map[k][h] == 1)
            {
                if (h % 2 == 0)
                {
                    i = k * 4 + 2;
                    j = h / 2;
                    b[i][j] = a[20];
                }
                else if (h % 2 == 1)
                {
                    i = k * 4 + 4;
                    j = h / 2;
                    b[i][j] = a[19];
                }
            }
        }
    }
    //BLOCK
    for (int h = 0; h < n; h++)
    {
        for (int k = 0; k < n; k++)
        {
            if (map[k][h] == 3)
            {
                if (h % 2 == 0)
                {
                    i = k * 4 + 2;
                    j = h / 2;
                    b[i][j] = a[22];
                }
                else if (h % 2 == 1)
                {
                    i = k * 4 + 4;
                    j = h / 2;
                    b[i][j] = a[21];
                }
            }
        }
    }

    struct cell *current = head;

    while (current != NULL)
    {
        if (current->x % 2 == 0)
        {
            i = current->y * 4 + 3;
            j = current->x / 2;
            b[i][j] = a[15];
        }
        if (current->x % 2 == 1)
        {
            i = current->y * 4 + 5;
            j = current->x / 2;
            b[i][j] = a[13];
        }
        current = current->next;
    }
    struct cell *current2 = head2;
    while (current2 != NULL)
    {
        if (current2->x % 2 == 0)
        {
            i = current2->y * 4 + 3;
            j = current2->x / 2;
            b[i][j] = a[16];
        }
        if (current2->x % 2 == 1)
        {
            i = current2->y * 4 + 5;
            j = current2->x / 2;
            b[i][j] = a[14];
        }
        current = current->next;
    }

    //PRINT
    //system("cls");
    SetConsoleTextAttribute(hConsole, 225);
    if (n % 2 == 1)
    {
        for (int i = 0; i <= n / 2 + 1; i++)
        {
            printf("%s", b[0][i]);
        }
    }
    else if (n % 2 == 0)
    {
        for (int i = 0; i <= n / 2; i++)
        {
            printf("%s", b[0][i]);
        }
    }
    printf("\n");

    for (int i = 1; i < 4 * n + 3; i++)
    {
        if (n % 2 == 1)
        {
            for (int j = 0; j < n / 2 + 1; j++)
            {
                if (i % 4 == 2)
                {
                    for (int k = 1; k < n; k++)
                    {
                        printf("%s", b[i][j]);
                        j++;
                    }
                }
                printf("%s", b[i][j]);
            }
        }
        else
        {
            for (int j = 0; j <= n / 2; j++)
            {
                printf("%s", b[i][j]);
            }
        }
        printf("\n");
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void information(int x, int y, struct energyblocks energyarr[10][10], struct cell *head)
{

    struct cell *current = head;
    while (current != NULL)
    {
        if ((current->x == x) && (current->y == y))
        {
            printf("\t\t\t\t\tCELL INFORMATION:\n");
            printf("\t\t\t\t\t(%d, %d)\n", x, y);
            printf("\t\t\t\t\tCELL ENERGY: %d\n", current->energy);
        }
        current = current->next;
    }
    if (energyarr[y][x].n == 1)
    {
        printf("\t\t\t\t\tHOMES ENERGY: %d\n", energyarr[y][x].energy);
    }
}

void playgame(struct cell *head, struct cell *head2, int n, struct energyblocks energyarr[10][10])
{
    while (1)
    {
        int e;
        printf("\t\t\t\t\tPlease choose one of your celles:\n");
        fflush(stdin);
        int x, y;
        scanf("(%d, %d)", &x, &y);
        getchar();
        information(x, y, energyarr, head);
        printf("\t\t\t\t\t[1] Move\n\t\t\t\t\t[2] Split a cell\n\t\t\t\t\t[3] Boost eneregy\n\t\t\t\t\t[4] Save\n\t\t\t\t\t[5] Exit\n\t\t\t\t\t\n");
        int k;
        scanf("%d", &k);

        if (k == 1)
        {
            e = move(x, y, n, head);
            if (e == 0)
            {
                MAP(head, head2, n);
            }
            else
            {
                printf("Can not do such a work\n");
                playgame(head, head2, n, energyarr);
            }
        }
        else if (k == 2)
        {
            e = spilit(x, y, n, &head);
            if (e == 0)
            {
                MAP(head, head2, n);
            }
            else if (e == -2)
            {
                printf("Here is not the correct room\n");
                playgame(head, head2, n, energyarr);
            }
            {
                printf("Can not do such a work\n");
                playgame(head, head2, n, energyarr);
            }
        }
        else if (k == 3)
        {
            e = energy(x, y, head, energyarr);
            if (e == 0)
            {
                printf("\t\t\t\t\tEnergy has boosted.\n");
            }
            else
            {
                printf("\t\t\t\t\tCannot boost the energy.choose again.\n");
                playgame(head, head2, n, energyarr);
            }
        }
        else if (k == 5)
        {
            printf("\t\t\t\t\tFINISH");
            exit(0);
        }
    }
}
int energy_sum(struct cell *head)
{
    struct cell *current = head;
    int sum = 0;
    while (current != NULL)
    {
        sum += current->energy;
        current = current->next;
    }
    return sum;
}
void playgame2(struct cell *head, struct cell *head2, int n, struct energyblocks energyarr[10][10])
{
    while (1)
    {
        printf("\t\t\t\t\t[1] Load\n\t\t\t\t\t[2] New single player game\n\t\t\t\t\t[3] New Multiplayer game\n\t\t\t\t\t[4] Exit\n\t\t\t\t\t");
        int p;
        scanf("%d", &p);
        if (p == 2)
        {
            printf("\t\t\t\t\tHow many cells do u need ?\n");
            int cells_num;
            scanf("%d", &cells_num);
            int x1, y1;
            int o = 0, c;
            while (o < cells_num)
            {
                x1 = rand() % n;
                y1 = rand() % n;
                while (map[y1][x1] == 3)
                {
                    x1 = rand() % n;
                    y1 = rand() % n;
                }
                c = check(x1, y1, head);
                if (c == 0)
                {

                    pushback(x1, y1, 0, &head);
                    o++;
                }
            }
            MAP(head, head2, n);
            playgame(head, head2, n, energyarr);
        }
    }
}