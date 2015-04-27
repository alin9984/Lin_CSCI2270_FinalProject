#ifndef HASHFUNC_H
#define HASHFUNC_H
#include <string>

using namespace std;

struct hashedObject{
    string objName;
    hashedObject *right;
    hashedObject *left;
    hashedObject *parent;
    int objID = 0;
};

class hashFunc {
    public:
        hashFunc();
        virtual ~hashFunc();
        bool isPrime(int inputSize);
        int findSize(int inputSize);
        int hashSum(string hashObj, int tableSize);
        void insertNewObj (string hashObj);
        int hashMult (string hashObj, int tableSize);
        int hashDJB(string objID, int tableSize);
        int loseLose(string objID, int tableSize);
        int hashSDBM(string objID, int tableSize);
        void getRange(vector<int>);
        int getWorstCollision(vector<int> vec, bool isIndex = false);
        float getLoadFactor(vector<int> vec);
        void intoTable(int index, string objName, hashedObject hashTable []);
        void insertNode(hashedObject *node, hashedObject *child);
        void printTable(hashedObject *node);

    protected:
    private:

        vector <hashedObject*> hashingObjects;
};

#endif // HASHFUNC_H
