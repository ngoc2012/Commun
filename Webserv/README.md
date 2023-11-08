# webserv

## Naming conventions:

- Class names, struct:	ThisIsMyClass
- Function names:	thisIsMyFunction
- Constants, macros:	CONSTANTS\_MACRO
- Class attributes:	\_attributes

## How the netcat command ```nc``` works:

[How to Use The Netcat (nc) Command](https://nooblinux.com/how-to-use-netcat/)
[Example](https://stackoverflow.com/questions/4238809/example-of-multipart-form-data)

## Upload a file to test the webserv:

```console
curl -X POST -F "file=@yourfile.txt" http://localhost/upload
```
