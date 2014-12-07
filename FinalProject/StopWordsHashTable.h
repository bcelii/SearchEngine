#ifndef STOP_WORDS_HASH_TABLE_H
#define STOP_WORDS_HASH_TABLE_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include"StopWordsAvlTree.h"
using namespace std;


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
class StopWordsHashTable
{
  public:
    void print(void){
        for(int u = 0;u<theLists.size();u++){
            cout<<"Tree "<<u<<endl;
            theLists[u]->printTree();
            cout<<endl;
        }
    }


    explicit StopWordsHashTable( int size = 101 )
      : currentSize( 0 )
      { theLists.resize( size );

            for(int i = 0;i<theLists.size();i++){
                theLists[i] = new StopWordsAvlTree<string>();
            }

      }

    void vectorSize(int x){
        theLists.resize(x);
    }


    bool contains(  HashedObj & x )
    {
         StopWordsAvlTree<HashedObj>* whichList = theLists[ myhash( x ) ];

        return whichList->contains(x);
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


    bool insert(  HashedObj & x )
    {
        StopWordsAvlTree<HashedObj>* & whichList = theLists[ myhash( x ) ];

        whichList->insert(x);
            // Rehash; see Section 5.5
        /*if( ++currentSize > theLists.size( ) )
            rehash( );
        */
        return true;
    }
/*
    bool remove(  HashedObj & x )
    {
        list<HashedObj> & whichList = theLists[ myhash( x ) ];
        typename list<HashedObj>::iterator itr = find( whichList.begin( ), whichList.end( ), x );

        if( itr == whichList.end( ) )
            return false;

        whichList.erase( itr );
        --currentSize;
        return true;
    }
*/
  private:
    vector<StopWordsAvlTree<HashedObj>* > theLists;   // The array of Lists
    int  currentSize;

    void rehash( )
    {
       /* vector<list<HashedObj> > oldLists = theLists;

            // Create new double-sized, empty table
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( int j = 0; j < theLists.size( ); j++ )
            theLists[ j ].clear( );

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldLists.size( ); i++ )
        {
            typename list<HashedObj>::iterator itr = oldLists[ i ].begin( );
            while( itr != oldLists[ i ].end( ) )
                insert( *itr++ );
        }*/
    }

    int myhash(  HashedObj & x )
    {
        int hashVal = hash( x );

        hashVal %= theLists.size( );
        if( hashVal < 0 )
            hashVal += theLists.size( );

        return hashVal;
    }
    /**
    * A hash routine for string objects.
    */

    int hash(  string & key )
    {
        int hashVal = 0;

        for( int i = 0; i < key.length( ); i++ )
            hashVal = 37 * hashVal + key[ i ];

        return hashVal;
    }
};

//int hash(  string & key );
//int hash( int key );

#endif //STOP_WORDS_HASH_TABLE_H
