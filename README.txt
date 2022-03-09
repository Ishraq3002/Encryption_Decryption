# Encryption_Decryption
Created by: Md Ishraq Tanzim
Date: 	    November, 2021

The C program allows user to choose whether to encrypt or decrypt a message depending on a specific key and the output gets shown on the screen.

1) The program prompts the user to indicate whether they wish to encrypt a readable message (the plaintext), 
   or if they wish to decrypt an already encrypted sequence (the ciphertext) back to its plaintext form.

2) Both the plaintext and the ciphertext are stored as arrays of unsigned chars, and the program manipulates the individual characters using bit masks

3) The program implements two algorithms:
	• an encryption algorithm that takes an array of plaintext bytes and encrypts each byte one at a
	  time into a corresponding ciphertext byte, and
	• a decryption algorithm that takes an array of ciphertext bytes and decrypts each byte one at a
	  time into a corresponding plaintext byte

4) The encryption process has two separate parts:
	• the computation of the key, and
	• the encryption of each plaintext byte into a ciphertext byte, using that key

5) Command for compiling the code in linux environment: gcc -o Encrypt_Decrypt Encrypt_Decrypt.c
6) Command for running the code after compiling	      : ./Encrypt_Decrypt	
