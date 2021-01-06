#include "Macierz.h"
#include <math.h>
#define M_PI 3.14159265358979323846

typ* macierzJednostkowa()
{
    typ mat[16] = 
    {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return mat;
}

typ* macierzTranslacji(const typ x, const typ y, const typ z)
{
    typ mat[16] =
    {
        1.0, 0.0, 0.0, x,
        0.0, 1.0, 0.0, y,
        0.0, 0.0, 1.0, z,
        0.0, 0.0, 0.0, 1.0
    };
    return mat;
}

typ* macierzSkali(const typ x, const typ y, const typ z)
{
    typ mat[16] =
    {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return mat;
}

typ* macierzObrotuX(const double radian)
{
    typ a = sin(radian);
    typ b = cos(radian);

    typ mat[16] =
    {
        1.0,    0.0,    0.0,    0.0,
        0.0,    b,      a,      0.0,
        0.0,    -a,     b,      0.0,
        0.0,    0.0,    0.0,    1.0
    };
    return mat;
}

typ* macierzObrotuY(const double radian)
{
    typ a = sin(radian);
    typ b = cos(radian);

    typ mat[16] =
    {
        b,      0.0,    a,      0.0,
        0.0,    1.0,    0.0,    0.0,
        -a,     0.0,    b,      0.0,
        0.0,    0.0,    0.0,    1.0
    };
    return mat;
}
typ* macierzObrotuZ(const double radian)
{
    typ a = sin(radian);
    typ b = cos(radian);

    typ mat[16] =
    {    
        b,      -a,     0.0,    0.0,
        a,      b,      0.0,    0.0,
        0.0,    0.0,    1.0,    0.0,
        0.0,    0.0,    0.0,    1.0
    };
    return mat;
}
typ* macierzProjekcji(const double radian, const double proporcja, const double n, const double f)
{
    return NULL;
}

typ* macierzProjekcji2(const double l, const double r, const double b, const double t, const double n, const double f)
{
    typ mat[16] =
    {
        2.*n/(r-l), 0.0,        (r+l)/(r-l),    0.0,
        0.0,        2.*n/(t-b), (t+b)/(t-b),    0.0,
        0.0,        0.0,        -(f+n)/(f-n),   -2.*f*n/(f-n),
        0.0,        0.0,        -1.0,           0.0
    };
    return mat;
}

typ* mnozenie(const typ* A, const typ* B)
{
    typ mat[16] =
    {
        A[0] * B[0] + A[1] * B[4] + A[2] * B[8] + A[3] * B[12],
        A[0] * B[1] + A[1] * B[5] + A[2] * B[9] + A[3] * B[13],
        A[0] * B[2] + A[1] * B[6] + A[2] * B[10] + A[3] * B[14],
        A[0] * B[3] + A[1] * B[7] + A[2] * B[11] + A[3] * B[15],

        A[4] * B[0] + A[5] * B[4] + A[6] * B[8] + A[7] * B[12],
        A[4] * B[1] + A[5] * B[5] + A[6] * B[9] + A[7] * B[13],
        A[4] * B[2] + A[5] * B[6] + A[6] * B[10] + A[7] * B[14],
        A[4] * B[3] + A[5] * B[7] + A[6] * B[11] + A[7] * B[15],

        A[8] * B[0] + A[9] * B[4] + A[10] * B[8] + A[11] * B[12],
        A[8] * B[1] + A[9] * B[5] + A[10] * B[9] + A[11] * B[13],
        A[8] * B[2] + A[9] * B[6] + A[10] * B[10] + A[11] * B[14],
        A[8] * B[3] + A[9] * B[7] + A[10] * B[11] + A[11] * B[15],

        A[12] * B[0] + A[13] * B[4] + A[14] * B[8] + A[15] * B[12],
        A[12] * B[1] + A[13] * B[5] + A[14] * B[9] + A[15] * B[13],
        A[12] * B[2] + A[13] * B[6] + A[14] * B[10] + A[15] * B[14],
        A[12] * B[3] + A[13] * B[7] + A[14] * B[11] + A[15] * B[15]
    };
    return mat;
}

double radiany(const double stopnie)
{
    return M_PI*stopnie/180.;
}

double stopnie(const double radiany)
{
    return 180.*radiany/M_PI;
}

