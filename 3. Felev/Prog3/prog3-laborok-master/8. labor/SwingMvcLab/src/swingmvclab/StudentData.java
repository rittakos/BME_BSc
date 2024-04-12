package swingmvclab;

import java.util.ArrayList;
import java.util.List;
import javax.swing.event.TableModelListener;
import javax.swing.table.AbstractTableModel;

/*
 * A hallgatók adatait tároló osztály.
 */
public class StudentData extends AbstractTableModel{

    /*
     * Ez a tagváltozó tárolja a hallgatói adatokat.
     * NE MÓDOSÍTSD!
     */
    List<Student> students = new ArrayList<>();

	@Override
	public int getRowCount() {
		return students.size();
	}

	@Override
	public int getColumnCount() {
		return 4;
	}

	@Override
	public Object getValueAt(int i, int i1) {
		Student student = students.get(i);
		switch(i1) {
			case 0: return student.getName();
			case 1: return student.getNeptun();
			case 2: return student.hasSignature();
			default: return student.getGrade();
		}
	}

	@Override
	public void addTableModelListener(TableModelListener tl) {
		super.addTableModelListener(tl); //To change body of generated methods, choose Tools | Templates.
	}
	
	@Override
	public String getColumnName(int i)
	{
		switch(i)
		{
			case 0: return "Név";
			case 1: return "Neptun";
			case 2: return "Aláírás";
			default: return "Jegy";
		}
	}
    
	@Override
	public Class<?> getColumnClass(int i)
	{
		Student s=students.get(0);
		switch(i)
		{
			case 0: return String.class;
			case 1: return String.class;
			case 2: return Boolean.class;
			default: return Integer.class;
		}
	}

	@Override
	public boolean isCellEditable(int i, int i1)
	{
		boolean[] b={false,false,true,true};
		return (i1<getColumnCount() && i1>=0)?b[i1]:false;
	}
	
	@Override
	public void setValueAt(Object o, int i, int i1)
	{
		Student s=students.get(i);
		if(i1>=2 && i1<=3)
		{
			switch(i1)
			{	
				case 2:
					s.setSignature((Boolean)o);
					break;
				default: 
					s.setGrade((Integer)o);
					break;
			}
			students.set(i, s);
			this.fireTableRowsUpdated(i, i);
		}
	}

	public void addStudent(String name, String neptun)
	{
		students.add(new Student(name, neptun, Boolean.FALSE, 0));
		this.fireTableDataChanged();
	}
}
