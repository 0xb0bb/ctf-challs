# Chall 03

## Description

A simple buffer overflow with a slightly tricky landing where some prior
knowledge about x86 segmentation and modes as well as ABI's will give an
advantage. The problem can be solved dynamically or statically (or both)
and there are a few tricky parts but nothing too painful.

There is a custom weak stack canary implementation to bypass which adds a
slight random factor to keep things interesting.

## Exploitation

The general idea is that you can bounce between `x64` and `x32` modes in
order to gain a shell gradually.

The simplest way to do this is the following:

  1. Provide a canary seed that can be used later (stored in a known location in `.bss`).
  2. Perform a buffer overflow that will point the return address to the `x86` gadgets in the `BuildID` (`mov esp, ebx; aaa; int 0x80; retf`). The interesting thing about this gadget chain is not just that it shows the trick of using the `BuildID` for occassional gadgets but that the chain has the `aaa` instruction which is not valid on x64 and will show as `*bad*` in tools and also cause a `#UD` exception in x64 mode. The idea is to pivot `esp` to .bss where the previous canary seed was written and use that to change the execution mode back to `x64` and restart the application.
  3. Now the stack is pivoted, run the application again in order to lay data down for later since the size of the input becomes the syscall number to use in x32 mode there will not be enough room to have a full SROP payload for `SYS_sigreturn` on `x32` (`0x77`).
  4. Restart the application yet again in `x64` mode and this time write the SROP payload and perform the SROP to gain control over registers.
  5. The SROP can be tricky with switching modes due to some segment registers being trashed until a context switch, but the idea is to get a quick `execve("/bin/sh", NULL, NULL)` but with some approaches another run may be required to correct the segmentation problem.

## Hints

  If there are hints provided I would imagine they would be:

    1. `BuildID`
