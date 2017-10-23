/**
 * Authors: Nedo Skobalj and Jacob Hallman
 * Class used for describing a matrix.
 */

public class Matrix {
	private double[][] matrix;

	public Matrix(int rows, int columns) {
		matrix = new double[rows][columns];
	}

	public int getRowLength() {
		return matrix.length;
	}

	public int getColumnLength() {
		return matrix[0].length;
	}

	public double getValue(int row, int column) {
		return matrix[row][column];
	}
	/**
	 * Get all values in a column
	 * @param  column index of column to get
	 * @return        values in column as a array.
	 */
	public Matrix getColumn(int column) {
		Matrix ret = new Matrix(matrix.length, 1);
		for (int i = 0; i < matrix.length; i++) {
			ret.addValue(i, 0, matrix[i][column]);
		}
		return ret;
	}
	
	public void addValue(int row, int column, double value) {
		matrix[row][column] = value;
	}

	public Matrix transpose() {
		Matrix ret = new Matrix(matrix[0].length, matrix.length);
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[0].length ; j++) {
				ret.addValue(j, i, matrix[i][j]);
			}
		}
		return ret;
	}

	public double sum() {
		double ret = 0;
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[0].length; j++) {
				ret += matrix[i][j];
			}
		}
		return ret;
	}

	public Matrix scalarMultiply(double value) {
		Matrix ret = new Matrix(matrix.length, matrix[0].length);
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[0].length; j++) {
				ret.addValue(i, j, matrix[i][j]*value);
			}
		}
		return ret;
	}
	/**
	 * return max value of a matrix and the max values row index.
	 * first return value is max, second value is row index. 
	 */
	public double[] max() {
		double[] ret = {Double.NEGATIVE_INFINITY, -1};
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[0].length; j++) {
				if (matrix[i][j] > ret[0]) {
					ret[0] = matrix[i][j];
					ret[1] = i; // Check if right
				}
			}
		}
		return ret;
	}

	public int maxValueRow() {
		int ret = -1;
		double max = Double.NEGATIVE_INFINITY;
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[0].length; j++) {
				if (matrix[i][j] > max) {
					ret = i;
					max = matrix[i][j];
				}
			}
		}
		return ret;
	}

	public Matrix elementWiseMultiply(Matrix rightMatrix) {
		int matrixRowLength = matrix.length;
		int rightMatrixColumnLength = rightMatrix.getColumnLength();
		int matrixColumnLength = matrix[0].length;
		int rightMatrixRowLength = rightMatrix.getRowLength();
		if (matrixRowLength != rightMatrixRowLength) {
			throw new IllegalArgumentException("Number of rows of matrices did not match");
		}
		if (matrixColumnLength != 1 || rightMatrixColumnLength != 1) {
			throw new IllegalArgumentException("Number of colums more than one");
		}
		Matrix ret = new Matrix(matrixRowLength, matrixColumnLength);
		double partResult = 0;
		for (int i = 0; i < matrixRowLength; i++) {
			partResult = matrix[i][0]*rightMatrix.getValue(i, 0);
			ret.addValue(i, 0, partResult);
		}
		return ret;
	}

	public Matrix multiplyMatrix(Matrix rightMatrix) {
		int matrixRowLength = matrix.length;
		int rightMatrixColumnLength = rightMatrix.getColumnLength();
		int matrixColumnLength = matrix[0].length;
		int rightMatrixRowLength = rightMatrix.getRowLength();
		if (matrixColumnLength != rightMatrixRowLength) {
			throw new IllegalArgumentException("Rows and columns of the matrices did not match");
		}
		Matrix resultMatrix = new Matrix(matrixRowLength, rightMatrixColumnLength);
		double partResult;
		for (int i = 0; i < matrixRowLength; i++) {
			for (int j = 0; j < rightMatrixColumnLength ; j++) {
				partResult = 0;
				for (int k = 0; k < matrix[0].length ; k++) {
					partResult += (matrix[i][k] * rightMatrix.getValue(k,j));
				}
				resultMatrix.addValue(i, j, partResult);
			}
		}
		return resultMatrix;
	}

	public void print() {
		System.out.print(matrix.length + " " + matrix[0].length + " ");
		for (int i = 0; i < matrix.length ; i++) {
			for (int j = 0; j < matrix[0].length ; j++) {
				System.out.print(matrix[i][j]);
				System.out.print(" ");
			}
		}
		System.out.println();	
	}
}