#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>
using namespace std;
class Book{
    long long ISBN;
    std::string name;
    std::vector<int> author_ids;
    std::vector<std::string*> categories;
    int publishDate;
    int nr_pages;

public:
    long long getISBN()   const {return ISBN;}
    std::string getName() const {return name;}
    std::vector<int> getAuthor_ids() const {return author_ids;}
    int getNr_pages() const {return nr_pages;}

    Book(const Book& other)
    : ISBN(other.ISBN),
      name(other.name),  // invoking copy constructor for 'name'
      author_ids(other.author_ids),
      categories(other.categories),
      publishDate(other.publishDate),
      nr_pages(other.nr_pages) {}
    Book(const long long& ISBN,  std::string& name,   const std::vector<int>& author_ids,
         const std::vector<std::string*>& categories, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        author_ids(author_ids),
        categories(categories),
        publishDate(publishDate),nr_pages(nr_pages){}
    bool operator==(const Book& other) const{
        return this->ISBN == other.ISBN;
    }

    friend std::ostream& operator<<(std::ostream& out,const Book& book){
        out << "(BOOK INFO) Title: "<< book.name;
        out << "; ISBN: " << book.ISBN;

        out << "; Authors: ";
        for(unsigned int i = 0 ; i < book.author_ids.size(); i ++ )
            out << i+1 << ": " << book.author_ids[i] << " ";
        out << "; Categories: ";
        for(unsigned int i = 0 ; i < book.categories.size(); i ++ )
            out << i+1 << ": " << *(book.categories[i]) << " ";

        out << "; Page count: " << book.nr_pages;
        return out;
    }
};

class Author{
    const int id;
    std::string penName;
    std::string name;
    std::vector<Book> books;

public:
    Author(const int id, const std::string name, const std::vector<Book> books= std::vector<Book>()):
        id(id),
        name(name),
        books(books){}
    bool operator==(const Author& other) const{
        return this->id == other.id;
    }
    int getID() const{return id;}
    std::vector<Book> getBooks() const {return books;}
    std::string getName() const {return name;}

    void setName(const std::string& newName){ name = newName; }
    void setPenName(const std::string& newPenName){ penName = newPenName; }
    void addBook(const Book& newBook){ books.push_back(newBook); }
    bool removeBook(const Book& removeBook){
        for(unsigned int i = 0; i < books.size(); i++)
            if(books[i] == removeBook){
                books.erase(books.begin() + i);
                return true;
            }
        return false;
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
