# HSuite

v4 Status: Working on new features.
please ignore the cmake stuff its only for testing purposes.

A comprehensive C++ utility library providing elegant solutions for common programming tasks, from fancy terminal output to LLM integration.

## 📦 Installation

1. Download the repository as a ZIP file or get the latest version from the [Releases](../../releases) tab

2. Extract the `hsuite` folder to your project directory

3. Include the headers you need in your C++ files:
   ```cpp
   #include "hsuite/fancyprint.h"
   #include "hsuite/cllama.h"
   #include "hsuite/stb.h"
   #include "hsuite/typesuite.h"
   ```

## 🎯 Features

### FancyPrint
Beautiful terminal output with ANSI colors and interactive elements:
- Colored logging (info, warning, error, success)
- User input prompts
- Selection menus
- Confirmation dialogs
- Loading animations
- Countdown timers
- ASCII graphs
- Math expression display

```cpp
FancyPrint::Print_info("Starting application...");
FancyPrint::Print_success("Operation completed!");
int choice = FancyPrint::Print_selection(options, 3);
bool confirmed = FancyPrint::Print_confirm("Continue?");
```

### CLLama
Simple integration with Ollama for local LLM interactions:
- Query any Ollama model
- List installed models
- Install new models
- Get responses directly or print to console

```cpp
CLLama::prompt("Hello, how are you?", "llama2");
string response = CLLama::promptReturn("Explain AI", "llama2");
string models = CLLama::listModels();
```

### STB (Simple Text Buffer)
Cross-platform console input handling:
- Key-by-key text capture
- Integer input with validation
- Backspace support
- Works on Windows and Unix-like systems

```cpp
string input = STB::getText();
int number = STB::getNumber();
STB::printText("Hello World!");
```

### TypeSuite
Extended data types for advanced operations:
- **InfInt**: Arbitrary precision integers
- **Vertex**: 2D/3D points with distance calculations
- **Matrix**: Matrix operations and transpose
- **Range**: Python-style range iteration
- **Timer**: High-resolution timing
- **Cmd**: Execute shell commands and capture output

```cpp
InfInt big("123456789012345678901234567890");
Vertex<double> point(1.0, 2.0, 3.0);
Matrix m(3, 3);
for (int i : Range(10)) { /* ... */ }
Timer t; t.start(); /* code */ long long ms = t.elapsed_ms();
string output = Cmd::run("ls -la");
```

## 📝 Example Usage

### Simple Chatbot
```cpp
#include "hsuite/cllama.h"
#include "hsuite/stb.h"

int main() {
    while (true) {
        string model = "llama2";
        FancyPrint::Print_info("You: ");
        string user_input = STB::getText();
        
        if (user_input == "exit" || user_input == "quit") {
            break;
        }
        
        CLLama::prompt(user_input, model);
    }
    return 0;
}
```

### Interactive Menu
```cpp
#include "hsuite/fancyprint.h"

int main() {
    FancyPrint fp;
    fp.Print_delimiter("Main Menu");
    
    const string options[] = {"Start Game", "Settings", "Exit"};
    int choice = fp.Print_selection(options, 3);
    
    fp.Print_success("You selected option " + to_string(choice));
    return 0;
}
```

## 🔧 Requirements

- C++17 or higher
- For CLLama: [Ollama](https://ollama.ai/) installed and running
- Cross-platform: Works on Windows, Linux, and macOS

## 📊 Version Status

**v3 Status**: Testing & Finishing Up 🚧

## 🤝 Contributing

Contributions are welcome! Feel free to submit issues and pull requests.

## 📄 License

GPL-v3

## 🔗 Links

- [Releases](../../releases) - Download the latest version
- [Issues](../../issues) - Report bugs or request features

---

Made with ❤️ for the C++ community
