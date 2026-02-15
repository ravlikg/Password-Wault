# PassLocker-CPP 🔐

A lightweight command-line password manager built with modern C++. This project demonstrates core Object-Oriented Programming principles, clean architecture, and encrypted data persistence.

## Features

- **CRUD Operations** - Create, read, update, and delete password entries
- **XOR Encryption** - Simple encryption via an extensible `ICipher` interface
- **File Persistence** - Automatic synchronization with encrypted local storage
- **Hex Encoding** - Prevents data corruption from special characters
- **Modern C++** - Uses C++17 features and STL best practices

## Architecture

The project follows a modular design:

- **Interface-Based Encryption** - `ICipher` abstraction allows easy algorithm swapping
- **Smart Pointers** - `std::unique_ptr` for safe resource management
- **STL Containers** - `std::vector` and lambda expressions for data handling

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- CMake 3.10 or higher

### Building

```bash
git clone https://github.com/ravlikg/Password-Wault.git
mkdir build && cd build
cmake ..
make
```

### Running

```bash
./pass_manager
```

## Security Note

This is an educational project demonstrating C++ programming concepts. The XOR encryption used here is **not suitable for production use**. For real password management, use established tools like KeePass or Bitwarden.

## Technologies

- C++17
- CMake
- Standard Template Library (STL)

## License

MIT License - see [LICENSE](LICENSE) for details.
