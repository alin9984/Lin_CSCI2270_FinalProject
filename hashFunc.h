#ifndef HASHFUNC_H
#define HASHFUNC_H
#include <string>

using namespace std;

class hashFunc {
    public:
        hashFunc();
        virtual ~hashFunc();
        /*isPrime determines whether a number passed in is prime
Preconditions: must have an integer passed in as an argument
Postcondition: returns a bool that is true if the integer is prime, false if not
        */
        bool isPrime(int inputSize);
        /*findSize determines the best size of the hash table, given the number of objects passed in from the file.
Precondition: a file must have been read in, and a vector must have been created that stores the values of each item.
The function takes the size of the vector as the argument.
Postcondition: compares the closest primes to the size, both above and below, and then returns the prime integer that is closest to the size.
        */
        int findSize(int inputSize);
        /*hashSum uses the Division method (outlined in Cormen text) to generate a hash index
Precondition: file of objects must have been read in, and the size of the table needs to have been determined.Takes a string to hash, as well as the size of the table as arguments.
Postcondition: converts object name to an integer index,returns index.
        */
        int hashSum(string hashObj, int tableSize);
        /*hashMult uses the Multiplication method (outlined in Cormen text) to generate a hash index
Precondition: file of objects must have been read in, and the size of the table needs to have been determined. Takes a string to hash, as well as the size of the table as arguments.
Postcondition: converts object name to an integer index, returns index.
        */
        int hashMult (string hashObj, int tableSize);
        /*hashDJB uses the DJB Method (developed by Prof. Daniel Bernstein, purportedly one of the more efficient hashing functions generated) to generate a hash index
Precondition: file of objects must have been read in, and the size of the table needs to have been determined. Takes a string to hash, as well as the size of the table as arguments.
Postcondition: converts object name to an integer index, returns index.
        */
        int hashDJB(string objID, int tableSize);
        /*loseLose uses the  lose- lose method (a very simple hashing method, but does not always yield the best distribution of indices, found in 1st edition of The C Programming Language) to generate a hash index
Precondition: file of objects must have been read in, and the size of the table needs to have been determined.Takes a string to hash, as well as the size of the table as arguments.
Postcondition: converts object name to an integer index, returns index.
        */
        int loseLose(string objID, int tableSize);
        /*hashSDBM uses the SDBM method (a basic database manager hashing method) to generate a hash index
Precondition: file of objects must have been read in, and the size of the table needs to have been determined.
Postcondition: converts object name to an integer index.
        */
        int hashSDBM(string objID, int tableSize);
        /*getRange gets the range of hash code IDs
Precondition: the hashing function must have already been run on the data, and the indices stored in a vector. Takes the vector as an argument
Postcondition: the range and indices are not changed, simply displayed. Returns nothing.
        */
        void getRange(vector<int>);
        /*getWorstCollision loops through a vector of indices to find the first most common index, and either returns the number of collisions or the index of the highest collisions
Precondition: the hashing function must have already been called and a vector of indices created. Takes the vector of indices as well as a boolean as an argument.
Postcondition: returns an int value which is either the higher number of collisions or the index where this happens if the boolean passed in is true.
        */
        int getWorstCollision(vector<int> vec, bool isIndex = false);
        /*getLoadFactor calculates the average number of objects stored at each index
Precondition: the indices must have already been calculated using a hashing function. takes in the vector of indices as an argument.
Postcondition: returns a float that is the load factor for that hash function.
        */
        float getLoadFactor(vector<int> vec);

    protected:
    private:

};

#endif // HASHFUNC_H
