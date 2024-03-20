#include "Logic.cpp"

struct UnitTest{
    static std::ofstream testOut;
    static void runAllTests(){
        runAuthorTests();
        runBookTests();
        runCategoryTests();
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
        Book hobbit(9783608987492, "The Hobbit", Tolkien, categories, 1937, 310);
        Book hobbit1(9783608987492, "fake", Tolkien, std::vector<std::string*>(), 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", Tolkien, categories, 1954, 1178);

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
        hobbit.addAuthor(newAuthor);
        assert(hobbit.getAuthors().size() == 2);
        assert(hobbit.getAuthors()[1]->getID() == 2); // Assuming new author's ID is 2

        assert(hobbit.removeAuthor(9) == false);
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
    static void runCategoryTests(){
        Author Tolkien(1, "John Ronald Reuel Tolkien", "J.R.R. Tolkien");
        std::vector<std::string*> catNames;
        catNames.push_back(new std::string("Fantasy"));
        Book hobbit(9783608987492, "The Hobbit", Tolkien, catNames, 1937, 310);
        Book hobbit1(9783608987492, "fake", Tolkien, std::vector<std::string*>(), 2024, 0);
        Book LoR(9780544003415, "The Lord of the Rings", Tolkien, catNames, 1954, 1178);

        Category fantasy("Fantasy");
        fantasy.addBook(hobbit);

        testOut << fantasy;

        assert(fantasy.getName() == "Fantasy");
        assert(fantasy.removeBook(LoR) == false);
        assert(fantasy.removeBook(hobbit1) == true);
        assert(fantasy.getBooks().empty());
    }
};
std::ofstream UnitTest::testOut("Tests/unit.out");

int main()
{
    UnitTest::runAllTests();
    return 0;
}
