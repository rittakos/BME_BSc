package junittest;

public class Calculator {
	public double multiply(double a, double b) {
		return a * b;
	}
	
	public double divide(double a, double b) throws IllegalArgumentException {
		if(b == 0) {
			throw new IllegalArgumentException();
		}
		return a / b;
	}
} 
