# NetDiscover Buddy

A Qt6-based GUI application for network discovery and scanning.

## Features

- **User-friendly GUI** - Clean and intuitive interface built with Qt6
- **Multiple scan types** - ARP scan, Ping scan, Fast port scan, and Comprehensive scan
- **Configurable timeouts** - Adjustable scan timeouts for different network conditions
- **Real-time results** - Live display of scan progress and results
- **Cross-platform** - Built with Qt6 for compatibility across different operating systems

## Building

### Prerequisites

- Qt6 (6.8+ recommended)
- CMake (3.16+)
- C++17 compatible compiler
- Build tools (make, g++, etc.)

### Ubuntu/Debian Installation

```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
```

### Build Instructions

1. Clone the repository:
```bash
git clone https://github.com/CyberOakAlpha/NetDiscover-buddy.git
cd NetDiscover-buddy
```

2. Create build directory and configure:
```bash
mkdir build
cd build
cmake ..
```

3. Build the application:
```bash
make -j$(nproc)
```

4. Run the application:
```bash
./bin/NetDiscoverBuddy
```

## Usage

1. **Configure Target**: Enter your target network (e.g., `192.168.1.0/24`) or IP range
2. **Select Scan Type**: Choose from available scan types based on your needs
3. **Set Timeout**: Adjust timeout value based on your network conditions
4. **Start Scan**: Click "Start Scan" to begin network discovery
5. **View Results**: Monitor progress and view discovered hosts in the results area

## Project Structure

```
NetDiscover-buddy/
├── src/
│   ├── main.cpp          # Application entry point
│   ├── mainwindow.h      # Main window header
│   └── mainwindow.cpp    # Main window implementation
├── CMakeLists.txt        # CMake build configuration
├── README.md             # This file
└── .gitignore           # Git ignore rules
```

## Development Status

🚧 **Early Development** - This is currently a GUI framework with basic interface elements. Actual network scanning functionality will be implemented in future updates.

## Planned Features

- [ ] ARP scanning implementation
- [ ] ICMP ping scanning
- [ ] TCP port scanning
- [ ] Host discovery algorithms
- [ ] Export results to various formats
- [ ] Scan scheduling
- [ ] Network topology visualization

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

## License

This project is open source. License details to be determined.

## Author

Built by CyberOakAlpha using Qt6 and C++.