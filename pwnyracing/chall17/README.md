# Chall 17 (Episode 10)

## Challenge

There is a trivial stack based buffer overflow in this tiny binary. There are
two main issues, firstly the overflow is small so the ROP chain is limited.
The second issue the player will discover is that there is no output of any
kind. Not only are there no output functions in the binary but `stdout` and
`stderr` are redirected to `/dev/null` through the wrapper script.

The way to solve this challenge is a classic ret2dlresolv and then ret2plt.
The idea is to fake a symbol table and relocation table entry in order to
have a function resolved without the need for any leaks.

### Method 1 (Fast)

There is a library that some people use called `roputils` that will forge the
structures for you. This can be done in two lines of code.

### Method 2 (Slower)

The method in the reference exploit is to do everything manually. Firstly the
player uses the small buffer overflow in order to read a second payload and
pivot to a known memory address (in `.data`). At that point they will be able
to plant strings and structs at known memory locations which allows them to
calculate the offsets of indexes to their forged structures relative to the
relocation and symbol tables. This will allow them to trigger the resolve
lookup for a given function (possibly `system()` and in that case they can
also plant a string for a command to execute).

At this point all they will need to do is fire a specific command, they will
need to remember that they have no output due to the wrapper.

## Protections

```
Arch:     i386-32-little
RELRO:    Partial RELRO
Stack:    No canary found
NX:       NX enabled
PIE:      No PIE (0x8048000)
```