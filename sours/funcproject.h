#include "funcproject.c"

struct cell *Newnode(int x, int y, int energy);

void pushback(int x, int y, int energy, struct cell **head);

void deletnode(int x, int y, struct cell **head);

int check(int x, int y, struct cell *head,struct cell *head2);

int move(int x, int y, int r, struct cell *head,struct cell *head2);

int energy(int x, int y, struct cell *head, struct energyblocks energyarr[10][10]);

int spilit(int x, int y, int r, struct cell **head,struct cell **head2);

void MAP(struct cell *head, struct cell *head2, int n);

void playgame(struct cell *head, struct cell *head2, int n, struct energyblocks energyarr[10][10]);

void information(int x, int y,struct energyblocks energyarr[10][10],struct cell *head);

int check2(int x, int y, int n, struct cell **head,struct cell **head2);

int energy_sum(struct cell *head);

void playgame2(struct cell **head, struct cell **head2, int n, struct energyblocks energyarr[10][10]);

void playgame3(struct cell *head, struct cell *head2, int n, struct energyblocks energyarr[10][10],int turn);

void load(struct energyblocks energyarr[10][10], int *n, int *turn, int select, struct cell **head, struct cell **head2, int *player_num);

void save(struct cell *head, struct cell *head2, struct energyblocks energyarr[10][10], int player_num, int turn, int cell1_num, int cell2_num, int n);

int cellnum(struct cell *head);
