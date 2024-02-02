#ifndef S21_BINARY_OPERATIONS_H
#define S21_BINARY_OPERATIONS_H

#include "../../s21_decimal.h"

int s21_int_get_bit(int number, int index);
int s21_int_set_bit(int value, int pos);

int s21_get_bit(s21_decimal value, int bit);
s21_decimal s21_set_bit(s21_decimal value, int pos);

int s21_decimal_binary_is_zero(s21_decimal value);
int s21_decimal_get_elder_bit(s21_decimal value);

int s21_binary_cmp(s21_decimal a, s21_decimal b);

s21_decimal s21_binary_and(s21_decimal value_a, s21_decimal value_b);
s21_decimal s21_binary_xor(s21_decimal value_a, s21_decimal value_b);
s21_decimal s21_binary_not(s21_decimal value);

s21_decimal s21_binary_right_shift_by_one(s21_decimal value);
s21_decimal s21_binary_left_shift_by_one(s21_decimal value);

s21_decimal s21_binary_right_shift(s21_decimal value, int shift);
s21_decimal s21_binary_left_shift(s21_decimal value, int shift);

s21_decimal s21_binary_add(s21_decimal value_a, s21_decimal value_b);
s21_decimal s21_binary_sub(s21_decimal value_a, s21_decimal value_b);
s21_decimal s21_binary_div(s21_decimal value_a, s21_decimal value_b,
                           s21_decimal *remainder);
s21_long_decimal s21_decimal_binary_mul(s21_decimal value_a,
                                        s21_decimal value_b);

void s21_decimal_normalization(s21_decimal value_a, s21_decimal value_b,
                               s21_long_decimal *value_al,
                               s21_long_decimal *value_bl);

s21_decimal s21_remove_trailing_zeros(s21_decimal value);

#endif /* S21_BINARY_OPERATIONS_H */
