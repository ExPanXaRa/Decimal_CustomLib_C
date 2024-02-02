#include "../s21_functions.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return CONV_ERROR_RETURN;

  *dst = 0;
  if (!s21_decimal_validation(src)) {
    return CONV_ERROR_RETURN;
  }

  int err = OK_RETURN;

  s21_decimal int_min = DECIMAL_INT_MIN;
  s21_decimal int_max = DECIMAL_INT_MAX;

  s21_decimal truncated_tmp;
  s21_init_decimal(&truncated_tmp);
  s21_truncate(src, &truncated_tmp);

  if (s21_is_less(truncated_tmp, int_min) ||
      s21_is_greater(truncated_tmp, int_max)) {
    err = CONV_ERROR_RETURN;
  } else {
    *dst = truncated_tmp.bits[0];
    if (s21_get_sign(src) && *dst != INT_MIN) *dst = -*dst;
  }

  return err;
}
