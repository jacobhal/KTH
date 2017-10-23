import java.lang.*;
import java.util.*;
import java.math.BigInteger;


public class Modexp {

  public static void main(String args []) {
    // Store each line in this array
    BigInteger[] values = new BigInteger[3];
    
    Scanner sc = new Scanner(System.in);  // Reading from System.in
    while(sc.hasNext()) {
      // Split the current line and store the integer values
      String[] nextLine = sc.nextLine().split(" ");
      for(int i = 0; i < nextLine.length; i++) {
        values[i] = new BigInteger(nextLine[i]);
      }

      // Perform exponentiation and calculate modulo with input value
      System.out.println(exp_by_squaring(values[0], values[1], values[2]));
    
    }
  }

  /**
   * Exponentiation by squaring
   * @param  x basis 
   * @param  e exponent
   * @param  n modulus
   * @return   a^e % n
   */
  public static BigInteger exp_by_squaring(BigInteger x, BigInteger e, BigInteger n) {

    BigInteger z = BigInteger.ONE;
    // Get the most significant set bit of e
    int i = e.bitLength();
    while(i >= 0) {
      // z*z % n
      z = z.multiply(z).mod(n);
      // Check if bit at index i in e is 1
      if(e.testBit(i)) {
        z = z.multiply(x).mod(n); // z*x % n
      }
      i--;
    }

    return z;
  }
}