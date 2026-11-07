# minitalk

`minitalk` sends a string from a client process to a server process using the
Unix signals `SIGUSR1` and `SIGUSR2`. The server prints the decoded characters
and reports its process ID when it starts.

## Build

The Makefile links both programs with `libftprintf.a` and expects the
`ft_printf` project inside this directory. Fetch it before building:

```sh
git clone git@github.com:am1ne14/ft_printf.git ft_printf
make
```

This produces `server` and `client`.

## Run

Start the server in one terminal:

```sh
./server
```

Copy the PID it prints, then send a message from another terminal:

```sh
./client 12345 "Hello from minitalk"
```

Replace `12345` with the PID printed by your server.

## Signal encoding

The client sends each character as eight bits, most significant bit first.
`SIGUSR1` represents a one and `SIGUSR2` represents a zero. It sends a null
byte after the message so the receiver can recognize the end. There is a
500-microsecond pause between signals in the client.

The server installs `sigaction` handlers with `SA_SIGINFO`, so it can read the
sender PID from `siginfo_t`. It shifts each received bit into a byte and prints
the byte after eight signals. For every bit it also sends the received signal
back to the client; the client's signal handlers print whether that bit was
one or zero.
