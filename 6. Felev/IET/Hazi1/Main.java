package hazi2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Iterator;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;

import org.eclipse.rdf4j.query.BindingSet;
import org.eclipse.rdf4j.query.QueryLanguage;
import org.eclipse.rdf4j.query.TupleQuery;
import org.eclipse.rdf4j.query.TupleQueryResult;
import org.eclipse.rdf4j.query.Update;
import org.eclipse.rdf4j.repository.manager.RemoteRepositoryManager;
import org.eclipse.rdf4j.repository.manager.RepositoryManager;
import org.eclipse.rdf4j.repository.Repository;
import org.eclipse.rdf4j.repository.RepositoryConnection;
import org.eclipse.rdf4j.repository.RepositoryException;
import org.eclipse.rdf4j.RDF4JException;
import org.eclipse.rdf4j.common.iteration.CloseableIteration;

public class Main {
	public static ArrayList<String> find(String name)
	{
		ArrayList<String> paintings = new ArrayList<String>();
		RepositoryManager repositoryManager = new RemoteRepositoryManager( "http://localhost:8080/rdf4j-server/" );
		repositoryManager.initialize();

		Repository repository = repositoryManager.getRepository("Szep");
		
		RepositoryConnection repositoryConnection = repository.getConnection();
		
		String queryString = 	  "PREFIX ecrm: <http://erlangen-crm.org/current/>\r\n"
								+ "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\r\n"
								+ "\r\n"
								+ "SELECT ?painting {\r\n"
								+ "?actor a ecrm:E39_Actor ;\r\n"
								+ "rdfs:label ?name.\r\n"
								+ "?creation ecrm:P11_had_participant ?actor ;\r\n"
								+ "a ecrm:E65_Creation .\r\n"
								+ "?object ecrm:P12i_was_present_at ?creation ;\r\n"
								+ "a ecrm:E18_Physical_Thing .\r\n"
								+ "?object rdfs:label ?painting.\r\n"
								+ "FILTER regex(?name, \"" + name + "\", \"i\")\r\n"
								+ "}";
		
		
		TupleQuery query = repositoryConnection.prepareTupleQuery(queryString);
		TupleQueryResult result = query.evaluate();
		for(BindingSet i : result)
		{
			paintings.add(i.getValue("painting").toString());
			//System.out.println(i.getValue("painting"));
		}
		
		
		repositoryConnection.close();
		repository.shutDown();
		repositoryManager.shutDown();
		
		return paintings;
	}

	public static void update(String labelText, String name)
	{
		RepositoryManager repositoryManager = new RemoteRepositoryManager( "http://localhost:8080/rdf4j-server/" );
		repositoryManager.initialize();

		Repository repository = repositoryManager.getRepository("Szep");
		
		RepositoryConnection repositoryConnection = repository.getConnection();
		
		String updateString = 	  "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\r\n"
								+ "INSERT{ \r\n"
								+ "  ?a rdfs:label \"" + labelText + "\" ; \r\n"
								+ "}\r\n"
								+ "WHERE{ \r\n"
								+ "  ?a rdfs:label '" + name + "'\r\n"
								+ "}";
		
		Update operation = repositoryConnection.prepareUpdate(QueryLanguage.SPARQL, updateString);
		
		operation.execute();
		
		repositoryConnection.close();
		repository.shutDown();
		repositoryManager.shutDown();
	}
	
	public static void Exercise1()
	{
		update("male", "Bernardino Luini");
		update("great", "Bernardino Luini");
		
		update("male", "Ugo da Carpi");
		update("great", "Ugo da Carpi");
		
		update("male", "Hendrick Goudt");
		update("great", "Hendrick Goudt");
		
	}
	
	public static void Exercise2()
	{
		JFrame frame = new JFrame();
        frame.setBounds(100, 100, 730, 489);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);
        
        JTextField textField = new JTextField();
        textField.setBounds(35, 30, 86, 20);
        textField.setText("luini");
        frame.getContentPane().add(textField);
        textField.setColumns(10);
         
        JLabel lblName = new JLabel("Név:");
        lblName.setBounds(5, 30, 46, 14);
        frame.getContentPane().add(lblName);
        
        JLabel descriptionLabel = new JLabel("Adja meg annak a mûvésznek a nevét akinek a mûveit keresi!");
        descriptionLabel.setBounds(5, 10, 500, 14);
        frame.getContentPane().add(descriptionLabel);
        
        /*JTextArea result = new JTextArea();
        result.setBounds(5, 50, 500, 500);
        result.disable();
        frame.getContentPane().add(result);*/
        
        JTextArea result = new JTextArea(16, 58);
        result.setEditable(false); // set textArea non-editable
        JScrollPane scroll = new JScrollPane(result);
        scroll.setBounds(5, 50, 500, 500);
        scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        frame.getContentPane().add(scroll);
        //result.setText("sdfsdfsfs");
        
        JButton okButton = new JButton("Keresés");
        okButton.addActionListener(new ActionListener() {

            @Override
            public final void actionPerformed(ActionEvent e) {
            	//frame.getContentPane().remove(scrollPane);
            	String name = textField.getText();
            	ArrayList<String> res = find(name);
            	
            	result.setText("");
            	
            	String content = "";
            	for(String s : res)
            	{
            		content += (s + "\n"); 
            	}
            	
            	result.setText(content);
            	//JScrollPane s = new JScrollPane(displayList);
            	//s.setBounds(5, 50, 500, 100);
            	//frame.getContentPane().add(s);
            }
        });
        okButton.setBounds(130, 30, 100, 20);
        frame.getContentPane().add(okButton);
        
        frame.setVisible(true);
	}
	
	public static void main(String [] args)
	{
		Exercise1();
		Exercise2();
	}
}
