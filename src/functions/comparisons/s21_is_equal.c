#include "../s21_functions.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int eq = 1;

  s21_decimal tmp_a = s21_remove_trailing_zeros(a);
  s21_decimal tmp_b = s21_remove_trailing_zeros(b);

  if (!(s21_mantissa_is_zero(tmp_a) && s21_mantissa_is_zero(tmp_b))) {
    for (int i = 0; i < 4; i++) {
      if (tmp_a.bits[i] != tmp_b.bits[i]) {
        eq = 0;
      }
    }
  }

  return eq;
}
