# IDE Setup - Visual Studio Code

This guide will help you set up **Visual Studio Code (VS Code)** for developing and debugging this project.

## 1. Install Visual Studio Code

Download and install VS Code from:  
[https://code.visualstudio.com/Download](https://code.visualstudio.com/Download)

---

## 2. Install Required Extensions

Open the Extensions panel (`Ctrl+Shift+X`) and install:

- **C/C++** (by Microsoft) – IntelliSense, debugging, and code browsing.
- **CMake Tools** – For configuring, building, and debugging CMake-based projects.
- **Dev Containers** *(optional)* – For working in a pre-configured containerized environment.
- **CodeLLDB** or **Microsoft C/C++ Debugger** – For debugging support.

---

## 3. Clone the Repository

Open a terminal and run:

```bash
git clone https://github.com/goatshriek/stumpless.git
cd stumpless
```

---

## 4. Open the Project in VS Code

From VS Code:
1. Click **File → Open Folder…**
2. Select the cloned repository folder.

---
## 5. Build, Clean, and Rebuild (VS Code)

This project includes predefined VS Code tasks for building, cleaning, and rebuilding.

#### Build the project
1. Press **Ctrl+Shift+B**.
2. Select **Build (Preset Auto)** from the list.

#### Clean the project
1. Press **Ctrl+Shift+B**.
2. Select **Clean (Preset Auto)**.
   - This will delete the entire `build` directory.

#### Clean & Rebuild the project
1. Press **Ctrl+Shift+B**.
2. Select **Clean & Rebuild**.
   - This will first delete the `build` directory and then run the build again automatically.

---

## 6. Building and Running Examples

This project includes example programs such as `basic_example`.  
To enable them, configure CMake with the `STUMPLESS_BUILD_EXAMPLES` option:

### Enable Examples

By default, example programs are **not** built.  
To enable them, you have two options:

1. **Enable via CMake command:**
```bash
cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug -DSTUMPLESS_BUILD_EXAMPLES=ON
```

2. **Enable via CMakeLists.txt:**  
Open the main `CMakeLists.txt` file and change:
```cmake
option(STUMPLESS_BUILD_EXAMPLES "Build example programs" OFF)
```
to:
```cmake
option(STUMPLESS_BUILD_EXAMPLES "Build example programs" ON)
```

### Build example
```bash
cmake --build build/Debug --target basic_example
```

### Run example
```bash
./build/Debug/basic_example
```
> This will create an `example.log` file in the current directory containing the log output.

### Disable examples
```bash
cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug -DSTUMPLESS_BUILD_EXAMPLES=OFF
```

---

## 7. Tips

- Use `.vscode/settings.json` to store workspace-specific settings.
- Use `.vscode/c_cpp_properties.json` to configure IntelliSense include paths.
- Use `.vscode/launch.json` to store debugging configurations.
- Use `.vscode/tasks.json` for custom build commands.

---

## 8. Troubleshooting

- **CMake not found**: Ensure CMake is installed and added to your system PATH.
- **Compiler not found**: Install GCC/Clang or Visual Studio Build Tools.
- **Debugger errors**: Check that `gdb` or `lldb` is installed.
- **Example not building**: Make sure `STUMPLESS_BUILD_EXAMPLES=ON` when running CMake.

---

**Now you’re ready to code, build, and debug the project in VS Code!**
