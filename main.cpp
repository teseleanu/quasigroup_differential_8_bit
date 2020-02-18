#include <iostream>
#include <random>
#include <array>
#include <algorithm>

#include "auxiliary.h"
#include "differentials.h"

using namespace std;

#define LEFT

const int iteratii = 10000;
const int key_iteratii = 1000;

void print_medie_dispersie(double xor_max[iteratii], double xor_quasigroup_max[3][iteratii], double keyed_xor_quasigroup_max[3][iteratii])
{
    double medie_max = 0, deviation_max = 0;

    #ifdef LEFT
    int i = left_div;
    cout << "Left" << endl;
    #else
    int i = right_div;
    cout << "Right" << endl;
    #endif // LEFT

    medie_max = sample_mean(xor_max, iteratii);
    deviation_max = sample_mean_absolute_deviation(xor_max, iteratii, medie_max);

    cout << "xor:      " << medie_max << " " << deviation_max << endl;

    medie_max = sample_mean(xor_quasigroup_max[i], iteratii);
    deviation_max = sample_mean_absolute_deviation(xor_quasigroup_max[i], iteratii, medie_max);

    cout << "xor quas: " << medie_max << " " << deviation_max << endl;

    medie_max = sample_mean(keyed_xor_quasigroup_max[i], iteratii);
    deviation_max = sample_mean_absolute_deviation(keyed_xor_quasigroup_max[i], iteratii, medie_max);

    cout << "keyed xor quas: " << medie_max << " " << deviation_max << endl;
}

void compute_max_diff(mt19937 &gen)
{
    unsigned char s_box_table[256];
    unsigned char perm[3][256], op_q[3][256][256];
    int diff_table[256][256] = {0};
    uniform_int_distribution<int> dist(1, 256);

    double xor_max[iteratii], xor_quasigroup_max[3][iteratii], keyed_xor_quasigroup_max[3][iteratii];

    for(int i = 0; i < iteratii; i++)
    {
        set_s_box_table(s_box_table, gen);

        set_s_box_table(perm[0], gen);
        set_s_box_table(perm[1], gen);
        set_s_box_table(perm[2], gen);

        set_xor_diff_table(s_box_table, diff_table);
        xor_max[i] = maximum_differential(diff_table);

        for(int k = 0; k < 256; k++)
            perm[0][k] = k;

        #ifdef LEFT

        for(int k = 0; k < 256; k++)
            perm[2][k] = k;

        set_xor_quasi_times(perm, op_q);

        set_left_quasigroup_diff_table(s_box_table, op_q, diff_table);
        xor_quasigroup_max[left_div][i] = maximum_differential_quasi(diff_table);

        keyed_xor_quasigroup_max[left_div][i] = 0;

        for(int j = 0; j < key_iteratii; j++)
        {
            int key = dist(gen);
            set_left_quasigroup_keyed_diff_table(s_box_table, op_q, key, diff_table);
            keyed_xor_quasigroup_max[left_div][i] += maximum_differential_quasi(diff_table);
        }

        keyed_xor_quasigroup_max[left_div][i] /= key_iteratii;

        #else

        for(int k = 0; k < 256; k++)
            perm[1][k] = k;

        set_xor_quasi_times(perm, op_q);

        set_right_quasigroup_diff_table(s_box_table, op_q, diff_table);
        xor_quasigroup_max[right_div][i] = maximum_differential_quasi(diff_table);

        keyed_xor_quasigroup_max[right_div][i] = 0;

        for(int j = 0; j < key_iteratii; j++)
        {
            int key = dist(gen);
            set_right_quasigroup_keyed_diff_table(s_box_table, op_q, key, diff_table);
            keyed_xor_quasigroup_max[right_div][i] += maximum_differential_quasi(diff_table);
        }

        keyed_xor_quasigroup_max[right_div][i] /= key_iteratii;

        #endif // LEFT
    }

    print_medie_dispersie(xor_max, xor_quasigroup_max, keyed_xor_quasigroup_max);
}



int main()
{
    mt19937 gen;

    compute_max_diff(gen);

    return 0;
}
