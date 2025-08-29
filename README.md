# minitalk - 42 Network
<div align="center">
<img src="minitalk.png"/>
</div>
A simple client-server communication program using UNIX signals.

## 📋 Project Overview

Minitalk is a 42 school project that implements a simple communication system between a client and server using only UNIX signals (`SIGUSR1` and `SIGUSR2`). The client sends a string message to the server by encoding each character bit by bit through signals.

## 🚀 Features

- Server displays its PID and waits for messages
- Client sends strings to server using server's PID
- Communication achieved exclusively through `SIGUSR1` and `SIGUSR2`
- Server can handle multiple clients sequentially
- Message acknowledgment system

## 🛠️ Installation

```bash
# Clone the repository
git clone https://github.com/msabr/MINITALK_1337 minitalk
cd minitalk

# Compile the project
make

# This creates two executables: server and client
```

## 📖 Usage

### Starting the Server
```bash
./server
```
The server will display its PID and wait for incoming messages.

### Sending a Message
```bash
./client [SERVER_PID] "Your message here"
```

### Example
```bash
# Terminal 1
./server
Server PID: 12345
Waiting for messages...

# Terminal 2
./client 12345 "Hello, 42!"

# Back to Terminal 1
Received: Hello, 42!
```

## 🔧 How it Works

1. **Server**: Creates a signal handler for `SIGUSR1` and `SIGUSR2`, then waits for signals
2. **Client**: Converts each character to binary and sends each bit as a signal:
   - `SIGUSR1` represents bit `0`
   - `SIGUSR2` represents bit `1`
3. **Server**: Reconstructs the message bit by bit and displays it when complete

## 📁 Project Structure

```
minitalk/
├── Makefile
├── bonus
│   ├── client_bonus.c
│   ├── ft_minitalk_bonus.h
│   ├── minilib_bonus.c
│   └── server_bonus.c
├── mandatory
│   ├── client.c
│   ├── ft_minitalk.h
│   ├── minilib.c
│   └── server.c
└── minitalk.png

3 directories, 12 files
```

## 🎯 42 Project Requirements

- ✅ Use only `SIGUSR1` and `SIGUSR2`
- ✅ Server displays PID at startup
- ✅ Client takes PID and string as parameters
- ✅ String transmission using signals only
- ✅ Server displays received messages
- ✅ Communication must be fast
- ✅ Handle memory properly (no leaks)

## 🔄 Compilation

The project includes a Makefile with the following rules:

- `make` or `make all`: Compile server and client
- `make clean`: Remove object files
- `make fclean`: Remove object files and executables
- `make re`: Recompile everything

## ⚠️ Important Notes

- Server must be started before client
- Only one client can send messages at a time
- Large messages may take time to transmit
- Server PID is required for client communication

## 🎨 Bonus Features (if implemented)

- Server acknowledgment to client
- Unicode character support
- Multiple client handling

## 📚 Key Concepts Learned

- UNIX signal handling
- Inter-process communication (IPC)
- Bit manipulation
- Process identification (PID)
- Asynchronous programming
