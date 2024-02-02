#ifndef S21_HELPER_FUNCS_H
#define S21_HELPER_FUNCS_H

#include "../../s21_decimal.h"

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal* value, int sign);
int s21_get_scale(s21_decimal value);
int s21_set_scale(s21_decimal* value, int scale);

int s21_get_float_exp(char* str);
int s21_mantissa_is_zero(s21_decimal value);
int s21_mantissa_get_elder_bit(s21_decimal value);

void s21_copy_decimal_to_decimal(s21_decimal value, s21_decimal* dst);
void s21_init_decimal(s21_decimal* dst);
void s21_init_long_decimal(s21_long_decimal* dst);
int s21_check_unused_bits(s21_decimal value);
int s21_decimal_validation(s21_decimal value);

s21_decimal s21_decimal_ten_pow_value(int pow);
s21_long_decimal s21_long_decimal_from_decimal(s21_decimal value_1);

s21_decimal s21_decimal_from_char(char ch);
s21_decimal s21_float_str_to_decimal(char* str);
#endif /* S21_HELPER_FUNCS_H */
