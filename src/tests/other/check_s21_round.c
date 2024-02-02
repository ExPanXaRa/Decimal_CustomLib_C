#include "../check_s21_decimal.h"

START_TEST(test_round_fail_invalid_value) {
  s21_decimal value = {{0, 0, 0, 1000000000}};
  s21_decimal res;

  int err = s21_round(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_round_fail_invalid_scale) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal res;

  int err = s21_round(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_round_fail_null_ptr) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};

  int err = s21_round(value, NULL);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_round_ok1) {
  // 7922816251426433759354395033.5
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  s21_assert_round(value, decimal_check);
}

START_TEST(test_round_ok2) {
  // -792281625142643375935439.50335
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
  // -792281625142643375935440
  s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x80000000}};

  s21_assert_round(value, decimal_check);
}

START_TEST(test_round_ok3) {
  // -429496.7297
  s21_decimal value = {{0x1, 0x1, 0x0, 0x80040000}};
  // -429497
  s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x80000000}};

  s21_assert_round(value, decimal_check);
}

START_TEST(test_round_ok4) {
  // 3961408126635554083362675097.6
  s21_decimal value = {{0x0, 0x80000000, 0x80000000, 0x10000}};
  // 3961408126635554083362675098
  s21_decimal decimal_check = {{0x9999999A, 0xD9999999, 0xCCCCCCC, 0x0}};

  s21_assert_round(value, decimal_check);
}

START_TEST(test_round_ok5) {
  // -3.9614081266355540833626750976
  s21_decimal value = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
  // -4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

  s21_assert_round(value, decimal_check);
}

START_TEST(test_round_ok6) {
  // 3961408125713216879891945881.6
  s21_decimal value = {{0x80000000, 0x0, 0x80000000, 0x10000}};
  // 3961408125713216879891945882
  s21_decimal decimal_check = {{0xD999999A, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

  s21_assert_round(value, decimal_check);
}

Suite *s21_round_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_round_suite");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_round_ok1);
  tcase_add_test(tc_core, test_round_ok2);
  tcase_add_test(tc_core, test_round_ok3);
  tcase_add_test(tc_core, test_round_ok4);
  tcase_add_test(tc_core, test_round_ok5);
  tcase_add_test(tc_core, test_round_ok6);
  tcase_add_test(tc_core, test_round_fail_invalid_value);
  tcase_add_test(tc_core, test_round_fail_invalid_scale);
  tcase_add_test(tc_core, test_round_fail_null_ptr);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_round(s21_decimal value, s21_decimal decimal_check) {
  s21_decimal result;

  int err = s21_round(value, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
