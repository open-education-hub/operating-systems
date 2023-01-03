/* SPDX-License-Identifier: BSD-3-Clause */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public final class FileOperations {
    /**
     * The file to be read or written.
     */
    public static final String FILE_NAME = "file.txt";

    /**
     * Reads the contents of the file and prints it to standard output.
     *
     * @param fileName the name of the file to read
     */
    private static void readFile(final String fileName) {
        try {
            // `file` is a handler to the file.
            File file = new File(fileName);
            Scanner scanner = new Scanner(file);

            String content = scanner.nextLine();
            System.out.println("File contents are: " + content);

            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    /**
     * Overwrites the contents of the file with the string "Java was here!".
     *
     * @param fileName the name of the file to overwrite
     */
    private static void writeFile(final String fileName) {
        try {
            // `file` is a handler to the file.
            File file = new File(fileName);
            FileWriter writer = new FileWriter(file);

            writer.write("Java was here!");
            System.out.println("Wrote new data to file");

            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    /**
     * The main method. Reads the contents of the file, overwrites it and then
     * rereads the file.
     *
     * @param args command line arguments - unused
     */
    public static void main(final String[] args) {
        readFile(FILE_NAME);
        writeFile(FILE_NAME);
        readFile(FILE_NAME);
    }

    private FileOperations() { }
}
