# Chall 12 (Episode 7c - Speedrun Edition)

## Challenge

The player can read or write any file on the system that they have valid
permissions for. There is no specific vulnerability (although there is
some buggy handling of read values, they are not specifically security
bugs).

It is a rather open ended challenge as there are a few ways to do the
challenge (although a file called `.ssh` that has been marked as immutable
to avoid planting of `.ssh` keys just in case the SSH port associated with
the IP is the same as on the docker container).

Ideally they would just acquire leaks from `/proc/self/maps` and write some
injected code/data using `/proc/self/mem`.

## Protections

```
Arch:     amd64-64-little
RELRO:    Full RELRO
Stack:    Canary found
NX:       NX enabled
PIE:      PIE enabled
```
