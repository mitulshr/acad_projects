
public class sentence 
{
	String [] RHS = new String[3];
	String LHS = new String();

	sentence(String ruleLHS, String ruleRHS)
	{
		LHS = ruleLHS;
		RHS = tokenizeAtomic.tokenize(ruleRHS);
	}



	public static void printFOL(sentence forPrint)
	{
		if(forPrint.LHS == null)
		{
			System.out.println("LHS: Atomic\nRHS: ");
			for(int i =0; i < 3; i++)
				System.out.println(forPrint.RHS[i]);
		}
		else
		{
			System.out.println("LHS: \n" + forPrint.LHS + "\nRHS:");
			for(int i =0; i < 3; i++)
				System.out.println(forPrint.RHS[i]);
		}

	}
}
