package caesarcode;

public class CaesarCode 
{
	public static String caesarCode(String input, char offset)
	{
		String s = "";
		input=input.toUpperCase();
		offset=Character.toUpperCase(offset);
		int numericOffset=(int)offset - (int)'A';
		int len = input.length();
		for(int x = 0; x < len; x++)
		{
			char c = (char)(input.charAt(x) + numericOffset);
			if (c > 'Z')
				s += (char)(input.charAt(x) - (26-numericOffset));
			else
				s += (char)(input.charAt(x) + numericOffset);
		}
		return s;
	}
	
	public static String caesarDeCode(String input, char offset)
	{
		String s = "";
		input=input.toUpperCase();
		offset=Character.toUpperCase(offset);
		int numericOffset=(int)offset - (int)'A';
		int len = input.length();
		for(int x = 0; x < len; x++)
		{
			char c = (char)(input.charAt(x) - numericOffset);
			if (c < 'A')
				s += (char)(input.charAt(x) + (26-numericOffset));
			else
				s += (char)(input.charAt(x) - numericOffset);
		}
		return s;
	}
}
