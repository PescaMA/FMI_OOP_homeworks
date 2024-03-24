#include "Logic.cpp"
#include <cassert>

struct UnitTest{
    static std::ofstream testOut;
    static void runAllTests(){
        runDateTests();
        runAuthorTests();
        runBookTests();
        runCategoryTests();
        runLibraryTests();
    }
    static void runDateTests(){
        // Test case 1: Construct Date object with valid date
        Date date1("2024-03-24");
        try {
            Date::parseDate(date1.getDate());
        } catch (const std::exception& e) {
            assert("False negative" == false);
        }
        try {
            Date::parseDate(Date::getCurrentDate());
        } catch (const std::exception& e) {
            assert("GetCurrentDate invalid format" == false);
        }

        // Test case 2: Construct Date object with invalid date
        try {
            Date::parseDate("2024-12-11asbad");
            Date date2("InvalidDate");
        } catch (const std::exception& e) {
            assert(std::string(e.what()) == "Invalid date string");
        }

        // Test case 3: Calculate difference between two dates
        Date date3("2024-03-20");
        Date date4("2024-04-20");
        assert(date4 - date3 == 31);

        date3 = Date("2024-04-20");
        date4 = Date("2024-05-20");
        assert(date4 - date3 == 30);

        testOut << "All Date tests passed successfully!\n\n";
    }
    static void runAuthorTests(){
         // Creating an author
        Author tolkien("John Ronald Reuel Tolkien", "J.R.R. Tolkien");

        // Adding books
        std::string b1("The Hobbit"),b2("The Lord of the Rings");
        tolkien.addBook(b1);
        tolkien.addBook(b2);

        // Testing getters
        assert(tolkien.getName() == "John Ronald Reuel Tolkien");
        assert(tolkien.getPenName() == "J.R.R. Tolkien");
        const std::vector<const std::string*>& booksNames = tolkien.getBooksNames();
        assert(booksNames.size() == 2);
        assert(*booksNames[0] == "The Hobbit");
        assert(*booksNames[1] == "The Lord of the Rings");

        // Testing removeBook
        assert(tolkien.removeBook("The Silmarillion") == false); // Book not present
        assert(tolkien.removeBook("The Hobbit") == true); // Book removed
        assert(booksNames.size() == 1);

        // Testing deleteAllBooksNames
        tolkien.deleteAllBooksNames();
        assert(tolkien.getBooksNames().empty() == true); // No books after deletion


        testOut << tolkien << "All Author tests passed successfully!\n\n";
    }
    static void runBookTests() {
        Author Tolkien("John Ronald Reuel Tolkien", "J.R.R. Tolkien");
        std::vector<const std::string*> categories;
        std::string a = "Fantasy";
        categories.push_back(&a);

        // Create instances of Book
        Book hobbit(9783608987492, "The Hobbit", Tolkien, categories,2000, 1937, 310);
        Book hobbit1(9783608987492, "fake", Tolkien, std::vector<const std::string*>(),2150, 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", Tolkien, categories, 4999, 1954, 1178);

        // Test getters
        assert(hobbit.getISBN() == 9783608987492);
        assert(hobbit.getName() == "The Hobbit");
        assert(hobbit.getAuthors().size() == 1); // Assuming one author added
        assert(hobbit.getCategories().size() == 1); // Assuming one category added
        assert(*(hobbit.getCategories()[0]) == "Fantasy");
        assert(hobbit.getNr_pages() == 310);

        // Test addAuthor and removeAuthor
        Author newAuthor("New Author", "New Pen Name");
        hobbit.addAuthor(newAuthor);
        assert(hobbit.getAuthors().size() == 2);

        assert(hobbit.removeAuthor("wrong") == false);
        hobbit.removeAuthor("New Pen Name");
        assert(hobbit.getAuthors().size() == 1); // After removal, only one author should remain

        // Test operator== and operator!=
        assert(hobbit != LoR); // Different ISBNs
        assert(hobbit == hobbit1); // Same ISBNs (equality based on ISBN)

        testOut << hobbit;

        testOut << "All Book tests passed successfully!\n\n";
    }
    static void runCategoryTests(){
        Author Tolkien("John Ronald Reuel Tolkien", "J.R.R. Tolkien");
        std::vector<const std::string*> catNames;
        std::string a = "Fantasy";
        catNames.push_back(&a);
        Book hobbit(9783608987492, "The Hobbit", Tolkien, catNames,2000, 1937, 310);
        Book hobbit1(9783608987492, "fake", Tolkien, std::vector<const std::string*>(),2150, 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", Tolkien, catNames, 4999, 1954, 1178);

        Category fantasy("Fantasy");
        fantasy.addBook(hobbit);

        assert(fantasy.getName() == "Fantasy");
        assert(fantasy.removeBook(LoR) == false);
        assert(fantasy.removeBook(hobbit1) == true);
        assert(fantasy.getBooks().empty());

        testOut << fantasy;

        testOut << "All Category tests passed successfully!\n\n";
    }
    static void runLibraryTests(){
        // Create authors
        Author author1("John Smith", "jsmith");
        Author author2("Jane Doe", "jdoe");

        // Create categories
        std::vector<const std::string*> str1,str2;
        std::string a = "Fantasy", b = "Non-fiction";
        str1.push_back(&a);
        str2.push_back(&b);

        // Create books
        Book book1(123456789, "Book 1", author1, str1, 500, 2000, 300);
        Book book2(987654321, "Book 2", author2, str2, 300, 1998, 250);

        // Create library
        Library library(1, "My Library");


        Category cat1(a);

        // Add books to library
        library.addBook(book1);
        library.addBook(book2);


        // Test assertions
        assert(library.getBooks().size() == 2);
        assert(library.getAuthors().size() == 2);
        assert(library.getCategories().size() == 2);
        assert(library.getBooksByAuthor(author1.getPenName()).size() == 1);
        assert(library.getBooksByAuthor(author2.getPenName()).size() == 1);
        assert(library.getBooksByCategory(cat1.getName()).size() == 1);

        // Remove a book and check assertions
        assert(library.removeAuthor("jsmith") == false);
        assert(library.removeAuthor("j") == false);
        library.removeBook(123456789);
        assert(library.removeAuthor("jsmith") == true);
        assert(library.removeCategory("Non-fiction") == false);
        assert(library.getBooks().size() == 1);
        assert(library.getBooksByAuthor(author1.getPenName()).size() == 0);
        assert(library.getBooksByCategory(cat1.getName()).size() == 0);

        testOut<<library;
        testOut << "All library tests passed successfully!" << std::endl;
    }
};
std::ofstream UnitTest::testOut("Tests/unit.out");

int main()
{
    UnitTest::runAllTests();
    return 0;
}
