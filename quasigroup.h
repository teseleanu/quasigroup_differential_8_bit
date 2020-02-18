#ifndef QUASIGROUP_H_INCLUDED
#define QUASIGROUP_H_INCLUDED

#include <random>

#include "auxiliary.h"

using namespace std;

void set_xor_quasi_times(unsigned char perm[3][256], unsigned char quasi_op[3][256][256]);
void set_add_quasi_times(unsigned char perm[3][256], unsigned char quasi_op[3][256][256]);
void set_minus_quasi_times(unsigned char perm[3][256], unsigned char quasi_op[3][256][256]);
void set_random_quasi_times(mt19937 &gen, unsigned char quasi_op_in[3][256][256], unsigned char quasi_op_out[3][256][256]);

//check if left division and right division are identical operations
void check_division_simetrie_all_operations(mt19937 &gen);

#endif // QUASIGROUP_H_INCLUDED
