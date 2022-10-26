#include "book_inventory.h"

Books book::read_database(std::string filepath){
    try{
        std::vector<std::string> my_book;
        Books my_books;
        std::string line;
        std::ifstream ifile(filepath);
        if (ifile) {
            size_t counter{0};
            for (std::string line ; getline(ifile, line); ){
                std::string delimiter = ",";
                size_t pos = 0;
                std::string token;
                line.append(",");
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    my_book.push_back(token);
                    line.erase(0, pos + delimiter.length());
                }
                my_books.push_back(Book());
                my_books[counter].title = my_book[1];
                my_books[counter].author = my_book[2];
                my_books[counter].cost = stof(my_book[3]);
                my_books[counter].isbn = my_book[4];
                my_books[counter].language_code = my_book[5];
                my_books[counter].num_pages = stoi(my_book[6]);
                my_books[counter].publisher = my_book[7];
                my_books[counter].count = stoi(my_book[8]);
                my_book.erase(my_book.begin(),my_book.end());
                counter++;
            }
            return my_books;
        }
        else{
            throw std::runtime_error("");
        }
        }
    catch(std::runtime_error e){
        Books my_books;
        std::cout<<"wrong filename !\n"<< e.what();
        throw std::runtime_error("wrong filename\n");
        return my_books;
    }
}


std::string book::search(Books inventory, std::string title){
    for (auto it = inventory.begin(); it != inventory.end(); it++){
        if (it->title == title)
            return it->isbn;        
    }
    return "none";
}


bool book::order(Books &inventory, Books &shopinglist, std::string isbn){
    for (auto it = inventory.begin(); it != inventory.end(); it++){
        if (it->isbn == isbn)
            if (it->count > 0){
                it->count -= 1;
                shopinglist.push_back(*it);
                return true;
            }        
    }
    return false;
}


double book::get_receipt(Books shopinglist){
    const std::string yellow("\033[1;33m");
    const std::string reset("\033[0m");
    const std::string green("\033[1;32m");
    const std::string cyan("\033[0;36m");
    const std::string red("\033[0;31m");
    double costs{0};

    std::cout << cyan <<"*********************************************************************************" << std::endl<<
                ">>"<< reset<<green<<"            title            ||         isbn         ||         price        "<< cyan << "<<" << reset<< std::endl<<
                 "---------------------------------------------------------------------------------" << std::endl;

    for (auto it = shopinglist.begin(); it != shopinglist.end(); it++){
        
        costs += it->cost;
        std::string substr_title;
        substr_title = it->title.substr(0,18);

        std::cout << cyan <<">>    "<< reset<< std::setw(18) << std::setw(18) << substr_title << "...    ||       "<< it->isbn  << "      ||         " <<
                  yellow << it->cost  << cyan <<"         <<"<< reset << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------"  << std::endl<<
                 cyan <<">>"<< reset<<"                                    "<<yellow << "Total Price"<< reset<<"       =>        "<<
                 yellow <<costs<<reset<<"         "<< cyan << "<<" << std::endl<<
                 "*********************************************************************************" << reset << std::endl;
    return costs;
}