# csv_master
This is a terminal-based program to handle csv-file.

### Compile:
You can simply type "make" to compile, but note that you must have a g++ compiler which 
surport C++11 to compile this program.

### Usage:
This command goes as follows

Note that all number appears in this program is 0-indexed!!

./csv_master [-p (colume numbers)] [-c (expression)] [-o (output file-name)] [-s (colume numbers)] 
             [-j (colume on join)] [-O] [-h] [file-name which be joined with] input-file-name
             
I'll explain each option in the following "Features Section"            

### Features:
1. Select some certain line using -s, you can either use ',' saperated notation or '-' notation.
For example, if the original csv file is:

sample.csv:

1,3,4,5  <br>
2,3,1,2  <br>
2,6,2,1  <br>

And you want to select colume 0,1,2
You can either do ./csv_master -s 0-2 -o output.txt sample.csv
               or ./csv_master -s 0,1,2 -o output.txt sample.csv
  
Note that if you don't use -o to specified a name the default output file name will be csv_master.out

2. Perform arithmetic operations and create a new colume.
For example:

sample.csv:

1,3,4,5  <br>
2,3,1,2  <br>
2,6,2,1  <br>

If you do ./csv_master -c 0+2 -o output.txt sample.csv
Then it will add each number in colume 0 with each number in colume 2 and create a new colume.
The resule will be:

line   0      1      2      3    new
0:     1      3      4      5  5.000000
1:     2      3      1      2  3.000000
2:     2      6      2      1  4.000000

Also note that to multiply it's col1xcol2 instead of col1*col2

3. Output statistics on a column: min, max, median and average
You can either do ./csv_master -p 0-2 -o output.txt sample.csv
               or ./csv_master -p 0,1,2 -o output.txt sample.csv

The result of the stats of selected colume will goes to standard output.

4. Perform an outer and inner join on two data sets
You can use -j colnumber option to do join using colnumber as a key.
If you want to do outer join, you should specify using -O options.
If not specified, the default way is inner join.

For example:
If you want to inner join f1.csv and f2.csv, using the 0th colume as key word, do:
./csv_master -j 0 -o output.txt f1.csv f2.csv

outer join:
./csv_master -j 0 -o output.txt -O f1.csv f2.csv

5. Other features:
You can use -h to specify if the csv file has a header line at the top.
If not, csv_master will auto-add names using 0-index colume number as the name.



