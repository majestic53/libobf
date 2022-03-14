# LibObf (Obfusticate)

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/libobf/blob/master/LICENSE.md) [![Build Status](https://github.com/majestic53/libobf/workflows/Build/badge.svg)](https://github.com/majestic53/libobf/actions/workflows/build.yml) [![Test Status](https://github.com/majestic53/libobf/workflows/Test/badge.svg)](https://github.com/majestic53/libobf/actions/workflows/test.yml)

### A lightweight obfustication library, written in C.

This library offers a quick way to obfusticate arbitrary data in a reverable way. __No actual encryption is performed, so the results should not be considered cryptographically secure.__

The algorithm uses a simple xor block cipher, which takes a 64-bit key, 32-bit IV and encodes/decodes data in 32-bit blocks:

<p align="center">
    <img src=https://github.com/majestic53/libobf/raw/master/docs/encode_0.png><img src=https://github.com/majestic53/libobf/raw/master/docs/decode_0.png>
</p>

The encoding process walks through the 32-bit blocks, encoding each block using the previous block and IV as input. At the end, the IV is wrapped one final time with the key:

<p align="center">
    <img src=https://github.com/majestic53/libobf/raw/master/docs/encode_1.png>
</p>

Similiarly, the decoding process performes the same process in reverse. First the IV is unwrapped, followed by decoding each block using the previous block and IV as input:

<p align="center">
    <img src=https://github.com/majestic53/libobf/raw/master/docs/decode_1.png>
</p>

## Building from source

__NOTE__: This project has been tested under Linux, using the GCC compiler. Some modifications may be required to build with a different OS/compiler.

### Cloning the project

Clone the project from the repo:

```bash
git clone https://github.com/majestic53/libobf
```

### Building the project

Navigate into the project directory and run make to build the binary:

```bash
cd libobf && make
```

## Using the library

Include the header file under `include/`:

```c
#include <obf.h>
```

Link to the library file under `build/`

```
-lobf
```

### Example usage

```c
/* Derive key/IV */
obf_key_t key = { .low = ..., .high = ... };
obf_iv_t iv = ...;

/* Setup data blocks/length */
obf_block_t *blocks = ...;
size_t length = ...;

/* Encode the data blocks with key/IV and collect the encoded data blocks/wrapped IV */
obf_error_e result = obf_encode(&key, &iv, blocks, length);
if(result != OBF_SUCCESS) {
    /* Handle error */
}

...

/* Decode the encoded data blocks with key and wrapped IV */
obf_error_e result = obf_decode(&key, &iv, blocks, length);
if(result != OBF_SUCCESS) {
    /* Handle error */
}
```

### Example output

```
Length = 32
Key    = 46637DB934A49B2F
IV     = 6211E62D

Plain  = 1F881BC4, 5BA82F51, 47500AA1, 58D7785B, 72D9931A, 2DF41AE3, 0EC22562, 664FFC1E,
         0901CBBF, 4919D44A, 74309B07, 24E65908, 70B4C9D9, 5989064A, 7D3406CE, 433CBE34,
         05B2BCF9, 497C83FF, 29E9ED9E, 0174FC8A, 4583A8A0, 196CB5C8, 629058F8, 50D6BD10,
         40135A9D, 0FECA49E, 0F32369C, 1D94399A, 71FE8ACB, 43D6D1CB, 63F7B753, 1186A68F

IV     = 10D600FA

Cipher = 387764DF, 135BE475, 01CEADA7, 361A08FA, 3B0833CF, 26D27DD0, 74EDCF11, 4A01BE80,
         70B3D538, 2111930B, 5BBBE743, 3730EE3A, 1D4C5870, 2595C1DB, 26D4B83F, 3AB0212F,
         07F9E034, 5D137BEA, 2C9485F2, 16EB704A, 4FF19F3B, 31793EAA, 348CCCBE, 31F88010,
         064B97E9, 13FA3CC9, 6BB6D536, 7ED9EC13, 14330AE7, 6D368090, 35F43D79, 6CD0D189

IV     = 6211E62D

Plain  = 1F881BC4, 5BA82F51, 47500AA1, 58D7785B, 72D9931A, 2DF41AE3, 0EC22562, 664FFC1E,
         0901CBBF, 4919D44A, 74309B07, 24E65908, 70B4C9D9, 5989064A, 7D3406CE, 433CBE34,
         05B2BCF9, 497C83FF, 29E9ED9E, 0174FC8A, 4583A8A0, 196CB5C8, 629058F8, 50D6BD10,
         40135A9D, 0FECA49E, 0F32369C, 1D94399A, 71FE8ACB, 43D6D1CB, 63F7B753, 1186A68F
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/libobf/blob/master/LICENSE.md).
