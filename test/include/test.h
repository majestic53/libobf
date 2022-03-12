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
 * @file test.h
 * @brief Test header.
 */

#ifndef OBF_TEST_H_
#define OBF_TEST_H_

#include <assert.h>

/**
 * @brief Test count macro.
 * @param _TESTS_ Pointer to test array
 * @return Number of test in test array
 */
#define TEST_COUNT(_TESTS_) \
    sizeof(_TESTS_) / sizeof(*(_TESTS_))

/**
 * @brief Test result macro.
 * @param _RESULT_ Test result
 */
#define TEST_RESULT(_RESULT_) \
    fprintf(((_RESULT_) != OBF_SUCCESS) ? stderr : stdout, "[%s%s%s] %s\n", \
        ((_RESULT_) != OBF_SUCCESS) ? "\x1b[91m" : "\x1b[94m", \
        ((_RESULT_) != OBF_SUCCESS) ? "FAIL" : "PASS", \
        "\x1b[0m", __FUNCTION__)

/**
 * @brief Test function.
 * @return OBF_FAILURE on failure, OBF_SUCCESS otherwise
 */
typedef obf_error_e (*test)(void);

#endif /* OBF_TEST_H_ */
