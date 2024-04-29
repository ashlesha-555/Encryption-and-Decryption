# Encryption and Decryption Program

This program provides functionality for encrypting and decrypting text using two different methods: circular shift encryption (xrot) and expression-based encryption (xplus).

## Usage

To use the program, follow these steps:

1. **Compile the program**: Compile the program using a C++ compiler, such as g++:

    ```bash
    g++ -o encryption_program main.cpp
    ```

2. **Run the compiled program**: Run the compiled program with the following command-line arguments:

    ```bash
    ./encryption_program <Encrypt|Decrypt> <xrot|xplus> <Password> <InputFile> <OutputFile>
    ```

    - `<Encrypt|Decrypt>`: Choose whether to encrypt or decrypt the input text.
    - `<xrot|xplus>`: Choose the encryption method (`xrot` for circular shift encryption or `xplus` for expression-based encryption).
    - `<Password>`: Provide an integer password used for encryption.
    - `<InputFile>`: Specify the input file containing the text to be encrypted or decrypted.
    - `<OutputFile>`: Specify the output file where the result will be written.

## Encryption Methods

### Circular Shift Encryption (xrot)

In circular shift encryption, each character in the input text is shifted a certain number of positions to the left or right based on the password provided.

### Expression-based Encryption (xplus)

In expression-based encryption, each character in the input text is transformed using the ASCII value of the character and a numeric value derived from the password and the character's position in the input text.

## Examples

### Encrypt using Circular Shift Encryption (xrot):

```bash
./encryption_program Encrypt xrot 4836 input.txt output.txt
