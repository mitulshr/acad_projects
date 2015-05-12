import java.io.*;
//import java.lang.reflect.Array;
import java.util.*;

public class inputData 
{
	private Scanner sc;
	ArrayList<sentence> KBrules = new ArrayList<sentence>();
	String[] queryT = new String[3];
	
	public void openFile()
	{
		try
		{
			sc = new Scanner (new File("input.txt")); 
		}
		catch(Exception e)
		{
			System.out.println("Error in opening File");
		}
	}
	public void readFile()
	{
		String query = sc.next();
		String numberOfstatements = sc.next();
		ArrayList<String> LHS = new ArrayList<String>();
		ArrayList<String> RHS = new ArrayList<String>();
		
		System.out.println("Query: " + query);
		
		queryT = tokenizeAtomic.tokenize(query);
		System.out.println("Tokenized Query\n" + "Predicate: " + queryT[0] + "\tArgument 1: " + queryT[1] + "\tArgument 2: " + queryT[2]);
		System.out.println("Number:" + numberOfstatements);
		
		while (sc.hasNext())
		{			
			String data = sc.next();
			boolean b;
			b = data.indexOf("=>") > 0;
			if(b)
			{
				String[] KB  = data.split("=>");

				LHS.add(KB[0]);
				RHS.add(KB[1]);
				sentence dummy = new sentence(KB[0],KB[1]);
				KBrules.add(dummy);
			}
			else
			{
				RHS.add(data);
				sentence dummy = new sentence(null,data);
				KBrules.add(dummy);
			}
		}
		System.out.println("\nLHS : \n");
		for(int i=0; i < LHS.size();i++)
			System.out.println(LHS.get(i));

		System.out.println("\nRHS : \n");
		for(int i=0; i < RHS.size();i++)	
			System.out.println(RHS.get(i));

		System.out.println("\nFrom Class\n");

		System.out.println(KBrules.size());
		for(int i=0; i < KBrules.size();i++)
		{
			System.out.println("\nSentence number: " + i + "\n");
			sentence.printFOL(KBrules.get(i));
		}


	}
	public void closeFile()
	{
		sc.close();
	}
    public boolean findInference()
    {
    	return inference.backChainOr(queryT,KBrules);
    }
}
