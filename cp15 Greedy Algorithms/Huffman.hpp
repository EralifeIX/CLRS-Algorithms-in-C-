#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <map>
using namespace std;

struct Node{
    char ch;
    int freq;
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;
    Node() {}
    Node(char character, int frequency) : ch(character), freq(frequency) {}

};

struct compare{
    bool operator()(shared_ptr<Node> left, shared_ptr<Node> right){
        return left->freq > right->freq; // comparison object in priority queue
    }
};

shared_ptr<Node> CreateNode(char ch, int freq,
                            shared_ptr<Node> left,
                            shared_ptr<Node> right){
    shared_ptr<Node> node = shared_ptr<Node>();
    node->ch = ch;
    node->freq = freq;
    node->left = std::move(left);
    node->right = std::move(right);
    return node;
}

//Traverse Huffman Tree snd store code in map
void encode(shared_ptr<Node>& root, string str, map<char, string>& HuffmanCode){
    if(root== nullptr)
        return;

    //leaf node case
    if(!root->left && !root->right)
        HuffmanCode[root->ch] = str;

    encode(root->left, str + "0", HuffmanCode);
    encode(root->right, str + "1", HuffmanCode);

}

void decode(shared_ptr<Node>& root, int& index, string str) {
    if (root == nullptr)
        return;
    if (!root->left && !root->right){
        cout << root->ch;
    return;
}
    index++;
    if(str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

shared_ptr<Node>buildHuffmanTree(const string& text){
    unordered_map<char, int> freqlist;
    for(char ch : text)
        freqlist[ch]++;

    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, compare> pq;
    for (const auto &elem: freqlist) {
        pq.push(make_shared<Node>(elem.first, elem.second));
    }

    while (pq.size() > 1){
        shared_ptr<Node> left = pq.top();
        pq.pop();
        shared_ptr<Node> right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        shared_ptr<Node> newNode = make_shared<Node>('\0', sum);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    return pq.top();
}
/*

int main() {
    string text = "Huffman coding is a data compression algorithm.";

    // Build Huffman Tree and get the root
    shared_ptr<Node> root = buildHuffmanTree(text);

    // Traverse the Huffman Tree and store Huffman Codes in a map
    map<char, string> HuffmanCode;
    encode(root, "", HuffmanCode);

    // Print Huffman Codes
    cout << "Huffman Codes are:\n";
    for (const auto& pair : HuffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    // Print original string
    cout << "\nOriginal string was:\n" << text << '\n';

    // Print encoded string
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += HuffmanCode[ch];
    }
    cout << "\nEncoded string is:\n" << encodedStr << '\n';

    // Decode the encoded string
    int index = -1;
    cout << "\nDecoded string is:\n";
    while (index < static_cast<int>(encodedStr.size()) - 1) {
        decode(root, index, encodedStr);
    }
    cout << '\n';

    return 0;
}
*/



