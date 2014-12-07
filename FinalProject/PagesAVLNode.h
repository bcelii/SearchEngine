#ifndef PAGESAVLNODE_H
#define PAGESAVLNODE_H

class PagesAVLNode
{
public:
    //constructor, destructor
    PagesAVLNode();
    ~PagesAVLNode();

    //constructor that initializes new node with a count of 1
    PagesAVLNode(int, PagesAVLNode*,PagesAVLNode*, int = 1, int h = 0);

    void incrementCount();

    //member functions
    int height;
    int element;
    int count;
    PagesAVLNode* right;
    PagesAVLNode* left;

    friend class PagesAVLTree;
    friend bool operator<(PagesAVLNode &a, PagesAVLNode &b);
};

#endif // PAGESAVLNODE_H
