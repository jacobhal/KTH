/**
 * Main class for HMM4
 * Authors: Nedo Skobalj and Jacob Hallman
 * Approximate model parameters with Baum-welch algorithm.
 * Scale numbers to prevent underflow. For instance, alpha tends to 0 as T increases.
 */
import java.util.*;

public class HMM4 {
	private static final int MAX_ITERS = 600;
	
	public static void main(String[] args) {
		// Read all input and create matrices
		Scanner sc = new Scanner(System.in);
		// First comes the transition matrix
		int transRowSize = sc.nextInt();
		int transColumnSize = sc.nextInt();
		double[][] transMatrix = new double[transRowSize][transColumnSize];
		for (int i = 0; i < transRowSize ; i++) {
			for (int j = 0; j < transColumnSize ; j++) {
				transMatrix[i][j] = sc.nextDouble();
			}
		}
		// Then the emission matrix
		int emissRowSize = sc.nextInt();
		int emissColumnSize = sc.nextInt();
		double[][] emissMatrix = new double[emissRowSize][emissColumnSize];
		for (int i = 0; i < emissRowSize ; i++) {
			for (int j = 0; j < emissColumnSize ; j++) {
				emissMatrix[i][j] = sc.nextDouble();
			}
		}
		// And the initial state 
		int initRowSize = sc.nextInt();
		int initColumnSize = sc.nextInt();
		double[][] initMatrix = new double[initRowSize][initColumnSize];
		for (int i = 0; i < initRowSize ; i++) {
			for (int j = 0; j < initColumnSize ; j++) {
				initMatrix[i][j] = sc.nextDouble();
			}
		}
		// Read emission/observation sequence
		int nrOfEmissions = sc.nextInt();
		int[] emissSequence = new int[nrOfEmissions];
		for (int i = 0; i < nrOfEmissions; i++) {
			emissSequence[i] = sc.nextInt();
		}
		// Create necessary matrices
		double[][] alphaMatrix = new double[transRowSize][nrOfEmissions];
		double[][] betaMatrix = new double[transRowSize][nrOfEmissions];
		double[][] gammaMatrix = new double[transRowSize][nrOfEmissions];
		HashMap<Integer, double[][]> diGammaMap = new HashMap<Integer, double[][]>();


		// 1. Initialization
		double[] cScaleVector =  new double[nrOfEmissions];
		double oldLogProb = Double.NEGATIVE_INFINITY;
		int iters = 0;
		double logProb = 0;
		while(iters < MAX_ITERS && logProb > oldLogProb) {
			//System.out.println("ITERATION " + iters + ":");
			if(iters != 0) {
				oldLogProb = logProb;
			}

			// 2. The alpha-pass
			 
			// compute alpha0(i)
			cScaleVector[0] = 0;
			for(int i = 0; i < transRowSize; i++) {
				alphaMatrix[i][0] = initMatrix[0][i] * emissMatrix[i][emissSequence[0]]; // Check if correct				                                                                         
				cScaleVector[0] += alphaMatrix[i][0];
			}


			// -------------DEBUG-----------
			/*
			printMatrix2(alphaMatrix, 4, 1);

			for(int i = 0; i < cScaleVector.length; i++) {
				System.out.println(cScaleVector[i]);
			}
			*/

			// scale the alpha0
			cScaleVector[0] = 1/cScaleVector[0];
			for(int i = 0; i < transRowSize; i++) {
				alphaMatrix[i][0] *= cScaleVector[0];
			}

			// RÄTT HITTILS
			// compute alphat(i)
			for(int t = 1; t < nrOfEmissions; t++) {
				cScaleVector[t] = 0;
				for(int i = 0; i < transColumnSize; i++) {
					alphaMatrix[i][t] = 0;
					for(int j = 0; j < transColumnSize; j++) {
						//System.out.println("j: " + j + ", t-1: " + (t-1) + ", alpha: " + alphaMatrix[j][t-1]);
						//System.out.println(transMatrix[j][i]);
						alphaMatrix[i][t] += alphaMatrix[j][t-1] * transMatrix[j][i];
					}
					//System.out.println(alphaMatrix[i][t]);
					alphaMatrix[i][t] *= emissMatrix[i][emissSequence[t]];
					cScaleVector[t] += alphaMatrix[i][t];
				}

				// scale alphat
				cScaleVector[t] = 1/cScaleVector[t];
				for(int i = 0; i < transRowSize; i++) {
					alphaMatrix[i][t] *= cScaleVector[t];
				}
				
			}

			//printMatrixColumnWise(alphaMatrix); // Rätt

			/*
			System.out.println("Printing alpha matrix...");
			System.out.println("-------------------------------------------------------------");
			printMatrixColumnWise(alphaMatrix);
			System.out.println("-------------------------------------------------------------");
			*/

			// 3. The beta-pass
			
			// Let betaT-1(i) = 1,scaled by cT.
			for (int i = 0; i < transRowSize; i++) {
				betaMatrix[i][nrOfEmissions-1] = cScaleVector[nrOfEmissions-1]; // Check if correct
			}

			// Beta-pass
			for (int t = nrOfEmissions-2; t >= 0; t--) {
				for (int i = 0; i < transRowSize; i++) {
					betaMatrix[i][t] = 0;
					for (int j = 0; j < transColumnSize; j++) {
						betaMatrix[i][t] += transMatrix[i][j] * emissMatrix[j][emissSequence[t+1]] * betaMatrix[j][t+1];
					}
					betaMatrix[i][t] *= cScaleVector[t];
				}
			}

			// printMatrixColumnWise(betaMatrix); // RÄTT

			/*
			System.out.println("Printing beta matrix...");
			System.out.println("-------------------------------------------------------------");
			printMatrixColumnWise(betaMatrix);
			System.out.println("-------------------------------------------------------------");
			*/

			// 4. Compute diGammaT(i, j) and gammaT(i)
			double denom;
			for (int t = 0; t < nrOfEmissions-1; t++) {
				denom = 0;
				for(int i = 0; i < transRowSize; i++) {
					for(int j = 0; j < transColumnSize; j++) {
						denom += alphaMatrix[i][t] * transMatrix[i][j] * emissMatrix[j][emissSequence[t+1]] * betaMatrix[j][t+1];
					}
				}

				double[][] diGammaMatrix = new double[transRowSize][transColumnSize];
				for (int i = 0; i < transRowSize; i++) {
					gammaMatrix[i][t] = 0;
					for (int j = 0; j < transColumnSize; j++) {
						diGammaMatrix[i][j] = (alphaMatrix[i][t] * transMatrix[i][j] * emissMatrix[j][emissSequence[t+1]] * betaMatrix[j][t+1]) / denom;
						gammaMatrix[i][t] += diGammaMatrix[i][j];
					}
				}
				diGammaMap.put(t, diGammaMatrix);
			}


			// special case for gammaT-1(i)
			denom = 0;
			for (int i = 0; i < transRowSize; i++) {
				denom += alphaMatrix[i][nrOfEmissions-1];
			}
			for (int i = 0; i < transRowSize; i++) {
				gammaMatrix[i][nrOfEmissions-1] = alphaMatrix[i][nrOfEmissions-1] / denom;
			}

			//printMatrixColumnWise(gammaMatrix); RÄTT

			// 5. Re-estimate A, B and pi

			// Re-estimate pi
			for (int i = 0; i < transRowSize; i++) {
				initMatrix[0][i] = gammaMatrix[i][0];
			}

			//printMatrix(initMatrix); // RÄTT
			
			// Re-estimate A
			double numer = 0;
			for (int i = 0; i < transRowSize; i++) {
				for (int j = 0; j < transColumnSize; j++) {
					denom = 0;
					numer = 0;
					for (int t = 0; t < nrOfEmissions-1; t++) {
						numer += diGammaMap.get(t)[i][j];
						denom += gammaMatrix[i][t];
					}
					transMatrix[i][j] = numer/denom;
				}
			}
 
			// printMatrix(transMatrix); RÄTT

			// Re-estimate B
			for (int i = 0; i < transRowSize; i++) {
				for (int j = 0; j < emissColumnSize; j++) {
					numer = 0;
					denom = 0;
					for (int t = 0; t < nrOfEmissions; t++) {
						if (emissSequence[t] == j) {
							numer += gammaMatrix[i][t];
						}
						denom += gammaMatrix[i][t];
					}
					emissMatrix[i][j] = numer/denom;
				}
			}

			// printMatrix(emissMatrix); RÄTT

			// 6. Compute log[P(O | lambda)]

			logProb = 0;
			for(int i = 0; i < nrOfEmissions; i++) {
				//System.out.println("cScale[" + i + "]: " + cScaleVector[i]);
				logProb += Math.log(cScaleVector[i]);
			}
			logProb = -logProb;
			//System.out.println(logProb);

			// 7. Go to start of big loop to check whether we should keep going
			iters++;

			//printMatrixColumnWise(alphaMatrix);
			//System.out.println();
			//System.out.println("-----------------------------------------------------");
		} 
		//System.out.println("SLUTGILTIGT SVAR: ");
		printMatrix(transMatrix);
		//System.out.println();
		printMatrix(emissMatrix);
		//System.out.println();
	}

	private static void printMatrix(double[][] matrix) {
		System.out.print(matrix.length + " " + matrix[0].length + " ");
		for(int i = 0; i < matrix.length; i++) {
			for(int j = 0; j < matrix[i].length; j++) {
				System.out.print(matrix[i][j] + " ");
			}
		}
		System.out.println();
		
	}

	private static void printMatrixColumnWise(double[][] matrix) {
		for(int i = 0; i < matrix[0].length; i++) {
			System.out.print(matrix.length + " " + matrix[0].length + " ");
			for(int j = 0; j < matrix.length; j++) {
				System.out.print(matrix[j][i] + " ");
			}
			System.out.println();
		}
		System.out.println();
		
	}

	private static void printMatrix2(double[][] matrix, int rows, int columns) {
		System.out.print(rows + " " + columns + " ");
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < columns; j++) {
				System.out.print(matrix[i][j] + " ");
			}
		}
		System.out.println();
		
	}
}