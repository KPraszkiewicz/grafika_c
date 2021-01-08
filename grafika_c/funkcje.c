#include "funkcje.h"
#include<time.h>
#include <stdlib.h>
#include <stdio.h>

GLuint init_vbo(GLfloat* bufor, unsigned int rozmiar)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    /*
        Funkcja glGenBuffers() zapisuje do zmiennej vbo listê liczb ca³kowitych zbudowan¹ z
        indeksów wolnych(nieu¿ywanych) buforów. W tym przypadku jako pierwszy parametr tej
        funkcji podaliœmy wartoœæ 1, a zatem ¿yczmy sobie, aby otrzymaæ tylko jedn¹ wartoœæ.
    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /*
        Gdy ju¿ mamy zapisany numer (albo numery) wolnego bufora
        mo¿emy go z czymœ powi¹zaæ. S³u¿y do tego funkcja glBindBuffer(). Przyjmuje ona
        dwa parametry. Pierwszym jest cel, czyli, z czym nale¿y ten bufor powi¹zaæ. W naszym
        przypadku jest to GL_ARRAY_BUFFER. Oznacza to, ¿e dany bufor bêdzie tablic¹ danych.
        Drugim parametrem, jak ³atwo siê domyœliæ, jest indeks danego bufora, który otrzymaliœmy
        w poprzednim kroku.
    */
    glBufferData(GL_ARRAY_BUFFER, rozmiar, bufor, GL_STATIC_DRAW);
    /*
        Ostatnim krokiem jest wpisanie danych do przygotowanego wczeœniej bufora. W tym celu
        wykorzystuje siê funkcjê glBufferData(). Jako jej parametry podajemy kolejno cel
        (taki sam jak wy¿ej), rozmiar danych, dane oraz przewidywane zastosowanie tych danych.
        W naszym przypadku jest to GL_STATIC_DRAW. Oznacza to, ¿e dane nie bêd¹
        modyfikowane oraz bêd¹ u¿ywane czêsto do rysowania.

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
        Funkcja glGenVertexArrays() dzia³a tak samo jak przedstawiona wy¿ej funkcja
        glGenBuffers(). Zwraca indeks (nazwê) wygenerowanej tablicy danych opisuj¹cych
        wierzcho³ek.
    */
    return vao;
}

void bind_vbo(GLuint vao, GLuint vbo, GLuint attr, GLint size)
{
    glBindVertexArray(vao);
    /*
        funkcja glBindVertexArray(), która
        uaktywnia wygenerowan¹ przed chwil¹ tablicê.
    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /*
        Funkcjê glBindBuffer() tak¿e ju¿ znamy. Nie
        napisa³em tylko o niej jednego. Powoduje ona tak¿e, ¿e przekazany do niej obiekt (w tym
        przypadku vbo) staje siê aktywny. Jeœli mielibyœmy kilka buforów VBO, np. jeden z
        wierzcho³kami, drugi z wektorami normalnymi, to wywo³anie tej funkcji powoduje, ¿e
        aktywujemy tylko jeden z nich, jakby wyci¹gamy go na wierzch. To wszystko stanie siê
        bardziej jasne, gdy w nastêpnym rozdziale poka¿ê jak wyœwietliæ na ekranie dwa trójk¹ty
    */
    glVertexAttribPointer(attr, size, GL_FLOAT, GL_FALSE, 0, 0);
    /*
        Funkcja glVertexAttribPointer() definiuje wskaŸnik pokazuj¹cy na pewne cechy
        figury (modelu), np. wspó³rzêdne wierzcho³ków, wektory normalne, itp. Z racji, ¿e wy¿ej
        mieliœmy wywo³anie funkcji glBindBuffer() dla obiektu vbo, w którym zapisane s¹
        wspó³rzêdne wierzcho³ków, to stworzymy wskaŸnik pokazuj¹cy na wspó³rzêdne
        wierzcho³ków. Parametrami tej funkcji s¹ po kolei: indeks, pod którym bêdziemy siê
        odwo³ywaæ, liczba elementów przypadaj¹ca na cechê (u nas s¹ to 3, gdy¿ mamy trzy
        wspó³rzêdne: X, Y i Z), typ danych, normalizacja. Dwa ostatnie parametry s¹ na razie nie
        istotne i je zerujemy.
    */
    glEnableVertexAttribArray(attr);
    /*
        Na zakoñczenie odblokowujemy mo¿liwoœæ korzystania z tego
        indeksu wskazywanego przez wskaŸnik. Dokonuje siê tego za pomoc¹ funkcji
        glEnableVertexAttribArray(), a jako jej parametr podaje siê numer indeksu u¿yty w
        funkcji powy¿ej.
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
