/**
 * @file fc_bignum_internal.h
 * @brief Internal declarations for high-precision bignum subsystem
 *
 * This header is private to the platform module implementation.
 * It provides shared struct definitions and internal functions for
 * bigint, bigfloat, and precision management.
 */

#ifndef FC_BIGNUM_INTERNAL_H
#define FC_BIGNUM_INTERNAL_H

#include "error.h"
#include "fc_precision.h"

#include <gmp.h>
#include <mpfr.h>

/**
 * @brief Internal representation of high-precision integer
 */
typedef struct fc_bigint {
    mpz_t value;
} fc_bigint_impl_t;

/**
 * @brief Internal representation of high-precision floating-point
 */
typedef struct fc_bigfloat {
    mpfr_t value;
} fc_bigfloat_impl_t;

/**
 * @brief Initialize the bignum subsystem
 *
 * Called by fc_init(). Sets up GMP memory hooks and MPFR defaults.
 *
 * @return FC_OK on success, error code otherwise
 */
fc_status_t fc_bignum_global_init(void);

/**
 * @brief Clean up the bignum subsystem
 *
 * Called by fc_cleanup(). Frees MPFR caches.
 */
void fc_bignum_global_cleanup(void);

/**
 * @brief Check if bignum subsystem is initialized
 *
 * @return 1 if initialized, 0 otherwise
 */
int fc_bignum_is_initialized(void);

/**
 * @brief Get current default rounding mode
 *
 * @return Current rounding mode
 */
fc_rounding_mode_t fc_bignum_current_rounding_mode(void);

/**
 * @brief Get current default precision bits (internal accessor)
 *
 * @return Current default precision in bits
 */
fc_uint64_t fc_precision_get_default_bits_internal(void);

/**
 * @brief Get current rounding mode (internal accessor)
 *
 * @return Current rounding mode
 */
fc_rounding_mode_t fc_precision_get_rounding_mode_internal(void);

/**
 * @brief Apply current defaults to MPFR global state
 *
 * Called during initialization to sync platform defaults with MPFR.
 */
void fc_precision_apply_defaults_to_mpfr(void);

#endif /* FC_BIGNUM_INTERNAL_H */
