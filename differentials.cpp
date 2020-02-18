#include"differentials.h"

void set_xor_diff_table(unsigned char s_box_table[256], int diff_table[256][256])
{
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            diff_table[i][j] = 0;

    for(int alpha = 0; alpha < 256; alpha++)
        for(int x = 0; x < 256; x++)
        {
            int beta = s_box_table[x]^s_box_table[x^alpha];
            diff_table[alpha][beta]++;
        }
}

void set_addition_diff_table(unsigned char s_box_table[256], int diff_table[256][256])
{
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            diff_table[i][j] = 0;

    for(int alpha = 0; alpha < 256; alpha++)
        for(int x = 0; x < 256; x++)
        {
            int beta = mod_256(s_box_table[mod_256(x+alpha)] - s_box_table[x]);
            diff_table[alpha][beta]++;
        }
}

void set_quasigroup_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], int diff_table[256][256], int flag)
{
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            diff_table[i][j] = 0;

    for(int x = 0; x < 256; x++)
        for(int y = 0; y < 256; y++)
        {
            int alpha = op[flag][x][y];
            int beta = op[flag][s_box_table[x]][s_box_table[y]];

            diff_table[alpha][beta]++;
        }
 }

void set_left_quasigroup_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], int diff_table[256][256])
{
    set_quasigroup_diff_table(s_box_table, op, diff_table, left_div);
}

void set_right_quasigroup_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], int diff_table[256][256])
{
    set_quasigroup_diff_table(s_box_table, op, diff_table, right_div);
}

void set_quasigroup_keyed_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], unsigned char key, int diff_table[256][256], int flag)
{
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            diff_table[i][j] = 0;

    for(int x = 0; x < 256; x++)
        for(int y = 0; y < 256; y++)
        {

            int alpha = op[flag][x][y];
            int k_x, k_y;

            if(flag == left_div)
            {
                k_x = op[0][key][x];
                k_y = op[0][key][y];
            }
            else
            {
                k_x = op[0][x][key];
                k_y = op[0][y][key];
            }

            int beta = op[flag][s_box_table[k_x]][s_box_table[k_y]];

            diff_table[alpha][beta]++;
        }
 }

void set_left_quasigroup_keyed_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], unsigned char key, int diff_table[256][256])
{
    set_quasigroup_keyed_diff_table(s_box_table, op, key, diff_table, left_div);
}

void set_right_quasigroup_keyed_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], unsigned char key, int diff_table[256][256])
{
    set_quasigroup_keyed_diff_table(s_box_table, op, key, diff_table, right_div);
}

int maximum_differential(int diff_table[256][256])
{
    int diff_max = 0;

    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            if(i!= 0 && j!= 0) diff_max = max(diff_max, diff_table[i][j]);

    return diff_max;
}

int maximum_differential_quasi(int diff_table[256][256])
{
    int diff_max = 0;

    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            diff_max = max(diff_max, diff_table[i][j]);

    return diff_max;
}

int check_diff_table_eq(unsigned char s_box_table[256], unsigned char op[3][256][256])
{
    int flag = 0;
    int l_diff_table[256][256], r_diff_table[256][256];

    set_left_quasigroup_diff_table(s_box_table, op, l_diff_table);
    set_right_quasigroup_diff_table(s_box_table, op, r_diff_table);

    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            if(l_diff_table[i][j] != r_diff_table[i][j]) flag++;

    return flag;
}

void check_diff_table_eq_all_operations(mt19937 &gen)
{
    int flag[6] = {0};

    unsigned char s_box_table[256];
    unsigned char perm[3][256], op_q[3][256][256], op_q_rand[3][256][256];

    for(int i = 0; i < iteratii; i++)
    {
        set_s_box_table(s_box_table, gen);

        set_s_box_table(perm[0], gen);
        set_s_box_table(perm[1], gen);
        set_s_box_table(perm[2], gen);

        for(int k = 0; k < 256; k++)
            perm[1][k] = perm[2][k];// = k;

        set_xor_quasi_times(perm, op_q);
        flag[0] += check_diff_table_eq(s_box_table, op_q);

        set_random_quasi_times(gen, op_q, op_q_rand);
        flag[1] += check_diff_table_eq(s_box_table, op_q_rand);

        set_add_quasi_times(perm, op_q);
        flag[2] += check_diff_table_eq(s_box_table, op_q);

        set_random_quasi_times(gen, op_q, op_q_rand);
        flag[3] += check_diff_table_eq(s_box_table, op_q_rand);

        set_minus_quasi_times(perm, op_q);
        flag[4] += check_diff_table_eq(s_box_table, op_q);

        set_random_quasi_times(gen, op_q, op_q_rand);
        flag[5] += check_diff_table_eq(s_box_table, op_q_rand);

    }

    for(int i = 0; i < 6; i++)
        cout << flag[i] << " ";
    cout << endl;
}
