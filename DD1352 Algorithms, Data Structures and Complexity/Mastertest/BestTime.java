/* Labb 2 i DD1352 Algoritmer, datastrukturer och komplexitet    */
/* Se labbanvisning under kurswebben https://www.kth.se/social/course/DD1352 */
/* Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se      */
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;
import java.io.*;
public class BestTime {
  private static int[] schedule = new int[3];

  public static void main(String args[]) throws IOException {
      InputStreamReader stdin = new InputStreamReader(System.in);
      BufferedReader console = new BufferedReader(stdin);
      String str;
      int sum = 0;
      int minCost = 0;
      try {
        System.out.print("Enter first number ");
        str = console.readLine();
        schedule[0] = Integer.parseInt(str);
        System.out.print("Enter second number ");
        str = console.readLine();
        schedule[1] = Integer.parseInt(str);
        System.out.print("Enter third number ");
        str = console.readLine();
        schedule[2] = Integer.parseInt(str);
        //sum = 100*(inputs[0] + (inputs[1] + inputs[0]) + (inputs[2] + inputs[1] + inputs[0])); 
       insertionSort(schedule);
       for(int i = 0; i < schedule.length; i++) {
        sum += schedule[i]*(schedule.length-i);
        //minCost = sum + schedule[i];
       }
        // Välj alltid det minsta talet -> Lägst värde
      } catch(IOException e)
        {
          System.out.println("Input error");
          System.exit(1);
      } catch(NumberFormatException e)
        {
          System.out.println(e.getMessage() + " is not numeric");
          System.exit(1);
        }
      System.out.println("Total kostnad: " + sum*100 + '\n' + "Längden på vektorn: " + schedule.length);

  }

   private static void insertionSort(int [] v) {
    for(int i = 1; i < v.length; i++) {
      int tmp = v[i];
      int j = i - 1;
      System.out.println("Innan for loop: j = " + j + ", i = " + i);
      for(; j >= 0 && tmp < v[j]; j--) {
          v[j+1] = v[j];      
      }
      System.out.println("v[" + (j+1) + "] = tmp = " + tmp + ", j = " + j);
      v[j+1] = tmp;
    }
  }
/*
  private static void sort(int[] values) {
    if (values ==null || values.length==0){
      return;
    }
    schedule = values;
    int number = values.length;
    quicksort(0, number - 1);
  }

  private static void quicksort(int low, int high) {
    int i = low, j = high;
    // Get the pivot element from the middle of the list
    int pivot = schedule[low + (high-low)/2];

    // Divide into two lists
    while (i <= j) {
      // If the current value from the left list is smaller then the pivot
      // element then get the next element from the left list
      while (schedule[i] < pivot) {
        i++;
      }
      // If the current value from the right list is larger then the pivot
      // element then get the next element from the right list
      while (schedule[j] > pivot) {
        j--;
      }

      // If we have found a values in the left list which is larger then
      // the pivot element and if we have found a value in the right list
      // which is smaller then the pivot element then we exchange the
      // values.
      // As we are done we can increase i and j
      if (i <= j) {
        exchange(i, j);
        i++;
        j--;
      }
    }
    // Recursion
    if (low < j)
      quicksort(low, j);
    if (i < high)
      quicksort(i, high);
  }

  private static void exchange(int i, int j) {
    int temp = schedule[i];
    schedule[i] = schedule[j];
    schedule[j] = temp;
  }
  */
}


