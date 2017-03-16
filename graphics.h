#ifndef GRAPHICS_H
#define GRAPHICS_H

extern SDL_Surface *screen;

void LIVEBOX(int x, int y);

void DEADEBOX(int x, int y);

void MENULOAD();

int Speed_slider(int x);

void Run_Button(int *run);

int Themeselect(int x, int y);

#endif // GRAPHICS_H
