#include "../s21_functions.h"

int s21_handle_add(s21_decimal value_a, s21_decimal value_b,
                   s21_decimal *result) {
  int err = OK_RETURN;
  s21_long_decimal value_al;
  s21_long_decimal value_bl;

  int scale_a = s21_get_scale(value_a);
  int scale_b = s21_get_scale(value_b);

  int max_scale = scale_a > scale_b ? scale_a : scale_b;

  s21_decimal_normalization(value_a, value_b, &value_al, &value_bl);

  s21_long_decimal res = s21_long_decimal_binary_add(value_al, value_bl);

  int shift = s21_get_shift_from_ld_to_decimal(res);

  int res_scale = max_scale - shift;

  if (res_scale < 0) {
    err = TOO_BIG_RETURN;
    s21_init_decimal(result);
  } else {
    while (shift > 28) {
      res = s21_long_decimal_binary_div(
          res, s21_long_decimal_from_decimal(s21_decimal_ten_pow_value(1)),
          NULL);
      --shift;
    }

    s21_long_decimal remainder;
    s21_init_long_decimal(&remainder);
    s21_long_decimal ten_pow =
        s21_long_decimal_from_decimal(s21_decimal_ten_pow_value(shift));

    res = s21_long_decimal_binary_div(res, ten_pow, &remainder);

    s21_set_scale(&remainder.decimals[0], shift);

    res.decimals[0] =
        s21_decimal_bank_round(res.decimals[0], remainder.decimals[0]);

    s21_set_scale(&res.decimals[0], res_scale);

    if (!s21_decimal_validation(res.decimals[0]) ||
        !s21_decimal_binary_is_zero(res.decimals[1])) {
      err = TOO_BIG_RETURN;
    } else {
      *result = res.decimals[0];
    }
  }

  return err;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return ANOTHER_ERROR_RETURN;

  if (!s21_decimal_validation(value_1) || !s21_decimal_validation(value_2)) {
    s21_init_decimal(result);
    return ANOTHER_ERROR_RETURN;
  }

  int err = OK_RETURN;
  s21_init_decimal(result);

  s21_decimal tmp;
  s21_init_decimal(&tmp);

  if (!s21_get_sign(value_1) && !s21_get_sign(value_2)) {
    err = s21_handle_add(value_1, value_2, &tmp);
  } else if (!s21_get_sign(value_1) && s21_get_sign(value_2)) {
    s21_decimal tmp_val2 = value_2;
    s21_set_sign(&tmp_val2, 0);
    err = s21_sub(value_1, tmp_val2, &tmp);

  } else if (s21_get_sign(value_1) && !s21_get_sign(value_2)) {
    s21_decimal tmp_val1 = value_1;
    s21_set_sign(&tmp_val1, 0);
    err = s21_sub(tmp_val1, value_2, &tmp);
    s21_negate(tmp, &tmp);

  } else if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
    s21_decimal tmp_val1 = value_1;
    s21_decimal tmp_val2 = value_2;
    s21_set_sign(&tmp_val1, 0);
    s21_set_sign(&tmp_val2, 0);

    err = s21_handle_add(tmp_val1, tmp_val2, &tmp);
    s21_negate(tmp, &tmp);
  }

  if (err == TOO_BIG_RETURN && s21_get_sign(tmp)) err = TOO_SMALL_RETURN;

  *result = tmp;

  return err;
}
