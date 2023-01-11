#include "s21_smart_calc_test.h"

START_TEST(s21_test_0) {
  double x = 0;
  double orig = 10;
  double result = 0;
  char str[255] = "5 + 5";

  s21_smart_calc(str, x, &result);
  ck_assert_double_eq(result, orig);
}
END_TEST

START_TEST(s21_test_1) {
  double x = 0;
  double orig = 162;
  double result = 0;
  char str[255] = "   4 * 5 * 2 ^ 2 * 2 + 2";

  s21_smart_calc(str, x, &result);
  ck_assert_double_eq(result, orig);
}
END_TEST

START_TEST(s21_test_2) {
  double x = 0;
  double orig = 150 / 10 + 5 * 2 / 2;
  double result = 0;
  char str[255] = "  150 / 10 + 5 * 2 / 2";

  s21_smart_calc(str, x, &result);
  ck_assert_double_eq(result, orig);
}
END_TEST

START_TEST(s21_test_3) {
  double x = 5;
  double orig = 5 + 5 - 2 * 3 / 6;
  double result = 0;
  char str[255] = "  5 + x - 2 * 3 / 6";

  s21_smart_calc(str, x, &result);
  ck_assert_double_eq(result, orig);
}
END_TEST

START_TEST(s21_test_4) {
  double x = 0;
  double orig = 2 + (5 * 5 * 5 + 5 + 2 * 2) / (2);
  double result = 0;
  char str[255] = "2+(5 * 5 * 5 + 5 + 2 * 2) / (2)";

  s21_smart_calc(str, x, &result);
  ck_assert_double_eq(result, orig);
}
END_TEST

START_TEST(s21_test_5) {
  double x = 0;
  double orig = 5 + (3 + sin(2 - 3.5)) * 2;
  double result = 0;
  char str[255] = "5 + (3 + sin(2 - 3.5)) *2";

  s21_smart_calc(str, x, &result);
  ck_assert_double_eq_tol(result, orig, 1e-7);
}
END_TEST

START_TEST(s21_test_6) {
  double x = 0.0;
  char *str = "24*4 -3 * 2";
  double orig = 90;
  double result = 0;

  s21_smart_calc(str, x, &result);
  ck_assert_int_eq(result, orig);
}
END_TEST

START_TEST(s21_test_7) {
  double orig = 4;
  char *str = "2 - (-2)";
  double x = 0.0;
  double result = 0;

  s21_smart_calc(str, x, &result);
  ck_assert_int_eq(result, orig);
}
END_TEST

START_TEST(s21_test_8) {
  double orig = 5.388742979;
  char *str = "-sin(9) + ln(256)";
  double x = 0.0;
  double result = 0;
  s21_smart_calc(str, x, &result);

  ck_assert_int_eq(result, orig);
}
END_TEST

START_TEST(s21_test_9) {
  double orig = sin(PI / 2) - (-2);
  char *str = "sin(pi/2)-(-2)";
  double x = 0.0;
  double result = 0;

  s21_smart_calc(str, x, &result);
  ck_assert_int_eq(result, orig);
}
END_TEST

START_TEST(s21_test_10) {
  double orig = 0.91113026188;
  char *str = "-cos(9)";
  double x = 0.0;
  double result = 0;

  s21_smart_calc(str, x, &result);
  ck_assert_int_eq(result, orig);
}
END_TEST

START_TEST(s21_test_11) {
  char *str = "-cos(9";
  double x = 0.0;
  double result = 0;

  int error = s21_smart_calc(str, x, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_test_12) {
  char *str = "8..";
  double x = 0.0;
  double result = 0;

  int error = s21_smart_calc(str, x, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_test_13) {
  char *str = "5/(1+2-3)";
  double x = 0.0;
  double result = 0;

  int error = s21_smart_calc(str, x, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_test_14) {
  char *str = "((()))";
  double x = 0.0;
  double result = 0;

  int error = s21_smart_calc(str, x, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_test_15) {
  char *str = "(((2-3^2*7)-7)mg)";
  double x = 0.0;
  double result = 0;

  int error = s21_smart_calc(str, x, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(plus_t) {
  double x = 0.0;
  double result = 0;

  s21_smart_calc("(-2)+2", x, &result);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(minus_t) {
  double x = 0.0;
  double result = 0;

  s21_smart_calc("(-2.2)-2.2", x, &result);
  ck_assert_float_eq(result, -4.4);
}
END_TEST

START_TEST(mult_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("(-2.2)*(+2.2)", x, &result);
  ck_assert_float_eq(result, -4.84);
}
END_TEST

START_TEST(division_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("(-2.2)/2.2", x, &result);
  ck_assert_float_eq(result, -1);
}
END_TEST

START_TEST(degr_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("(2.2)^(-2.2)", x, &result);
  ck_assert_double_eq_tol(result, 0.17647, 0.17647);
}
END_TEST

START_TEST(sin_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("sin(+2)", x, &result);
  ck_assert_double_eq(result, sin(2));
}
END_TEST

START_TEST(cos_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("cos(2)", x, &result);
  ck_assert_double_eq_tol(result, cos(2), 1e-7);
}
END_TEST

START_TEST(tan_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("tan(2)", x, &result);
  ck_assert_ldouble_eq(result, tan(2));
}
END_TEST

START_TEST(asin_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("asin(1)", x, &result);
  ck_assert_ldouble_eq(result, asin(1));
}
END_TEST

START_TEST(acos_t) {
  double x = 0.0;
  double result = s21_smart_calc("acos(1)", x, &result);
  ck_assert_ldouble_eq(result, acos(1));
}
END_TEST

START_TEST(atan_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("atan(1)", x, &result);
  ck_assert_ldouble_eq(result, atan(1));
}
END_TEST

START_TEST(ln_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("log(1)", x, &result);
  ck_assert_ldouble_eq(result, log(1));
}
END_TEST

START_TEST(log_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("log(1)", x, &result);
  ck_assert_ldouble_eq(result, log10(1));
}
END_TEST

START_TEST(sqrt_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("sqrt(1)", x, &result);
  ck_assert_ldouble_eq(result, sqrt(1));
}
END_TEST

START_TEST(mod_t) {
  double x = 0.0;
  double result = 0;
  s21_smart_calc("4mod8", x, &result);
  ck_assert_ldouble_eq(result, 4);
}
END_TEST
Suite *suite_smart_calc(void) {
  Suite *s = suite_create("suite_smart_calc");
  TCase *tc = tcase_create("suite_smart_calc");

  tcase_add_test(tc, s21_test_0);
  tcase_add_test(tc, s21_test_1);
  tcase_add_test(tc, s21_test_2);
  tcase_add_test(tc, s21_test_3);
  tcase_add_test(tc, s21_test_4);
  tcase_add_test(tc, s21_test_5);
  tcase_add_test(tc, s21_test_6);
  tcase_add_test(tc, s21_test_7);
  tcase_add_test(tc, s21_test_8);
  tcase_add_test(tc, s21_test_9);
  tcase_add_test(tc, s21_test_10);
  tcase_add_test(tc, s21_test_11);
  tcase_add_test(tc, s21_test_12);
  tcase_add_test(tc, s21_test_13);
  tcase_add_test(tc, s21_test_14);
  tcase_add_test(tc, s21_test_15);

  tcase_add_test(tc, plus_t);
  tcase_add_test(tc, minus_t);
  tcase_add_test(tc, division_t);
  tcase_add_test(tc, mult_t);
  tcase_add_test(tc, degr_t);
  tcase_add_test(tc, sin_t);
  tcase_add_test(tc, cos_t);
  tcase_add_test(tc, tan_t);
  tcase_add_test(tc, asin_t);
  tcase_add_test(tc, acos_t);
  tcase_add_test(tc, atan_t);
  tcase_add_test(tc, ln_t);
  tcase_add_test(tc, log_t);
  tcase_add_test(tc, sqrt_t);
  tcase_add_test(tc, mod_t);
  suite_add_tcase(s, tc);
  return s;
}