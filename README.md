# randpw — Secure Random Password Generator in C

`randpw` is a simple and secure command-line tool for generating high-entropy, cryptographically strong passwords using the Linux kernel’s `getrandom()` syscall. Built in C with no external dependencies, it ensures reliability and speed while minimizing bias in password generation.

## 🔐 Features
- 📏 Customizable password length (8–999 characters)
- 🔁 16-bit entropy per character (bias-minimized)
- 🔒 Uses `/dev/urandom` via `getrandom()` syscall
- ⚡ Extremely fast and dependency-free
- 🧬 High-entropy character set (includes special characters)

## Usage/Example
```bash
$ randpw
dN7jL#iCpwFt-Q9yMkZA5B?fuwvGeLhO
$ randpw -n 64
fQAKGL4F_1OJyA4epw4ZjD1nW9BFAg3UWEboVQ1LbeM6bn2NSoPi5-rqbpZJ9e#X
$ randpw --help
A simple and secure command-line tool for generating random, high-entropy passwords using /dev/urandom.
Usage: randpw [option]

Options:
    -h, --help         print randpw command line options (currently set)
    -v, --version      print randpw version
    -n, --length       length of the generated password (default: 32)
```
## Installation
Clone the repository:
```bash
git clone https://github.com/pr00x/randpw.git
cd randpw
```

Build and install the binary:
```bash
sudo make install
```

## Uninstallation
To remove the installed binary, run:
```Bash
sudo make uninstall
```

To remove the compiled binary file from the source directory, run:
```Bash
sudo make clean
```

Uninstall and clean in one command:
```Bash
sudo make clean uninstall
```

## 🔐 Security Considerations
- Uses `getrandom()` instead of reading from `/dev/urandom` manually, ensuring no file descriptors or blocking.
- Employs **16-bit entropy per character** to minimize modulo bias.

## 🧠 How It Works

1. The program requests `2 * n` bytes from `getrandom()`, where `n` is the desired password length.
2. For each password character, it consumes 16 bits (2 bytes) to get a high-entropy number.
3. That number is mapped to a character in the allowed charset via modulo operation.
4. The password is printed to standard output.

## Author
[@prox](https://www.github.com/pr00x)

## Contributing
Contributions are welcome! Please create a pull request or submit an issue for any feature requests or bug reports.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.