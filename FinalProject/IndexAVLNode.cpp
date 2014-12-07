#include "IndexAVLNode.h"

IndexAVLNode::IndexAVLNode()
{
}


IndexAVLNode::IndexAVLNode(std::string word, IndexAVLNode* l,
                           IndexAVLNode* r, int h )
{
    left = l;
    right = r;
    element = word;
    pageNumbers = new vector<int>();
}

IndexAVLNode::IndexAVLNode(int Pages,std::string word, IndexAVLNode* l,
                IndexAVLNode* r, int h)
{
    height = h;
    left = l;
    right = r;
    this->pageNumbers = new vector<int>();
    pageNumbers->push_back(Pages);
    pageNumbers->push_back(1);
    element = word;
    totalCount = 1;

}
//constructor for clone function
IndexAVLNode::IndexAVLNode( string word, IndexAVLNode* l,IndexAVLNode* r
                                 ,vector<int>* newVector,int h){
    height = h;
    left = l;
    right = r;
    //delete existing pagenumbers

    pageNumbers = newVector;
    element= word;

    totalCount = 0;
    for(int i = 0;i<pageNumbers->size();i++){
       totalCount += pageNumbers->at(i+1);
       i++;
    }

}

//copy constructor
/*IndexAVLNode::IndexAVLNode(IndexAVLNode y, IndexAVLNode* l, IndexAVLNode* r){
    left = l;
    right = r;
    this->element = y.element;
    //will now access the same vector as the one created
    this->pageNumbers = y.pageNumbers;

}*/

bool operator<(IndexAVLNode &a, IndexAVLNode &b){
    if(a.element.compare(b.element) < 0){
        return true;
    }
    else{
        return false;
    }
}

