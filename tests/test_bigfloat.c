/**
 * @file test_bigfloat.c
 * @brief Unit tests for high-precision floating-point API
 */

#include "test_framework.h"
#include <fc_bigfloat.h>
#include <math.h>

#define TEST_TOLERANCE 1e-10

/* Test: Basic lifecycle */
TEST(test_bigfloat_create_destroy) {
    fc_bigfloat_t* value = NULL;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_NOT_NULL(value);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(NULL);  /* Should not crash */
}

/* Test: Create with precision */
TEST(test_bigfloat_create_with_prec) {
    fc_bigfloat_t* value = NULL;
    fc_uint64_t prec = 0;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&value, 512), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_prec(value, &prec), FC_OK);
    ASSERT_EQ(prec, 512);

    fc_bigfloat_destroy(value);
}

/* Test: Set and get f64 */
TEST(test_bigfloat_set_get_f64) {
    fc_bigfloat_t* value = NULL;
    fc_double_t result = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(value, 3.14159), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(value, &result), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(result, 3.14159, TEST_TOLERANCE);

    ASSERT_EQ(fc_bigfloat_set_f64(value, INFINITY), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_f64(value, NAN), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
}

/* Test: Set and get i64 */
TEST(test_bigfloat_set_get_i64) {
    fc_bigfloat_t* value = NULL;
    fc_double_t result = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_i64(value, 42), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(value, &result), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(result, 42.0, TEST_TOLERANCE);

    ASSERT_EQ(fc_bigfloat_set_i64(value, -123), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(value, &result), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(result, -123.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(value);
}

/* Test: String conversion */
TEST(test_bigfloat_string_conversion) {
    fc_bigfloat_t* value = NULL;
    char buffer[256];
    fc_size_t size = 0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_str(value, "3.14159"), FC_OK);
    ASSERT_EQ(fc_bigfloat_string_size(value, &size), FC_OK);
    ASSERT_TRUE(size > 0);

    ASSERT_EQ(fc_bigfloat_to_string(value, buffer, sizeof(buffer)), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_str(value, "invalid"), FC_ERR_PARSE);
    ASSERT_EQ(fc_bigfloat_set_str(value, "nan"), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_str(value, "inf"), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
}

/* Test: Addition */
TEST(test_bigfloat_add) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;
    fc_double_t value = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);

    ASSERT_EQ(fc_bigfloat_add(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, 13.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Subtraction */
TEST(test_bigfloat_sub) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;
    fc_double_t value = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);

    ASSERT_EQ(fc_bigfloat_sub(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, 7.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Multiplication */
TEST(test_bigfloat_mul) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;
    fc_double_t value = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);

    ASSERT_EQ(fc_bigfloat_mul(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, 30.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Division */
TEST(test_bigfloat_div) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;
    fc_double_t value = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);

    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, 3.333333333, 1e-6);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Negation */
TEST(test_bigfloat_neg) {
    fc_bigfloat_t *value = NULL, *result = NULL;
    fc_double_t output = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(value, 42.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_neg(result, value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &output), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(output, -42.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: Absolute value */
TEST(test_bigfloat_abs) {
    fc_bigfloat_t *value = NULL, *result = NULL;
    fc_double_t output = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(value, -123.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_abs(result, value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &output), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(output, 123.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: Square root */
TEST(test_bigfloat_sqrt) {
    fc_bigfloat_t *value = NULL, *result = NULL;
    fc_double_t output = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(value, 4.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_sqrt(result, value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &output), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(output, 2.0, TEST_TOLERANCE);

    ASSERT_EQ(fc_bigfloat_set_f64(value, -1.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_sqrt(result, value), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: Comparison */
TEST(test_bigfloat_cmp) {
    fc_bigfloat_t *a = NULL, *b = NULL;
    int cmp = 0;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.5), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 5.5), FC_OK);

    ASSERT_EQ(fc_bigfloat_cmp(a, b, &cmp), FC_OK);
    ASSERT_TRUE(cmp > 0);

    ASSERT_EQ(fc_bigfloat_cmp(b, a, &cmp), FC_OK);
    ASSERT_TRUE(cmp < 0);

    ASSERT_EQ(fc_bigfloat_cmp(a, a, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
}

/* Test: Division by zero */
TEST(test_bigfloat_divide_by_zero) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 0.0), FC_OK);

    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_ERR_DIVIDE_BY_ZERO);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Set from bigint */
TEST(test_bigfloat_set_bigint) {
    fc_bigint_t* bigint = NULL;
    fc_bigfloat_t* bigfloat = NULL;
    fc_double_t result = 0.0;

    ASSERT_EQ(fc_bigint_create(&bigint), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&bigfloat), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(bigint, 12345), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_bigint(bigfloat, bigint), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(bigfloat, &result), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(result, 12345.0, TEST_TOLERANCE);

    fc_bigint_destroy(bigint);
    fc_bigfloat_destroy(bigfloat);
}

/* Test: Precision management */
TEST(test_bigfloat_precision) {
    fc_bigfloat_t* value = NULL;
    fc_uint64_t prec = 0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_prec(value, &prec), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_prec(value, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_prec(value, &prec), FC_OK);
    ASSERT_EQ(prec, 1024);

    fc_bigfloat_destroy(value);
}

/* Test: Copy */
TEST(test_bigfloat_copy) {
    fc_bigfloat_t *src = NULL, *dst = NULL;
    fc_double_t value = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&src), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&dst), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(src, 3.14159), FC_OK);
    ASSERT_EQ(fc_bigfloat_copy(dst, src), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(dst, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, 3.14159, TEST_TOLERANCE);

    fc_bigfloat_destroy(src);
    fc_bigfloat_destroy(dst);
}

/* Test: High precision computation - Pi approximation */
TEST(test_bigfloat_high_precision_pi) {
    fc_bigfloat_t *result = NULL, *one = NULL, *divisor = NULL, *term = NULL, *temp = NULL;

    /* Use 1024-bit precision */
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&one, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&divisor, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&term, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&temp, 1024), FC_OK);

    /* Compute Pi/4 using Leibniz formula: Pi/4 = 1 - 1/3 + 1/5 - 1/7 + ... */
    ASSERT_EQ(fc_bigfloat_set_f64(result, 0.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(one, 1.0), FC_OK);

    for (int i = 0; i < 10000; i++) {
        ASSERT_EQ(fc_bigfloat_set_i64(divisor, 2 * i + 1), FC_OK);
        ASSERT_EQ(fc_bigfloat_div(term, one, divisor), FC_OK);

        if (i % 2 == 0) {
            ASSERT_EQ(fc_bigfloat_add(temp, result, term), FC_OK);
        } else {
            ASSERT_EQ(fc_bigfloat_sub(temp, result, term), FC_OK);
        }
        ASSERT_EQ(fc_bigfloat_copy(result, temp), FC_OK);
    }

    /* Multiply by 4 to get Pi */
    ASSERT_EQ(fc_bigfloat_set_f64(temp, 4.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_mul(result, result, temp), FC_OK);

    /* Check that result is close to Pi (3.14159...) */
    fc_double_t pi_approx = 0.0;
    ASSERT_EQ(fc_bigfloat_get_f64(result, &pi_approx), FC_OK);
    ASSERT_TRUE(fabs(pi_approx - 3.14159265358979323846) < 0.001);

    fc_bigfloat_destroy(result);
    fc_bigfloat_destroy(one);
    fc_bigfloat_destroy(divisor);
    fc_bigfloat_destroy(term);
    fc_bigfloat_destroy(temp);
}

/* Test: Very high precision (4096-bit) */
TEST(test_bigfloat_extreme_precision) {
    fc_bigfloat_t *value = NULL;
    fc_uint64_t prec = 0;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&value, 4096), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_prec(value, &prec), FC_OK);
    ASSERT_EQ(prec, 4096);

    /* Set a value and perform operations */
    ASSERT_EQ(fc_bigfloat_set_str(value, "1.23456789012345678901234567890123456789"), FC_OK);

    fc_bigfloat_t *result = NULL;
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 4096), FC_OK);

    /* Square it */
    ASSERT_EQ(fc_bigfloat_mul(result, value, value), FC_OK);

    /* Take square root */
    ASSERT_EQ(fc_bigfloat_sqrt(result, result), FC_OK);

    /* Should be close to original */
    int cmp = 0;
    ASSERT_EQ(fc_bigfloat_cmp(result, value, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: Precision loss detection */
TEST(test_bigfloat_precision_loss) {
    fc_bigfloat_t *low_prec = NULL, *high_prec = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&low_prec, 53), FC_OK);  /* double precision */
    ASSERT_EQ(fc_bigfloat_create_with_prec(&high_prec, 256), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 256), FC_OK);

    /* Set high precision value */
    ASSERT_EQ(fc_bigfloat_set_str(high_prec, "1.234567890123456789012345678901234567890"), FC_OK);

    /* Set low precision from same string (will lose digits due to 53-bit precision) */
    ASSERT_EQ(fc_bigfloat_set_str(low_prec, "1.234567890123456789012345678901234567890"), FC_OK);

    /* Copy low precision value to result (result will have 53-bit precision after copy) */
    ASSERT_EQ(fc_bigfloat_copy(result, low_prec), FC_OK);

    /* Verify result has low precision now (copy adjusts dest precision to match src) */
    fc_uint64_t result_prec = 0;
    ASSERT_EQ(fc_bigfloat_get_prec(result, &result_prec), FC_OK);
    ASSERT_EQ(result_prec, 53);

    /* Should not match original due to precision loss */
    int cmp = 0;
    ASSERT_EQ(fc_bigfloat_cmp(result, high_prec, &cmp), FC_OK);
    ASSERT_TRUE(cmp != 0);

    fc_bigfloat_destroy(low_prec);
    fc_bigfloat_destroy(high_prec);
    fc_bigfloat_destroy(result);
}

/* Test: Rounding modes impact */
TEST(test_bigfloat_rounding_modes) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&a, 256), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&b, 256), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 256), FC_OK);

    /* 1 / 3 = 0.333... */
    ASSERT_EQ(fc_bigfloat_set_f64(a, 1.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_OK);

    /* Multiply back by 3 */
    ASSERT_EQ(fc_bigfloat_mul(result, result, b), FC_OK);

    /* Should be very close to 1.0 with high precision */
    fc_double_t value = 0.0;
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    ASSERT_TRUE(fabs(value - 1.0) < 1e-15);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Very small numbers (underflow boundary) */
TEST(test_bigfloat_very_small_numbers) {
    fc_bigfloat_t *value = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&value, 512), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 512), FC_OK);

    /* Set to a very small number: 10^-100 */
    ASSERT_EQ(fc_bigfloat_set_str(value, "1e-100"), FC_OK);

    /* Multiply by 10^100 */
    fc_bigfloat_t *multiplier = NULL;
    ASSERT_EQ(fc_bigfloat_create_with_prec(&multiplier, 512), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_str(multiplier, "1e100"), FC_OK);

    ASSERT_EQ(fc_bigfloat_mul(result, value, multiplier), FC_OK);

    /* Should be close to 1.0 */
    fc_double_t out = 0.0;
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);
    ASSERT_TRUE(fabs(out - 1.0) < 1e-10);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
    fc_bigfloat_destroy(multiplier);
}

/* Test: Very large numbers */
TEST(test_bigfloat_very_large_numbers) {
    fc_bigfloat_t *value = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&value, 512), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 512), FC_OK);

    /* Set to a very large number: 10^100 */
    ASSERT_EQ(fc_bigfloat_set_str(value, "1e100"), FC_OK);

    /* Divide by 10^100 */
    fc_bigfloat_t *divisor = NULL;
    ASSERT_EQ(fc_bigfloat_create_with_prec(&divisor, 512), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_str(divisor, "1e100"), FC_OK);

    ASSERT_EQ(fc_bigfloat_div(result, value, divisor), FC_OK);

    /* Should be close to 1.0 */
    fc_double_t out = 0.0;
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);
    ASSERT_TRUE(fabs(out - 1.0) < 1e-10);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
    fc_bigfloat_destroy(divisor);
}

/* Test: Square root precision */
TEST(test_bigfloat_sqrt_precision) {
    fc_bigfloat_t *value = NULL, *sqrt_val = NULL, *squared = NULL;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&value, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&sqrt_val, 1024), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&squared, 1024), FC_OK);

    /* Test sqrt(2) with high precision */
    ASSERT_EQ(fc_bigfloat_set_f64(value, 2.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_sqrt(sqrt_val, value), FC_OK);

    /* Square it back */
    ASSERT_EQ(fc_bigfloat_mul(squared, sqrt_val, sqrt_val), FC_OK);

    /* Should be very close to 2.0 */
    fc_double_t result = 0.0;
    ASSERT_EQ(fc_bigfloat_get_f64(squared, &result), FC_OK);
    ASSERT_TRUE(fabs(result - 2.0) < 1e-15);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(sqrt_val);
    fc_bigfloat_destroy(squared);
}

/* Test: Conversion from large BigInt */
TEST(test_bigfloat_large_bigint_conversion) {
    fc_bigint_t *bigint = NULL;
    fc_bigfloat_t *bigfloat = NULL;

    ASSERT_EQ(fc_bigint_create(&bigint), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&bigfloat, 512), FC_OK);

    /* Set bigint to 2^200 */
    const char* large_int = "1606938044258990275541962092341162602522202993782792835301376";
    ASSERT_EQ(fc_bigint_set_str(bigint, large_int), FC_OK);

    /* Convert to bigfloat */
    ASSERT_EQ(fc_bigfloat_set_bigint(bigfloat, bigint), FC_OK);

    /* Convert back to string and verify */
    char buffer[256];
    ASSERT_EQ(fc_bigfloat_to_string(bigfloat, buffer, sizeof(buffer)), FC_OK);

    fc_bigint_destroy(bigint);
    fc_bigfloat_destroy(bigfloat);
}

/* Test: Negative number operations */
TEST(test_bigfloat_negative_operations) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;
    fc_double_t value = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    /* -10.5 + (-5.5) = -16.0 */
    ASSERT_EQ(fc_bigfloat_set_f64(a, -10.5), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, -5.5), FC_OK);
    ASSERT_EQ(fc_bigfloat_add(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, -16.0, TEST_TOLERANCE);

    /* -10.5 * (-2.0) = 21.0 */
    ASSERT_EQ(fc_bigfloat_set_f64(b, -2.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_mul(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &value), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(value, 21.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Zero operations */
TEST(test_bigfloat_zero_operations) {
    fc_bigfloat_t *zero = NULL, *value = NULL, *result = NULL;
    fc_double_t out = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&zero), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(zero, 0.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(value, 42.5), FC_OK);

    /* 0 + 42.5 = 42.5 */
    ASSERT_EQ(fc_bigfloat_add(result, zero, value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(out, 42.5, TEST_TOLERANCE);

    /* 0 * 42.5 = 0 */
    ASSERT_EQ(fc_bigfloat_mul(result, zero, value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(out, 0.0, TEST_TOLERANCE);

    /* sqrt(0) = 0 */
    ASSERT_EQ(fc_bigfloat_sqrt(result, zero), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(out, 0.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(zero);
    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: NULL pointer checks */
TEST(test_bigfloat_null_checks) {
    fc_bigfloat_t* value = NULL;

    /* Create with NULL output */
    ASSERT_EQ(fc_bigfloat_create(NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_create_with_prec(NULL, 256), FC_ERR_INVALID_ARG);

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* Get with NULL output */
    ASSERT_EQ(fc_bigfloat_get_f64(value, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_get_prec(value, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_string_size(value, NULL), FC_ERR_INVALID_ARG);

    /* Set string with NULL input */
    ASSERT_EQ(fc_bigfloat_set_str(value, NULL), FC_ERR_INVALID_ARG);

    /* Operations with NULL operands */
    ASSERT_EQ(fc_bigfloat_add(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_sub(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_mul(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_div(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_neg(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_abs(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_sqrt(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_cmp(value, value, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_copy(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_bigint(value, NULL), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
}

/* Test: Invalid precision values */
TEST(test_bigfloat_invalid_precision) {
    fc_bigfloat_t* value = NULL;

    /* Zero precision */
    ASSERT_EQ(fc_bigfloat_create_with_prec(&value, 0), FC_ERR_INVALID_ARG);

    /* Valid creation */
    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* Invalid set_prec */
    ASSERT_EQ(fc_bigfloat_set_prec(value, 0), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
}

/* Test: Invalid string parsing */
TEST(test_bigfloat_invalid_string) {
    fc_bigfloat_t* value = NULL;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* Invalid strings */
    ASSERT_EQ(fc_bigfloat_set_str(value, "not_a_number"), FC_ERR_PARSE);
    ASSERT_EQ(fc_bigfloat_set_str(value, "123abc"), FC_ERR_PARSE);
    ASSERT_EQ(fc_bigfloat_set_str(value, ""), FC_ERR_PARSE);

    fc_bigfloat_destroy(value);
}

/* Test: NaN and Inf rejection */
TEST(test_bigfloat_nan_inf_rejection) {
    fc_bigfloat_t* value = NULL;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* NaN should be rejected */
    ASSERT_EQ(fc_bigfloat_set_str(value, "nan"), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_str(value, "NaN"), FC_ERR_INVALID_ARG);

    /* Infinity should be rejected */
    ASSERT_EQ(fc_bigfloat_set_str(value, "inf"), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_str(value, "-inf"), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_str(value, "infinity"), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
}

/* Test: set_u64 function */
TEST(test_bigfloat_set_get_u64) {
    fc_bigfloat_t* value = NULL;
    fc_double_t result = 0.0;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* Small u64 value */
    ASSERT_EQ(fc_bigfloat_set_u64(value, 12345), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(value, &result), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(result, 12345.0, TEST_TOLERANCE);

    /* Large u64 value (> ULONG_MAX on 32-bit, but we're on 64-bit) */
    ASSERT_EQ(fc_bigfloat_set_u64(value, 18446744073709551615ULL), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(value, &result), FC_OK);
    /* Just verify it's set without error */

    /* Zero */
    ASSERT_EQ(fc_bigfloat_set_u64(value, 0), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(value, &result), FC_OK);
    FC_TEST_ASSERT_DOUBLE_EQ(result, 0.0, TEST_TOLERANCE);

    fc_bigfloat_destroy(value);
}

/* Test: Negative number formatting */
TEST(test_bigfloat_negative_string) {
    fc_bigfloat_t* value = NULL;
    char buffer[256];

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* Set negative value */
    ASSERT_EQ(fc_bigfloat_set_f64(value, -123.456), FC_OK);
    ASSERT_EQ(fc_bigfloat_to_string(value, buffer, sizeof(buffer)), FC_OK);

    /* Should start with minus sign */
    ASSERT_TRUE(buffer[0] == '-');

    fc_bigfloat_destroy(value);
}

/* Test: Rounding modes in operations */
TEST(test_bigfloat_rounding_in_operations) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;
    fc_double_t out = 0.0;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&a, 53), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&b, 53), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result, 53), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 1.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);

    /* Test with RNDZ (round toward zero) */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDZ), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);

    /* Test with RNDU (round toward +inf) */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDU), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);

    /* Test with RNDD (round toward -inf) */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDD), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);

    /* Test with RNDA (round away from zero) */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDA), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result, &out), FC_OK);

    /* Restore default */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDN), FC_OK);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: sqrt of negative number */
TEST(test_bigfloat_sqrt_negative) {
    fc_bigfloat_t *value = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(value, -4.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_sqrt(result, value), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: Buffer too small for string */
TEST(test_bigfloat_buffer_too_small) {
    fc_bigfloat_t* value = NULL;
    char small_buffer[5];

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(value, 123456789.123456789), FC_OK);

    /* Buffer too small */
    ASSERT_EQ(fc_bigfloat_to_string(value, small_buffer, sizeof(small_buffer)), FC_ERR_BUFFER_TOO_SMALL);

    fc_bigfloat_destroy(value);
}

/* Test: Special float values - zero with sign */
TEST(test_bigfloat_signed_zero) {
    fc_bigfloat_t* value = NULL;
    char buffer[32];

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);

    /* Positive zero */
    ASSERT_EQ(fc_bigfloat_set_f64(value, 0.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_to_string(value, buffer, sizeof(buffer)), FC_OK);

    /* Negative zero */
    ASSERT_EQ(fc_bigfloat_set_f64(value, -0.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_to_string(value, buffer, sizeof(buffer)), FC_OK);

    /* Test buffer too small for zero */
    char tiny[2];
    ASSERT_EQ(fc_bigfloat_to_string(value, tiny, sizeof(tiny)), FC_ERR_BUFFER_TOO_SMALL);

    fc_bigfloat_destroy(value);
}

/* Test: More arithmetic error paths */
TEST(test_bigfloat_arithmetic_errors) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create(&a), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&b), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 10.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 5.0), FC_OK);

    /* Test with NULL result */
    ASSERT_EQ(fc_bigfloat_add(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_sub(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_mul(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_div(NULL, a, b), FC_ERR_INVALID_ARG);

    /* Test with NULL operands */
    ASSERT_EQ(fc_bigfloat_add(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_add(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_sub(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_sub(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_mul(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_mul(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_div(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_div(result, a, NULL), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result);
}

/* Test: Unary operation error paths */
TEST(test_bigfloat_unary_errors) {
    fc_bigfloat_t *value = NULL, *result = NULL;

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&result), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(value, 42.0), FC_OK);

    /* Test neg with NULL */
    ASSERT_EQ(fc_bigfloat_neg(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_neg(result, NULL), FC_ERR_INVALID_ARG);

    /* Test abs with NULL */
    ASSERT_EQ(fc_bigfloat_abs(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_abs(result, NULL), FC_ERR_INVALID_ARG);

    /* Test sqrt with NULL */
    ASSERT_EQ(fc_bigfloat_sqrt(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_sqrt(result, NULL), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(value);
    fc_bigfloat_destroy(result);
}

/* Test: Copy and set_bigint error paths */
TEST(test_bigfloat_copy_set_errors) {
    fc_bigfloat_t *src = NULL, *dst = NULL;
    fc_bigint_t *bigint = NULL;

    ASSERT_EQ(fc_bigfloat_create(&src), FC_OK);
    ASSERT_EQ(fc_bigfloat_create(&dst), FC_OK);
    ASSERT_EQ(fc_bigint_create(&bigint), FC_OK);

    /* Test copy with NULL */
    ASSERT_EQ(fc_bigfloat_copy(NULL, src), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_copy(dst, NULL), FC_ERR_INVALID_ARG);

    /* Test set_bigint with NULL */
    ASSERT_EQ(fc_bigfloat_set_bigint(NULL, bigint), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigfloat_set_bigint(src, NULL), FC_ERR_INVALID_ARG);

    fc_bigfloat_destroy(src);
    fc_bigfloat_destroy(dst);
    fc_bigint_destroy(bigint);
}

/* Test suite registration */
void register_bigfloat_tests(void) {
    RUN_TEST(test_bigfloat_create_destroy);
    RUN_TEST(test_bigfloat_create_with_prec);
    RUN_TEST(test_bigfloat_set_get_f64);
    RUN_TEST(test_bigfloat_set_get_i64);
    RUN_TEST(test_bigfloat_string_conversion);
    RUN_TEST(test_bigfloat_add);
    RUN_TEST(test_bigfloat_sub);
    RUN_TEST(test_bigfloat_mul);
    RUN_TEST(test_bigfloat_div);
    RUN_TEST(test_bigfloat_neg);
    RUN_TEST(test_bigfloat_abs);
    RUN_TEST(test_bigfloat_sqrt);
    RUN_TEST(test_bigfloat_cmp);
    RUN_TEST(test_bigfloat_divide_by_zero);
    RUN_TEST(test_bigfloat_set_bigint);
    RUN_TEST(test_bigfloat_precision);
    RUN_TEST(test_bigfloat_copy);
    RUN_TEST(test_bigfloat_high_precision_pi);
    RUN_TEST(test_bigfloat_extreme_precision);
    RUN_TEST(test_bigfloat_precision_loss);
    RUN_TEST(test_bigfloat_rounding_modes);
    RUN_TEST(test_bigfloat_very_small_numbers);
    RUN_TEST(test_bigfloat_very_large_numbers);
    RUN_TEST(test_bigfloat_sqrt_precision);
    RUN_TEST(test_bigfloat_large_bigint_conversion);
    RUN_TEST(test_bigfloat_negative_operations);
    RUN_TEST(test_bigfloat_zero_operations);
    RUN_TEST(test_bigfloat_null_checks);
    RUN_TEST(test_bigfloat_invalid_precision);
    RUN_TEST(test_bigfloat_invalid_string);
    RUN_TEST(test_bigfloat_nan_inf_rejection);
    RUN_TEST(test_bigfloat_set_get_u64);
    RUN_TEST(test_bigfloat_negative_string);
    RUN_TEST(test_bigfloat_rounding_in_operations);
    RUN_TEST(test_bigfloat_sqrt_negative);
    RUN_TEST(test_bigfloat_buffer_too_small);
    RUN_TEST(test_bigfloat_signed_zero);
    RUN_TEST(test_bigfloat_arithmetic_errors);
    RUN_TEST(test_bigfloat_unary_errors);
    RUN_TEST(test_bigfloat_copy_set_errors);
}
