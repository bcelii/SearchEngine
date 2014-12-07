#ifndef INDEXAVLNODE_H
#define INDEXAVLNODE_H

class IndexAVLNode:public AVLNode
{
public:
    IndexAVLNode();

    //data structure to hold page numbers
    AVLTree< AVLNode<int> >* pageNumbers;

    friend class AVLTree;
};


IndexAVLNode::IndexAVLNode();
#endif // INDEXAVLNODE_H
