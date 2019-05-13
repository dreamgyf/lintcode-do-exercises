//
//  trie.h
//  lintcode-do-exercises
//
//  Created by 高云峰 on 2019/5/13.
//  Copyright © 2019 高云峰. All rights reserved.
//
//442. 实现 Trie（前缀树）

#ifndef trie_h
#define trie_h

#include <string>

using namespace std;

class Trie {
public:
    Trie() {
        // do intialization if necessary
        root = new node();
    }
    
    /*
     * @param word: a word
     * @return: nothing
     */
    void insert(string &word) {
        // write your code here
        node *temp = root;
        for(int i = 0;i < word.length();i++){
            if(word[i] >= 'a' && word[i] <= 'z'){
                if(temp->children[word[i] - 'a'] == nullptr)
                    temp->children[word[i] - 'a'] = new node;
                temp = temp->children[word[i] - 'a'];
            }
            else if(word[i] >= 'A' && word[i] <= 'Z'){
                if(temp->children[word[i] - 'A' + 26] == nullptr)
                    temp->children[word[i] - 'A' + 26] = new node;
                temp = temp->children[word[i] - 'A' + 26];
            }
        }
        temp->is_end = true;
    }
    
    /*
     * @param word: A string
     * @return: if the word is in the trie.
     */
    bool search(string &word) {
        // write your code here
        node *temp = root;
        for(int i = 0;i < word.length();i++){
            if(word[i] >= 'a' && word[i] <= 'z'){
                if(temp->children[word[i] - 'a'] == nullptr)
                    return false;
                temp = temp->children[word[i] - 'a'];
            }
            else if(word[i] >= 'A' && word[i] <= 'Z'){
                if(temp->children[word[i] - 'A' + 26] == nullptr)
                    return false;
                temp = temp->children[word[i] - 'A' + 26];
            }
        }
        return temp->is_end;
    }
    
    /*
     * @param prefix: A string
     * @return: if there is any word in the trie that starts with the given prefix.
     */
    bool startsWith(string &prefix) {
        // write your code here
        node *temp = root;
        for(int i = 0;i < prefix.length();i++){
            if(prefix[i] >= 'a' && prefix[i] <= 'z'){
                if(temp->children[prefix[i] - 'a'] == nullptr)
                    return false;
                temp = temp->children[prefix[i] - 'a'];
            }
            else if(prefix[i] >= 'A' && prefix[i] <= 'Z'){
                if(temp->children[prefix[i] - 'A' + 26] == nullptr)
                    return false;
                temp = temp->children[prefix[i] - 'A' + 26];
            }
        }
        return true;
    }
    
private:
    class node {
    public:
        node *children[52];
        bool is_end = false;
        node(){
            for(int i = 0;i < 52;i++)
                children[i] = nullptr;
        }
    };
    node *root;
};

#endif /* trie_h */
