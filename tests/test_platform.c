/**
 * @file test_platform.c
 * @brief platform module test entry point
 *
 * This file serves as the main test registration point for the platform module.
 * Individual test modules are in separate files:
 */

#include "test_framework.h"

/* External test registration functions from sub-modules */
extern void register_bigint_tests(void);
extern void register_bigfloat_tests(void);
extern void register_precision_tests(void);

/* Entry point for platform tests */
void register_platform_tests(void) {
    /* Register all sub-module tests */
    register_bigint_tests();
    register_bigfloat_tests();
    register_precision_tests();
}
