#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <array>
#include <vector>
#include "hashFunc.h"

using namespace std;

hashFunc::hashFunc()
{
    //ctor
}

hashFunc::~hashFunc()
{
    //dtor
}
//isPrime determines whether a number passed in is prime
//Preconditions: must have an integer passed in as an argument
//Postcondition: returns a bool that is true if the integer is prime, false if not
bool hashFunc::isPrime(int dataSize) {
    bool isPrime = true;

    for ( int i = 2; i< dataSize; i++) {
        if(dataSize%i == 0){
            isPrime = false;
            return isPrime;
        }
    }

    return isPrime;
}

//findSize determines the best size of the hash table, given the number of objects passed in from the file.
//Precondition: a file must have been read in, and a vector must have been created that stores the values of each item.
//The function takes the size of the vector as the argument.
//Postcondition: compares the closest primes to the size, both above and below, and then returns the prime integer that is closest to the size.
int hashFunc::findSize(int dataSize) {
    int smallerPrime;
    int largerPrime;

    for( int i = dataSize; i>0; i--) {
        if(isPrime(i) == true) {
            smallerPrime = i;
            break;
        }
    }

    largerPrime = dataSize;

    while ( isPrime(largerPrime) != true) {
        isPrime(largerPrime++);
    }

    if ((largerPrime-dataSize)<(dataSize-smallerPrime)) {
        return largerPrime;
    } else return smallerPrime;
}

//hashSum uses the Division method (outlined in Cormen text) to generate a hash index
//Precondition: file of objects must have been read in, and the size of the table needs to have been determined.
//Postcondition: converts object name to an integer index.
int hashFunc::hashSum(string hashObj, int tableSize) {
    int sum = 0;

    for (int i = 0; i< hashObj.size(); i++){
        sum = sum + (int)hashObj[ i ];
    }

    sum = sum % tableSize;
    return sum;
}

//hashSum uses the Multiplication method (outlined in Cormen text) to generate a hash index
//Precondition: file of objects must have been read in, and the size of the table needs to have been determined.
//Postcondition: converts object name to an integer index.
int hashFunc::hashMult(string hashObj, int tableSize) {
    float sum = 0;

    for ( int i = 0; i < hashObj.size(); i++) {
        sum = sum + (int)hashObj[ i ];
    }

    sum = sum * 13 / 32;
    sum = sum - (int)sum;
    sum = int(sum * tableSize);

    return sum;
}

//hashSum uses the DJB Method (developed by Prof. Daniel Bernstein, purportedly one of the more efficient hashing functions generated)
// to generate a hash index
//Precondition: file of objects must have been read in, and the size of the table needs to have been determined.
//Postcondition: converts object name to an integer index.
int hashFunc::hashDJB(string objID, int tableSize) {
    int c, i, h;

    for(i = h = 0; i < objID.length(); i++) {
        c = toupper(objID[ i ]);
        h = ((h << 5) + h) ^ c;
    }

    return abs(h % tableSize);
}

//hashSum uses the SDBM method (a basic database manager hashing method) to generate a hash index
//Precondition: file of objects must have been read in, and the size of the table needs to have been determined.
//Postcondition: converts object name to an integer index.
int hashFunc::hashSDBM(string objID, int tableSize) {
    int h = 0;

    for(int i = 0; i < objID.length(); i++) {
        h = objID[i] + (h << 6) + (h << 16) - h;
    }

    return abs(h % tableSize);
}
//hashSum uses the  loseLose method (a very simple hashing method, but does not always yield the best distribution of indices, found in 1st edition of The C Programming Language)
//to generate a hash index
//Precondition: file of objects must have been read in, and the size of the table needs to have been determined.
//Postcondition: converts object name to an integer index.
int hashFunc::loseLose(string objID, int tableSize) {
   int hashVal = 0;

   for (int i = 0; i < objID.length(); i++) {
      hashVal = hashVal * i + objID[ i ];
   }

   return abs(hashVal % tableSize);
}

//getRange gets the range of hash code IDs
//Precondition: the hashing function must have already been run on the data, and the inddices stored in a vector
//Postcondition: the range and indices are not changed, simply displayed.
void hashFunc::getRange(vector<int>hashIDs) {
    int minIndex = hashIDs.size();
    int maxIndex = 0;

    for ( int i = 0; i<hashIDs.size(); i++) {
        if(hashIDs[i] < minIndex){
            minIndex = hashIDs[i];
        }
    }

    cout<<"Minimum index: "<<minIndex<<endl;

    for ( int j = 0; j<hashIDs.size(); j++) {
        if(hashIDs[j] > maxIndex){
            maxIndex = hashIDs[j];
        }
    }

    cout<<"Maximum index: "<<maxIndex<<endl;
    cout<<"Range: "<<maxIndex-minIndex<<endl;
}

//getWorstCollision loops through a vector of indices to find the first most common index, and either returns the number of collisions or the index of the highest collisions
//Precondition: the hashing function must have already been called and a vector of indices created.
//Postcondition: returns an int value which is either the higher number of collisions or the index where this happens.
int hashFunc::getWorstCollision(vector<int> vec, bool isIndex) {
    int indexes[ vec.size() ];

    for (int i = 0; i < vec.size(); i++) {
        indexes[ i ] = 0;
    }

    for (int i = 0; i < vec.size(); i++) {
        indexes[ vec[ i ] ]++;
    }

    int worstIndex = -1;
    int worstCollision = -1;

    for (int i = 0; i < vec.size(); i++) {
        if (indexes[ i ] > worstCollision) {
            worstCollision = indexes[ i ];
            worstIndex = i;
        }
    }

    if (isIndex) {
        return worstIndex;
    } else {
        return worstCollision;
    }
}

//getLoadFactor calculates the average number of objects stored at each index
//Precondition: the indices must have already been calculated using a hashing function.
//Postcondition: returns a float that is the load factor for that hash function.
float hashFunc::getLoadFactor(vector<int> vec) {
    int indexes[ vec.size() ];

    for (int i = 0; i < vec.size(); i++) {
        indexes[ i ] = 0;
    }

    for (int i = 0; i < vec.size(); i++) {
        indexes[ vec[ i ] ]++;
    }

    int numUsedIndex = 0;

    for (int i = 0; i < vec.size(); i++) {
        if (indexes[ i ] > 0) {
            numUsedIndex++;
        }
    }

    float loadFactor = (float)vec.size() / (float)numUsedIndex;

    return loadFactor;
}
