#include <iostream>

#include "hello.h"
#include <ctype.h>

using namespace std;

void hello (const char * name, int count) {
  if(count == 0) {
    if(name == NULL) {
    	cout << "Hello, world!" << endl;
    }
  } else if (count == 1) {
  	cout << "Hello, " << name << "!" << endl;
  } else {
  	cout << "Hello,";
  	for(int i = 0; i < count; i++) {
  		cout << " " << name;
  	}
  	cout << "!" << endl;
  }
}

std::pair<const char *, int> parse_args (int argc, char * argv[]) {
  char *word = NULL;
  int reps = 0;
  // Inga argument
  if(argc == 1){
  	reps = 0;
  } else if (argc == 2) { // Endast ordet
  	word = argv[1];
  	reps = 1;
  } else if (argc == 3) { // 2 argument
  	word = argv[1];
    if(!isdigit(*argv[2]) || argv[2] < 0) {
      cerr << "error: 2nd argument must be an integral greater than zero!" << endl;
      reps = -1;
    } else {
      reps = atoi(argv[2]);
    }
  } else {
  	cerr << "error: Too many arguments!" << endl;
    reps = -1;
  }
  return std::make_pair (word, reps);
}
