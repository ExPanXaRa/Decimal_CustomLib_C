#include "../check_s21_decimal.h"

START_TEST(test_from_decimal_to_int_fail_invalid_scale) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  int res;
  int err = s21_from_decimal_to_int(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_invalid_value) {
  s21_decimal value = {{-1, 0, 0, 0x1C0001}};
  int res;
  int err = s21_from_decimal_to_int(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_null_ptr) {
  s21_decimal value = {{-1, 0, 0, 0x1C0001}};

  int err = s21_from_decimal_to_int(value, NULL);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_ok1) {
  // 264093874.98605864508043122005
  s21_decimal value = {{0x55555555, 0x0, 0x55555555, 0x140000}};
  int check = 264093874;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok2) {
  // -264093874.98605864508043122005
  s21_decimal value = {{0x55555555, 0x0, 0x55555555, 0x80140000}};
  int check = -264093874;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok3) {
  // 2.6409387498605864508043122005
  s21_decimal value = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
  int check = 2;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok4) {
  // -2.6409387498605864508043122005
  s21_decimal value = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
  int check = -2;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok5) {
  // 264093874.98605864506611466240
  s21_decimal value = {{0x0, 0x0, 0x55555555, 0x140000}};
  int check = 264093874;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok6) {
  // -264093874.98605864506611466240
  s21_decimal value = {{0x0, 0x0, 0x55555555, 0x80140000}};
  int check = -264093874;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok7) {
  // 2.6409387498605864506611466240
  s21_decimal value = {{0x0, 0x0, 0x55555555, 0x1C0000}};
  int check = 2;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok8) {
  // -2.6409387498605864506611466240
  s21_decimal value = {{0x0, 0x0, 0x55555555, 0x801C0000}};
  int check = -2;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok9) {
  // 6148914.691236517205
  s21_decimal value = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
  int check = 6148914;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok10) {
  // -6148914.691236517205
  s21_decimal value = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
  int check = -6148914;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok11) {
  // 6.148914691236517205
  s21_decimal value = {{0x55555555, 0x55555555, 0x0, 0x120000}};
  int check = 6;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok12) {
  // -6.148914691236517205
  s21_decimal value = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
  int check = -6;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok13) {
  // 6148914.689804861440
  s21_decimal value = {{0x0, 0x55555555, 0x0, 0xC0000}};
  int check = 6148914;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok14) {
  // -6148914.689804861440
  s21_decimal value = {{0x0, 0x55555555, 0x0, 0x800C0000}};
  int check = -6148914;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok15) {
  // 6.148914689804861440
  s21_decimal value = {{0x0, 0x55555555, 0x0, 0x120000}};
  int check = 6;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok16) {
  // -6.148914689804861440
  s21_decimal value = {{0x0, 0x55555555, 0x0, 0x80120000}};
  int check = -6;

  s21_assert_from_decimal_to_int(value, check);
}

START_TEST(test_from_decimal_to_int_ok17) {
  // 1431655765
  s21_decimal value = {{0x55555555, 0x0, 0x0, 0x0}};
  int check = 1431655765;

  s21_assert_from_decimal_to_int(value, check);
}

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_decimal_to_int");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_decimal_to_int_ok1);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok2);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok3);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok4);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok5);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok6);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok7);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok8);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok9);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok10);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok11);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok12);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok13);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok14);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok15);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok16);
  tcase_add_test(tc_core, test_from_decimal_to_int_ok17);

  tcase_add_test(tc_core, test_from_decimal_to_int_fail_invalid_scale);
  tcase_add_test(tc_core, test_from_decimal_to_int_fail_invalid_value);
  tcase_add_test(tc_core, test_from_decimal_to_int_fail_null_ptr);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_from_decimal_to_int(s21_decimal value, int check) {
  int res;
  int err = s21_from_decimal_to_int(value, &res);

  ck_assert_int_eq(res, check);
  ck_assert_int_eq(err, 0);
}