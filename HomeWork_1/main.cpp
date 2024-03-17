#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class Author;
class AllAuthors{
    static std::map<int,Author*> authors;
public:
    static bool isNewID(int id){
        return authors.find(id) == authors.end()
        || id == -1
        || authors[id] == NULL;
    }
    static void removeAuthor(const int id){
        authors.erase(id);
    }
    static bool addAuthor(const int id, Author* const newAuthor){
        if(!isNewID(id))
            return false;
        authors[id] = newAuthor;
        return true;
    }
    static std::string getAuthorName(const int id);
};
std::map<int,Author*>AllAuthors::authors;


class Book;
class AllBooks{
    static std::map<int,Book*> books_by_id;
    static std::map<std::string,std::vector<int> > books_by_name;
public:
    static bool isNewID(int id){
        return books_by_id.find(id) == books_by_id.end()
        || id == -1
        || books_by_id[id] == NULL;
    }
    static void removeBook(const int id);
    static bool addBook(const int id, Book* newBook);
    static std::string getBookName(const int id);
};
std::map<int,Book*>AllBooks::books_by_id;
std::map<std::string,std::vector<int> > AllBooks::books_by_name;


class Book{
    std::string name;
    int nr_pages;
    const long long ISBN;
    std::vector<int> author_ids;
public:
    std::string getName() const {return name;}
    const long long getISBN() const {return ISBN;}
    int getNr_pages() const {return nr_pages;}
    std::vector<int> getAuthor_ids() const {return author_ids;}

    Book():ISBN(-1){}
    Book(std::string name,const int nr_pages, const long long ISBN, std::vector<int> const  author_ids):
        name(name),
        nr_pages(nr_pages),
        ISBN(ISBN),
        author_ids(author_ids)
        {AllBooks::addBook(ISBN,this);}
    ~Book(){AllBooks::removeBook(ISBN);}

    friend std::ostream& operator<<(std::ostream& out, const Book book);
};
std::ostream& operator<<(std::ostream& out, const Book book){
    out << "Title: "<< book.name;
    out << "; Page count: " << book.nr_pages;
    out << "; ISBN: " << book.ISBN;
    out << "; Authors: ";
    for(unsigned int i = 0 ; i < book.author_ids.size(); i ++ )
        out << i+1 << ": " << book.author_ids[i] << "(" <<
        AllAuthors::getAuthorName(book.author_ids[i]) << "), ";
    return out;
}

void AllBooks::removeBook(const int id){
    if(isNewID(id))
        return;
    books_by_name.erase(books_by_id[id]->getName());
    books_by_id.erase(id);
}
bool AllBooks::addBook(const int id, Book* newBook){
    if(!isNewID(id))
        return false;
    books_by_id[id] = newBook;
    books_by_name[newBook->getName()].push_back(id);
    return true;
}
std::string AllBooks::getBookName(const int id){
    if(!isNewID(id))
        return "NOT_FOUND";
    return books_by_id[id]->getName();
}



class Author{
    int const id;
    std::vector<Book> books;
    std::string name;
public:
    Author():id(-1){}
    Author(int const id, std::vector<Book> const books, std::string const name):
        id(id),
        books(books),
        name(name)
        {AllAuthors::addAuthor(id,this);}
    int getID() const{return id;}
    std::vector<Book> getBooks() const {return books;}
    std::string getName() const{return name;}

    void setName(std::string newName){
        name = newName;
    }
    ~Author(){AllAuthors::removeAuthor(id);}
};

std::string AllAuthors::getAuthorName(const int id){
    if(isNewID(id))
        return "NOT_FOUND";
    return authors[id]->getName();
}


class Renter{

};

class Employee{

};

class Library{

};

struct Tester{
    static void testAll(){
        testBook();
        testAllBooks();
        testAuthor();
        testAllAuthors();
    }
    static void testBook(){

    }
    static void testAllBooks(){

    }
    static void testAuthor(){

    }
    static void testAllAuthors(){

    }
};

int main()
{
    Tester::testAll();
}
