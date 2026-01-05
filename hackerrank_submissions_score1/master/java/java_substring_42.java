/*
 * Contest: Master
 * Challenge: Java Substring
 * Language: java
 * Score: 1.0
 */

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String S = in.next();
        int start = in.nextInt();
        int end = in.nextInt();
        
        // The substring method extracts from 'start' (inclusive) to 'end' (exclusive)
        System.out.println(S.substring(start, end));
    }
}
