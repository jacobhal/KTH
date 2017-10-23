#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include "aes.h"

// Store byte matrices here
vector<BLOCK_MAT> blocks;
// Store initial key here
BLOCK key;
// Byte matrix
BLOCK_MAT block; 
// Number of bytes read
int bytesRead = 0;
// Expanded key length is 176 bytes for 128-bit keys
unsigned char expandedKey[176];


int main() {

  // Buffer to hold 1 byte from input
  unsigned char byte;

  // Counter used for storing the initial key
  int count = 0;
  cin.unsetf(ios_base::skipws);
 
  // Keep track of rows and columns when reading input into byte matrix
  int row = 0;
  int col = 0;
  cin.unsetf(ios_base::skipws);
  // Read input and convert each block to state matrix format
  while(cin >> byte) {
    bytesRead += sizeof(byte);
    // Read the first 16 bytes into key
    if(count < 16) {
      key.val[count] = byte;
      count++;
    } else {  // Read the rest into matrices of 16 bytes
      block.setVal(row, col, byte);
      row++;
      
      // Go to next col if we are at last row
      if(row == 4) {
        row = 0;
        col++;
      }

      // Reset matrix values and save matrix if we are at last element
      if(row == 3 && col == 3) {
        cin >> byte;
        block.setVal(row, col, byte);
        blocks.push_back(block);
        row = 0;
        col = 0;
      }
    }
  }


// Test data from NIST
/*
  unsigned char expandTest[16] = {
    0x2b, 0x7e, 0x15, 0x16,
    0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88,
    0x09, 0xcf, 0x4f, 0x3c
  };
  

  unsigned char key[16] = {
    0x00, 0x01, 0x02, 0x03, 
    0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0a, 0x0b, 
    0x0c, 0x0d, 0x0e, 0x0f
  };
  

  unsigned char text[16] = {
    0x00, 0x11, 0x22, 0x33,
    0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb,
    0xcc, 0xdd, 0xee, 0xff
  };

  BLOCK_MAT t;
  t.setVal(0, 0, 0x00);
  t.setVal(1, 0, 0x11);
  t.setVal(2, 0, 0x22);
  t.setVal(3, 0, 0x33);
  t.setVal(0, 1, 0x44);
  t.setVal(1, 1, 0x55);
  t.setVal(2, 1, 0x66);
  t.setVal(3, 1, 0x77);
  t.setVal(0, 2, 0x88);
  t.setVal(1, 2, 0x99);
  t.setVal(2, 2, 0xaa);
  t.setVal(3, 2, 0xbb);
  t.setVal(0, 3, 0xcc);
  t.setVal(1, 3, 0xdd);
  t.setVal(2, 3, 0xee);
  t.setVal(3, 3, 0xff);
 

  unsigned char key2[16] = {
    0x2b, 0x7e, 0x15, 0x16, 
    0x28, 0xae, 0xd2, 0xa6, 
    0xab, 0xf7, 0x15, 0x88, 
    0x09, 0xcf, 0x4f, 0x3c
  };


  BLOCK_MAT cipher;
  cipher.setVal(0, 0, 0x32);
  cipher.setVal(1, 0, 0x43);
  cipher.setVal(2, 0, 0xf6);
  cipher.setVal(3, 0, 0xa8);
  cipher.setVal(0, 1, 0x88);
  cipher.setVal(1, 1, 0x5a);
  cipher.setVal(2, 1, 0x30);
  cipher.setVal(3, 1, 0x8d);
  cipher.setVal(0, 2, 0x31);
  cipher.setVal(1, 2, 0x31);
  cipher.setVal(2, 2, 0x98);
  cipher.setVal(3, 2, 0xa2);
  cipher.setVal(0, 3, 0xe0);
  cipher.setVal(1, 3, 0x37);
  cipher.setVal(2, 3, 0x07);
  cipher.setVal(3, 3, 0x34);
  */
  
  // Loop through block and encrypt each one
  for(int i = 0; i < blocks.size(); ++i) {
    AES_Encrypt(blocks[i], key.val);
  }
  return 0;
}

/**
 * The main method for encrypting one block of 16 bytes with AES
 * @param state Block to encrypt
 * @param key   16 byte key
 */
void AES_Encrypt(BLOCK_MAT& state, unsigned char* key) {

  // Create expanded key
  expandKey(key);

  // Initial addRoundKey
  addRoundKey(state, expandedKey);

  // Perform 10 rounds for 128-bit keys
  for(int i = 0; i < ROUNDS; ++i) {
    subBytes(state);
    shiftRows(state);
    // Skip mixcolumns the last iteration
    if(i != ROUNDS-1) {
      mixColumns(state);
    }
    // Advance 16 bytes in our expandedKey for each iteration to read the next roundKey
    addRoundKey(state, &expandedKey[16+MAT_SIZE_FULL*i]);
  }
  // Print output after encryption of block is complete
  state.printRes();
}

/**
 * Expand the 16 byte key to a 176 byte key according to Rijndael key schedule
 * @param in [description]
 */
void expandKey(unsigned char* in) {
  // Defined sizes for 128-bit keys according to Rijndael key schedule
  int n = 16;
  int b = 176;

  // Create expanded key of b bits
  unsigned char* expanded = new unsigned char[b];

  // The first n bytes of the expanded key are simply the encryption key.
  for(int i = 0; i < n; ++i) {
    expanded[i] = in[i];
    expandedKey[i] = in[i];
  }


  int r = 1; // The rcon iteration value i is set to 1
  int offset = n; 
  unsigned char tmp[4];

  // Until we have b bytes of expanded key, we do the following to generate n more bytes of expanded key:
  while(offset < b) {
    // We assign the value of the previous four bytes in the expanded key to tmp
    for(int i = 0; i < 4; ++i) {
      tmp[i] = expanded[offset - 4 + i];
    }

    // We perform the key schedule core (see above) on tmp every four blocks, with i as the rcon iteration value
    if(offset % n == 0) {
      scheduleCore(tmp, r);
      r++;
    }

    // We exclusive-OR tmp with the four-byte block n bytes before the new expanded key. 
    // This becomes the next 4 bytes in the expanded key
    for(int i = 0; i < 4; ++i) {
      expanded[offset] = tmp[i]^expanded[offset - n];
      expandedKey[offset] = expanded[offset];
      offset++;
    }
    
  }
  // Free pointer memory
  delete[] expanded;
}

/**
 * Perform xor operation between each byte in state matrix and the same byte position in the key
 * @param in  state matrix
 * @param key expanded key
 */
void addRoundKey(BLOCK_MAT& in, unsigned char* key) {
 
  for(int i = 0; i < MAT_SIZE; ++i) {
    for(int j = 0; j < MAT_SIZE; ++j) {
      // Iterate through matrix column-wise since the expanded key is stored as an array that way
      unsigned char tmp = in.getVal(j, i)^key[j+i*4];
      in.setVal(j, i, tmp);
    }
  }
  
}

/**
 * Substitute each byte in state matrix with corresponding sbox value
 * @param in [description]
 */
void subBytes(BLOCK_MAT& in) {
  for(int i = 0; i < MAT_SIZE; ++i) {
    for(int j = 0; j < MAT_SIZE; ++j) {
      in.setVal(j, i, sbox[in.getVal(j, i)]);
    }
  }
}

/**
 * Shift each row in state matrix. First row is unchanged, second is shifted one byte, 
 * third is shifted two bytes and fourth is shifted three bytes
 * @param in state matrix
 */
void shiftRows(BLOCK_MAT& in) {
  unsigned char tmp[4];
  for(int i = 1; i < 4; ++i) {
    // Copy row to tmp
    for(int j = 0; j < 4; ++j) {
      tmp[j] = in.getVal(i, j);
    }

    // Shift places and store in input
    for(int j = 0; j < 4; ++j) {
      // (j+i) % 4 will be a rest of 1,2,3,0 when j is 0 and shift one more step to the left
      // each time i is incremented
      in.setVal(i, j, tmp[(j+i)%4]);
    }
    
  }
}

/**
 * Mix the columns according to NIST specification with the use of lookup tables
 * @param in state matrix
 */
void mixColumns(BLOCK_MAT& in) {
  // Copy over state matrix since we want to use these values multiple times without changing them
  BLOCK_MAT copy;
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      copy.setVal(i, j, in.getVal(i, j));
    }
  }

  // Go through column-wise and mix columns
  for(int i = 0; i < 4; ++i) {
    in.setVal(0, i, multBy2[copy.getVal(0, i)] ^ multBy3[copy.getVal(1, i)] ^ copy.getVal(2, i) ^ copy.getVal(3, i));
    in.setVal(1, i, copy.getVal(0, i) ^ multBy2[copy.getVal(1, i)] ^ multBy3[copy.getVal(2, i)] ^ copy.getVal(3, i));
    in.setVal(2, i, copy.getVal(0, i) ^ copy.getVal(1, i) ^ multBy2[copy.getVal(2, i)] ^ multBy3[copy.getVal(3, i)]);
    in.setVal(3, i, multBy3[copy.getVal(0, i)] ^ copy.getVal(1, i) ^ copy.getVal(2, i) ^ multBy2[copy.getVal(3, i)]);
  }
}

/**
 * HELPERS
 */

/**
 * The main key schedule (https://en.wikipedia.org/wiki/Rijndael_key_schedule)
 * @param in state matrix
 * @param r  rcon iteration value
 */
void scheduleCore(unsigned char* in, int r) {

  // Rotate input with no offset
  rotWord(in, 0);

  // Apply sbox values
  for(int i = 0; i < 4; ++i) 
    in[i] = sbox[in[i]];

  // On the first byte, add 2^i
  in[0] ^= rcon[r];
}

/**
 * Rotate word by shifting everything one step to the left
 * @param in     word
 * @param offset offset value
 */
void rotWord(unsigned char* in, int offset) {
  unsigned char tmp = in[offset];
  for(int i = 0; i < MAT_SIZE-1; ++i) {
    in[i + offset] = in[ i + 1 + offset];
  }
  in[offset + 3] = tmp;
}




