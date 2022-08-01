# QRona

![QRona](img/qrona.png?raw=true)

## Description

This is a simple stack based buffer overflow but the `main()` function
never returns. The purpose of the challenge is to receive a `base64`
encoded image and then `zbarimg` is run on it. The results are output
via `stdout`.

[ptrYudai](https://twitter.com/ptrYudai) was kind enough to honour this challenge in his [best pwnables of 2021](https://ptr-yudai.hatenablog.com/entry/2021/12/06/001931#qrona---%E5%89%B5%E9%80%A0%E5%8A%9B%E8%B3%9E)
list where it received the "creativity award".

## Exploitation

You can exploit with the script in `solution/solve.py` it will run
with `HOST=localhost` and `PORT=1337` by default but if you provide
the argument `local` it will launch locally. Use the argument `debug`
to attach to a debugger.

If the first argument is not `local` or `debug` it will use that as
the host, and likewise for the second argument for the port.

**example usage (remote):**
```bash
$ ./solution/solve.py localhost 1337
[+] Opening connection to localhost on port 1337: Done
[*] leak: 0x7ffd4560e240
[*] envp: 0x7ffd4560e7d8
[*] file: /tmp/covid-8aUH-S5Uqfc
[*] name: /tmp/covid-8aUH-

[+] shell: uid=999(ctf) gid=999(ctf) groups=999(ctf)
[*] Switching to interactive mode
$ cat flag
midnight{34sy_pWns_m4k3_p30pl3_h4ppY}
```

**example usage (local):**
```bash
$ ./solution/solve.py local
[+] Starting local process './docker/files/qrona': pid 3329905
[*] leak: 0x7ffe4ff9eb90
[*] envp: 0x7ffe4ff9f128
[*] file: /tmp/covid-TfHK-KKvdj1
[*] name: /tmp/covid-TfHK-

[+] shell: uid=1000(user) gid=1000(user) groups=1000(user)
[*] Switching to interactive mode
```

The exploit is simple, first it uses the fact the buffer is printed
when the `base64` fails in order to acquire a stack leak, this will
be used later.

Then the player needs to flip a `debug` switch in order to
leak the tmp file name, this will allow them to overwrite this data
in such a way as to pass sanity checks but not have their tmp file
deleted after a run.

Once they have done that, they can make sure the data in this file
is an `ELF shared library`. This will be used for the final step.

Finally, they can overwrite the `envp` array on the stack, so it
will include the string `LD_PRELOAD=/path/to/lib` so they can have
a shell popped when `zbarimg` runs.

## Building

In order to build, just move into the `src` folder and type `make`,
this will generate an executable file.

## Docker

In order to get the dockerised version up and running just move into
the `docker` folder and type the following command:

```bash
docker-compose up --build -d
```

## Distribution

The only file intended to be provided to the player is the `qrona`
challenge binary which has been archived in `dist/qrona.tar.gz`.

## Author

b0bb
