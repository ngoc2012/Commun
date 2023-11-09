# webserv

## README.md

[Example](https://github.com/github-linguist/linguist/blob/3c3b037910006fc2f1a9bb34b2c4e9cde062206c/README.md)

## Naming conventions

[Google rules](https://google.github.io/styleguide/cppguide.html)

- Class names, struct:  ThisIsMyClass
- Function names:       this\_is\_a\_function
- Constants, macros:    CONSTANTS\_MACRO
- Class attributes:     \_attributes\_of\_class

### Header files
Related header, C system headers, C++ standard library headers, other libraries' headers, your project's headers

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
