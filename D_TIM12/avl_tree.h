#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>
#include "laundry_core.h"

using namespace std;

// ===== AVL TREE UNTUK CUSTOMER LOYALTY RANKING =====
struct CustomerPoints {
    string customerName;
    int totalPoints;
    int transactionCount;
};

struct AVLNode {
    CustomerPoints data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(CustomerPoints d) : data(d), left(nullptr), right(nullptr), height(1) {}
};

AVLNode* avlRoot = nullptr;

int getHeight(AVLNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

int getBalance(AVLNode* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

void updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    updateHeight(y);
    updateHeight(x);
    
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    updateHeight(x);
    updateHeight(y);
    
    return y;
}

AVLNode* insertAVL(AVLNode* node, CustomerPoints data) {
    if (node == nullptr) {
        return new AVLNode(data);
    }
    
    if (data.totalPoints < node->data.totalPoints) {
        node->left = insertAVL(node->left, data);
    } else if (data.totalPoints > node->data.totalPoints) {
        node->right = insertAVL(node->right, data);
    } else {
        node->data = data;
        return node;
    }
    
    updateHeight(node);
    int balance = getBalance(node);
    
    // Left Left
    if (balance > 1 && data.totalPoints < node->left->data.totalPoints) {
        return rotateRight(node);
    }
    
    // Right Right
    if (balance < -1 && data.totalPoints > node->right->data.totalPoints) {
        return rotateLeft(node);
    }
    
    // Left Right
    if (balance > 1 && data.totalPoints > node->left->data.totalPoints) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left
    if (balance < -1 && data.totalPoints < node->right->data.totalPoints) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

void inorderDescendingAVL(AVLNode* node, int &rank) {
    if (node == nullptr) return;
    
    inorderDescendingAVL(node->right, rank);
    cout << rank++ << ". " << node->data.customerName 
         << " - " << node->data.totalPoints << " poin"
         << " (" << node->data.transactionCount << " transaksi)\n";
    inorderDescendingAVL(node->left, rank);
}

void addCustomerPoints(string name, int points) {
    CustomerPoints cp;
    cp.customerName = name;
    cp.totalPoints = points;
    cp.transactionCount = 1;
    avlRoot = insertAVL(avlRoot, cp);
}

void tampilkanLeaderboard() {
    system("cls");
    cout << "\n===== LEADERBOARD CUSTOMER (AVL Tree) =====\n";
    cout << "Self-Balancing Binary Search Tree\n\n";
    
    if (avlRoot == nullptr) {
        cout << "Belum ada data customer.\n";
    } else {
        int rank = 1;
        inorderDescendingAVL(avlRoot, rank);
    }
    
    cout << "\n==========================================\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void menuAVLTree() {
    int pilihan;
    do {
        system("cls");
        cout << "\n=== AVL TREE - CUSTOMER LOYALTY ===\n";
        cout << "1. Tambah Customer Points\n";
        cout << "2. Tampilkan Leaderboard\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: {
                cin.ignore(10000, '\n');
                string name;
                int points;
                cout << "Nama Customer: ";
                getline(cin, name);
                cout << "Total Points: ";
                cin >> points;
                addCustomerPoints(name, points);
                cout << "\n✓ Customer berhasil ditambahkan!\n";
                cout << "Tekan ENTER...";
                cin.ignore(10000, '\n');
                cin.get();
                break;
            }
            case 2:
                tampilkanLeaderboard();
                break;
        }
    } while (pilihan != 0);
}

#endif
