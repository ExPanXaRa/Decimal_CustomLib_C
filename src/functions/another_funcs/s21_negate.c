#include "../s21_functions.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return CONV_ERROR_RETURN;

  int err = OK_RETURN;

  s21_init_decimal(result);

  *result = value;
  s21_get_sign(value) ? s21_set_sign(result, 0) : s21_set_sign(result, 1);

  if (!s21_decimal_validation(value)) err = CONV_ERROR_RETURN;

  return err;
}
