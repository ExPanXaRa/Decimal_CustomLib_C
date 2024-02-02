#include "../check_s21_decimal.h"

START_TEST(test_negate_fail_invalid_value) {
  s21_decimal value = {{0, 0, 0, 1000000000}};
  s21_decimal res;

  int err = s21_negate(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_negate_fail_invalid_scale) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal res;

  int err = s21_negate(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_negate_fail_null_ptr) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};

  int err = s21_negate(value, NULL);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_negate_ok1) {
  // 156064767562212695305426944
  s21_decimal value = {{0x811800, 0x811800, 0x811800, 0x0}};
  // -156064767562212695305426944
  s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80000000}};

  s21_assert_negate(value, decimal_check);
}

START_TEST(test_negate_ok2) {
  // -1.5
  s21_decimal value = {{0xF, 0x0, 0x0, 0x80010000}};
  // 1.5
  s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x10000}};

  s21_assert_negate(value, decimal_check);
}

START_TEST(test_negate_ok3) {
  // 1.49
  s21_decimal value = {{0x95, 0x0, 0x0, 0x20000}};
  // -1.49
  s21_decimal decimal_check = {{0x95, 0x0, 0x0, 0x80020000}};

  s21_assert_negate(value, decimal_check);
}

START_TEST(test_negate_ok4) {
  // 1.9999999999999999999999999999
  s21_decimal value = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal_check = {
      {0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};

  s21_assert_negate(value, decimal_check);
}

START_TEST(test_negate_ok5) {
  // -2.596597038203724290724477478
  s21_decimal value = {{0x64B83A26, 0x7E973CF9, 0x863DACF, 0x801B0000}};
  // 2.596597038203724290724477478
  s21_decimal decimal_check = {{0x64B83A26, 0x7E973CF9, 0x863DACF, 0x1B0000}};

  s21_assert_negate(value, decimal_check);
}

START_TEST(test_negate_ok6) {
  // -7391817384113353885252676556.8
  s21_decimal value = {{0xD4363600, 0x3C647D46, 0xEED7AE29, 0x80010000}};
  // 7391817384113353885252676556.8
  s21_decimal decimal_check = {{0xD4363600, 0x3C647D46, 0xEED7AE29, 0x10000}};

  s21_assert_negate(value, decimal_check);
}

Suite *s21_negate_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_negate_suite");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_negate_ok1);
  tcase_add_test(tc_core, test_negate_ok2);
  tcase_add_test(tc_core, test_negate_ok3);
  tcase_add_test(tc_core, test_negate_ok4);
  tcase_add_test(tc_core, test_negate_ok5);
  tcase_add_test(tc_core, test_negate_ok6);
  tcase_add_test(tc_core, test_negate_fail_invalid_value);
  tcase_add_test(tc_core, test_negate_fail_invalid_scale);
  tcase_add_test(tc_core, test_negate_fail_null_ptr);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_negate(s21_decimal value, s21_decimal decimal_check) {
  s21_decimal res;

  int err = s21_negate(value, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}
