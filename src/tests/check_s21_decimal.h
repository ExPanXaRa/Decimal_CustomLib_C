#ifndef CHECK_S21_DECIMAL_H
#define CHECK_S21_DECIMAL_H

#include <check.h>

#include "../s21_decimal.h"

#define GT_MAX_FLOAT_TO_DECIMAL 7922815773391897854723898736640.0f
#define LT_MIN_FLOAT_TO_DECIMAL \
  0.0000000000000000000000000000000000000000317107681509710513471323135264753814751475646110991f

Suite *s21_add_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);

Suite *s21_is_less_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_is_greater_or_equal_suite(void);
Suite *s21_is_not_equal_suite(void);

Suite *s21_from_decimal_to_float_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_int_to_decimal_suite(void);

Suite *s21_floor_suite(void);
Suite *s21_negate_suite(void);
Suite *s21_round_suite(void);
Suite *s21_truncate_suite(void);

void s21_assert_add(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check);
void s21_assert_sub(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check);
void s21_assert_mul(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check);
void s21_assert_div(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check);

void s21_assert_is_less(s21_decimal value_a, s21_decimal value_b, int check);
void s21_assert_is_equal(s21_decimal value_a, s21_decimal value_b, int check);
void s21_assert_is_less_or_equal(s21_decimal value_a, s21_decimal value_b,
                                 int check);
void s21_assert_is_greater(s21_decimal value_a, s21_decimal value_b, int check);
void s21_assert_is_greater_or_equal(s21_decimal value_a, s21_decimal value_b,
                                    int check);
void s21_assert_is_not_equal(s21_decimal value_a, s21_decimal value_b,
                             int check);

void s21_assert_from_decimal_to_float(s21_decimal value, float check);
void s21_assert_from_decimal_to_int(s21_decimal value, int check);
void s21_assert_from_float_to_decimal(float value, s21_decimal check);
void s21_assert_from_int_to_decimal(int value, s21_decimal check);

void s21_assert_floor(s21_decimal value, s21_decimal decimal_check);
void s21_assert_negate(s21_decimal value, s21_decimal decimal_check);
void s21_assert_round(s21_decimal value, s21_decimal decimal_check);
void s21_assert_truncate(s21_decimal value, s21_decimal decimal_check);

#endif  // CHECK_S21_DECIMAL_H
