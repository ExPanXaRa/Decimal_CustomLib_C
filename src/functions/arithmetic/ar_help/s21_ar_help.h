#ifndef S21_AR_HELP_H
#define S21_AR_HELP_H
#include "../../../s21_decimal.h"

int s21_calc_fraction(s21_long_decimal* res, s21_long_decimal value_bl,
                      s21_long_decimal* remainder);

s21_decimal s21_decimal_bank_round(s21_decimal int_part,
                                   s21_decimal fract_part);
int s21_get_shift_from_ld_to_decimal(s21_long_decimal value);
#endif
