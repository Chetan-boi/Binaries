# binaries

A personal collection of minimal developer tools, scaffolding utilities, and scratch-built implementations of standard Unix core utilities in C++ and Rust.

## Tools & Utilities

### Scaffolding
* **`cnew`** — A minimal project scaffolder that sets up a standard modern C++ directory layout (`src/`, `include/`), a ready-to-build `CMakeLists.txt`

---

## Roadmap: Coreutils from Scratch

Step-by-step re-implementations of POSIX/Unix utilities to explore low-level systems programming, syscalls, and I/O mechanics:

- [ ] **`my-cat`** — Basic file reading, standard input concatenation, and unbuffered I/O.
- [ ] **`my-wc`** — Byte, word, and newline counting.
- [ ] **`my-head` / `my-tail`** — Buffer traversal and ring-buffer tracking for stream ends.
- [ ] **`my-ls`** — Directory traversal via filesystem APIs, file metadata parsing, and column formatting.
- [ ] **`my-grep`** — Pattern matching, stream scanning, and basic regex parsing.

---

## Building & Installation

### Prerequisites
* A C++20-compliant compiler (`clang++` or `g++`)
* CMake 3.10+
* Rust toolchain (`cargo`, `rustc`)

### Install to Path
Compile any binary and link it to your local binary path:

```bash
# Example: Build cnew
clang++ -std=c++20 cnew/src/main.cpp -o ~/.local/bin/cnew
