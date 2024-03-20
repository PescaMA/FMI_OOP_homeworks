#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>

class Author{
    const int id;
    std::string name;
    std::string penName;
    int bookCount; /// amount of books in library.

public:
    Author(const int& id, const std::string& name, const std::string& penName):
        id(id),
        name(name),
        penName(penName),
        bookCount(0){}
    bool operator==(const Author& other) const{
        return this->id == other.id;
    }
    const int& getID() const{return id;}
    const int& getBookCount() const{return bookCount;}
    const std::string& getName() const {return name;}
    const std::string& getPenName() const {return penName;}

    void setName(const std::string& newName){ name = newName; }
    void setPenName(const std::string& newPenName){ penName = newPenName; }
    void addBook(){bookCount++;}
    void removeBook(){bookCount--;}
    friend std::ostream& operator<<(std::ostream& out,const Author& myAuthor){
        out << "(Author INFO) Name: "<< myAuthor.name;
        out << "; penName: " << myAuthor.penName;
        out << "; id: " << myAuthor.id;
        out << "; books in library: " << myAuthor.bookCount;
        out << '\n';
        return out;
    }
};

class Book{
    long long ISBN;
    std::string name;
    std::vector<Author*> authors;
    std::vector<std::string*> categoriesNames;
    int publishDate;
    int nr_pages;

public:
    const long long& getISBN()   const {return ISBN;}
    const std::string& getName() const {return name;}
    const std::vector<Author*>& getAuthors() const {return authors;}
    const std::vector<std::string*>& getCategories() const {return categoriesNames;}
    const int& getNr_pages() const {return nr_pages;}

    void addAuthor(Author& newAuthor){
        authors.push_back(&newAuthor);
    }
    bool removeAuthor(const int id){
        for(unsigned int i = 0 ; i < authors.size() ; i++)
            if(id == authors[i]->getID()){
                authors.erase(authors.begin() + i);
                return true;
            }
        return false;
    }
    Book(const long long& ISBN, const std::string& name,Author& author,
         const std::vector<std::string*>& categoriesNames, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        categoriesNames(categoriesNames),
        publishDate(publishDate),nr_pages(nr_pages)
        {authors.push_back(&author);}
    Book(const long long& ISBN, const std::string& name,   const std::vector<Author*>& authors,
         const std::vector<std::string*>& categoriesNames, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        authors(authors),
        categoriesNames(categoriesNames),
        publishDate(publishDate),nr_pages(nr_pages){}
    Book(const Book& other)
    : ISBN(other.ISBN),
      name(other.name),
      authors(other.authors),
      categoriesNames(other.categoriesNames),
      publishDate(other.publishDate),
      nr_pages(other.nr_pages) {}

      bool operator==(const Book& other) const{
        return this->ISBN == other.ISBN;
    }
    bool operator!=(const Book& other) const{
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out,const Book& book){
        out << "(BOOK INFO) Title: "<< book.name;
        out << "; ISBN: " << book.ISBN;

        out << "; Authors: ";
        for(unsigned int i = 0 ; i < book.authors.size(); i ++ )
            out << "(" << i+1 << ": " << book.authors[i]->getPenName() << ") ";
        out << "; Categories: ";
        for(unsigned int i = 0 ; i < book.categoriesNames.size(); i ++ )
            out << "(" << i+1 << ": " << *(book.categoriesNames[i]) << ") ";

        out << "; Page count: " << book.nr_pages;
        out << '\n';
        return out;
    }
};
class Category{
    std::string name;
    std::vector <Book*> libraryBooks;

public:
    Category(const std::string &name):name(name){}
    const std::string& getName() const{return name;}
    const std::vector<Book*>& getBooks() const {return libraryBooks;}

    void addBook(Book& book){
        libraryBooks.push_back(&book);
    }
    bool removeBook(Book& book){
        for(unsigned int i = 0 ; i < libraryBooks.size() ; i++)
            if(book == *libraryBooks[i]){
                libraryBooks.erase(libraryBooks.begin() + i);
                return true;
            }
        return false;
    }
    friend std::ostream& operator<<(std::ostream& out, const Category& category){
        out << "(CATEGORY INFO) Name: "<< category.name;
        out << "; Library books of this category: ";
        for(unsigned int i = 0 ; i < category.libraryBooks.size(); i ++ )
            out << "(" << i+1 << ": " << category.libraryBooks[i]->getName() << ") ";
        out << '\n';
        return out;
    }
};


