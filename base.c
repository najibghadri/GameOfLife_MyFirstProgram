#include <stdio.h>
#include <stdlib.h>

#include "base.h"

void SETUP(Cell ***Table){
    Cell **New;
    /* Foglalás */
    do{
        int y;
        New=(Cell**)calloc(MAG, sizeof(Cell*));
        New[0]=(Cell*)calloc(MAG * SZEL, sizeof(Cell));
        for(y = 1; y < MAG; y++)
            New[y] = New[0] + y * SZEL;
    }while(New == NULL);
    *Table=New;
}

/* Kiszámolja az egyes cellák fokszámát, majd az életjelet*/
void Rank_and_State_calc(Cell **Table){
    int x, y;
    /*Rank_Calc*/
    /* Lenullázott rankok a State_calc alatt, hogy megkapjuk a tényleges mostanit.*/
    /* Kiszámolja a cellák rangját: az élõ, szomszédos cellák száma. */
    for(y = 1; y<MAG-1; y++){ /* edge problem +-1 */
        for(x = 1; x<SZEL-1; x++){
            if(Table[y][x].state){
                Table[y-1][x].rank++;
                Table[y+1][x].rank++;

                Table[y-1][x+1].rank++;
                Table[y+1][x+1].rank++;
                Table[y][x+1].rank++;

                Table[y-1][x-1].rank++;
                Table[y+1][x-1].rank++;
                Table[y][x-1].rank++;
            }
        }
    }
    /*State_Calc*/
    /* A cella életjelét a játékszabály szerint megváltoztatja; a rang alapján élõ vagy halott sejt. */
    for(y = 1; y < MAG-1; y++){ /* edge problem +1*/
        for(x = 1; x < SZEL-1; x++){
            if(Table[y][x].rank == 3)
                Table[y][x].state=1;
            else if (Table[y][x].rank != 2)
                Table[y][x].state=0;

            Table[y][x].rank=0; /*Nullázás a következő Rank_calc számára: lenullázás - egy ciklussal kevesebb*/
        }
    }
}

/* Kiírja a tömböt SDL-ben*/
void PRINTCELLS(Cell **Table, Coo coo){
    /* 150*70-es a táblázatunk ezen bellül a mozgatást az xcoo és ycoo koordináták alapján mozgtajuk */
    int x, y;
    for(y = coo.y; y < coo.y+70; y++){
        for(x = coo.x; x < coo.x+150; x++){
           if(Table[y][x].state)
                LIVEBOX(x-coo.x,y-coo.y);
            else
                DEADBOX(x-coo.x,y-coo.y);
        }
    }
}

void LOOP(Cell **Table,Coo coo){ /*Futtató függvény- egy lépéssel egyenlő a futtatása */
    Rank_and_State_calc(Table);/* 1.-2. ciklus Sorrend: várás, rank számolás amiből a state számolható, majd nullázás és  egyből kiírás */
    Statistic(0,Table);/* 3. ciklus élet-generáció*/
    PRINTCELLS(Table,coo);/* 4. ciklus ami körbejárja az egy tömböt*/
    return;
}
