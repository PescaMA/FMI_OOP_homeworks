#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <cassert>
class Category;
class AllCategories{
    static std::map<std::string,Category*> categories;
public:
    static bool isNewId(std::string name){
        return categories.find(name) == categories.end()
        || categories[name] == NULL
        || name == "NONE";
    }
    static bool exists(Category* category);
    static bool addCategory(Category* category);
    static bool removeCategory(Category* category);
    static Category* findCategory(std::string name)
    {
        if(isNewId(name))
            return NULL;
        return categories[name];
    }
};
std::map<std::string,Category*> AllCategories::categories;

class Category{
    const std::string name;
public:
    Category():name("NONE"){}
    Category(std::string name):name(name){
        AllCategories::addCategory(this);
    }
    ~Category(){AllCategories::removeCategory(this);}
    std::string getName(){return name;}
};
bool AllCategories::exists(Category* category){
    if(category == NULL) return false;
    if(isNewId(category->getName())) return false;
    return categories[category->getName()] == category;
}
bool AllCategories::addCategory(Category* category){
    if(!isNewId(category->getName()))
        return false;
    categories[category->getName()] = category;
    return true;
}
bool AllCategories::removeCategory(Category* category){
    if(!exists(category))
        return false;
    categories.erase(category->getName());
    return true;
}

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
    static std::vector<Book*> getBooksByName(const std::string name){
        std::vector<Book* > result;
        if(books_by_name.find(name) == books_by_name.end())
            return result;
        for(int i=0; i <books_by_name[name].size(); i++)
            result.push_back(books_by_id[books_by_name[name][i]]);
        return result;
    }
};
std::map<long long,Book*>AllBooks::books_by_id;
std::map<std::string,std::vector<long long> > AllBooks::books_by_name;
long long AllBooks::maxID = 0;


class Book{
    const long long ISBN;
    std::string name;
    std::vector<int> author_ids;
    std::vector<Category*> categories;
    int publishDate;
    int nr_pages;


public:
    const long long getISBN() const {return ISBN;}
    std::string getName() const {return name;}
    std::vector<int> getAuthor_ids() const {return author_ids;}
    int getNr_pages() const {return nr_pages;}

    Book():ISBN(-1){}
    Book(std::string name,std::vector<int> const  author_ids, const std::vector<Category*> categories, const int publishDate,const int nr_pages):
        ISBN(AllBooks::getNextId()),
        name(name),
        author_ids(author_ids),
        categories(categories),
        publishDate(publishDate),
        nr_pages(nr_pages){AllBooks::addBook(ISBN,this);}
    Book(const long long ISBN,std::string name,std::vector<int> const  author_ids,const std::vector<Category*> categories, const int publishDate,const int nr_pages ):
        ISBN(ISBN),
        name(name),
        author_ids(author_ids),
        categories(categories),
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
    if(v->empty())
        books_by_name.erase(books_by_id[id]->getName());
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
        testCategory();
        testBook();
        testAuthor();
    }
    static void testCategory(){
        Category sf("SF"), fn("Fantasy");
        assert(AllCategories::isNewId("Test") == true);
        assert(AllCategories::isNewId("SF") == false);
        {
            Category sf2("SF");

        }
        assert(AllCategories::isNewId("SF") == false);
        assert(AllCategories::findCategory("Fantasy") != NULL);
    }
    static void testBook(){
        Category a("SF");
        std::vector<Category*> sf(1,&a);

        std::vector<int> author_ids;
        author_ids.push_back(1);
        author_ids.push_back(2);
        author_ids.push_back(3);
        {
        Book book1(1234567890, "Book1",author_ids, sf, 1992,121);
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
