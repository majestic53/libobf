/*
 * LibObf
 * Copyright (C) 2022 David Jolly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * @file obf.h
 * @brief LibObf interface.
 */

#ifndef OBF_H_
#define OBF_H_

#include <stddef.h>
#include <stdint.h>

#define OBF_API_VERSION_1 1                 /*!< Interface version 1 */
#define OBF_API_VERSION OBF_API_VERSION_1   /*!< Current interface version */

/*!
 * @enum obf_error_e
 * @brief LibObf error codes.
 */
typedef enum {
    OBF_SUCCESS = 0,                        /*!< Operation succeeded */
    OBF_FAILURE,                            /*!< Operation failed */
    OBF_INVALID_KEY,                        /*!< Invalid key argument */
    OBF_INVALID_IV,                         /*!< Invalid IV argument */
    OBF_INVALID_DATA,                       /*!< Invalid data argument */
    OBF_INVALID_LENGTH,                     /*!< Invalid length argument */
} obf_error_e;

/*!
 * @typedef obf_block_t
 * @brief LibObf block type.
 */
typedef uint32_t obf_block_t;

/*!
 * @typedef obf_iv_t
 * @brief LibObf IV type.
 */
typedef uint32_t obf_iv_t;

/*!
 * @union obf_key_t
 * @brief LibObf key type.
 */
typedef union {

    struct {
        uint32_t low;                       /*!< Key (low-part) */
        uint32_t high;                      /*!< Key (high-part) */
    };

    uint64_t raw;                           /*!< Raw key */
} obf_key_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Decode data blocks using key and IV.
 * @param key Constant pointer to key struct
 * @param iv Pointer to IV struct
 * @param data Pointer to data blocks
 * @param length Number of blocks in data
 * @return OBF_SUCCESS on success, OBF_INVALID_KEY, OBF_INVALID_IV, OBF_INVALID_DATA or OBF_INVALID_LENGTH otherwise
 */
obf_error_e obf_decode(const obf_key_t *key, obf_iv_t *iv, obf_block_t *data, size_t length);

/*!
 * @brief Encode data blocks using key and IV.
 * @param key Constant pointer to key struct
 * @param iv Pointer to IV struct
 * @param data Pointer to data blocks
 * @param length Number of blocks in data
 * @return OBF_SUCCESS on success, OBF_INVALID_KEY, OBF_INVALID_IV, OBF_INVALID_DATA or OBF_INVALID_LENGTH otherwise
 */
obf_error_e obf_encode(const obf_key_t *key, obf_iv_t *iv, obf_block_t *data, size_t length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OBF_H_ */
