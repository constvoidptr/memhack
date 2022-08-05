# Memhack

Memhack is an **easy-to-use** and **cross-platform** memory hacking library
that strives to be **consistent** and **well documented**.

Simple example without error checking.
```C
// Variable that will hold the score, opaque pointer to the mh_process struct
int score = 0;
mh_process_t *process = NULL;

// Attach to the target process, sets the mh_process pointer
mh_process_attach_by_pid(&process, 28191);

// Read out the current score, add 100 and write the new value back into process memory
mh_memory_read(process, (void *) 0x0618C0DC, &score, sizeof (score));
score += 100;
mh_memory_write(process, &score, (void *) 0x0618C0DC, sizeof (score));

// Detach from the process again
mh_process_detach(process);
```

## Features

* Easy to use, consistent and well documented library calls
* Cross-platform with Windows and Linux officially supported. Easy to add
  support for a new platforms because the library was designed with
  multi-platform support in mind
* Static and dynamic linkage available
* Written in C and therefore, most likely, callable from your favourite
  programming language
* Read and write from/to another processes memory

With a lot more to come...

## Usage

Admin or Superuser privileges are required to run.

Code examples will follow...

## Compilation

### Windows

Under Windows Visual Studio is required to compile the code.

1. `git clone https://github.com/constvoidptr/memhack.git`
2. Open the project with the editor of your choice
3. Compile to a static or dynamic library using CMake

Alternatively, there are pre-built Windows binaries available.

### Linux

Building for Linux is done by gcc + make.

1. `git clone https://github.com/constvoidptr/memhack.git`
2. Change into the `project/` directory
3. Execute `make` to build the `all` target, or select another target of your
   choosing

## License

Memhack is published under the Zlib license. See the full license
[here](https://github.com/constvoidptr/memhack/blob/master/LICENSE).
