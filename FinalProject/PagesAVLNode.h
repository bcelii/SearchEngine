#ifndef PAGESAVLNODE_H
#define PAGESAVLNODE_H

class PagesAVLNode
{
public:
    //constructor, destructor
    //! Constructor for the PagesAVLNode class
    //!
    PagesAVLNode();
    //! Destructor for the PagesAVLNode class
    //!
    ~PagesAVLNode();

    //constructor that initializes new node with a count of 1
    //! Constructor for the PagesAVLNode class that initializes a new node with count of 1
    //! \param: pageNumb, number of pages (element)
    //! \param: l, left side
    //! \param: r, right side
    //! \param: repetition, is the count
    //! \param: h, is the height
    //!
    PagesAVLNode(int, PagesAVLNode*,PagesAVLNode*, int = 1, int h = 0);
    //! function to increment the count
    //!
    void incrementCount();

    //member functions
    int height;
    int element;
    int count;
    PagesAVLNode* right;
    PagesAVLNode* left;

    friend class PagesAVLTree;
    //! Overloaded constructor
    //!
    friend bool operator<(PagesAVLNode &a, PagesAVLNode &b);
};

#endif // PAGESAVLNODE_H
