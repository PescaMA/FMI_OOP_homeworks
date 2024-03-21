#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>
#include <set>

class Author{
    int id;
    std::string name;
    std::string penName;
    std::vector<const std::string*> booksNames;
public:
    Author(const int& id, const std::string& name, const std::string& penName):
        id(id),
        name(name),
        penName(penName){}
    bool operator==(const Author& other) const{
        return this->id == other.id;
    }
    bool operator<(const Author& other) const{
        return this->id < other.id;
    }

    const int& getID() const{return id;}
    const std::vector<const std::string*>& getBooksNames() const{return booksNames;}
    const std::string& getName() const {return name;}
    const std::string& getPenName() const {return penName;}

    void setName(const std::string& newName){ name = newName; }
    void setPenName(const std::string& newPenName){ penName = newPenName; }
    /// note: no setter for id as it should not be changed.

    void deleteAllBooksNames(){booksNames.clear();}
    void addBook(const std::string &name){booksNames.push_back(&name);}
    bool removeBook(std::string name){
        for(unsigned int i = 0; i < booksNames.size(); i++)
        if(*booksNames[i] == name){
            booksNames.erase(booksNames.begin() + i);
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<(std::ostream& out,const Author& myAuthor){
        out << "(Author INFO) Name: "<< myAuthor.name;
        out << "; PenName: " << myAuthor.penName;
        out << "; Id: " << myAuthor.id;
        out << "; Books in library: ";
        for(unsigned int i = 0; i < myAuthor.booksNames.size(); i++)
            out << "(" << i << ": " << *myAuthor.booksNames[i] << ") ";
        out << '\n';
        return out;
    }
};

class Book{
    long long ISBN;
    std::string name;
    std::vector<const Author*> authors;
    std::vector<std::string*> categoriesNames;
    int publishDate;
    int nr_pages;

public:
    const long long& getISBN()   const {return ISBN;}
    const std::string& getName() const {return name;}
    const std::vector<const Author*>& getAuthors() const {return authors;}
    const std::vector<std::string*>& getCategories() const {return categoriesNames;}
    const int& getNr_pages() const {return nr_pages;}

    void addAuthor(const Author& newAuthor){
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
    void replaceAuthor(const unsigned int& i, Author* &newAuthor){
        if(i > authors.size())
            return;
        authors[i] = newAuthor;
    }
    Book(const long long& ISBN, const std::string& name,Author& author,
         const std::vector<std::string*>& categoriesNames, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        categoriesNames(categoriesNames),
        publishDate(publishDate),nr_pages(nr_pages)
        {authors.push_back(&author);}
    Book(const long long& ISBN, const std::string& name,   const std::vector<const Author*>& authors,
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
    std::vector <const Book*> libraryBooks;

public:
    Category(const std::string &name):name(name){}
    const std::string& getName() const{return name;}
    const std::vector<const Book*>& getBooks() const {return libraryBooks;}

    void addBook(const Book& book){
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

class Library{
    const int ID;
    std::string name;
    std::vector<Book> books;
    std::vector<Author> authors;
    std::set< Category> categories;

public:
    const int& getID(){return ID;}
    const std::string& getName(){return name;}
    const std::vector<Book>& getBooks() const{return books;}
    const std::vector<Author>& getAuthors() const{return authors;}
    const std::set<Category>& getCategories() const{return categories;}

    Library(const int& ID,const std::string& name,const std::vector<Book>& books,const std::vector<Author>& authors,const std::set<Category>& categories):
        ID(ID), name(name), books(books),
        authors(authors), categories(categories){}
    Library(const int& ID,const std::string& name):
        ID(ID), name(name) {}
    int addAuthor(const Author& author){ /// returns index
        unsigned int i;
        for( i = 0; i < authors.size(); i++)
            if(author == authors[i])
                return i;
        authors.push_back(author);
        authors[i].deleteAllBooksNames();
        return i;
    }
    void addBookAuthors(Book& book){ /// also modifies the pointers from book!
        const std::vector<const Author*>& bookAuthors = book.getAuthors();
        for(unsigned int i = 0; i < bookAuthors.size(); i++){
            int insertIndex = addAuthor( *(bookAuthors[i]) );
            authors[insertIndex].addBook(book.getName());
            Author* newAuthor = &authors[insertIndex];
            book.replaceAuthor(i, newAuthor );
        }
    }
    void addBook(Book book){
        addBookAuthors(book);
        books.push_back(book);
    }

    friend std::ostream& operator<<(std::ostream& out, const Library& library){
        out << "(Library INFO) Name: "<< library.name;
        out << "; ID: " << library.ID;
        out << "Containing the following books:\n";
        unsigned int i;
        for(i = 0 ; i < library.books.size(); i ++)
            out << "\n  " << i << ". " << library.books[i];

        out << "The authors frome these books are:\n";
        i = 0;
        for(std::vector<Author>::const_iterator it = library.authors.begin();
        it != library.authors.end(); it++){
            out << "\n  " << i << ". " << *it;
            i++;
        }
        out << "The categories frome these books are:\n";
        i = 0;
        for(std::set<Category>::const_iterator it = library.categories.begin();
        it != library.categories.end(); it++){
            out << "\n  " << i << ". " << *it;
            i++;
        }

        return out;
    }
};
