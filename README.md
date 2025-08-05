# Sorting Algorithms in C

This project implements various **sorting algorithms** in ANSI C (`-std=c90`) with a focus on correctness, safety, and simplicity. Currently, it includes:

* ✅ `merge_sort.c` – Merge Sort (Top-down, Recursive, with buffer-based merging)

Additional algorithms will be added in separate source files, each independently buildable and runnable via `make`.

## 📁 Project Structure

```text
.
├── merge_sort.c        # Implementation of merge sort
├── Makefile            # Build system
├── README.md           # Project documentation
└── build/              # (auto-created) Compiled binaries and objects
    ├── bin/            # Final executables
    └── obj/            # Intermediate object files
```

## 📦 Installation (on Windows)

1. Install [Scoop](https://scoop.sh/) if you haven't already.
2. Install `make` and `gcc`:

```bash
scoop install make gcc
```

3. Clone this repository and `cd` into it.
4. Use `make` (see below) to build and run.


## 🛠️ Building

> ⚠️ This project’s `Makefile` uses Windows shell commands (`mkdir`, `rmdir`, `del`) and assumes `make` is installed natively on Windows (e.g., via [Scoop](https://scoop.sh/)).
> 
> It will **not work on Unix/Linux/macOS** without modification.
> 

To build all sorting executables:

```bash
make
```

Each `.c` file in the project will produce a corresponding binary in `build/bin/`.

## ▶️ Running

You can run a sorting program like this:

```bash
make run NAME=merge_sort ARGS="5 1212 33 3 -1 0"
```

This runs the compiled binary `build/bin/merge_sort` with the following input:

* First argument: number of elements (`5`)
* Next arguments: array elements (`1212 33 3 -1 0`)

**Output:**

```
-1 0 3 33 1212
```

## 🧹 Cleaning

To clean all build artifacts:

```bash
make clean
```

This will remove the entire `build/` directory, including binaries and object files.

## 🚀 Planned Features

* [ ] Ensure portability (not just working on Windows)
* [x] Merge Sort
* [ ] Quick Sort
* [ ] Heap Sort
* [ ] Insertion Sort
* [ ] Bubble Sort
* [ ] Shell Sort
* [ ] Unit tests for correctness
* [ ] Benchmarking mode

## 📋 License

This project is provided under the [**MIT License**](./LICENSE). You are free to use, modify, and distribute it.
