#include "../../s21_functions.h"

int s21_int_get_bit(int value, int pos) { return !!(value & (1U << pos)); }

int s21_int_set_bit(int value, int pos) { return value | (1U << pos); }

int s21_get_bit(s21_decimal value, int pos) {
  return s21_int_get_bit(value.bits[pos / BLOCK_SIZE], pos % BLOCK_SIZE);
}

s21_decimal s21_set_bit(s21_decimal value, int pos) {
  value.bits[pos / 32] =
      s21_int_set_bit(value.bits[pos / BLOCK_SIZE], pos % BLOCK_SIZE);
  return value;
}

int s21_mantissa_get_elder_bit(s21_decimal value) {
  int elder_bit = -1;

  for (int i = MANTISSA_SIZE - 1; i >= 0; i--) {
    if (s21_get_bit(value, i)) {
      elder_bit = i;
      break;
    }
  }

  return elder_bit;
}

int s21_decimal_get_elder_bit(s21_decimal value) {
  int elder_bit = -1;

  for (int i = MAX_SIZE - 1; i >= 0; i--) {
    if (s21_get_bit(value, i)) {
      elder_bit = i;
      break;
    }
  }

  return elder_bit;
}

int s21_decimal_binary_is_zero(s21_decimal value) {
  int res = 1;

  for (int i = 0; i < 4; i++) {
    if (value.bits[i] != 0) res = 0;
  }

  return res;
}

s21_decimal s21_binary_and(s21_decimal value_a, s21_decimal value_b) {
  s21_decimal res;
  s21_init_decimal(&res);

  for (int i = 0; i < 4; i++) {
    res.bits[i] = value_a.bits[i] & value_b.bits[i];
  }

  return res;
}

s21_decimal s21_binary_xor(s21_decimal value_a, s21_decimal value_b) {
  s21_decimal res;
  s21_init_decimal(&res);

  for (int i = 0; i < 4; i++) {
    res.bits[i] = value_a.bits[i] ^ value_b.bits[i];
  }

  return res;
}

s21_decimal s21_binary_not(s21_decimal value) {
  s21_decimal res;
  s21_init_decimal(&res);

  for (int i = 0; i < 4; i++) {
    res.bits[i] = ~value.bits[i];
  }

  return res;
}

s21_long_decimal s21_decimal_binary_mul(s21_decimal value_a,
                                        s21_decimal value_b) {
  s21_long_decimal long_res;
  s21_init_long_decimal(&long_res);

  s21_long_decimal long_tmp_a = s21_long_decimal_from_decimal(value_a);

  int elder_bit = s21_decimal_get_elder_bit(value_b);

  for (int i = 0; i <= elder_bit; i++) {
    if (s21_get_bit(value_b, i) != 0) {
      long_res = s21_long_decimal_binary_add(long_res, long_tmp_a);
    }
    long_tmp_a = s21_long_decimal_left_shift(long_tmp_a, 1);
  }

  return long_res;
}

s21_decimal s21_binary_div(s21_decimal value_a, s21_decimal value_b,
                           s21_decimal *remainder) {
  s21_decimal res;

  s21_decimal part_remainder;

  s21_decimal quotient;
  s21_init_decimal(&part_remainder);
  s21_init_decimal(&quotient);

  if (!s21_mantissa_is_zero(value_a) &&
      s21_binary_cmp(value_a, value_b) != -1) {
    int left_shift_a = s21_decimal_get_elder_bit(value_a);
    int left_shift_b = s21_decimal_get_elder_bit(value_b);
    int shift = left_shift_a - left_shift_b;

    s21_decimal shifted_divisor = s21_binary_left_shift(value_b, shift);

    s21_decimal tmp_dividend = value_a;

    int is_sub_required = 1;

    while (shift >= 0) {
      if (is_sub_required) {
        part_remainder = s21_binary_sub(tmp_dividend, shifted_divisor);
      } else {
        part_remainder = s21_binary_add(tmp_dividend, shifted_divisor);
      }

      quotient = s21_binary_left_shift_by_one(quotient);

      if (!s21_get_bit(part_remainder, MAX_SIZE - 1)) {
        quotient = s21_set_bit(quotient, 0);
      }

      tmp_dividend = s21_binary_left_shift_by_one(part_remainder);

      if (!s21_get_bit(part_remainder, MAX_SIZE - 1)) {
        is_sub_required = 1;
      } else {
        is_sub_required = 0;
      }
      --shift;
    }

    if (s21_get_bit(part_remainder, MAX_SIZE - 1)) {
      part_remainder = s21_binary_add(part_remainder, shifted_divisor);
    }

    part_remainder =
        s21_binary_right_shift(part_remainder, left_shift_a - left_shift_b);
  } else if (s21_binary_cmp(value_a, value_b) == -1) {
    part_remainder = value_a;
  }

  res = quotient;
  if (remainder != NULL) {
    *remainder = part_remainder;
  }

  return res;
}

s21_decimal s21_binary_add(s21_decimal value_a, s21_decimal value_b) {
  s21_decimal res = value_a;
  s21_decimal tmp = value_b;

  while (!s21_decimal_binary_is_zero(tmp)) {
    s21_decimal overflow_bits = s21_binary_and(res, tmp);
    overflow_bits = s21_binary_left_shift(overflow_bits, 1);
    res = s21_binary_xor(res, tmp);
    tmp = overflow_bits;
  }

  return res;
}

s21_decimal s21_binary_sub(s21_decimal value_a, s21_decimal value_b) {
  s21_decimal res;
  s21_decimal tmp;
  s21_init_decimal(&tmp);
  tmp.bits[0] = 1;

  value_b = s21_binary_not(value_b);
  value_b = s21_binary_add(value_b, tmp);
  res = s21_binary_add(value_a, value_b);

  return res;
}

int s21_binary_cmp(s21_decimal a, s21_decimal b) {
  int res = 0;

  for (int i = MAX_SIZE - 1; i >= 0; i--) {
    int bit_a = s21_get_bit(a, i);
    int bit_b = s21_get_bit(b, i);

    if (!bit_a && bit_b) res = -1;

    if (bit_a && !bit_b) res = 1;

    if (res != 0) break;
  }

  return res;
}

s21_decimal s21_binary_left_shift_by_one(s21_decimal value) {
  s21_decimal res;
  s21_init_decimal(&res);

  unsigned int res0 = value.bits[0];
  unsigned int res1 = value.bits[1];
  unsigned int res2 = value.bits[2];
  unsigned int res3 = value.bits[3];

  int bits0 = s21_int_get_bit(value.bits[0], BLOCK_SIZE - 1);
  int bits1 = s21_int_get_bit(value.bits[1], BLOCK_SIZE - 1);
  int bits2 = s21_int_get_bit(value.bits[2], BLOCK_SIZE - 1);

  res0 <<= 1;
  res1 <<= 1;
  res2 <<= 1;
  res3 <<= 1;

  res.bits[0] = res0;
  res.bits[1] = res1;
  res.bits[2] = res2;
  res.bits[3] = res3;

  if (bits0) res.bits[1] = s21_int_set_bit(res.bits[1], 0);

  if (bits1) res.bits[2] = s21_int_set_bit(res.bits[2], 0);

  if (bits2) res.bits[3] = s21_int_set_bit(res.bits[3], 0);

  return res;
}

s21_decimal s21_binary_right_shift_by_one(s21_decimal value) {
  s21_decimal res;
  s21_init_decimal(&res);

  unsigned int res3 = value.bits[3];
  unsigned int res2 = value.bits[2];
  unsigned int res1 = value.bits[1];
  unsigned int res0 = value.bits[0];

  int bits3 = s21_int_get_bit(value.bits[3], 0);
  int bits2 = s21_int_get_bit(value.bits[2], 0);
  int bits1 = s21_int_get_bit(value.bits[1], 0);

  res3 >>= 1;
  res2 >>= 1;
  res1 >>= 1;
  res0 >>= 1;

  res.bits[3] = res3;
  res.bits[2] = res2;
  res.bits[1] = res1;
  res.bits[0] = res0;

  if (bits3) res.bits[2] = s21_int_set_bit(res.bits[2], BLOCK_SIZE - 1);

  if (bits2) res.bits[1] = s21_int_set_bit(res.bits[1], BLOCK_SIZE - 1);

  if (bits1) res.bits[0] = s21_int_set_bit(res.bits[0], BLOCK_SIZE - 1);

  return res;
}

s21_decimal s21_binary_left_shift(s21_decimal value, int shift) {
  s21_decimal res = value;

  while (shift > 0) {
    res = s21_binary_left_shift_by_one(res);
    --shift;
  }
  return res;
}

s21_decimal s21_binary_right_shift(s21_decimal value, int shift) {
  s21_decimal res = value;

  while (shift > 0) {
    res = s21_binary_right_shift_by_one(res);
    --shift;
  }

  return res;
}

void s21_decimal_normalization(s21_decimal value_a, s21_decimal value_b,
                               s21_long_decimal *value_al,
                               s21_long_decimal *value_bl) {
  s21_decimal tmp1 = value_a;
  s21_decimal tmp2 = value_b;

  int scale_a = s21_get_scale(value_a);
  int scale_b = s21_get_scale(value_b);

  tmp1.bits[3] = 0;
  tmp2.bits[3] = 0;

  if (scale_a > scale_b) {
    *value_al = s21_long_decimal_from_decimal(tmp1);
    *value_bl = s21_decimal_binary_mul(
        tmp2, s21_decimal_ten_pow_value(scale_a - scale_b));
  } else if (scale_a < scale_b) {
    *value_al = s21_decimal_binary_mul(
        tmp1, s21_decimal_ten_pow_value(scale_b - scale_a));
    *value_bl = s21_long_decimal_from_decimal(tmp2);
  } else {
    *value_al = s21_long_decimal_from_decimal(tmp1);
    *value_bl = s21_long_decimal_from_decimal(tmp2);
  }
}

s21_decimal s21_remove_trailing_zeros(s21_decimal value) {
  s21_decimal res = value;
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);

  if (scale > 0 && s21_decimal_validation(value)) {
    s21_decimal remainder;
    s21_init_decimal(&remainder);
    s21_decimal tmp = value;
    tmp.bits[3] = 0;

    int stop = 0;
    while ((!stop && scale > 0)) {
      tmp = s21_binary_div(tmp, s21_decimal_ten_pow_value(1), &remainder);
      if (s21_decimal_binary_is_zero(remainder)) {
        --scale;
        res = tmp;
      } else {
        stop = 1;
      }
    }
    s21_set_scale(&res, scale);
    s21_set_sign(&res, sign);
  }

  return res;
}
