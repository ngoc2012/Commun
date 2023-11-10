# webserv

## README.md

[Example](https://github.com/github-linguist/linguist)

## Naming conventions

[Google rules](https://google.github.io/styleguide/cppguide.html)

- Class names, struct:  ThisIsMyClass
- Function names:       this\_is\_a\_function
- Constants, macros:    CONSTANTS\_MACRO
- Class attributes:     \_attributes\_of\_class

### Header files
Related header, C system headers, C++ standard library headers, other libraries' headers, your project's headers

Example header of a `fooserver.c`
```
#include "foo/server/fooserver.h"

#include <sys/types.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "foo/server/bar.h"
#include "third_party/absl/flags/flag.h"
```
### Vim (personal)

`qg` getter function
`qs` setter function

So to save a macro `'x'`, you can do:

    From normal mode: `qx`
    enter whatever commands
    From normal mode: `q`
    open `.vimrc`
    insert a line `let @x = '...'` (see the following)
    For the above `...` pattern, you can use `"xp` or `Ctrl+r Ctrl+r registerName` just at the place where the pattern should be placed. But this is not essential, you can just type in the macro definition.

## Basics tests

### How the netcat command ```nc``` works:

[How to Use The Netcat (nc) Command](https://nooblinux.com/how-to-use-netcat/)

[Example of using netcqt to send a file](https://stackoverflow.com/questions/4238809/example-of-multipart-form-data)

### Upload a file to test the webserv:

```console
curl -X POST -F "file=@yourfile.txt" http://localhost/upload
```

## Some C++ notions

[Static keyword](https://stackoverflow.com/questions/15235526/the-static-keyword-and-its-various-uses-in-c)