#include "Logic.cpp"

struct UnitTest{
    static std::ofstream testOut;
    static void runAllTests(){
        runAuthorTests();
        runBookTests();
        runCategoryTests();
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
        Book hobbit(9783608987492, "The Hobbit", Tolkien, categories, 1937, 310);
        Book hobbit1(9783608987492, "fake", Tolkien, std::vector<const std::string*>(), 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", Tolkien, categories, 1954, 1178);

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
    }
    static void runCategoryTests(){
        Author Tolkien("John Ronald Reuel Tolkien", "J.R.R. Tolkien");
        std::vector<const std::string*> catNames;
        std::string a = "Fantasy";
        catNames.push_back(&a);
        Book hobbit(9783608987492, "The Hobbit", Tolkien, catNames, 1937, 310);
        Book hobbit1(9783608987492, "fake", Tolkien, std::vector<const std::string*>(), 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", Tolkien, catNames, 1954, 1178);

        Category fantasy("Fantasy");
        fantasy.addBook(hobbit);

        assert(fantasy.getName() == "Fantasy");
        assert(fantasy.removeBook(LoR) == false);
        assert(fantasy.removeBook(hobbit1) == true);
        assert(fantasy.getBooks().empty());

        testOut << fantasy;
    }
};
std::ofstream UnitTest::testOut("Tests/unit.out");

int main()
{
    UnitTest::runAllTests();
    return 0;
}
