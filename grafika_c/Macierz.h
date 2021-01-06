#pragma once

typedef float typ;

// generowanie macierzy
typ* macierzJednostkowa(typ mat[16]);
typ* macierzTranslacji(typ mat[16], const typ x, const  typ y, const  typ z);
typ* macierzSkali(typ mat[16], const typ x, const  typ y, const  typ z);
typ* macierzObrotuX(typ mat[16], const double radian);
typ* macierzObrotuY(typ mat[16], const double radian);
typ* macierzObrotuZ(typ mat[16], const double radian);
typ* macierzProjekcji(typ mat[16], const double radian, const double proporcja, const double n, const double f);
typ* macierzProjekcji2(typ mat[16], const double l, const double r, const double b, const double t, const double n, const double f);



// MAT = A * B
typ* mnozenie(typ mat[16], const typ A[16], const typ B[16]); 

double radiany(const double stopnie);
double stopnie(const double radiany);