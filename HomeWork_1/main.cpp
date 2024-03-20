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
    std::vector<std::string*> categories;
    int publishDate;
    int nr_pages;

public:
    long long getISBN()   const {return ISBN;}
    std::string getName() const {return name;}
    std::vector<Author*> getAuthors() const {return authors;}
    std::vector<std::string*> getCategories() const {return categories;}
    int getNr_pages() const {return nr_pages;}

    void addAuthor(Author* const newAuthor){
        authors.push_back(newAuthor);
    }
    bool removeAuthor(const int id){
        for(unsigned int i = 0 ; i < authors.size() ; i++)
            if(id == authors[i]->getID()){
                authors.erase(authors.begin() + i);
                return true;
            }
        return false;
    }
    Book(const long long& ISBN, const std::string& name,Author* const& author,
         const std::vector<std::string*>& categories, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        categories(categories),
        publishDate(publishDate),nr_pages(nr_pages)
        {authors.push_back(author);}
    Book(const long long& ISBN, const std::string& name,   const std::vector<Author*>& authors,
         const std::vector<std::string*>& categories, const int& publishDate,const int& nr_pages ):
        ISBN(ISBN), name(name),
        authors(authors),
        categories(categories),
        publishDate(publishDate),nr_pages(nr_pages){}
    Book(const Book& other)
    : ISBN(other.ISBN),
      name(other.name),
      authors(other.authors),
      categories(other.categories),
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
            out << i+1 << ": " << book.authors[i]->getPenName() << " ";
        out << "; Categories: ";
        for(unsigned int i = 0 ; i < book.categories.size(); i ++ )
            out << i+1 << ": " << *(book.categories[i]) << " ";

        out << "; Page count: " << book.nr_pages;
        out << '\n';
        return out;
    }
};




struct UnitTest{
    static std::ofstream testOut;
    static void runAllTests(){
        runAuthorTests();
        runBookTests();

    }
    static void runAuthorTests(){
        Author Tolkien(1, "John Ronald Reuel Tolkien", "J.R.R. Tolkien");

        // Test getters
        assert(Tolkien.getID() == 1);
        assert(Tolkien.getName() == "John Ronald Reuel Tolkien");
        assert(Tolkien.getPenName() == "J.R.R. Tolkien");
        assert(Tolkien.getBookCount() == 0);

        // Test setters
        Tolkien.setName("New Name");
        Tolkien.setPenName("New Pen Name");
        assert(Tolkien.getName() == "New Name");
        assert(Tolkien.getPenName() == "New Pen Name");

        // Test addBook and removeBook
        Tolkien.addBook();
        Tolkien.addBook();
        assert(Tolkien.getBookCount() == 2);
        Tolkien.removeBook();
        assert(Tolkien.getBookCount() == 1);

        testOut << Tolkien;
    }
    static void runBookTests() {
        Author Tolkien(1, "John Ronald Reuel Tolkien", "J.R.R. Tolkien");
        std::vector<std::string*> categories;
        categories.push_back(new std::string("Fantasy"));

        // Create instances of Book
        Book hobbit(9783608987492, "The Hobbit", &Tolkien, categories, 1937, 310);
        Book hobbit1(9783608987492, "fake", &Tolkien, std::vector<std::string*>(), 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", &Tolkien, categories, 1954, 1178);

        // Test getters
        assert(hobbit.getISBN() == 9783608987492);
        assert(hobbit.getName() == "The Hobbit");
        assert(hobbit.getAuthors().size() == 1); // Assuming one author added
        assert(hobbit.getAuthors()[0]->getID() == 1); // Assuming Tolkien's ID is 1
        assert(hobbit.getCategories().size() == 1); // Assuming one category added
        assert(*(hobbit.getCategories()[0]) == "Fantasy");
        assert(hobbit.getNr_pages() == 310);

        // Test addAuthor and removeAuthor
        Author newAuthor(2, "New Author", "New Pen Name");
        hobbit.addAuthor(&newAuthor);
        assert(hobbit.getAuthors().size() == 2);
        assert(hobbit.getAuthors()[1]->getID() == 2); // Assuming new author's ID is 2

        hobbit.removeAuthor(2);
        assert(hobbit.getAuthors().size() == 1); // After removal, only one author should remain

        // Test operator== and operator!=
        assert(hobbit != LoR); // Different ISBNs
        assert(hobbit == hobbit1); // Same ISBNs (equality based on ISBN)

        testOut << hobbit;
        // Free memory allocated for string pointers in categories vector
        for (unsigned int i = 0; i < categories.size() ; i++)
            delete categories[i];
    }
};
std::ofstream UnitTest::testOut("Tests/unit.out");

int main()
{
    UnitTest::runAllTests();
    return 0;
}
