# Data Structures and Algorithms in C

> ⚠️ This project is under development!

This project provides code examples for various **data structures and algorithms** in C90 (ANSI C) with a focus on correctness, safety, and simplicity.

## 🧪 List

### 🧩 Data Structures

| File | Data Structure | Description |
| ---- | -------------- | ----------- |
| [`simple_bst.c`](./simple_bst.c) | Binary Searcy Tree (BST) | Basic, unbalanced tree |
| [`avl_tree.c`](./avl_tree.c) | AVL Tree | Search and Delete operations are unimplemented |

### 🥜 Sorting Algorithms

| File | Algorithm | Description | Recursive | Buffer-based |
| ---- | --------- | ----------- | --------- | ------------ |
| [`merge_sort.c`](./merge_sort.c) | Merge Sort | Top-down | Yes | Yes (buffer-based merging) |
| [`tree_sort.c`](./tree_sort.c) | Tree Sort | Simple BST | Yes | Yes (BST) |
| [`tree_sort_no_recursion.c`](./tree_sort_no_recursion.c) | Tree Sort | Simple BST | **No** | Yes (BST and stacks) |

## 📑 Usage

Just copy the code into existing code bases and refactor it a bit to fit your preferences. The code is short and doing that should be easy for any programmers.

The sorted element type is `int` in the examples, but those can easily be used for any comparable types.

## 👟 Build Guide

<details>
<summary>🪟 Windows</summary>

In case you need something to run out-of-the-box, you can follow the instruction in this section. 

> ⚠️ This project’s Makefile uses Windows shell commands. It will **not work on Unix/Linux/macOS** without modification. Efforts for cross-platform compatibility is in progress.

### 📦 Installation (on Windows)

1. Install [Scoop](https://scoop.sh/) if you haven't already.
2. Install `make` and `gcc`:

```bash
scoop install make gcc
```

3. Clone this repository and `cd` into it.
4. Use `make` (see below) to build and run.

### 🛠️ Building

To build all sorting executables:

```bash
make
```

Each `.c` file in the project will produce a corresponding binary in `build/bin/`.

### ▶️ Running

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

### 🧹 Cleaning

To clean all build artifacts:

```bash
make clean
```

This will remove the entire `build/` directory, including binaries and object files.
</details>

## 🚀 Planned Features

* [ ] Ensure portability for Makefile (not just working on Windows)
* [x] Merge Sort
* [x] Tree Sort
  * [x] Using simple BST
  * [ ] Using red-black tree
* [ ] Quicksort
* [ ] Heap **Sort**
* [ ] Insertion Sort
* [ ] Bubble Sort
* [ ] Shell Sort
* [ ] Unit tests for correctness
* [ ] Benchmarking mode

## 📋 License

This project is provided under the [Creative Commons Zero v1.0 Universal](./LICENSE), i.e. this work is under world-wide *public domain*.
