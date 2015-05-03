# Lin_CSCI2270_FinalProject
Project Summary:
The program will take in a list of objects, and then run through several different hashing functions to determine which one is the best for sorting the data given. It will read in the objects from a text file, and then the user will have the option of hashing using one of five different hashing methods. The user can either choose manually which hashing function to use, or have the program evaluate and then choose the best one. The program will choose the best hashing function based on which one yields the least number of average collisions. After it has created and then populated the hash table, the user can choose to print out the hashed objects, and can also re-hash using a new function if they so desire. The hash table will be an array of linked lists, and collisions will be resolved by chaining.

How to Run:
The user should download the main.cpp along with the hTree and hashFunc .cpp and .h files. Upon starting the program, the user should input the name of a text file containing the objects they desire to be hashed, with each object on a new line in the file. A sample text file has been provided, titled data.txt. Afterwards, a menu will display options allowing the user to see the range and maximium number of collisions resulting from each hashing function. The menu will continue to displa until the user selects the quit option. The user can then choose to have the program build the hash table automatically, by first selecting the "evaluating hash functiongs" option and then selecting the "select best function" option. They can also manually choose which hashing option they want to use. After the hash table has been created, the user can select to print out the hashed table, which will display the indices of the hashed objects and the object names.

Dependencies:
The program uses the C++ standard library. The standard library can be imported by the declaration to use the std namespace.

System Requirements:
The program is designed for use on Windows.

Group Members:
Antonia Lin

Contributors:
brkn8102

Open Issues/Bugs:
The program currently only allows for input of one file; furthermore, if the user misenters the file name, the program does not handle this and must be restarted to take in the correct file name. (EDIT: wrong file name issue has been resolved by brkn 8102)
