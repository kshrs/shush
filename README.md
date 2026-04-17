# shush - a shell

**shush** is a simple shell written in C.

## Code Structure

```text
shush
 |--build/      -> This is where the binary goes after make.
 |--include/
     |--shell.h
     |--exec.h
     |--builtins.h
 |--shell.c     -> Main shell rules and function calls.
 |--exec.c      -> Definitions of exec functions.
 |--builtins.c  -> Definitions of builtin functions.
 |--Makefile
 |--LICENSE
 |--README.md   -> You are here.
```

## How to run?

```bash
# clone the project
git clone https://github.com/kshrs/shush.git

# move into the directory
cd shush

# build the binary
make 

# run the program
cd build/
./shush

# (or)
./build/shush
```

## Chores

1. Implement Environment variable setup.
2. Alias Feature.
3. Some more builtin commands.
4. Handle keyboard events.

---

yeah! that's it, it's simple right?
