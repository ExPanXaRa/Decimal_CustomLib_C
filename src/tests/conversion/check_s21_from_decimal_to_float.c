#include "../check_s21_decimal.h"

START_TEST(test_from_decimal_to_float_fail_null_ptr) {
  s21_decimal value = {{0x4F02F7, 0x269, 0x0, 0xC0000}};

  int err = s21_from_decimal_to_float(value, NULL);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_invalid_scale) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  float res;
  int err = s21_from_decimal_to_float(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_invalid_value) {
  s21_decimal value = {{-1, 0, 0, 0x1C0001}};
  float res;
  int err = s21_from_decimal_to_float(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_ok1) {
  // 2.649999999735
  s21_decimal value = {{0x4F02F7, 0x269, 0x0, 0xC0000}};
  float check = 2.649999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok2) {
  // -0.9999999999
  s21_decimal value = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
  float check = -0.999999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok3) {
  // -2.649999999735
  s21_decimal value = {{0x4F02F7, 0x269, 0x0, 0x800C0000}};
  float check = -2.649999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok4) {
  // 0.99999999999999999999
  s21_decimal value = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
  float check = 0.999999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok5) {
  // -0.99999999999999999999
  s21_decimal value = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
  float check = -0.999999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok6) {
  // 2.6499999999999999999735
  s21_decimal value = {{0x8B8FFEF7, 0x91607CFB, 0x59C, 0x160000}};
  float check = 2.649999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok7) {
  // -2.6499999999999999999735
  s21_decimal value = {{0x8B8FFEF7, 0x91607CFB, 0x59C, 0x80160000}};
  float check = -2.649999;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok8) {
  // -0
  s21_decimal value = {{0x0, 0x0, 0x0, 0x80000000}};
  float check = -0.0;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok9) {
  // 0
  s21_decimal value = {{0x0, 0x0, 0x0, 0x0}};
  float check = 0.0;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok10) {
  // -0.0
  s21_decimal value = {{0x0, 0x0, 0x0, 0x80010000}};
  float check = -0.0;

  s21_assert_from_decimal_to_float(value, check);
}

START_TEST(test_from_decimal_to_float_ok11) {
  // 0.0
  s21_decimal value = {{0x0, 0x0, 0x0, 0x10000}};
  float check = 0.0;

  s21_assert_from_decimal_to_float(value, check);
}

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_decimal_to_float");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_decimal_to_float_ok1);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok2);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok3);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok4);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok5);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok6);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok7);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok8);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok9);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok10);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok11);

  tcase_add_test(tc_core, test_from_decimal_to_float_fail_null_ptr);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_invalid_value);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_invalid_scale);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_from_decimal_to_float(s21_decimal value, float check) {
  float res;
  int err = s21_from_decimal_to_float(value, &res);

  ck_assert_float_eq_tol(res, check, 0.00001);
  ck_assert_int_eq(err, 0);
}