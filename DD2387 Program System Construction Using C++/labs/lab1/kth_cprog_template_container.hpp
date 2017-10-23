#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>


#include <cstdlib>
#include <cstdint>

#include <iterator>
#include <memory>
#include <sstream>
#include <type_traits>

using namespace std;
//unsigned int *ptr;k
//size_t count; // Actual number of elements in the vector (size)
template <typename T>
class Vector {
private:
	// Private variables
	//const size_t DEFAULT_SIZE = 16;

	// Check that this hint works
	// Assigning a vector to itself might seem silly, but you are to make sure that it is
	// handled correctly.

	// Make sure to use const properly
	// Make sure that member-functions that does not change the internal state of the
	// Vector is marked as const.

	T *ptr;
	size_t count; // Actual number of elements in the vector (size)
	size_t limit; // To check if out of space
public:
	// Default
	Vector();
	// Destructor
	~Vector();
	// Define vector of given size. Explicit since Vector v = 3; works but looks weird.
	explicit Vector(size_t);
	// Initiate vector with initializer list.
	Vector(initializer_list<T>);
	// Initiate vector with type T and number of elements.
	Vector(size_t, T);
	// Copy
	Vector(Vector const&);
	// Move
	Vector(Vector &&);
	// Assignment (=) operator
	Vector& operator= (Vector const&);
	const Vector & operator=(Vector &&);
	// Access element at desired index, operator []
	T& operator[] (size_t);
	const T& operator[] (size_t)const;

	/*
	Member functions
	*/

	// Initiate vector with given size, 0 initialized with clear according to lab pm
	void init(const size_t);
	// Fill vector with 0:s
	void reset();

	size_t size()const;

	void mem_alloc(size_t);

	void copy_vals(const T* src, const size_t start,
	                        const size_t end, const int shift);

	const void push_back(T);
	const void insert(size_t, T);
	const void clear();
	const void erase(size_t);
	size_t capacity() const;

	typedef T* iterator;
	iterator begin();
	iterator end();
	iterator find(T const&);

	typedef const T* c_iterator;
	c_iterator begin()const;
	c_iterator end()const;
	c_iterator find(T const&)const;

};

/*

Non-member functions

*/

// Initiate vector with given size, 0 initialized with clear according to lab pm
template <typename T>
void Vector<T>::init(const size_t s) {
	count = s;
	limit = count;
	ptr = new T[s];

	reset();
}

template<typename T>
void Vector<T>::reset() {
	T nullVal = '\0';
	for (size_t i = 0; i < count; ++i) {
		ptr[i] = nullVal;
	}
}

template<typename T>
size_t Vector<T>::size() const { 
	return count; 
}

template<typename T>
void Vector<T>::mem_alloc(size_t t) {
	T *tmp = new T[t + count];
	limit = t + count; // Set new capacity

	for(int i = 0; i < size(); ++i) {
		tmp[i] = ptr[i];
	}

	delete[] ptr;

	ptr = tmp;

}

template <typename T>
void Vector<T>::copy_vals(const T* src, const size_t start,
	                        const size_t end, const int shift) {
	if (shift > 0) {
	// Start from end and move elements 1 step forward to leave room for insert
		for (size_t i = end - 1; i < end && i >= start; --i) {
			ptr[i + shift] = src[i];
		}
	} else {
	// Start from the beginning and shift elements one step forward
		for (size_t i = start; i < end; ++i) {
			ptr[i + shift] = src[i];
		}
	}
}

/*

Member functions

*/
// Capacity
template<typename T>
size_t Vector<T>::capacity() const {
	return limit;
}
template<typename T>
// Clear (TODO)
const void Vector<T>::clear() {
	//ptr = (T*) realloc(ptr, sizeof(T) * count); 
	ptr->~T();
	count = 0;
	
}

template<typename T>
typename Vector<T>::iterator Vector<T>::find(T const& t) {
	for(auto i = begin(); i != end(); ++i) {
		if(t == *i){
			return i;
		}
	}

	return end();
}

// Returns a RAI referring to the element after the last element of the range.
template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
	return &ptr[size()];
}

// Returns a RAI referring to the first element of the range.
template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
	return ptr;
}
template<typename T>
const void Vector<T>::erase(size_t t) {
	if (count == 1) // If array has only one element, clear
		clear();
	else 
	{ 
	// otherwise, shift array elements  
	for(size_t i = t; i<count-1; i++) 
		ptr[i] = ptr[i+1];
	--count;
	} 
}
template<typename T>
const void Vector<T>::insert(size_t t, T val) {
	// TODO: error handling for negatives
	if(t == count) { push_back(val); }
	if(t >= count) {
		throw out_of_range("Out of range");
	}
	if(count > limit) {
		mem_alloc(count*2);
	}
/*
	T *tmp = new T[2*size() + count];
	T tmpVal;
	++count;
	*/

	copy_vals(ptr, t, count, 1);
	if(t != 0) {
		ptr[t-1] = val;
	} else {
		ptr[t] = val;
	}
	++count;
}

template<typename T>
const void Vector<T>::push_back(T val) {
	mem_alloc(size()*2);
	++count;
	ptr[count-1] = val;
}
//template<typename T>

// Default
template<typename T>
Vector<T>::Vector() {
	init(0);
	//cout << "Default constructor" << endl;
}
// Define vector of given size. Explicit since Vector v = 3; works but looks weird.
template<typename T>
Vector<T>::Vector (size_t t) {
	//cout << "Initialization with " << t << " elements" << endl;
	init(t);
}

template <typename T>
Vector<T>::Vector (initializer_list<T> l) {
	//cout << "Initializer list" << endl;
	count = l.size();
	ptr = new T[count];
	int j = 0;
	//for (auto i = begin(l); i < end(l); ++i) {
	for(const T* i = l.begin(); i != l.end(); ++i) {
		//cout << "*i: " << *i << endl;
		ptr[j] = *i;
		//cout << "ptr[j]: " << ptr[j] << endl;
		j++;
	}
}
// Copy
// Check that hint down below works
// Modifying the contents of a copied-to Vector, should not change the contents
// of the copied-from Vector.
template <typename T>
Vector<T>::Vector (Vector const& src) {
	count = src.count;
	ptr = new T[count];
	for(int i = 0; i < count; ++i) {
		ptr[i] = src.ptr[i];
	}
	//cout << "Copy constructor" << endl;
}

// Move
template<typename T>
Vector<T>::Vector (Vector && src) {
	// TODO
	ptr = src.ptr;
	count = src.count;
	// Clear values
	src.count = 0;
	src.ptr = nullptr;


	//cout << "Move constructor" << endl;
	
}
// Destructor
template<typename T>
Vector<T>::~Vector() {
	delete []ptr;
	//cout << "Destructor" << endl;
}

// Assignment (=) operator
template <typename T>
Vector<T>& Vector<T>::operator= (Vector const& src) {
	// Same as copy
	if(src.ptr == ptr) {
		return *this;
	}
	delete [] ptr;
	count = src.count;
	ptr = new T[count];
	for(int i = 0; i < count; ++i) {
		ptr[i] = src.ptr[i];
	}
	//cout << "Assignment operator" << endl;
	return *this;
}
// Assignment (=) operator for move
template <typename T>
const Vector<T>& Vector<T>::operator= (Vector && src) {
	// Orsakar minnesläckor, varför?
	if(src.ptr == ptr) {
		return *this;
	}
	size_t tmp1 = count;
	T *tmp2 = ptr;
	count = src.count;
	src.count = tmp1;

	delete [] ptr;
	ptr = src.ptr;
	src.ptr = tmp2;
	

	src.count = 0;
	src.ptr = nullptr;
	//cout << "Move-assignment operator" << endl;
	return *this;
}
// Access element at desired index, operator []
template <typename T>
T& Vector<T>::operator[] (size_t i) {
	//cout << "operator[]" << endl;
	//cout << "ptr[" << i << "]: " << ptr[i] << endl;
	if(i >= count) {
		throw out_of_range("Out of range");
	}
	/*if(ptr[i] == NULL) {
		throw out_of_range("Out of range");

	}*/
	// TODO: Error handlingc.
	return ptr[i];
}


// Access element at desired index, operator []
template <typename T>
const T& Vector<T>::operator[] (size_t i) const {
	//cout << "operator[]" << endl;
	//cout << "ptr[" << i << "]: " << ptr[i] << endl;
	if(i >= count) {
		throw out_of_range("Out of range");
	}
	/*if(ptr[i] == NULL) {
		throw out_of_range("Out of range");

	}*/
	// TODO: Error handlingc.
	return ptr[i];
}