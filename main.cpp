#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include "sortInventory.h"
#include <array>
#include <vector>
#include "hashFunc.h"
#include "hTree.h"

using namespace std;

int displayMenu() {
    int choiceNumber = 0;
    string choice;

    cout << "======Main Menu======\n";
    cout << "1. Input Data\n";
    cout << "2. Hash with Division Hash\n";
    cout << "3. Hash with Multiplication Hash\n";
    cout << "4. Hash with SDBM Hash\n";
    cout << "5. Hash with DJB Hash\n";
    cout << "6. Hash with Lose Lose Hash\n";
    cout << "7. Evaluate all Hashing Functions\n";
    cout << "8. Select Best Function (auto)\n";
    cout << "9. Select Best Function (user input)\n";
    cout << "10. Print Hashed Table\n";
    cout << "11. Quit\n";

    getline(cin,choice);

    stringstream(choice) >> choiceNumber;

    if (choiceNumber > 11 || choiceNumber < 1) {
        cout<<"Invalid Input"<<endl;
    }

    return choiceNumber;
}

int main() {
    hashFunc *hFunct = new hashFunc();
    int bestSize = 0;
    vector <string> hashingObjectNames;
    hTree *h = new hTree();
    hTreeN *hashTable [113];

    for (int i = 0; i < 113; i++) {
        hashTable[i] = NULL;
    }

    vector <int> sumMethodIndexes;
    vector <int> multMethodIndexes;
    vector <int> SDBMIndexes;
    vector <int> DJBIndexes;
    vector <int> loseLoseIndexes;

    int minFunc = 0;

    while(true) {
        int choiceNumber = displayMenu();

        if (choiceNumber == 1){
            string fileName;
            cout<<"Enter filename of list: ";
            getline(cin, fileName);
            ifstream in_stream;
            in_stream.open(fileName);
            string hashingObject;

            while(!in_stream.eof()){
                getline(in_stream, hashingObject);

                if(hashingObject == ""){ //catches that last line
                    break;
                }

                hashingObjectNames.push_back(hashingObject);
                hFunct->insertNewObj(hashingObject);

            }

            bestSize = hFunct->findSize(hashingObjectNames.size());

            cout << "Number of objects: " << hashingObjectNames.size() << endl;
            cout << "Best hash table size is: " << bestSize << endl;

        } else if (choiceNumber == 2) {

            for ( int i = 0; i< hashingObjectNames.size(); i++){
                int index = hFunct->hashSum (hashingObjectNames[i], bestSize);
                sumMethodIndexes.push_back(index);
            }

            hFunct->getRange(sumMethodIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(sumMethodIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(sumMethodIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(sumMethodIndexes)<<endl;
        } else if (choiceNumber == 3) {
            for ( int i = 0; i< hashingObjectNames.size(); i++){
                int index = hFunct->hashMult (hashingObjectNames[i], bestSize);
                multMethodIndexes.push_back(index);
            }

            hFunct->getRange(multMethodIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(multMethodIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(multMethodIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(multMethodIndexes)<<endl;
        } else if (choiceNumber == 4) {
            for ( int i = 0; i<hashingObjectNames.size(); i++){
                int index = hFunct->hashSDBM (hashingObjectNames[i], bestSize);
                SDBMIndexes.push_back(index);
            }

            hFunct->getRange(SDBMIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(SDBMIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(SDBMIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(SDBMIndexes)<<endl;
        } else if (choiceNumber == 5) {
            for ( int i = 0; i<hashingObjectNames.size(); i++){
                int index = hFunct->hashDJB (hashingObjectNames[i], bestSize);
                DJBIndexes.push_back(index);
            }

            hFunct->getRange(DJBIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(DJBIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(DJBIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(DJBIndexes)<<endl;
        } else if (choiceNumber == 6) {
            for(int i = 0; i<hashingObjectNames.size(); i++) {
                int index = hFunct->loseLose(hashingObjectNames[i], bestSize);
                loseLoseIndexes.push_back(index);
            }

            hFunct->getRange(loseLoseIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(loseLoseIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(loseLoseIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(loseLoseIndexes)<<endl;
        } else if (choiceNumber == 7) {
            int h1, h2, h3, h4, h5;
            vector<int> sum, mult, SDBM, DJB, lL;

            for ( int i = 0; i<hashingObjectNames.size(); i++){
                h1 = hFunct->hashSum(hashingObjectNames[i], bestSize);
                sum.push_back(h1);
                h2 = hFunct->hashMult(hashingObjectNames[i], bestSize);
                mult.push_back(h2);
                h3 = hFunct->hashSDBM(hashingObjectNames[i], bestSize);
                SDBM.push_back(h3);
                h4 = hFunct->hashDJB(hashingObjectNames[i], bestSize);
                DJB.push_back(h4);
                h5 = hFunct->loseLose(hashingObjectNames[i], bestSize);
                lL.push_back(h5);
            }

            vector<int>loadFactors;
            float l1, l2, l3, l4, l5;
            l1 = hFunct->getLoadFactor(sum);
            l2 = hFunct->getLoadFactor(mult);
            l3 = hFunct->getLoadFactor(SDBM);
            l4 = hFunct->getLoadFactor(DJB);
            l5 = hFunct->getLoadFactor(lL);
            cout<<l1 <<" "<<l2<<" "<<l3<<" "<<l4<<" "<<l5<<endl;

            if (l1 < l2 && l1 < l3 && l1<l4 && l1< l5){
                cout<<"Division hashing suggested"<<endl;
                minFunc = 2;
            } else if (l2 <= l1 && l2<=l3 && l2<=l4 && l2<=l5){
                cout<<"Multiplication hashing suggested"<<endl;
                minFunc = 3;
            } else if (l3<= l1 && l3<=l2 && l3<=l4 && l3<=l5) {
                cout<<"SDBM hashing suggested"<<endl;
                minFunc = 4;
            } else if (l4<=l1 && l4<=l2 && l4<=l3 && l4<=l5) {
                cout<<"DJB hashing suggested"<<endl;
                minFunc = 5;
            } else {
                cout<<"Lose-Lose hashing suggested"<<endl;
                minFunc = 6;
            }
        } else if (choiceNumber == 8) {
            cout<<minFunc<<endl;
            if (minFunc == 2) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashSum(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    }else{
                        hTreeN *nextNode = hashTable[index];
                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            } else if (minFunc == 3) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashMult(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    }else{
                        hTreeN *nextNode = hashTable[index];
                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            } else if (minFunc == 4) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashSDBM(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    }else{
                        hTreeN *nextNode = hashTable[index];
                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            } else if (minFunc == 5) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashDJB(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    }else{
                        hTreeN *nextNode = hashTable[index];
                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            } else if (minFunc ==6) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->loseLose(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    }else{
                        hTreeN *nextNode = hashTable[index];
                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            }
        } else if (choiceNumber == 9) {
        } else if (choiceNumber == 10) {
            /*for ( int i = 0; i < bestSize; i++) {
                hTreeN *current;
                //cout << hashTable[i]->title <<endl;
                current = hashTable[i];
                cout << endl;
                while(current->next != NULL){
                    cout<<current->title<<", ";
                    current = current->next;
                }
            }*/
            for (int i = 0; i<bestSize; i++){
                        if(hashTable[i] != NULL){
                            hTreeN *tNode = hashTable[i];
                            cout<<i<<" " << hashTable[i]->title<<endl;
                            while(tNode->next != NULL){
                                tNode = tNode->next;
                                cout<<"   "<<tNode->title<<endl;
                            }
                        }
            }
        } else if (choiceNumber == 11) {
            cout<<"Goodbye!"<<endl;
            break;
        }
    }

    return 0;
}
