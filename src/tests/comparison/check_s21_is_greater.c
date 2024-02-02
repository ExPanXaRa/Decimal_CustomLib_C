#include "../check_s21_decimal.h"

START_TEST(test_is_greater_ok1) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // -1.22
  s21_decimal value_b = {{0x7A, 0x0, 0x0, 0x80020000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok2) {
  // -1.22
  s21_decimal value_a = {{0x7A, 0x0, 0x0, 0x80020000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok3) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1.230001
  s21_decimal value_b = {{0x12C4B1, 0x0, 0x0, 0x60000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok4) {
  // 1.230001
  s21_decimal value_a = {{0x12C4B1, 0x0, 0x0, 0x60000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok5) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // -1.230001
  s21_decimal value_b = {{0x12C4B1, 0x0, 0x0, 0x80060000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok6) {
  // -1.230001
  s21_decimal value_a = {{0x12C4B1, 0x0, 0x0, 0x80060000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok7) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok8) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok9) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // -1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x80050000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok10) {
  // -1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x80050000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok11) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok12) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok13) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // -1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x80000000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok14) {
  // -1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok15) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1431655765.00000
  s21_decimal value_b = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok16) {
  // 1431655765.00000
  s21_decimal value_a = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok17) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // -1431655765.00000
  s21_decimal value_b = {{0x5554D320, 0x8235, 0x0, 0x80050000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok18) {
  // -1431655765.00000
  s21_decimal value_a = {{0x5554D320, 0x8235, 0x0, 0x80050000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok19) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1431655765.000000000000000001
  s21_decimal value_b = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x120000}};
  int check = 0;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok20) {
  // 1431655765.000000000000000001
  s21_decimal value_a = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x120000}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok21) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // -1431655765.000000000000000001
  s21_decimal value_b = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x80120000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

START_TEST(test_is_greater_ok22) {
  // -1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x80050000}};
  // -52818775009509558395695966890
  s21_decimal value_b = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  int check = 1;

  s21_assert_is_greater(value_a, value_b, check);
}

Suite *s21_is_greater_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_is_greater");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_greater_ok1);
  tcase_add_test(tc_core, test_is_greater_ok2);
  tcase_add_test(tc_core, test_is_greater_ok3);
  tcase_add_test(tc_core, test_is_greater_ok4);
  tcase_add_test(tc_core, test_is_greater_ok5);
  tcase_add_test(tc_core, test_is_greater_ok6);
  tcase_add_test(tc_core, test_is_greater_ok7);
  tcase_add_test(tc_core, test_is_greater_ok8);
  tcase_add_test(tc_core, test_is_greater_ok9);
  tcase_add_test(tc_core, test_is_greater_ok10);
  tcase_add_test(tc_core, test_is_greater_ok11);
  tcase_add_test(tc_core, test_is_greater_ok12);
  tcase_add_test(tc_core, test_is_greater_ok13);
  tcase_add_test(tc_core, test_is_greater_ok14);
  tcase_add_test(tc_core, test_is_greater_ok15);
  tcase_add_test(tc_core, test_is_greater_ok16);
  tcase_add_test(tc_core, test_is_greater_ok17);
  tcase_add_test(tc_core, test_is_greater_ok18);
  tcase_add_test(tc_core, test_is_greater_ok19);
  tcase_add_test(tc_core, test_is_greater_ok20);
  tcase_add_test(tc_core, test_is_greater_ok21);
  tcase_add_test(tc_core, test_is_greater_ok22);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_is_greater(s21_decimal value_a, s21_decimal value_b,
                           int check) {
  int err = s21_is_greater(value_a, value_b);
  ck_assert_int_eq(err, check);
}