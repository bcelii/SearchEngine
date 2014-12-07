/***********Code used from weiss*************/
/****http://users.cis.fiu.edu/~weiss/dsaa_c++3/code/********/
#ifndef PAGESAVLTREE_H
#define PAGESAVLTREE_H

//#include "dsexceptions.h"
#include <iostream>    // For NULL
#include"Index.h"
#include"PagesAVLNode.h"
using namespace std;

// PagesAvlTree class
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
class PagesAvlTree
{
  public:
    int size(){
        return elementCount;
    }

    PagesAVLNode* getRoot(){
        return root;
    }

    PagesAvlTree( ) : root( NULL )
    {
        elementCount = 0;
        //cout<<"Root = "<<root<<endl;
    }
   //copy ructor

    PagesAvlTree(  PagesAvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }
    //destructor
    ~PagesAvlTree( )
    {
        makeEmpty();
    }
/*
    vector<int>* findWord(Comparable & word)  {
        return findWord(word,root);
    }
*/

    //********* Maybe find page number?********//

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

    bool contains(  Comparable & x )
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

/*    vector<PagesAvlTree*>* giveBackNodes(){
        if(isEmpty())
             return NULL;
        else{
            vector<PagesAvlTree*>* listOfNodes = new vector<PagesAvlTree*>();
            giveBackNodes(root, listOfNodes);
        }
    }
*/
    /*,*
     * Make the tree logically empty.
     * int x will signal that it is the destructor that is calling the makeEmpty
     * So the word lists can be deleted
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
/*    void insert(  Comparable & x )
    {
        insert( x, root );
    }
*/
     bool insert( Comparable &x ) {
        //cout<<"X = "<<x<<endl;
        //cout<<"Pages = "<<pages<<endl;
        insert( x, root );

    }

/*    //overloaded insert for rehashing
    bool insert( Comparable &x, vector<int>* &pages ){

        insert( x, pages, root );


        return true;
    }
*/
 /* Code when I thought I needed function that just inserted node
  *    void insert( PagesAvlTree* &x){
        insert(x,root);
    }
*/
    /**
     * Deep copy.
     */
     PagesAvlTree & operator=(  PagesAvlTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty(root);
            root = clone( rhs.root );
        }
        return *this;
    }

  private:
    /*struct PagesAvlTree
    {
        Comparable element;
        PagesAvlTree   *left;
        PagesAvlTree   *right;
        int       height;

        PagesAvlTree(  Comparable & theElement, PagesAvlTree *lt,
                                                PagesAvlTree *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };
*/
    //only data memober which is root
    PagesAVLNode *root;
    int elementCount;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(  Comparable & x, PagesAVLNode * & t )
    {
        if( t == NULL ){
            //the sent object is now stored in the tree
            t = new PagesAVLNode(x, NULL, NULL);
            elementCount++;

        }

        else if(t->element == x){
             // Duplicates, add pageNumbers to list
             //cout<<"X = "<<x<<endl;
             //cout<<"The same word was encountered"<<endl;
             //cout<<"Page Number pushed back:"<<endl;

                t->incrementCount();

        }
        else if( x < t->element )
        {
            //cout<<x<<" less than = "<<t->element<<endl;
            insert( x, t->left );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {

            //cout<<x<<" greater than = "<<t->element;
            insert( x, t->right );
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

                t->incrementCount();

        }
             // Duplicates, add pageNumbers to list
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

/*  //overloaded insert for rehashing
    void insert(  Comparable & x,vector<int>* pages, PagesAvlTree * & t )
    {
        if( t == NULL )
            //the sent object is now stored in the tree
            t = new PagesAvlTree( x, NULL, NULL,pages );
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
             for(int j = 0;j<pages->size();j++){
                 t->pageNumbers->push_back((*pages)[j]);
             }
        }
             // Duplicates, add pageNumbers to list
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
*/
/*
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
    PagesAvlTree * findMin( PagesAvlTree *t )
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
    PagesAvlTree * findMax( PagesAvlTree *t )
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
    bool contains(  Comparable & x, PagesAVLNode *t )
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
/*
    vector<int>* findWord(  Comparable & x, PagesAvlTree *t )
    {
        cout<<"findWord of AVL tree"<<endl;
        if( t == NULL ){
            cout<<"\nwas found as NULL"<<endl;
            return NULL;}
        else if( x < t->element )
            return findWord( x, t->left );
        else if( t->element < x )
            return findWord( x, t->right );
        else
            cout<<"PageNumbers size is "<<t->pageNumbers->size()<<endl;
            return t->pageNumbers; // Match

    }
*/
/****** NONRECURSIVE VERSION*************************
    bool contains(  Comparable & x, PagesAvlTree *t )
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
    void makeEmpty( PagesAVLNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left);
            makeEmpty( t->right);
            //release dynmaic memory allocated to vector
            //but if for the rehashing don't want to free memory of vecotrs
            //because reuse that dynamically allocated memory on the new nodes
            //in the new hash table


            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( PagesAVLNode *t )
    {
        if( t != NULL )
        {
            printTree(t->right);
            cout << t->element << endl;
            //print out all page numbers
            cout<<"Frequency:"<<t->count<<endl;

            cout<<endl;

            printTree( t->left );

        }
    }

/*    void giveBackNodes(PagesAvlTree *t, vector<PagesAvlTree* >* list ){
         if( t != NULL )
        {
            giveBackNodes( t->left );
            list->push_back(t);

            printTree( t->right );
        }
    }
*/
    /**
     * Internal method to clone subtree.
     */
    PagesAVLNode * clone( PagesAVLNode *t )
    {
        if( t == NULL )
            return NULL;
        else
            return new PagesAVLNode( t->element, clone( t->left ), clone( t->right )
                                     ,t->count,t->height );
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( PagesAVLNode *t )
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
    void rotateWithLeftChild( PagesAVLNode * & k2 )
    {
        PagesAVLNode *k1 = k2->left;
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
    void rotateWithRightChild( PagesAVLNode * & k1 )
    {
        PagesAVLNode *k2 = k1->right;
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
    void doubleWithLeftChild( PagesAVLNode * & k3 )
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
    void doubleWithRightChild( PagesAVLNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif // PAGESAVLTREE_H
