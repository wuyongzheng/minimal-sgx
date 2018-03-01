# Minimal Intel SGX Example

This is a minimal hello world-like sample program for Intel Software Guard
Extensions.
It consists of an untrusted app and a trusted enclave.
The app passes two integers to the enclave which then computes their sum and
returns to the app.

# Prerequisites

To compile and run, you need to have:
* A Linux system. (Sorry, Windows is not supported, because real developers
  don't use Windows.)
* An Intel CPU supporting SGX.
* Intel SGX SDK (for compiling)
* Intel SGX PSW and Intel SGX Driver (for running)

# How to compile

1. Make sure SGX\_SDK in the Makefile is correct.
1. `make`

# How to run

1. `./app`
