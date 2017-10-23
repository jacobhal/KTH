#include <iostream>
#include <cstdlib>

#include "hello.h"
using namespace std;

void hello (const char * name, int count) {
	if(count > 0){
		cout << "Hello,";
		for(int i=0; i<count; i++){
			cout << " " << name;
		}
		cout << "!" << endl;
	}
}

pair<const char *, int> parse_args (int argc, char * argv[]) {  
  int reps = 0;
  const char * word;
  word = argv[1];
  if(argv[2] != 0){
  reps = atoi(argv[2]);
  }

  if(argv[2] != 0 && argc == 3){
	reps = -1;
	cout << "Please use whole numbers as 2nd argument.\n";
  }else
  if(reps == 0){
	reps = -1;
	cerr << "Please use numbers higher than 0.\n";
  }else
  if(argc > 3){
	reps = -1;
	cerr << "Too many arguments!\n";
  }else
  if(argc == 1){
	word = "world";
	reps = 1;
  }else
  if(argc == 2){
	reps = 1;
  }
  return make_pair (word, reps);
}
