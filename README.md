# CPPLogger

A modern C++ logging library with console and file output support, featuring multiple log levels, colored console output, and template-based message formatting.

## Features

- **Multiple Log Levels**: Debug, Info, Warning, Error, and Fatal
- **Console Output**: Color-coded console logging with customizable colors
- **File Logging**: Optional file output with timestamp support
- **Timed Copies**: Automatically create timestamped backup copies of log files
- **Template-Based Formatting**: Uses C++20 `std::format` for type-safe string formatting
- **Configurable Filtering**: Set different minimum log levels for console and file output
- **Static API**: Simple, global logger interface

## Requirements

- **C++ Standard**: C++20 or later
- **CMake**: Version 3.10 or later
- **Compiler**: MSVC 2019 or later (or compatible C++20 compiler)

## Building

### Prerequisites

Ensure you have CMake and a compatible C++ compiler installed on your system.

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Release
```

### Build Options

- **CPPLogger_SHARED**: Set to `ON` to build as a shared library (default: `OFF` for static library)

```bash
cmake .. -DCPPLogger_SHARED=ON
```

## Usage

### Basic Setup

```cpp
#include "Logger.hpp"

using namespace TachiTools::Logger;

int main()
{
    // Setup logger with default settings
    Logger::setup();
    
    // Setup with custom parameters
    Logger::setup(
        Level::Debug,           // Minimum console print level
        Level::Warning,         // Minimum file output level
        true,                   // Enable file output
        "myapp.log",            // Log file name
        true,                   // Save timed copy
        false                   // Don't override file
    );
    
    return 0;
}
```

### Logging Messages

#### Simple Messages
```cpp
Logger::logSimple(Logger::Level::Info, "Application started");
Logger::logSimple(Logger::Level::Error, "An error occurred");
```

#### Formatted Messages
```cpp
Logger::log(Logger::Level::Info, "User {} logged in", "john_doe");
Logger::log(Logger::Level::Warning, "Memory usage: {} MB / {} MB", 512, 1024);
Logger::log(Logger::Level::Error, "Failed to open file: {}", filename);
```

### Log Levels

- **Debug**: Detailed information for diagnostic purposes
- **Info**: General informational messages
- **Warning**: Warning messages for potentially problematic situations
- **Error**: Error messages for error events
- **Fatal**: Fatal error messages

### Console Colors

The logger supports the following console colors:
- Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Reset

## Project Structure

```
CPPLogger/
├── CMakeLists.txt              # Root CMake configuration
├── CPPLogger/
│   ├── CMakeLists.txt          # Library CMake configuration
│   ├── include/
│   │   └── Logger.hpp          # Main logger header
│   └── src/
│       ├── Logger.cpp          # Logger implementation
│       ├── StringHelp.cpp      # String utility implementation
│       └── StringHelp.hpp      # String helper header
├── build/                       # Build artifacts (generated)
└── README.md                    # This file
```

## API Reference

### Logger::setup()

Initialize the logger with custom configuration.

```cpp
static void setup(
    const Level minimumPrintLevel = Level::Info,
    const Level minimumFileLevel = Level::Warning,
    const bool printToFile = false,
    const std::string fileName = "",
    const bool saveTimedCopy = true,
    const bool overrideFile = true
);
```

**Parameters:**
- `minimumPrintLevel`: Minimum level for console output
- `minimumFileLevel`: Minimum level for file output
- `printToFile`: Enable/disable file logging
- `fileName`: Name of the log file
- `saveTimedCopy`: Create timestamped backup copies
- `overrideFile`: Whether to override existing log file

### Logger::log()

Log a formatted message (variadic template).

```cpp
template<typename ... Args>
static void log(
    const Logger::Level level,
    const std::string_view message,
    Args&& ... args
);
```

### Logger::logSimple()

Log a simple message without formatting.

```cpp
static void logSimple(
    const Level level,
    const std::string_view message
);
```

## Example Application

```cpp
#include "Logger.hpp"

using namespace TachiTools::Logger;

int main()
{
    Logger::setup(
        Level::Debug,
        Level::Info,
        true,
        "application.log"
    );
    
    Logger::log(Level::Info, "Application version: {}", "1.0.0");
    Logger::log(Level::Debug, "Starting initialization...");
    
    try {
        Logger::log(Level::Info, "Processing file: {}", "data.txt");
    } catch (const std::exception& e) {
        Logger::log(Level::Error, "Exception occurred: {}", e.what());
    }
    
    Logger::log(Level::Info, "Application shutting down");
    
    return 0;
}
```

## License

This project is licensed under the MPL 2.0 license.
See the LICENSE file for details.

## Contributing

Contributions are welcome.

Before submitting a pull request:

- Follow the existing code style.
- Keep public API changes documented.
- Update documentation when necessary.
- Ensure the project builds successfully.

By contributing, you agree that your contributions may be distributed under the project's license.

## Author

Tachi
