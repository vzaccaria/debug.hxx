# debug

  tiny, C++11 header-only debug utility inspired to TJ's node and go debug libraries. Tested with clang.

## Installation

Just drop this file wherever you want and include it.

## Usage

With `debug` you simply invoke `Debug("your_module_name")` to generate your debug function. The debug function will log to cerr the string passed as parameter by prefixing it with the module name. By default, module names are printed in colors. You can disable this with the env variable `DEBUG_COLORS=no`.

## Example

Assume you have two c++ modules:

```c++
#include "debug.hxx"

auto debug = Debug("test");

void secondfunction() {
  debug("This is just another function");
}
```

and

```c++
#include <iostream>
#include "debug.hxx"

auto debug = Debug("main");

using namespace std;

extern void secondfunction();

int main(int argc, char const *argv[])
{
  debug("this is a main`s message");
  secondfunction();
  return 0;
}
```

You use the the __DEBUG__ environment variable to enable these based on a regular expression. Here are some examples:

  λ debug.hxx/ DEBUG=* ./bin/test                       
   main this is a main`s message
   test This is just another module message

  λ debug.hxx/ DEBUG=main ./bin/test                       
   main this is a main`s message

## Conventions

If you're using this in one or more of your libraries, you _should_ use the name of your library so that developers may toggle debugging as desired without guessing names. 

## Authors

- Vittorio Zaccaria

## Previous work

- TJ Holowaychuk
- Nathan Rajlich

## License

(The MIT License)

