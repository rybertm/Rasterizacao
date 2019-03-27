#ifndef RASTE_H
#define RASTE_H

#include <stdio.h>
#include <GL/freeglut.h>

#define SIGN(x) ((x) < 0 ? (-1) : (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FLOOR(x) ((x) < 0 ? ((x) - (int)(x) != 0 ? ((int)(x)-1) : ((int)(x))) : (int)(x))
#define FALSE 0
#define TRUE 1

void dda(int x1, int y1, int x2, int y2);
void ponto_medio(int x1, int y1, int x2, int y2);
void setPixel(int x, int y);

void inicia_glut(int argc, char *argv[]);
void reshape(int width, int height);
void desenha_reta(int width, int height);
void desenha_dda(void);
void desenha_pontom(void);

#endif //RASTE_H