#ifndef INDEXAVLNODE_H
#define INDEXAVLNODE_H
#include<vector>
#include<string>
#include"PagesAvlTree.h"
using namespace std;
class IndexAVLNode
{
public:
    //constructor with no parameters
    IndexAVLNode();
    ~IndexAVLNode(){}

    //constructor that accepts word, left pointer, right pointer and height
    IndexAVLNode(std::string word, IndexAVLNode* l,
                           IndexAVLNode* r, int h = 0);
    //constructor accepts:word, left pointer, right pointer, height and vector pointer
    IndexAVLNode(int Pages,std::string word, IndexAVLNode* l,
                           IndexAVLNode* r, int h = 0);
    IndexAVLNode( std::string, IndexAVLNode*,IndexAVLNode*,
                  vector<int>*,int = 0);

    string element;
    int height;
    int totalCount;
    IndexAVLNode* right;
    IndexAVLNode* left;
    //data structure to hold page numbers --> will be changed
    //to tree after 24th Demo
    vector<int>* pageNumbers;

    //To be included after 24th deadline: pages sorted in AVL tree
    //by term frequency relevance with relevancy info in their nodes
    friend class AVLTree;
    friend bool operator<(IndexAVLNode &a, IndexAVLNode &b);

    //overloaded comparison operator

};

#endif // INDEXAVLNODE_H
