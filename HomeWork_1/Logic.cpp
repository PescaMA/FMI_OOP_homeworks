#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>

/// libraries necessary for date/time
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class Date { /// Copied most the logic (haven't worked with <ctime>/dates before)
    std::string date; /// format is "YYYY-MM-DD"

  public:
    Date(std::string myDate) {
        parseDate(myDate); /// gives errors if invalid type
        date = myDate;
    }
    const std::string& getDate() const{ return date;}

    int operator-(const Date& other) {
        return getDaysDifference(parseDate(date), parseDate(other.date));
    }

// Function to parse a date string into a time_point
    static std::chrono::system_clock::time_point parseDate(const std::string& dateStr) {
        std::tm tm = {}; /// tm structure, which represents a calendar date and time broken down into its components (e.g., year, month, day, etc.)
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d"); // Checks format is "YYYY-MM-DD"
        if (ss.fail() || dateStr.size() != 10) {
            throw std::invalid_argument("Invalid date string");
        }
        std::time_t tt = std::mktime(&tm); /// transformms to Unix_epoch time.
        if (tt == -1) {
            throw std::runtime_error("Conversion of date string to time failed");
        }
        return std::chrono::system_clock::from_time_t(tt);
    }
// Function to get the current date as a string. format is "YYYY-MM-DD"
    static std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* timeinfo = std::localtime(&currentTime);
        std::ostringstream oss;
        oss << std::put_time(timeinfo, "%Y-%m-%d");
        return oss.str();
    }
// Function to get the number of days between two dates
    static int getDaysDifference(const std::chrono::system_clock::time_point& t1,
                                const std::chrono::system_clock::time_point& t2) {
        auto diff = t1 - t2; // Calculate the difference
        return (std::chrono::duration_cast<std::chrono::hours>(diff)).count() / 24; // Return the number of hours
    }
};


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
    int price; /// in cents
    int publishYear;
    int nr_pages;
    int stockCount = 1;

public:
    const long long& getISBN() const {return ISBN;}
    const int& getPrice() const {return price;}
    const std::string& getName() const {return name;}
    const std::vector<const Author*>& getAuthors() const {return authors;}
    const std::vector<const std::string*>& getCategories() const {return categoriesNames;}
    const int& getNr_pages() const {return nr_pages;}
    const int& getStockCount() const {return stockCount;}

    Book():ISBN(0),name(""){}
    Book(const long long& ISBN, const std::string& name,Author& author,
         const std::vector<const std::string*>& categoriesNames,
         const double& price, const int& publishYear,const int& nr_pages, const int& stockCount = 1 ):
        ISBN(ISBN), name(name), categoriesNames(categoriesNames),
        price(price), publishYear(publishYear), nr_pages(nr_pages),stockCount(stockCount)
        {authors.push_back(&author);}
    Book(const long long& ISBN, const std::string& name,   const std::vector<const Author*>& authors,
         const std::vector<const std::string*>& categoriesNames, const int& price,
         const int& publishYear,const int& nr_pages, const int& stockCount = 1 ):
        ISBN(ISBN), name(name), authors(authors),
        categoriesNames(categoriesNames), price(price),
        publishYear(publishYear),nr_pages(nr_pages), stockCount(stockCount){}

    void setPrice(const int& newPrice) { price = newPrice;}

    bool operator==(const Book& other) const{
        return this->ISBN == other.ISBN;
    }
    bool operator!=(const Book& other) const{
        return !(*this == other);
    }

    bool addBooks(const int& bookAmount){
        if(bookAmount < 0)
            return false;
        stockCount += bookAmount;
        return true;
    }
    bool removeBooks(const int& bookAmount){
        if(bookAmount < 0)
            return false;
        if(bookAmount > stockCount)
            return false;
        stockCount -= bookAmount;
        return true;
    }


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

    Book& operator=(const Book& other){
        /// Guard self assignment
        if (this == &other)
            return *this;

        /// Copy all the fields
        ISBN = other.ISBN;
        name = other.name;
        authors = other.authors;
        categoriesNames = other.categoriesNames;
        publishYear = other.publishYear;
        nr_pages = other.nr_pages;

        /// Return this for chained assignment
        return *this;
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
        out << "; Price: " << book.price / 100 << "." << book.price %100 << "$";
        out << "; Publish year: " << book.publishYear;
        out << "; Page count: " << book.nr_pages;
        out << "; Book count: " << book.stockCount;

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
class Customer{
    std::string name;
    std::string email;
public:
    std::string getName() const {return name;}
    std::string getEmail() const {return email;}
    void setName(const std::string& newName){ name = newName;}
    void setEmail(const std::string& newEmail){email = newEmail;}

    Customer(std::string name, std::string email):
        name(name),email(email){}

    bool operator==(Customer other){
        return name == other.name &&
        email == other.email;
    }
    friend std::ostream& operator<<(std::ostream& out, const Customer& myCustomer){
        out << "---(CUSTOMER INFO)--- Name: "<< myCustomer.name;
        out << "; Email: " << myCustomer.email;
        out << '\n';
        return out;
    }
};

class Loan{
    std::list<int> booksISBN; /// preferred not to store pointers.
    Customer customer;

};

class Library{
    const int ID;
    std::string name;
    /// using lists instead of vectors so pointers don't break.
    std::list<Customer> customers;
    std::list<Book> books;
    std::unordered_map<long long, Book*> booksByISBN;
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
        if(booksByISBN.find(ISBN) != booksByISBN.end())
            return *booksByISBN[ISBN];
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
///getters:
    const int& getID(){return ID;}
    const std::string& getName(){return name;}
    const std::list<Book>& getBooks() const{return books;}
    const std::list<Author>& getAuthors() const{return authors;}
    const std::list<Category>& getCategories() const{return categories;}
///setters/modifiers
    bool addBook(Book book){
        if(booksByISBN.find(book.getISBN()) != booksByISBN.end())
            return false;
        addBookAuthors(book);
        addBookCategories(book);
        books.push_back(book);
        booksByISBN[book.getISBN()] = &books.back();
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
        booksByISBN.erase(book.getISBN());
        return true;
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
/// Simple queries:
    const Author getAuthor(const std::string& penName) const{
        for(auto& currentAuthor:authors)
            if(currentAuthor.getPenName() == penName)
                return currentAuthor;
        return Author("","");
    }
    const Book getBook(const long long& ISBN) const{
        Book result = Book();
        if(booksByISBN.find(ISBN) != booksByISBN.end())
            result = *booksByISBN.at(ISBN); /// doesn't work with []. it needs to be const.
        return result;
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
/// join queries:
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
/// constructor & destructor
    Library(const int& ID,const std::string& name,const std::list<Book>& books,
            const std::list<Author>& authors,const std::list<Category>& categories):
        ID(ID), name(name), books(books),
        authors(authors), categories(categories){}
    Library(const int& ID,const std::string& name):
        ID(ID), name(name) {}

        ~Library(){
        /// Unnecessary.the pointers inside the classes are pointers to const so
        /// they don't need to be manually freed. Default destructor
        /// would have done the exact same.
        name = "";
        books.clear();
        authors.clear();
        categories.clear();

        std::cout << "Cleared a full library.";
    }
/// operators
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
