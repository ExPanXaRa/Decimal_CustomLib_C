#include "../check_s21_decimal.h"

START_TEST(test_div_fail_invalid_value) {
  s21_decimal value_a = {{-1, 0, 0, 0x1C0001}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  int err = s21_div(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_div_fail_null_pointer) {
  s21_decimal value_a = {{-1, 0, 0, 0x1C0001}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int err = s21_div(value_a, value_b, NULL);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_div_fail_invalid_scale) {
  s21_decimal value_a = {{-1, 0, 0, 0x1D0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  int err = s21_div(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_div_fail_overflow_big) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal value_b = {{0x1, 0x0, 0x0, 0x1C0000}};

  s21_decimal res;

  int check = 1;

  int err = s21_div(value_a, value_b, &res);
  ck_assert_int_eq(err, check);
}

START_TEST(test_div_fail_overflow_small) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal value_b = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal res;

  int check = 2;

  int err = s21_div(value_a, value_b, &res);
  ck_assert_int_eq(err, check);
}
START_TEST(test_div_fail_division_by_zero) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal value_b = {{0x0, 0x0, 0x0, 0x0}};

  s21_decimal res;
  int check = 3;

  int err = s21_div(value_a, value_b, &res);
  ck_assert_int_eq(err, check);
}

START_TEST(test_div_ok1) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal value_b = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80000000}};

  s21_assert_div(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_div_ok2) {
  // 39614081257132168796771975168
  s21_decimal value_a = {{0x0, 0x0, 0x80000000, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal value_b = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -19807040628566084398385987585
  s21_decimal decimal_check = {{0x1, 0x0, 0x40000000, 0x80000000}};

  s21_assert_div(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_div_ok3) {
  // 4294967296
  s21_decimal value_a = {{0x0, 0x1, 0x0, 0x0}};
  // 3656273013.5441854660747245473
  s21_decimal value_b = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 1.1746845161971917984513124388
  s21_decimal decimal_check = {{0x27BBE824, 0x39191E73, 0x25F4C338, 0x1C0000}};

  s21_assert_div(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_div_ok4) {
  // -5
  s21_decimal value_a = {{0x5, 0x0, 0x0, 0x80000000}};
  // 39614081257132168796771975168
  s21_decimal value_b = {{0x0, 0x0, 0x80000000, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

  s21_assert_div(value_a, value_b, decimal_check);
}
END_TEST

START_TEST(test_div_ok5) {
  // -1429062841781896312709593009.2
  s21_decimal value_a = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 5
  s21_decimal value_b = {{0x5, 0x0, 0x0, 0x0}};
  // -285812568356379262541918601.84
  s21_decimal decimal_check = {
      {0xBE2C59D8, 0xADA12E5D, 0x5C59DC8D, 0x80020000}};

  s21_assert_div(value_a, value_b, decimal_check);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_div");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_div_ok1);
  tcase_add_test(tc_core, test_div_ok2);
  tcase_add_test(tc_core, test_div_ok3);
  tcase_add_test(tc_core, test_div_ok4);
  tcase_add_test(tc_core, test_div_ok5);

  tcase_add_test(tc_core, test_div_fail_invalid_value);
  tcase_add_test(tc_core, test_div_fail_null_pointer);
  tcase_add_test(tc_core, test_div_fail_invalid_scale);
  tcase_add_test(tc_core, test_div_fail_overflow_big);
  tcase_add_test(tc_core, test_div_fail_overflow_small);
  tcase_add_test(tc_core, test_div_fail_division_by_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_div(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check) {
  s21_decimal res;
  int err = s21_div(value_a, value_b, &res);

  ck_assert_int_eq(s21_is_equal(res, check), 1);
  ck_assert_int_eq(err, 0);
}
