# JmTCP

JmTCP is a simple Java port for mTCP.

It consists of a Java Maven project `li.winston.jmtcp` and a shared library
`libjmtcp.so` which is called into via native methods.

The shared library depends on mTCP `libmtcp.so`, which depends on DPDK
`libdpdk.so`.

## Build and Run

### Java Project

Build the Java project from the project root with Maven (or import into
IntelliJ with Maven), and make sure `libjmtcp.so`, `libmtcp.so` and `libdpdk.so`
are on the shared library path when running it. The main class is
`li.winston.jmtcp.SocketBench`.
 
You can use `-Djava.library.path=<directory>` to manually add to Java's library
path. 

### libjmtcp.so

Go to `src/main/c` and run `./compile.sh`. It may not work in all environments,
but the idea is just to compile the 2 C files into a shared library.

### libmtcp.so and libdpdk.so

There are pre-built `.so`s for Linux in `lib/`, but they may not work in all
environments. They can be built from mTCP and DPDK sources.

Make sure mTCP is configured properly, i.e. ARP, routing, and the DPDK device.
