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
Key    = 7D1D263759F45E16
IV     = 1D07D801

Plain  = 5094D678, 540C2EA8, 6465EA31, 56D71C0D, 285C9585, 2D100B4D, 311A3DA8, 56C73EA8,
         11257B06, 0486CC36, 1512BD26, 5178E29E, 72A920B9, 5551FFA7, 287E574B, 26857C4B,
         0D2339E4, 757EF510, 4C0724E9, 18174FE7, 05AD8ADC, 1953D5F2, 196B5DC1, 180A8A72,
         61138345, 7D1041BA, 646D28D4, 2161E972, 1A1819BB, 3E6186EA, 1E7F0FA9, 6AACF033

IVW    = 39EEA061

Cipher = 46B7B715, 4FD73F3A, 0FBC41C0, 36B50D09, 446C85CA, 03EE4088, 747B5686, 2FF3A526,
         3FBBB025, 23D10628, 263AA416, 2BC46304, 6A459E87, 446A9BB1, 2213B929, 711314F4,
         19911D71, 6137F500, 71E8306C, 303709FB, 74F8A79C, 289D5B33, 70ACAA7F, 2CF1DEE4,
         75A1F816, 50E585B9, 15B661B9, 298F7577, 29D050D4, 2E90B4D0, 0AB60E27, 2DE86367

IV     = 1D07D801

Plain  = 5094D678, 540C2EA8, 6465EA31, 56D71C0D, 285C9585, 2D100B4D, 311A3DA8, 56C73EA8,
         11257B06, 0486CC36, 1512BD26, 5178E29E, 72A920B9, 5551FFA7, 287E574B, 26857C4B,
         0D2339E4, 757EF510, 4C0724E9, 18174FE7, 05AD8ADC, 1953D5F2, 196B5DC1, 180A8A72,
         61138345, 7D1041BA, 646D28D4, 2161E972, 1A1819BB, 3E6186EA, 1E7F0FA9, 6AACF033
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/libobf/blob/master/LICENSE.md).
