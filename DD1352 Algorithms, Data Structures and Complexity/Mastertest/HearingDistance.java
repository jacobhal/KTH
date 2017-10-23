/* Labb 2 i DD1352 Algoritmer, datastrukturer och komplexitet    */
/* Se labbanvisning under kurswebben https://www.kth.se/social/course/DD1352 */
/* Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se      */
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.Random;
import java.lang.Math;
import java.io.*;

public class HearingDistance {
  private static int k = 0;
  private static int n = 0;
  public static void main(String args[]) throws IOException {
     n = Integer.parseInt(args[0]);
     k = Integer.parseInt(args[1]);
     int [] p = new int[n];
     String str;
     Random random = new Random();
     InputStreamReader stdin = new InputStreamReader(System.in);
     BufferedReader console = new BufferedReader(stdin);
      try {
        for(int i = 0; i < p.length; i++) {
          p[i] = random.nextInt(2*k*n);
          System.out.println(p[i]);
        }
     
        
        //sum = 100*(inputs[0] + (inputs[1] + inputs[0]) + (inputs[2] + inputs[1] + inputs[0])); 
      System.out.println("Heltalskoordinaterna går mellan: 0 och " + 2*k*n);
      System.out.println("k: " + k);

      System.out.println("Resultat: " + movePersons(p));
        // Alla måste vara k nära minst en annan person
      } catch(NumberFormatException e)
        {
          System.out.println(e.getMessage() + " is not numeric");
          System.exit(1);
        }

  }

   private static void insertionSort(int [] v) {
    for(int i = 1; i < v.length; i++) {
      int tmp = v[i];
      int j = i - 1;
      //System.out.println("Innan for loop: j = " + j + ", i = " + i);
      for(; j >= 0 && tmp < v[j]; j--) {
          v[j+1] = v[j];      
      }
      //System.out.println("v[" + (j+1) + "] = tmp = " + tmp + ", j = " + j);
      v[j+1] = tmp;
    }
  }

  public static int movePersons(int[] p) {
    insertionSort(p);
    int res = 0;
    print(p);
    for(int i = 0; i < p.length-1; i++) {
      if(p[i+1]-p[i] > k) {
        /*
        System.out.println("Nu är vi här, p[" + i + "]: " + p[i]);
        System.out.println("Nu är vi här, p[" + (i+1) + "]: " + p[i+1]);
        System.out.println("Nu är vi här, k: " + k);
        */
        res += p[i+1]-p[i]-k;
        p[i] = p[i+1]-k;
      }
        //print(p);
    }
      //print(p);
    return res;
  }

  public static void print(int [] p) {
    System.out.print("{");
    for(int i = 0; i < p.length; i++) {
      System.out.print(p[i]);
      if(i+1 < p.length) { System.out.print(",");}
    }
    System.out.println("}");
  }
}


