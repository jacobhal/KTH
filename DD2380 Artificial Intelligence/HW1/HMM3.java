/**
 * Main class for HMM3
 * Authors: Nedo Skobalj and Jacob Hallman
 */

// SMH VI ÄR IDIOTER.
// vi måste ju backtracka inte spara ner under the shits.
// 
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

public class HMM3 {
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
		// HashMap of HashMaps that hold delta values and their preceeding states.
		HashMap<Integer, HashMap<Integer, Integer>> deltaMap = new HashMap<Integer, HashMap<Integer, Integer>>();
		for (int i = 0; i < nrOfEmissions; i++) {
			deltaMap.put(i, new HashMap<Integer, Integer>());
		}
		ArrayList<Matrix> deltaList = new ArrayList<Matrix>();
		// Initialze delta 1.
		Matrix observation1 = emissMatrix.getColumnValue(emissSequence[0]);
		Matrix initTransposed = initMatrix.transpose();
		Matrix delta1 = initTransposed.elementWiseMultiply(observation1);
		deltaList.add(0, delta1);
		// stateSequence holds the most likely sequence of states that has been
		// computed. 
		int[] stateSequence = new int[nrOfEmissions];
		// Update delta values 
		for (int i = 1; i < nrOfEmissions; i++) {
			Matrix deltaValue = new Matrix(transRowSize, 1);
			int observation = emissSequence[i]; // Next emission in the emission sequence
			Matrix prevProb = deltaList.get(i-1); // Previous delta
			Matrix observationColumn = emissMatrix.getColumnValue(observation); 
			// Compute max for each state (column)
			for (int j = 0; j < transColumnSize; j++) {
				Matrix transColumn = transMatrix.getColumnValue(j);
				double obsValue = observationColumn.getValue(j, 0);
				Matrix partResult = prevProb.elementWiseMultiply(transColumn);
				double[] rowResult = partResult.scalarMultiply(obsValue).max();
				deltaValue.addValue(j, 0, rowResult[0]);
				deltaMap.get(i).put(j, (int)rowResult[1]);
			}
			deltaList.add(i, deltaValue);
		}
		Matrix lastDelta = deltaList.get(deltaList.size()-1);
		int lastState = lastDelta.maxValueRowIndex();
		stateSequence[nrOfEmissions-1] = lastState;
		for (int i = nrOfEmissions-1; i > 0; i--) {
			stateSequence[i-1] = deltaMap.get(i).get(lastState);
			lastState = deltaMap.get(i).get(lastState);
		}
		for (int k = 0; k < deltaList.size(); k++) {
			System.out.print(stateSequence[k] + " ");
		}
	}
}