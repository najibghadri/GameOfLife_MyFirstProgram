#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <string.h>

#include "general.h"

SDL_Surface *screen;
SDL_Event event;

void mySDLeventhandler(int *exit, Coo *plus,int *run, Cell **Table,Coo *coo){
    static int click=0;
    int x, y;
    while(SDL_PollEvent(&event)){ /*Szünetmentes eseménykezelés*/
        switch(event.type){
            case SDL_QUIT:
                *exit=1;
                return; /*Ki fog lépni az egész ciklusból > free > exit */
            case SDL_KEYDOWN:
                switch(event.key.keysym.unicode){
                    case 'a':
                      plus->x = -1;
                      break;
                    case 'd':
                      plus->x = 1;
                      break;
                    case 'w':
                      plus->y = -1;
                      break;
                    case 's':
                      plus->y = 1;
                      break;
                    default:
                      break;
                   }
                   return;
            case SDL_KEYUP:
                plus->y = 0;
                plus->x = 0;
                return;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) { /*Bal egérnyomás -> gombok vizsgálata*/
                    click = 1;
                    x = event.button.x;
                    y = event.button.y;

                    Left_Click_Switch(x,y,run,Table,*coo);
                    SDL_Flip(screen);
                }
                return;

            /* egergomb elengedese */
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = 0;
                }
                return;

            /* eger mozdulat */
            case SDL_MOUSEMOTION:

                x=event.motion.x;
                y=event.motion.y;

                /*Sebesség tologató*/
                if(click && ( x >=115 ) && ( y >=560) && ( x <=315) && ( y <=600))
                    Speed_slider(x);
                /*Táblba való rajzolás folytatása*/
                if (click && ( x <1200 ) && ( y <560))
                    Draw(x,y,Table,*coo);
                SDL_Flip(screen);
                return;
        }
    }
}

/*  */
int main(int argc, char *argv[]){

    /* Globális változók, mivel az egész program alatt csak rájuk hivatkozunk */
    Cell **Table;
    Coo coo={430,450}; /*Mozgatható pálya kezdeti koordinátái */

    /* SDL és minden más inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(1200, 660, 0, SDL_ANYFORMAT);
      if(!screen){
        exit(1);
      }
    SDL_WM_SetCaption("Conway's Game Of Life - by Ghadri Najib", "Game Of Life"); /*Fejléc*/
    SDL_EnableUNICODE(1);  /*Billenytűzent bemenetéhez*/
    srand(time(0));

    SETUP(&Table);  /* Tömb lefoglalása */

    MENULOAD();
    NAV_BOX(coo);
    Statistic(1,Table);
    PRINTCELLS(Table,coo);
    SDL_Flip(screen);

    /** SDL timer*/

    int exit=0;
    int run=0;
    int cnt=Speed_slider(0);
    Coo plus={0,0};

    while(!exit){

        mySDLeventhandler(&exit,&plus,&run,Table,&coo);
        /*Mozgatás*/
        /*A folyamatos lenyomvatartáshoz kell-> könnyen mozgatható tábla */
        if(plus.x || plus.y){
            if(coo.x<SZEL-151 && plus.x>0)
               coo.x+=plus.x;
            else if(coo.x>1 && plus.x<0)
               coo.x+=plus.x;
                                                /* Határokon belül kell maradni */
            if(coo.y<MAG-71 && plus.y>0)
               coo.y+=plus.y;
            else if(coo.y>1 && plus.y<0)
               coo.y+=plus.y;
            NAV_BOX(coo);
            PRINTCELLS(Table,coo);
            SDL_Flip(screen);
        }

        /*Run és cnt (counter - saját készítésű időzítő/sebesség szabályozó) változóra működik a fő algoritmus;
        csak akkor lép be a cikusba ha a cnt=0; amíg pedig nem nulla, addig folyamatosan csökken, és nem lép be
        majd ha nulla újból reset az alapértékre, ezzel a módszerrel nem kell "timer" vagy "Sleep" függvényt használni,
        ami meggátolja a fenti Pollevent működését különböző timerek lefutási ideje alatt*/
        if(run && !cnt && !plus.x && !plus.y){
            LOOP(Table,coo);
            SDL_Flip(screen);
        }
        if(!cnt)
            cnt=Speed_slider(0);
        cnt--;
    }

    /*Goodbye*/

    free(Table[0]);/*felszabadítás*/
    free(Table);
    SDL_Quit();/* Exit */
    return 0;
}



