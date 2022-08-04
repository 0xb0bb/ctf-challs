# Chall 11 (Episode 7b - Speedrun Edition)

## Challenge

A format string attack with an `exit()` call right after the format string is
printed to the user. Obviously the idea is to overwrite the `exit()` pointer
in the GOT much like `.dtors` writes, however there are many things that can
be after that step, each with benefits and detriments.

The reference exploit is crafted for stability, it will put the program in a
loop by restarting it (pointing `exit()` to `main()`) and then write over
`__malloc_hook` after leaking libc. Another method was tested for speed where
`exit()` could be overwritten with a one shot gadget (after leaking and
restarting). This works because you can control `eax` which is the key
requirement for the gadget that was the most stable.

## Protections

```
Arch:     i386-32-little
RELRO:    Partial RELRO
Stack:    Canary found
NX:       NX enabled
PIE:      No PIE (0x8048000)
```
