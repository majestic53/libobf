# LibObf (Obfusticate)

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/libobf/blob/master/LICENSE.md) [![Build Status](https://github.com/majestic53/libobf/workflows/Build/badge.svg)](https://github.com/majestic53/libobf/actions/workflows/build.yml) [![Test Status](https://github.com/majestic53/libobf/workflows/Test/badge.svg)](https://github.com/majestic53/libobf/actions/workflows/test.yml)

### A lightweight obfustication library, written in C.

This library offers a quick way to obfusticate arbitrary data in a reverable way. No actual encryption is performed, so the results should not be considered cryptographically secure.

The algorithm uses a simple xor block cipher, which takes a 64-bit key, 32-bit IV and encoding the data in 32-bit blocks:

<p align="center">
    <img src=https://github.com/majestic53/libobf/raw/master/docs/overview.png>
</p>

The encoding process walks through the 32-bit blocks, encoding each block using the previous block and IV as input. At the end, the IV is wrapped one final time with the key:

<p align="center">
    <img src=https://github.com/majestic53/libobf/raw/master/docs/encode.png>
</p>

Similiarly, the decoding process performes the same process in reverse. First the IV is unwrapped, followed by decoding each block using the previous block and IV as input:

<p align="center">
    <img src=https://github.com/majestic53/libobf/raw/master/docs/decode.png>
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

/* Encode the data blocks with key/IV and collect the modified data blocks/IV */
obf_error_e result = obf_encode(&key, &iv, blocks, length);
if(result != OBF_SUCCESS) {
    /* Handle error */
}

...

/* Decode the modified data blocks with key and modified IV */
obf_error_e result = obf_decode(&key, &iv, blocks, length);
if(result != OBF_SUCCESS) {
    /* Handle error */
}
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/libobf/blob/master/LICENSE.md).
