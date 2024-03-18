#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>

class Author;
class AllAuthors{
    static std::map<int,Author*> authors;
    static std::map<std::string, std::vector<int> >authors_by_name;
    static int maxID ;
public:
    static int getNextId(){
        maxID++;
        return maxID;
    }
    static bool isNewID(int id){
        return authors.find(id) == authors.end()
        || id == -1
        || authors[id] == NULL;
    }
    static void removeAuthor(const int id);
    static bool addAuthor(const int id, Author* const newAuthor);
    static std::string getAuthorName(const int id);
};
std::map<int,Author*>AllAuthors::authors;
std::map<std::string, std::vector<int> >AllAuthors::authors_by_name;
int AllAuthors::maxID = 0;


class Book;
class AllBooks{
    static long long maxID;
    static std::map<long long,Book*> books_by_id;
    static std::map<std::string,std::vector<long long> > books_by_name;
public:
    static long long getNextId(){
        maxID++;
        return maxID;
    }
    static bool isNewID(const long long id){
        return books_by_id.find(id) == books_by_id.end()
        || id == -1
        || books_by_id[id] == NULL;
    }
    static void removeBook(const long long id);
    static bool addBook(const long long id, Book* newBook);
    static std::string getBookName(const long long id);
};
std::map<long long,Book*>AllBooks::books_by_id;
std::map<std::string,std::vector<long long> > AllBooks::books_by_name;
long long AllBooks::maxID = 0;


class Book{
    const long long ISBN;
    std::string name;
    std::vector<int> author_ids;
    int publishDate;
    int nr_pages;

public:
    const long long getISBN() const {return ISBN;}
    std::string getName() const {return name;}
    std::vector<int> getAuthor_ids() const {return author_ids;}
    int getNr_pages() const {return nr_pages;}

    Book():ISBN(-1){}
    Book(std::string name,std::vector<int> const  author_ids, const int publishDate,const int nr_pages):
        ISBN(AllBooks::getNextId()),
        name(name),
        author_ids(author_ids),
        publishDate(publishDate),
        nr_pages(nr_pages){AllBooks::addBook(ISBN,this);}
    Book(const long long ISBN,std::string name,std::vector<int> const  author_ids, const int publishDate,const int nr_pages ):
        ISBN(ISBN),
        name(name),
        author_ids(author_ids),
        publishDate(publishDate),
        nr_pages(nr_pages){AllBooks::addBook(ISBN,this);}
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

void AllBooks::removeBook(const long long id){
    if(isNewID(id))
        return;
    std::vector<long long> *v = &books_by_name[books_by_id[id]->getName()];
    for(std::vector<long long>::iterator currentID = v->begin();
        currentID != v->end(); currentID++)
        if(*currentID == id){
            v->erase(currentID);break;}
    books_by_id.erase(id);
}
bool AllBooks::addBook(const long long id, Book* newBook){
    if(!isNewID(id))
        return false;
    maxID = std::max(maxID,id);
    books_by_id[id] = newBook;
    books_by_name[newBook->getName()].push_back(id);
    return true;
}
std::string AllBooks::getBookName(const long long id){
    if(isNewID(id))
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
    Author(std::vector<Book> const books, std::string const name):
        id(AllAuthors::getNextId()),
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
bool AllAuthors::addAuthor(const int id, Author* const newAuthor){
        if(!isNewID(id))
            return false;
        maxID = std::max(maxID,id);
        authors[id] = newAuthor;
        authors_by_name[newAuthor->getName()].push_back(id);
        return true;
    }
void AllAuthors::removeAuthor(const int id){
    if(isNewID(id)) return;
    std::vector<int> *v = &authors_by_name[authors[id]->getName()];
    for(std::vector<int>::iterator currentID = v->begin();
        currentID != v->end(); currentID++)
        if(*currentID == id){
            v->erase(currentID);break;}
    authors.erase(id);
}
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
        testAuthor();
    }
    static void testBook(){
        std::vector<int> author_ids;
        author_ids.push_back(1);
        author_ids.push_back(2);
        author_ids.push_back(3);
        {
        Book book1(1234567890, "Book1",author_ids, 1992,121);
        assert(AllBooks::addBook(book1.getISBN(),&book1) == false);
        assert(book1.getNr_pages() == 121);
        assert(AllBooks::isNewID(1234567890) == false);
        assert(AllBooks::getBookName(1234567890) == "Book1");
        } /// testing the destructor

        assert(AllBooks::isNewID(1234567890) == true);
        assert(AllBooks::getBookName(1234567890) == "NOT_FOUND");
    }
    static void testAuthor(){

        std::vector<Book> author_ids;
        Author author1(1, author_ids, "Author1");
        assert(AllAuthors::isNewID(1) == false);
        assert(AllAuthors::getAuthorName(1) == "Author1");

        AllAuthors::removeAuthor(1);
        assert(AllAuthors::isNewID(1) == true);
        assert(AllAuthors::getAuthorName(1) == "NOT_FOUND");
    }
};

int main()
{
    Tester::testAll();
}
