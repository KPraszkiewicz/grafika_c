#include "Macierz.h"
#include <math.h>
#define M_PI 3.14159265358979323846

typ* macierzJednostkowa(typ mat[16])
{
    mat[0] = 1.0;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;

    mat[4] = 0.0;
    mat[5] = 1.0;
    mat[6] = 0.0;
    mat[7] = 0.0;

    mat[8] = 0.0;
    mat[9] = 0.0;
    mat[10] = 1.0;
    mat[11] = 0.0;

    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 0.0;
    mat[15] = 1.0;

    return mat;
}

typ* macierzTranslacji(typ mat[16], const typ x, const typ y, const typ z)
{
    /*
    typ mat[16] =
    {
        1.0, 0.0, 0.0, x,
        0.0, 1.0, 0.0, y,
        0.0, 0.0, 1.0, z,
        0.0, 0.0, 0.0, 1.0
    };
    */
    macierzJednostkowa(mat);
    mat[3] = x;
    mat[7] = y;
    mat[11] = z;

    return mat;
}

typ* macierzSkali(typ mat[16], const typ x, const typ y, const typ z)
{
   /* typ mat[16] =
    {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };*/
    macierzJednostkowa(mat);
    mat[0] = x;
    mat[5] = y;
    mat[10] = z;
    return mat;
}

typ* macierzObrotuX(typ mat[16], const double radian)
{
    typ a = sin(radian);
    typ b = cos(radian);
    /*typ mat[16] =
    {
        1.0,    0.0,    0.0,    0.0,
        0.0,    b,      a,      0.0,
        0.0,    -a,     b,      0.0,
        0.0,    0.0,    0.0,    1.0
    };*/
    macierzJednostkowa(mat);
    mat[5] = b;
    mat[6] = a;
    mat[9] = -a;
    mat[10] = b;
    return mat;
}

typ* macierzObrotuY(typ mat[16], const double radian)
{
    typ a = sin(radian);
    typ b = cos(radian);
    /*typ mat[16] =
    {
        b,      0.0,    a,      0.0,
        0.0,    1.0,    0.0,    0.0,
        -a,     0.0,    b,      0.0,
        0.0,    0.0,    0.0,    1.0
    };*/
    macierzJednostkowa(mat);
    mat[0] = b;
    mat[2] = a;
    mat[8] = -a;
    mat[10] = b;
    return mat;
}
typ* macierzObrotuZ(typ mat[16], const double radian)
{
    typ a = sin(radian);
    typ b = cos(radian);

    /*typ mat[16] =
    {    
        b,      -a,     0.0,    0.0,
        a,      b,      0.0,    0.0,
        0.0,    0.0,    1.0,    0.0,
        0.0,    0.0,    0.0,    1.0 
    };*/
    macierzJednostkowa(mat);
    mat[0] = b;
    mat[1] = -a;
    mat[4] = a;
    mat[5] = b;
    return mat;
}
typ* macierzProjekcji(typ mat[16], const double fov_radian, const double proporcja, const double n, const double f)
{
    float D = tan(0.5 * fov_radian * n);
    float Sx = (2.0 * n) / (2. * D * proporcja);
    float Sy = n / D;
    float Sz = -(f + n) / (f - n);
    float Pz = -(2.0f * f * n) / (f - n);
    /*typ mat[16] =
    {
        Sx,     0.0,    0.0,    0.0,
        0.0,    Sy,     0.0,    0.0,
        0.0,    0.0,    Sz,     Pz, 
        0.0,    0.0,    -1.0,   0.0
    };*/
    macierzJednostkowa(mat);
    mat[0] = Sx;
    mat[5] = Sy;
    mat[10] = Sz;
    mat[11] = Pz;
    mat[14] = -1.0;
    return mat;
    /*
    float D = 1 / tan(0.5 * fov_radian);
    float A = -f / (f - n);
    float B = -(f * n) / (f - n);
    typ mat[16] =
    {
        D,     0.0,    0.0,    0.0,
        0.0,    D,     0.0,    0.0,
        0.0,    0.0,    A,     B,
        0.0,    0.0,    -1,     0.0
    };
    return mat;
    */
}

typ* macierzProjekcji2(typ mat[16], const double l, const double r, const double b, const double t, const double n, const double f)
{
    /*
    typ mat[16] =
    {
        2.*n/(r-l), 0.0,        (r+l)/(r-l),    0.0,
        0.0,        2.*n/(t-b), (t+b)/(t-b),    0.0,
        0.0,        0.0,        -(f+n)/(f-n),   -2.*f*n/(f-n),
        0.0,        0.0,        -1.0,           0.0
    };
    */
    macierzJednostkowa(mat);
    return mat;
}

typ* mnozenie(typ mat[16], const typ A[16], const typ B[16])
{
    /*typ mat[16] =
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
    };*/
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            mat[i * 4 + j] = 0;
            for (int k = 0; k < 4; ++k)
                mat[i * 4 + j] += A[i * 4 + k] * B[k * 4 + j];
        }
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

