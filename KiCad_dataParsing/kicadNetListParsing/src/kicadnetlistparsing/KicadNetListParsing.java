/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package kicadnetlistparsing;

import java.io.*;
import java.util.*;

/**
 *
 * @author Administrator
 */
class Label2Mem {

    String label;
    Integer adr;

    Label2Mem(String label) {
        this.label = label;
        this.adr = -1;
    }

}

public class KicadNetListParsing {

    static Scanner in = new Scanner(System.in);
    static FileReader fileReader;
    static BufferedReader bufferedReader;
    static ArrayList<Integer> adrList_taken = new ArrayList<>();
    static ArrayList<Label2Mem> l2mList = new ArrayList<>();
    static Label2Mem l2m;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
// The name of the file to open.

        String fileName;
        System.out.println("type the file you KiCad.net file you wish to use.");
        fileName = in.next();

        System.out.println("type the label2Ignore file you wish to use.");
        String ignoreFileName = in.next();
        ArrayList<String> ignoreList = labels2Ignore(ignoreFileName);

        ArrayList<String> strList = scanFile(fileName, ignoreList);

        for (int i = 0; i < strList.size(); i++) {
            //System.out.println(i);
            l2m = new Label2Mem(strList.get(i));
            l2mList.add(l2m);
        }

        int count = 0;
        for (int i = 0; i < l2mList.size(); i++) {
            //System.out.println(labelList.get(i) + "; " + (i+1));
            if (l2mList.get(i).label != null) {
                count++;
                //System.out.println(l2mList.get(i).label + "\t" + (i + 1));
            }
        }

        System.out.println("total digital i/o in use " + count);
        
        
        int i = 0, i_adr = 0;
        while (i < count) {
            if (l2mList.get(i).label != null) {
                //System.out.println(l2mList.get(i).label);
                changeAdr(i, i_adr);
                i_adr++;
            }

            i++;
        }
        System.out.println("//------------COPY TEXT BELOW------------");
        System.out.println();
        print2MemMap("80080000");
        System.out.println();    
        System.out.println("//------------COPY TEXT ABOVE------------");


    }

    static ArrayList<String> scanFile(String fileName, ArrayList<String> ignoreList) {
        // This will reference one line at a time
        String line = null;
        ArrayList<String> strList = new ArrayList<>();
        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader
                    = new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader
                    = new BufferedReader(fileReader);

            String strTemp = "not initalized";
            while ((line = bufferedReader.readLine()) != null) {

                if (line.contains("(net (code ") && !line.contains("Net-")) {
                    strTemp = String.valueOf(line);
                    break;
                }
            }

            while ((line = bufferedReader.readLine()) != null) {

                if (line.contains("(net (code ") && !line.contains("Net-")) {
                    strTemp = String.valueOf(line);

                } else if (line.contains("(node") && line.contains("(ref U1)")) {

                    //pin
                    int index = line.indexOf("pin ") + 4;//"pin " has 4 characters
                    line = line.replace(')', '\0');
                    line = String.valueOf(line.subSequence(index, line.length()));
                    line = line.replaceAll("[^0-9.]", "");
                    line = line.trim();

                    Integer pin = 0;
                    if (!ignoreList.contains(line)) {
                        pin = Integer.valueOf(line);
                    }
                    //pin equals to 0 if on ignore list

                    //label
                    index = strTemp.indexOf("name ") + 5;//"name " has 5 characters
                    strTemp = strTemp.replace(')', '\0');

                    String label = String.valueOf(strTemp.subSequence(index, strTemp.length() - 1));
                    //labelList.add(pin - 1, label);
                    if (!ignoreList.contains(label) && pin != 0) {
                        //strList[pin - 1] = new String(label + (pin-1));
                        strList.add(stripWeirdChar(label+"_p"+(pin-1)));
                    }
                }
            }

//            for (int i = 0; i < 100; i++) {
//                //System.out.println(labelList.get(i) + "; " + (i+1));
//                if(strList[i] != "")
//                    System.out.println(strList[i]);
//            }
            // Always close files.
            bufferedReader.close();
        } catch (FileNotFoundException ex) {
            System.out.println(
                    "Unable to open file '"
                    + fileName + "'");
        } catch (IOException ex) {
            System.out.println(
                    "Error reading file '"
                    + fileName + "'");
            // Or we could just do this: 
            // ex.printStackTrace();
        }

        return strList;
    }

    static ArrayList<String> labels2Ignore(String fileName) {

        // This will reference one line at a time
        String line = null;
        ArrayList<String> ignoreList = null;
        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            ignoreList = new ArrayList<>();
            while ((line = bufferedReader.readLine()) != null) {
                ignoreList.add(line);
            }

            // Always close files.
            bufferedReader.close();

        } catch (FileNotFoundException ex) {
            System.out.println(
                    "Unable to open file '"
                    + fileName + "'");
            ignoreList.add("");
        } catch (IOException ex) {
            System.out.println(
                    "Error reading file '"
                    + fileName + "'");
            // Or we could just do this: 
            // ex.printStackTrace();
            ignoreList.add("");
        }
//        System.out.println("IGNORE!!!");
//        for (int i = 0; i < ignoreList.size(); i++) {
//            System.out.println(ignoreList.get(i));
//        }
//
//        System.out.println("IGNORE!!!");
        return ignoreList;
    }

    static int changeAdr(int l2mIndex, int adr) {
        if (adrAvailable(adr) == 0) {
            return 0;
        } else {
            // remove current address
            adrList_taken.remove(l2mList.get(l2mIndex).adr);
            // add new address to taken list
            adrList_taken.add(adr);
            // add new address to object
            l2mList.get(l2mIndex).adr = adr;
        }
        return 1;
    }

    // 1 - available
    // 0 - not
    static int adrAvailable(int adr) {
        if (adrList_taken.contains(adr)) {
            return 0;
        } else {
            return 1;
        }
    }

    static void print2MemMap(String baseAdrHex) {
        Long baseAdrInt = Long.parseLong(baseAdrHex, 16);
        //baseAdr ex. 0x08080000
        for (int i = 0; i < adrList_taken.size(); i++) {
            if (l2mList.get(i).label != null) {
                int adr = l2mList.get(i).adr;
                Long curAdr = adr + baseAdrInt;
                String curAdrString = Long.toHexString(curAdr);

                // change to file out...
                System.out.print("#define sysMem_");
                System.out.print(l2mList.get(i).label + "\t\t((uint32_t)0x");
                System.out.println(curAdrString + ")");
            }
        }
    }
    
    static String stripWeirdChar(String str)
    {
        str = str.replace("+", "");
        str = str.replace("-", "");
        str = str.replace("/", "");
        str = str.replace(".", "");
        return str;
    }
}
