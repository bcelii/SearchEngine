#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include<iterator>
#include"IndexAVLNode.h"
#include"AvlTree.h"

using namespace std;


int hash( const string & key );
int hash( int key );
int nextPrime( int n );

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
public:
    void print(void){
        for(int u = 0;u<theLists.size();u++){
            cout<<"Tree "<<u<<endl;
            theLists[u]->printTree();
            cout<<endl;
        }
    }

    int getSize(void){
        return currentSize;
    }

    //constructor that sets initial size to 101 by default
    explicit HashTable( int size = 10 )
      : currentSize( 0 )
      { theLists.resize( size );
        cout<<"TheLists constructor called"<<endl;
        //initialize tree objects
        for(int i = 0;i<theLists.size();i++){
            theLists[i] = new AvlTree<string>();
        }
      }

    bool contains( const HashedObj & x ) const
    {
        //creates alias for list that is used as seperate chaining

        //const list<HashedObj> & whichList = theLists[ myhash( x ) ];
        const AvlTree<string>* whichList = theLists[ myhash(x)];

        //uses iterator to find --> change to AVL tree
        return whichList->contains(x);

        //return find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
    }

    //makes the entire data structure empty
    void makeEmpty( )
    {
        //calls clear funcion on all of the
        for( int i = 0; i < theLists.size( ); i++ ){
            //theLists[ i ].clear( );
            theLists[i]->makeEmpty();

        }
    }

    //finds hashing index and then checks that the value is not already in the list
    //If it is not hten it adds it to the list, increments, and then rehashes if
    //size is too large
    bool insert( const HashedObj & x , int &page)
    {
        //cout<<"Size = "<<theLists.size()<<endl;
        cout<<x<<" Hashed to "<<myhash(x)<<endl;
        //list<HashedObj> & whichList = theLists[ myhash( x ) ];
        AvlTree<string>* & whichList = theLists[myhash(x)];
        /*if( find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
            return false;*/
        whichList->insert(x, page);
        //inserting in linked list-->change to AVL tree insert(x)
        //whichList.push_back( x );

        //////currently not using rehashing functoin////
            // Rehash; see Section 5.5
        /*if( ++currentSize > theLists.size( ) )
            rehash( );*/

        return true;
    }

    //overloaded insert function for rehashing
    bool insert( IndexAVLNode* & node){
        AvlTree<string>* & whichList = theLists[myhash(node->element)];

        whichList->insert(node->element,node->pageNumbers);
        //inserting in linked list-->change to AVL tree insert(x)

        // Rehash; see Section 5.5
        /*if( ++currentSize > theLists.size( ) )
            rehash( );*/

        return true;
    }

    //don't need this function because won't remove any items
    /*bool remove( const HashedObj & x )
    {
        list<HashedObj> & whichList = theLists[ myhash( x ) ];
        typename list<HashedObj>::iterator itr = find( whichList.begin( ), whichList.end( ), x );

        if( itr == whichList.end( ) )
            return false;

        whichList.erase( itr );
        --currentSize;
        return true;
    }*/

    //will return vector of lists of the hashed object
    /*vector< AvlTree<string> > getList(void){
     * return theLists;
     * } */
    vector< AvlTree<HashedObj> > getList(void){
        return theLists;
    }

  private:

    vector< AvlTree<string>* > theLists;
    //vector<list<HashedObj> > theLists;   // The array of Lists
    int  currentSize;

    void rehash( )
    {
        //stores off old hash table in vector
        vector< AvlTree<string>* > oldList = theLists;
        //vector<list<HashedObj> > oldLists = theLists;

        // Create new double-sized, empty table using resize and size function
        //of the vector class
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        //make sure empty empty --> could get rid of this?
        for( int j = 0; j < theLists.size( ); j++ )
            theLists[ j ]->makeEmpty( );

        // Copy table over
        currentSize = 0;
        /*for( int i = 0; i < oldLists.size( ); i++ )
        {
            //iterating through and re-inserting all new values

            typename list<HashedObj>::iterator itr = oldLists[ i ].begin( );
            while( itr != oldLists[ i ].end( ) )
                //inserts value back into new list
                insert( *itr++ );
        }*/

        /* AVL tree implementation*/

        for(int i = 0;i<oldList.size();i++){
            vector< IndexAVLNode* >* oldNodes =  oldList[i]->giveBackNodes();
            if(oldNodes != NULL){
                for(int z = 0;z<oldNodes->size();z++){
                    insert(oldNodes[z]);
                }
            }
        }
    }

    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash( x );

        hashVal %= theLists.size( );
        if( hashVal < 0 )
            hashVal += theLists.size( );

        return hashVal;
    }
};
#endif
