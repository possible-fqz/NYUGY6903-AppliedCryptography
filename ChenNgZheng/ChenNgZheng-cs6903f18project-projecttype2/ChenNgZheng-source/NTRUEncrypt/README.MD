# Implementation of NTRUEncrypt

## Dependencies

[NTL](https://www.shoup.net/ntl/)

## Building

First, ensured the following programs are installed:

* [meson](https://mesonbuild.com/)
* [ninja](https://ninja-build.org/)

Then, change into this directory. Run `meson --buildtype debug debug` to create a build folder called debug. Change into it with `cd debug`, then type `ninja` to build the executable

## Usage

The program takes 3 arguments - first is the *N* parameter, then the *q_base*, and finally the *q_power*. *q* is split up into a base and a power since the inverse algorithm used to compute *fq* works on a prime base raised to a certain power. Most commonly, *q_base* is two.

The program will then output the average time in microseconds it takes to perform each of the three operations: key generation, encryption, and decryption.

## Program Structure

The main class that allows for easy use of the NTRU cryptosystem is in the `NTRUEncrypter.cpp` file. It exposes a constructor that generates a key, plus encrypt\decrypt methods, and a public key getter. This class makes use of underlying functions in the `NTRU.cpp` file which actual perform the base operations of key generation, encrypting, and decrypting.

The `polyinvert.cpp` file contains functions that implement fast polynomial inverses mod some prime. These are used during key generation.

Finally, the `tests` folder contains functions for testing the specific functions in `NTRU.cpp` and the `NTRUEncrypter` class. The `benchmark.cpp` file then contains functions that benchmarks the performance of the `NTRUEncrypter` class.

## Reference Materials

<https://assets.onboardsecurity.com/static/downloads/NTRU/resources/NTRU-PKCS-Tutorial.pdf>

<https://assets.onboardsecurity.com/static/downloads/NTRU/resources/NTRUTech014.pdf>

<https://assets.onboardsecurity.com/static/downloads/NTRU/resources/NTRU-Algebra-Tutorial.pdf>