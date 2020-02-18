#ifndef DIFFERENTIALS_H_INCLUDED
#define DIFFERENTIALS_H_INCLUDED

#include "auxiliary.h"
#include "quasigroup.h"

static const int left_div = 1, right_div = 2;

void set_xor_diff_table(unsigned char s_box_table[256], int diff_table[256][256]);
void set_addition_diff_table(unsigned char s_box_table[256], int diff_table[256][256]);

void set_left_quasigroup_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], int diff_table[256][256]);
void set_right_quasigroup_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], int diff_table[256][256]);

void set_left_quasigroup_keyed_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], unsigned char key, int diff_table[256][256]);
void set_right_quasigroup_keyed_diff_table(unsigned char s_box_table[256], unsigned char op[3][256][256], unsigned char key, int diff_table[256][256]);

int maximum_differential(int diff_table[256][256]);
int maximum_differential_quasi(int diff_table[256][256]);

//check if left division and right division are differential tables (without a key) are identical
void check_diff_table_eq_all_operations(mt19937 &gen);

#endif // DIFFERENTIALS_H_INCLUDED
