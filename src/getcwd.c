/**
 *  Copyright (C) 2022 Masatoshi Fukunaga
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
// lua
#include <lua_errno.h>

static size_t CWD_BUFSIZ = PATH_MAX;
static char *CWD_BUF     = NULL;

static int getcwd_lua(lua_State *L)
{
    char *cwd = getcwd(CWD_BUF, CWD_BUFSIZ);

    if (cwd) {
        lua_pushstring(L, cwd);
        return 1;
    }

    // got error
    lua_pushnil(L);
    lua_errno_new(L, errno, "getcwd");
    return 2;
}

LUALIB_API int luaopen_getcwd(lua_State *L)
{
    long pathmax = pathconf(".", _PC_PATH_MAX);

    lua_errno_loadlib(L);

    // set the maximum number of bytes in a pathname
    if (pathmax != -1) {
        CWD_BUFSIZ = pathmax;
    }
    // allocate the buffer for getcwd
    CWD_BUF = lua_newuserdata(L, CWD_BUFSIZ);
    // holds until the state closes
    luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushcfunction(L, getcwd_lua);
    return 1;
}
