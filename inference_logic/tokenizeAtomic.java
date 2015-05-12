
public class tokenizeAtomic 

{

	public static String[] tokenize(String clause)
	{

		String[] tokenizedclause = new String[3];
		String[] predicate = clause.split("\\(");
		tokenizedclause[0] = predicate[0];
		String arguments = predicate[1];

		boolean b;
		b = arguments.indexOf(",") > 0;
		if(b)
		{
			String[] argument1  = arguments.split(",");
			tokenizedclause[1] = argument1[0];			
			String[] argument2 = argument1[1].split("\\)");
			tokenizedclause[2] = argument2[0];
		}
		else
		{
			String[] argument1  = arguments.split("\\)");
			tokenizedclause[1] = argument1[0];
			tokenizedclause[2] = null;
		}   

		return tokenizedclause;
	}

}
