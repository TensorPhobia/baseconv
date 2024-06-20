#!/bin/bash

# Set installation directories
INSTALL_DIR="/usr/local/bin"
MAN_DIR="/usr/share/man/man1/"

# Check if running with root privileges
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root or using sudo."
    exit 1
fi

g++ -o baseconv main.cpp

# Copy baseconv binary to installation directory
mv -f ./baseconv $INSTALL_DIR/

# Set permissions (adjust as needed)
chmod +x $INSTALL_DIR/baseconv

# Compress man page
gzip -k ./baseconv.1

# Copy man page to man directory
mv -f ./baseconv.1.gz $MAN_DIR/

# Update man database
mandb

# Clear the screen
clear

echo "baseconv installed successfully."
echo "You can now use 'baseconv' command in your terminal."

# Wait for user to hit a key
read -p "press any key to continue" -n1 -s

# Clear the screen
clear