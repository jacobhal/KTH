/**
 * Main class for HMM2
 * Authors: Nedo Skobalj and Jacob Hallman
 */
import java.util.Scanner;
import java.util.ArrayList;

public class HMM2 {
	
	public static void main(String[] args) {
		// Read all input and crete matrices
		Scanner sc = new Scanner(System.in);
		// First comes the transition matrix
		int transRowSize = sc.nextInt();
		int transColumnSize = sc.nextInt();
		Matrix transMatrix = new Matrix(transRowSize, transColumnSize);
		for (int i = 0; i < transRowSize ; i++) {
			for (int j = 0; j < transColumnSize ; j++) {
				transMatrix.addValue(i, j, sc.nextDouble());
			}
		}
		// Then the emission matrix
		int emissRowSize = sc.nextInt();
		int emissColumnSize = sc.nextInt();
		Matrix emissMatrix = new Matrix(emissRowSize, emissColumnSize);
		for (int i = 0; i < emissRowSize ; i++) {
			for (int j = 0; j < emissColumnSize ; j++) {
				emissMatrix.addValue(i, j, sc.nextDouble());
			}
		}
		// And the initial state 
		int initRowSize = sc.nextInt();
		int initColumnSize = sc.nextInt();
		Matrix initMatrix = new Matrix(initRowSize, initColumnSize);
		for (int i = 0; i < initRowSize ; i++) {
			for (int j = 0; j < initColumnSize ; j++) {
				initMatrix.addValue(i, j, sc.nextDouble());
			}
		}
		// Read emission sequence
		int nrOfEmissions = sc.nextInt();
		int[] emissSequence = new int[nrOfEmissions];
		for (int i = 0; i < nrOfEmissions; i++) {
			emissSequence[i] = sc.nextInt();
		}
		// Arraylist of matrices that hold alpha values. index i in the list corresponds
		// to time t in HMM. 
		ArrayList<Matrix> alphaMatrix = new ArrayList<Matrix>();
		// Initialze alpha 1.
		Matrix observation1 = emissMatrix.getColumnValue(emissSequence[0]);
		Matrix initTransposed = initMatrix.transpose();
		Matrix alpha1 = initTransposed.elementWiseMultiply(observation1);
		alphaMatrix.add(0, alpha1);
		for (int i = 1; i < nrOfEmissions; i++) {
			Matrix prevTrans = alphaMatrix.get(i-1).transpose();
			Matrix temp = prevTrans.multiplyMatrix(transMatrix).transpose();
			Matrix observationColumn = emissMatrix.getColumnValue(emissSequence[i]);
			Matrix result = temp.elementWiseMultiply(observationColumn);
			alphaMatrix.add(i, result);
		}
		System.out.println(alphaMatrix.get(nrOfEmissions-1).sum());
	}
}