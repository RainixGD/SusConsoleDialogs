# SusConsoleDialogs
A lightweight, header-only C++17 library for building simple, type-safe console dialogs - input prompts, yes/no questions, message boxes, and option/select menus - without writing the same std::cin parsing and validation loop over and over again.

## Installation
### Option 1:
Copy the `include/SusConsoleDialogs` folder into your project and add it to your include path:
```cpp
#include "./SusConsoleDialogs/SusConsoleDialogs.h>
```

### Option 2:
```bash
git submodule add https://github.com/RainixGD/SusConsoleDialogs.git libraries/SusConsoleDialogs
```

Add to CMakeLists.txt of your project:
```cmake
add_subdirectory(libraries/SusConsoleDialogs)
target_link_libraries(${PROJECT_NAME} PRIVATE SusConsoleDialogs)
```

*When the library is added as a submodule, examples won't be built*
