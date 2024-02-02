#include "../../s21_functions.h"

int s21_get_sign(s21_decimal value) { return ((value.bits[3] >> 31) & 1); }

void s21_set_sign(s21_decimal* value, int sign) {
  if (value) {
    if (sign) {
      value->bits[3] |= MINUS;
    } else {
      value->bits[3] &= ~MINUS;
    }
  }
}

int s21_get_scale(s21_decimal value) { return (value.bits[3] & SCALE) >> 16; }

int s21_set_scale(s21_decimal* value, int scale) {
  int res = 1;
  if (value) {
    if (scale <= 28 && scale >= 0) {
      res = 0;
      value->bits[3] |= (scale << 16) & SCALE;
    }
  }

  return res;
}

int s21_get_float_exp(char* str) {
  int res = 0;
  char* tmp = str;
  while (*tmp != '\0') {
    if (*tmp == 'E') {
      ++tmp;
      res = strtol(tmp, NULL, 10);
      break;
    }
    ++tmp;
  }

  return res;
}

int s21_mantissa_is_zero(s21_decimal value) {
  int res = 0;
  if ((value.bits[0] == 0) && (value.bits[1] == 0) && (value.bits[2] == 0)) {
    res = 1;
  }

  return res;
}

void s21_copy_decimal_to_decimal(s21_decimal value, s21_decimal* dst) {
  if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = value.bits[i];
    }
  }
}

void s21_init_decimal(s21_decimal* dst) {
  if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
  }
}

void s21_init_long_decimal(s21_long_decimal* dst) {
  if (dst) {
    s21_init_decimal(&dst->decimals[0]);
    s21_init_decimal(&dst->decimals[1]);
  }
}

int s21_check_unused_bits(s21_decimal value) {
  int res = 0;

  if ((value.bits[3] & 0x7F00FFFF) != 0) {
    res = 1;
  }

  return res;
}

int s21_decimal_validation(s21_decimal value) {
  int res = 1;
  if (s21_check_unused_bits(value) ||
      (s21_get_scale(value) < 0 || s21_get_scale(value) > 28)) {
    res = 0;
  }

  return res;
}

s21_long_decimal s21_long_decimal_from_decimal(s21_decimal value_0) {
  s21_long_decimal res;
  s21_init_long_decimal(&res);

  res.decimals[0] = value_0;

  return res;
}

s21_decimal s21_decimal_ten_pow_value(int value) {
  TEN_POW_VALUES;
  return ten_pow_values[value];
}

s21_decimal s21_decimal_from_char(char ch) {
  s21_decimal res;
  s21_init_decimal(&res);

  if (ch != '0') s21_from_int_to_decimal(ch - '0', &res);

  return res;
}

s21_decimal s21_float_str_to_decimal(char* str) {
  char* tmp_str = str;
  int count = 6;
  s21_decimal res;
  s21_init_decimal(&res);

  int exp = s21_get_float_exp(str);

  while (*tmp_str != '\0') {
    if (*tmp_str == '.') {
      ++tmp_str;
    } else if (isdigit(*tmp_str)) {
      s21_decimal tmp;
      s21_init_decimal(&tmp);
      s21_mul(s21_decimal_from_char(*tmp_str), s21_decimal_ten_pow_value(count),
              &tmp);

      s21_add(res, tmp, &res);
      --count;
      ++tmp_str;
    } else {
      break;
    }
  }

  int scale = exp - 6;

  if (scale > 0) {
    s21_mul(res, s21_decimal_ten_pow_value(scale), &res);
  } else if (scale < 0) {
    if (scale < -28) {
      s21_div(res, s21_decimal_ten_pow_value(28), &res);
      scale += 28;
    }
    s21_div(res, s21_decimal_ten_pow_value(-scale), &res);
  }

  return res;
}