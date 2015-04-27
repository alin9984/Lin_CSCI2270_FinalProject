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

int hashFunc::hashSum(string hashObj, int tableSize) {
    int sum = 0;

    for (int i = 0; i< hashObj.size(); i++){
        sum = sum + (int)hashObj[ i ];
    }

    sum = sum % tableSize;
    return sum;
}

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

void hashFunc::insertNewObj(string objID) {
    hashedObject *newObj = new hashedObject;
    newObj->objName = objID;
    newObj->right = NULL;
    newObj->left = NULL;
    newObj->parent = NULL;
    hashingObjects.push_back(newObj);
}

int hashFunc::hashDJB(string objID, int tableSize) {
    int c, i, h;

    for(i = h = 0; i < objID.length(); i++) {
        c = toupper(objID[ i ]);
        h = ((h << 5) + h) ^ c;
    }

    return abs(h % tableSize);
}

int hashFunc::hashSDBM(string objID, int tableSize) {
    int h = 0;

    for(int i = 0; i < objID.length(); i++) {
        h = objID[i] + (h << 6) + (h << 16) - h;
    }

    return abs(h % tableSize);
}

int hashFunc::loseLose(string objID, int tableSize) {
   int hashVal = 0;

   for (int i = 0; i < objID.length(); i++) {
      hashVal = hashVal * i + objID[ i ];
   }

   return abs(hashVal % tableSize);
}

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
/*void hashFunc::intoTable(hashedObject *ho, string objName) {
    hashedObject *newNode = new hashedObject;
    newNode->parent = NULL;
    newNode->objName = objName;
    newNode->left = NULL;
    newNode->right = NULL;

    insertNode(ho, newNode);
}
void hashFunc::insertNode(hashedObject *node, hashedObject *child) {
    if (node == NULL) {
        node = child;
    }
    else if (node->objName.compare(child->objName) < 0) {

        if (node->right == NULL) {
            node->right = child;
            child->parent = node;
        } else {
            insertNode(node->right, child);
        }
    }
    else if (node->objName.compare(child->objName) > 0) {

        if (node->left == NULL) {
            node->left = child;
            child->parent = node;
        } else {
            insertNode(node->left, child);
        }
    }
}
void hashFunc::printTable(hashedObject *node) {

    if (node != NULL) {
        //if the node passed in is not null, first call the printfunction on the leftChild, then print the node, then call the function on the rightChild
        printTable(node->left);

        cout << node->objName << endl;

        printTable(node->right);
    }
}*/
