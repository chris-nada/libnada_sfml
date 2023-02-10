# libnada_sfml - SFML Addons

+ **C++17 or later required**
+ only SFML required

**Documented**
+ Usage examples see below
+ All functions are documented in their headers

**Unit Tested**
+ in `./test/` using the awesome [doctest header-only library](https://github.com/doctest/doctest/)
+ tests also provide more usage examples

## How to include in your project
1. Git clone or copy folder `libnada` to the same directory your `CMakeLists.txt` is in.
2. Add these 3 lines to your `CMakeLists.txt`
```cmake
    ...
    add_subdirectory(libnada_sfml)
    ...
    include_directories(libnada_sfml/include)
    ...
    target_link_libraries(PROJECT_NAME PRIVATE nada_sfml)
    ...
```
## Usage examples

### Particle
### `#include <nada/particle.hpp>`
TODO

### Gif
### `#include <nada/gif.hpp>`
TODO

### Graphic
### `#include <nada/graphic.hpp>`
TODO
