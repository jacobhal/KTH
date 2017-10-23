#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include "sha.h"

// NIST functions
#define ROTL(a,b)     (((a) << (b)) | ((a) >> (32-(b))))
#define ROTR(a,b)     (((a) >> (b)) | ((a) << (32-(b))))
#define SHFR(x, n)    (x >> n)

#define CH(x,y,z)     (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z)    (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)        (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define EP1(x)        (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SIG0(x)       (ROTR(x, 7) ^ ROTR(x, 18) ^ SHFR(x, 3))
#define SIG1(x)       (ROTR(x, 17) ^ ROTR(x, 19) ^ SHFR(x, 10))

// Debug booleans
bool hash_debug = 0;
bool padding_debug = 0;
bool convert_debug = 0;
bool inputsize_debug = 0;

// Set to 1 if testing normal string input
bool convert = 0;

int main() {

  vector<word> block;
  string input;

  while(getline(cin, input)) {

    if(convert) {
      input = string_to_hex(input);
      if(convert_debug)
        cout << "Input string after convertion: " << input << endl;
    }
    input = hex_to_string(input);
    int inputsize = input.size()*8;
    if(inputsize_debug) cout << "Input size in bits: " << inputsize << endl;


    // Start by converting string to a vector of 32 bit words as unsigned int
    bool padded = string_to_wordvector(block, input);
    int messagesize = block.size()*32;
    
    // Debug
    if(padding_debug) {
      cout << "----------BEFORE PADDING----------\n";
      cout << "Printing block as binary...\n";
      print_block_binary(block);
      cout << "Block size: " << block.size()*32 << endl;
    }

    // Pad block array to multiple of 512 bits
    pad(block, inputsize, padded);

    // Debug
    if(padding_debug) {
      cout << "----------AFTER PADDING----------\n";
      cout << "Printing block as binary...\n";
      print_block_binary(block);
      cout << "Block size: " << block.size()*32 << endl;
    }

    // Perform SHA-256 and print hash value to std
    cout << sha_256(block) << endl;

    // Clear block vector
    block.clear();

  }

  // Special case for empty string (not sure if necessary...)
  if(0) {
    // Start by converting string to a vector of 32 bit words as unsigned int
    bool padded = string_to_wordvector(block, input);

    // Pad block array to multiple of 512 bits
    pad(block, 0, padded);

    // Perform SHA-256 and print hash value to std
    cout << sha_256(block) << endl;
  }

  return 0;
}

/**
 * Main functions
 */


/**
 * Pad a message block. For SHA-1 and SHA-256, each message block has 512 bits, which are
 * represented as a sequence of sixteen 32-bit words.
 * @param message a vector of words
 */
void pad(vector<word>& message, int l, bool padded) {

  // Find out how many zeroes to add with NIST equation
  // l + 1 + k = 448 mod 512
  int k = (512 + 448 - (l % 512 + 1)) % 512;

  if(!padded && k > 0) {
    bitset<32> w("10000000000000000000000000000000");
    message.push_back((word) w.to_ulong());
    // Take into account the word we just added
    //k = k - 32;
  }

  // Add 32 bit blocks containing zeroes
  for(int i = 0; i < k / 32; ++i)
    message.push_back(0x00000000);

  // Add the length of the message as binary in the last 2 blocks
  bitset<64> tail(l);
  string tail_str = tail.to_string();
  for(int i = 0; i < 2; ++i) {
    bitset<32> x(tail_str.substr(i*32, (i+1)*32));
    unsigned long converted = x.to_ulong(); 
    message.push_back((word) converted);
  }
}

/**
 * Compute sha-256
 * @param  paddedmessage The full padded message
 * @return               The computed hash
 */
string sha_256(vector<word>& m) {

  // Initialize hash values
  // These words were obtained by taking the first thirty-two bits of the fractional parts of the square
  // roots of the first eight prime numbers.
  word H0 = 0x6a09e667;
  word H1 = 0xbb67ae85;
  word H2 = 0x3c6ef372;
  word H3 = 0xa54ff53a;
  word H4 = 0x510e527f;
  word H5 = 0x9b05688c;
  word H6 = 0x1f83d9ab;
  word H7 = 0x5be0cd19;

  // Iterate over blocks of 512 bits
  for(int i = 0; i < m.size()/16; ++i) {  

    // Prepare message schedule W
    word W[64];

    for(int t = 0; t <= 15; ++t) {
      // Offset message by 16 to get the next 512 bit block since 16*32 = 512
      W[t] = m[t+16*i] & 0xFFFFFFFF;

      if(hash_debug) {
          cout << "W[" << t << "]: " << to_hex(W[t]) << endl;
      }
    }

    for(int t = 16; t <= 63; ++t) {
      W[t] = SIG1(W[t-2]) + W[t-7] + SIG0(W[t-15]) + W[t-16];
      W[t] = W[t] & 0xFFFFFFFF;

      if(hash_debug) {
        cout << "W[" << t << "]: " << to_hex(W[t]) << endl;
      }
    }

    if(hash_debug) {
      cout << "         A        B        C        D        E        F        G        H\n";
    }

    word T1, T2;
    word a = H0;
    word b = H1;
    word c = H2;
    word d = H3;
    word e = H4;
    word f = H5;
    word g = H6;
    word h = H7;

    for(int t = 0; t < 64; ++t) {
      T1 = h + EP1(e) + CH(e, f, g) + k_value[t] + W[t];
      T2 = EP0(a) + MAJ(a, b, c);

      // NIST operations
      h = g;
      g = f;
      f = e;
      e = (d + T1) & 0xFFFFFFFF; // AND to 32 bits
      d = c;
      c = b;
      b = a;
      a = (T1 + T2) & 0xFFFFFFFF; // AND to 32 bits

      if(hash_debug) {
        cout << "t= " << t << ": " << to_hex(a) << " " << to_hex(b) << " " << to_hex(c) 
        << " "  << to_hex(d) << " " << to_hex(e) << " " << to_hex(f) << " " << to_hex(g) 
        << " " << to_hex(h) << endl;
      }
    }

    // Compute intermediate hash values
    H0 = (H0 + a) & 0xFFFFFFFF;
    H1 = (H1 + b) & 0xFFFFFFFF;
    H2 = (H2 + c) & 0xFFFFFFFF;
    H3 = (H3 + d) & 0xFFFFFFFF;
    H4 = (H4 + e) & 0xFFFFFFFF;
    H5 = (H5 + f) & 0xFFFFFFFF;
    H6 = (H6 + g) & 0xFFFFFFFF;
    H7 = (H7 + h) & 0xFFFFFFFF;
  }

  // Compute full hash
  return to_hex(H0) + to_hex(H1) + to_hex(H2) + to_hex(H3)
        + to_hex(H4) + to_hex(H5) + to_hex(H6) + to_hex(H7);
}

/**
 * CONVERTION FUNCTIONS
 */

// Convert a hex string to string
string hex_to_string(string s)
{
  int len = s.length();
  string newString;
  for(int i = 0; i < len; i += 2)
  {
      string byte = s.substr(i, 2);
      char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
      newString.push_back(chr);
  }

  return newString;
}

// Convert a string to hex string (used for testing only)
string string_to_hex(const std::string& input) {
  static const char* const lut = "0123456789ABCDEF";
  size_t len = input.length();

  std::string output;
  output.reserve(2 * len);
  for (size_t i = 0; i < len; ++i)
  {
      const unsigned char c = input[i];
      output.push_back(lut[c >> 4]);
      output.push_back(lut[c & 15]);
  }
  return output;
}

// Convert a string to a word vector
bool string_to_wordvector(vector<word>& block, string s) {
  int len = s.size();
  int nr_of_zeroes_added = 0;
  // Iterate over string
  for (int i = 0; i < len; i = i+4) {
    stringstream ss;
    int diff = len - i;
    // If there is more or exactly 32 bytes left
    if(diff >= 4) {
      // Create bitsets for 4 next characters and store as unsigned integer in block
      bitset<8> a(s.c_str()[i]);
      bitset<8> b(s.c_str()[i+1]);
      bitset<8> c(s.c_str()[i+2]);
      bitset<8> d(s.c_str()[i+3]);

      ss << a << b << c << d;
      bitset<32> w(ss.str());
      block.push_back((word) w.to_ulong());
      
    // If there is less than 32 bytes left
    } else {
      // Create bitsets for remaining characters and store as unsigned integer in block
      for(int j = 0; j < diff; ++j) {
        bitset<8> x(s.c_str()[i+j]);
        ss << x;
      }
      // Pad with zeroes
      for(int j = 0; j < 4-diff; ++j) {
        if(j == 0) {
          bitset<8> x("10000000");
          ss << x;
        } else {
          bitset<8> x("00000000");
          ss << x;
        }
      }
      bitset<32> w(ss.str());
      block.push_back((word) w.to_ulong());
      return true;
    }
  }
  return false;
}

// Convert word to hex string
string to_hex(word w) {

  stringstream stream;
  stream << hex << setfill('0') << setw(8) << w;
  return stream.str();
}


/**
 * PRINT FUNCTIONS
 */

// Print a word vector in the same format it is stored in
void print_block(vector<word> v) {
  for(int i = 0; i < v.size(); ++i) {
    cout << i << ":" << v[i] << endl;
  }
  cout << endl;
}

// Print a word vector in hexadecimal format
void print_block_hex(vector<word> v) {
  for(int i = 0; i < v.size(); ++i) {
    cout << hex << (int) v[i];
  }
  cout << dec << endl;
}

// Print a word vector in binary format
void print_block_binary(vector<word> v) {
  for(int i = 0; i < v.size(); ++i) {
    bitset<32> x(v[i]);
    cout << i*4 << ":" << x.to_string().substr(0,8) << " ";
    cout << i*4+1 << ":" << x.to_string().substr(8,8) << " ";
    cout << i*4+2 << ":" << x.to_string().substr(16,8) << " ";
    cout << i*4+3 << ":" << x.to_string().substr(24,8) << endl;
  }
  cout << dec << endl;
}















