#include "../check_s21_decimal.h"

START_TEST(test_mul_fail_invalid_value) {
  s21_decimal value_a = {{-1, 0, 0, 0x401C0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  int err = s21_mul(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_mul_fail_null_pointer) {
  s21_decimal value_a = {{-1, 0, 0, 0x401C0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int err = s21_mul(value_a, value_b, NULL);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_mul_fail_invalid_scale) {
  s21_decimal value_a = {{-1, 0, 0, 0x1D0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  int err = s21_mul(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_mul_fail_overflow_big) {
  // 7922816251426433759354395032.8
  s21_decimal value_a = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10.000000000000000000000000001
  s21_decimal value_b = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};

  s21_decimal res;
  int err = s21_mul(value_a, value_b, &res);
  int check = 1;

  ck_assert_int_eq(err, check);
}

START_TEST(test_mul_fail_overflow_small) {
  // 7922816251426433759354395032.8
  s21_decimal value_a = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10.000000000000000000000000001
  s21_decimal value_b = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};

  s21_decimal res;
  int err = s21_mul(value_a, value_b, &res);
  int check = 2;

  ck_assert_int_eq(err, check);
}

START_TEST(test_mul_ok1) {
  // 6148914689804861440
  s21_decimal value_a = {{0x0, 0x55555555, 0x0, 0x0}};
  // -1
  s21_decimal value_b = {{0x1, 0x0, 0x0, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

  s21_assert_mul(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_mul_ok2) {
  // -1431655765
  s21_decimal value_a = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal value_b = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000001431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x1C0000}};

  s21_assert_mul(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_mul_ok3) {
  // -0.5
  s21_decimal value_a = {{0x5, 0x0, 0x0, 0x80010000}};
  // 6148914689804861440
  s21_decimal value_b = {{0x0, 0x55555555, 0x0, 0x0}};
  // -3074457344902430720.0
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA9, 0x1, 0x80010000}};

  s21_assert_mul(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_mul_ok4) {
  // 7055.820576069728775806815669
  s21_decimal value_a = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // 7055.820576069728775806815669
  s21_decimal value_b = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // 49784604.001688959238158904099
  s21_decimal decimal_check = {{0x40136B23, 0xBF8285B9, 0xA0DCDBF6, 0x150000}};

  s21_assert_mul(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_mul_ok5) {
  // 26409387504754779197847983445
  s21_decimal value_a = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal value_b = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  s21_assert_mul(value_a, value_b, decimal_check);
}

Suite *s21_mul_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_mul");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_mul_ok1);
  tcase_add_test(tc_core, test_mul_ok2);
  tcase_add_test(tc_core, test_mul_ok3);
  tcase_add_test(tc_core, test_mul_ok4);
  tcase_add_test(tc_core, test_mul_ok5);

  tcase_add_test(tc_core, test_mul_fail_invalid_value);
  tcase_add_test(tc_core, test_mul_fail_null_pointer);
  tcase_add_test(tc_core, test_mul_fail_invalid_scale);
  tcase_add_test(tc_core, test_mul_fail_overflow_big);
  tcase_add_test(tc_core, test_mul_fail_overflow_small);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_mul(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check) {
  s21_decimal res;
  int err = s21_mul(value_a, value_b, &res);

  ck_assert_int_eq(s21_is_equal(res, check), 1);
  ck_assert_int_eq(err, 0);
}
