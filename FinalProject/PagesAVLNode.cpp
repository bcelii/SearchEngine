#include "PagesAVLNode.h"

PagesAVLNode::PagesAVLNode()
{
}

PagesAVLNode::~PagesAVLNode(){

}

PagesAVLNode::PagesAVLNode(int pageNumb, PagesAVLNode* l,
                           PagesAVLNode* r, int repetition, int h )
{
    left = l;
    right = r;
    element = pageNumb;
    height = h;
    count = repetition;

}

//overloaded constructor
bool operator<(PagesAVLNode &a, PagesAVLNode &b){
    if(a.count<b.count){
        return true;
    }
    else{
        return false;
    }
}

void PagesAVLNode::incrementCount(){
    count++;
}
