# Getting Started on Windows (MSYS2/MinGW64 + CMake + Ninja)

This Quick Start shows a **tested working path** to build *stumpless* on Windows using **MSYS2/MinGW64**, then compile & run a minimal example.

> This guide was validated on Windows 10 with MSYS2, GCC 15.2, CMake 4.1, Ninja 1.13. Versions may differ slightly on your machine.

---

## 1) Install MSYS2

**Option A (winget):**

```powershell
winget install -e --id MSYS2.MSYS2
```

**Option B (manual):**
Download from [https://www.msys2.org/](https://www.msys2.org/) and install to the default `C:\msys64`.

---

## 2) Open the **correct shell** (MINGW64)

Use **Start Menu → MSYS2 MinGW 64-bit** (not “MSYS” and not Git Bash).

Verify:

```sh
echo $MSYSTEM
# Expect: MINGW64
```
---

## 3) Update MSYS2

First full update (may ask you to close the window):

```sh
pacman -Syu
```

If asked, **close** the shell, then reopen **MSYS2 MinGW 64-bit** and run:

```sh
pacman -Su
```

---

## 4) Install build tools

```sh
pacman -S --needed \
  mingw-w64-x86_64-gcc \
  mingw-w64-x86_64-cmake \
  mingw-w64-x86_64-ninja \
  git
```

Verify tools:

```sh
which gcc && gcc --version
which cmake && cmake --version
which ninja && ninja --version
# Paths should be under /mingw64/bin
```

---

## 5) Get the source (fork optional)

```sh
# Clone your fork (recommended) or the upstream repo
git clone https://github.com/<your-username>/stumpless.git
cd stumpless

```

---

## 6) Configure (CMake + Ninja)

Create a clean build directory and configure **Release**:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

If configuration reports missing optional components (e.g., journald/sqlite/socket targets) or you want a quieter config on Windows, you can explicitly disable them:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_SQLITE3_TARGETS=OFF \
  -DENABLE_JOURNALD_TARGETS=OFF
```

---

## 7) Build

```sh
cmake --build build -j 8
```

Expected artifacts include:

* `build/stumpless.dll`  (the runtime DLL)
* `build/libstumpless.dll.a`  (import library for linking)

---

## 8) (Optional) Run tests

```sh
ctest --test-dir build -j 8
```

---

## 9) Sanity check: compile the bundled example

Use the example already in the repo to confirm headers & linking.

```sh
# from repo root, after a successful CMake build
cp -f build/stumpless.dll .    # ensure the DLL is alongside the exe at runtime

# Try A: link by name
gcc -I include -I build/include docs/examples/basic/basic_example.c \
    -L build -lstumpless -lws2_32 -o basic_example.exe

# Or B: link using the exact import lib (if A says "cannot find -lstumpless")
# gcc -I include -I build/include docs/examples/basic/basic_example.c \
#     build/libstumpless.dll.a -lws2_32 -o basic_example.exe

# Run
./basic_example.exe
```
---

## Troubleshooting

* **`pacman: command not found`** → You are not in an MSYS2 shell. Open **MSYS2 MinGW 64-bit**.
* **`echo $MSYSTEM` prints `MSYS`** → Wrong shell. Use **MINGW64** (or `exec /usr/bin/env MSYSTEM=MINGW64 /usr/bin/bash --login`).
* **`fatal error: stumpless/config.h: No such file or directory`** → Add generated headers path: `-I build/include`.
* **`cannot find -lstumpless`** → Link with the exact import lib: `build/libstumpless.dll.a`.
* **Winsock undefined refs (e.g., `closesocket`)** → Add `-lws2_32` to your gcc link command.
* **Runtime error: DLL not found** → Ensure `stumpless.dll` is alongside your `exe` (or add `build` to `PATH`).
* **Doxygen/journald/sqlite/socket messages during configure** → These are optional; safe to ignore on Windows.

---