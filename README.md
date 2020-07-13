## Header File

C++ provides a number of useful functions that we can use to determine whether specific characters are numbers or letters - requires **cctype** header:

```
#include <cctype>
```

## Functions

|Function        |Description|
|----------------|-----------|
|``isalnum(int)``|Returns non-zero if the parameter is a letter or a digit.|
|``isalpha(int)``|Returns non-zero if the parameter is a letter.|
|``iscntrl(int)``|Returns non-zero if the parameter is a control character.|
|``isdigit(int)``| Returns non-zero if the parameter is a digit.|
|``isgraph(int)``| Returns non-zero if the parameter is printable character that is not whitespace.|
|``isprint(int)``| Returns non-zero if the parameter is printable character (including whitespace).|
|``ispunct(int)``| Returns non-zero if the parameter is neither alphanumeric or whitespace.|
|``isspace(int)``| Returns non-zero if the parameter is whitespace.|
|``isxdigit(int)``| Returns non-zero if the parameter is a hexadecimal digit (0-9, A-F).| 