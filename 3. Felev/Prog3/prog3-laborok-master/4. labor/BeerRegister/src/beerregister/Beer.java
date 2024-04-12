package beerregister;

import java.io.Serializable;

public class Beer implements Serializable{
	String name, style;
	double strength;

	public Beer(String name, String style, double strength) 
	{
		this.name=name;
		this.style=style;
		this.strength=strength;
	}
	
	public String toString()
	{
		return name + " " + style + " " + strength;		
	}
}
