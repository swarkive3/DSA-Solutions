/*
 * Contest: Master
 * Challenge: Java Regex 2 - Duplicate Words
 * Language: java
 * Score: 0.0
 */

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DuplicateWords {

    public static void main(String[] args) {

        // Regex to match a word boundary, a word (captured), followed by 
        // one or more occurrences of non-word chars and the SAME word.
        String regex = "\\b(\\w+)(?:\\W+\\1\\b)+";
        
        // Compile with CASE_INSENSITIVE flag so 'Hello' matches 'hello'
        Pattern p = Pattern.compile(regex, Pattern.CASE_INSENSITIVE);

        Scanner in = new Scanner(System.in);
        int numSentences = Integer.parseInt(in.nextLine());
        
        while (numSentences-- > 0) {
            String input = in.nextLine();
            
            Matcher m = p.matcher(input);
            
            // Check for subsequences of input that match the compiled pattern
            while (m.find()) {
                // Replace the entire match (original + duplicates) with just the first word (Group 1)
                // m.group() is the whole match. "$1" refers to the first captured group.
                input = input.replaceAll(m.group(), m.group(1));
            }
            
            // Prints the modified sentence.
            System.out.println(input);
        }
        
        in.close();
    }
}
