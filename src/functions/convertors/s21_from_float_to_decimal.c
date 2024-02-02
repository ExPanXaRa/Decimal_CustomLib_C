
#include "../s21_functions.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return CONV_ERROR_RETURN;

  s21_init_decimal(dst);

  if (src == 0.0) {
    if (signbit(src) != 0) s21_set_sign(dst, 1);
    return OK_RETURN;
  }

  if (fabsf(src) < MIN_FLOAT_TO_DECIMAL) return CONV_ERROR_RETURN;

  if ((isinf(src) || isnan(src)) || fabsf(src) > MAX_FLOAT_TO_DECIMAL) {
    s21_decimal inf = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    *dst = inf;
    if (signbit(src) != 0) s21_set_sign(dst, 1);
    return CONV_ERROR_RETURN;
  }

  s21_decimal res;
  char float_str[64];

  sprintf(float_str, "%.6E", fabsf(src));

  int exp = s21_get_float_exp(float_str);

  if (exp <= -23) {
    int precision = exp + 28;
    sprintf(float_str, "%.*E", precision, fabsf(src));
  }

  res = s21_float_str_to_decimal(float_str);

  if (signbit(src)) s21_set_sign(&res, 1);

  *dst = res;

  return OK_RETURN;
}
