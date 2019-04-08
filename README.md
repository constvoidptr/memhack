# Memhack

Memhack is a **easy to use** memory hacking library with a multi-plattform design.

Simple example without error checking.
```C
// Variable that will hold the score, opaque pointer to the mh_process struct
int score = 0;
struct mh_process *process = NULL;

// Attach to the target process, sets the mh_process pointer
mh_process_attach(&process, "example.exe");

// Read out the current score, add 100 and write the new value back into process memory
mh_memory_read(process, (void *) 0x0618C0DC, &score, sizeof (score));
score += 100;
mh_memory_write(process, &score, (void *) 0x0618C0DC, sizeof (score));

// Detach from the process again
mh_process_detach(process);
```

## Features

* Easy to use, consistent library function calls
* Designed with multi-plattform support in mind
* Static and dynamic library available
* Library is written in C and is therefor compatible with every language that
  provides C bindings
* Read from process memory
* Write to process memory

With a lot more to come...

## Usage

Code examples will follow...

## Installation

### Windows

Under Windows Visual Studio is required to compile the code.

`git clone https://github.com/constvoidptr/memhack.git`

Open the Visual Studio Solution under `project/memhack.sln`

## License

Memhack is published under the Zlib license. See the full license
[here](https://github.com/constvoidptr/memhack/blob/master/LICENSE).
