#include "funkcje.h"
#include<time.h>
#include <stdlib.h>
#include <stdio.h>

GLuint init_vbo(GLfloat* bufor, unsigned int rozmiar)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    /*
        Funkcja glGenBuffers() zapisuje do zmiennej vbo list� liczb ca�kowitych zbudowan� z
        indeks�w wolnych(nieu�ywanych) bufor�w. W tym przypadku jako pierwszy parametr tej
        funkcji podali�my warto�� 1, a zatem �yczmy sobie, aby otrzyma� tylko jedn� warto��.
    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /*
        Gdy ju� mamy zapisany numer (albo numery) wolnego bufora
        mo�emy go z czym� powi�za�. S�u�y do tego funkcja glBindBuffer(). Przyjmuje ona
        dwa parametry. Pierwszym jest cel, czyli, z czym nale�y ten bufor powi�za�. W naszym
        przypadku jest to GL_ARRAY_BUFFER. Oznacza to, �e dany bufor b�dzie tablic� danych.
        Drugim parametrem, jak �atwo si� domy�li�, jest indeks danego bufora, kt�ry otrzymali�my
        w poprzednim kroku.
    */
    glBufferData(GL_ARRAY_BUFFER, rozmiar, bufor, GL_STATIC_DRAW);
    /*
        Ostatnim krokiem jest wpisanie danych do przygotowanego wcze�niej bufora. W tym celu
        wykorzystuje si� funkcj� glBufferData(). Jako jej parametry podajemy kolejno cel
        (taki sam jak wy�ej), rozmiar danych, dane oraz przewidywane zastosowanie tych danych.
        W naszym przypadku jest to GL_STATIC_DRAW. Oznacza to, �e dane nie b�d�
        modyfikowane oraz b�d� u�ywane cz�sto do rysowania.

    */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /*
        Pewnie odbidowanie bufora
    */
    return vbo;
}

GLuint init_vao()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    /*
        Funkcja glGenVertexArrays() dzia�a tak samo jak przedstawiona wy�ej funkcja
        glGenBuffers(). Zwraca indeks (nazw�) wygenerowanej tablicy danych opisuj�cych
        wierzcho�ek.
    */
    return vao;
}

void bind_vbo(GLuint vao, GLuint vbo, GLuint attr, GLint size)
{
    glBindVertexArray(vao);
    /*
        funkcja glBindVertexArray(), kt�ra
        uaktywnia wygenerowan� przed chwil� tablic�.
    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /*
        Funkcj� glBindBuffer() tak�e ju� znamy. Nie
        napisa�em tylko o niej jednego. Powoduje ona tak�e, �e przekazany do niej obiekt (w tym
        przypadku vbo) staje si� aktywny. Je�li mieliby�my kilka bufor�w VBO, np. jeden z
        wierzcho�kami, drugi z wektorami normalnymi, to wywo�anie tej funkcji powoduje, �e
        aktywujemy tylko jeden z nich, jakby wyci�gamy go na wierzch. To wszystko stanie si�
        bardziej jasne, gdy w nast�pnym rozdziale poka�� jak wy�wietli� na ekranie dwa tr�jk�ty
    */
    glVertexAttribPointer(attr, size, GL_FLOAT, GL_FALSE, 0, 0);
    /*
        Funkcja glVertexAttribPointer() definiuje wska�nik pokazuj�cy na pewne cechy
        figury (modelu), np. wsp�rz�dne wierzcho�k�w, wektory normalne, itp. Z racji, �e wy�ej
        mieli�my wywo�anie funkcji glBindBuffer() dla obiektu vbo, w kt�rym zapisane s�
        wsp�rz�dne wierzcho�k�w, to stworzymy wska�nik pokazuj�cy na wsp�rz�dne
        wierzcho�k�w. Parametrami tej funkcji s� po kolei: indeks, pod kt�rym b�dziemy si�
        odwo�ywa�, liczba element�w przypadaj�ca na cech� (u nas s� to 3, gdy� mamy trzy
        wsp�rz�dne: X, Y i Z), typ danych, normalizacja. Dwa ostatnie parametry s� na razie nie
        istotne i je zerujemy.
    */
    glEnableVertexAttribArray(attr);
    /*
        Na zako�czenie odblokowujemy mo�liwo�� korzystania z tego
        indeksu wskazywanego przez wska�nik. Dokonuje si� tego za pomoc� funkcji
        glEnableVertexAttribArray(), a jako jej parametr podaje si� numer indeksu u�yty w
        funkcji powy�ej.
    */
}

void gora(GLfloat teren_wyso[TN1][TN1], int ROZ_X, int ROZ_Z, int px, int pz, int r1, int r2, int wys)
{
    for (int i = -r1 / 2; i < r1 / 2; ++i)
        for (int j = -r1 / 2; j < r1 / 2; ++j)
            if (2 * sqrt(i * i + j * j) < r1)
            {
                int xx = (i + px + ROZ_X) % ROZ_X;
                int zz = (j + pz + ROZ_Z) % ROZ_Z;
                teren_wyso[xx][zz] += MIN(wys, (r1 - 2 * sqrt(i * i + j * j) * wys / (r1 - r2)));
            }

}

void inicjuj_plansze(GLfloat teren_wys[TN1][TN1], int ROZ_X, int ROZ_Z, int liczba_gor, int max_promien, int max_wys)
{
    int i, j, r1, r2, px, pz, wys;
    for (int a = 0; a < liczba_gor; ++a)
    {
        r1 = rand() * max_promien / RAND_MAX + 5;
        //r2 = rand() * ((r1-5) / 2) / RAND_MAX;
        r2 = 0;
        wys = rand() * max_wys / RAND_MAX;
        px = rand() * ROZ_X / RAND_MAX;
        pz = rand() * ROZ_Z / RAND_MAX;
        printf("%d %d %d\n", r1, r2, wys);
        gora(teren_wys, ROZ_X, ROZ_Z, px, pz, r1, r2, wys);
    }
}

GLuint inicjuj_teksture(char nazwa[])
{
    unsigned char* buf = malloc(256*256*3);
    long i;
    FILE* ws;
    fopen_s(&ws, nazwa, "rb");
    if (!ws)
    {
        printf("blad otwarcia");
        return 0;
    }
    fseek(ws, -256 * 256 * 3, SEEK_END);
    for (i = 0; i < 256 * 256 * 3; i += 3)
    {
        buf[i + 2] = getc(ws);
        buf[i + 1] = getc(ws);
        buf[i] = getc(ws);
    }
    
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glGenerateMipmap(GL_TEXTURE_2D);

    fclose(ws);
    free(buf);
    return texture;
}
