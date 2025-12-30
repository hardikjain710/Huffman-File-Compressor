#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <fstream>

using namespace std;


struct Node{
    int freq;
    char ch;
    Node *left;
    Node *right;
    Node(int f, char c, Node *l=NULL, Node *r=NULL){
        freq = f;
        ch = c;
        left = l;
        right = r;
    }
};


struct compare{
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};


void countFreq(string input);
Node* buildHuffmanTree(vector<char>& arr, vector<int>& freq, int n);
void compressFile(string input, string output);
void decompressFile(string inputFileName, string outputFileName, Node* root);

#endif