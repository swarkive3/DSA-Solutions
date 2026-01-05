/*
 * Contest: Master
 * Challenge: Tag Content Extractor
 * Language: java
 * Score: 1.0
 */

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    public static void main(String[] args){
        
        Scanner in = new Scanner(System.in);
        // Parse the number of test cases
        int testCases = Integer.parseInt(in.nextLine());
        
        while(testCases > 0){
            String line = in.nextLine();
            
            boolean matchFound = false;
            
            // Compile the Regex Pattern
            // <(.+?)>  : Start tag (Group 1)
            // ([^<]+)  : Content with no nested tags (Group 2)
            // </\\1>   : End tag matching Group 1
            Pattern r = Pattern.compile("<(.+?)>([^<]+)</\\1>");
            Matcher m = r.matcher(line);
            
            // Find all subsequences in the line that match the pattern
            while (m.find()) {
                // Print the content (Group 2)
                System.out.println(m.group(2));
                matchFound = true;
            }
            
            // If no valid tags were found in the line, print "None"
            if (!matchFound) {
                System.out.println("None");
            }
            
            testCases--;
        }
        in.close();
    }
}


