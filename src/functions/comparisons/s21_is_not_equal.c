#include "../s21_functions.h"

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !(s21_is_equal(a, b));
}