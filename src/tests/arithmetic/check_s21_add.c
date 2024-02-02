#include "../check_s21_decimal.h"

START_TEST(test_add_fail_invalid_value) {
  s21_decimal value_a = {{-1, 0, 0, 0x11C0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;

  int err = s21_add(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_add_fail_null_pointer) {
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x80000000}};

  int err = s21_add(value_a, value_b, NULL);
  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_add_fail_invalid_scale) {
  s21_decimal value_a = {{0, 0, 0, 0x1D0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;

  int err = s21_add(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_add_fail_overflow_big) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;

  int check = 1;
  int err = s21_add(value_a, value_b, &res);

  ck_assert_int_eq(err, check);
}

START_TEST(test_add_fail_overflow_small) {
  // -79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;

  int check = 2;
  int err = s21_add(value_a, value_b, &res);

  ck_assert_int_eq(err, check);
}

START_TEST(test_add_ok1) {
  // 7922816251426433759354395033.5
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1431655765
  s21_decimal value_b = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 7922816251426433757922739268.5
  s21_decimal check = {{0xAAAAAAAD, 0xFFFFFFFC, 0xFFFFFFFF, 0x10000}};

  s21_assert_add(value_a, value_b, check);
}
END_TEST

START_TEST(test_add_ok2) {
  // -7922816251426433759354395035
  s21_decimal value_a = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal value_b = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  s21_assert_add(value_a, value_b, check);
}
END_TEST

START_TEST(test_add_ok3) {
  // 1.9999999999999999999999999000
  s21_decimal value_a = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -0
  s21_decimal value_b = {{0x0, 0x0, 0x0, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal check = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};

  s21_assert_add(value_a, value_b, check);
}
END_TEST

START_TEST(test_add_ok4) {
  // 8
  s21_decimal value_a = {{0x8, 0x0, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal value_b = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 6148914691236517213
  s21_decimal check = {{0x5555555D, 0x55555555, 0x0, 0x0}};

  s21_assert_add(value_a, value_b, check);
}
END_TEST

START_TEST(test_add_ok5) {
  // 649244002.20841517182548587502
  s21_decimal value_a = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // -56124981125209321576924.010631
  s21_decimal value_b = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // -56124981125208672332921.802216
  s21_decimal check = {{0x29358DE8, 0x553CC7C5, 0xB5597F0B, 0x80060000}};

  s21_assert_add(value_a, value_b, check);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_add");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add_ok1);
  tcase_add_test(tc_core, test_add_ok2);
  tcase_add_test(tc_core, test_add_ok3);
  tcase_add_test(tc_core, test_add_ok4);
  tcase_add_test(tc_core, test_add_ok5);
  tcase_add_test(tc_core, test_add_fail_invalid_value);
  tcase_add_test(tc_core, test_add_fail_null_pointer);
  tcase_add_test(tc_core, test_add_fail_invalid_scale);
  tcase_add_test(tc_core, test_add_fail_overflow_big);
  tcase_add_test(tc_core, test_add_fail_overflow_small);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_add(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check) {
  s21_decimal res;
  int err = s21_add(value_a, value_b, &res);

  ck_assert_int_eq(s21_is_equal(res, check), 1);
  ck_assert_int_eq(err, 0);
}
