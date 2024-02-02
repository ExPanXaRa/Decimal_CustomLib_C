#include "../s21_functions.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result || !s21_decimal_validation(value)) {
    return CONV_ERROR_RETURN;
  }

  s21_init_decimal(result);
  int sign = s21_get_sign(value);

  s21_decimal fraction;
  s21_decimal val_unsigned_trunc;
  s21_decimal val_unsigned = value;

  if (sign) s21_negate(value, &val_unsigned);

  s21_truncate(val_unsigned, &val_unsigned_trunc);

  s21_sub(val_unsigned, val_unsigned_trunc, &fraction);

  val_unsigned_trunc = s21_decimal_bank_round(val_unsigned_trunc, fraction);

  *result = val_unsigned_trunc;
  s21_set_sign(result, sign);

  return OK_RETURN;
}