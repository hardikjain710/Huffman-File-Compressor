#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
struct Node
{
    int freq;
    char ch;
    Node *left;
    Node *right;
    Node(int f, char c, Node *l = NULL, Node *r = NULL)
    {
        freq = f;
        ch = c;
        left = l;
        right = r;
    }
};
struct compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

map<char, string> huffmanTable;

void decompressFile(string inputFileName, string outputFileName, Node *root)
{
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Error opening files for decompression!" << endl;
        return;
    }

    Node *curr = root;
    unsigned char buffer;

    while (inputFile.read((char *)&buffer, 1))
    {

        for (int i = 7; i >= 0; i--)
        {

            int bit = (buffer >> i) & 1;

            if (bit == 0)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }

            if (curr->left == NULL && curr->right == NULL)
            {
                outputFile.put(curr->ch);
                curr = root;
            }
        }
    }

    inputFile.close();
    outputFile.close();
}

void compressFile(string input, string output)
{
    ifstream inputFile(input);
    ofstream outputFile(output, ios::binary);
    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Could'nt find the file" << endl;
        return;
    }

    char ch;
    unsigned char buffer = 0;
    int count = 0;

    while (inputFile.get(ch))
    {
        string code = huffmanTable[ch];

        for (char bit : code)
        {
            if (bit == '0')
            {
                buffer = buffer << 1;
            }
            else
            {
                buffer = buffer << 1;
                buffer = buffer | 1;
            }
            count++;

            if (count == 8)
            {
                outputFile.put(buffer);
                count = 0;
                buffer = 0;
            }
        }
    }
    if (count > 0)
    {
        buffer = buffer << (8 - count);
        outputFile.put(buffer);
    }
    inputFile.close();
    outputFile.close();
}

void storeCodes(Node *root, string s)
{
    if (root == NULL)
        return;
    if (root->ch != '$')
    {
        huffmanTable[root->ch] = s;
        return;
    }
    storeCodes(root->left, s + '0');
    storeCodes(root->right, s + '1');
}

Node *printHCodes(vector<char> arr, vector<int> freq, int n)
{
    priority_queue<Node *, vector<Node *>, compare> h;

    for (int i = 0; i < n; i++)
    {
        h.push(new Node(freq[i], arr[i]));
    }
    while (h.size() > 1)
    {
        Node *l = h.top();
        h.pop();

        Node *r = h.top();
        h.pop();

        Node *node = new Node(l->freq + r->freq, '$', l, r);
        h.push(node);
    }
    storeCodes(h.top(), "");
    return h.top();
}
map<char, int> mp;
void countFreq(string input)
{
    ifstream inputFile(input);

    if (!inputFile.is_open())
    {
        cout << "Could not open file" << endl;
        return;
    }

    char ch;
    while (inputFile.get(ch))
    {
        mp[ch]++;
    }

    inputFile.close();
}

int main()
{
    string fileName;

    cout << "Enter the name of the file to compress (e.g. input.txt): ";
    cin >> fileName;

    countFreq(fileName);

    int n = mp.size();
    vector<char> arr;
    vector<int> freq;
    for (auto pair : mp)
    {
        arr.push_back(pair.first);
        freq.push_back(pair.second);
    }

    Node *root = printHCodes(arr, freq, n);

    compressFile(fileName, "compressed.bin");

    decompressFile("compressed.bin", "output.txt", root);

    return 0;
}
