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
Key    = 1E03C35F139284D4
IV     = 2690C487

Plain  = 22600419, 6A0BAFCE, 6B9E78B5, 405B93EC, 33D53378, 39F327EE, 11200CCF, 62133550,
         5F5EA47C, 526D243B, 5CC9E7BF, 646D924D, 50A420C0, 159B43B3, 7306736A, 32116E90,
         5F9F6ABA, 5418A129, 2498B06A, 45AA10BD, 7B278B82, 74E888AC, 0DD6BCEA, 13ECE325,
         48DF7EA0, 1CDC4FE2, 0D44EF1E, 4B21132A, 436D1469, 20D773F2, 6924D689, 65CD1882

IVW    = 79F09939

Cipher = 1A689B53, 2B9A1BDF, 56F3F016, 6694A7E2, 3038A777, 73D15010, 2F5B4416, 44619853,
         6BD8B5B7, 3DAFF8A1, 1F25551F, 47F6DB8E, 5DD803C7, 31C23FDC, 6ED384E3, 64548822,
         7A522EEA, 1D5B260E, 08DA4B58, 1F5352FC, 6BE09F78, 42E41DE4, 3998D34B, 69A26592,
         0CE4F4EF, 07EDDFAC, 36A87FAE, 2C39F412, 5B19A821, 49C424D9, 5D5E1F74, 067036F4

IV     = 2690C487

Plain  = 22600419, 6A0BAFCE, 6B9E78B5, 405B93EC, 33D53378, 39F327EE, 11200CCF, 62133550,
         5F5EA47C, 526D243B, 5CC9E7BF, 646D924D, 50A420C0, 159B43B3, 7306736A, 32116E90,
         5F9F6ABA, 5418A129, 2498B06A, 45AA10BD, 7B278B82, 74E888AC, 0DD6BCEA, 13ECE325,
         48DF7EA0, 1CDC4FE2, 0D44EF1E, 4B21132A, 436D1469, 20D773F2, 6924D689, 65CD1882
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/libobf/blob/master/LICENSE.md).
