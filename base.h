#ifndef BASE_H
#define BASE_H

#define MAG 1000
#define SZEL 1000

/* Ez egy cella típusa; state: halott=0, élõ=1, rank: élõ szomszédok száma */
typedef struct Cell{
    int state;
    int rank;
}Cell;

typedef struct Coo{
    int x;
    int y;
}Coo;

void SETUP(Cell ***Table);

void Rank_and_State_calc(Cell **Table);

void PRINTCELLS(Cell **Table, Coo coo);

void LOOP(Cell **Table,Coo coo);

#endif // BASE_H
