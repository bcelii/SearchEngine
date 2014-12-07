#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <cmath>
#include <iostream>
using namespace std;

#endif // AVLTREE_H


template<typename Type>
class AVLTree
{
private:
    AVLNode<Type>* root;

    int getHeight(AVLNode<Type>* t)
    {
        return (t == nullptr? -1 : t->height);
    }

public:
    //constructor
    AVLTree()
    {
        root = nullptr;
    }

    //destructor
    ~AVLTree()
    {
        makeEmpty();   //cycle thorugh and delete all nodes?
    }

    //public interface
    void insert(Type element)
    {
        insert(element, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

//Already have insert method
 /*
    /**
      * Insert x into the tree; duplicates are ignored.

     void insert( const Comparable & x )
     {
         insert( x, root );
     }

     /**
      * Deep copy.

 */
     const AvlTree & operator=( const AvlTree & rhs )
     {
         if( this != &rhs )
         {
             makeEmpty( );
             root = clone( rhs.root );
         }
         return *this;
     }




/***********Code used from weiss*************/
/****http://users.cis.fiu.edu/~weiss/dsaa_c++3/code/********/
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

//begin private insert method
private:

    void insert(int val, AVLNode<Type> *&t)
    {
        if (t == nullptr)
            t = new AVLNode<Type>(val, nullptr, nullptr);
        //element is smaller than current element
        else if (val < t->element)
        {
            insert(val, t->left);
            //if this is true it is either case 1 or case 2
            if (height(t->left)-height(t->right) == 2)
            {
                //check for case 1
                if(val < t->left->element)
                    rotateWithLeftChild(t);
                //otherwise is case 2
                else
                    doubleWithLeftChild(t);
            }
        }
        //element is bigger than current element
        else if (t->element < val)
        {
            insert(val, t->right);
            //if true is either case 3 or case 4
            if(height(t->right) - height(t->left) == 2)
            {
                //check for case 4
                if(val > t->right->element)
                    rotateWithRightChild(t);
                //otherwise is case 3
                else
                    doubleWithRightChild(t);
            }
        }

        t->height = max(height(t->left), height(t->right) + 1);

    }
    //end private insert method

    void rotateWithLeftChild(AVLNode<Type>*& k1) //k1 is a reference variable for the pointer to the parent of alpha. k1 is alpha, k2 is the child?
    {
        AVLNode<Type>* k2 = k1->left; //bad line of code
        k1->left = k2->right;	//bad line of code
        k2->right = k1;
        k1->height = max(height(k1->left), height(k1->right) + 1);
        k2->height = max(height(k2->left), height(k2->right) + 1);
        k1 = k2;
    }

    void rotateWithRightChild(AVLNode<Type>*& k2)
    {
        //same but opposite of left
    }

    void doubleWithLeftChild(AVLNode<Type>*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AVLNode<Type>*& k2)
    {
        rotateWithLeftChild(k2->left);
        rotateWithRightChild(k2);
    }

};
