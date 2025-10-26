#include <iostream>               
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>

using namespace std;

int list_book_size = 0; 
string* list_book = nullptr;
string filename = "books.txt";

string* push_mas(string* old_array, int size, string s) {
    string* n_list_book = new string[size + 1]; 

    for (int i = 0; i < size; ++i) {
        n_list_book[i] = old_array[i];
    }

    n_list_book[size] = s;  

    delete[] old_array;
    return n_list_book;
}

void add_book() {
    string name;
    string auth;
    string year;
    string ots;

    cout << "--Add book--\nName:" << endl;
    cin >> name;
    while(name.length() > 100) {
        cout << "Error: too much letters(" << endl;
        cout << "Name:" << endl;
        cin >> name;
    }
    list_book = push_mas(list_book, list_book_size, name);
    list_book_size++;

    cout << "Author:" << endl;
    cin >> auth;
    while(auth.length() > 50) {
        cout << "Error: too much letters(" << endl;
        cout << "Author:" << endl;
        cin >> auth;
    }
    list_book = push_mas(list_book, list_book_size, auth);
    list_book_size++;

    cout << "Year:" << endl;
    cin >> year;
    list_book = push_mas(list_book, list_book_size, year);
    list_book_size++;

    cout << "Rating:" << endl;
    cin >> ots;
    while(stof(ots) > 10) {
        cout << "Error: maximum 10(" << endl;
        cout << "Rating:" << endl;
        cin >> ots;
    }
    list_book = push_mas(list_book, list_book_size, ots);
    list_book_size++;

    cout << endl;
    cout << "Book added!" << endl;
    cout << endl;
}

void show_book() {
    cout << "--All books--" << endl;
    cout << endl;
    
    int book_count = list_book_size / 4; 
    for(int i = 0; i < book_count; i++) {
        int base_index = i * 4;
        cout << "Book " << (i + 1) << ": " 
             << list_book[base_index] << " " 
             << list_book[base_index + 1] << " " 
             << list_book[base_index + 2] << " " 
             << list_book[base_index + 3] << endl;
    }
    cout << endl;
}

void statistic() {
    cout << "--Book statistic--" << endl;
    cout << endl;
    
    int book_count = list_book_size / 4; 
    string numb = to_string(book_count);

    cout << "Number of books read: " + numb << endl;
    cout << endl;

    if (book_count == 0) {
        cout << "No books for statistics" << endl;
        cout << endl;
        return;
    }

    float num_ots = 0;
    float max_ots = 0;
    for(int i = 0; i < book_count; i++) {
        float rating = stof(list_book[i * 4 + 3]);
        num_ots += rating;
        if (rating > max_ots) {
            max_ots = rating;
        }
    }
    
    cout << "Average rating: " + to_string(num_ots / book_count) << endl;
    cout << endl;

    cout << "Best book(s): " << endl;
    for(int i = 0; i < book_count; i++) {
        if (stof(list_book[i * 4 + 3]) == max_ots) {
            cout << list_book[i * 4] << endl;
        }
    }
    cout << endl;
}

void save() {
    ofstream out(filename, ios::trunc);
    if (out.is_open()) {
        for(int i = 0; i < list_book_size; ++i) {
            out << list_book[i] << "$"; 
            
            if ((i + 1) % 4 == 0) {
                out << endl; 
            }
        }
    }
    out.close();  
}

void menu() {
    int num;                          
    cout << "--Book tracker by Lera--\n1. Add book\n2. Show all books\n3. Show statistic\n4. Exit\n\nSelect:" << endl;
    cin >> num;
    switch(num) {
        case 1: add_book(); menu(); break;
        case 2: show_book(); menu(); break;
        case 3: statistic(); menu(); break;
        case 4: save(); break;
        default: cout << "Error :(" << endl; menu();
    }
}

int main() {
    
    list_book = new string[0];
    list_book_size = 0;

    if (filesystem::exists(filename)) {
        string s;
        ifstream file(filename);
        while (getline(file, s)) {
            stringstream ss(s);
            string segm;

            while(getline(ss, segm, '$')) {
                if (!segm.empty()) { 
                    list_book = push_mas(list_book, list_book_size, segm);
                    list_book_size++;
                }
            }
        }
    } else {
        ofstream outfile(filename);
        outfile.close();
    }

    menu();
    
    
    delete[] list_book;
    
    return 0; 
}