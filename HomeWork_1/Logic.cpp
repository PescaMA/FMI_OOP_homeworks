#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>
#include <set>

class Author{
    std::string name;
    std::string penName; /// must be unique!
    std::vector<const std::string*> booksNames;
public:
    Author(const std::string& name, const std::string& penName):
        name(name),
        penName(penName){}
    bool operator==(const Author& other) const{
        return this->penName == other.penName;
    }

    const std::vector<const std::string*>& getBooksNames() const{return booksNames;}
    const std::string& getName() const {return name;}
    const std::string& getPenName() const {return penName;}

    void setName(const std::string& newName){ name = newName; }
    void setPenName(const std::string& newPenName){ penName = newPenName; }

    void deleteAllBooksNames(){booksNames.clear();}
    void addBook(const std::string& name){booksNames.push_back(&name);}
    bool findBook(const std::string& name) const {
        for(unsigned int i = 0; i < booksNames.size(); i++)
        if(*booksNames[i] == name)
            return true;
        return false;
    }
    bool removeBook(const std::string& name){
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
        out << "; Books in library: ";
        for(unsigned int i = 0; i < myAuthor.booksNames.size(); i++)
            out << "(" << i+1 << ": " << *myAuthor.booksNames[i] << ") ";
        out << '\n';
        return out;
    }
};

class Book{
    long long ISBN; /// must be unique!
    std::string name;
    std::vector<const Author*> authors;
    std::vector<const std::string*> categoriesNames;
    int publishDate;
    int nr_pages;

public:
    const long long& getISBN()   const {return ISBN;}
    const std::string& getName() const {return name;}
    const std::vector<const Author*>& getAuthors() const {return authors;}
    const std::vector<const std::string*>& getCategories() const {return categoriesNames;}
    const int& getNr_pages() const {return nr_pages;}

    void addAuthor(const Author& newAuthor){
        authors.push_back(&newAuthor);
    }
    bool findAuthor(const std::string& penName) const{
        for(unsigned int i = 0 ; i < authors.size() ; i++)
            if(penName == authors[i]->getPenName())
                return true;
        return false;
    }
    bool removeAuthor(const std::string& penName){
        for(unsigned int i = 0 ; i < authors.size() ; i++)
            if(penName == authors[i]->getPenName()){
                authors.erase(authors.begin() + i);
                return true;
            }
        return false;
    }
    void replaceAuthor(const unsigned int& i, const Author &newAuthor){
        if(i > authors.size())
            return;
        authors[i] = &newAuthor;
    }
    void replaceCategory(const unsigned int& i, const std::string& newCategoryName){
        if(i > authors.size())
            return;
        categoriesNames[i] = &newCategoryName;
    }
    Book(const long long& ISBN, const std::string& name,Author& author,
         const std::vector<const std::string*>& categoriesNames, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        categoriesNames(categoriesNames),
        publishDate(publishDate),nr_pages(nr_pages)
        {authors.push_back(&author);}
    Book(const long long& ISBN, const std::string& name,   const std::vector<const Author*>& authors,
         const std::vector<const std::string*>& categoriesNames, const int& publishDate,const int& nr_pages ):
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
    std::string name; /// must be unique!
    std::vector <const Book*> libraryBooks;

public:
    Category(const std::string &name):name(name){}
    bool operator==(const Category& other) const{
        return name == other.name;}
    const std::string& getName() const{return name;}
    const std::vector<const Book*>& getBooks() const {return libraryBooks;}

    void addBook(const Book& book){
        libraryBooks.push_back(&book);
    }
    void deleteAllBooks(){libraryBooks.clear();}
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
    std::vector<Category> categories;

    int addAuthor(const Author& author){ /// returns index
        unsigned int i;
        for( i = 0; i < authors.size(); i++)
            if(author == authors[i])
                return i;

        authors.push_back(author);
        for(unsigned int i = 0 ; i < books.size(); i ++)
            std::cout << books[i];

        authors[i].deleteAllBooksNames();

        return i;
    }
    void addBookAuthors(Book& book){ /// also modifies the pointers from book!
        const std::vector<const Author*>& bookAuthors = book.getAuthors();
        for(unsigned int i = 0 ; i < books.size(); i ++)
            std::cout << books[i];

        for(unsigned int i = 0; i < bookAuthors.size(); i++){
            int insertIndex = addAuthor( *(bookAuthors[i]) );
            authors[insertIndex].addBook(book.getName());
            book.replaceAuthor(i, authors[insertIndex] );
        }
        for(unsigned int i = 0 ; i < books.size(); i ++)
            std::cout << books[i];
    }
    int addCategory(const Category& category){ /// returns index
        unsigned int i;
        for( i = 0; i < categories.size(); i++)
            if(category == categories[i])
                return i;
        categories.push_back(category);
        categories[i].deleteAllBooks();

        return i;
    }
    void addBookCategories(Book& book){ /// also modifies the pointers from book!
        const std::vector<const std::string*>& catNames = book.getCategories();
        for(unsigned int i = 0; i < catNames.size(); i++){
            int insertIndex = addCategory( *(catNames[i]) );
            categories[insertIndex].addBook(book);
            book.replaceCategory(i, categories[insertIndex].getName() );
        }

    }
public:
    ///getters
    const int& getID(){return ID;}
    const std::string& getName(){return name;}
    const std::vector<Book>& getBooks() const{return books;}
    const std::vector<Author>& getAuthors() const{return authors;}
    const std::vector<Category>& getCategories() const{return categories;}

    int getAuthorIndex(const std::string& penName) const{
        for(unsigned int i = 0 ; i < authors.size(); i ++)
            if(authors[i].getPenName() == penName)
                return i;
        return -1;
    }
    int getBookIndex(const long long& ISBN) const{
        for(unsigned int i = 0 ; i < books.size(); i ++)
            if(books[i].getISBN() == ISBN)
                return i;
        return -1;
    }
    std::vector<int> getBooksIndex(const std::string& name) const{
        std::vector<int> result;
        for(unsigned int i = 0 ; i < books.size(); i ++)
            if(books[i].getName() == name)
                result.push_back(i);
        return result;
    }
    int getCategoryIndex(const std::string& name) const{
        for(unsigned int i = 0 ; i < categories.size(); i ++)
            if(categories[i].getName() == name)
                return i;
        return -1;
    }

    std::vector<Book> getBooksByAuthor(Author myAuthor) const{
        std::vector<Book> result;
        for(unsigned int i = 0 ; i < books.size(); i ++){
                ///std::cout << myAuthor.getPenName() << ' ' << books[i];
            if(books[i].findAuthor(myAuthor.getPenName()))
                result.push_back(books[i]);
        }
        return result;
    }
    std::vector<Author> getAuthorsOfBook(Book book) const{
        std::vector<Author> result;
        std::vector<const  Author*> almost = book.getAuthors();
        for(unsigned int i = 0 ; i < almost.size(); i ++)
            result.push_back(*almost[i]);
        return result;
    }
    std::vector<Category> getCategoriesOfBook(Book book) const{
        std::vector<Category> result;
        std::vector<const std::string*> almost = book.getCategories();
        for(unsigned int i = 0 ; i < almost.size(); i ++)
            result.push_back(categories[getCategoryIndex (*almost[i])] );
        return result;
    }
    std::vector<Book> getBooksByCategory(Category category) const{
        std::vector<Book> result;
        std::vector<const  Book*> almost = category.getBooks();
        for(unsigned int i = 0 ; i < almost.size(); i ++)
            result.push_back(*almost[i]);
        return result;
    }

    /// constructors
    Library(const int& ID,const std::string& name,const std::vector<Book>& books,
            const std::vector<Author>& authors,const std::vector<Category>& categories):
        ID(ID), name(name), books(books),
        authors(authors), categories(categories){}
    Library(const int& ID,const std::string& name):
        ID(ID), name(name) {}

    void addBook(Book book){
        addBookAuthors(book);
        addBookCategories(book);
        books.push_back(book);


    }
    void removeBook(const long long& ISBN){
        Book& book = books[getBookIndex(ISBN)];
        for(unsigned int i = 0; i< book.getAuthors().size();i ++){
            int index = getAuthorIndex(book.getAuthors()[i]->getPenName());
            authors[index].removeBook(book.getName());
        }

        for(unsigned int i = 0; i< book.getCategories().size();i ++){
            int index = getCategoryIndex(*book.getCategories()[i]);
            categories[index].removeBook(book);
        }
        books.erase(books.begin() + getBookIndex(ISBN));
    }

    friend std::ostream& operator<<(std::ostream& out, const Library& library){
        out << "(Library INFO) Name: "<< library.name;
        out << "; ID: " << library.ID;
        out << "\n  Containing the following books:\n";
        unsigned int i;
        for(i = 0 ; i < library.books.size(); i ++)
            out<<"    " << i << ". " << library.books[i];

        out << "\n  The authors from these books are:\n";
        i = 0;
        for(std::vector<Author>::const_iterator it = library.authors.begin();
        it != library.authors.end(); it++){
            out  <<"    " << i << ". " << *it;
            i++;
        }
        out << "\n  The categories from these books are:\n";
        i = 0;
        for(std::vector<Category>::const_iterator it = library.categories.begin();
        it != library.categories.end(); it++){
            out<<"    " << i << ". " << *it;
            i++;
        }

        return out;
    }
};
