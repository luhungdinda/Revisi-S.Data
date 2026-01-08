#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// ===== HUFFMAN CODING UNTUK KOMPRESI DATA =====
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) return;
    
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->data] = code.empty() ? "0" : code;
        return;
    }
    
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

HuffmanNode* buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }
    
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;
    
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    if (pq.size() == 1) {
        HuffmanNode* single = pq.top();
        pq.pop();
        HuffmanNode* root = new HuffmanNode('\0', single->frequency);
        root->left = single;
        return root;
    }
    
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        
        HuffmanNode* right = pq.top();
        pq.pop();
        
        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    return pq.top();
}

string encodeHuffman(string text, unordered_map<char, string>& huffmanCodes) {
    HuffmanNode* root = buildHuffmanTree(text);
    generateCodes(root, "", huffmanCodes);
    
    string encoded = "";
    for (char c : text) {
        encoded += huffmanCodes[c];
    }
    
    return encoded;
}

void demoHuffmanCoding() {
    system("cls");
    cout << "\n===== HUFFMAN CODING - KOMPRESI DATA =====\n";
    cout << "Greedy Algorithm untuk Text Compression\n\n";
    
    string text;
    cin.ignore(10000, '\n');
    
    cout << "Masukkan teks untuk dikompresi: ";
    getline(cin, text);
    
    if (text.empty()) {
        cout << "Teks kosong!\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }
    
    unordered_map<char, string> huffmanCodes;
    string encoded = encodeHuffman(text, huffmanCodes);
    
    int originalBits = text.length() * 8;
    int compressedBits = encoded.length();
    double ratio = (1.0 - (double)compressedBits / originalBits) * 100;
    
    cout << "\n===== HASIL KOMPRESI =====\n";
    cout << "Teks asli        : " << text << "\n";
    cout << "Panjang          : " << text.length() << " karakter\n";
    cout << "Ukuran asli      : " << originalBits << " bits (ASCII 8-bit)\n\n";
    
    cout << "Huffman Codes (Variable-Length):\n";
    for (auto pair : huffmanCodes) {
        if (pair.first == ' ') {
            cout << "  [SPACE] -> " << pair.second << "\n";
        } else {
            cout << "  '" << pair.first << "' -> " << pair.second << "\n";
        }
    }
    
    cout << "\nTeks terkompresi : " << encoded << "\n";
    cout << "Ukuran kompresi  : " << compressedBits << " bits\n";
    cout << "Rasio kompresi   : " << fixed << setprecision(2) << ratio << "%\n";
    cout << "Penghematan      : " << (originalBits - compressedBits) << " bits\n";
    
    cout << "\n==========================\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.get();
}

void menuHuffman() {
    int pilihan;
    do {
        system("cls");
        cout << "\n=== HUFFMAN CODING ===\n";
        cout << "1. Kompresi Teks\n";
        cout << "2. Info Huffman Coding\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                demoHuffmanCoding();
                break;
            case 2:
                system("cls");
                cout << "\n=== INFO HUFFMAN CODING ===\n\n";
                cout << "Huffman Coding adalah algoritma kompresi lossless\n";
                cout << "yang menggunakan variable-length encoding.\n\n";
                cout << "Cara Kerja:\n";
                cout << "1. Hitung frekuensi setiap karakter\n";
                cout << "2. Buat min heap berdasarkan frekuensi\n";
                cout << "3. Build Huffman tree (merge 2 node terkecil)\n";
                cout << "4. Generate kode: left=0, right=1\n";
                cout << "5. Karakter frequent -> kode pendek\n";
                cout << "   Karakter rare -> kode panjang\n\n";
                cout << "Kompleksitas: O(n log n)\n";
                cout << "\nTekan ENTER...";
                cin.ignore(10000, '\n');
                cin.get();
                break;
        }
    } while (pilihan != 0);
}

#endif
