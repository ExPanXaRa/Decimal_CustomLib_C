#include "../check_s21_decimal.h"

START_TEST(test_is_less_or_equal_ok1) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x50000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok2) {
  // 1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x50000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok3) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // -1.23000
  s21_decimal value_b = {{0x1E078, 0x0, 0x0, 0x80050000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok4) {
  // -1.23000
  s21_decimal value_a = {{0x1E078, 0x0, 0x0, 0x80050000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok5) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok6) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok7) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // -1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x80000000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok8) {
  // -1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok9) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655765.00000
  s21_decimal value_b = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok10) {
  // 1431655765.00000
  s21_decimal value_a = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok11) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // -1431655765.00000
  s21_decimal value_b = {{0x5554D320, 0x8235, 0x0, 0x80050000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok12) {
  // -1431655765.00000
  s21_decimal value_a = {{0x5554D320, 0x8235, 0x0, 0x80050000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok13) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655765.000000000000000001
  s21_decimal value_b = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x120000}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok14) {
  // 1431655765.000000000000000001
  s21_decimal value_a = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x120000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok15) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // -1431655765.000000000000000001
  s21_decimal value_b = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x80120000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok16) {
  // -1431655765.000000000000000001
  s21_decimal value_a = {{0xC8340001, 0x8881186E, 0x4A03CE6, 0x80120000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok17) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 1431655764.999999999999999999
  s21_decimal value_b = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok18) {
  // 1431655764.999999999999999999
  s21_decimal value_a = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok19) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // -1431655764.999999999999999999
  s21_decimal value_b = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x80120000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok20) {
  // -1431655764.999999999999999999
  s21_decimal value_a = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x80120000}};
  // 1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

START_TEST(test_is_less_or_equal_ok21) {
  // 1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal value_b = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  int check = 0;

  s21_assert_is_less_or_equal(value_a, value_b, check);
}

Suite *s21_is_less_or_equal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_is_less_or_equal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_less_or_equal_ok1);
  tcase_add_test(tc_core, test_is_less_or_equal_ok2);
  tcase_add_test(tc_core, test_is_less_or_equal_ok3);
  tcase_add_test(tc_core, test_is_less_or_equal_ok4);
  tcase_add_test(tc_core, test_is_less_or_equal_ok5);
  tcase_add_test(tc_core, test_is_less_or_equal_ok6);
  tcase_add_test(tc_core, test_is_less_or_equal_ok7);
  tcase_add_test(tc_core, test_is_less_or_equal_ok8);
  tcase_add_test(tc_core, test_is_less_or_equal_ok9);
  tcase_add_test(tc_core, test_is_less_or_equal_ok10);
  tcase_add_test(tc_core, test_is_less_or_equal_ok11);
  tcase_add_test(tc_core, test_is_less_or_equal_ok12);
  tcase_add_test(tc_core, test_is_less_or_equal_ok13);
  tcase_add_test(tc_core, test_is_less_or_equal_ok14);
  tcase_add_test(tc_core, test_is_less_or_equal_ok15);
  tcase_add_test(tc_core, test_is_less_or_equal_ok16);
  tcase_add_test(tc_core, test_is_less_or_equal_ok17);
  tcase_add_test(tc_core, test_is_less_or_equal_ok18);
  tcase_add_test(tc_core, test_is_less_or_equal_ok19);
  tcase_add_test(tc_core, test_is_less_or_equal_ok20);
  tcase_add_test(tc_core, test_is_less_or_equal_ok21);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_is_less_or_equal(s21_decimal value_a, s21_decimal value_b,
                                 int check) {
  int err = s21_is_less_or_equal(value_a, value_b);
  ck_assert_int_eq(err, check);
}
