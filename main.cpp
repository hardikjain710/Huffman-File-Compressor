#include "huffman.h"

// We need to access freqMap which is defined in huffman.cpp
extern map<char, int> freqMap;

int main() {
    string fileName;
    cout << "Enter the name of the file to compress (e.g. input.txt): ";
    cin >> fileName;


    countFreq(fileName);


    int n = freqMap.size();
    vector<char> arr;
    vector<int> freq;
    for(auto pair : freqMap){
        arr.push_back(pair.first);
        freq.push_back(pair.second);
    }

    Node* root = buildHuffmanTree(arr, freq, n);

    
    compressFile(fileName, "compressed.bin");
    

    decompressFile("compressed.bin", "output.txt", root);

    cout << "Process Complete! Check output.txt" << endl;

    return 0;
}