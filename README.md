# Sundown - LAN Shutdown Server


A lightweight Windows service application that allows scheduling and managing
system shutdowns over a local network (LAN).

The application exposes a simple TCP-based control interface and periodically
broadcasts its presence via UDP for device discovery. A companion Android
application can discover the server and send shutdown scheduling commands.

## Motivation

I built Sundown as a way to get hands‑on experience with real device‑to‑device communication. I wanted to learn how to design small, modular systems that talk over a network, define their own protocol, and stay clean and maintainable as they grow. Working with TCP, UDP, and a simple JSON API gave me a practical way to explore those ideas instead of just reading about them.

There was also a simple everyday problem behind it: I often stream media from my laptop to my tablet, and I wanted an easy way to shut the laptop down remotely when I’m already away from it. Turning that small need into a structured project gave me a chance to experiment, learn, and build something genuinely useful at the same time.

## Features

- Schedule Windows shutdowns using native system commands
- Cancel or reschedule shutdowns
- Persistent shutdown state across application restarts
- LAN device discovery via UDP broadcast (designed for local network use only)
- TCP command server with optional pairing/authentication
- Client‑agnostic protocol (Android app included, others possible)
- Lightweight, no external dependencies beyond Qt

## Architecture Overview

This application is designed as a **LAN service**, is client-agnostic, supports Android clients and may support additional clients in the future.

- **Service**: Qt/C++ application running on Windows
- **Client**: Android application (separate repository), check out here.
- **Communication**:
  - Discovery: UDP broadcast
  - Commands: TCP + JSON messages
  - Security: Optional pairing via one‑time code

## Platform

- Windows 10 / 11
- Built with Qt 6
- CMake-based build system

## Security Model

- LAN-only communication
- Optional pairing mechanism using a one-time code
- No cloud, no external servers
- Minimal attack surface

## Build

```bash
git clone https://github.com/yourname/sundown.git
cd sundown
cmake -B build
cmake --build build
```

More detailed instructions are coming soon.

## Contributing

Contributions, suggestions, and issue reports are welcome. Please open an issue before submitting a pull request.

## License

This project is licensed under the MIT License.  
Copyright (c) 2025 John Doe (aka Praktik)

See the [LICENSE](./LICENSE) file for the full text.
