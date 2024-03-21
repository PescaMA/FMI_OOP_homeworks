#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <list>

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
        out << "---(AUTHOR INFO)--- Name: "<< myAuthor.name;
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
    Book():ISBN(0),name(""){}
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
        out << "---(BOOK INFO)--- Title: "<< book.name;
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
        out << "---(CATEGORY INFO)--- Name: "<< category.name;
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
    std::list<Book> books;
    std::list<Author> authors;
    std::list<Category> categories;

    Author& addAuthor(const Author& author){ /// returns index
        for(auto& currentAuthor:authors)
            if(author == currentAuthor)
                return currentAuthor;

        authors.push_back(author);
        authors.back().deleteAllBooksNames();

        return authors.back();
    }
    void addBookAuthors(Book& book){ /// also modifies the pointers from book!
        const std::vector<const Author*>& bookAuthors = book.getAuthors();
        int i = 0;
        for(auto& currentBookAuthor:bookAuthors){
            Author& myAuthor = addAuthor( *(currentBookAuthor) );
            myAuthor.addBook(book.getName());
            book.replaceAuthor(i, myAuthor );
            i++;
        }
    }
    Category& addCategory(const Category& category){ /// returns index
        for(auto& currentCategory:categories)
            if(category == currentCategory)
                return currentCategory;
        categories.push_back(category);
        categories.back().deleteAllBooks();

        return categories.back();
    }
    void addBookCategories(Book& book){ /// also modifies the pointers from book!
        const std::vector<const std::string*>& catNames = book.getCategories();
        int i=0;
        for(auto& currentAuthor:catNames){
            Category& myCategory = addCategory( *(currentAuthor) );
            myCategory.addBook(book);
            book.replaceCategory(i, myCategory.getName() );
            i++;
        }

    }
    Author& getAuthorReference(const std::string& penName){
        for(auto& currentAuthor:authors)
            if(currentAuthor.getPenName() == penName)
                return currentAuthor;
        static Author fake("","");
        return fake;
    }
    Book& getBookReference(const long long& ISBN){
        for(auto& currentBook:books)
            if(currentBook.getISBN() == ISBN)
                return currentBook;
        static Book fake=Book();
        return fake;
    }
    Category& getCategoryReference(const std::string& name){
        for(auto &currentCategory:categories)
            if(currentCategory.getName() == name)
                return currentCategory;
        static Category fake("");
        return fake;
    }
public:
    ///getters
    const int& getID(){return ID;}
    const std::string& getName(){return name;}
    const std::list<Book>& getBooks() const{return books;}
    const std::list<Author>& getAuthors() const{return authors;}
    const std::list<Category>& getCategories() const{return categories;}

    Author getAuthor(const std::string& penName) const{
        for(auto& currentAuthor:authors)
            if(currentAuthor.getPenName() == penName)
                return currentAuthor;
        return Author("","");
    }
    const Book getBook(const long long& ISBN) const{
        for(auto& currentBook:books)
            if(currentBook.getISBN() == ISBN)
                return currentBook;
        return Book();
    }
    const Category getCategory(const std::string& name) const{
        for(auto &currentCategory:categories)
            if(currentCategory.getName() == name)
                return currentCategory;
        return Category("");
    }
    const std::vector<Book> getBooks(const std::string& name) const{
        std::vector<Book> result;
        for(auto& currentBook:books)
            if(currentBook.getName() == name)
                result.push_back(currentBook);
        return result;
    }


    std::vector<Book> getBooksByAuthor(const std::string& penName) const{
        const Author myAuthor = getAuthor(penName);
        std::vector<Book> result;
        for(auto& currentBook:books){
                ///std::cout << myAuthor.getPenName() << ' ' << books[i];
            if(currentBook.findAuthor(myAuthor.getPenName()))
                result.push_back(currentBook);
        }
        return result;
    }
    std::vector<Author> getAuthorsOfBook(const long long& ISBN) const{
        const Book book = getBook(ISBN);
        std::vector<Author> result;
        std::vector<const  Author*> almost = book.getAuthors();
        for(unsigned int i = 0 ; i < almost.size(); i ++)
            result.push_back(*almost[i]);
        return result;
    }
    std::vector<Category> getCategoriesOfBook(const long long& ISBN) const{
        const Book book = getBook(ISBN);
        std::vector<Category> result;
        std::vector<const std::string*> almost = book.getCategories();
        for(unsigned int i = 0 ; i < almost.size(); i ++)
            result.push_back(getCategory(*almost[i]) );
        return result;
    }
    std::vector<Book> getBooksByCategory(const std::string& name) const{
        const Category& category = getCategory(name);
        std::vector<Book> result;
        std::vector<const  Book*> almost = category.getBooks();
        for(unsigned int i = 0 ; i < almost.size(); i ++)
            result.push_back(*almost[i]);
        return result;
    }

    /// constructors
    Library(const int& ID,const std::string& name,const std::list<Book>& books,
            const std::list<Author>& authors,const std::list<Category>& categories):
        ID(ID), name(name), books(books),
        authors(authors), categories(categories){}
    Library(const int& ID,const std::string& name):
        ID(ID), name(name) {}

    void addBook(Book book){
        addBookAuthors(book);
        addBookCategories(book);
        books.push_back(book);
    }
    bool removeAuthor(const std::string penName){
        Author& author = getAuthorReference(penName);
        if(author.getName() == "" || !author.getBooksNames().empty())
            return false;
        authors.remove(author);
        return true;
    }
    bool removeCategory(const std::string name){
        Category& category = getCategoryReference(name);
        if(category.getName() == "" || !category.getBooks().empty())
            return false;
        categories.remove(category);
        return true;
    }
    bool removeBook(const long long& ISBN){
        Book& book = getBookReference(ISBN);
        if(book.getName() == "")
            return false;
        for(auto& currentAuthor:book.getAuthors()){
            auto& myAuthor = getAuthorReference(currentAuthor->getPenName());
            myAuthor.removeBook(book.getName());
        }

       for(auto& currentCategory:book.getCategories()){
            auto& myCategory = getCategoryReference(*currentCategory);
            myCategory.removeBook(book);
        }
        books.remove(book);
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const Library& library){
        out << "---(LIBRARY INFO)--- Name: "<< library.name;
        out << "; ID: " << library.ID;
        out << "\n  Containing the following books:\n";
        unsigned int i = 0;
        for(auto& currentBook:library.books)
            out<<"    " << i+1 << ". " << currentBook;

        out << "\n  The authors from these books are:\n";
        i = 0;
        for(auto& currentAuthor:library.authors){
            out  <<"    " << i+1 << ". " << currentAuthor;
            i++;
        }
        out << "\n  The categories from these books are:\n";
        i = 0;
        for(auto& currentCategory:library.categories){
            out<<"    " << i+1 << ". " << currentCategory;
            i++;
        }

        return out;
    }
};
