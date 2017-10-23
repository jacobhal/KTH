#include <iostream>
#include <stdexcept>
#include <initializer_list>
//#include "Vector.hpp"

using namespace std;

/*
private:
// Private variables

// Check that this hint works
// Assigning a vector to itself might seem silly, but you are to make sure that it is
// handled correctly.

// Make sure to use const properly
// Make sure that member-functions that does not change the internal state of the
// Vector is marked as const.

unsigned int *ptr;
size_t count = 0; // Actual number of elements in the vector (size)
*/
		// Fill vector with 0:s
	template<typename T>
	void Vector<T>::reset() {
		for (size_t i = 0; i < count; ++i) {
			ptr[i] = (unsigned int) 0;
		}
	}
	template<typename T>
	// Initiate vector with given size, 0 initialized with clear according to lab pm
	void Vector<T>::init(const size_t s) {
		count = s;
		ptr = new T[s];

		reset();
	}
	template<typename T>
	// Default
	Vector<T>::Vector () {
		init(0);
		//cout << "Default constructor" << endl;
	}
	template<typename T>
	// Define vector of given size. Explicit since Vector v = 3; works but looks weird.
	Vector<T>::Vector (size_t t) {
		//cout << "Initialization with " << t << " elements" << endl;
		init(t);
	}
	template<typename T>
	Vector<T>::Vector (initializer_list<T> l){
		//cout << "Initializer list" << endl;
		count = l.size();
		ptr = new T[count];
		int j = 0;
		for (auto i = begin(l); i < end(l); ++i) {
		//for(const unsigned int* i = l.begin(); i != l.end(); ++i) {
			//cout << "*i: " << *i << endl;
			ptr[j] = *i;
			//cout << "ptr[j]: " << ptr[j] << endl;
			++j;
		}
	}
	template<typename T>
	// Copy
	// Check that hint down below works
	// Modifying the contents of a copied-to Vector, should not change the contents
	// of the copied-from Vector.
	Vector<T>::Vector (Vector const& src) {
		count = src.count;
		ptr = new T[count];
		for(size_t i = 0; i < count; ++i) {
			ptr[i] = src.ptr[i];
		}
		//cout << "Copy constructor" << endl;
	}
	template<typename T>
	// Move
	Vector<T>::Vector (Vector && src) {
		// TODO
		ptr = src.ptr;
		count = src.count;
		// Clear values
		src.count = 0;
		src.ptr = nullptr;


		//cout << "Move constructor" << endl;
		
	}
	template<typename T>
	// Destructor
	Vector<T>::~Vector() {
		delete []ptr;
		//cout << "Destructor" << endl;
	}
	template<typename T>
	// Assignment (=) operator
	Vector<T>& Vector<T>::operator= (Vector const& src) {
		// Same as copy
		if(src.ptr == ptr) { return *this; }
		delete [] ptr;
		count = src.count;
		ptr = new T[count];
		for(size_t i = 0; i < count; ++i) {
			ptr[i] = src.ptr[i];
		}
		//cout << "Assignment operator" << endl;
		return *this;
	}
	template<typename T>
	// Assignment (=) operator for move
	const Vector<T>& Vector<T>::operator= (Vector && src) {
		// Orsakar minnesläckor, varför?
		if(src.ptr == ptr) { return *this; }
		size_t tmp1 = count;
		T *tmp2 = ptr;
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
	template<typename T>
	// Access element at desired index, operator []
	T& Vector<T>::operator[] (size_t i) {
		//cout << "operator[]" << endl;
		//cout << "ptr[" << i << "]: " << ptr[i] << endl;
		if(i >= count) {
			throw out_of_range("Out of range");
		}
		return ptr[i];
	}

	template<typename T>
	// Access element at desired index, operator []
	const T& Vector<T>::operator[] (size_t i) const{
		//cout << "operator[]" << endl;
		//cout << "ptr[" << i << "]: " << ptr[i] << endl;
		if(i >= count) {
			throw out_of_range("Out of range");
		}
		return ptr[i];
	}