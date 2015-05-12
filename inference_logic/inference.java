import java.util.ArrayList;

public class inference 
{

	public static String variable = new String();
	public static String theta = "";
	public static boolean orResult = true;
	public static boolean backChainOr(String[] query, ArrayList<sentence> KB)
	{
		for(int i =0; i < KB.size(); i++)
		{
			if(query[0].equals(KB.get(i).RHS[0]))
			{
				System.out.println("Found one shit!!");
				if((checkArgument(query[1],KB.get(i).RHS[1])) && (checkArgument(query[2],KB.get(i).RHS[2])))
				{
					KB.get(i).RHS[1] = query[1];
					KB.get(i).RHS[2] = query[2];

					System.out.println("\nInside Inference: " + KB.get(i).RHS[0]+ "  Arguments: " + KB.get(i).RHS[1] + "," + KB.get(i).RHS[2] );

					orResult = backChainAnd(KB,KB.get(i).LHS);
					if(orResult == false && i < KB.size())
						continue;
					else
						return orResult;
				}
				else
					continue;

			}

		}
		return false;
	}

	public static boolean backChainAnd(ArrayList<sentence> KB, String LHS)
	{
		boolean result1, result2;
		String[] dividedLHS;
		String[] newQuery = new String[3];
		String restOfLHS = "";
		if(LHS == null)
			return true;
		else
		{
			boolean b;
			b = LHS.indexOf("&") > 0;
			if(b)
			{
				dividedLHS = LHS.split("&");
				newQuery = tokenizeAtomic.tokenize(dividedLHS[0]); 
				for(int i =1 ; i < dividedLHS.length ; i++ )
				{
					if(dividedLHS.length > 1)						
					{
						if(i ==1)
							restOfLHS += dividedLHS[i];
						else
							restOfLHS += "&" + dividedLHS[i];
					}

					else
						restOfLHS += dividedLHS[i];	
				}	
			}
			else
			{
				newQuery = tokenizeAtomic.tokenize(LHS);
				restOfLHS = null;
			}
			System.out.println("\nNew Query\t" + newQuery[0] + "," + newQuery[1] + "," + newQuery[2]);
			result1 = backChainOr(subs(newQuery),KB);
			System.out.println("\nRest Of LHS: " + restOfLHS);
			result2 = backChainAnd(KB, restOfLHS);
			return (result1 & result2);
		}
		//return true;	

	}

	public static String[] subs(String[] query)
	{
		if(query[1] != null && !(theta.equals("")))
		{
			String first = "" + query[1].charAt(0);
			if(first.equals(first.toLowerCase()))
			{
				query[1] = theta;
			}
		}

		if(query[2] != null && !(theta.equals("")))
		{
			String first = "" + query[2].charAt(0);
			if(first.equals(first.toLowerCase()))
			{
				query[2] = theta;
			}
		}

		System.out.println("returning from subs: " + query[1] + "," + query[2] );
		return query;
	}
	public static boolean checkArgument(String query, String argument)
	{	
		String firstQuery = new String();
		String firstArgum = new String();
		if(query != null)
			firstQuery  = "" + query.charAt(0);
		if(argument != null)
			firstArgum  = "" + argument.charAt(0);	
		if(query == null && argument == null)
			return true;
		else if(query == null && argument != null)
			return false;
		else if(query != null && argument == null)
			return false;
		else if(query.equals(argument))
			return true;
		else if(query != null && (firstQuery.equals(firstQuery.toLowerCase()))) 			
		{
			variable =  query;
			theta = argument; 
			System.out.println("Check Argument Value: of theta" + theta);
			return true;
		}
		else if(argument != null && (firstArgum.equals(firstArgum.toLowerCase()))) 			
		{
			variable =  argument;
			theta = query; 
			System.out.println("Check Argument Value: of theta" + theta);
			return true;
		}
		else
		{
			System.out.println("Could find match for  " + query + argument);
			return false;
		}

	}


}
