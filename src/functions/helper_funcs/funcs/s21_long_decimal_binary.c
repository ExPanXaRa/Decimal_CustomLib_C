#include "../../s21_functions.h"

s21_long_decimal s21_long_decimal_binary_add(s21_long_decimal value_a,
                                             s21_long_decimal value_b) {
  s21_long_decimal res = value_a;
  s21_long_decimal tmp = value_b;

  while (!s21_decimal_binary_is_zero(tmp.decimals[0]) ||
         !s21_decimal_binary_is_zero(tmp.decimals[1])) {
    s21_long_decimal overflow_bits;
    overflow_bits.decimals[0] =
        s21_binary_and(res.decimals[0], tmp.decimals[0]);
    overflow_bits.decimals[1] =
        s21_binary_and(res.decimals[1], tmp.decimals[1]);

    overflow_bits = s21_long_decimal_left_shift(overflow_bits, 1);
    res.decimals[0] = s21_binary_xor(res.decimals[0], tmp.decimals[0]);
    res.decimals[1] = s21_binary_xor(res.decimals[1], tmp.decimals[1]);

    tmp = overflow_bits;
  }

  return res;
}

s21_long_decimal s21_long_decimal_binary_sub(s21_long_decimal value_a,
                                             s21_long_decimal value_b) {
  s21_long_decimal res;
  value_b.decimals[0] = s21_binary_not(value_b.decimals[0]);
  value_b.decimals[1] = s21_binary_not(value_b.decimals[1]);

  s21_long_decimal one;
  s21_init_long_decimal(&one);
  one.decimals[0].bits[0] = 1;

  value_b = s21_long_decimal_binary_add(value_b, one);
  res = s21_long_decimal_binary_add(value_a, value_b);

  return res;
}

s21_long_decimal s21_long_decimal_binary_div(s21_long_decimal value_a,
                                             s21_long_decimal value_b,
                                             s21_long_decimal *remainder) {
  s21_long_decimal res;

  s21_long_decimal part_remainder;
  s21_long_decimal quotient;

  s21_init_long_decimal(&part_remainder);
  s21_init_long_decimal(&quotient);

  if (s21_long_decimal_binary_cmp(value_a, value_b) == -1) {
    part_remainder = value_a;
  } else {
    int left_shift_a = s21_decimal_get_elder_bit(value_a.decimals[1]);
    if (left_shift_a == -1) {
      left_shift_a = s21_decimal_get_elder_bit(value_a.decimals[0]);
    } else {
      left_shift_a += MAX_SIZE;
    }

    int left_shift_b = s21_decimal_get_elder_bit(value_b.decimals[1]);
    if (left_shift_b == -1) {
      left_shift_b = s21_decimal_get_elder_bit(value_b.decimals[0]);
    } else {
      left_shift_b += MAX_SIZE;
    }

    int shift = left_shift_a - left_shift_b;

    s21_long_decimal shifted_divisor =
        s21_long_decimal_left_shift(value_b, shift);

    s21_long_decimal tmp_dividend = value_a;

    int is_sub_required = 1;

    while (shift >= 0) {
      if (is_sub_required) {
        part_remainder =
            s21_long_decimal_binary_sub(tmp_dividend, shifted_divisor);
      } else {
        part_remainder =
            s21_long_decimal_binary_add(tmp_dividend, shifted_divisor);
      }

      quotient = s21_long_decimal_left_shift(quotient, 1);

      if (!s21_get_bit(part_remainder.decimals[1], MAX_SIZE - 1)) {
        quotient.decimals[0] = s21_set_bit(quotient.decimals[0], 0);
      }

      tmp_dividend = s21_long_decimal_left_shift(part_remainder, 1);

      if (!s21_get_bit(part_remainder.decimals[1], MAX_SIZE - 1)) {
        is_sub_required = 1;
      } else {
        is_sub_required = 0;
      }
      --shift;
    }

    if (s21_get_bit(part_remainder.decimals[1], MAX_SIZE - 1)) {
      part_remainder =
          s21_long_decimal_binary_add(part_remainder, shifted_divisor);
    }

    part_remainder = s21_long_decimal_right_shift(part_remainder,
                                                  left_shift_a - left_shift_b);
  }

  res = quotient;
  if (remainder) {
    *remainder = part_remainder;
  }

  return res;
}

s21_long_decimal s21_long_decimal_binary_mul(s21_long_decimal value_a,
                                             s21_decimal value_b) {
  s21_decimal zero;
  s21_init_decimal(&zero);

  s21_long_decimal res = s21_long_decimal_from_decimal(zero);
  s21_long_decimal tmp = value_a;

  int max_bit = s21_decimal_get_elder_bit(value_b);

  for (int i = 0; i <= max_bit; i++) {
    if (s21_get_bit(value_b, i) != 0) {
      res = s21_long_decimal_binary_add(res, tmp);
    }

    tmp = s21_long_decimal_left_shift(tmp, 1);
  }

  return res;
}

int s21_long_decimal_binary_cmp(s21_long_decimal value_a,
                                s21_long_decimal value_b) {
  int cmp = s21_binary_cmp(value_a.decimals[1], value_b.decimals[1]);

  if (!cmp) cmp = s21_binary_cmp(value_a.decimals[0], value_b.decimals[0]);

  return cmp;
}

s21_long_decimal s21_long_decimal_left_shift(s21_long_decimal value,
                                             int shift) {
  s21_long_decimal res = value;
  while (shift > 0) {
    int bit0 = s21_get_bit(res.decimals[0], MAX_SIZE - 1);
    res.decimals[0] = s21_binary_left_shift_by_one(res.decimals[0]);
    res.decimals[1] = s21_binary_left_shift_by_one(res.decimals[1]);
    if (bit0) {
      res.decimals[1] = s21_set_bit(res.decimals[1], 0);
    }
    --shift;
  }

  return res;
}

s21_long_decimal s21_long_decimal_right_shift(s21_long_decimal value,
                                              int shift) {
  s21_long_decimal res = value;
  while (shift > 0) {
    int bits1 = s21_get_bit(res.decimals[1], 0);
    res.decimals[0] = s21_binary_right_shift_by_one(res.decimals[0]);
    res.decimals[1] = s21_binary_right_shift_by_one(res.decimals[1]);
    if (bits1) {
      res.decimals[0] = s21_set_bit(res.decimals[0], MAX_SIZE - 1);
    }
    --shift;
  }

  return res;
}
