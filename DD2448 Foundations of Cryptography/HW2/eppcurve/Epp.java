import java.lang.*;
import java.util.*;
import java.math.BigInteger;

// Struct for storing points
class Point {
  private BigInteger x;
  private BigInteger y;

  public Point(BigInteger p1, BigInteger p2){
    this.x = p1;
    this.y = p2;
  }

  public BigInteger getX() { return x; }
  public BigInteger getY() { return y; }
  public void setX(BigInteger new_x) { this.x = new_x; }
  public void setY(BigInteger new_y) { this.y = new_y; }
}

public class Epp {

  private static boolean debug = false;

  /*
    This is a curve of the form y^2 = x^3 + ax + b over Z_p 
    with a standard generator G = (g_x, g_y) ∈ Z^2_p of order q, where:
   */
  private static BigInteger _p = new BigInteger("0fffffffffffffffffffffffffffffffeffffffffffffffff", 16);
  private static BigInteger _a = new BigInteger("0fffffffffffffffffffffffffffffffefffffffffffffffc", 16);
  private static BigInteger _b = new BigInteger("022123dc2395a05caa7423daeccc94760a7d462256bd56916", 16);
  private static BigInteger _gx = new BigInteger("07d29778100c65a1da1783716588dce2b8b4aee8e228f1896", 16);
  private static BigInteger _gy = new BigInteger("038a90f22637337334b49dcb66a6dc8f9978aca7648a943b0", 16);
  private static BigInteger _q = new BigInteger("0ffffffffffffffffffffffff7a62d031c83f4294f640ec13", 16);

  public static void main(String args []) {

    Scanner sc = new Scanner(System.in);  // Reading from System.in
    
    while(sc.hasNext()) {
  
      // Read input as hex string and store as BigInteger
      String input = sc.nextLine();
      input = "0" + input.substring(2, input.length()); // Remove "0x"
      BigInteger e = new BigInteger(input, 16);

      // Create base point from gx and gy values
      Point base_point = new Point(_gx, _gy);

      // Perform scalar multiplication on basepoint and exponent to calculate (x, y) = e*G
      Point res_point = scalar_multiply(base_point, e);
    
      // Print result as hex string
      System.out.println("0x" + res_point.getX().toString(16) + " 0x" + res_point.getY().toString(16));
    }
    
    // Debug
    /*
    if(debug) {
      System.out.println("Testing add (17, 10) + (95, 31)");
      Point p = new Point(BigInteger.valueOf(17),BigInteger.valueOf(10));
      Point q = new Point(BigInteger.valueOf(95), BigInteger.valueOf(31));
      _a = BigInteger.valueOf(2);
      _b = BigInteger.valueOf(3);
      _p = BigInteger.valueOf(97);

      Point test_add = point_add(p, q, _p, _a);
      System.out.println("x_r: " + test_add.getX() + "   <----Should be 1");
      System.out.println("y_r: " + test_add.getY() + "   <----Should be 54");

      System.out.println("Testing add (5, 1) + (5, 1)");
      p = new Point(BigInteger.valueOf(5),BigInteger.valueOf(1));
      q = new Point(BigInteger.valueOf(5), BigInteger.valueOf(1));
      _p = BigInteger.valueOf(17);
      test_add = point_add(p, q, _p, _a);
      System.out.println("x_r: " + test_add.getX() + "   <----Should be 6");
      System.out.println("y_r: " + test_add.getY() + "   <----Should be 3");

      System.out.println("Testing Scalar Multiplication");
      _p = BigInteger.valueOf(97);
      _a = BigInteger.valueOf(2);
      p = new Point(BigInteger.valueOf(3),BigInteger.valueOf(6));
      Point res_point = scalar_multiply(p, BigInteger.valueOf(2));
      System.out.println("x_r: " + res_point.getX() + "   <----Should be 80");
      System.out.println("y_r: " + res_point.getY() + "   <----Should be 10");

    }
    */
  }

  /**
   * The operation of adding two points involves finding the third point of
   * intersection between the curve and the straight line passing through the
   * two points that are being added, then reflecting the result in the x axis. 
   * @param  p1 First point
   * @param  p2 Second point
   * @param  p  prime number p that defines our set of integers modulo p
   * @param  a  coefficient a in equation
   * @return    the result of p1 + p2
   */
  private static Point point_add(Point p1, Point p2, BigInteger p, BigInteger a) {

    // Corner case P + (-P) = 0
    if( p1.getX().equals(p2.getX()) && p1.getY().equals(p2.getY().negate().mod(p)) ) {
      return new Point(BigInteger.ZERO, BigInteger.ZERO);
    }
    // Corner case 0 + P = P
    if(p1.getX().equals(BigInteger.ZERO) && p1.getY().equals(BigInteger.ZERO)) {
      return p2;
    }
    // Corner case P + 0 = P
    if(p2.getX().equals(BigInteger.ZERO) && p2.getY().equals(BigInteger.ZERO)) {
      return p1;
    }

    BigInteger m;
    /*
      Calculate the slope m for the line through p1 and p2.
      This equation is different depending on whether they are equal or not.
     */
    // P1 == P2
    if( p1.getX().equals(p2.getX()) && p1.getY().equals(p2.getY()) ) {
      BigInteger upper = p1.getX().pow(2).multiply(BigInteger.valueOf(3)).add(a);
      BigInteger lower = p1.getY().multiply(BigInteger.valueOf(2));
      m = (upper.multiply(lower.modInverse(p))).mod(p);
    } else {
      BigInteger upper = p1.getY().subtract(p2.getY());
      BigInteger lower = p1.getX().subtract(p2.getX());
      m = (upper.multiply(lower.modInverse(p))).mod(p);
    }

    // Calculate x-coordinate of result
    BigInteger r_x = (m.pow(2).subtract(p1.getX()).subtract(p2.getX())).mod(p);
    // Calculate y-coordinate of result
    BigInteger r_y = (p1.getY().add( m.multiply( r_x.subtract(p1.getX()) ) )).mod(p);

    // We have calculated p1 + p2 = -res.
    // This means that our result has to be inverted like this: (p1_x, p1_y) + (p2_x, p2_y) = (r_x, -r_y)
    return new Point(r_x, r_y.negate().mod(p));
  }

  /**
   * Scalar multiplication using the double and add algorithm
   * @param  x The point to multiply
   * @param  n A natural number n
   * @return   n*x
   */
  private static Point scalar_multiply(Point x, BigInteger n) {

    // Define initial points
    Point res = new Point(BigInteger.ZERO, BigInteger.ZERO);
    Point point = x;

    BigInteger k = n;
    int bitLen = k.bitLength();

    // Loop through each bit in n
    for(int i = 0; i < bitLen; i++) {
      // If this bit is 1, add current value of point to res
      if(k.testBit(i)) {
        res = point_add(res, point, _p, _a);
      }
      // Add the point to itself
      point = point_add(point, point, _p, _a);
    }

    return res;
  }

}
