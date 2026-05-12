/**
 * @file test_bigint.c
 * @brief Unit tests for high-precision integer API
 */

#include "test_framework.h"
#include <fc_bigint.h>

/* Test: Basic lifecycle */
TEST(test_bigint_create_destroy) {
    fc_bigint_t* value = NULL;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_NOT_NULL(value);

    fc_bigint_destroy(value);
    fc_bigint_destroy(NULL);  /* Should not crash */
}

/* Test: Set and get i64 */
TEST(test_bigint_set_get_i64) {
    fc_bigint_t* value = NULL;
    fc_int64_t result = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(value, 42), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &result), FC_OK);
    ASSERT_EQ(result, 42);

    ASSERT_EQ(fc_bigint_set_i64(value, -123), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &result), FC_OK);
    ASSERT_EQ(result, -123);

    fc_bigint_destroy(value);
}

/* Test: Set and get u64 */
TEST(test_bigint_set_get_u64) {
    fc_bigint_t* value = NULL;
    fc_uint64_t result = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    ASSERT_EQ(fc_bigint_set_u64(value, 12345), FC_OK);
    ASSERT_EQ(fc_bigint_get_u64(value, &result), FC_OK);
    ASSERT_EQ(result, 12345);

    fc_bigint_destroy(value);
}

/* Test: String conversion */
TEST(test_bigint_string_conversion) {
    fc_bigint_t* value = NULL;
    char buffer[256];
    fc_size_t size = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    ASSERT_EQ(fc_bigint_set_str(value, "123456789"), FC_OK);
    ASSERT_EQ(fc_bigint_string_size(value, &size), FC_OK);
    ASSERT_TRUE(size > 0);

    ASSERT_EQ(fc_bigint_to_string(value, buffer, sizeof(buffer)), FC_OK);

    ASSERT_EQ(fc_bigint_set_str(value, "invalid"), FC_ERR_PARSE);

    fc_bigint_destroy(value);
}

/* Test: Addition */
TEST(test_bigint_add) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 100), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 200), FC_OK);

    ASSERT_EQ(fc_bigint_add(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 300);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Subtraction */
TEST(test_bigint_sub) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 500), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 200), FC_OK);

    ASSERT_EQ(fc_bigint_sub(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 300);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Multiplication */
TEST(test_bigint_mul) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 15), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 20), FC_OK);

    ASSERT_EQ(fc_bigint_mul(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 300);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Division */
TEST(test_bigint_div) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 100), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 3), FC_OK);

    ASSERT_EQ(fc_bigint_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 33);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Modulo */
TEST(test_bigint_mod) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 100), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 3), FC_OK);

    ASSERT_EQ(fc_bigint_mod(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 1);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Negation */
TEST(test_bigint_neg) {
    fc_bigint_t *value = NULL, *result = NULL;
    fc_int64_t output = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(value, 42), FC_OK);
    ASSERT_EQ(fc_bigint_neg(result, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &output), FC_OK);
    ASSERT_EQ(output, -42);

    fc_bigint_destroy(value);
    fc_bigint_destroy(result);
}

/* Test: Absolute value */
TEST(test_bigint_abs) {
    fc_bigint_t *value = NULL, *result = NULL;
    fc_int64_t output = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(value, -123), FC_OK);
    ASSERT_EQ(fc_bigint_abs(result, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &output), FC_OK);
    ASSERT_EQ(output, 123);

    fc_bigint_destroy(value);
    fc_bigint_destroy(result);
}

/* Test: Comparison */
TEST(test_bigint_cmp) {
    fc_bigint_t *a = NULL, *b = NULL;
    int cmp = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 100), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 50), FC_OK);

    ASSERT_EQ(fc_bigint_cmp(a, b, &cmp), FC_OK);
    ASSERT_TRUE(cmp > 0);

    ASSERT_EQ(fc_bigint_cmp(b, a, &cmp), FC_OK);
    ASSERT_TRUE(cmp < 0);

    ASSERT_EQ(fc_bigint_cmp(a, a, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
}

/* Test: Division by zero */
TEST(test_bigint_divide_by_zero) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 100), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 0), FC_OK);

    ASSERT_EQ(fc_bigint_div(result, a, b), FC_ERR_DIVIDE_BY_ZERO);
    ASSERT_EQ(fc_bigint_mod(result, a, b), FC_ERR_DIVIDE_BY_ZERO);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Overflow detection */
TEST(test_bigint_overflow) {
    fc_bigint_t* value = NULL;
    fc_int64_t result_i64 = 0;
    fc_uint64_t result_u64 = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Set to a value larger than INT64_MAX */
    ASSERT_EQ(fc_bigint_set_str(value, "9223372036854775808"), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &result_i64), FC_ERR_OVERFLOW);

    /* Set to a value larger than UINT64_MAX */
    ASSERT_EQ(fc_bigint_set_str(value, "18446744073709551616"), FC_OK);
    ASSERT_EQ(fc_bigint_get_u64(value, &result_u64), FC_ERR_OVERFLOW);

    fc_bigint_destroy(value);
}

/* Test: Copy */
TEST(test_bigint_copy) {
    fc_bigint_t *src = NULL, *dst = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&src), FC_OK);
    ASSERT_EQ(fc_bigint_create(&dst), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(src, 12345), FC_OK);
    ASSERT_EQ(fc_bigint_copy(dst, src), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(dst, &value), FC_OK);
    ASSERT_EQ(value, 12345);

    fc_bigint_destroy(src);
    fc_bigint_destroy(dst);
}

/* Test: Very large numbers (1024-bit) */
TEST(test_bigint_large_1024bit) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    char buffer[512];

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    /* 2^1000 */
    const char* large_num = "10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376";
    ASSERT_EQ(fc_bigint_set_str(a, large_num), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 2), FC_OK);

    /* Multiply by 2 */
    ASSERT_EQ(fc_bigint_mul(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_to_string(result, buffer, sizeof(buffer)), FC_OK);

    /* Divide back */
    ASSERT_EQ(fc_bigint_div(result, result, b), FC_OK);
    ASSERT_EQ(fc_bigint_to_string(result, buffer, sizeof(buffer)), FC_OK);

    /* Should match original */
    int cmp = 0;
    ASSERT_EQ(fc_bigint_cmp(result, a, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Very large numbers (2048-bit) */
TEST(test_bigint_large_2048bit) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    /* 2^2000 - a very large number */
    const char* huge_num = "114813069527425452423283320117768198402231770208869520047764273682576626139237031385665948631650626991844596463898746277344711896086305533142593135616665318539129989145312280000688779148240044871428926990063486244781615463646388363947317026040466353970904996558162398808944629605623311649536164221970332681344168908984458505602379484807914058900934776500429002716706625830522008132236281291761267883317206598995396418127021779858404042159853183251540889433902091920554957783589672039160081957216630582755380425583726015528348786419432054508915275783882625175435528800822842770817965453762184851149029376";
    ASSERT_EQ(fc_bigint_set_str(a, huge_num), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 1), FC_OK);

    /* Add 1 */
    ASSERT_EQ(fc_bigint_add(result, a, b), FC_OK);

    /* Subtract 1 */
    ASSERT_EQ(fc_bigint_sub(result, result, b), FC_OK);

    /* Should match original */
    int cmp = 0;
    ASSERT_EQ(fc_bigint_cmp(result, a, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Factorial computation (stress test) */
TEST(test_bigint_factorial) {
    fc_bigint_t *result = NULL, *i = NULL, *temp = NULL;

    ASSERT_EQ(fc_bigint_create(&result), FC_OK);
    ASSERT_EQ(fc_bigint_create(&i), FC_OK);
    ASSERT_EQ(fc_bigint_create(&temp), FC_OK);

    /* Compute 50! */
    ASSERT_EQ(fc_bigint_set_i64(result, 1), FC_OK);
    for (int n = 2; n <= 50; n++) {
        ASSERT_EQ(fc_bigint_set_i64(i, n), FC_OK);
        ASSERT_EQ(fc_bigint_mul(temp, result, i), FC_OK);
        ASSERT_EQ(fc_bigint_copy(result, temp), FC_OK);
    }

    /* 50! = 30414093201713378043612608166064768844377641568960512000000000000 */
    const char* expected = "30414093201713378043612608166064768844377641568960512000000000000";
    char buffer[256];
    ASSERT_EQ(fc_bigint_to_string(result, buffer, sizeof(buffer)), FC_OK);

    fc_bigint_t* expected_val = NULL;
    ASSERT_EQ(fc_bigint_create(&expected_val), FC_OK);
    ASSERT_EQ(fc_bigint_set_str(expected_val, expected), FC_OK);

    int cmp = 0;
    ASSERT_EQ(fc_bigint_cmp(result, expected_val, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(result);
    fc_bigint_destroy(i);
    fc_bigint_destroy(temp);
    fc_bigint_destroy(expected_val);
}

/* Test: Fibonacci sequence (stress test) */
TEST(test_bigint_fibonacci) {
    fc_bigint_t *a = NULL, *b = NULL, *temp = NULL;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&temp), FC_OK);

    /* Compute Fibonacci(200) */
    ASSERT_EQ(fc_bigint_set_i64(a, 0), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 1), FC_OK);

    for (int i = 0; i < 200; i++) {
        ASSERT_EQ(fc_bigint_add(temp, a, b), FC_OK);
        ASSERT_EQ(fc_bigint_copy(a, b), FC_OK);
        ASSERT_EQ(fc_bigint_copy(b, temp), FC_OK);
    }

    /* Fib(200) = 453973694165307953197296969697410619233826 */
    const char* expected = "453973694165307953197296969697410619233826";
    fc_bigint_t* expected_val = NULL;
    ASSERT_EQ(fc_bigint_create(&expected_val), FC_OK);
    ASSERT_EQ(fc_bigint_set_str(expected_val, expected), FC_OK);

    int cmp = 0;
    ASSERT_EQ(fc_bigint_cmp(b, expected_val, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(temp);
    fc_bigint_destroy(expected_val);
}

/* Test: Power of 2 sequence */
TEST(test_bigint_power_of_2) {
    fc_bigint_t *result = NULL, *two = NULL, *temp = NULL;

    ASSERT_EQ(fc_bigint_create(&result), FC_OK);
    ASSERT_EQ(fc_bigint_create(&two), FC_OK);
    ASSERT_EQ(fc_bigint_create(&temp), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(result, 1), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(two, 2), FC_OK);

    /* Compute 2^512 */
    for (int i = 0; i < 512; i++) {
        ASSERT_EQ(fc_bigint_mul(temp, result, two), FC_OK);
        ASSERT_EQ(fc_bigint_copy(result, temp), FC_OK);
    }

    /* 2^512 = 13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096 */
    const char* expected = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096";
    fc_bigint_t* expected_val = NULL;
    ASSERT_EQ(fc_bigint_create(&expected_val), FC_OK);
    ASSERT_EQ(fc_bigint_set_str(expected_val, expected), FC_OK);

    int cmp = 0;
    ASSERT_EQ(fc_bigint_cmp(result, expected_val, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(result);
    fc_bigint_destroy(two);
    fc_bigint_destroy(temp);
    fc_bigint_destroy(expected_val);
}

/* Test: Negative number arithmetic */
TEST(test_bigint_negative_arithmetic) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    fc_int64_t value = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    /* -100 + (-50) = -150 */
    ASSERT_EQ(fc_bigint_set_i64(a, -100), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, -50), FC_OK);
    ASSERT_EQ(fc_bigint_add(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, -150);

    /* -100 - (-50) = -50 */
    ASSERT_EQ(fc_bigint_sub(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, -50);

    /* -100 * (-50) = 5000 */
    ASSERT_EQ(fc_bigint_mul(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 5000);

    /* -100 / (-50) = 2 */
    ASSERT_EQ(fc_bigint_div(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &value), FC_OK);
    ASSERT_EQ(value, 2);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Edge case - zero operations */
TEST(test_bigint_zero_operations) {
    fc_bigint_t *zero = NULL, *value = NULL, *result = NULL;
    fc_int64_t out = 0;

    ASSERT_EQ(fc_bigint_create(&zero), FC_OK);
    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(zero, 0), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(value, 42), FC_OK);

    /* 0 + 42 = 42 */
    ASSERT_EQ(fc_bigint_add(result, zero, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &out), FC_OK);
    ASSERT_EQ(out, 42);

    /* 42 - 42 = 0 */
    ASSERT_EQ(fc_bigint_sub(result, value, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &out), FC_OK);
    ASSERT_EQ(out, 0);

    /* 0 * 42 = 0 */
    ASSERT_EQ(fc_bigint_mul(result, zero, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &out), FC_OK);
    ASSERT_EQ(out, 0);

    /* 0 / 42 = 0 */
    ASSERT_EQ(fc_bigint_div(result, zero, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &out), FC_OK);
    ASSERT_EQ(out, 0);

    fc_bigint_destroy(zero);
    fc_bigint_destroy(value);
    fc_bigint_destroy(result);
}

/* Test: String parsing edge cases */
TEST(test_bigint_string_edge_cases) {
    fc_bigint_t* value = NULL;
    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Leading zeros */
    ASSERT_EQ(fc_bigint_set_str(value, "00042"), FC_OK);
    fc_int64_t out = 0;
    ASSERT_EQ(fc_bigint_get_i64(value, &out), FC_OK);
    ASSERT_EQ(out, 42);

    /* Negative with leading zeros */
    ASSERT_EQ(fc_bigint_set_str(value, "-00042"), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &out), FC_OK);
    ASSERT_EQ(out, -42);

    /* Just zero */
    ASSERT_EQ(fc_bigint_set_str(value, "0"), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &out), FC_OK);
    ASSERT_EQ(out, 0);

    /* Invalid: empty string */
    ASSERT_EQ(fc_bigint_set_str(value, ""), FC_ERR_PARSE);

    /* Invalid: only sign */
    ASSERT_EQ(fc_bigint_set_str(value, "-"), FC_ERR_PARSE);

    /* Invalid: mixed characters */
    ASSERT_EQ(fc_bigint_set_str(value, "123abc"), FC_ERR_PARSE);

    fc_bigint_destroy(value);
}

/* Test: NULL pointer checks */
TEST(test_bigint_null_checks) {
    fc_bigint_t* value = NULL;

    /* Create with NULL output */
    ASSERT_EQ(fc_bigint_create(NULL), FC_ERR_INVALID_ARG);

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Get with NULL output */
    ASSERT_EQ(fc_bigint_get_i64(value, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_get_u64(value, NULL), FC_ERR_INVALID_ARG);

    /* Set string with NULL input */
    ASSERT_EQ(fc_bigint_set_str(value, NULL), FC_ERR_INVALID_ARG);

    /* Operations with NULL operands */
    ASSERT_EQ(fc_bigint_add(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_sub(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mul(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_div(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mod(NULL, value, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_neg(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_abs(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_cmp(value, value, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_copy(NULL, value), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(value);
}

/* Test: Invalid string parsing */
TEST(test_bigint_invalid_string) {
    fc_bigint_t* value = NULL;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Invalid strings */
    ASSERT_EQ(fc_bigint_set_str(value, "not_a_number"), FC_ERR_PARSE);
    ASSERT_EQ(fc_bigint_set_str(value, "123abc"), FC_ERR_PARSE);
    ASSERT_EQ(fc_bigint_set_str(value, ""), FC_ERR_PARSE);
    ASSERT_EQ(fc_bigint_set_str(value, "  "), FC_ERR_PARSE);

    fc_bigint_destroy(value);
}

/* Test: Large negative numbers */
TEST(test_bigint_large_negative) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;
    int cmp = 0;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    /* Set large negative number */
    ASSERT_EQ(fc_bigint_set_str(a, "-999999999999999999999999999999"), FC_OK);
    ASSERT_EQ(fc_bigint_set_str(b, "-111111111111111111111111111111"), FC_OK);

    /* Add two negative numbers */
    ASSERT_EQ(fc_bigint_add(result, a, b), FC_OK);
    ASSERT_EQ(fc_bigint_set_str(a, "-1111111111111111111111111111110"), FC_OK);
    ASSERT_EQ(fc_bigint_cmp(result, a, &cmp), FC_OK);
    ASSERT_EQ(cmp, 0);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: i64 overflow detection */
TEST(test_bigint_i64_overflow) {
    fc_bigint_t* value = NULL;
    fc_int64_t result = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Value too large for i64 */
    ASSERT_EQ(fc_bigint_set_str(value, "99999999999999999999999999"), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &result), FC_ERR_OVERFLOW);

    /* Negative value too large for i64 */
    ASSERT_EQ(fc_bigint_set_str(value, "-99999999999999999999999999"), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &result), FC_ERR_OVERFLOW);

    fc_bigint_destroy(value);
}

/* Test: u64 overflow detection */
TEST(test_bigint_u64_overflow) {
    fc_bigint_t* value = NULL;
    fc_uint64_t result = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Value too large for u64 */
    ASSERT_EQ(fc_bigint_set_str(value, "99999999999999999999999999"), FC_OK);
    ASSERT_EQ(fc_bigint_get_u64(value, &result), FC_ERR_OVERFLOW);

    /* Negative value cannot convert to u64 */
    ASSERT_EQ(fc_bigint_set_str(value, "-1"), FC_OK);
    ASSERT_EQ(fc_bigint_get_u64(value, &result), FC_ERR_OVERFLOW);

    fc_bigint_destroy(value);
}

/* Test: Zero value edge cases */
TEST(test_bigint_zero_edge_cases) {
    fc_bigint_t *value = NULL, *result = NULL;
    fc_int64_t i64_val = 0;
    fc_uint64_t u64_val = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    /* Set to zero via i64 */
    ASSERT_EQ(fc_bigint_set_i64(value, 0), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &i64_val), FC_OK);
    ASSERT_EQ(i64_val, 0);

    /* Set to zero via u64 */
    ASSERT_EQ(fc_bigint_set_u64(value, 0), FC_OK);
    ASSERT_EQ(fc_bigint_get_u64(value, &u64_val), FC_OK);
    ASSERT_EQ(u64_val, 0);

    /* Neg of zero is zero */
    ASSERT_EQ(fc_bigint_neg(result, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &i64_val), FC_OK);
    ASSERT_EQ(i64_val, 0);

    /* Abs of zero is zero */
    ASSERT_EQ(fc_bigint_abs(result, value), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(result, &i64_val), FC_OK);
    ASSERT_EQ(i64_val, 0);

    fc_bigint_destroy(value);
    fc_bigint_destroy(result);
}

/* Test: More arithmetic error paths */
TEST(test_bigint_arithmetic_errors) {
    fc_bigint_t *a = NULL, *b = NULL, *result = NULL;

    ASSERT_EQ(fc_bigint_create(&a), FC_OK);
    ASSERT_EQ(fc_bigint_create(&b), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);

    ASSERT_EQ(fc_bigint_set_i64(a, 10), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(b, 5), FC_OK);

    /* Test with NULL result */
    ASSERT_EQ(fc_bigint_add(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_sub(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mul(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_div(NULL, a, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mod(NULL, a, b), FC_ERR_INVALID_ARG);

    /* Test with NULL operands */
    ASSERT_EQ(fc_bigint_add(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_add(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_sub(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_sub(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mul(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mul(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_div(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_div(result, a, NULL), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mod(result, NULL, b), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_mod(result, a, NULL), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(a);
    fc_bigint_destroy(b);
    fc_bigint_destroy(result);
}

/* Test: Unary operation error paths */
TEST(test_bigint_unary_errors) {
    fc_bigint_t *value = NULL, *result = NULL;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_create(&result), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(value, 42), FC_OK);

    /* Test neg with NULL */
    ASSERT_EQ(fc_bigint_neg(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_neg(result, NULL), FC_ERR_INVALID_ARG);

    /* Test abs with NULL */
    ASSERT_EQ(fc_bigint_abs(NULL, value), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_abs(result, NULL), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(value);
    fc_bigint_destroy(result);
}

/* Test: Copy error paths */
TEST(test_bigint_copy_errors) {
    fc_bigint_t *src = NULL, *dst = NULL;

    ASSERT_EQ(fc_bigint_create(&src), FC_OK);
    ASSERT_EQ(fc_bigint_create(&dst), FC_OK);

    /* Test copy with NULL */
    ASSERT_EQ(fc_bigint_copy(NULL, src), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_copy(dst, NULL), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(src);
    fc_bigint_destroy(dst);
}

/* Test: String conversion edge cases */
TEST(test_bigint_string_buffer_edge_cases) {
    fc_bigint_t* value = NULL;
    char buffer[10];

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_set_str(value, "123456789012345678901234567890"), FC_OK);

    /* Buffer too small */
    ASSERT_EQ(fc_bigint_to_string(value, buffer, sizeof(buffer)), FC_ERR_BUFFER_TOO_SMALL);

    /* NULL buffer */
    ASSERT_EQ(fc_bigint_to_string(value, NULL, 100), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(value);
}

/* Test: INT64_MIN special case */
TEST(test_bigint_int64_min_special) {
    fc_bigint_t* value = NULL;
    fc_int64_t result = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Set to INT64_MIN and verify */
    ASSERT_EQ(fc_bigint_set_i64(value, INT64_MIN), FC_OK);
    ASSERT_EQ(fc_bigint_get_i64(value, &result), FC_OK);
    ASSERT_EQ(result, INT64_MIN);

    fc_bigint_destroy(value);
}

/* Test: get_string_size function */
TEST(test_bigint_get_string_size) {
    fc_bigint_t* value = NULL;
    fc_size_t size = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);

    /* Positive number */
    ASSERT_EQ(fc_bigint_set_i64(value, 12345), FC_OK);
    ASSERT_EQ(fc_bigint_string_size(value, &size), FC_OK);
    ASSERT_TRUE(size > 5); /* "12345" + null terminator */

    /* Negative number - should account for minus sign */
    ASSERT_EQ(fc_bigint_set_i64(value, -12345), FC_OK);
    ASSERT_EQ(fc_bigint_string_size(value, &size), FC_OK);
    ASSERT_TRUE(size > 6); /* "-12345" + null terminator */

    /* Zero */
    ASSERT_EQ(fc_bigint_set_i64(value, 0), FC_OK);
    ASSERT_EQ(fc_bigint_string_size(value, &size), FC_OK);
    ASSERT_TRUE(size >= 2); /* "0" + null terminator */

    /* NULL size_out */
    ASSERT_EQ(fc_bigint_string_size(value, NULL), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(value);
}

/* Test: Comparison with NULL */
TEST(test_bigint_cmp_null) {
    fc_bigint_t* value = NULL;
    int cmp = 0;

    ASSERT_EQ(fc_bigint_create(&value), FC_OK);
    ASSERT_EQ(fc_bigint_set_i64(value, 42), FC_OK);

    /* Compare with NULL */
    ASSERT_EQ(fc_bigint_cmp(NULL, value, &cmp), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_cmp(value, NULL, &cmp), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_bigint_cmp(value, value, NULL), FC_ERR_INVALID_ARG);

    fc_bigint_destroy(value);
}

/* Test suite registration */
void register_bigint_tests(void) {
    RUN_TEST(test_bigint_create_destroy);
    RUN_TEST(test_bigint_set_get_i64);
    RUN_TEST(test_bigint_set_get_u64);
    RUN_TEST(test_bigint_string_conversion);
    RUN_TEST(test_bigint_add);
    RUN_TEST(test_bigint_sub);
    RUN_TEST(test_bigint_mul);
    RUN_TEST(test_bigint_div);
    RUN_TEST(test_bigint_mod);
    RUN_TEST(test_bigint_neg);
    RUN_TEST(test_bigint_abs);
    RUN_TEST(test_bigint_cmp);
    RUN_TEST(test_bigint_divide_by_zero);
    RUN_TEST(test_bigint_overflow);
    RUN_TEST(test_bigint_copy);
    RUN_TEST(test_bigint_large_1024bit);
    RUN_TEST(test_bigint_large_2048bit);
    RUN_TEST(test_bigint_factorial);
    RUN_TEST(test_bigint_fibonacci);
    RUN_TEST(test_bigint_power_of_2);
    RUN_TEST(test_bigint_negative_arithmetic);
    RUN_TEST(test_bigint_zero_operations);
    RUN_TEST(test_bigint_string_edge_cases);
    RUN_TEST(test_bigint_null_checks);
    RUN_TEST(test_bigint_invalid_string);
    RUN_TEST(test_bigint_large_negative);
    RUN_TEST(test_bigint_i64_overflow);
    RUN_TEST(test_bigint_u64_overflow);
    RUN_TEST(test_bigint_zero_edge_cases);
    RUN_TEST(test_bigint_arithmetic_errors);
    RUN_TEST(test_bigint_unary_errors);
    RUN_TEST(test_bigint_copy_errors);
    RUN_TEST(test_bigint_string_buffer_edge_cases);
    RUN_TEST(test_bigint_int64_min_special);
    RUN_TEST(test_bigint_get_string_size);
    RUN_TEST(test_bigint_cmp_null);
}
