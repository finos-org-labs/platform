/**
 * @file test_precision.c
 * @brief Unit tests for precision and rounding mode control
 */

#include "test_framework.h"
#include <fc_precision.h>
#include <fc_bigfloat.h>

/* Test: Default precision bits */
TEST(test_precision_default_bits) {
    fc_uint64_t bits = 0;

    ASSERT_EQ(fc_precision_get_default_bits(&bits), FC_OK);
    ASSERT_EQ(bits, 256);

    ASSERT_EQ(fc_precision_set_default_bits(512), FC_OK);
    ASSERT_EQ(fc_precision_get_default_bits(&bits), FC_OK);
    ASSERT_EQ(bits, 512);

    /* Restore default */
    ASSERT_EQ(fc_precision_set_default_bits(256), FC_OK);
}

/* Test: Invalid precision bits */
TEST(test_precision_invalid_bits) {
    ASSERT_EQ(fc_precision_set_default_bits(0), FC_ERR_INVALID_ARG);
}

/* Test: NULL pointer in get_default_bits */
TEST(test_precision_null_get_bits) {
    ASSERT_EQ(fc_precision_get_default_bits(NULL), FC_ERR_INVALID_ARG);
}

/* Test: NULL pointer in get_rounding_mode */
TEST(test_precision_null_get_rounding) {
    ASSERT_EQ(fc_precision_get_rounding_mode(NULL), FC_ERR_INVALID_ARG);
}

/* Test: Rounding mode */
TEST(test_precision_rounding_mode) {
    fc_rounding_mode_t mode = FC_RNDN;

    ASSERT_EQ(fc_precision_get_rounding_mode(&mode), FC_OK);
    ASSERT_EQ(mode, FC_RNDN);

    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDZ), FC_OK);
    ASSERT_EQ(fc_precision_get_rounding_mode(&mode), FC_OK);
    ASSERT_EQ(mode, FC_RNDZ);

    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDU), FC_OK);
    ASSERT_EQ(fc_precision_get_rounding_mode(&mode), FC_OK);
    ASSERT_EQ(mode, FC_RNDU);

    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDD), FC_OK);
    ASSERT_EQ(fc_precision_get_rounding_mode(&mode), FC_OK);
    ASSERT_EQ(mode, FC_RNDD);

    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDA), FC_OK);
    ASSERT_EQ(fc_precision_get_rounding_mode(&mode), FC_OK);
    ASSERT_EQ(mode, FC_RNDA);

    /* Restore default */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDN), FC_OK);
}

/* Test: Invalid rounding mode */
TEST(test_precision_invalid_rounding_mode) {
    /* Test invalid mode values (outside valid range) */
    ASSERT_EQ(fc_precision_set_rounding_mode((fc_rounding_mode_t)-1), FC_ERR_INVALID_ARG);
    ASSERT_EQ(fc_precision_set_rounding_mode((fc_rounding_mode_t)99), FC_ERR_INVALID_ARG);
}

/* Test: Precision affects bigfloat */
TEST(test_precision_affects_bigfloat) {
    fc_bigfloat_t* value = NULL;
    fc_uint64_t prec = 0;

    ASSERT_EQ(fc_precision_set_default_bits(384), FC_OK);

    ASSERT_EQ(fc_bigfloat_create(&value), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_prec(value, &prec), FC_OK);
    ASSERT_EQ(prec, 384);

    fc_bigfloat_destroy(value);

    /* Restore default */
    ASSERT_EQ(fc_precision_set_default_bits(256), FC_OK);
}

/* Test: Multiple precision changes */
TEST(test_precision_multiple_changes) {
    fc_uint64_t bits = 0;

    /* Change precision multiple times */
    ASSERT_EQ(fc_precision_set_default_bits(128), FC_OK);
    ASSERT_EQ(fc_precision_get_default_bits(&bits), FC_OK);
    ASSERT_EQ(bits, 128);

    ASSERT_EQ(fc_precision_set_default_bits(256), FC_OK);
    ASSERT_EQ(fc_precision_get_default_bits(&bits), FC_OK);
    ASSERT_EQ(bits, 256);

    ASSERT_EQ(fc_precision_set_default_bits(512), FC_OK);
    ASSERT_EQ(fc_precision_get_default_bits(&bits), FC_OK);
    ASSERT_EQ(bits, 512);

    ASSERT_EQ(fc_precision_set_default_bits(1024), FC_OK);
    ASSERT_EQ(fc_precision_get_default_bits(&bits), FC_OK);
    ASSERT_EQ(bits, 1024);

    /* Restore default */
    ASSERT_EQ(fc_precision_set_default_bits(256), FC_OK);
}

/* Test: Rounding mode affects operations */
TEST(test_precision_rounding_affects_operations) {
    fc_bigfloat_t *a = NULL, *b = NULL, *result1 = NULL, *result2 = NULL;
    fc_double_t out1 = 0.0, out2 = 0.0;

    ASSERT_EQ(fc_bigfloat_create_with_prec(&a, 53), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&b, 53), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result1, 53), FC_OK);
    ASSERT_EQ(fc_bigfloat_create_with_prec(&result2, 53), FC_OK);

    ASSERT_EQ(fc_bigfloat_set_f64(a, 1.0), FC_OK);
    ASSERT_EQ(fc_bigfloat_set_f64(b, 3.0), FC_OK);

    /* Compute 1/3 with RNDD (round down) */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDD), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result1, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result1, &out1), FC_OK);

    /* Compute 1/3 with RNDU (round up) */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDU), FC_OK);
    ASSERT_EQ(fc_bigfloat_div(result2, a, b), FC_OK);
    ASSERT_EQ(fc_bigfloat_get_f64(result2, &out2), FC_OK);

    /* Results should be different due to rounding */
    ASSERT_TRUE(out1 != out2);

    /* Restore default */
    ASSERT_EQ(fc_precision_set_rounding_mode(FC_RNDN), FC_OK);

    fc_bigfloat_destroy(a);
    fc_bigfloat_destroy(b);
    fc_bigfloat_destroy(result1);
    fc_bigfloat_destroy(result2);
}

/* Test suite registration */
void register_precision_tests(void) {
    RUN_TEST(test_precision_default_bits);
    RUN_TEST(test_precision_invalid_bits);
    RUN_TEST(test_precision_null_get_bits);
    RUN_TEST(test_precision_null_get_rounding);
    RUN_TEST(test_precision_rounding_mode);
    RUN_TEST(test_precision_invalid_rounding_mode);
    RUN_TEST(test_precision_affects_bigfloat);
    RUN_TEST(test_precision_multiple_changes);
    RUN_TEST(test_precision_rounding_affects_operations);
}
