# holghol

**holghol** is acronym for "header only library to generate header only
library".


## Usage

Download the `holghol.h` into your porject. Create a `holghol.c` and define the
implementation:

```c
#define HOLGHOL_IMPLEMENTATION
#include "holghol.h"
```

Create the main function and describe your project:
```c
#define HOLGHOL_IMPLEMENTATION
#include "holghol.h"

int main(int argc, char **argv) {
    const char *output = "my_lib.h";

    const char *intro[] = {
        "src/HEADER",
    };
    const char *includes_rm[] = {
        "my_lib.h",
        "my_lib_common.h",
    };
    const char *api[] = {
        "src/my_lib.h",
        "src/my_lib_common.h",
        "src/core.c",
        "src/files.c",
    };
    const char *footer[] = {
        "src/LICENSE",
        "src/LINKS",
    };

    gholCredits(output);
    gholPlainFile(intro, GHOL_ARRAY_SIZE(intro), output);
    gholIfdefine("MY_LIB", output);
    gholLibFile(api, GHOL_ARRAY_SIZE(api), includes_rm, GHOL_ARRAY_SIZE(includes_rm), output);
    gholEndif("MY_LIB", output);
    gholPlainFile(footer, GHOL_ARRAY_SIZE(footer), output);

    return 0;
}
```

The program above, gerenate the header for some library called `my_lib`.

To build your library, compile the file with your main function, and execute.

> If the output name is NULL, the result is print on stdout.

## Build from  source

You can build this lib from source.

It is recommended to use CMake, because it is already configured in the project.
If you want to compile directly, include the `build.c` file and all `.h` and
`.c` files in the `src` folder.

Using CMake:

```sh
cmake -S . -B build
cmake --build build
```

Inside the `build` directory there will be a `holghol` executable. Running the
program will generate `holghol.h` on the root folder.

## Test

Tests use
[unity 2.5.2](https://github.com/ThrowTheSwitch/Unity/releases/tag/v2.5.2).

To only build the tests

```sh
cmake -DTARGET_BUIL=test -S . -B build
cmake --build build
```

Inside `build` folder are other folder called `test`, all the test programs are
there.

##### Ispired by:

- [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear): A single-header ANSI
C immediate mode cross-platform GUI library

- [nobuild](https://github.com/tsoding/nobuild): Header only library for writing
build recipes in C.

- [stb](https://github.com/nothings/stb): stb single-file public domain
libraries for C/C++

