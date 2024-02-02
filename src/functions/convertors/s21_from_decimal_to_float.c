#include "../s21_functions.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return CONV_ERROR_RETURN;

  if (!s21_decimal_validation(src)) return CONV_ERROR_RETURN;

  int err = OK_RETURN;
  *dst = 0.0;

  if (s21_mantissa_is_zero(src)) {
    if (s21_get_sign(src)) *dst = -0.0;
  } else {
    double tmp = 0.0;

    for (int i = 0; i < MANTISSA_SIZE; i++) {
      if (s21_get_bit(src, i)) {
        tmp += pow(2.0, i);
      }
    }

    int scale = s21_get_scale(src);
    while (scale != 0) {
      tmp /= 10.0;
      --scale;
    }

    if (s21_get_sign(src)) tmp *= -1.0;

    *dst = (float)tmp;
  }

  return err;
}