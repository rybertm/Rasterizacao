#include "raste.h"

#include <stdio.h>
#include <GL/freeglut.h>

int id1, id2, x[100] = { 0 }, y[100] = { 0 }, x2[100] = { 0 }, y2[100] = { 0 }, n = 0;

int main(int argc, char *argv[])
{
	inicia_glut(argc, argv);

	printf("\nDigite um valor maior que 10 para sair.\n");
	while (1)
	{
		printf("x1 y1: ");
		scanf("%d %d%*c", &x[n], &y[n]);

		if (x[n] > 10 || y[n] > 10)
			break;

		printf("x2 y2: ");
		scanf("%d %d%*c", &x2[n], &y2[n]);

		if (x2[n] > 10 || y2[n] > 10)
			break;

		n++;
	}

	printf("\n");

	desenha_reta(640, 480);

	glutMainLoop();

	return 0;
}

void reshape(int width, int height)
{
	if (height == 0)
		height = 1;
	float aspect = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height)
	{
		gluOrtho2D(-10 * aspect, 10 * aspect, -10, 10);
	}
	else
		gluOrtho2D(-10, 10, -10 / aspect, 10 / aspect);
}

void inicia_glut(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void desenha_reta(int width, int height)
{
	int posx, posy;

	posx = (glutGet(GLUT_SCREEN_WIDTH) - 640) / 2;
	posy = (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2;

	// DDA
	glutInitWindowPosition(posx - 350, posy);
	glutInitWindowSize(width, height);
	id1 = glutCreateWindow("DDA");

	glutDisplayFunc(desenha_dda);
	glutReshapeFunc(reshape);

	// Ponto Medio
	glutInitWindowPosition(posx + 350, posy);
	glutInitWindowSize(width, height);
	id2 = glutCreateWindow("Ponto Medio");

	glutDisplayFunc(desenha_pontom);
	glutReshapeFunc(reshape);
}

void desenha_dda(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	for (i = 0; i < n; i++)
	{
		dda(x[i], y[i], x2[i], y2[i]);
	}

	glFlush();
}

void dda(int x1, int y1, int x2, int y2)
{
	int length, i;
	float x, y, deltax, deltay;

	if (ABS((x2 - x1)) >= ABS((y2 - y1)))
		length = ABS((x2 - x1));
	else
		length = ABS((y2 - y1));
	deltax = (float)(x2 - x1) / (float)length;
	deltay = (float)(y2 - y1) / (float)length;
	x = x1 + 0.5 * SIGN(deltax);
	y = y1 + 0.5 * SIGN(deltay);
	for (i = 0; i < length; i++)
	{
		setPixel(FLOOR(x), FLOOR(y));
		x += deltax;
		y += deltay;
	}
}

void desenha_pontom(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	for (i = 0; i < n; i++)
	{
		ponto_medio(x[i], y[i], x2[i], y2[i]);
	}

	glFlush();
}

void ponto_medio(int x1, int y1, int x2, int y2)
{
	int i, interchange, deltax, deltay, signalx, signaly, x, y, tmp, erro;

	deltax = ABS((x2 - x1));
	deltay = ABS((y2 - y1));
	signalx = SIGN((x2 - x1));
	signaly = SIGN((y2 - y1));
	x = x1;
	y = y1;
	if (signalx < 0)
		x -= 1;
	if (signaly < 0)
		y -= 1;
	// trocar deltax com deltay dependendo da inclinacao da reta
	interchange = FALSE;
	if (deltay > deltax)
	{
		tmp = deltax;
		deltax = deltay;
		deltay = tmp;
		interchange = TRUE;
	}
	erro = 2 * deltay - deltax;
	for (i = 0; i < deltax; i++)
	{
		setPixel(x, y);
		while (erro >= 0)
		{
			if (interchange)
				x = x + signalx;
			else
				y = y + signaly;
			erro = erro - 2 * deltax;
		} // while
		if (interchange)
			y = y + signaly;
		else
			x = x + signalx;
		erro = erro + 2 * deltay;
	}
}

void setPixel(int x, int y)
{
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(x - 0.47f, y + 0.47f);
		glVertex2f(x + 0.47f, y + 0.47f);
		glVertex2f(x + 0.47f, y - 0.47f);
		glVertex2f(x - 0.47f, y - 0.47f);
	}
	glEnd();
}