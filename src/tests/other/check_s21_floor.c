#include "../check_s21_decimal.h"

START_TEST(test_floor_fail_invalid_value) {
  s21_decimal value = {{0, 0, 0, 1000000000}};
  s21_decimal res;

  int err = s21_floor(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_floor_fail_invalid_scale) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal res;

  int err = s21_floor(value, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_floor_fail_null_ptr) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};

  int err = s21_floor(value, NULL);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_floor_ok1) {
  // -228.99457042623138959107055924
  s21_decimal value = {{0x24506134, 0xB7AFB101, 0x49FDFCA5, 0x801A0000}};
  // -229
  s21_decimal decimal_check = {{0xE5, 0x0, 0x0, 0x80000000}};

  s21_assert_floor(value, decimal_check);
}

START_TEST(test_floor_ok2) {
  // -16066.739544792969751303352033
  s21_decimal value = {{0xF670EEE1, 0xF60EEAD0, 0x33EA186F, 0x80180000}};
  // -16067
  s21_decimal decimal_check = {{0x3EC3, 0x0, 0x0, 0x80000000}};

  s21_assert_floor(value, decimal_check);
}

START_TEST(test_floor_ok3) {
  // -660457428.36542893573839092119
  s21_decimal value = {{0x3ED57997, 0x5706227F, 0xD567C20D, 0x80140000}};
  // -660457429
  s21_decimal decimal_check = {{0x275DC7D5, 0x0, 0x0, 0x80000000}};

  s21_assert_floor(value, decimal_check);
}

START_TEST(test_floor_ok4) {
  // 7120.7520400793708529155804637
  s21_decimal value = {{0xFFC78DDD, 0xCAD5895E, 0xE6157AF7, 0x190000}};
  // 7120
  s21_decimal decimal_check = {{0x1BD0, 0x0, 0x0, 0x0}};

  s21_assert_floor(value, decimal_check);
}

START_TEST(test_floor_ok5) {
  // 6.3088881678789399064616234879
  s21_decimal value = {{0x37F1EF7F, 0xCA8D68B1, 0xCBD9E658, 0x1C0000}};
  // 6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

  s21_assert_floor(value, decimal_check);
}

START_TEST(test_floor_ok6) {
  // 6716.2096685279774385346371547
  s21_decimal value = {{0x3466DFDB, 0xBE3B3C8D, 0xD9032F2C, 0x190000}};
  // 6716
  s21_decimal decimal_check = {{0x1A3C, 0x0, 0x0, 0x0}};

  s21_assert_floor(value, decimal_check);
}

Suite *s21_floor_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_floor_suite");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_floor_ok1);
  tcase_add_test(tc_core, test_floor_ok2);
  tcase_add_test(tc_core, test_floor_ok3);
  tcase_add_test(tc_core, test_floor_ok4);
  tcase_add_test(tc_core, test_floor_ok5);
  tcase_add_test(tc_core, test_floor_ok6);
  tcase_add_test(tc_core, test_floor_fail_invalid_value);
  tcase_add_test(tc_core, test_floor_fail_invalid_scale);
  tcase_add_test(tc_core, test_floor_fail_null_ptr);

  suite_add_tcase(s, tc_core);
  return s;
}

void s21_assert_floor(s21_decimal value, s21_decimal decimal_check) {
  s21_decimal res;

  int err = s21_floor(value, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}
