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
     |--color.h
     |--prompt.h
     |--alias.h
 |--shell.c     -> Main shell rules and function calls.
 |--exec.c      -> Definitions of exec functions.
 |--builtins.c  -> Definitions of builtin functions.
 |--prompt.c    -> Prompt Handling and Configuration.*
 |--alias.c     -> Alias Handling and Configuration.*
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
2. Some more builtin commands.
3. Handle keyboard events.
4. Bug: Ignorance of extra arguments during the usage of alias.

---

yeah! that's it, it's simple right?
