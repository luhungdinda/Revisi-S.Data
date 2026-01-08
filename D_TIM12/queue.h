#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include "laundry_core.h"

using namespace std;

// ===== QUEUE UNTUK ANTRIAN LAUNDRY =====
struct QueueNode {
    string customerName;
    string serviceType;
    int estimatedTime;  // dalam menit
    string priority;     // "Normal" atau "Express"
    QueueNode* next;
    
    QueueNode(string name, string service, int time, string prio) 
        : customerName(name), serviceType(service), estimatedTime(time), 
          priority(prio), next(nullptr) {}
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
    
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    void enqueue(string name, string service, int time, string priority) {
        QueueNode* newNode = new QueueNode(name, service, time, priority);
        
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    void dequeue() {
        if (isEmpty()) {
            cout << "Antrian kosong!\n";
            return;
        }
        
        QueueNode* temp = front;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        size--;
    }
    
    QueueNode* peek() {
        return front;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Antrian kosong.\n";
            return;
        }
        
        QueueNode* current = front;
        int position = 1;
        
        cout << "\n===== ANTRIAN LAUNDRY (Queue - FIFO) =====\n\n";
        while (current != nullptr) {
            cout << "Posisi " << position++ << ":\n";
            cout << "  Customer    : " << current->customerName << "\n";
            cout << "  Layanan     : " << current->serviceType << "\n";
            cout << "  Estimasi    : " << current->estimatedTime << " menit\n";
            cout << "  Prioritas   : " << current->priority << "\n";
            cout << "  -----------------------------------\n";
            current = current->next;
        }
        cout << "Total antrian: " << size << " customer\n";
        cout << "==========================================\n";
    }
};

Queue laundryQueue;

void tambahAntrian() {
    system("cls");
    cout << "\n=== TAMBAH ANTRIAN LAUNDRY ===\n";
    
    cin.ignore(10000, '\n');
    string name, service, priority;
    int time;
    
    cout << "Nama Customer: ";
    getline(cin, name);
    
    cout << "Jenis Layanan: ";
    getline(cin, service);
    
    cout << "Estimasi Waktu (menit): ";
    cin >> time;
    cin.ignore();
    
    cout << "Prioritas (1=Normal, 2=Express): ";
    int pil;
    cin >> pil;
    priority = (pil == 2) ? "Express" : "Normal";
    
    laundryQueue.enqueue(name, service, time, priority);
    
    cout << "\n✓ Customer berhasil ditambahkan ke antrian!\n";
    cout << "Posisi antrian: " << laundryQueue.size << "\n";
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void prosesAntrian() {
    system("cls");
    cout << "\n=== PROSES ANTRIAN (DEQUEUE) ===\n";
    
    if (laundryQueue.isEmpty()) {
        cout << "Antrian kosong!\n";
    } else {
        QueueNode* current = laundryQueue.peek();
        cout << "Memproses customer:\n";
        cout << "  Nama     : " << current->customerName << "\n";
        cout << "  Layanan  : " << current->serviceType << "\n";
        cout << "  Estimasi : " << current->estimatedTime << " menit\n";
        cout << "  Prioritas: " << current->priority << "\n\n";
        
        laundryQueue.dequeue();
        cout << "✓ Customer berhasil diproses!\n";
        cout << "Sisa antrian: " << laundryQueue.size << " customer\n";
    }
    
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void tampilkanAntrian() {
    system("cls");
    laundryQueue.display();
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void menuQueue() {
    int pilihan;
    do {
        system("cls");
        cout << "\n=== QUEUE - ANTRIAN LAUNDRY ===\n";
        cout << "1. Tambah ke Antrian (Enqueue)\n";
        cout << "2. Proses Antrian (Dequeue)\n";
        cout << "3. Tampilkan Antrian\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: tambahAntrian(); break;
            case 2: prosesAntrian(); break;
            case 3: tampilkanAntrian(); break;
        }
    } while (pilihan != 0);
}

#endif
