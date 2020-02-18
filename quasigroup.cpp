#include "quasigroup.h"

void set_xor_quasi_times(unsigned char perm[3][256], unsigned char quasi_op[3][256][256])
{
    for(int x = 0; x < 256; x++)
        for(int y = 0; y < 256; y++)
        {
            unsigned char z = perm[0][perm[1][x] ^ perm[2][y]];
            quasi_op[0][x][y] = z;//times
            quasi_op[1][x][z] = y;//left div
            quasi_op[2][z][y] = x;//right div
        }
}

void set_add_quasi_times(unsigned char perm[3][256], unsigned char quasi_op[3][256][256])
{
    for(int x = 0; x < 256; x++)
        for(int y = 0; y < 256; y++)
        {
            unsigned char z = perm[0][mod_256(perm[1][x] + perm[2][y])];
            quasi_op[0][x][y] = z;//times
            quasi_op[1][x][z] = y;//left div
            quasi_op[2][z][y] = x;//right div
        }
}

void set_minus_quasi_times(unsigned char perm[3][256], unsigned char quasi_op[3][256][256])
{
    for(int x = 0; x < 256; x++)
        for(int y = 0; y < 256; y++)
        {
            unsigned char z = perm[0][mod_256(perm[1][x] - perm[2][y])];
            quasi_op[0][x][y] = z;//times
            quasi_op[1][x][z] = y;//left div
            quasi_op[2][z][y] = x;//right div
        }
}

void set_random_quasi_times(mt19937 &gen, unsigned char quasi_op_in[3][256][256], unsigned char quasi_op_out[3][256][256])
{
    unsigned char perm[3][256];

    set_s_box_table(perm[0], gen);
    set_s_box_table(perm[1], gen);
    set_s_box_table(perm[2], gen);

    for(int x = 0; x < 256; x++)
        for(int y = 0; y < 256; y++)
        {
            unsigned char temp = quasi_op_in[0][perm[1][x]][perm[2][y]];
            unsigned char z = perm[0][temp];
            quasi_op_out[0][x][y] = z;//times
            quasi_op_out[1][x][z] = y;//left div
            quasi_op_out[2][z][y] = x;//right div
        }
}

int check_division_simetrie(unsigned char op_q[3][256][256])
{
    int flag = 0;

    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
        if(op_q[1][i][j] != op_q[2][j][i]) flag++;

    return flag;
}

void check_division_simetrie_all_operations(mt19937 &gen)
{
    int flag[6] = {0};

    unsigned char s_box_table[256];
    unsigned char perm[3][256], op_q[3][256][256], op_q_rand[3][256][256];

    for(int i = 0; i < iteratii; i++)
    {
        set_s_box_table(s_box_table, gen);

        set_s_box_table(perm[0], gen);
        set_s_box_table(perm[1], gen);

        for(int k = 0; k < 256; k++)
            perm[2][k] = perm[1][k];

        set_xor_quasi_times(perm, op_q);
        flag[0] += check_division_simetrie(op_q);

        set_random_quasi_times(gen, op_q, op_q_rand);
        flag[1] += check_division_simetrie(op_q_rand);

        set_add_quasi_times(perm, op_q);
        flag[2] += check_division_simetrie(op_q);

        set_random_quasi_times(gen, op_q, op_q_rand);
        flag[3] += check_division_simetrie(op_q_rand);

        set_minus_quasi_times(perm, op_q);
        flag[4] += check_division_simetrie(op_q);

        set_random_quasi_times(gen, op_q, op_q_rand);
        flag[5] += check_division_simetrie(op_q_rand);

    }

    for(int i = 0; i < 6; i++)
        cout << flag[i] << " ";
    cout << endl;
}
