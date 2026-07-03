# sticksniffer

A command-line USB device sniffer for Linux, built in C on top of `libusb-1.0`. The goal is a lightweight CLI tool you can run  that lists and inspects USB devices connected to your machine.

## Purpose

`sticksniffer` initializes a `libusb` context and talks directly to the USB subsystem to enumerate connected devices with terminal output. Longer term it's meant to grow into a proper dashboard: listing devices, showing vendor/product IDs, and eventually watching for connect/disconnect events in real time.

## Current State (Work in Progress)

This project is early-stage. Right now:

- `libusb` context initializes correctly
- Clean init/exit lifecycle (`libusb_init` → `libusb_exit`)
- **Not yet implemented:** actual device enumeration (`libusb_get_device_list`) — this is the next step
- **Not yet implemented:** packaging (Makefile install target / `.deb`)
- **Not yet implemented:** live device watching / dashboard view


## Requirements

- GCC (or another C compiler)
- `libusb-1.0` development headers
- `pkg-config`

On Debian/Ubuntu:

```bash
sudo apt install build-essential libusb-1.0-0-dev pkg-config
```

### Note for WSL2 users

WSL2 has no visibility into your host's USB bus by default. `libusb_init()` will still succeed, but device enumeration will return nothing unless you bridge devices in with [`usbipd-win`](https://github.com/dorssel/usbipd-win):

```powershell
# On Windows (as Administrator)
winget install usbipd-win
usbipd list
usbipd bind --busid <BUSID>
usbipd attach --wsl --busid <BUSID>
```

Then confirm the device is visible inside WSL2 with `lsusb`.

## Build & Run

Currently there's no Makefile yet — build directly with `gcc` and `pkg-config`:

```bash
gcc sticksniffer.c -o sticksniffer $(pkg-config --cflags --libs libusb-1.0)
./sticksniffer
```

Expected output:

```
libusb initialized successfully!
```

(No device list yet — see Roadmap below.)

## Roadmap

1. Add `libusb_get_device_list()` to enumerate and print connected USB devices (VID/PID, device class, etc.)
2. Add a `Makefile` with `install` / `uninstall` targets so it can be run as `sticksniffer` from anywhere on `PATH`
3. Package as a `.deb` with `libusb-1.0-0` declared as a runtime dependency
4. Add live device connect/disconnect monitoring

## License

TBD