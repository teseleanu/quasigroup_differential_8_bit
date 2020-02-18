#ifndef AUXILIARY_H_INCLUDED
#define AUXILIARY_H_INCLUDED

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

extern const int iteratii;

int mod_256(int a);
void set_s_box_table(unsigned char s_box_table[256], mt19937 &gen);

double sample_mean(double *x, int size_x);
double sample_mean_absolute_deviation(double *x, int size_x, double sample_mean);



#endif // AUXILIARY_H_INCLUDED
