#include "../s21_functions.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result || !s21_decimal_validation(value)) return CONV_ERROR_RETURN;

  s21_init_decimal(result);

  s21_decimal tmp_val = value;
  s21_decimal exp = s21_decimal_ten_pow_value(s21_get_scale(value));
  tmp_val.bits[3] = 0;

  tmp_val = s21_binary_div(tmp_val, exp, NULL);

  *result = tmp_val;

  s21_get_sign(value) ? s21_set_sign(result, 1) : s21_set_sign(result, 0);

  return OK_RETURN;
}
