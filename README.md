# Minimal Intel SGX Example

This is a minimal hello world-like sample program for Intel Software Guard
Extensions.
It consists of an untrusted app and a trusted enclave.
The app passes two integers to the enclave which then computes their sum and
returns it to the app.
This code is based on digawp's [hello-enclave](https://github.com/digawp/hello-enclave)

# Prerequisites

To compile and run, you need:
* A Linux system. Sorry. Windows is not supported, because real developers
  don't use Windows :)
* Intel SGX SDK (for compiling)
* Intel SGX PSW and Intel SGX Driver (for running)
* An Intel CPU supporting SGX (for running).

# How to compile

1. Make sure SGX\_SDK in the Makefile is correct.
1. `make`

# How to run

run `./app`. You should see "Succeed: 8 + 17 = 25!"
