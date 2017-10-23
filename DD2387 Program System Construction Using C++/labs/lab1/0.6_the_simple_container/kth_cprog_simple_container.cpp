#include <iostream>
#include "kth_cprog_simple_container.hpp"
#include <stdexcept>
#include <initializer_list>

using namespace std;

/*
private:
// Private variables

// Check that this hint works
// Assigning a vector to itself might seem silly, but you are to make sure that it is
// handled correctly.

// Make sure to use const properly
// Make sure that member-functions that does not change the internal state of the
// UIntVector is marked as const.

unsigned int *ptr;
size_t count = 0; // Actual number of elements in the vector (size)
*/

	// Fill vector with 0:s
	void UIntVector::reset() {
		for (size_t i = 0; i < count; ++i) {
			ptr[i] = (unsigned int) 0; // (unsigned int){}; enligt lab pm
		}
	}
	// Initiate vector with given size, 0 initialized with clear according to lab pm
	void UIntVector::init(const size_t s) {
		count = s;
		ptr = new unsigned int[s];

		reset();
	}
	// Default
	UIntVector::UIntVector () {
		init(0);
		//cout << "Default constructor" << endl;
	}
	// Define vector of given size. Explicit since UIntVector v = 3; works but looks weird.
	UIntVector::UIntVector (size_t t) {
		//cout << "Initialization with " << t << " elements" << endl;
		init(t);
	}
	UIntVector::UIntVector (initializer_list<unsigned int> l){
		//cout << "Initializer list" << endl;
		count = l.size();
		ptr = new unsigned int[count];
		int j = 0;
		for (auto i = begin(l); i < end(l); ++i) {
		//for(const unsigned int* i = l.begin(); i != l.end(); ++i) {
			//cout << "*i: " << *i << endl;
			ptr[j] = *i;
			//cout << "ptr[j]: " << ptr[j] << endl;
			++j;
		}
	}

	// Copy
	// Check that hint down below works
	// Modifying the contents of a copied-to UIntVector, should not change the contents
	// of the copied-from UIntVector.
	UIntVector::UIntVector (UIntVector const& src) {
		count = src.count;
		ptr = new unsigned int[count];
		for(size_t i = 0; i < count; ++i) {
			ptr[i] = src.ptr[i];
		}
		//cout << "Copy constructor" << endl;
	}
	// Move
	UIntVector::UIntVector (UIntVector && src) {
		// TODO
		ptr = src.ptr;
		count = src.count;
		// Clear values
		src.count = 0;
		src.ptr = nullptr;


		//cout << "Move constructor" << endl;
		
	}
	// Destructor
	UIntVector::~UIntVector() {
		delete []ptr;
		//cout << "Destructor" << endl;
	}
	// Assignment (=) operator
	UIntVector& UIntVector::operator= (UIntVector const& src) {
		// Same as copy
		if(src.ptr == ptr) { return *this; }
		delete [] ptr;
		count = src.count;
		ptr = new unsigned int[count];
		for(size_t i = 0; i < count; ++i) {
			ptr[i] = src.ptr[i];
		}
		//cout << "Assignment operator" << endl;
		return *this;
	}
	// Assignment (=) operator for move
	const UIntVector& UIntVector::operator= (UIntVector && src) {
		// Orsakar minnesläckor, varför?
		if(src.ptr == ptr) { return *this; }
		size_t tmp1 = count;
		unsigned int *tmp2 = ptr;
		delete [] ptr;

		count = src.count;
		src.count = tmp1;


		ptr = src.ptr;
		src.ptr = tmp2;
		

		src.count = 0;
		src.ptr = nullptr;
		//cout << "Move-assignment operator" << endl;
		return *this;
	}
	
	// Access element at desired index, operator []
	unsigned int& UIntVector::operator[] (size_t i) {
		//cout << "operator[]" << endl;
		//cout << "ptr[" << i << "]: " << ptr[i] << endl;
		if(i >= count) {
			throw out_of_range("Out of range");
		}
		return ptr[i];
	}


	// Access element at desired index, operator []
	const unsigned int& UIntVector::operator[] (size_t i) const{
		//cout << "operator[]" << endl;
		//cout << "ptr[" << i << "]: " << ptr[i] << endl;
		if(i >= count) {
			throw out_of_range("Out of range");
		}
		return ptr[i];
	}