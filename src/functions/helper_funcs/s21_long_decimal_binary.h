#ifndef S21_LONG_DECIMAL_BINARY_H
#define S21_LONG_DECIMAL_BINARY_H

#include "../../s21_decimal.h"

s21_long_decimal s21_long_decimal_binary_add(s21_long_decimal value_a,
                                             s21_long_decimal value_b);

s21_long_decimal s21_long_decimal_binary_sub(s21_long_decimal value_a,
                                             s21_long_decimal value_b);

s21_long_decimal s21_long_decimal_binary_div(s21_long_decimal value_a,
                                             s21_long_decimal value_b,
                                             s21_long_decimal *remainder);

s21_long_decimal s21_long_decimal_binary_mul(s21_long_decimal decimal1,
                                             s21_decimal decimal2);

int s21_long_decimal_binary_cmp(s21_long_decimal value_a,
                                s21_long_decimal value_b);

s21_long_decimal s21_long_decimal_left_shift(s21_long_decimal value, int shift);

s21_long_decimal s21_long_decimal_right_shift(s21_long_decimal value,
                                              int shift);

#endif /* S21_LONG_DECIMAL_BINARY_H */
