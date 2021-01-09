#pragma once
#include<GL/glew.h>
#include<math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define TN 100
#define TN1 101

struct Obiekt
{
    float mT[16];
    float mR[16];
    float mS[16];
    float mvp[16];
    GLuint vao;
    GLuint ebo;
};
typedef struct Obiekt Obiekt;

GLuint init_vbo(GLfloat* bufor, unsigned int rozmiar);

GLuint init_ebo(unsigned int indexy[], unsigned int rozmiar);

GLuint init_vao();

void bind_vbo(GLuint vao, GLuint vbo, GLuint attr, GLint size);

void gora(GLfloat teren_wyso[TN1][TN1], int ROZ_X, int ROZ_Z, int px, int pz, int r1, int r2, int wys);

void inicjuj_plansze(GLfloat teren_wys[TN1][TN1], int ROZ_X, int ROZ_Z, int liczba_gor, int max_promien, int max_wys);

GLuint inicjuj_teksture(char nazwa[]);

void inicjuj_obiekty(Obiekt obiekty[], const int N);

Obiekt generuj_kostke(float skala, float pozX, float pozY, float pozZ);

Obiekt generuj_domek(float skala, float pozX, float pozY, float pozZ);