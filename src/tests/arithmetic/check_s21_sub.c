#include "../check_s21_decimal.h"

START_TEST(test_sub_fail_invalid_value) {
  s21_decimal value_a = {{-1, 0, 0, 0x1C0001}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  int err = s21_sub(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_sub_fail_null_pointer) {
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int err = s21_sub(value_a, value_b, NULL);

  ck_assert_int_ne(err, 0);
}

START_TEST(test_sub_fail_invalid_scale) {
  s21_decimal value_a = {{-1, 0, 0, 0x1D0000}};
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  int err = s21_sub(value_a, value_b, &res);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(test_sub_fail_overflow_big) {
  // 79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal value_b = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal res;
  int err = s21_sub(value_a, value_b, &res);
  int check = 1;

  ck_assert_int_eq(err, check);
}

START_TEST(test_sub_fail_overflow_small) {
  // -79228162514264337593543950335
  s21_decimal value_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal res;
  int check = 2;
  int err = s21_sub(value_a, value_b, &res);
  ck_assert_int_eq(err, check);
}

START_TEST(test_sub_ok1) {
  // 7922816251426433759354395034
  s21_decimal value_a = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 26409387498605864508043122005
  s21_decimal value_b = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -18486571247179430748688726971
  s21_decimal check = {{0xBBBBBBBB, 0x66666666, 0x3BBBBBBB, 0x80000000}};

  s21_assert_sub(value_a, value_b, check);
}
END_TEST

START_TEST(test_sub_ok2) {
  // -0.5000000000000000000000000001
  s21_decimal value_a = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal value_b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 7.4228162514264337593543950334
  s21_decimal check = {{0x77FFFFFE, 0xE0ED7ECF, 0xEFD818D0, 0x1C0000}};

  s21_assert_sub(value_a, value_b, check);
}
END_TEST

START_TEST(test_sub_ok3) {
  // -6148914689804861440
  s21_decimal value_a = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal value_b = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -6148914689804861440.5000000000
  s21_decimal check = {{0x2A05F200, 0x8EA6B401, 0xC6AEA154, 0x800A0000}};

  s21_assert_sub(value_a, value_b, check);
}
END_TEST

START_TEST(test_sub_ok4) {
  // 0
  s21_decimal value_a = {{0x0, 0x0, 0x0, 0x0}};
  // -26409387
  s21_decimal value_b = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 26409387
  s21_decimal check = {{0x192F9AB, 0x0, 0x0, 0x0}};

  s21_assert_sub(value_a, value_b, check);
}
END_TEST

START_TEST(test_sub_ok5) {
  // -60233732531769558296976156804
  s21_decimal value_a = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal value_b = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -60233732531769558296976156804
  s21_decimal check = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};

  s21_assert_sub(value_a, value_b, check);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sub");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sub_ok1);
  tcase_add_test(tc_core, test_sub_ok2);
  tcase_add_test(tc_core, test_sub_ok3);
  tcase_add_test(tc_core, test_sub_ok4);
  tcase_add_test(tc_core, test_sub_ok5);

  tcase_add_test(tc_core, test_sub_fail_invalid_value);
  tcase_add_test(tc_core, test_sub_fail_null_pointer);
  tcase_add_test(tc_core, test_sub_fail_invalid_scale);
  tcase_add_test(tc_core, test_sub_fail_overflow_big);
  tcase_add_test(tc_core, test_sub_fail_overflow_small);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_sub(s21_decimal value_a, s21_decimal value_b,
                    s21_decimal check) {
  s21_decimal res;
  int err = s21_sub(value_a, value_b, &res);
  ck_assert_int_eq(s21_is_equal(res, check), 1);
  ck_assert_int_eq(err, 0);
}
