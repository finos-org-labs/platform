/**
 * @file fc_bigint.h
 * @brief High-precision integer API
 *
 * Provides arbitrary-precision integer arithmetic backed by GMP.
 * All operations are thread-safe after initialization.
 */

#ifndef FC_BIGINT_H
#define FC_BIGINT_H

#include "error.h"
#include "platform.h"

FC_BEGIN_DECLS

/**
 * @brief Opaque handle for high-precision integer
 */
typedef struct fc_bigint fc_bigint_t;

/**
 * @brief Create a new high-precision integer initialized to zero
 *
 * @param[out] value_out Pointer to receive the created bigint handle
 *
 * @return FC_OK on success, FC_ERR_INVALID_ARG if value_out is NULL,
 *         FC_ERR_NOT_INITIALIZED if library not initialized,
 *         FC_ERR_OUT_OF_MEMORY if allocation fails
 */
FC_API fc_status_t fc_bigint_create(fc_bigint_t** value_out);

/**
 * @brief Destroy a high-precision integer and free its resources
 *
 * Safe to call with NULL pointer.
 *
 * @param value Bigint handle to destroy
 */
FC_API void fc_bigint_destroy(fc_bigint_t* value);

/**
 * @brief Copy a high-precision integer
 *
 * @param dest Destination bigint
 * @param src Source bigint
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_copy(fc_bigint_t* dest, const fc_bigint_t* src);

/**
 * @brief Set bigint from signed 64-bit integer
 *
 * @param value Bigint to set
 * @param input Input value
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_set_i64(fc_bigint_t* value, fc_int64_t input);

/**
 * @brief Set bigint from unsigned 64-bit integer
 *
 * @param value Bigint to set
 * @param input Input value
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_set_u64(fc_bigint_t* value, fc_uint64_t input);

/**
 * @brief Set bigint from decimal string
 *
 * @param value Bigint to set
 * @param input Decimal string (e.g., "12345", "-9876")
 *
 * @return FC_OK on success, FC_ERR_PARSE if string is invalid
 */
FC_API fc_status_t fc_bigint_set_str(fc_bigint_t* value, const char* input);

/**
 * @brief Convert bigint to signed 64-bit integer
 *
 * @param value Bigint to convert
 * @param[out] output Pointer to receive the result
 *
 * @return FC_OK on success, FC_ERR_OVERFLOW if value doesn't fit
 */
FC_API fc_status_t fc_bigint_get_i64(const fc_bigint_t* value, fc_int64_t* output);

/**
 * @brief Convert bigint to unsigned 64-bit integer
 *
 * @param value Bigint to convert
 * @param[out] output Pointer to receive the result
 *
 * @return FC_OK on success, FC_ERR_OVERFLOW if value doesn't fit or is negative
 */
FC_API fc_status_t fc_bigint_get_u64(const fc_bigint_t* value, fc_uint64_t* output);

/**
 * @brief Get required buffer size for string representation
 *
 * @param value Bigint to measure
 * @param[out] size_out Pointer to receive buffer size (including null terminator)
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_string_size(const fc_bigint_t* value, fc_size_t* size_out);

/**
 * @brief Convert bigint to decimal string
 *
 * @param value Bigint to convert
 * @param buffer Output buffer
 * @param buffer_size Size of output buffer
 *
 * @return FC_OK on success, FC_ERR_BUFFER_TOO_SMALL if buffer is too small
 */
FC_API fc_status_t
fc_bigint_to_string(const fc_bigint_t* value, char* buffer, fc_size_t buffer_size);

/**
 * @brief Add two bigints: result = lhs + rhs
 *
 * @param result Destination bigint
 * @param lhs Left operand
 * @param rhs Right operand
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t
fc_bigint_add(fc_bigint_t* result, const fc_bigint_t* lhs, const fc_bigint_t* rhs);

/**
 * @brief Subtract two bigints: result = lhs - rhs
 *
 * @param result Destination bigint
 * @param lhs Left operand
 * @param rhs Right operand
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t
fc_bigint_sub(fc_bigint_t* result, const fc_bigint_t* lhs, const fc_bigint_t* rhs);

/**
 * @brief Multiply two bigints: result = lhs * rhs
 *
 * @param result Destination bigint
 * @param lhs Left operand
 * @param rhs Right operand
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t
fc_bigint_mul(fc_bigint_t* result, const fc_bigint_t* lhs, const fc_bigint_t* rhs);

/**
 * @brief Divide two bigints: result = lhs / rhs (truncated toward zero)
 *
 * @param result Destination bigint
 * @param lhs Left operand
 * @param rhs Right operand
 *
 * @return FC_OK on success, FC_ERR_DIVIDE_BY_ZERO if rhs is zero
 */
FC_API fc_status_t
fc_bigint_div(fc_bigint_t* result, const fc_bigint_t* lhs, const fc_bigint_t* rhs);

/**
 * @brief Compute modulo: result = lhs mod rhs
 *
 * @param result Destination bigint
 * @param lhs Left operand
 * @param rhs Right operand
 *
 * @return FC_OK on success, FC_ERR_DIVIDE_BY_ZERO if rhs is zero
 */
FC_API fc_status_t
fc_bigint_mod(fc_bigint_t* result, const fc_bigint_t* lhs, const fc_bigint_t* rhs);

/**
 * @brief Negate a bigint: result = -input
 *
 * @param result Destination bigint
 * @param input Input bigint
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_neg(fc_bigint_t* result, const fc_bigint_t* input);

/**
 * @brief Absolute value: result = |input|
 *
 * @param result Destination bigint
 * @param input Input bigint
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_abs(fc_bigint_t* result, const fc_bigint_t* input);

/**
 * @brief Compare two bigints
 *
 * @param lhs Left operand
 * @param rhs Right operand
 * @param[out] cmp_out Pointer to receive comparison result:
 *                     negative if lhs < rhs, zero if lhs == rhs, positive if lhs > rhs
 *
 * @return FC_OK on success, error code otherwise
 */
FC_API fc_status_t fc_bigint_cmp(const fc_bigint_t* lhs, const fc_bigint_t* rhs, int* cmp_out);

FC_END_DECLS

#endif /* FC_BIGINT_H */
