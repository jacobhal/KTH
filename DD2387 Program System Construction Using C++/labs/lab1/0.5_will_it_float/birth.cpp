#include <iostream>

class A {
public:
   A () {
     std::cout << "default-constructor" << std::endl;
   }

   A (A const& src) {
     std::cout << "copy-constructor" << std::endl;
   }

  ~A () {
    std::cout << "destructor" << std::endl;
  }

   A(char const* s) {
      std::cout << "some other constructor" << std::endl;
   }

   A& operator= (A const& src) {
     std::cout << "the assignment operator" << std::endl;
     return *this;
   }
};

void no_ref(A a) {} // Destructor sker precis då denna metod lämnas.
void with_ref(const A & a) {}

int main()
{
    A a("my name is a"); // some other constructor
    std::cout << "-" << std::endl;
    A b = a;          // what is the difference, copy constructor
    std::cout << "--" << std::endl;
    A c(a);           // between these three, copy constructor
    std::cout << "---" << std::endl;
    A d;              // forms of initialization?, default constructor, initierar här utan värde vilket resulterar i default.
    std::cout << "----" << std::endl;
    d = a; // assignment operator

    no_ref (a);     // will this copy the value of `a`? JA
      // Destructor (sker då no_ref lämnas)
    with_ref (a);     // will this copy the value of `a`? NEJ

    A *aa = new A[5]; // default x 5
    delete []aa;        // what will happen?
    // Destructor x 9
    return 0;
}
