#include <iostream>
#include<string>
#include "AvlTree.h"
#include"IndexAVLNode.h"
#include<vector>
#include"SeparateChaining.h"
#include"StopWordsAvlTree.h"
#include"StopWordsHashTable.h"
#include<fstream>
#include<iterator>
//Code From Stemmer
#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
//Datastructres project:

/*
xml dumps:
Important things to keep in mind:

xml files go through parser (2 min). inverted file indexing: gets author, get date
    eliminate stop words, stemming, fluff



Research and Find Stemmer and Stop Word Filter: Shawlol
-use c not c++???
-DON'T ACTUALLY LOOK AT WHAT WAS STEMMED
stem before inserting and searching

Due: Saturday

2) Term Frequency Calculator: Shawlol

Due Saturday

bool operator>(const T& rhs) {
    return !*this<rhs;
            !*this==rhs;
}

//What to implement in the final project:
Parser:
    fake parser class (extends parser) that has the same list of functions, e.g. string getnextword()
    to generate fake data.
Index:
    -AVL
    -Hash

Index *idx=new hashindex;
parser*p=new Fakeparser
string x=p.getnextword()
idx.addword(x, pg#)

Collision Resolution Strategy.
    -Separate Chaining:
    -Probing (aka closed hashing aka open addressing)
        *hash function needs good distribution over the range of hash functions

        load factor: # of items in hash table vs # of spots in the table.

        ******MAKE/FIND STEMMER and TERM FREQUENCY CALCULATOR

STEMMER

prepare stop table
    -open original stop words file
    -loop through
        -stem
        -write to file2

load stop table:
    -open file
    -loop through words
        *store in hashtable:
            Hashtable<string> insert();

-make a filter function (StopAndStem)
    -stop words
    -strange characters
    -etc
-find a stemmer function
-stem stop words and then put stop words in Brendan's 'hashtable
//-bool contains() shows if the word is a stop or not.
-StopAndStem(char*)
    -if its not a stop word/once stemmed, return char*
    -if it's a stop word, return null
-prepareStopList()
-loadStopList()

*/
//http://tartarus.org/~martin/PorterStemmer/c.txt

/* This is the Porter stemming algorithm, coded up in ANSI C by the
   author. It may be be regarded as canonical, in that it follows the
   algorithm presented in

   Porter, 1980, An algorithm for suffix stripping, Program, Vol. 14,
   no. 3, pp 130-137,

   only differing from it at the points marked --DEPARTURE-- below.

   See also http://www.tartarus.org/~martin/PorterStemmer

   The algorithm as described in the paper could be exactly replicated
   by adjusting the points of DEPARTURE, but this is barely necessary,
   because (a) the points of DEPARTURE are definitely improvements, and
   (b) no encoding of the Porter stemmer I have seen is anything like
   as exact as this version, even with the points of DEPARTURE!

   You can compile it on Unix with 'gcc -O3 -o stem stem.c' after which
   'stem' takes a list of inputs and sends the stemmed equivalent to
   stdout.

   The algorithm as encoded here is particularly fast.

   Release 1: was many years ago
   Release 2: 11 Apr 2013
       fixes a bug noted by Matt Patenaude <matt@mattpatenaude.com>,

       case 'o': if (ends("\03" "ion") && (b[j] == 's' || b[j] == 't')) break;
           ==>
       case 'o': if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't')) break;

       to avoid accessing b[k0-1] when the word in b is "ion".
   Release 3: 25 Mar 2014
       fixes a similar bug noted by Klemens Baum <klemensbaum@gmail.com>,
       that if step1ab leaves a one letter result (ied -> i, aing -> a etc),
       step2 and step4 access the byte before the first letter. So we skip
       steps after step1ab unless k > k0.
*/

#include <string.h>  /* for memmove */

#define TRUE 1
#define FALSE 0

/* The main part of the stemming algorithm starts here. b is a buffer
   holding a word to be stemmed. The letters are in b[k0], b[k0+1] ...
   ending at b[k]. In fact k0 = 0 in this demo program. k is readjusted
   downwards as the stemming progresses. Zero termination is not in fact
   used in the algorithm.

   Note that only lower case sequences are stemmed. Forcing to lower case
   should be done before stem(...) is called.
*/

static char * b;       /* buffer for word to be stemmed */
static int k,k0,j;     /* j is a general offset into the string */

/* cons(i) is TRUE <=> b[i] is a consonant. */

static int cons(int i)
{  switch (b[i])
   {  case 'a': case 'e': case 'i': case 'o': case 'u': return FALSE;
      case 'y': return (i==k0) ? TRUE : !cons(i-1);
      default: return TRUE;
   }
}

/* m() measures the number of consonant sequences between k0 and j. if c is
   a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
   presence,

      <c><v>       gives 0
      <c>vc<v>     gives 1
      <c>vcvc<v>   gives 2
      <c>vcvcvc<v> gives 3
      ....
*/

static int m()
{  int n = 0;
   int i = k0;
   while(TRUE)
   {  if (i > j) return n;
      if (! cons(i)) break; i++;
   }
   i++;
   while(TRUE)
   {  while(TRUE)
      {  if (i > j) return n;
            if (cons(i)) break;
            i++;
      }
      i++;
      n++;
      while(TRUE)
      {  if (i > j) return n;
         if (! cons(i)) break;
         i++;
      }
      i++;
   }
}

/* vowelinstem() is TRUE <=> k0,...j contains a vowel */

static int vowelinstem()
{  int i; for (i = k0; i <= j; i++) if (! cons(i)) return TRUE;
   return FALSE;
}

/* doublec(j) is TRUE <=> j,(j-1) contain a double consonant. */

static int doublec(int j)
{  if (j < k0+1) return FALSE;
   if (b[j] != b[j-1]) return FALSE;
   return cons(j);
}

/* cvc(i) is TRUE <=> i-2,i-1,i has the form consonant - vowel - consonant
   and also if the second c is not w,x or y. this is used when trying to
   restore an e at the end of a short word. e.g.

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/

static int cvc(int i)
{  if (i < k0+2 || !cons(i) || cons(i-1) || !cons(i-2)) return FALSE;
   {  int ch = b[i];
      if (ch == 'w' || ch == 'x' || ch == 'y') return FALSE;
   }
   return TRUE;
}

/* ends(s) is TRUE <=> k0,...k ends with the string s. */

static int ends(char * s)
{  int length = s[0];
   if (s[length] != b[k]) return FALSE; /* tiny speed-up */
   if (length > k-k0+1) return FALSE;
   if (memcmp(b+k-length+1,s+1,length) != 0) return FALSE;
   j = k-length;
   return TRUE;
}

/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
   k. */

static void setto(char * s)
{  int length = s[0];
   memmove(b+j+1,s+1,length);
   k = j+length;
}

/* r(s) is used further down. */

static void r(char * s) { if (m() > 0) setto(s); }

/* step1ab() gets rid of plurals and -ed or -ing. e.g.

       caresses  ->  caress
       ponies    ->  poni
       ties      ->  ti
       caress    ->  caress
       cats      ->  cat

       feed      ->  feed
       agreed    ->  agree
       disabled  ->  disable

       matting   ->  mat
       mating    ->  mate
       meeting   ->  meet
       milling   ->  mill
       messing   ->  mess

       meetings  ->  meet

*/

static void step1ab()
{  if (b[k] == 's')
   {  if (ends("\04" "sses")) k -= 2; else
      if (ends("\03" "ies")) setto("\01" "i"); else
      if (b[k-1] != 's') k--;
   }
   if (ends("\03" "eed")) { if (m() > 0) k--; } else
   if ((ends("\02" "ed") || ends("\03" "ing")) && vowelinstem())
   {  k = j;
      if (ends("\02" "at")) setto("\03" "ate"); else
      if (ends("\02" "bl")) setto("\03" "ble"); else
      if (ends("\02" "iz")) setto("\03" "ize"); else
      if (doublec(k))
      {  k--;
         {  int ch = b[k];
            if (ch == 'l' || ch == 's' || ch == 'z') k++;
         }
      }
      else if (m() == 1 && cvc(k)) setto("\01" "e");
   }
}

/* step1c() turns terminal y to i when there is another vowel in the stem. */

static void step1c() { if (ends("\01" "y") && vowelinstem()) b[k] = 'i'; }


/* step2() maps double suffices to single ones. so -ization ( = -ize plus
   -ation) maps to -ize etc. note that the string before the suffix must give
   m() > 0. */

static void step2() { switch (b[k-1])
{
    case 'a': if (ends("\07" "ational")) { r("\03" "ate"); break; }
              if (ends("\06" "tional")) { r("\04" "tion"); break; }
              break;
    case 'c': if (ends("\04" "enci")) { r("\04" "ence"); break; }
              if (ends("\04" "anci")) { r("\04" "ance"); break; }
              break;
    case 'e': if (ends("\04" "izer")) { r("\03" "ize"); break; }
              break;
    case 'l': if (ends("\03" "bli")) { r("\03" "ble"); break; } /*-DEPARTURE-*/

 /* To match the published algorithm, replace this line with
    case 'l': if (ends("\04" "abli")) { r("\04" "able"); break; } */

              if (ends("\04" "alli")) { r("\02" "al"); break; }
              if (ends("\05" "entli")) { r("\03" "ent"); break; }
              if (ends("\03" "eli")) { r("\01" "e"); break; }
              if (ends("\05" "ousli")) { r("\03" "ous"); break; }
              break;
    case 'o': if (ends("\07" "ization")) { r("\03" "ize"); break; }
              if (ends("\05" "ation")) { r("\03" "ate"); break; }
              if (ends("\04" "ator")) { r("\03" "ate"); break; }
              break;
    case 's': if (ends("\05" "alism")) { r("\02" "al"); break; }
              if (ends("\07" "iveness")) { r("\03" "ive"); break; }
              if (ends("\07" "fulness")) { r("\03" "ful"); break; }
              if (ends("\07" "ousness")) { r("\03" "ous"); break; }
              break;
    case 't': if (ends("\05" "aliti")) { r("\02" "al"); break; }
              if (ends("\05" "iviti")) { r("\03" "ive"); break; }
              if (ends("\06" "biliti")) { r("\03" "ble"); break; }
              break;
    case 'g': if (ends("\04" "logi")) { r("\03" "log"); break; } /*-DEPARTURE-*/

 /* To match the published algorithm, delete this line */

} }

/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

static void step3() { switch (b[k])
{
    case 'e': if (ends("\05" "icate")) { r("\02" "ic"); break; }
              if (ends("\05" "ative")) { r("\00" ""); break; }
              if (ends("\05" "alize")) { r("\02" "al"); break; }
              break;
    case 'i': if (ends("\05" "iciti")) { r("\02" "ic"); break; }
              break;
    case 'l': if (ends("\04" "ical")) { r("\02" "ic"); break; }
              if (ends("\03" "ful")) { r("\00" ""); break; }
              break;
    case 's': if (ends("\04" "ness")) { r("\00" ""); break; }
              break;
} }

/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>. */

static void step4()
{  switch (b[k-1])
    {  case 'a': if (ends("\02" "al")) break; return;
       case 'c': if (ends("\04" "ance")) break;
                 if (ends("\04" "ence")) break; return;
       case 'e': if (ends("\02" "er")) break; return;
       case 'i': if (ends("\02" "ic")) break; return;
       case 'l': if (ends("\04" "able")) break;
                 if (ends("\04" "ible")) break; return;
       case 'n': if (ends("\03" "ant")) break;
                 if (ends("\05" "ement")) break;
                 if (ends("\04" "ment")) break;
                 if (ends("\03" "ent")) break; return;
       case 'o': if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't')) break;
                 if (ends("\02" "ou")) break; return;
                 /* takes care of -ous */
       case 's': if (ends("\03" "ism")) break; return;
       case 't': if (ends("\03" "ate")) break;
                 if (ends("\03" "iti")) break; return;
       case 'u': if (ends("\03" "ous")) break; return;
       case 'v': if (ends("\03" "ive")) break; return;
       case 'z': if (ends("\03" "ize")) break; return;
       default: return;
    }
    if (m() > 1) k = j;
}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
   m() > 1. */

static void step5()
{  j = k;
   if (b[k] == 'e')
   {  int a = m();
      if (a > 1 || a == 1 && !cvc(k-1)) k--;
   }
   if (b[k] == 'l' && doublec(k) && m() > 1) k--;
}

/* In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
   p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
   character of a string, (p[j+1] == '\0'). The stemmer adjusts the
   characters p[i] ... p[j] and returns the new end-point of the string, k.
   Stemming never increases word length, so i <= k <= j. To turn the stemmer
   into a module, declare 'stem' as extern, and delete the remainder of this
   file.
*/

int stem(char * p, int i, int j)
{  b = p; k = j; k0 = i; /* copy the parameters into statics */
   if (k <= k0+1) return k; /*-DEPARTURE-*/

   /* With this line, strings of length 1 or 2 don't go through the
      stemming process, although no mention is made of this in the
      published algorithm. Remove the line to match the published
      algorithm. */

   step1ab();
   if (k > k0) {
       step1c(); step2(); step3(); step4(); step5();
   }
   return k;
}

/*--------------------stemmer definition ends here------------------------*/

#include <stdio.h>
#include <stdlib.h>      /* for malloc, free */
#include <ctype.h>       /* for isupper, islower, tolower */

static char * s;         /* a char * (=string) pointer; passed into b above */

#define INC 50           /* size units in which s is increased */
static int i_max = INC;  /* maximum offset in s */

void increase_s()
{  i_max += INC;
   {  char * new_s = (char *) malloc(i_max+1);
      { int i; for (i = 0; i < i_max; i++) new_s[i] = s[i]; } /* copy across */
      free(s); s = new_s;
   }
}

#define LETTER(ch) (isupper(ch) || islower(ch))

string stemWord(string f)
{  /*while(TRUE)
   {  int ch = getc(f);
      if (ch == EOF) return;
      if (LETTER(ch))
      {  int i = 0;
         while(TRUE)
         {  if (i == i_max) increase_s();

            ch = tolower(ch); /* forces lower case

            s[i] = ch; i++;
            ch = getc(f);
            if (!LETTER(ch)) { ungetc(ch,f); break; }
         }*/
        cout<<f<<endl;
        cout<<f.c_str()<<endl;
         char* word  = new char[f.size()+1];
         strcpy(word,f.c_str());
         strcpy(s,word);
         cout<<word<<endl;
         cout<<s<<endl;
         s[stem(s,0,f.size()-1)+1] = 0;

         /* the previous line calls the stemmer and uses its result to
            zero-terminate the string in s */
         //printf("%s",s);
         string BrendanString = s;
         cout<<s;
         return s;

}




//END OF CODE FROM STEMMER



//Test program for AVL trees with IndexAVLNodes as nodes
/*int main(){
    AvlTree<string> t;
    vector<int>* myVector = new vector<int>;
    for(int i = 0;i<10;i++){
        myVector->push_back(i);
    }


    vector<int>* myVector1 = new vector<int>;
    myVector1->push_back(42);

    vector<int>* myVector2 = new vector<int>;
    myVector2->push_back(80);

    t.insert("dog",myVector);
    t.insert("aa",myVector1);
    t.insert("yo",myVector2);

    vector<int>* newVector = new vector<int>;
    newVector->push_back(14);
    newVector->push_back(20);
    t.insert("dog",newVector);

    t.printTree();
}*/
    // Test program for AVL tree
/*int main( )
{
    AvlTree<int> t, t2;
    int NUMS = 20;
    const int GAP  =   37;
    int i;
    int myArray[] = {1, 3, 6, 9, 11, 17, 18, 45, 24, 19, 18, 22, 20};
    int size = 13;

    cout << "Checking... (no more output means success)" << endl;

    /*for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );*/
/*
    for(i = 0;i<size;i++){
        t.insert(myArray[i]);
    }

    t.printTree( );
/*    if( t.findMin( ) != 1 || t.findMax( ) != NUMS - 1 )
        cout << "FindMin or FindMax error!" << endl;

    t2 = t;

    for( i = 1; i < NUMS; i++ )
        if( !t2.contains( i ) )
            cout << "Find error1!" << endl;
    if( t2.contains( 0 ) )
        cout << "ITEM_NOT_FOUND failed!" << endl;
*/
 /*   cout << "Test finished" << endl;
    return 0;
}
*/

//Test program for hash table
#include <iostream>
#include "SeparateChaining.h"

//Simple main
/*int main( )
{
    HashTable<string>* H = new HashTable<string>(6);

    const int NUMS = 4000;
    const int GAP  =   37;
    int i;

    string myArray[] =
    {"hey","there","dawg","how","Dawg","Dahn","Basketball","does","mouse","heydur","wasup","idk"};
    for(int i = 0;i<6;i++){
        H->insert(myArray[i]);
    }

    for(int i = 1;i<H->getSize();i++){
        cout<<(H->getList())[i].front()<<endl;
    }
*//*
    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        H.insert( i );
    for( i = 1; i < NUMS; i += 2 )
        H.remove( i );

    for( i = 2; i < NUMS; i += 2 )
        if( !H.contains( i ) )
            cout << "Contains fails " << i << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( H.contains( i ) )
            cout << "OOPS!!! " <<  i << endl;
    }

}*/

/**
 * A hash routine for string objects.
 */
int hash( const string & key , int size)
{
    int hashVal = 0;

    for( int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    hashVal %= size;
    if( hashVal < 0 )
        hashVal += size;

    return hashVal;
}

/*int main(){


    vector<string> myVec;
    string myArray[] = {"hey","there","dawg","how","Dawg","Dahn","Basketball","does","mouse","heydur","wasup","idk"
                       "Collete","Elise","Brendan","Irisa","random","word","hello","do","a","b","c","d","e","f","g",
                       "h","i","J","hola","yo","sup","herro"};
    for(int i = 0;i<sizeof(myArray)/sizeof(myArray[1]);i++){
        cout<<myArray[i]<<endl;
        myVec.push_back(myArray[i]);
    }

   StopWordsHashTable<string>* myTable =  new StopWordsHashTable<string>(10);

   for(int j = 0;j<myVec.size();j++){

        myTable->insert(myVec.at(j));
   }

   myTable->print();
   cout<<"Contains Elise? "<<myTable->contains("Elise")<<endl;

   cout<<"Contains sup? "<<myTable->contains("sup")<<endl;

   cout<<"Contains notdurr?"<<myTable->contains("notdurr")<<endl;

}
*/
//Testing hashtable Friday 11/21/14
/*int main(){


    vector<string> myVec;
    string myArray[] = {"hey","there","dawg","how","Dawg","Dahn","Basketball","does","mouse","heydur","wasup","idk"
                       "Collete","Elise","Brendan","Irisa","random","word","hello","do","a","b","c","d","e","f","g",
                       "h","i","J","hola","yo","sup","herro"};
    for(int i = 0;i<sizeof(myArray)/sizeof(myArray[1]);i++){
        cout<<myArray[i]<<endl;
        myVec.push_back(myArray[i]);
    }

   HashTable<string>* myTable =  new HashTable<string>(10);

   for(int j = 0;j<myVec.size();j++){

        myTable->insert(myVec.at(j),j);
   }

   myTable->print();
   cout<<"Contains Elise? "<<myTable->contains("Elise")<<endl;

   cout<<"Contains sup? "<<myTable->contains("sup")<<endl;

   cout<<"Contains notdurr?"<<myTable->contains("notdurr")<<endl;

}
*/
/*
string stemWord(string f);

int main(){

    s = new char[80];
    ifstream inputFile;
    inputFile.open("StopWordsStemmed.txt");

    vector<string> myVec;
    /*string myArray[] = {"hey","there","dawg","how","Dawg","Dahn","Basketball","does","mouse","heydur","wasup","idk"
                       "Collete","Elise","Brendan","Irisa","random","word","hello","do","a","b","c","d","e","f","g",
                       "h","i","J","hola","yo","sup","herro"};*/
    /*for(int i = 0;i<sizeof(myArray)/sizeof(myArray[1]);i++){
        cout<<myArray[i]<<endl;
        myVec.push_back(myArray[i]);
    }*/
    //get all words from input file
/*    string buffer;
    inputFile>>buffer;
    if(!inputFile){
        cout<<"file did not open"<<endl;
        exit(1);
    }
    ofstream output;
   StopWordsHashTable<string>* myTable =  new StopWordsHashTable<string>(509);
    while(inputFile ){
       myTable->insert(buffer);
       cout<<buffer<<endl;
       inputFile>>buffer;
    }

   output.open("StopWordsHashTable.txt");
   myTable->print(output);
   cout<<stemWord("again")<<endl;
   cout<<"Contains again? "<<myTable->contains(stemWord("again"))<<endl;
    cout<<stemWord("anything");
   cout<<"Contains anything? "<<myTable->contains(stemWord("anything"))<<endl;

   cout<<"Contains sure? "<<myTable->contains(stemWord("sure"))<<endl;

   cout<<"Contains subway? "<<myTable->contains(stemWord("subway"))<<endl;
}
*/
/*
int main(){
    ifstream input;
    input.open("IndexInputTest.txt");

    string word;
    char dummy[400];
    int page;
    int freq;

    while(input>>word){
        cout<<word<<endl;
        while(1){
            input>>page;
            if(page == -1){
                //go to next line
                //input.getline(dummy,390);
                break;
            }
            //if not hit end of page, frequency list
            input>>freq;
            cout<<page<<" : "<<freq<<endl;

        }

    }

}
*/

void andFunction(vector<string>& nextWords){
        cout<<"AND function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void orFunction(vector<string>& nextWords){
        cout<<"OR function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void notFunction(vector<string>& nextWords){
        cout<<"NOT function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){

            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void gtFunction(vector<string>& nextWords){
        cout<<"DATEGT function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void ltFunction(vector<string>& nextWords){
        cout<<"DATELT function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

void usernameFunction(vector<string>& nextWords){
        cout<<"USERNAME function:"<<endl;
        cout<<"Collected next words"<<endl;
        //print out all following words
        for(int y = 0;y<nextWords.size();y++){
            cout<<nextWords.at(y)<<" size: "<<nextWords.at(y).size()<<endl;
        }
}

/*int main(){
    while(1){
        //get user input

        //beginning of loop that
        cout<<"Please Enter Query (or END to Quit):";
        string userQuery;
        getline(cin,userQuery);
        cout<<"User Query Before Parsing: "<<userQuery<<endl;
        cout<<"size of User query: "<<userQuery.size()<<endl;
        string delimiter = " ";


        //eliminate any leading white space
        while(1){
           if(delimiter.compare(userQuery.substr(0,1)) == 0){
               userQuery = userQuery.substr(1,userQuery.size()-1);
           }
           else{
               break;
           }
        }
        //get first string of user keyword
        string firstCommand = userQuery.substr(0,userQuery.find(delimiter));
        cout<<"find(delimiter) "<<userQuery.find(delimiter)<<endl;
        cout<<"size of firstCommand "<<firstCommand.size()<<endl;
        //reset user string to not include first command

        //check that the first word is not END
        if(firstCommand.compare("END") == 0){
            cout<<"Selected to End program";
            return 0;
        }

        vector<string> keyWords;
        keyWords.push_back("AND");
        keyWords.push_back("OR");
        keyWords.push_back("NOT");
        keyWords.push_back("DATEGT");
        keyWords.push_back("DATELT");
        keyWords.push_back("USERNAME");

       //make sure first commmand is either AND or OR
       //RULE must start wiht AND or OR!!!!
        int commandFlag = 0;
        for(int i = 0;i<2;i++){
            if(firstCommand.compare(keyWords.at(i)) == 0){
                 commandFlag= 1;
                break;
            }
        }

        if(commandFlag != 1){
            cout<<"Need to Enter AND or OR as first word in Query!"<<endl;
            continue;
        }

        //gets rid of first word from user string
        userQuery = userQuery.substr(userQuery.find(delimiter)+1,userQuery.size());

        //cout<<"NewUserQuery "<<userQuery<<endl;
        //cout<<"size = "<<userQuery.size()<<endl;

        cout<<"First Command"<<firstCommand;
        string currKeyWord = firstCommand;

        //get all words until next keyword
        vector<string> nextWords;
        string currWord;

        //need loop that checks userQuery not empty
        while(!currKeyWord.empty()){
            cout<<"\nCurrKeyWord = "<<currKeyWord<<endl;
            //while loop that collects all following words after keyword;
            while(1){
                //eliminate whitespace
                while(1){
                   if(delimiter.compare(userQuery.substr(0,1)) == 0){
                       userQuery = userQuery.substr(1,userQuery.size()-1);
                   }
                   else{
                       break;
                   }
                }
                //check that userQuery string not empty
                if(userQuery.empty()){
                   currWord = "";
                   break;
                }
                else{
                    cout<<"UserQuery = "<<userQuery<<endl;
                    //get next word
                    currWord = userQuery.substr(0,userQuery.find(delimiter));
                    cout<<"CurrWord collected = "<<currWord<<endl;
                    //take off processed word from userQuery
                    if(userQuery.size() <= currWord.size()+1){
                        userQuery = "";
                    }
                    else{
                     userQuery = userQuery.substr(userQuery.find(delimiter)+1,userQuery.size());
                    cout<<"UserQuery after deletion = "<<userQuery<<endl;

                    }
                }

                //cout<<"inside loop"<<endl;
                bool breakFlag = 0;
                //check nextWord not match any of key words
                for(int i = 0;i<keyWords.size();i++){
                    if(currWord.compare(keyWords.at(i)) == 0){
                        breakFlag = 1;

                        break;
                    }
                }


                if(breakFlag == 1){
                    break;
                }

                //haven't encountered keyword yet
                nextWords.push_back(currWord);

            }

            //once break and have keyword

            //verify that at least got one argument
            if(nextWords.size()<1){
                cout<<"Keyword was followed by no arguments so just ignoring"<<endl;
                currKeyWord = currWord;
                cout<<"currKeyWord inside empty list catcher = "<<currKeyWord;
                continue;

            }

            //call the keyword function
            if(currKeyWord.compare("AND") == 0){
                andFunction(nextWords);

            }
            else if(currKeyWord.compare("OR") == 0){
                orFunction(nextWords);
            }
            else if(currKeyWord.compare("NOT") == 0){
                notFunction(nextWords);

            }else if(currKeyWord.compare("DATEGT") == 0){
                gtFunction(nextWords);

            }
            else if(currKeyWord.compare("DATELT") == 0){
                ltFunction(nextWords);
            }
            else if(currKeyWord.compare("USERNAME") == 0){
                usernameFunction(nextWords);
            }


            //set next key word to what was currently stored in currWord
            currKeyWord = currWord;
            cout<<currKeyWord<<endl;
            //clear next words
            nextWords.clear();
        }

    }
}

*/


/*int containsPage(vector<int>* list, int page){
    int counter = 0;
    vector<int>::iterator it;
    while(1){
        it = find(list->begin() + counter,list->end(),page);
        if(it != list->end()){
            if(*it%2 == 0){

                return (it-list->begin());
            }
            else{
                counter = *it;
            }
        }
        else{
            return -1;
        }

    }

}
*/
int containsPage(vector<int>* myList,int page){
    for(int i = 0;i<myList->size();i++){
        if(myList->at(i) == page){
            return i;
        }

        i++;
    }

    //if didn't find it
    return -1;
}

void insertion_sort(vector<int>& passedPages,
                                        vector<int>& passedTFs,
                                        int start,int end);

int main(){
/*    vector<int>* newVec = new vector<int>();
//    newVec->push_back(5);

    newVec->push_back(6);
    newVec->push_back(5);
    newVec->push_back(10);
    newVec->push_back(11);
    newVec->push_back(13);
    newVec->push_back(14);
    newVec->push_back(19);
    newVec->push_back(20);

    newVec->push_back(24);
    newVec->push_back(27);
    int page = 24;
    int answer = containsPage(newVec,page);
    cout<<"Index of page "<<page<<" is "<<answer<<endl;
    //print out vector
    cout<<"Printing out new vec before deletion:"<<endl;
    for(int i = 0;i<newVec->size();i++){
        cout<<newVec->at(i)<<endl;
    }
    cout<<endl;


    newVec->erase(newVec->begin() + answer);

    cout<<"Printing out new vec after deletion:"<<endl;
    for(int i = 0;i<newVec->size();i++){
        cout<<newVec->at(i)<<endl;
    }
    cout<<endl;

    cout<<"Log(18/7) = "<<log10(18.0/7)<<endl;
    cout<<"Log(18/8) = "<<log10(18.0/8)<<endl;
*/
/*    vector<int> firstVec,secondVec;
    for(int i = 0;i<10;i++){
        firstVec.push_back(i);
        secondVec.push_back(i);
        cout<<firstVec.at(i);
    }

    insertion_sort(firstVec,secondVec,0,firstVec.size()-1);
    cout<<"FirstVec: "<<endl;
    for(int j = 0;j<firstVec.size();j++){
       cout<<firstVec.at(j)<<endl;
    }

    cout<<"SecondVec: "<<endl;
    for(int j = 0;j<secondVec.size();j++){
       cout<<secondVec.at(j)<<endl;
    }

*/

    string string1 = "Danh";
    string string2 = " Danh ";
    string delimiter = " ";

    cout<<"comparison after elim white space = "<<string2.compare(string1)<<endl;

    //eliminate any leading white space
    while(1){
       if(delimiter.compare(string2.substr(0,1)) == 0){
           string2= string2.substr(1,string2.size()-1);
       }
       else{
           break;
       }
    }

    cout<<"String2 = "<<string2<<" size = "<<string2.size()<<endl;

    //eliminate trailing white space
    while(string2.size()>=1){
        cout<<"substring = "<<string2.substr(string2.size()-1,1);
        cout<<" size = "<<(string2.substr(string2.size()-1,1)).size()<<endl;
        if(delimiter.compare(string2.substr(string2.size()-1,
                                            1)) == 0){
            string2 = string2.substr(0,string2.size()-1);
        }
        else{
            break;
        }
    }

    cout<<"String2 = "<<string2<<" size = "<<string2.size()<<endl;
    cout<<"comparison after elim white space = "<<string2.compare(string1)<<endl;



    cout<<endl<<endl;
    string string3 = "Hey";
    string string4 = "there";
    string string5 = string3 + " " + string4;
    cout<<string5;

    string2 = "  2009-10-09T3849578";
    string1 = "2009-10-10";

    //eliminate any leading white space
    while(1){
       if(delimiter.compare(string2.substr(0,1)) == 0){
           string2= string2.substr(1,string2.size()-1);
       }
       else{
           break;
       }
    }

    //get the substring for t
    int index = string2.find("T");

    string2 = string2.substr(0,index);
    cout<<"String 2 = "<<string2<<endl;
    cout<<"Comparing "<<string1<< " vs. "<<string2<<endl;
    cout<<string1.compare(string2);

}


//http://mycodinglab.com/insertion-sort-algorithm/
void insertion_sort(vector<int>& passedPages,
                                        vector<int>& passedTFs,
                                        int start,int end){
     cout<<"made it inside insertion_sort"<<endl;
     int i, j;
     int tempPage;
     int tempTF;
     int length = end - start + 1;

     for (i = start + 1; i < start + length; i++) {
         j = i;
         while(j>start && (passedTFs.at(j-1)<passedTFs.at(j))){
            tempPage = passedPages.at(j);
            tempTF  = passedTFs.at(j);
            passedPages.at(j) = passedPages.at(j-1);
            passedTFs.at(j) = passedTFs.at(j-1);
            passedPages.at(j-1) = tempPage;
            passedTFs.at(j-1) = tempTF;

             j--;
         }//end of while loop

    }

}
