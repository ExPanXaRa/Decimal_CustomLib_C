#include "../s21_functions.h"

int s21_handle_is_less(s21_decimal a, s21_decimal b) {
  int res = 0;

  s21_decimal tmp_a = a;
  s21_decimal tmp_b = b;

  s21_long_decimal tmp_al;
  s21_long_decimal tmp_bl;

  if (s21_get_sign(tmp_a) && s21_get_sign(tmp_b)) {
    s21_set_sign(&tmp_a, 0);
    s21_set_sign(&tmp_b, 0);
  }

  s21_decimal_normalization(tmp_a, tmp_b, &tmp_al, &tmp_bl);

  int cmp = s21_long_decimal_binary_cmp(tmp_al, tmp_bl);

  if (cmp == -1) res = 1;

  return res;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  int res = 0;

  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  if ((s21_mantissa_is_zero(a) && s21_mantissa_is_zero(b))) {
    res = 0;
  } else if (sign_a != sign_b) {
    res = sign_a > sign_b;
  } else if (sign_a && sign_b) {
    res = s21_handle_is_less(b, a);
  } else {
    res = s21_handle_is_less(a, b);
  }
  return res;
}
