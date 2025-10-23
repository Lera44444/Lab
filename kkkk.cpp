#include <iostream>               
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::vector<std::string>> list_book;
std::string filename = "data_book.txt";

void add_book()
{
    using namespace std;

    std::string name;
    std::string auth;
    int year;
    float ots;

    std::cout << "--Add book--\nName:" << std::endl;
    std::cin >> name;
    while(name.length() > 100)
    {
        std::cout << "Error: too much latters(" << std::endl;
        std::cout << "Name:" << std::endl;
        std::cin >> name;
    }

    std::cout << "Author:" << std::endl;
    std::cin >> auth;
    while(auth.length() > 50)
    {
        std::cout << "Error: too much latters(" << std::endl;
        std::cout << "Author:" << std::endl;
        std::cin >> auth;
    }

    std::cout << "Year:" << std::endl;
    std::cin >> year;
    std::cout << "Otsenka:" << std::endl;
    std::cin >> ots;
    while(ots > 10)
    {
        std::cout << "Error: maximum 10(" << std::endl;
        std::cout << "Otsenka:" << std::endl;
        std::cin >> ots;
    }

    vector<string> segmlist = {name, auth, to_string(year), to_string(ots)};
    list_book.push_back(segmlist);

    std::cout<< std::endl;
    std::cout << "Book added!" << std::endl;
    std::cout<< std::endl;
    

}
void show_book()
{
    std::cout << "--All books--" << std::endl;
    std::cout << std::endl;
    for(int i {0}; i < list_book.size(); i++) {
            for (int ii {0}; ii < list_book[i].size(); ii++) {
                std::cout << list_book[i][ii] << " "; 
            }
            std::cout << std::endl; 
        }
    std::cout << std::endl;
}
void statistic()
{
    using namespace std;
    std::cout << "--Book statistic--" << std::endl;
    std::cout << std::endl;
    string numb = to_string(list_book.size());

    std::cout << "Number of books read: "+ numb << std::endl;
    std::cout << std::endl;

    float num_ots = 0;
    float max_ots = 0;
    for(int i {0}; i < list_book.size(); i++) {
        num_ots+=stof(list_book[i][3]);
        if (stof(list_book[i][3])>max_ots){
            max_ots=stof(list_book[i][3]);
        }
    }
    
    std::cout << "Middle otsenka: "+ to_string(num_ots/list_book.size()) << std::endl;
    std::cout << std::endl;

    std::cout << "Best book: " << std::endl;
    
    for(int i {0}; i < list_book.size(); i++) {
        if (stof(list_book[i][3])==max_ots){
            std::cout << list_book[i][0] << std::endl;
        }
    }
    std::cout << std::endl;
    
}

void save(){
    using namespace std;
    
    ofstream out(filename, std::ios::trunc);
    if (out.is_open())
    {
        for(int i {0}; i < list_book.size(); i++) {
            for (int ii {0}; ii < list_book[i].size(); ii++) {
                out << list_book[i][ii] << "$"; 
            }
            out << std::endl; 
        }
        
    }
    out.close();  
}


void menu(){
    int num;  
    using namespace std;                        
    cout << "--Book treker by Lera--\n1. Add book\n2. Show all books\n3. Show statistic\n4. Go out\n\nSelect:" << endl;
    cin >> num;
    switch(num)
    {
        case 1: add_book(); menu();break;
        case 2: show_book();menu();break;
        case 3: statistic();menu();break;
        case 4: save();break;
        default: cout << "Error :(" << endl; menu();
    }
    return;
}

int main()
{
    
    using namespace std;
    if (filesystem::exists(filename)){
        string s;
        ifstream file(filename);
        while (getline(file, s)){
            
            stringstream ss(s);
            string segm;
            vector<string> segmlist;

            while(getline(ss, segm, '$')){
                segmlist.push_back(segm);
            }

            
            list_book.push_back(segmlist);
            
        }
        
        
    } else {
        ofstream outfile(filename);
        outfile.close();
    }

    menu();
    return 0; 
}