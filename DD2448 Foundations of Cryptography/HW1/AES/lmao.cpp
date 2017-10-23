#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include "aes.h"

using namespace std;

int main() {

  // Buffer to hold 8 bits (1 byte)
  unsigned char byte;
  // Byte matrix
  unsigned char block[MAT_SIZE][MAT_SIZE]; 
  // Check how many bytes were read (will always be 1)
  unsigned int readBufSize = 0;

  // Keep track of rows and columns when reading input into byte matrix
  int row = 0;
  int col = 0;
  int count = 1;
  while(cin >> byte) {
    
    printByte(byte);
    if(count == 16) {
      cout << endl;
      count = 1;
    }  
    count++;  
  }




  return 0;
}

void addRoundKey() {

}

void subBytes() {

}

void shiftRows() {

}

void mixColumns() {

}

void printByte(unsigned char res) {
  cout << hex << uppercase << setfill('0') << setw(2)<< static_cast<unsigned>(res) << endl;
}

void printMatrix(unsigned char mat[MAT_SIZE][MAT_SIZE]) {
  for(int i = 0; i < MAT_SIZE; ++i) {
    for(int j = 0; j < MAT_SIZE; ++i) {
      printByte(mat[i][j]);
    }
  }
}

bool getBit(unsigned char byte, int position) {
  // Retrieve all but the last (position) bits and cut off all but the lsb
  return (byte >> position) & 0x1;
}

