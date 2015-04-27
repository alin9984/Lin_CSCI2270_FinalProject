#include <string>
#ifndef HTREE_H
#define HTREE_H
#include <string>

using namespace std;

struct hTreeN {
    string title;

    //hTreeN *parent;
    //hTreeN *leftChild;
    //hTreeN *rightChild;
    hTreeN *next = NULL;

    hTreeN(){};

    hTreeN(std::string name) {
        title = name;
    }
};

class hTree {
    public:

        void insertNode(hTreeN*, hTreeN*);
        void printTree(hTreeN*);

        hTree();
        virtual ~hTree();

    protected:
    private:

        hTreeN *root;
};

#endif // MOVIETREE_H
