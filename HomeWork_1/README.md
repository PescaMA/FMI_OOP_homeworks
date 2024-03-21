 # Project Name:  **Book_inventary_manager**
 
## Chosen theme and a short description: 
 -> implements a library database in C++. Stores data about books. Allows adding/removing/querying about the books, authors, categories present in a library (which handles the circular dependencies of the objects).


## A list of the features your app currently has respectively: 
 - can get and remember a multitude of information about books, authors, categories which come together in the Library class.
 - the `Book class` contains attributes such as ISBN, title, authors, categories, publish date, and number of pages.
 - the `Author class` remembers the name, pen name of a author and has a vector of pointers to their books.
 - the `Category class` stores the name (allowing storing of a category only once instead of per every book) and pointers to books which fit in this category.
 - the `Library class` makes use of all the previous classes, allowing the finding a specific book/author/category based on their attributes or in relation to the other 2 classes.
 - data is minimally sotred, each Author/Category being stored only once per Library and not once per Book they appear in.