#include <string>
#ifndef HTREE_H
#define HTREE_H
#include <string>

using namespace std;

//create a struct for the objects to be read in from the text file; each has a title and a next pointer

struct hTreeN {
    string title;
    hTreeN *next = NULL;

    hTreeN(){};

    hTreeN(std::string name) {
        title = name;
    }
};

class hTree {
    public:

        hTree();
        virtual ~hTree();

    protected:
    private:

        hTreeN *root;
};

#endif // MOVIETREE_H
