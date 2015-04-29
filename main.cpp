#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <array>
#include <vector>
#include "hashFunc.h"
#include "hTree.h"

/*The program accepts a file name from the user, then runs through a variety of hashing functions to determine the best one given the data.
The items are then read in and stored in a hash table using either the method specified by the user or the method chosen by the program itself.
*/

using namespace std;

/*displayMenu displays the list of options available to the user when the program runs.
Preconditions: none
Postconditions: returns an integer which determines which operation to perform. The displayMenu function will run until the user inputs
the choice which terminates it.
*/
int displayMenu()
{
    int choiceNumber = 0;
    string choice;

    cout << "======Main Menu======\n";
    cout << "1. Get best table size\n";
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

    if (choiceNumber > 11 || choiceNumber < 1)
    {
        cout<<"Invalid Input"<<endl;
    }

    return choiceNumber;
}

int main()
{
    hashFunc *hFunct = new hashFunc(); //declares a new instance of the hashFunc class, which contains all the hashing methods
    int bestSize = 0;
    vector <string> hashingObjectNames; //initialize a vector to store the objects initially when they're read in
    hTree *h = new hTree(); //initialize the hash table

    /*initialize vectors to store the indexes created by the various hashing functions*/
    vector <int> sumMethodIndexes;
    vector <int> multMethodIndexes;
    vector <int> SDBMIndexes;
    vector <int> DJBIndexes;
    vector <int> loseLoseIndexes;

    int minFunc = 0; //determines which hashing function to use to create the hash table
    
    //read in the file when the program starts
    string fileName;
    
    cout << "Enter file name of list: ";
    getline( cin, fileName );
    
    ifstream in_stream ( fileName );
    // ask for file name again if file does not open
    while ( !in_stream.is_open() )
    {
        cout << "Error: file failed to open." << endl;
        cout << "If error persists, try including full file path in file name." << endl << endl;
        cout << "Re-enter file name of list: ";
        getline( cin, fileName );
        
        in_stream.open( fileName );
    }
    
    string hashingObject;

    while(!in_stream.eof()) {
        getline(in_stream, hashingObject);

        if(hashingObject == "") {
            break;
        }

        hashingObjectNames.push_back(hashingObject);
    }
    //get the best size for the hash table, then create an array of that size
    bestSize = hFunct->findSize(hashingObjectNames.size());
    hTreeN *hashTable [bestSize];

    for (int i = 0; i < bestSize; i++) {
        hashTable[i] = NULL;
    }

    while(true) {
        int choiceNumber = displayMenu();

        if (choiceNumber == 1) {
            //display the number of objects read in as well as the best calculated size for the hash table
            /*Precondition: a valid file must be read in, containing strings of objects
            Postcondition: the best size for the hashing table will be outputted, given the original data set.
            */
            cout << "Number of objects: " << hashingObjectNames.size() << endl;
            cout << "Best hash table size is: " << bestSize << endl;

        } else if (choiceNumber == 2) {
            //use the hashSum method to determine index for each value, get the range of indices, then call getWorstCollision to
            //get the number of maximum collixions and call getLoadFactor to get avg # of values stored per index
            for ( int i = 0; i< hashingObjectNames.size(); i++) {
                int index = hFunct->hashSum (hashingObjectNames[i], bestSize);
                sumMethodIndexes.push_back(index);
            }

            hFunct->getRange(sumMethodIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(sumMethodIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(sumMethodIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(sumMethodIndexes)<<endl;
        } else if (choiceNumber == 3) {
            //use the hashMult method to determine index for each value, get the range of indices, then call getWorstCollision to
            //get the number of maximum collisions and call getLoadFactor to get avg # of values stored per index
            for ( int i = 0; i< hashingObjectNames.size(); i++) {
                int index = hFunct->hashMult (hashingObjectNames[i], bestSize);
                multMethodIndexes.push_back(index);
            }

            hFunct->getRange(multMethodIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(multMethodIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(multMethodIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(multMethodIndexes)<<endl;
        } else if (choiceNumber == 4) {
            //use the hashSDBM method to determine index for each value, get the range of indices, then call getWorstCollision to
            //get the number of maximum collisions and call getLoadFactor to get avg # of values stored per index
            for ( int i = 0; i<hashingObjectNames.size(); i++)
            {
                int index = hFunct->hashSDBM (hashingObjectNames[i], bestSize);
                SDBMIndexes.push_back(index);
            }

            hFunct->getRange(SDBMIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(SDBMIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(SDBMIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(SDBMIndexes)<<endl;
        } else if (choiceNumber == 5) {
            //use the hashDJB method to determine index for each value, get the range of indices, then call getWorstCollision to
            //get the number of maximum collisions and call getLoadFactor to get avg # of values stored per index
            for ( int i = 0; i<hashingObjectNames.size(); i++) {
                int index = hFunct->hashDJB (hashingObjectNames[i], bestSize);
                DJBIndexes.push_back(index);
            }

            hFunct->getRange(DJBIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(DJBIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(DJBIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(DJBIndexes)<<endl;
        } else if (choiceNumber == 6) {
            //use the loseLose method to determine index for each value, get the range of indices, then call getWorstCollision to
            //get the number of maximum collisions and call getLoadFactor to get avg # of values stored per index
            for(int i = 0; i<hashingObjectNames.size(); i++) {
                int index = hFunct->loseLose(hashingObjectNames[i], bestSize);
                loseLoseIndexes.push_back(index);
            }

            hFunct->getRange(loseLoseIndexes);
            cout<<"Max number of collisions: "<<hFunct->getWorstCollision(loseLoseIndexes)<<endl;
            cout<<"Index of max number of collisions: "<<hFunct->getWorstCollision(loseLoseIndexes, true)<<endl;
            cout<<"Average number of items stored per index: "<<hFunct->getLoadFactor(loseLoseIndexes)<<endl;
        }
        else if (choiceNumber == 7) {
            //evaluate all hashing functions.
            //create a vector for each hashing function, then store the indices generated in the vector
            int h1, h2, h3, h4, h5;
            vector<int> sum, mult, SDBM, DJB, lL;

            for ( int i = 0; i<hashingObjectNames.size(); i++) {
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
            //calculate avg number of stored values per index for each hashing method by passing in the vector of indices
            l1 = hFunct->getLoadFactor(sum);
            l2 = hFunct->getLoadFactor(mult);
            l3 = hFunct->getLoadFactor(SDBM);
            l4 = hFunct->getLoadFactor(DJB);
            l5 = hFunct->getLoadFactor(lL);
            cout<<"Avg number of items stored per index: \n";
            cout<<"Division Method: "<<l1<<endl;
            cout<<"Multiplication Method: "<<l2<<endl;
            cout<<"SDBM Method: "<<l3<<endl;
            cout<<"DJB Method: "<<l4<<endl;
            cout<<"Lose-lose Method: "<<l5<<endl;

            //find the method which has the lower avg number of collisions and pick that one. Assign the minFunc a value based on the hashing function chosen.

            if (l1 < l2 && l1 < l3 && l1<l4 && l1< l5) {
                cout<<"Division hashing suggested"<<endl;
                minFunc = 1;
            } else if (l2 <= l1 && l2<=l3 && l2<=l4 && l2<=l5) {
                cout<<"Multiplication hashing suggested"<<endl;
                minFunc = 2;
            } else if (l3<= l1 && l3<=l2 && l3<=l4 && l3<=l5) {
                cout<<"SDBM hashing suggested"<<endl;
                minFunc = 3;
            } else if (l4<=l1 && l4<=l2 && l4<=l3 && l4<=l5) {
                cout<<"DJB hashing suggested"<<endl;
                minFunc = 4;
            } else {
                cout<<"Lose-Lose hashing suggested"<<endl;
                minFunc = 5;
            }
        } else if (choiceNumber == 8) {
            //clear the hashing table
            for ( int i = 0; i<bestSize; i++){
                hashTable[i] = NULL;
            }
            //Precondition for choice 8: the minFunc value must first be assigned; that is, a hashing function must first be chosen via option 7
            //Postcondition: a hash table will be created using the best hashing function, resolving collisions by chaining.
            //Hash table is an array of linked lists.
            if (minFunc ==0) {
                cout<<"Please evaluate all hashing functions first by selecting option seven"<<endl;
            }
            //depending on the hashing function chosen, create a different hash table.
            if (minFunc == 1) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashSum(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            }
            else if (minFunc == 2) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++)
                {
                    int index = hFunct->hashMult(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            } else if (minFunc == 3) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashSDBM(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            } else if (minFunc == 4) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashDJB(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            } else if (minFunc ==5) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->loseLose(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            }
        } else if (choiceNumber == 9) {
            //Precondition: a valid file name must be read in first, and a vector of strings containing the object names must have been created.
            //Postcondition: a hash table will be created according to the user's preferences.
            int choice = 0;
            while (choice > 5 || choice < 1){
            cout<<"Choose the desired hashing function: "<<endl;
            cout<<"1. Division Method"<<endl;
            cout<<"2. Multiplication Method"<<endl;
            cout<<"3. SDBM Method"<<endl;
            cout<<"4. DJB Method"<<endl;
            cout<<"5. Lose-Lose Method"<<endl;
            string choiceNum;
            getline(cin, choiceNum);
            choice = atoi(choiceNum.c_str());
            }
            for ( int i = 0; i<bestSize; i++){
                hashTable[i] = NULL;
            }
            minFunc = choice;
            if (minFunc == 1) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashSum(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            }
            else if (minFunc == 2) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++)
                {
                    int index = hFunct->hashMult(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;


                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }

            } else if (minFunc == 3) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashSDBM(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            } else if (minFunc == 4) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->hashDJB(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            } else if (minFunc ==5) {
                for ( unsigned int i = 0; i < hashingObjectNames.size(); i++) {
                    int index = hFunct->loseLose(hashingObjectNames[i], bestSize);

                    hTreeN *tNode = new hTreeN;
                    tNode->title = hashingObjectNames[i];
                    tNode->next = NULL;

                    if (hashTable[index] == NULL) {
                        hashTable[index]=(tNode);
                    } else {
                        hTreeN *nextNode = hashTable[index];

                        while (nextNode->next != NULL) {
                            nextNode = nextNode->next;
                        }
                        nextNode->next = tNode;
                    }
                }
            }


        } else if (choiceNumber == 10) { //Prints the hashed values at their assigned indices
            //Precondition: the hash table must have been created and populated.
            //Postcondition: prints out a list of the hashed objects at their assigned indices

            for (int i = 0; i<bestSize; i++) {
                if (hashTable[i] != NULL) {
                    hTreeN *tNode = hashTable[i];
                    cout<<i<<":"<< endl;
                    cout<<hashTable[i]->title<<endl;

                    while(tNode->next != NULL) {
                        tNode = tNode->next;
                        cout<<tNode->title<<endl;
                    }
                    cout<<endl;
                }
            }
        } else if (choiceNumber == 11) {
            cout<<"Goodbye!"<<endl;
            break;
        }
    }

    return 0;
}
