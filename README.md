# lua-getcwd

[![test](https://github.com/mah0x211/lua-getcwd/actions/workflows/test.yml/badge.svg)](https://github.com/mah0x211/lua-getcwd/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/mah0x211/lua-getcwd/branch/master/graph/badge.svg)](https://codecov.io/gh/mah0x211/lua-getcwd)

get working directory pathname.

## Installation

```
luarocks install getcwd
```

## Error Handling

the following functions return the `error` object created by https://github.com/mah0x211/lua-errno module.


## cwd, err = getcwd()

get the absolute pathname of the current working directory.

**Returns**

- `cwd:string`: the absolute pathname of the current working directory.
- `err:error`: error object on failure.

