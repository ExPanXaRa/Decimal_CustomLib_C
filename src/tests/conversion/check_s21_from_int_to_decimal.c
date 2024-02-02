#include "../check_s21_decimal.h"

START_TEST(test_from_int_to_decimal_fail_null_ptr) {
  int value = 0;
  int err = s21_from_int_to_decimal(value, NULL);
  ck_assert_int_eq(err, 1);
}

START_TEST(test_from_int_to_decimal_ok1) {
  int value = -2147483648;

  s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok2) {
  int value = -2147483647;

  s21_decimal decimal_check = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok3) {
  int value = -214748364;

  s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok4) {
  int value = -214748;

  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok5) {
  int value = -1000;

  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80000000}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok6) {
  int value = -1;

  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok7) {
  int value = 0;

  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok8) {
  int value = 1;

  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok9) {
  int value = 1000;

  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x0}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok10) {
  int value = 214748;

  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

  s21_assert_from_int_to_decimal(value, decimal_check);
}

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_int_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_int_to_decimal_fail_null_ptr);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok1);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok2);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok3);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok4);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok5);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok6);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok7);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok8);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok9);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok10);

  suite_add_tcase(s, tc_core);

  return s;
}

void s21_assert_from_int_to_decimal(int value, s21_decimal decimal_check) {
  s21_decimal res;
  int err = s21_from_int_to_decimal(value, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}
