#ifndef AVLNODE_H
#define AVLNODE_H
using namespace std;
#include<cstdlib>

template <typename Type> class AVLNode
{

    Type element;
    int height;
    AVLNode<Type>* left;
    AVLNode<Type>* right;
    ~AVLNode(){}
    friend class AVLTree;

};
//constructor
template<typename Type>
AVLNode::AVLNode (Type theElem, AVLNode* l, AVLNode* r, int h = 0)
    : element(theElem), left(l), right(r), height(h){}

//destructor

#endif // AVLNODE_H
