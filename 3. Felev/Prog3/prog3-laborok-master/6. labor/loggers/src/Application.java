import java.io.FileNotFoundException;

public class Application {
	public static void main(String[] args) throws FileNotFoundException 
	{
		PercentCounter pc=new PercentCounter();
		pc.register(new StdOutLogger());
		pc.register(new FileLogger("observer.txt"));
		pc.run();
	}
}
