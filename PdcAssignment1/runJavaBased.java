import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class runJavaBased {
    public static void callReadMatrixAndMultiply(String filepath) {
        String data = "";
        int store_row = 0;
        int store_col = 0;
        int store_row1 = 0;
        int store_col1 = 0;
        int[][] dynamicArray = null;
        int[][] dynamicArray2 = null;
        int[][] resultArray = null;


        File myfile = new File(filepath);
        try {
            try (Scanner myscanner = new Scanner(myfile)) {
                for (int i = 0; i < 2; i++) {
                    if (myscanner.hasNextLine()) {
                        data = myscanner.nextLine();
                        // System.out.println(data);
                    }
                }
                if (myscanner.hasNextLine()) {
                    data = myscanner.nextLine();
                }
                String[] parts = data.split("X");
                String part1 = parts[0];
                String part2 = parts[1];
                System.out.println(part1);
                System.out.println(part2);// have read the first matrix dimensions till now
                store_row = Integer.parseInt(part1);
                store_col = Integer.parseInt(part2);
                int count = 0;

                dynamicArray = new int[store_row][store_col];
                int j = 0;
                myscanner.useDelimiter(",|\\n");
                for (int i = 0; i < store_row; i++) {
                    j = 0;
                    while (myscanner.hasNext() && j < store_col) {
                        count++;
                        if (myscanner.hasNextInt()) {
                            int intValue = myscanner.nextInt();
                            dynamicArray[i][j] = intValue;
                            System.out.println("Read integer: " + intValue);
                        } else {
                            System.out.println("Invalid input: " + myscanner.next());
                        }
                        j++;
                    }
                }

                System.out.println("Count is " + count);

                //------------------------------------------
                Scanner myNewScanner = new Scanner(myfile);
                for (int i = 0; i < store_row + 3; i++) {
                    if (myNewScanner.hasNextLine()) {
                        myNewScanner.nextLine();
                    } else {
                        System.out.println("File has fewer lines than specified to skip.");
                        return;
                    }
                }

                if (myNewScanner.hasNextLine()) {
                    data = myNewScanner.nextLine();
                }
                String[] part = data.split("X");
                String par1 = part[0];
                String par2 = part[1];
                System.out.println(par1);
                System.out.println(par2);// have read the first matrix dimensions till now
                store_row1 = Integer.parseInt(par1);
                store_col1 = Integer.parseInt(par2);
                count = 0;

                dynamicArray2 = new int[store_row][store_col];
                j = 0;
                myNewScanner.useDelimiter(",|\\n");
                for (int i = 0; i < store_row; i++) {
                    j = 0;
                    while (myNewScanner.hasNext() && j < store_col) {
                        if (myNewScanner.hasNextInt()) {
                            int intValue = myNewScanner.nextInt();
                            dynamicArray2[i][j] = intValue;
                            System.out.println("Read integer: " + intValue);
                            count++;
                        } else if (myNewScanner.hasNext("\n")) {
                            myNewScanner.nextLine();
                            break;
                        } else {
                            System.out.println("Invalid input: " + myNewScanner.next());
                        }
                        j++;
                    }
                }

                System.out.println("Count is " + count);
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());
        }
        resultArray = new int[store_row][store_col1];

        if(store_row1==store_col)
        {
        for(int i=0;i<store_row;i++)
        {
            for(int j=0;j<store_col1;j++)
            { 
                int sum=0;
                for(int k=0;k<store_col;k++)
                {
                    sum+=dynamicArray[i][k]*dynamicArray2[k][j];
                }
                resultArray[i][j]=sum;
            }
        }
        System.out.println("Result is \n");

        for (int i = 0; i < store_row; i++) {
            for (int j = 0; j < store_col1; j++) {
                System.out.print(resultArray[i][j] + " ");
            }
            System.out.println(); 
        }
        
    }

    }

    public static void main(String[] args) {
        String filepath = "/home/hamad/Desktop/PdcAssignment1/inputFIle.txt";
        callReadMatrixAndMultiply(filepath);
    }
}
