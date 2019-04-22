# Implementation of Secret Sharing Made Short

## Dependencies

[Boost](https://www.boost.org/)
[Crypto++](https://www.cryptopp.com/)

## Building

Simply run the the executable.


## Implementation

This implementation of Secret Sharing Made Short utilizes Shamir's Secret Sharing Scheme for Key Generation, AES for secure encryption of a plaintext, and Rabin's  Information Dispersal Algorithm for ciphertext distribution. A share of the key and a piece of the ciphertext is distributed to n members. The plaintext can be recovered when m(<n) members combine shares and pieces.

The implementation of Shamir's Secret Sharing Scheme was based on [opensource code](https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing).


AES and Rabin's Information Dispersal Algorithm was partially implemented with sample code from the Crypto++ library.