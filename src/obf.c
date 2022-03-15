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
 * @file obf.c
 * @brief LibObf implementation.
 */

#include <obf.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Decode block.
 * @param iv Pointer to IV struct
 * @param left Left block data
 * @param right Right block data
 * @return Decoded block
 */
static obf_block_t obf_decode_block(obf_iv_t *iv, obf_block_t left, obf_block_t right)
{
    /* xor with pre-decremented IV */
    return (left ^ right ^ --(*iv));
}

/*!
 * @brief Encode block.
 * @param iv Pointer to IV struct
 * @param left Left block data
 * @param right Right block data
 * @return Encoded block
 */
static obf_block_t obf_encode_block(obf_iv_t *iv, obf_block_t left, obf_block_t right)
{
    /* xor with post-incremented IV */
    return (left ^ right ^ (*iv)++);
}

/*!
 * @brief Decode blocks.
 * @param key Constant pointer to key struct
 * @param iv Pointer to IV struct
 * @param data Pointer to data blocks
 * @param length Number of blocks in data
 */
static void obf_decode_blocks(const obf_key_t *key, obf_iv_t *iv, obf_block_t *data, size_t length)
{
    obf_iv_t tiv = 0;

    /* Unwrap IV */
    *iv = obf_encode_block(&tiv, *iv, data[0]);
    *iv = obf_encode_block(&tiv, *iv, key->low * key->high);

    /* Decode ciphertext blocks with key high-part */
    for(size_t index = 0; index < length; ++index) {
        data[index] = obf_decode_block(iv, data[index], index == (length - 1) ? key->high : data[index + 1]);
    }

    /* Decode ciphertext blocks with key low-part */
    for(size_t index = 0; index < length; ++index) {
        data[length - index - 1] = obf_decode_block(iv, data[length - index - 1], index == (length - 1) ? key->low : data[length - index - 2]);
    }
}

/*!
 * @brief Encode blocks.
 * @param key Constant pointer to key struct
 * @param iv Pointer to IV struct
 * @param data Pointer to data blocks
 * @param length Number of blocks in data
 */
static void obf_encode_blocks(const obf_key_t *key, obf_iv_t *iv, obf_block_t *data, size_t length)
{
    obf_iv_t tiv = 0;

    /* Encode plaintext blocks with key low-part */
    for(size_t index = 0; index < length; ++index) {
        data[index] = obf_encode_block(iv, data[index], !index ? key->low : data[index - 1]);
    }

    /* Encode plaintext blocks with key high-part */
    for(size_t index = 0; index < length; ++index) {
        data[length - index - 1] = obf_encode_block(iv, data[length - index - 1], !index ? key->high : data[length - index]);
    }

    /* Wrap IV */
    *iv = obf_encode_block(&tiv, *iv, key->low * key->high);
    *iv = obf_encode_block(&tiv, *iv, data[0]);
}

/*!
 * @brief Validate arguments.
 * @param key Constant pointer to key struct
 * @param iv Pointer to IV struct
 * @param data Pointer to data blocks
 * @param length Number of blocks in data
 * @return OBF_SUCCESS on success, OBF_INVALID_KEY, OBF_INVALID_IV, OBF_INVALID_DATA or OBF_INVALID_LENGTH otherwise
 */
static obf_error_e obf_validate(const obf_key_t *key, const obf_iv_t *iv, const obf_block_t *data, size_t length)
{
    obf_error_e result = OBF_SUCCESS;

    /* Validate key is non-NULL */
    if(!key) {
        result = OBF_INVALID_KEY;
        goto exit;
    }

    /* Validate IV is non-NULL */
    if(!iv) {
        result = OBF_INVALID_IV;
        goto exit;
    }

    /* Validate data is non-NULL */
    if(!data) {
        result = OBF_INVALID_DATA;
        goto exit;
    }

    /* Validate length is non-zero */
    if(!length) {
        result = OBF_INVALID_LENGTH;
        goto exit;
    }

exit:
    return result;
}

obf_error_e obf_decode(const obf_key_t *key, obf_iv_t *iv, obf_block_t *data, size_t length)
{
    obf_error_e result;

    /* Validate ciphertext arguments */
    if((result = obf_validate(key, iv, data, length)) != OBF_SUCCESS) {
        goto exit;
    }

    /* Decode ciphertext */
    obf_decode_blocks(key, iv, data, length);

exit:
    return result;
}

obf_error_e obf_encode(const obf_key_t *key, obf_iv_t *iv, obf_block_t *data, size_t length)
{
    obf_error_e result;

    /* Validate plaintext arguments */
    if((result = obf_validate(key, iv, data, length)) != OBF_SUCCESS) {
        goto exit;
    }

    /* Encode plaintext */
    obf_encode_blocks(key, iv, data, length);

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
