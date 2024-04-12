package beerRegister;

import java.io.Serializable;


public class Beer implements Serializable
{
	String name;
	String style;
	double strength;

	public Beer (String n, String s, double st)
	{
		name = n;
		style = s;
		strength = st;
	}
	
	public String toString()
	{
		return name + " " + style + " " + strength;
	}
}
