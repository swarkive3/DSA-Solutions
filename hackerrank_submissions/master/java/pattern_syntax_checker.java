/*
 * Contest: Master
 * Challenge: Pattern Syntax Checker
 * Language: java
 * Score: 1.0
 */

import java.util.Scanner;
import java.util.regex.*;

public class Solution {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int testCases = Integer.parseInt(in.nextLine());
        
        while(testCases > 0){
            String pattern = in.nextLine();
            
            try {
                // Attempt to compile the pattern
                Pattern.compile(pattern);
                System.out.println("Valid");
            } catch (PatternSyntaxException e) {
                // If compilation fails, the pattern syntax is broken
                System.out.println("Invalid");
            }
            
            testCases--;
        }
        in.close();
    }
}



