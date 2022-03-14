/**
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

/**
 * @file main.c
 * @brief Test application for LibObf.
 */

#include <stdlib.h>
#include <time.h>
#include <test.h>

#define BLOCK_LENGTH 32 /*< Test data blocks */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Print block contents.
 * @param data Pointer to data blocks
 * @param length Number of blocks in data
 */
static void print_blocks(const obf_block_t *data, size_t length)
{

    for(size_t index = 0; index < length; ++index) {

        if(index && !(index % 8)) {
            fprintf(stdout, "\n         ");
        }

        fprintf(stdout, "%08X", data[index]);

        if(index < (length - 1)) {
            fprintf(stdout, ", ");
        }
    }

    fprintf(stdout, "\n");
}

/**
 * @brief Test encode/decode arguments validation.
 * @return OBF_SUCCESS on success, OBF_FAILURE otherwise
 */
static obf_error_e test_arguments(void)
{

    obf_iv_t iv = 0;
    obf_key_t key = {};
    size_t length = BLOCK_LENGTH;
    obf_error_e result = OBF_SUCCESS;
    obf_block_t block[BLOCK_LENGTH] = {};

    if(ASSERT(obf_encode(NULL, &iv, block, length) == OBF_INVALID_KEY)) {
        result = OBF_FAILURE;
        goto exit;
    }

    if(ASSERT(obf_encode(&key, NULL, block, length) == OBF_INVALID_IV)) {
        result = OBF_FAILURE;
        goto exit;
    }

    if(ASSERT(obf_encode(&key, &iv, NULL, length) == OBF_INVALID_DATA)) {
        result = OBF_FAILURE;
        goto exit;
    }

    if(ASSERT(obf_encode(&key, &iv, block, 0) == OBF_INVALID_LENGTH)) {
        result = OBF_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

/**
 * @brief Test encode/decode.
 * @return OBF_SUCCESS on success, OBF_FAILURE otherwise
 */
static obf_error_e test_encode_decode(void)
{
    obf_error_e result = OBF_SUCCESS;
    size_t index, length = BLOCK_LENGTH;

    obf_iv_t iv = rand(), iv_cipher = iv;
    obf_key_t key = { .low = rand(), .high = rand() };
    obf_block_t cipher[BLOCK_LENGTH] = {}, plain[BLOCK_LENGTH] = {};

    for(index = 0; index < length; ++index) {
        plain[index] = rand();
        cipher[index] = plain[index];
    }

    fprintf(stdout, "Length = %zu\n", length);
    fprintf(stdout, "Key    = %08X%08X\n", key.high, key.low);
    fprintf(stdout, "IV     = %08X\n", iv);
    fprintf(stdout, "\nPlain  = ");
    print_blocks(plain, length);

    if(ASSERT(obf_encode(&key, &iv_cipher, cipher, length) == OBF_SUCCESS)) {
        result = OBF_FAILURE;
        goto exit;
    }

    fprintf(stdout, "\nIVW    = %08X\n", iv_cipher);
    fprintf(stdout, "\nCipher = ");
    print_blocks(cipher, length);

    for(index = 0; index < length; ++index) {

        if(ASSERT(cipher[index] != plain[index])) {
            result = OBF_FAILURE;
            goto exit;
        }
    }

    if(ASSERT(iv_cipher != iv)) {
        result = OBF_FAILURE;
        goto exit;
    }

    if(ASSERT(obf_decode(&key, &iv_cipher, cipher, length) == OBF_SUCCESS)) {
        result = OBF_FAILURE;
        goto exit;
    }

    fprintf(stdout, "\nIV     = %08X\n", iv_cipher);
    fprintf(stdout, "\nPlain  = ");
    print_blocks(cipher, length);

    for(index = 0; index < length; ++index) {

        if(ASSERT(cipher[index] == plain[index])) {
            result = OBF_FAILURE;
            goto exit;
        }
    }

    if(ASSERT(iv_cipher == iv)) {
        result = OBF_FAILURE;
        goto exit;
    }

exit:
    TEST_RESULT(result);

    return result;
}

int main(void)
{
    static const test TEST[] = {
        test_arguments,
        test_encode_decode,
        };

    obf_error_e result = OBF_SUCCESS;

    srand(time(NULL));

    for(int index = 0; index < TEST_COUNT(TEST); ++index) {

        if(TEST[index]() == OBF_FAILURE) {
            result = OBF_FAILURE;
        }
    }

    return (int)result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
