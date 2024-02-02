#include "../s21_functions.h"

int s21_handle_mul(s21_decimal value_a, s21_decimal value_b,
                   s21_decimal *result) {
  int err = OK_RETURN;
  s21_decimal zero;
  s21_init_decimal(&zero);
  int scale_a = s21_get_scale(value_a);
  int scale_b = s21_get_scale(value_b);

  value_a.bits[3] = 0;
  value_b.bits[3] = 0;

  s21_long_decimal res = s21_decimal_binary_mul(value_a, value_b);

  int shift = s21_get_shift_from_ld_to_decimal(res);
  int res_scale = scale_a + scale_b - shift;

  if (res_scale >= 0) {
    while (shift > 28) {
      res = s21_long_decimal_binary_div(
          res, s21_long_decimal_from_decimal(s21_decimal_ten_pow_value(1)),
          NULL);
      --shift;
    }

    if (res_scale > 28) {
      s21_long_decimal tmp = res;
      int tmp_scale = res_scale;
      while (tmp_scale > 28) {
        tmp = s21_long_decimal_binary_div(
            tmp, s21_long_decimal_from_decimal(s21_decimal_ten_pow_value(1)),
            NULL);
        --tmp_scale;
      }
      shift = res_scale - tmp_scale + shift;
      res_scale = tmp_scale;
    }

    s21_long_decimal remainder;
    s21_long_decimal ten_pow =
        s21_long_decimal_from_decimal(s21_decimal_ten_pow_value(shift));

    s21_init_long_decimal(&remainder);
    res = s21_long_decimal_binary_div(res, ten_pow, &remainder);

    s21_set_scale(&remainder.decimals[0], shift);

    res.decimals[0] =
        s21_decimal_bank_round(res.decimals[0], remainder.decimals[0]);

    s21_set_scale(&res.decimals[0], res_scale);

    if (!s21_decimal_validation(res.decimals[0]) ||
        s21_is_not_equal(res.decimals[1], zero)) {
      err = TOO_BIG_RETURN;
    } else {
      *result = res.decimals[0];
    }
  } else {
    err = TOO_BIG_RETURN;
    s21_init_decimal(result);
  }

  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = OK_RETURN;

  if (!result) return ANOTHER_ERROR_RETURN;

  if (!s21_decimal_validation(value_1) || !s21_decimal_validation(value_2)) {
    s21_init_decimal(result);
    return ANOTHER_ERROR_RETURN;
  }

  s21_init_decimal(result);
  s21_decimal tmp;
  s21_init_decimal(&tmp);

  if (!s21_get_sign(value_1) && !s21_get_sign(value_2)) {
    err = s21_handle_mul(value_1, value_2, &tmp);
  } else if (!s21_get_sign(value_1) && s21_get_sign(value_2)) {
    s21_decimal tmp_val_2 = value_2;
    s21_set_sign(&tmp_val_2, 0);

    err = s21_handle_mul(value_1, tmp_val_2, &tmp);
    s21_negate(tmp, &tmp);

  } else if (s21_get_sign(value_1) && !s21_get_sign(value_2)) {
    s21_decimal tmp_val_1 = value_1;
    s21_set_sign(&tmp_val_1, 0);

    err = s21_handle_mul(tmp_val_1, value_2, &tmp);
    s21_negate(tmp, &tmp);

  } else if ((s21_get_sign(value_1) && s21_get_sign(value_2))) {
    s21_decimal tmp_val_1 = value_1;
    s21_decimal tmp_val_2 = value_2;

    s21_set_sign(&tmp_val_1, 0);
    s21_set_sign(&tmp_val_2, 0);

    err = s21_handle_mul(tmp_val_1, tmp_val_2, &tmp);
  }

  if (err == TOO_BIG_RETURN) {
    if (s21_get_sign(tmp)) err = TOO_SMALL_RETURN;
  }

  s21_decimal zero;
  s21_init_decimal(&zero);
  if (!err && s21_is_not_equal(value_1, zero) &&
      s21_is_not_equal(value_2, zero) && s21_is_equal(tmp, zero)) {
    err = TOO_SMALL_RETURN;
  }

  *result = tmp;

  return err;
}
