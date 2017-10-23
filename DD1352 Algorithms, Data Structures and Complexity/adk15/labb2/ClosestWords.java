/* Labb 2 i DD1352 Algoritmer, datastrukturer och komplexitet    */
/* Se labbanvisning under kurswebben https://www.kth.se/social/course/DD1352 */
/* Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se      */
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;

public class ClosestWords {
  ArrayList<String> closestWords = new ArrayList<String>();

  int closestDistance = -1;
  // Definierar matris av storlek 40 x 40 då inget ord är längre än 40 tecken enligt kattis.
  private static final int MSIZE = 40;
  private static final int[][] matrix = new int[MSIZE][MSIZE];

  // Array for bloom filter
  private int[] bloom = new int[256];

  private int offset = 1;

  private String prevWord = "";
  

  // Constructor
  public ClosestWords(String w, ArrayList<String> wordList) {
    // Fill matrix
    for(int j = 0; j < MSIZE; j++) {
      matrix[0][j] = j;
      matrix[j][0] = j;
    }
    // Fill bloom array
    for(int i = 0; i < w.length(); ++i) {
      bloom[(int) w.charAt(i)] = 1;
    }
    // Go through wordlist
    for (String s : wordList) {
      offset = 1;
      // Om skillnaden i längd mellan w och s är större än closestDistance, skippa.
      // Om antalet unika bokstäver i ordet från ordlistan är fler än closestDistance kan det också skippas.
      if(Math.abs(s.length() - w.length()) > closestDistance && closestDistance != -1 || checkUniqueChars(s) > closestDistance && closestDistance != -1){
        continue;
      }
      /*
      for(int i = 0; i < s.length() && i < prevWord.length() && prevWord.charAt(i) == s.charAt(i); i++) {
        offset++;
        if(s.equals("betalade") && w.equals("etalade")) {


          System.out.println("s: " + s);
          System.out.println("prevWord: " + prevWord);
          System.out.println("Offset: " + offset);
          System.out.println();
          System.out.println();

        }
      }
      */
      int dist = Distance(w, s);
      if (dist < closestDistance || closestDistance == -1) {
        closestDistance = dist;
        closestWords.clear();
        closestWords.add(s);
      }
      else if (dist == closestDistance) {
        closestWords.add(s);
      }
      prevWord = s;
    }
  }

  int partDist(String w1, String w2, int w1len, int w2len) {
    // Triviala fall
    if(w1 == w2){ return 0; }
    if(w1len == 0){ return w2len; }
    if(w2len == 0){ return w1len; }
    int prevWordlen = prevWord.length();
    int min = 0;

    for(int i = 0; i < prevWordlen && i < w2len && prevWord.charAt(i) == w2.charAt(i); ++i) {
        ++offset;
    }

    //System.out.println("HEJ" + offset);
    // Samma operationer som i rekursiva partDist men matrisen konstrueras nu på ett mer optimalt sätt.
    for (int y = offset; y <= w2len; ++y) {
        for (int x = 1; x <= w1len; ++x) {
          min = matrix[x - 1][y - 1];
          if (w1.charAt(x - 1) != w2.charAt(y - 1)) {
            ++min;
          }
          if (min > matrix[x][y - 1]) {
            min = 1 + matrix[x][y - 1];
          }
          if (min > matrix[x - 1][y]) {
            min = 1 + matrix[x - 1][y];
          }
          matrix[x][y] = min;
        }
      }
    return matrix[w1len][w2len];
  }

  int Distance(String w1, String w2) {
    return partDist(w1, w2, w1.length(), w2.length());
  }

  int getMinDistance() {
    return closestDistance;
  }

  List<String> getClosestWords() {
    return closestWords;
  }

  // Returns number of unique chars found (i.e. number of chars that doesn't exist in the word searched for)
  int checkUniqueChars(String s) {
        int res = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (bloom[(int) s.charAt(i)] == 0)
                ++res;
        }
        return res;
    }
}

