# Chall 10 (Episode 7a - Speedrun Edition)

## Challenge

A standard stack based buffer overflow challenge on a x86_64 binary. The intended method
for solving is to build a ROP chain in order to leak and read in a second payload in order
to run something.

## Protections

```
Arch:     amd64-64-little
RELRO:    Partial RELRO
Stack:    No canary found
NX:       NX enabled
PIE:      No PIE (0x400000)
```
