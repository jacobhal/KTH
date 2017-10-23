/**
 * Main class for HMM4
 * Authors: Nedo Skobalj and Jacob Hallman
 */
import java.util.*;

public class HMM4 {
	private static final int MAX_ITERS = 1;
	
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
		HashMap<Integer, Matrix> betaMatrix = new HashMap<Integer, Matrix>();
		ArrayList<Matrix> gammaMatrix = new ArrayList<Matrix>();
		ArrayList<Matrix> diGammaMatrix = new ArrayList<Matrix>();
		double[] cScaleVector =  new double[nrOfEmissions];
		double oldLogProb = Double.NEGATIVE_INFINITY;
		int iters = 0;
		double logProb = 0;
		while (iters < MAX_ITERS && logProb > oldLogProb) {
			System.out.println("ITERATION " + iters + ":");
			if (iters != 0) {
				oldLogProb = logProb;
			}
			System.out.println("logProb " + logProb);
			System.out.println("oldLogProb: " + oldLogProb);
			double cScale = 0;
			Matrix observation1 = emissMatrix.getColumn(emissSequence[0]);
			Matrix initTransposed = initMatrix.transpose();
			Matrix alpha0 = initTransposed.elementWiseMultiply(observation1);
			cScale += alpha0.sum();
			// scale the alpha0
			cScale = 1/cScale;
			cScaleVector[0] = cScale;
			alpha0 = alpha0.scalarMultiply(cScale);
			alphaMatrix.add(0, alpha0);
			for (int i = 0; i < alpha0.getRowLength(); i++) {
				System.out.println("alpha[" + i + "]: " + alpha0.getValue(i, 0));
			}
			// compute alphat(i) old version
			/*
			for (int i = 1; i < nrOfEmissions; i++) {
				cScale = 0;
				Matrix prevTrans = alphaMatrix.get(i-1).transpose();
				Matrix temp = prevTrans.multiplyMatrix(transMatrix).transpose();
				Matrix observationColumn = emissMatrix.getColumn(emissSequence[i]);
				Matrix result = temp.elementWiseMultiply(observationColumn);
				cScale += result.sum();
			}
			*/
			// compute alphat(i)
			double part;
			for (int t = 1; t < nrOfEmissions; t++) {
				cScaleVector[t] = 0;
				Matrix alphaPart = new Matrix(transColumnSize, 1);
				for (int i = 0; i < transColumnSize; i++) {
					part = 0;
					for (int j = 0; j < transColumnSize; j++) {
						double prevAlpha = alphaMatrix.get(t-1).getValue(j, 0);
						double trans = transMatrix.getValue(j, i);
						part += prevAlpha*trans;
					}
					double emiss = emissMatrix.getValue(i, emissSequence[t]);
					part *= emiss;
					cScaleVector[t] += part;
					alphaPart.addValue(i, 0, part);
				}
				// scale alphat
				cScaleVector[t] = 1/cScaleVector[t];
				alphaPart = alphaPart.scalarMultiply(cScaleVector[t]);
				alphaMatrix.add(t, alphaPart);
			}
			// dis print looked good man
			//printList(alphaMatrix);

			// Let betaT-1(i) = 1,scaled by cT.
			Matrix initBeta = new Matrix(transRowSize, 1);
			for (int i = 0; i < transRowSize; i++) {
				initBeta.addValue(i, 0, cScaleVector[nrOfEmissions-1]);
			}
			betaMatrix.put(nrOfEmissions-1, initBeta);
			for (int t = nrOfEmissions-2; t >= 0; t--) {
				Matrix betaPart = new Matrix(transRowSize, 1);
				for (int i = 0; i < transRowSize; i++) {
					part = 0;
					for (int j = 0; j < transRowSize; j++) {
						double aij = transMatrix.getValue(i, j);
						double bJ = emissMatrix.getValue(j, emissSequence[t+1]);
						double nextBt = betaMatrix.get(t+1).getValue(j, 0);
						part += (aij*bJ*nextBt);
					}
					part = part*cScaleVector[t];
					betaPart.addValue(i, 0, part);
				}
				betaMatrix.put(t, betaPart);
			}
			//printHash(betaMatrix);
			double denom;
			Matrix helpMatrix = new Matrix(transColumnSize, transColumnSize);
			for (int t = 0; t < nrOfEmissions-1; t++) {
				denom = 0;
				for(int i = 0; i < transColumnSize; i++) {
					for(int j = 0; j < transColumnSize; j++) {
						double aplhaT = alphaMatrix.get(t).getValue(i, 0);
						double aij = transMatrix.getValue(i, j);
						double bJ = emissMatrix.getValue(j, emissSequence[t+1]);
						double nextBt = betaMatrix.get(t+1).getValue(j, 0);
						part = aplhaT * aij * bJ * nextBt;
						denom = denom + part;
						helpMatrix.addValue(i, j, part); // save this cuz we need it later
					}
				}
				double gammaI;
				for (int i = 0; i < transColumnSize; i++) {
					Matrix initDiGamma = new Matrix(transColumnSize, transColumnSize);
					diGammaMatrix.add(t, initDiGamma);
					Matrix initGamma = new Matrix(transColumnSize, 1);
					gammaMatrix.add(t, initGamma);
					for (int j = 0; j < transColumnSize; j++) {
						part = helpMatrix.getValue(i, j);
						diGammaMatrix.get(t).addValue(i, j, (part/denom));
						gammaI = gammaMatrix.get(t).getValue(i, 0);
						gammaMatrix.get(t).addValue(i, 0, (gammaI + (part/denom)));
					}
				}
			}
			// special case for gammaT-1(i)
			denom = 0;
			for (int i = 0; i < transColumnSize; i++) {
				denom += alphaMatrix.get(nrOfEmissions-1).getValue(i, 0);
			}
			for (int i = 0; i < transColumnSize; i++) {
				part = alphaMatrix.get(nrOfEmissions-1).getValue(i, 0);
				gammaMatrix.get(nrOfEmissions-1).addValue(i, 0, part/denom);
			}
			// Re-estimate pi
			Matrix gamma0 = gammaMatrix.get(0);
			for (int i = 0; i < transColumnSize; i++) {
				initMatrix.addValue(0, i, gamma0.getValue(i, 0));
			}
			// Re-estimate A
			double numer = 0;
			for (int i = 0; i < transColumnSize; i++) {
				for (int j = 0; j < transColumnSize; j++) {
					denom = 0;
					numer = 0;
					for (int t = 0; t < nrOfEmissions-1; t++) {
						numer += diGammaMatrix.get(t).getValue(i, j);
						denom += gammaMatrix.get(t).getValue(i, 0);
					}
					transMatrix.addValue(i, j, numer/denom);
				}
			}
			// Re-estimate B
			for (int i = 0; i < transColumnSize; i++) {
				for (int j = 0; j < emissColumnSize; j++) {
					numer = 0;
					denom = 0;
					for (int t = 0; t < nrOfEmissions; t++) {
						if (emissSequence[t] == j) {
							numer += gammaMatrix.get(t).getValue(i, 0);
						}
						denom += gammaMatrix.get(t).getValue(i, 0);
					}
					emissMatrix.addValue(i, j, numer/denom);
				}
			}

			// Compute log(sum bullshit)
			logProb = 0;
			for(int i = 0; i < nrOfEmissions; i++) {
				//System.out.println("Jkorv: " + cScaleVector[i]);
				logProb += Math.log(cScaleVector[i]);
			}
			logProb = -logProb;
			// To iterate or not to iterate wtf mayne
			iters++;
			System.out.print(transMatrix.getRowLength() + " " + transMatrix.getColumnLength());
			for (int i = 0; i < transMatrix.getRowLength(); i++) {
				for (int j = 0; j < transMatrix.getColumnLength(); j++) {
					System.out.print(" " + transMatrix.getValue(i, j));
				}
			}
			System.out.println();
			System.out.println("-----------------------------------------------------");
		} 
		System.out.println("SLUTGILTIG SVAR: ");
		System.out.print(emissMatrix.getRowLength() + " " + emissMatrix.getColumnLength());
		for (int i = 0; i < emissMatrix.getRowLength(); i++) {
			for (int j = 0; j < emissMatrix.getColumnLength(); j++) {
				System.out.print(" " + emissMatrix.getValue(i, j));
			}
		}
		System.out.println();
	}

	private static void printList(ArrayList<Matrix> list) {
		for (Matrix m : list) {
			m.print();
		}
	}

	private static void printHash(HashMap<Integer, Matrix> map) {
		Iterator it = map.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry pair = (Map.Entry)it.next();
			Matrix m = (Matrix)pair.getValue();
			m.print();
		}
	}
}