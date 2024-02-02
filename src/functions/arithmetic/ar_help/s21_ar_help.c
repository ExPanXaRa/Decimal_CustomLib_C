#include "../../s21_functions.h"

s21_decimal s21_decimal_bank_round(s21_decimal int_part,
                                   s21_decimal fract_part) {
  s21_decimal zero_five = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal one;
  s21_init_decimal(&one);
  one.bits[0] = 1;

  s21_decimal res;

  if (s21_is_equal(fract_part, zero_five)) {
    if ((int_part.bits[0] & 1) != 1) {
      /* если число четное */
      res = int_part;
    } else {
      res = s21_binary_add(int_part, one);
    }
  } else if (s21_is_greater(fract_part, zero_five)) {
    res = s21_binary_add(int_part, one);
  } else {
    res = int_part;
  }

  return res;
}

int s21_get_shift_from_ld_to_decimal(s21_long_decimal value) {
  int res = 0;

  if (!(s21_decimal_binary_is_zero(value.decimals[0]) &&
        s21_decimal_binary_is_zero(value.decimals[1]))) {
    s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    s21_long_decimal max_decimal = s21_long_decimal_from_decimal(max);

    s21_long_decimal quotient =
        s21_long_decimal_binary_div(value, max_decimal, NULL);

    while (1) {
      int cmp =
          s21_binary_cmp(quotient.decimals[0], s21_decimal_ten_pow_value(res));
      if (cmp == -1 || !cmp) break;
      ++res;
    }

    s21_long_decimal tmp = s21_long_decimal_binary_div(
        value, s21_long_decimal_from_decimal(s21_decimal_ten_pow_value(res)),
        NULL);

    if (!s21_decimal_binary_is_zero(tmp.decimals[1]) ||
        tmp.decimals[0].bits[3] != 0) {
      ++res;
    }
  }

  return res;
}

int s21_calc_fraction(s21_long_decimal *res, s21_long_decimal value_bl,
                      s21_long_decimal *remainder) {
  int scale = 0;

  s21_decimal zero;
  s21_init_decimal(&zero);

  s21_long_decimal num = *res;
  s21_long_decimal tmp;
  s21_long_decimal tmp_remainder = *remainder;

  while ((s21_is_not_equal((*remainder).decimals[0], zero) ||
          s21_is_not_equal((*remainder).decimals[1], zero)) &&
         scale < 28) {
    s21_long_decimal num_stored = num;
    s21_long_decimal remainder_stored = tmp_remainder;

    num = s21_long_decimal_binary_mul(num, s21_decimal_ten_pow_value(1));
    tmp_remainder = s21_long_decimal_binary_mul(tmp_remainder,
                                                s21_decimal_ten_pow_value(1));
    tmp = s21_long_decimal_binary_div(tmp_remainder, value_bl, &tmp_remainder);
    num = s21_long_decimal_binary_add(num, tmp);

    if (!s21_decimal_validation(num.decimals[0])) {
      num = num_stored;
      tmp_remainder = remainder_stored;
      break;
    }

    ++scale;
  }

  *res = num;
  *remainder = tmp_remainder;

  return scale;
}
