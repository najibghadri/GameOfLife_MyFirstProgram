#ifndef GENERAL_H
#define GENERAL_H

#include "graphics.h"
#include "base.h"

void Statistic(int n, Cell **Table);

void NAV_BOX(Coo coo);

void Clear(Cell **Table);

void Rand(Cell **Table);

void Left_Click_Switch(int x, int y, int *run, Cell **Table,Coo coo);

void Draw(int x, int y, Cell **Table,Coo coo);

int Draw_state(int i);

#endif // GENERAL_H
