# Chall 01

## Description

The application has two (intentional) bugs:

  1. stack based buffer overflow.
  2. malloc result is not checked.

## Bugs

### Buffer Overflow

There is a simple buffer overflow, the stack is setup like:

```
  +-----------------+
  | buffer[00 - 03] |  <----+
  +-----------------+       |
  +-----------------+       |
  | buffer[04 - 07] |       |
  +-----------------+       |
  +-----------------+       |
  | buffer[08 - 0b] |       |
  +-----------------+       |
  +-----------------+       |
  | buffer[0c - 0f] |       |
  +-----------------+       |
  +-----------------+       |
  | buffer[10 - 13] |       |
  +-----------------+       |
  +-----------------+       |
  | buffer[14 - 17] |       |
  +-----------------+       |
  +-----------------+       |
  | buffer[18 - 1b] |       |
  +-----------------+       |
  +-----------------+       |
  | ptr             |  -----+
  +-----------------+
```

So the buffer is written to, byte by byte through the ptr pointer, once the
buffer overflows it will write into that very pointer. This poses a bit of a
problem since there is no stable way to overwrite the pointer, instead you can
just alter the LSByte.

This means that sending too many characters into the first buffer you see, even
though it is vulnerable may not result in a crash you can take advantage of
right away, at least nothing to yield a 0x41414141.

Normally this sort of thing could be used to "jump" over the stack canary in
order to alter the saved return address, however in this case, the function
will never return as there is an _exit call (so no handler hooks will be run).

At this point it will feel like a dead end.

### Malloc results are not checked

Every decent programmer knows two things about malloc, firstly that you do not
need to cast the results and also to always check the result of a call to
malloc. In this case, the results are not checked and the pointer is passed as
an argument to the next function. Within that function it will only set a
variable (alias) if that ptr is not NULL. This means that should the malloc
call fail the address will be whatever was on the stack.

Since the malloc is user controlled it is pretty easy to make it fail, just
pass a size too large for the threshold. In this case just a simple -1 will do.

## Exploitation

The application is straight-forward to exploit but the trick is the player must
not write the buffer from a low to high address, instead they should look to
write into a lower address (future stack frame) and then they will
achieve the ability to write anywhere.

```
 +---------------------------------+
 |  future work() frame            |
 |                                 |
 |  +-----------------+            |
 |  | ptr: 0x58585858 |            | <----------<
 |  +-----------------+            |            |
 +---------------------------------+            |
    +-----------------+                         |
    | return addr     |  <-- reached            |
    +-----------------+                         |
 +---------------------------------+            |
 |  main() frame                   |            |
 |                                 |            |
 |  +-----------------+            |            |
 |  | buffer...       |  <----+    | O          |
 |  +-----------------+       |    | |          |
 |  ...                       |    | |          |
 |  +-----------------+       |    | |          |
 |  | ptr             |  -----+    | v----------^
 |  +-----------------+            |
 |  ...                            |
 +---------------------------------+
 +-----------------+
 | return addr     |  <-- never reached
 +-----------------+
```

## Hints

There are a few hints provided in the binary in order to make it easy to figure
out how to chain the two issues. Both of those hints will be in the form of
stack alignment, the idea is that the player will wonder why and the answer will
lead them to the final exploitation.
