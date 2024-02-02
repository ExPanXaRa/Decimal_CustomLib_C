#include "../s21_functions.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return CONV_ERROR_RETURN;

  int err = OK_RETURN;
  s21_init_decimal(dst);

  if (src < 0) {
    s21_set_sign(dst, 1);
    if (src != INT_MIN) src = -src;
  }

  dst->bits[0] = src;

  return err;
}