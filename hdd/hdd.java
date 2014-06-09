package sdtl_project;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.math.BigInteger;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
                              

            /*Duplicate files are listed using MD5 algorithm...
               it converts files into hex code and depending on that the duplicated files are listed..
                As per the user choice file is deleted or not.*/

public class FindDuplicates {
    private static MessageDigest md;         //MD5
    static {
        try {
            md = MessageDigest.getInstance("SHA-1");       //SHA is a secure hash function..
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Error in algo", e);
        }
    }

    public static void check_subdirectory(Map<String, List<String>> lists, File directory) {
        for (File child : directory.listFiles()) {
            if (child.isDirectory()) {
                check_subdirectory(lists, child);
            } else {
                try {
                    FileInputStream fin = new FileInputStream(child);
                    byte data[] = new byte[(int) child.length()];
                    fin.read(data);
                    fin.close();
                    String hash = new BigInteger(1, md.digest(data)).toString(16);
                    List<String> mylist = lists.get(hash);
                    if (mylist == null) {
                        mylist = new LinkedList<String>();
                        lists.put(hash, mylist);
                    }
                    mylist.add(child.getPath());
                } catch (IOException e) {
                    throw new RuntimeException("Error in reading path " + child.getPath(), e);
                }
            }
        }
    }

    public static void main(String[] args) {
    	String[] drivearray = new String[]{"C","D","E","F"};
    	int array_size=drivearray.length;
        
    	//For each directory find the duplicate files.......
    	
    	//Here i have considered just one directory as hard disk contents are large...
    	//for checking if code is properly working or not its better to consider smaller directory...
    	
    	
    	String name_drive=new String("E:/sample");
        if (name_drive.length() < 1) {
            System.out.println("Enter a valid path");
            return;
        }
        File folder = new File("E:/sample");
        if (!folder.isDirectory()) {
            System.out.println("Directory does not exists");
            return;
        }
        Map<String, List<String>> contents = new HashMap<String, List<String>>();
        FindDuplicates.check_subdirectory(contents, folder);
        
        System.out.print("*****************DUPLICATE FILES ARE:**************");
        for (List<String> final_list : contents.values()) {
            if (final_list.size() > 1) {
                System.out.println("--");
                for (String dup_file : final_list) 
                {
                    System.out.println(dup_file);
                }
            }
        }
        System.out.println("Do you want to delete any duplicate files:1)YES 2)NO");
        Scanner n1=new Scanner(System.in);
        int ans=n1.nextInt();
        if(ans==1)
        {
         for (List<String> final_list : contents.values()) {
            if (final_list.size() > 1) {
                System.out.println("--");
                for (String dup_file : final_list) 
                {
                    System.out.println(dup_file);
                    
                    
                    System.out.print("DO YOU WANT DELETE THE DUPLICATE FILE 1)NO 2)YES\n");
                    int ans1=n1.nextInt();
                    if(ans1==2)
                    {
                    File file1=new File(dup_file);
                    file1.delete();
                    System.out.println("File Successfully Deleted");
                    }
           
                }
            }
        }
        }
        System.out.println("END");
       
        	
        }
        
        
        
    }