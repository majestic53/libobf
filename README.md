# LibObf (Obfusticate)

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/obf/blob/master/LICENSE) [![Build Status](https://github.com/majestic53/obf/workflows/Build/badge.svg)](https://github.com/majestic53/obf/actions/workflows/build.yml) [![Test Status](https://github.com/majestic53/obf/workflows/Test/badge.svg)](https://github.com/majestic53/obf/actions/workflows/test.yml)

### A lightweight obfustication library, written in C.

## Building from source

__NOTE__: This project has been tested under Linux, using the GCC compiler. Some modifications may be required to build with a different OS/compiler.

### Cloning the project

Clone the project from the repo:

```bash
git clone https://github.com/majestic53/obf
```

### Building the project

Navigate into the project directory and run make to build the binary:

```bash
cd obf && make
```

## Using the library

Include the library file under `include/`:

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

/* Read data blocks/length */
obf_block_t *blocks = ...;
size_t length = ...;

/* Encode the data blocks with key/IV and collect the modified IV */
obf_error_e result = obf_encode(&key, &iv, blocks, length);

if(result != OBF_SUCCESS) {
    /* Handle error */
}

...

/* Decode the data blocks with key and modified IV */
obf_error_e result = obf_decode(&key, &iv, blocks, length);

if(result != OBF_SUCCESS) {
    /* Handle error */
}
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/obf/blob/master/LICENSE).
