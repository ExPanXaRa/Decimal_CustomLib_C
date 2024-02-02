#include "../check_s21_decimal.h"

START_TEST(test_from_float_to_decimal_fail_inf) {
  float f = INFINITY;
  s21_decimal result;

  int err = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_minus_inf) {
  float f = -INFINITY;
  s21_decimal result;

  int err = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_nan) {
  float f = NAN;
  s21_decimal result;

  int err = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_minus_nan) {
  float f = -NAN;
  s21_decimal result;

  int err = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_null_ptr) {
  float f = 123.123;
  int err = s21_from_float_to_decimal(f, NULL);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_min_float) {
  float f = LT_MIN_FLOAT_TO_DECIMAL;
  s21_decimal result;

  int err = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_max_float) {
  float f = GT_MAX_FLOAT_TO_DECIMAL;
  s21_decimal result;

  int err = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_ok1) {
  float f = -0.0255207196;

  // -0.02552072
  s21_decimal decimal_check = {{0x26F108, 0x0, 0x0, 0x80080000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2) {
  float f = -0.00399137754;
  // -0.003991378
  s21_decimal decimal_check = {{0x3CE752, 0x0, 0x0, 0x80090000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok3) {
  float f = -0.0764362067;
  // -0.07643621
  s21_decimal decimal_check = {{0x74A1E5, 0x0, 0x0, 0x80080000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok4) {
  float f = 46282560;
  s21_decimal decimal_check = {{0x2C23740, 0x0, 0x0, 0x0}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok5) {
  float f = 5010.18115;
  // 5010.181
  s21_decimal decimal_check = {{0x4C7305, 0x0, 0x0, 0x30000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok6) {
  float f = -5010.18115;
  // 5010.181
  s21_decimal decimal_check = {{0x4C7305, 0x0, 0x0, 0x80030000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok7) {
  float f = -0.000745483907;
  // -0.0007454839
  s21_decimal decimal_check = {{0x71C077, 0x0, 0x0, 0x800A0000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok8) {
  float f = 0.0104842195;
  // 0.01048422
  s21_decimal decimal_check = {{0xFFF66, 0x0, 0x0, 0x80000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok9) {
  float f = -0.0104842195;
  // -0.01048422
  s21_decimal decimal_check = {{0xFFF66, 0x0, 0x0, 0x80080000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok10) {
  float f = -356700.438;
  // -356700.4
  s21_decimal decimal_check = {{0x366D9C, 0x0, 0x0, 0x80010000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok11) {
  float f = -3807398.25;
  // -3807398
  s21_decimal decimal_check = {{0x3A18A6, 0x0, 0x0, 0x80000000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok12) {
  float f = 807.082397;
  // 807.0824
  s21_decimal decimal_check = {{0x7B26A8, 0x0, 0x0, 0x40000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}
START_TEST(test_from_float_to_decimal_ok13) {
  float f = 0.0;
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok14) {
  float f = -0.0;
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  s21_assert_from_float_to_decimal(f, decimal_check);
}

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_float_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_float_to_decimal_fail_inf);
  tcase_add_test(tc_core, test_from_float_to_decimal_fail_minus_inf);
  tcase_add_test(tc_core, test_from_float_to_decimal_fail_nan);
  tcase_add_test(tc_core, test_from_float_to_decimal_fail_minus_nan);
  tcase_add_test(tc_core, test_from_float_to_decimal_fail_max_float);
  tcase_add_test(tc_core, test_from_float_to_decimal_fail_min_float);
  tcase_add_test(tc_core, test_from_float_to_decimal_fail_null_ptr);

  tcase_add_test(tc_core, test_from_float_to_decimal_ok1);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok2);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok3);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok4);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok5);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok6);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok7);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok8);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok9);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok10);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok11);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok12);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok13);
  tcase_add_test(tc_core, test_from_float_to_decimal_ok14);

  suite_add_tcase(s, tc_core);

  return s;
}

void s21_assert_from_float_to_decimal(float f, s21_decimal decimal_check) {
  s21_decimal res;

  int err = s21_from_float_to_decimal(f, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}