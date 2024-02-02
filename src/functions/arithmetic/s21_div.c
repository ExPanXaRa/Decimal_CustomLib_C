#include "../s21_functions.h"

int s21_handle_div(s21_long_decimal value_bl, s21_long_decimal res,
                   s21_long_decimal remainder, s21_decimal *result) {
  int err = OK_RETURN;

  s21_decimal zero;
  s21_init_decimal(&zero);

  int scale_1 = s21_calc_fraction(&res, value_bl, &remainder);
  s21_long_decimal tmp_res = s21_long_decimal_from_decimal(zero);
  int scale_2 = s21_calc_fraction(&tmp_res, value_bl, &remainder);

  s21_set_scale(&tmp_res.decimals[0], scale_2);

  s21_decimal zero_five = {{0x5, 0x0, 0x0, 0x10000}};

  if (s21_is_equal(tmp_res.decimals[0], zero_five)) {
    if (s21_is_not_equal(remainder.decimals[0], zero) ||
        s21_is_not_equal(remainder.decimals[1], zero)) {
      s21_decimal min_decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
      s21_add(tmp_res.decimals[0], min_decimal, &tmp_res.decimals[0]);
    }
  }

  res.decimals[0] =
      s21_decimal_bank_round(res.decimals[0], tmp_res.decimals[0]);

  s21_set_scale(&res.decimals[0], scale_1);
  if (s21_is_not_equal(res.decimals[1], zero) ||
      !s21_decimal_validation(res.decimals[0])) {
    err = TOO_BIG_RETURN;
    s21_init_decimal(result);
  } else {
    *result = res.decimals[0];
  }

  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero;
  s21_init_decimal(&zero);

  if (!result) return ANOTHER_ERROR_RETURN;

  if (!s21_decimal_validation(value_1) || !s21_decimal_validation(value_2)) {
    s21_init_decimal(result);
    return ANOTHER_ERROR_RETURN;
  }

  if (s21_is_equal(value_2, zero)) {
    s21_init_decimal(result);
    return DIV_BY_ZERO_RETURN;
  }

  int err = OK_RETURN;

  s21_init_decimal(result);

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  s21_long_decimal val_1l;
  s21_long_decimal val_2l;

  s21_decimal_normalization(value_1, value_2, &val_1l, &val_2l);

  s21_long_decimal remainder = s21_long_decimal_from_decimal(zero);
  s21_long_decimal res;

  res = s21_long_decimal_binary_div(val_1l, val_2l, &remainder);

  if (res.decimals[0].bits[3] != 0 || s21_is_not_equal(res.decimals[1], zero)) {
    if (sign1 != sign2) {
      err = TOO_SMALL_RETURN;
    } else {
      err = TOO_BIG_RETURN;
    }

    s21_init_decimal(result);
  } else {
    err = s21_handle_div(val_2l, res, remainder, result);

    if (sign1 != sign2) {
      s21_set_sign(result, 1);
    }

    if (s21_get_sign(*result) && err == TOO_BIG_RETURN) {
      err = TOO_SMALL_RETURN;
    }

    if (err == OK_RETURN && s21_is_not_equal(value_1, zero) &&
        s21_is_equal(*result, zero)) {
      err = TOO_SMALL_RETURN;
    }
  }

  return err;
}
