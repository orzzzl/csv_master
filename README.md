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

1,3,4,5
2,3,1,2
2,6,2,1

And you want to select colume 0,1,2
You can either do ./csv_master -s 0-2 -o output.txt sample.csv
               or ./csv_master -s 0,1,2 -o output.txt sample.csv

