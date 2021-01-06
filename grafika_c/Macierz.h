#pragma once

typedef float typ;

typ* macierzJednostkowa();
typ* macierzTranslacji(const typ x, const  typ y, const  typ z);
typ* macierzSkali(const typ x, const  typ y, const  typ z);
typ* macierzObrotuX(const double radian);
typ* macierzObrotuY(const double radian);
typ* macierzObrotuZ(const double radian);
typ* macierzProjekcji(const double radian, const double proporcja, const double n, const double f);
typ* macierzProjekcji2(const double l, const double r, const double b, const double t, const double n, const double f);

typ* mnozenie(const typ* A, const typ* B); // C = A * B

double radiany(const double stopnie);
double stopnie(const double radiany);