#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "general.h"

void Statistic(int n, Cell **Table){
    int x, y;

    static int Livecells=0;           /* Aktuális élõk száma */
    static int Generation=0;          /*Generáció száma*/

    for(y = 1; y < MAG-1; y++){ /* edge problem +1*/
        for(x = 1; x < SZEL-1; x++){
            if(Table[y][x].state)
                Livecells++;
        }
    }

    Generation++;
    if(n)
       Generation=0;

    boxRGBA(screen, 330, 620, 490, 660,/*Gen, Live*/95,0,95,255);
    char data1[30];
    sprintf(data1, "Generation: %d", Generation);
    stringRGBA(screen, 340, 628, data1, 255, 255, 255, 255);

    char data2[30];
    sprintf(data2, "Live cells: %d", Livecells);
    stringRGBA(screen, 340, 645, data2, 255, 255, 255, 255);
    Livecells=0;

}

void NAV_BOX(Coo coo){ /* Megmutatja a pályán belüli helyzetünket*/
    boxRGBA(screen, 500, 560, 600, 660,      95, 0,95, 255);
    boxRGBA(screen,501+(coo.x/10), 561+(coo.y/10), 515+(coo.x/10), 567+(coo.y/10),      139, 0,139, 255);
}

/*Törli a képernyőt úgy, hogy nullázza az élők értékét (majd meg fog állni a ciklus is) */
void Clear(Cell **Table){
    int x, y;
    for(y = 0; y < MAG; y++){
        for(x = 0; x < SZEL; x++){
                Table[y][x].state=0;
        }
    }
}

void Rand(Cell **Table){
    int x, y;
    for(y = 1; y < MAG-1; y++){
        for(x = 1; x < SZEL-1; x++){
            if(rand()%15==0)
            Table[y][x].state=1;
        }
    }

}

void Left_Click_Switch(int x, int y, int *run, Cell **Table,Coo coo){
    /*Táblba való rajzolás kezdete*/
    if (( x <1200 ) && ( y <560)){
        Draw(x,y,Table,coo);
        return;
    }

    /*Gombok, eszközök*/

    /*Draw state*/
    if(( x >=440 ) && ( y >=560) && ( x <=490) && ( y <=600) ){
        Draw_state(0);
        return;
    }
    /*Step Button*/
    if(( x >=330 ) && ( y >=560) && ( x <=430) && ( y <=600) ){
        *run=1;
        Run_Button(run);
        LOOP(Table,coo);
        return;
    }
    /*Run Button*/
    if(( x >=0 ) && ( y >=560) && ( x <=100) && ( y <=600) ){
        Run_Button(run);
        return;
    }
    /*Clear Button*/
    if(( x >=0 ) && ( y >=620) && ( x <=100) && ( y <=660) ){
        Clear(Table);
        Statistic(1,Table);
        PRINTCELLS(Table,coo);
        *run=1;
        Run_Button(run); /*Stop mindig*/
        return;
    }
    /*Rand Button*/
    if(( x >=110 ) && ( y >=620) && ( x <=210) && ( y <=660) ){
        Clear(Table);
        Rand(Table);
        Statistic(1,Table);
        PRINTCELLS(Table,coo);
        *run=1;
        Run_Button(run);
        return;
    }

    /*Témaválasztó terület*/
    if(( x >=1060 ) && ( y >=560)){ /* Kevesebb feltétel*/
        Themeselect(x,y);
        PRINTCELLS(Table,coo);
        return;
    }
}

/*Koordináták alapján rajzol életet */
void Draw(int x, int y, Cell **Table,Coo coo){

    if(Draw_state(1)){
        Table[(y/8)+coo.y][(x/8)+coo.x].state=1;
        LIVEBOX(x/8,y/8);
    }
    else{
        Table[(y/8)+coo.y][(x/8)+coo.x].state=0;
        DEADBOX(x/8,y/8);
    }
}

/*Flip-Flop és lekérdező*/
int Draw_state(int i){
    static draw=1;
    if(i)
        return draw;
    if(draw){
        draw=0;
        boxRGBA(screen, 450, 570, 480, 590,95,0,95,255);
    }
    else{
        draw=1;
        boxRGBA(screen, 450, 570, 480, 590,139,0,139,255);
    }
    return;
}
