CC = gcc
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
TARGET = sticksniffer
SRC = sticksniffer.c

CFLAGS = -Wall -Wextra $(shell pkg-config --cflags libusb-1.0)
LDFLAGS = $(shell pkg-config --libs libusb-1.0)

.PHONY: all install uninstall clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)