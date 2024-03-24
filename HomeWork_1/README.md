 # Project Name:  **Library manager**
 
## Chosen theme and a short description: 
 -> implements a library database in C++. 
 - Stores data about books. Allows adding/removing/querying about the books, authors, categories present in a library (which handles the circular dependencies of the objects).
 - Stores customer basic information and loan history. Can calculate overdue time/price for returning books.

## A list of the features your app currently has respectively: 
 - can get and remember a multitude of information about *dates, books, authors, categories, customers, loans* which come together in the Library class.
 - the `Date class` is necessary for remembering and calculating dates for loan durations.
 - the `Book class` contains attributes such as ISBN, title, authors, categories, publish date, and number of pages.
 - the `Author class` remembers the name, pen name of a author and has a vector of pointers to their books.
 - the `Category class` stores the name (allowing storing of a category only once instead of per every book) and pointers to books which fit in this category.
 - the `Customer class` is super simplistic: has the customer name and email.
 - the `Loan class` is used for calculating loan value based on date, remembering dates, price, and a list of the books lent. Can handle returning multiple books even if they have been lent in the object or not. 
 - the `Library class` is the main class. Makes use of all the previous classes, allowing the finding a specific book/author/category based on their attributes or in relation to the other 2 classes. Allows loaning and returning books for customers. Handles relation between customer and its history of loans, and allows loaning of existing books that are in stock.
 - data is minimally sotred, each Author/Category being stored only once per Library and not once per Book they appear in.