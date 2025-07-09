<p align="center">
  <img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=32&duration=3000&pause=1000&color=00FFAA&center=true&vCenter=true&width=900&lines=Welcome+to+RohitOS+v0.1+%F0%9F%9A%80;A+16-bit+%2B+32-bit+Handcrafted+Operating+System;Made+with+C+%2B+Assembly+from+Scratch;No+LibC+-+No+STD+Libraries+-+Pure+Baremetal" alt="Typing SVG" />
</p>

---

# 🧠 RohitOS v0.1 — A Minimal Custom Operating System

> A fully handcrafted operating system from scratch in **C + Assembly**, booting with a custom bootloader, entering protected mode, and running a feature-rich CLI.

![Build with love](https://img.shields.io/badge/Built%20with-%E2%9D%A4-red?style=for-the-badge)
![Language](https://img.shields.io/badge/Written%20In-C%20%2B%20NASM-blue?style=for-the-badge)
![No LibC](https://img.shields.io/badge/Standard%20Library-None-red?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

---





## 📽️ Demo 

https://github.com/user-attachments/assets/f6dc31a4-a00f-4498-bc3c-66988119a2de

---

## 🧱 Project Structure
```
RohitOS/
├── bootloader.asm # 16-bit bootloader to load kernel
├── disk_load.asm # Sector loader (INT 13h)
├── gdt.asm # GDT for protected mode
├── kernel/
│ ├── kernel_entry.asm # Jump into 32-bit mode
│ ├── kernel.c # Core logic, splash, progress, init
│ ├── cli.c # Command parser + dispatcher
│ └── cli.h # CLI header
├── lib/
│ ├── stdio.c/.h # Custom print() and console I/O
│ └── string.c/.h # Basic string ops (no libc)
├── linker.ld # Custom linker script
├── Makefile # Complete build system
├── build/ # Compiled output binaries
└── README.md # This file 📄

```


---

## 🚀 Features

- 🔹 **Custom 16-bit bootloader**
- 🔹 **Protected mode (32-bit) kernel**
- 🔹 **Fully functional CLI shell**
- 🔹 **ASCII splash screen + loading bar**
- 🔹 **No libc** – all string/IO functions built manually
- 🔹 **System uptime tracking**
- 🔹 **Custom command parsing**
- 🔹 **Print with no standard output**
- 🔹 **Written in pure C and NASM**

---

## 🖥️ CLI Commands

| Command    | Description                        |
|------------|------------------------------------|
| `help`     | Show all commands                  |
| `clear`    | Clear the terminal screen          |
| `ver`      | Show OS version                    |
| `uptime`   | Show system uptime in seconds      |
| `date`     | Show kernel build date/time        |
| `whoami`   | Print the current user             |
| `sysinfo`  | Show system info summary           |
| `shutdown` | Halt execution (`hlt` loop)        |
| `echo`     | Print custom text                  |
| `calc`     | Add, subtract, multiply, divide    |
| `timer`    | Countdown timer                    |
| `hex`      | Convert decimal to hexadecimal     |
| `bin`      | Convert decimal to binary          |
| `fortune`  | Show a random coding quote         |

---

## 🧪 Build & Run Instructions

### 🛠 Requirements

- `nasm`
- `gcc` with 32-bit support (`-m32`)
- `ld`
- `QEMU` (or Bochs/VirtualBox for ISO testing)

### 🔨 Commands

```bash
make clean
make        # Assembles + compiles everything
make run    # Runs RohitOS in QEMU
```
---

# 🌟 Author
**Rohit Yadav
🎓 CS Undergrad @ NIT Jalandhar
👨‍💻 Systems Programmer | VM + Compiler Dev**

---

⭐ If you liked it — drop a star! <p align="center"> <img src="https://media.giphy.com/media/26tn33aiTi1jkl6H6/giphy.gif" width="300"> </p> 


