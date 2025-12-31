#include <iostream>
#include <string>
using namespace std;

/* -------- Book Node (BST Node) -------- */
class Book {
public:
    int bookID;
    string title;
    string author;
    bool isAvailable;

    Book* left;
    Book* right;

    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        isAvailable = true;
        left = right = nullptr;
    }
};

/* -------- Library Management System -------- */
class Library {
private:
    Book* root;

    /* Insert book into BST */
    Book* insert(Book* node, int id, string title, string author) {
        if (node == nullptr)
            return new Book(id, title, author);

        if (id < node->bookID)
            node->left = insert(node->left, id, title, author);
        else if (id > node->bookID)
            node->right = insert(node->right, id, title, author);
        else
            cout << "Book ID already exists.\n";

        return node;
    }

    /* Search book in BST */
    Book* search(Book* node, int id) {
        if (node == nullptr || node->bookID == id)
            return node;

        if (id < node->bookID)
            return search(node->left, id);

        return search(node->right, id);
    }

    /* In-order traversal (sorted view) */
    void inorder(Book* node) {
        if (!node) return;
        inorder(node->left);
        cout << "ID: " << node->bookID
             << " | Title: " << node->title
             << " | Author: " << node->author
             << " | Available: " << (node->isAvailable ? "Yes" : "No") << endl;
        inorder(node->right);
    }

public:
    Library() {
        root = nullptr;
    }

    /* Add a new book */
    void addBook(int id, string title, string author) {
        root = insert(root, id, title, author);
        cout << "Book added successfully.\n";
    }

    /* Fetch book details */
    void fetchBook(int id) {
        Book* book = search(root, id);
        if (book) {
            cout << "\nBook Found:\n";
            cout << "ID: " << book->bookID
                 << "\nTitle: " << book->title
                 << "\nAuthor: " << book->author
                 << "\nAvailable: " << (book->isAvailable ? "Yes" : "No") << endl;
        } else {
            cout << "Book not found.\n";
        }
    }

    /* Borrow a book */
    void borrowBook(int id) {
        Book* book = search(root, id);
        if (book) {
            if (book->isAvailable) {
                book->isAvailable = false;
                cout << "Book borrowed successfully.\n";
            } else {
                cout << "Book is already borrowed.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }

    /* Return a book */
    void returnBook(int id) {
        Book* book = search(root, id);
        if (book) {
            if (!book->isAvailable) {
                book->isAvailable = true;
                cout << "Book returned successfully.\n";
            } else {
                cout << "Book was not borrowed.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }

    /* Check availability */
    void checkAvailability(int id) {
        Book* book = search(root, id);
        if (book) {
            cout << (book->isAvailable ? "Book is available.\n"
                                       : "Book is currently borrowed.\n");
        } else {
            cout << "Book not found.\n";
        }
    }

    /* Display all books */
    void displayBooks() {
        if (!root) {
            cout << "Library is empty.\n";
            return;
        }
        inorder(root);
    }
};

/* -------- Main Function -------- */
int main() {
    Library lib;
    int choice, id;
    string title, author;

    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Fetch Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Check Availability\n";
        cout << "6. Display All Books\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            lib.addBook(id, title, author);
            break;

        case 2:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.fetchBook(id);
            break;

        case 3:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.borrowBook(id);
            break;

        case 4:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.returnBook(id);
            break;

        case 5:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.checkAvailability(id);
            break;

        case 6:
            lib.displayBooks();
            break;

        case 0:
            cout << "Exiting system.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
