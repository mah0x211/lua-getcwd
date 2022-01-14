local testcase = require('testcase')
local chdir = require('testcase.filesystem').chdir
local getcwd = require('getcwd')

local DIRS = {
    'foo',
    'bar',
    'baz',
}
local TESTDIR = table.concat(DIRS, '/')

local function exec(cmd)
    if string.find(_VERSION, '5.1', nil, true) then
        assert(os.execute(cmd) == 0, string.format('failed to %q', cmd))
    else
        assert(os.execute(cmd))
    end
end

function testcase.before_all()
    exec('mkdir -p ' .. TESTDIR)
end

function testcase.after_all()
    for i = #DIRS, 1, -1 do
        local dirname = table.concat(DIRS, '/', 1, i)
        os.remove(dirname)
    end
end

function testcase.getcwd()
    -- test that return current working directory
    local cwd = assert(getcwd())
    assert.match(cwd, '/lua%-getcwd/test$', false)

    -- test that change working directory
    local err = chdir(TESTDIR)
    assert(not err, err)
    cwd = assert(getcwd())
    assert.match(cwd, '/lua%-getcwd/test/' .. TESTDIR .. '$', false)
end
