#include <iostream>               
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Book {
    char name[101];     
    char author[51];  
    int year;          
    float rating;       
};

const int max_kolich_book = 1000;
Book list_book[max_kolich_book];
int book_count = 0;
const char* filename = "books.txt";

void add_book() {
    if (book_count >= max_kolich_book) {
        cout << "Error: maximum book limit reached!" << endl;
        return;
    }

    cout << "--Add book--" << endl;
    
    
    cout << "Name:" << endl;
    char name[101];
    cin.ignore(); 
    cin.getline(name, 100);
    while(strlen(name) > 100) {
        cout << "Error: too many letters!" << endl;
        cout << "Name:" << endl;
        cin.getline(name, 100);
    }
    strcpy(list_book[book_count].name, name);
    
  
    cout << "Author:" << endl;
    char author[51];
    cin.getline(author, 50);
    while(strlen(author) > 50) {
        cout << "Error: too many letters!" << endl;
        cout << "Author:" << endl;
        cin.getline(author, 50);
    }
    strcpy(list_book[book_count].author, author);
    

    cout << "Year:" << endl;
    cin >> list_book[book_count].year;
    
  
    cout << "Rating:" << endl;
    cin >> list_book[book_count].rating;
    while(list_book[book_count].rating > 10) {
        cout << "Error: maximum 10!" << endl;
        cout << "Rating:" << endl;
        cin >> list_book[book_count].rating;
    }
    
    book_count++;
    cout << endl << "Book added!" << endl << endl;
}

void show_book() {
    cout << "--All books--" << endl;
    cout << endl;
    
    if (book_count == 0) {
        cout << "No books available." << endl << endl;
        return;
    }
    
    for(int i = 0; i < book_count; i++) {
        cout << "Book " << (i + 1) << ": " 
             << list_book[i].name << " | " 
             << list_book[i].author << " | " 
             << list_book[i].year << " | " 
             << list_book[i].rating << endl;
    }
    cout << endl;
}

void statistic() {
    cout << "--Book statistic--" << endl;
    cout << endl;
    
    if (book_count == 0) {
        cout << "No books for statistics" << endl;
        cout << endl;
        return;
    }


    char numb[5];
    int n = book_count;
    int digits = 0;
    int temp = n;
    

    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    

    temp = n;
    for (int i = digits - 1; i >= 0; i--) {
        numb[i] = '0' + (temp % 10);
        temp /= 10;
    }
    numb[digits] = '\0';

    cout << "Number of books read: ";
    if (n == 0) {
        cout << "0" << endl;
    } else {
        cout << numb << endl;
    }
    cout << endl;

    float num_ots = 0;
    float max_ots = 0;
    for(int i = 0; i < book_count; i++) {
        num_ots += list_book[i].rating;
        if (list_book[i].rating > max_ots) {
            max_ots = list_book[i].rating;
        }
    }
    

    cout << "Average rating: ";
    float avg = num_ots / book_count;
    cout << avg << endl;
    cout << endl;

    cout << "Best book(s): " << endl;
    for(int i = 0; i < book_count; i++) {
        if (list_book[i].rating == max_ots) {
            cout << list_book[i].name << endl;
        }
    }
    cout << endl;
}

void save() {
    ofstream out(filename, ios::trunc);
    if (out.is_open()) {
        for(int i = 0; i < book_count; i++) {
            out << list_book[i].name << "$" 
                << list_book[i].author << "$" 
                << list_book[i].year << "$" 
                << list_book[i].rating;
            
            if (i < book_count - 1) {
                out << endl;
            }
        }
    }
    out.close();  
    cout << "Data saved to " << filename << endl;
}


int string_to_int(const char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}


float string_to_float(const char* str) {
    float result = 0.0;
    float decimal = 0.1;
    bool after_decimal = false;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            after_decimal = true;
            continue;
        }
        
        if (str[i] >= '0' && str[i] <= '9') {
            if (after_decimal) {
                result += (str[i] - '0') * decimal;
                decimal *= 0.1;
            } else {
                result = result * 10 + (str[i] - '0');
            }
        }
    }
    return result;
}

void load_books() {
    ifstream file(filename);
    if (!file.is_open()) {
        return; 
    }
    
    char line[256];
    book_count = 0;
    
    while (file.getline(line, 256) && book_count < max_kolich_book) {
        char* tokens[4];
        int token_count = 0;
        
 
        char* token = strtok(line, "$");
        while (token != nullptr && token_count < 4) {
            tokens[token_count] = token;
            token_count++;
            token = strtok(nullptr, "$");
        }
        
        if (token_count == 4) {
    
            strncpy(list_book[book_count].name, tokens[0], 100);
            list_book[book_count].name[100] = '\0';
            
        
            strncpy(list_book[book_count].author, tokens[1], 50);
            list_book[book_count].author[50] = '\0';
            

            list_book[book_count].year = string_to_int(tokens[2]);
            

            list_book[book_count].rating = string_to_float(tokens[3]);
            
            book_count++;
        }
    }
    file.close();
}

void menu() {
    int num;                          
    cout << "--Book tracker by Lera--" << endl;
    cout << "1. Add book" << endl;
    cout << "2. Show all books" << endl;
    cout << "3. Show statistic" << endl;
    cout << "4. Exit" << endl;
    cout << "Select: ";
    cin >> num;
    
    switch(num) {
        case 1: 
            add_book(); 
            menu(); 
            break;
        case 2: 
            show_book();
            menu(); 
            break;
        case 3: 
            statistic();
            menu(); 
            break;
        case 4: 
            save(); 
            break;
        default: 
            cout << "Error :(" << endl; 
            menu();
    }
}

int main() {

    book_count = 0;
    

    load_books();
    

    menu();
    
    return 0; 
}
