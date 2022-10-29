package pao.homework;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in); // presupun ca intai scrie lungimea si dupa numele fisierului
        int x = input.nextInt();
        String fileName = input.nextLine();
        System.out.println(getForLengthX(fileName, x));
    }

    public static HashMap<Integer, LinkedList<String>> separateWords(String fileName) {
        File file = new File(fileName);
        Scanner inputFile = null;

        try {
            inputFile = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        HashMap<Integer, LinkedList<String>> map = new HashMap<>();
        while(inputFile.hasNext()) {
            String word = inputFile.next().split("[!?.,()-]")[0];
            int length = word.length();

            if(map.get(length) != null) {
                LinkedList<String> stringList = map.get(length);
                stringList.add(word);
                map.put(length, stringList);
            } else {
                LinkedList<String> strings = new LinkedList<>();
                strings.add(word);
                map.put(length, strings);
            }
        }

        return map;
    }

    public static List<String> getForLengthX(String fileName, int x) {
        return separateWords(fileName).get(x);
    }
}