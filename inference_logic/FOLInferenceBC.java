import java.io.*;
public class FOLInferenceBC 
{

	public static void main(String[] args) 

	{
		inputData r = new inputData();
		r.openFile();
		r.readFile();
		r.closeFile();
		PrintWriter writer = null;
		try
		{
			writer = new PrintWriter("output.txt", "UTF-8");
		}
		catch(Exception e)
		{
			System.out.println("Error in opening file");
		}
		boolean b = r.findInference();
		if(b)
		        writer.println("TRUE");
		else
		        writer.println("FALSE");
		writer.close();
		
	}

}
