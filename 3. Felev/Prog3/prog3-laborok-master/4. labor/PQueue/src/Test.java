
public class Test {
	public static void main(String args[])
	{
		PQueue<String> q=new PQueue<>();
		q.push("alma");
		q.push("körte");
		q.push("kiwi");
		for(String s: q)
		{
			System.out.println(s);
		}
		System.out.println(q.size());
		System.out.println(q.pop());
		System.out.println(q.pop());	
		System.out.println(q.pop());
//		System.out.println(q.pop());//exceptiont dobna ami nekünk most jó

		PQueue<Integer> s = new PQueue<>();
		s.push(1); s.push(2); s.push(3); s.push(4);
		for (Integer i : s) {
			System.out.println(i);
		}

	}
	
}
