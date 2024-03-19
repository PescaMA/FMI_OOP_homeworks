#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>

class Author{
    const int id;
    std::string name;
    std::string penName;
    int bookCount = 0; /// for logic inside Library class

public:
    Author(const int& id, const std::string& name, const std::string& penName):
        id(id),
        name(name),
        penName(penName){}
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
        return out;
    }
};

class Book{
    long long ISBN;
    std::string name;
    std::vector<Author*> authors;
    std::vector<std::string*> categories;
    int publishDate;
    int nr_pages;

public:
    long long getISBN()   const {return ISBN;}
    std::string getName() const {return name;}
    std::vector<Author*> getAuthors() const {return authors;}
    int getNr_pages() const {return nr_pages;}

    Book(const Book& other)
    : ISBN(other.ISBN),
      name(other.name),
      authors(other.authors),
      categories(other.categories),
      publishDate(other.publishDate),
      nr_pages(other.nr_pages) {}
    Book(const long long& ISBN,  std::string& name,   const std::vector<Author*>& authors,
         const std::vector<std::string*>& categories, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        authors(authors),
        categories(categories),
        publishDate(publishDate),nr_pages(nr_pages){}
    bool operator==(const Book& other) const{
        return this->ISBN == other.ISBN;
    }

    friend std::ostream& operator<<(std::ostream& out,const Book& book){
        out << "(BOOK INFO) Title: "<< book.name;
        out << "; ISBN: " << book.ISBN;

        out << "; Authors: ";
        for(unsigned int i = 0 ; i < book.authors.size(); i ++ )
            out << i+1 << ": " << book.authors[i]->getPenName() << " ";
        out << "; Categories: ";
        for(unsigned int i = 0 ; i < book.categories.size(); i ++ )
            out << i+1 << ": " << *(book.categories[i]) << " ";

        out << "; Page count: " << book.nr_pages;
        return out;
    }
};



int main()
{
    Author test(1,"a","b");
    std:: cout << test << std::endl;
    return 0;
}
