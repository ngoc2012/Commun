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
`qc` getter to setter function
`qt` function definition to forward declaration

So to save a macro `'x'`, you can do:

    From normal mode: `qx`
    enter whatever commands
    From normal mode: `q`
    open `.vimrc`
    insert a line `let @x = '...'` (see the following)
    For the above `...` pattern, you can use `"xp` or `Ctrl+r Ctrl+r registerName` just at the place where the pattern should be placed. But this is not essential, you can just type in the macro definition.

## Basics tests

### How the netcat command `nc` works:

[How to Use The Netcat (nc) Command](https://nooblinux.com/how-to-use-netcat/)

[Example of using netcqt to send a file](https://stackoverflow.com/questions/4238809/example-of-multipart-form-data)

### Upload a file to test the webserv:

```console
curl -X POST -F "file=@yourfile.txt" http://localhost/upload
```

`-X`, `--request <method>`

(HTTP) Specifies a custom request method to use when communicating with the HTTP server.  The specified request method will be used instead of the method  otherwise  used  (which defaults  to  GET). Read the HTTP 1.1 specification for details and explanations. Common additional HTTP requests include PUT and DELETE, but related  technologies  like  WebDAV offers PROPFIND, COPY, MOVE and more.

Normally  you do not need this option. All sorts of GET, HEAD, POST and PUT requests are rather invoked by using dedicated command line options.  This option only changes the actual word used in the HTTP request, it does not alter the way  curl  behaves.  So  for example if you want to make a proper HEAD request, using -X HEAD will not suffice. You need to use the -I, --head option.

The method string you set with -X, --request will be used for all requests, which if you for  example  use  -L,  --location  may cause unintended side-effects when curl does not change request method according to the HTTP 30x response codes - and similar.

(FTP) Specifies a custom FTP command to use instead of LIST when doing file  lists  with FTP.

(POP3) Specifies a custom POP3 command to use instead of LIST or RETR.

(IMAP) Specifies a custom IMAP command to use instead of LIST. (Added in 7.30.0)

(SMTP) Specifies a custom SMTP command to use instead of HELP or VRFY. (Added in 7.34.0)

If this option is used several times, the last one will be used.

Examples:
 ``` console
 curl -X "DELETE" https://example.com
 curl -X NLST ftp://example.com/
 ```


## Some C++ notions

[Static keyword](https://stackoverflow.com/questions/15235526/the-static-keyword-and-its-various-uses-in-c)

## HTTP
HTTP requests typically include a Content-Type header that indicates the type of data in the request body. Here are some common Content-Type values:

* `application/json`: Used for JSON data.
* `application/xml`: Used for XML data.
* `application/x-www-form-urlencoded`: Used for form data submitted in the body of the request.
* `multipart/form-data`: Used when submitting forms that include binary data, like file uploads.
* `text/plain`: Used for plain text data.
* `application/octet-stream`: Used for binary data when the specific type is not known.
