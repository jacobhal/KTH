#include <iostream>
#include <initializer_list>

using namespace std;
//unsigned int *ptr;
//size_t count; // Actual number of elements in the vector (size)
class UIntVector {
private:
	// Private variables
	//const size_t DEFAULT_SIZE = 16;

	// Check that this hint works
	// Assigning a vector to itself might seem silly, but you are to make sure that it is
	// handled correctly.

	// Make sure to use const properly
	// Make sure that member-functions that does not change the internal state of the
	// UIntVector is marked as const.

	unsigned int *ptr;
	size_t count; // Actual number of elements in the vector (size)
public:
	// Initiate vector with given size, 0 initialized with clear according to lab pm
	void init(const size_t s);
	// Fill vector with 0:s
	void reset();

	void copy(UIntVector const& src);
	// Default
	UIntVector ();
	// Destructor
	~UIntVector();
	// Define vector of given size. Explicit since UIntVector v = 3; works but looks weird.
	explicit UIntVector (size_t t);
	UIntVector (initializer_list<unsigned int> l);
	// Copy
	// Check that hint down below works
	// Modifying the contents of a copied-to UIntVector, should not change the contents
	// of the copied-from UIntVector.
	UIntVector (UIntVector const& src);
	// Move
	UIntVector (UIntVector && src);

	const UIntVector & operator=(UIntVector && src);
	// Initializer list, TODO
	/*
	UIntVector () {
		
	}
	*/
	// Assignment (=) operator
	UIntVector& operator= (UIntVector const& src);
	// Access element at desired index, operator []
	unsigned int& operator[] (size_t i);
	const unsigned int& operator[] (size_t i)const;
	size_t size() const { return count; }

};
