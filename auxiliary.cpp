#include "auxiliary.h"

int mod_256(int a)
{
    if(a%256 >= 0) return a%256;
    else return 256+a%256;
}

void set_s_box_table(unsigned char s_box_table[256], mt19937 &gen)
{
    for(int i = 0; i < 256; i++)
        s_box_table[i] = i;

    shuffle(s_box_table, s_box_table+256, gen);
}

double sample_mean(double *x, int size_x)
{
    double sum = 0.0;

    for(int i = 0; i < size_x; i++)
        sum += x[i];

    return sum/size_x;
}

double sample_mean_absolute_deviation(double *x, int size_x, double sample_mean)
{
    double sum = 0.0;

    for(int i = 0; i < size_x; i++)
        sum += abs(x[i]-sample_mean);

    return sum/size_x;
}


