#include <stdio.h>
#include <string.h>


#define MAX_BUF  256
#define IV 0b11001011

void encode (unsigned char *, unsigned char *, unsigned char);
void decode (unsigned char *, unsigned char *, unsigned char, int);

unsigned char computeKey (unsigned char);
unsigned char encryptByte (unsigned char, unsigned char);
unsigned char decryptByte (unsigned char, unsigned char);

unsigned char inverseCircularShift (unsigned char);
unsigned char circularShift (unsigned char);

unsigned char getBit (unsigned char, int);
unsigned char setBit (unsigned char, int);
unsigned char clearBit (unsigned char, int);

int
main ()
{

  char str[8];
  int choice;
  unsigned char msg[8];
  unsigned char pt[MAX_BUF];
  unsigned char ct[MAX_BUF];
  unsigned char partialKey;


  printf ("\nYou may:\n");
  printf ("  (1) Encrypt a message \n");
  printf ("  (2) Decrypt a message \n");
  printf ("\n  What is your selection: ");

  fgets (str, sizeof (str), stdin);
  sscanf (str, "%d", &choice);


  //Switch statement takes the user's choice and runs the code accordingly
  //if 1: Encrypt
  //if 2: Decrypt
  switch (choice)
    {

    case 1:

      //The While loop checks for valid input
      while (1)
	{
	  printf ("Enter a partial key value between 1 to 15(inclusive): ");
	  scanf ("\n %hhu", &partialKey);

	  //Loop terminates everytime a right key is entered
	  if (partialKey > 0 & partialKey <= 15)
	    break;

	}

      printf ("\n");


      //Computing Partial_key

      partialKey = computeKey (partialKey);



      // Asking for Plaintext

      printf ("Enter plaintext to be encrypted: ");

      //Since scanf() implemented in the while loop above added 0 to the
      //buffer,I am implementing fgetc to get rid of the unwanted and random
      //values

      fgetc (stdin);
      fgets ((char *) pt, sizeof (pt), stdin);


      //Encrypting

      encode (pt, ct, partialKey);


      break;

    case 2:

      //while loop ensures that a valid value is input

      while (1)
	{
	  printf ("Enter a partial key value between 1 to 15(inclusive): ");
	  scanf ("\n %hhu", &partialKey);

	  //The loop breaks if the right input is entered
	  if (partialKey > 0 & partialKey <= 15)
	    break;
	}



      //Computing partial_key

      partialKey = computeKey (partialKey);

      //Asking for cyphertext

      printf ("Enter the cyphertext (Please enter '-1' to end the input): ");
      fgetc (stdin);


      //'i' is used to count the number of bytes entered by the user
      int i = 0;



      for (int c = 0; c < sizeof (ct); c++)
	{

	  scanf ("%hhu", &ct[c]);

	  ++i;

	  //The 'for' loop terminates when '-1' is input
	  //The ASCII value of '-1' is 255

	  if (ct[c] == 255)

	    break;
	}

      --i;

      //Decoding

      decode (ct, pt, partialKey, i);


      break;

    default:

      break;

    }
  return 0;
}


unsigned char
computeKey (unsigned char partial)
{
  unsigned char b, temp;

  int t = 7;
  for (int i = 0; i < 4; ++i)
    {
      //get the bit at position 'i'
      temp = getBit (partial, i);

      b = b | (temp << t);
      --t;
    }

  //getting partial key
  partial = partial | b;
  return partial;
}


unsigned char
encryptByte (unsigned char src, unsigned char k)
{
  unsigned char temp, cyph, str;

  int mirror = 7;

  //Sending the source code to the circular shift function where it is been shifted

  temp = circularShift (src);

  for (int i = 0; i < 8; ++i)
    {

      str = getBit (temp, i) ^ getBit (k, mirror);

      if (str != 0)
	{
	  cyph = setBit (cyph, i);
	}
      else
	{
	  cyph = clearBit (cyph, i);
	}
      --mirror;
    }

  return cyph;

}


//Encode function without any output
//Passes value into function (unsigned char encryptByte())
void
encode (unsigned char *pt, unsigned char *ct, unsigned char k)
{
  int i = 0;
  unsigned char src, cyph;
  unsigned char mrp = IV;


  int j = 0;
  //While goes on till the partialText value is 0 which means enter
  while (pt[i] != 0)
    {
      //the XOR of the current partial Text value and IV is set by src

      src = pt[i] ^ mrp;
      ct[i] = encryptByte (src, k);
      mrp = ct[i];
      ++i;
      ++j;
    }

  for (int m = 0; m < j; m++)
    {
      printf ("%03d ", ct[m]);
    }

}


unsigned char
decryptByte (unsigned char ct, unsigned char k)
{

  unsigned char temp, shift, str;
  int count = 7;

  for (int i = 0; i < 8; ++i)
    {
      str = getBit (ct, i) ^ getBit (k, count);

      if (str != 0)
	{
	  shift = setBit (shift, i);
	}
      else
	{
	  shift = clearBit (shift, i);
	}
      --count;

    }

  temp = inverseCircularShift (shift);

}


void
decode (unsigned char *ct, unsigned char *pt, unsigned char k, int numBytes)
{
  unsigned char src, nbt;

  for (int i = numBytes; i >= 0; --i)
    {
      //getting decrypted source code
      src = decryptByte (ct[i], k);

      if (i > 0)
	{
	  //if the index is more than 0 the previous cyphertext is being taken to decrypt
	  nbt = src ^ ct[i - 1];
	}
      else
	{
	  //if index is 0 it uses IV to decrypt
	  nbt = src ^ IV;
	}

      pt[i] = nbt;

    }

  //print the statements in the terminal
  for (int z = 0; z < numBytes; ++z)
    {

      printf ("%c", pt[z]);



    }

}

unsigned char
circularShift (unsigned char circ)
{
  unsigned char temp1, temp2;

  //gets the most significant bits at 6 and 7
  temp1 = getBit (circ, 7);
  temp2 = getBit (circ, 6);

  //left shifts the data
  circ = circ << 2;

  //This puts in the most significant bits stored before to the least sig. bits
  circ = circ | (temp1 << 1);
  circ = circ | (temp2 << 0);


  return circ;

}

unsigned char
inverseCircularShift (unsigned char uncirc)
{
  unsigned char temp1, temp2;

  temp1 = getBit (uncirc, 1);
  temp2 = getBit (uncirc, 0);

  uncirc = uncirc >> 2;

  uncirc = uncirc | (temp1 << 7);
  uncirc = uncirc | (temp2 << 6);

  return uncirc;

}



/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char
getBit (unsigned char c, int n)
{
  return ((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char
setBit (unsigned char c, int n)
{
  c = (c | (1 << n));
  return c;
}


/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char
clearBit (unsigned char c, int n)
{
  c = (c & (~(1 << n)));
  return c;
}
