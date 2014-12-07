/***********Code used from weiss*************/
/****http://users.cis.fiu.edu/~weiss/dsaa_c++3/code/********/
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include"IndexAVLNode.h"
//#include "dsexceptions.h"
#include <iostream>    // For NULL
#include"Index.h"
#include<fstream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree:public Index
{
  public:
    AvlTree( ) : Index(),root( NULL )
    {
        //cout<<"Root = "<<root<<endl;
    }
   //copy ructor

    AvlTree(  AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }
    //destructor
    ~AvlTree( )
    {
        makeEmpty(1);
        cout<<"End Destructor: AVL Tree"<<endl;
    }

    vector<int>* findWord(Comparable & word) override {
        return findWord(word,root);
    }

    //return the element and page numbers pointer of the nth
    //element in the tree where starting numbering from

/*    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     Comparable & findMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     Comparable & findMax( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */

    bool contains(  Comparable & x )  override
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( )
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( )
    {
        if( isEmpty( ) ){
            cout << "Empty tree" << endl;
            cout<<endl;
        }
        else
            printTree( root );
    }

    void printToFile(char* output )
    {
        ofstream out;
        out.open(output,std::fstream::app);

        if( isEmpty( ) ){
            //cout << "Tried to Store Empty tree to hard memory" << endl;
            //cout<<endl;
            return;
        }
        else{
            printToFile(out, root );
        }
        out.close();
    }
/*    vector<IndexAVLNode*>* giveBackNodes(){
        if(isEmpty())
             return NULL;
        else{
            vector<IndexAVLNode*>* listOfNodes = new vector<IndexAVLNode*>();
            giveBackNodes(root, listOfNodes);
        }
    }*/

    /*,*
     * Make the tree logically empty.
     * int x will signal that it is the destructor that is calling the makeEmpty
     * So the word lists can be deleted
     */
    void makeEmpty() override
    {
        int x = 0;
        makeEmpty(root,x );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
/*    void insert(  Comparable & x )
    {
        insert( x, root );
    }
*/
     bool insert( Comparable &x, int &pages ) override{
        //cout<<"X = "<<x<<endl;
        //cout<<"Pages = "<<pages<<endl;
        insert( x, pages, root );

    }

    //overloaded insert for building index from hard memory
    bool insert( Comparable &x, vector<int>* pages ){

        insert( x, pages, root );


        return true;
    }

 /* Code when I thought I needed function that just inserted node
  *    void insert( IndexAVLNode* &x){
        insert(x,root);
    }
*/
    /**
     * Deep copy.
     */
     AvlTree & operator=(  AvlTree & rhs )
    {
        if( this != &rhs )
        {
            int x = 1;
            makeEmpty(root,x );
            root = clone( rhs.root );
        }
        return *this;
    }

  private:
    /*struct IndexAVLNode
    {
        Comparable element;
        IndexAVLNode   *left;
        IndexAVLNode   *right;
        int       height;

        IndexAVLNode(  Comparable & theElement, IndexAVLNode *lt,
                                                IndexAVLNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };
*/
    //only data memober which is root
    IndexAVLNode *root;
    int elementCount;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(  Comparable & x,int& pages, IndexAVLNode * & t )
    {
        if( t == NULL ){
            //the sent object is now stored in the tree
            t = new IndexAVLNode(pages, x, NULL, NULL);

            //for(int i = 0;i< t->pageNumbers->size();i++){
                //cout<<"t's "<<i<<"th element is"<<t->pageNumbers->at(i)<<endl;
            //}
        }
        else if( x < t->element )
        {
            //cout<<x<<" less than = "<<t->element<<endl;
            insert( x,pages, t->left );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {

            //cout<<x<<" greater than = "<<t->element;
            insert( x,pages, t->right );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }
        else if(t->element == x){
             // Duplicates, add pageNumbers to list
             //cout<<"X = "<<x<<endl;
             //cout<<"The same word was encountered"<<endl;
             //cout<<"Page Number pushed back:"<<endl;
             if(t->pageNumbers->at(t->pageNumbers->size()-2) != pages){
                t->pageNumbers->push_back(pages);
                //if page has never been encountered then set frequency as 1
                t->pageNumbers->push_back(1);

                t->totalCount = t->totalCount +1;
              }
              else{
                 //if page number has already been encountered then increment frequency
                (*(t->pageNumbers))[t->pageNumbers->size()-1]+= 1;
                 t->totalCount = t->totalCount +1;
             }

        }
             // Duplicates, add pageNumbers to list
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    //overloaded insert for building index form hard memory
    void insert(  Comparable & x,vector<int>* pages, IndexAVLNode * & t )
    {
        if( t == NULL )
            //the sent object is now stored in the tree
            t = new IndexAVLNode( x, NULL, NULL,pages );
        else if( x < t->element )
        {
            //cout<<x<<" less than = "<<t->element<<endl;
            insert( x,pages, t->left );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {

            //cout<<x<<" greater than = "<<t->element;
            insert( x,pages, t->right );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }
        else if(t->element == x){
            cerr<<"When building from Index tried to insert the same word!"<<endl;

        }
             // Duplicates, add pageNumbers to list
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

/*
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
    IndexAVLNode * findMin( IndexAVLNode *t )
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
    IndexAVLNode * findMax( IndexAVLNode *t )
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }

*/
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(  Comparable & x, IndexAVLNode *t )
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    vector<int>* findWord(  Comparable & x, IndexAVLNode *t )
    {
        //cout<<"findWord of AVL tree"<<endl;
        if( t == NULL ){
            //cout<<"\nwas found as NULL"<<endl;
            return NULL;}
        else if( x < t->element )
            return findWord( x, t->left );
        else if( t->element < x )
            return findWord( x, t->right );
        else
            //cout<<"PageNumbers size is "<<t->pageNumbers->size()<<endl;
            //make new vector that has page number followed
            //by term freuquency in a vector

            //vector<int>* newVector = new vector<int>();
            //call recursive function that will populate new vector
            //fillPageVector(newVector,t->pageNumbers->getRoot());

            return t->pageNumbers;
    }

    void fillPageVector(vector<int>* passedVector,PagesAVLNode* t){
        if(t != NULL){

            fillPageVector(passedVector,t->right);

            //fill vector with page number then count
            passedVector->push_back(t->element);
            passedVector->push_back(t->count);

            fillPageVector(passedVector,t->left);
        }
    }

/****** NONRECURSIVE VERSION*************************
    bool contains(  Comparable & x, IndexAVLNode *t )
    {
        while( t != NULL )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     *  int will tell if the function has been called form the rehashing funtion
     * which in that case should not delete the vector list
     */
    void makeEmpty( IndexAVLNode * & t, int &x )
    {
        if( t != NULL )
        {
            makeEmpty( t->left,x );
            makeEmpty( t->right,x );
            //release dynmaic memory allocated to vector
            //but if for the rehashing don't want to free memory of vecotrs
            //because reuse that dynamically allocated memory on the new nodes
            //in the new hash table
            if(x!=0 ){
                delete t->pageNumbers;
            }

            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( IndexAVLNode *t )
    {
        if( t != NULL )
        {
            printTree( t->left );
            cout << t->element << endl;
            //print out all page numbers
            cout<<"Page Numbers:"<<endl;
            //t->pageNumbers->printTree();

            for(int i = 0;i<t->pageNumbers->size();i++){
                cout<<t->pageNumbers->at(i)<<endl;
                cout<<"Frequency: "<<t->pageNumbers->at(i+1)<<endl;
                i++;
            }


            cout<<endl;

            printTree( t->right );
        }
    }

    void printToFile(ofstream& output, IndexAVLNode *t){
        if( t != NULL )
        {
            printToFile(output, t->left );
            output << t->element<<" ";
            //print out all page numbers
            //cout<<"Page Numbers:"<<endl;
            //t->pageNumbers->printTree();

            for(int i = 0;i<t->pageNumbers->size();i++){
                output<<t->pageNumbers->at(i)<<" ";

            }

            output<<"-1"<<endl;

            printToFile(output, t->right );
        }
    }

    void giveBackNodes(IndexAVLNode *t, vector<IndexAVLNode* >* list ){
         if( t != NULL )
        {
            giveBackNodes( t->left );
            list->push_back(t);

            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    IndexAVLNode * clone( IndexAVLNode *t )
    {
        if( t == NULL )
            return NULL;
        else
            return new IndexAVLNode( t->element, clone( t->left ), clone( t->right )
                                     ,t->pageNumbers,t->height );
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( IndexAVLNode *t )
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs )
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( IndexAVLNode * & k2 )
    {
        IndexAVLNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( IndexAVLNode * & k1 )
    {
        IndexAVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( IndexAVLNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( IndexAVLNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
