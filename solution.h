//
//  solution.h
//


/*



Modified by Hu Chuxuan on 11.04.2021
*/

#ifndef TRIE_SOLUTION_H
#define TRIE_SOLUTION_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

// Helper function you may or may not use, convert AList<char> into string
string CharList2Str(AList<char> list) {
    string s;
    for (int i = 0; i < list.getlength(); ++i) {
        s += list[i+1];
    }
    return s;
}

/* ========== Function headers for Ex.2 (i) ========== */
//This function search for extensions(with only one character) in dictionary
template<class T> AList<string> trie<T>::return_extend(AList<T> list, AList<string> &result) {
    /*
    STEP0: Preparation Works
    */
    if (list.getlength() == 0){
        cout<<"Empty Input!"<<endl;
        return result;
    }
    string input=CharList2Str(list);
    trienode<T>* pt=start;
    if (pt == 0){
        cout<<"No Extensions!"<<endl;
        return result;
    }
    T key = list[1];  // examine the first element of the input list
     
    /*
    STEP1: Find the appropriate starting point
    */
    while( pt!=0 && (*pt).getdata()!=key){
        pt=pt->getnext();
    }
    //if no appropriate starting point, we can not find extensions
    if(pt==0){
        cout<<"No Extensions!"<<endl;
        return result;
    }

    /*
    STEP2: Find where the last letter stops
    */
    while (1)
    {
        list.remove(1);
        //breaks if we have gone through all the letters
        if(list.getlength()==0) break;
        //update key value
        key=list[1];
        //update pointer
        pt=pt->getfollow();
        //search for the value equalling the key
        while(pt && pt->getdata()!=key){
            pt=pt->getnext();
        }
        //if no, simply print error message and break
        if(!pt){
            cout<<"No Extensions!"<<endl;
            return result;
        }
    }

    /*
    STEP3: Put everything linked by the next pointer into the return list
    */
   //now we are at a point where we stop at the position of the last letter
   //we should then check whether this one has a "stop"
    trienode<T>* check=pt->getfollow();
    while(check){
        if(check->getlast()){
            string ret=input+check->getdata();
            result.append(ret);
        }
        check=check->getnext();
    }
    if(result.getlength()==0) cout<<"No Extensions!"<<endl;
    return result;
}

/* ========== Function headers for Ex.2 (ii) ========== */
//This function checks for the prefixes with one or two characters shorter
template<class T> AList<string> trie<T>::return_prefix(AList<T> list, AList<string> &result) {

    //if we are given an empty string or only one char, there's no point for going through the function
    if (list.getlength() == 0 || list.getlength()==1){
        cout<<"Invalid Input!"<<endl;
        return result;
    }

    //get our input transferred into string
    string input=CharList2Str(list);
    int n=input.size();

    trienode<T>* pt=start;
    if (pt == 0){
        cout<<"Empty Dictionary!"<<endl;
        return result;
    }
    T key = list[1];  // examine the first element of the input list
     
    /*
    STEP1: Find the appropriate starting point
    */
    while( pt!=0 && (*pt).getdata()!=key){
        pt=pt->getnext();
    }
    if(pt==0){
        cout<<"No Prefixes!"<<endl;
        return result;
    }

    /*
    STEP2: Find where the last letter stops
    */
   //The difference is that the maximum of our output list is 2, as there will 1 or 2, so we can just list it out
    while (1)
    {
        list.remove(1);

        if(list.getlength()==2 && pt->getlast()){
            //This point should be added
            string ret(input,0,n-2);
            result.append(ret);

            //Then we check if the next one is also available
            key=list[1];
            pt=pt->getfollow();

            while(pt && pt->getdata()!=key) pt=pt->getnext();

            if(!pt) return result;
            else{
                string ret(input,0,n-1);
                result.append(ret);
                return result; 
            }
        }
        //if it is not reduced from 2, we deal with this separately
        if(list.getlength()==1 && pt->getlast()){
            string ret(input,0,n-1);
            result.append(ret);
            return result;
        }

        //This is for the updates at each level
        //In other words, we do this examination after each removal point check
        //(2->1)is a special case dealt with earlier
        key=list[1];
        pt=pt->getfollow();
        while(pt && pt->getdata()!=key){
            pt=pt->getnext();
        }
        if(!pt){
            cout<<"No Prefixes!"<<endl;
            return result;
        }
    }

    return result;
}

/* ========== Function headers for Ex.2 (iii) ========== */
//This function searches for words with only one character in difference
template<class T> AList<string> trie<T>::return_diff(AList<T> list, AList<string> &result) {
    int step=0;   //recording which char is different
    int n=list.getlength();
    if (list.getlength() == 0){
        cout<<"Empty Input!"<<endl;
        return result;
    }
    string input=CharList2Str(list);
    trienode<T>* pt=this->start;
    if (pt == 0){
        cout<<"Empty Dictionary!"<<endl;
        return result;
    }
    T key = list[1];  // examine the first element of the input list
    trienode<T>* real=0; //record where the pointer of next level should go

    while(step<n){
        key=list[step+1];   //update key value
        while(pt){          //go through all the following pointer at this level(each round for each node)
            if(pt->getdata()==key) real=pt;    //we will not have two pointers of same data
            else{
                //check if modified, this one is in dictionary or not
                AList<T> check=copy(pt,list,step);
                if(intrie(check)) {
                    result.append(CharList2Str(check));
                }
            }
            pt=pt->getnext();
        }
        if(!real) break;   //if there are no appropriate next ones, we can simply break
        pt=real->getfollow();  //going to the next level
        step++;
    }
    if(result.getlength()==0) cout<<"No Matches!"<<endl;
    return result;
}

// Helper function you may or may not use(not used)







template<class T> bool trie<T>::contains_extend(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result) {
    return 0;
}

// Helper function you may or may not use
template<class T> bool trie<T>::contains_diff(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result, int diff) {
    return 0;
}

#endif //TRIE_SOLUTION_H
