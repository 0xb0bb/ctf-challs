# Chall 13 (Episode 7d - Speedrun Edition)

## Challenge

This challenge has two methods to solve, one is fairly obvious but slower and
the other is much faster but might not immediately pop out to players.

There is a `buffer` on the stack and input is read to it. This input is then
formatted as part of a command that is passed to `system()`. The command has
single quotes to prevent trivial command injection, it is in the format of
`$PROG '%s'` where `$PROG` is set to `/bin/cat` and `%s` is where their input
will appear.

So the idea is the player will provide input for a filename in the current
directory and they will read the file. The characters `'`, `/`, `\`, `\n` and
`\r` are all filtered.

The vulnerability is a trivial stack based buffer overflow, however `main()`
never returns.

The two methods of exploitation are described below:

### Method 1 (Fast)

The general idea is to overwrite the `envp` pointer to `$PROG` so that the
string can be arbitrarily controlled in order to pop a shell.

This is done in two parts, first `main()` calls `input()` with the pointer
to the input buffer, this means the pointer is on the stack and can be
overwritten (to point to a known memory location) so the next time input is
read, it will not be on the stack, but rather at that known location.

This means not only can the command be written to that known location, but
also a fake ENV string like `PROG=sh -c` so the player can also overflow
the correct `envp` pointer to point to that string and get the easy shell.

### Method 2 (Slower)

Since there is a buffer overflow and a null terminator is not added to the
end of the input before it is passed to `snprintf()` to format the command,
the player can leak all the values on the stack in the error message `sh`
will spit out due to the file not existing.

So similarly to the above method, if the player controls the `buffer` pointer
by overwriting it and gets the right stack leaks, although `main()` never
returns, `input()` does, and so they can calculate the return address location
of `input()` before that function even runs and have `input()` write a ROP chain
to that location. Since it is 32bit, they don't need to do much except pass
a valid command string to `system()`.

## Protections

```
Arch:     i386-32-little
RELRO:    Full RELRO
Stack:    Canary found
NX:       NX enabled
PIE:      No PIE (0x8048000)
```