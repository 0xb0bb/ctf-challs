# Chall 02

## Description

A silly application that takes some data from the user and then generates crc32
checksums from each block of 16 bytes and then executes a given function based
on that value. So it is possible to call a list of junk functions in whatever
order the user wishes.

The application has a combination of bugs, the leaks can all be used in any
order (and are interchangable)

  1. casting error on debug switch (used to enable leak)
  2. printing 15 bytes of "random" stack space (leak depending on what is there).
  3. free() on arb memory.
  4. possible buffer overflow/.
  5. leblancian paradox

## Bugs

There are three main bugs required to pwn this optimally.

### Casting Error

The user only has 3 tries to input something that pops a shell. If there is an
error reading the input, it does not count as one of their tries. To implement
this there is a `fail` counter that is right next to the `debug` switch (that
is supposed to only be invoked from the command line). Due to an error in
casting when passing this value around the application it is possible to
increase the 32bit `fail` counter so that the 32bit `debug` switch will be
greater than 0 when cast as a 64bit long int.

One of the easiest ways to trigger the fail counter is just to ensure the
strlen() returns 0 for the user input.

Using this casting error it is possible to enable the `debug` functionality
which will write a hexdump and the crc32 of each 16 byte block of input to the
user. This will be useful to provide a leak as if 1024 bytes are written by the
user then the input is squeezed next to the list of function pointers.

There are other ways to leak, but this is by far the least painful and quickest
route.

### Leblancian Paradox

The application will decide what function to execute based on the CRC by
performing `abs(crc) % 0xf`. This means the application is vulnerable to an
interesting edge case that relies on a beautiful old school ASM optimsation
combined with the fact that there is 1 more number in the negative range of a
signed integer than in the similar positive range.

To understand why, the usual asm operations for abs must be considered:

```asm
    cdq           ; eax sign to edx, if > 0 edx = 0 else edx = -1
    xor eax, edx  ; if edx == 0 then eax will stay the same
    sub eax, edx  ; subtract eax with result of xor, 0 if eax was > 0
```

So this means that:

```asm
    eax = 0x80000000
    edx = 0xffffffff
    eax = 0x80000000 xor 0xffffffff (0x7fffffff)
    eax = 0x7fffffff  -  0xffffffff (0x80000000)
```

Using this it is possible to get an out of bounds reference for a function
pointer and since there is a reference to system() within the binary, it is an
easy win.

The application will also call the function pointer with the contents of the
string that generated the CRC in the first place. So this means the goal will
be to provide a string that is both a valid shell argument and makes a CRC
value that equals `0x80000000`.

Luckily there are two methods to do this that are both feasible. The first is
to just brute force something like

```
  /bin/sh#????
```

Or you can just use a known tool like `forcecrc32` (https://www.nayuki.io/page/forcing-a-files-crc-to-any-value).
