//Group:R3A
//Assignment No2: BIRTHDAY PARADOX

/*
 In probability theory, the birthday paradox concerns the probability that, in a set of n randomly chosen people, 
 some pair of them will have the same birthday. By the pigeonhole principle, the probability reaches 100% when the
 number of people reaches 366. 
 However, 99.9% probability is reached with just 70 people, and 50% probability with 23 people.
 
 We take input of number of people and perform 1000 trials on them and find the probability when atleast a pair
 will have same birthday.
 
 */

package birthday_paradox;

import java.util.HashSet;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

 
public class birthdayParadox {
 
	/*
	    randGen object of Random class is used to generate random birthdays, using the function nextInt(365),
	    which generates a number from 1 to 365.
	 */
	
    private static final Random randGen = new Random();
 
    static float generate(int np, int nt) {
        int n = 0;
        
        for(int i = 0; i < nt; i++)
        {
            if(check(np)) 
            {
            	n++;
           	}
        }
        return (float)n/nt;
    }
 
    /*
     	HashSet extends AbstractSet and implements the set interface. It creates a collection that uses a
     	hash table for storage. A hash table stores information using hashing. The information content of a
     	key is used to determine a unique value called hashcode. The hashcode is then used as an index at 
     	which data associated with the key is stored.
     	
     	We have used to functions: 
     	contains(): To check if the date is present in the set.
     	add(): To add the date in the HashSet, if not already present.
     	
     */
    
    static boolean check(int np) {
        
    	Set<Integer> birthdays = new HashSet<Integer>();
        
        for (int i = 0; i < np; i++) 
        {
            int day = randGen.nextInt(365);
            
            if (birthdays.contains(day)) 
            {
            	return true;
            }
            birthdays.add(day);
        }
        return false;
    }
 
    public static void main(String[] args) {
        int no,ch;
        float ans;
        
    	Scanner in=new Scanner(System.in);
    	
    	System.out.println("\n\n\tBIRTHDAY PARADOX");
    	
    	do
    	{
    		
    		System.out.println("\n\tEnter number of people: ");
    		no=in.nextInt();
    	
    		ans=generate(no,1000);
    		ans=ans*100;
    	
    		System.out.println("\nProbability is: "+ans+"%");
    		System.out.println("\n 1.Continue \n 0. exit");
   		 ch=in.nextInt();
    	}while(ch!=0);
    }
}