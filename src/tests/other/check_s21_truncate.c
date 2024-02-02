#include "../check_s21_decimal.h"

START_TEST(test_truncate_fail_invalid_value) {
  s21_decimal value = {{0, 0, 0, 1000000000}};
  s21_decimal res;

  int err = s21_truncate(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_truncate_fail_invalid_scale) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal res;

  int err = s21_truncate(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_truncate_fail_null_ptr) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};

  int err = s21_truncate(value, NULL);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_truncate_ok1) {
  // 792281625142643375935439503.35
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  s21_assert_truncate(value, decimal_check);
}

START_TEST(test_truncate_ok2) {
  // -79228162514264337593543950.335
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

  s21_assert_truncate(value, decimal_check);
}

START_TEST(test_truncate_ok3) {
  // 122978293.79609722880
  s21_decimal value = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
  // 122978293
  s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

  s21_assert_truncate(value, decimal_check);
}

START_TEST(test_truncate_ok4) {
  // -122978293.79609722880
  s21_decimal value = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
  // -122978293
  s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x80000000}};

  s21_assert_truncate(value, decimal_check);
}

START_TEST(test_truncate_ok5) {
  // 1.2297829379609722880
  s21_decimal value = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  s21_assert_truncate(value, decimal_check);
}

START_TEST(test_truncate_ok6) {
  // -286331.1530
  s21_decimal value = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
  // -286331
  s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x80000000}};

  s21_assert_truncate(value, decimal_check);
}

Suite *s21_truncate_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_truncate_suite");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_truncate_ok1);
  tcase_add_test(tc_core, test_truncate_ok2);
  tcase_add_test(tc_core, test_truncate_ok3);
  tcase_add_test(tc_core, test_truncate_ok4);
  tcase_add_test(tc_core, test_truncate_ok5);
  tcase_add_test(tc_core, test_truncate_ok6);
  tcase_add_test(tc_core, test_truncate_fail_invalid_value);
  tcase_add_test(tc_core, test_truncate_fail_invalid_scale);
  tcase_add_test(tc_core, test_truncate_fail_null_ptr);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_truncate(s21_decimal value, s21_decimal decimal_check) {
  s21_decimal res;

  int err = s21_truncate(value, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}
