# Chall 08

## Description

The vulnerability is a simple stack based buffer overflow where the buffer is
written byte by byte according to an index variable `i`. Since `i` is stored
after the buffer, after `1024` bytes the attacker will be able to write over
the LSByte of the index, this allows them to skip over the stack canary in
order to control the flow of the application (though the stored return address).

Although all of that is simple enough, that is where the real problem begins.
The premis of this challenge is to showcase a set of techniques that are useful
when a leak and second payload are required to successfully pop a shell but
there is no easy access to direct input and output functions such as `puts`,
`printf`, `read`, `write` etc.

All input and output in the binary is done through the `f*()` family of
functions that expect a valid `FILE *` as an argument. Since it is a 64 bit
binary with ASLR, this makes the `stdin` and `stdout` file pointers effectively
unpredictable. In addition to these limitations, one cannot expect to simply
jump into the middle of some function to supply a different buffer to some call
to `fwrite` as `stdin` and `stdout` are dereferenced from `.data` and that
happens before any other function arguments are placed into registers. Even if
you could jump into the middle of a function in order to obtain a valid leak,
you would have the additional burden of having to pass the stack canary check
at the end of that function (the same stack canary that was not setup due to
the fact the attacker jumped into the middle of a function).

## Note

The only artificial addition to the binary is the clearing of registers before
returning from `main()`. This is not to make things trickier, but rather to not
confuse the players as there is a rather interesting behavioural difference with
this kind of binary that is buffered both at the kernel level as well as libc
when served over `xinetd`. Once a buffer is soley managed by libc as opposed to
the kernel, then the `xinetd` buffering can alter the order of operations in
the `IO` jump table.

This has the effect of making the values in volatile and regular registers less
consistent with local runs and so the players might have a dangling `FILE *`
reference in a register locally but they will be confused when this is not the
case remotely. So by clearing the possible locations for a `FILE *` reference
after `IO` jumps we can ensure the players will not attempt to waste time
building payloads around these values.

## Exploitation

There are a few ways to deal with this kind of problems (some more esoteric
than others) but I will limit myself to explaining the simplest and most
general method (in my opinion) that is quite simple, although some people may
not be familiar or have never independently arrived at the same conclusion
(because there are other methods).

The idea is quite simple, do a partial pivot (using `rbp`) to a known memory
location. Since all local variables are positioned relative to `rbp` (by
default), it will be possible to shuffle certain useful values on the fake
stack. Once we have the data we need  (to perform a libc ID), then we can
read/write a useful payload.

So the idea is to use the fake stack to generate real unguessable values
(like a stack canary or `stdout FILE *`) and then build a ropchain around
them, being careful to not damage the uninitialised values over several runs
(restarting the binary).

Keep in mind that the `FILE *` will be line buffered by default, so any leaks
that do not contain whitespace that forces a flush (like `\n` and `\r`) will
require a `fflush(fp)` call.
