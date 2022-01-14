rockspec_format = '3.0'
package = 'getcwd'
version = 'scm-1'
source = {
    url = 'git+https://github.com/mah0x211/lua-getcwd.git',
}
description = {
    summary = 'get working directory pathname.',
    homepage = 'https://github.com/mah0x211/lua-getcwd',
    license = 'MIT/X11',
    maintainer = 'Masatoshi Fukunaga'
}
dependencies = {
    'lua >= 5.1',
}
build = {
    type = 'builtin',
    modules = {
        getcwd = {
            sources = { 'src/getcwd.c' }
        },
    }
}
