#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "graphics.h"

void LIVEBOX(int x, int y){
    int r, g, b;
    int a=255;
    int theme=Themeselect(-1,-1);
    switch(theme){
        case 0: r=255; g=255; b=0;   break;
        case 1: r=255; g=255; b=255; break;
        case 2: r=0; g=0; b=0; break;
        case 3: r=255; g=255; b=255; break;
        case 4: r=0; g=255; b=255; break;
        case 5: r=rand()%220+20; g=rand()%220+20; b=rand()%220+20;  a=67; break;
    }
    boxRGBA(screen, x*8, y*8, (x*8)+6, (y*8)+6,         r, g, b, a);

}

void DEADBOX(int x, int y){
    int r, g, b, a;
    int theme=Themeselect(-1,-1);
    switch(theme){
        case 0: r=190; g=0; b=190;   break; /**< Mine*/
        case 1: r=10; g=10; b=10; break; /**< CONTRAST BLACK */
        case 2: r=240; g=240; b=240; break; /**< CONTRAST WHITE */
        case 3: r=rand()%30+180; g=rand()%70; b=r; break; /**< PURPULE */
        case 4: r=rand()%30+180; g=rand()%30; b=g; break;  /**< RED */
        case 5: r=rand()%240+10; g=rand()%240+10; b=rand()%240+10; break; /**< HOLYGODDAMNSHIT */
    }
    boxRGBA(screen, x*8, y*8, (x*8)+6,(y*8)+6,         r, g, b, 255);
}

void MENULOAD(){
    /*CANVAS*/
    boxRGBA(screen, 0, 0, 1200, 660,      139, 0,	139, 255);
    boxRGBA(screen, 0, 0, 1200, 558,      200, 0,200, 255);

    /*bal oldali gombok*/
    boxRGBA(screen, 0, 560, 100, 600, /*Stop Run*/95,0,95,255);                                                          /*Speed*/                                                   boxRGBA(screen, 330, 560, 430, 600,/*Step*/95,0,95,255);
    boxRGBA(screen, 0, 620, 100, 660, /*Clear*/95,0,95,255);  boxRGBA(screen, 110, 620, 210, 660,/*Rand*/95,0,95,255); /* Function statistic: Gen, Live*/
    /*jobb oldali témaválasztó gombok*/
    boxRGBA(screen, 1060, 560, 1100, 600, /*THEME0*/190,0,190,255); boxRGBA(screen, 1110, 560, 1150, 600, /*THEME1*/10,10,10,255); boxRGBA(screen, 1160, 560, 1200, 600, /*THEME2*/240,240,240,255);
    boxRGBA(screen, 1060, 620, 1100, 660, /*THEME3*/190,50,190,255); boxRGBA(screen, 1110, 620, 1150, 660, /*THEME4*/200,15,15,255); rectangleRGBA(screen, 1160, 620, 1199, 659, /*THEME5*/95,0,95,255);
    /*DíSZELemek*/
    boxRGBA(screen, 1070, 570, 1090,590, 95,0,95,255); boxRGBA(screen, 1120,570,1140,590, 95,0,95,255); boxRGBA(screen, 1170,570,1190,590, 95,0,95,255);
    boxRGBA(screen, 1070, 630, 1090,650, 95,0,95,255); boxRGBA(screen, 1120,630,1140,650, 95,0,95,255); boxRGBA(screen, 1170,630,1190,650, 95,0,95,255);

    stringRGBA(screen, 35, 576, "RUN", 255, 255, 255, 255);stringRGBA(screen, 364, 576, "STEP", 255, 255, 255, 255);
    stringRGBA(screen, 30, 637, "CLEAR", 255, 255, 255, 255);stringRGBA(screen, 136, 637, "RANDOM", 255, 255, 255, 255);

    Speed_slider(180);
    boxRGBA(screen, 440, 560, 490, 600,/*Drawstate*/95,0,95,255);
    boxRGBA(screen, 450, 570, 480, 590,139,0,139,255);
}

int Speed_slider(int x){/*Sebesség szabáylozó*/
    static int V;
    if(!x){
        return V;
    }
    boxRGBA(screen, 110, 560, 320, 600,  /*Speed base box*/    139,0,139,255);
    boxRGBA(screen, 110, 560, 320, 580,  /*Speed box*/    95,0,95,255);
    stringRGBA(screen, 197, 567, "SPEED", 255, 255, 255, 255);
    boxRGBA(screen, x-5, 560, x+5, 600,  /*Speed Slider*/    255,255,255,255);
    V=1+(x-115)*2000;
    return;
}

void Run_Button(int *run){/*Stop/Run*/
    if(*run){
        *run=0;
        boxRGBA(screen, 0, 560, 100, 600, /*Stop Run*/95,0,95,255);
        stringRGBA(screen, 35, 576, "RUN", 255, 255, 255, 255);
    }
    else{
        *run=1;
        boxRGBA(screen, 0, 560, 100, 600, /*Stop Run*/95,0,95,255);
        stringRGBA(screen, 32, 576, "STOP", 255, 255, 255, 255);
    }
}

int Themeselect(int x, int y){/*Left_Click_Switch függvényben - a témaválasztó területért felelős */
    static theme;

    if(x==-1 && y==-1)
        return theme;

    if(( x >=1060 ) && ( y >=560) && ( x <=1100) && ( y <=600) ){/*Theme 0*/
        boxRGBA(screen, 0, 0, 1200, 558,      200, 0,200, 255);
        theme=0;
        return;
    }
    if(( x >=1110 ) && ( y >=560) && ( x <=1150) && ( y <=600) ){/*Theme 1*/
        boxRGBA(screen, 0, 0, 1200, 558,      20, 20,20, 255);
        theme=1;
        return;
    }
    if(( x >=1160 ) && ( y >=560) && ( x <=1200) && ( y <=600) ){/*Theme 2*/
        boxRGBA(screen, 0, 0, 1200, 558,      230, 230,230, 255);
        theme=2;
        return;
    }
    if(( x >=1060 ) && ( y >=620) && ( x <=1100) && ( y <=660) ){/*Theme 3*/
        boxRGBA(screen, 0, 0, 1200, 558,      190, 0,190, 255);
        theme=3;
        return;
    }
    if(( x >=1110 ) && ( y >=620) && ( x <=1150) && ( y <=660) ){/*Theme 4*/
        boxRGBA(screen, 0, 0, 1200, 558,      200,25,15, 255);
        theme=4;
        return;
    }
    if(( x >=1160 ) && ( y >=620) && ( x <=1200) && ( y <=660) ){/*Theme 5*/
        boxRGBA(screen, 0, 0, 1200, 558,      139, 0,139, 255);
        theme=5;
        return;
    }
}
