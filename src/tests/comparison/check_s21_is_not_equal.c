#include "../check_s21_decimal.h"

START_TEST(test_is_not_equal_ok1) {
  // 5281877500950955839569596689
  s21_decimal value_a = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 5281877500950955839569596689
  s21_decimal value_b = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  int check = 0;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok2) {
  // 5281877500950955839569596689
  s21_decimal value_a = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 5281877500950955839569596689
  s21_decimal value_b = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  int check = 0;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok3) {
  // -5281877500950955839569596689
  s21_decimal value_a = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  // -5281877500950955839569596689.0
  s21_decimal value_b = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  int check = 0;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok4) {
  // -5281877500950955839569596689.0
  s21_decimal value_a = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // -5281877500950955839569596689
  s21_decimal value_b = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  int check = 0;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok5) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689.0
  s21_decimal value_b = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok6) {
  // 5281877500950955839569596689.0
  s21_decimal value_a = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok7) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689.0
  s21_decimal value_b = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok8) {
  // -5281877500950955839569596689.0
  s21_decimal value_a = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok9) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal value_b = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok10) {
  // 7922816251426433759354395033
  s21_decimal value_a = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok11) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal value_b = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok12) {
  // -7922816251426433759354395033
  s21_decimal value_a = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok13) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal value_b = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok14) {
  // 7922816251426433759354395034
  s21_decimal value_a = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok15) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal value_b = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok16) {
  // -7922816251426433759354395034
  s21_decimal value_a = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok17) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034409
  s21_decimal value_b = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok18) {
  // 7922816251426433759354395034
  s21_decimal value_a = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395034
  s21_decimal value_b = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  int check = 0;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok19) {
  // 7922816251426433759354395034
  s21_decimal value_a = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395034
  s21_decimal value_b = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  int check = 0;

  s21_assert_is_not_equal(value_a, value_b, check);
}

START_TEST(test_is_not_equal_ok20) {
  // 7922816251426433759354395034
  s21_decimal value_a = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395034
  s21_decimal value_b = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  int check = 1;

  s21_assert_is_not_equal(value_a, value_b, check);
}

Suite *s21_is_not_equal_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_is_not_equal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_not_equal_ok1);
  tcase_add_test(tc_core, test_is_not_equal_ok2);
  tcase_add_test(tc_core, test_is_not_equal_ok3);
  tcase_add_test(tc_core, test_is_not_equal_ok4);
  tcase_add_test(tc_core, test_is_not_equal_ok5);
  tcase_add_test(tc_core, test_is_not_equal_ok6);
  tcase_add_test(tc_core, test_is_not_equal_ok7);
  tcase_add_test(tc_core, test_is_not_equal_ok8);
  tcase_add_test(tc_core, test_is_not_equal_ok9);
  tcase_add_test(tc_core, test_is_not_equal_ok10);
  tcase_add_test(tc_core, test_is_not_equal_ok11);
  tcase_add_test(tc_core, test_is_not_equal_ok12);
  tcase_add_test(tc_core, test_is_not_equal_ok13);
  tcase_add_test(tc_core, test_is_not_equal_ok14);
  tcase_add_test(tc_core, test_is_not_equal_ok15);
  tcase_add_test(tc_core, test_is_not_equal_ok16);
  tcase_add_test(tc_core, test_is_not_equal_ok17);
  tcase_add_test(tc_core, test_is_not_equal_ok18);
  tcase_add_test(tc_core, test_is_not_equal_ok19);
  tcase_add_test(tc_core, test_is_not_equal_ok20);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_is_not_equal(s21_decimal value_a, s21_decimal value_b,
                             int check) {
  int err = s21_is_not_equal(value_a, value_b);
  ck_assert_int_eq(err, check);
}