// 1. Returnerar inte 16 eftersom for-loopen uppfattas som tom då semikolon sätts direkt efter.
// 2/3. 3.1415 uppfattas inte som en float, genom att lägga till f efter talet kommer if-satsen bli sann då
// man i koden explicit säger att det ska tolkas som en float.
// 4. Eftersom jämförning av floats kan ge fel resultat verkar det vanligaste sättet att använda sig av epsilon,
// dvs. ett värde som representerar en godtagbar felmarginal. Det kan se ut på detta sätt för floats: if (fabs(a-b) < epsilon) {...}
#include <iostream>

int powerof (int x, int y) {
  int res = 1;

  for (int i = 0; i < y; ++i);
    res *= x;

  return res;
}

int main () {
  int const a = 2;
  int const b = 4;

  int   x = powerof(a, b); 
  float y = 3.1415;

  std::cout << a << "^" << b << " = " << x << ";\n";

  if (y == 3.1415)
    std::cout << y << " is equal to 3.1415!\n";
  else
    std::cout << y << " is not equal to 3.1415!\n";
}
