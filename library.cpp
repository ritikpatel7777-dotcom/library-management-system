#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// ======================================================
// BOOK CLASS
// ======================================================

class Book {
private:
    int bookId;
    string title;
    string author;
    string category;
    int quantity;

public:

    Book() {
        bookId = 0;
        quantity = 0;
    }

    Book(int id, string t, string a, string c, int q) {
        bookId = id;
        title = t;
        author = a;
        category = c;
        quantity = q;
    }

    int getBookId() const {
        return bookId;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    string getCategory() const {
        return category;
    }

    int getQuantity() const {
        return quantity;
    }

    void increaseQuantity() {
        quantity++;
    }

    void decreaseQuantity() {
        if (quantity > 0) {
            quantity--;
        }
    }

    void updateBook(string t, string a, string c, int q) {
        title = t;
        author = a;
        category = c;
        quantity = q;
    }

    void displayBook() const {
        cout << "\n-----------------------------------";
        cout << "\nBook ID     : " << bookId;
        cout << "\nTitle       : " << title;
        cout << "\nAuthor      : " << author;
        cout << "\nCategory    : " << category;
        cout << "\nQuantity    : " << quantity;
        cout << "\n-----------------------------------\n";
    }
};


// ======================================================
// MEMBER CLASS
// ======================================================

class Member {
private:
    int memberId;
    string name;
    string contact;
    int issuedBooks;

public:

    Member() {
        memberId = 0;
        issuedBooks = 0;
    }

    Member(int id, string n, string c, int issued = 0) {
        memberId = id;
        name = n;
        contact = c;
        issuedBooks = issued;
    }

    int getMemberId() const {
        return memberId;
    }

    string getName() const {
        return name;
    }

    string getContact() const {
        return contact;
    }

    int getIssuedBooks() const {
        return issuedBooks;
    }

    void increaseIssuedBooks() {
        issuedBooks++;
    }

    void decreaseIssuedBooks() {
        if (issuedBooks > 0) {
            issuedBooks--;
        }
    }

    void updateMember(string n, string c) {
        name = n;
        contact = c;
    }

    void displayMember() const {
        cout << "\n-----------------------------------";
        cout << "\nMember ID    : " << memberId;
        cout << "\nName         : " << name;
        cout << "\nContact      : " << contact;
        cout << "\nIssued Books : " << issuedBooks;
        cout << "\n-----------------------------------\n";
    }
};


// ======================================================
// TRANSACTION CLASS
// ======================================================

class Transaction {
private:
    int transactionId;
    int bookId;
    int memberId;
    string issueDate;
    string returnDate;
    string status;
    int fine;

public:

    Transaction() {
        transactionId = 0;
        bookId = 0;
        memberId = 0;
        fine = 0;
        status = "Issued";
    }

    Transaction(int tid, int bid, int mid, string iDate) {
        transactionId = tid;
        bookId = bid;
        memberId = mid;
        issueDate = iDate;
        returnDate = "Not Returned";
        status = "Issued";
        fine = 0;
    }

    int getTransactionId() const {
        return transactionId;
    }

    int getBookId() const {
        return bookId;
    }

    int getMemberId() const {
        return memberId;
    }

    string getStatus() const {
        return status;
    }

    void returnBook(string rDate, int f) {
        returnDate = rDate;
        fine = f;
        status = "Returned";
    }

    void displayTransaction() const {
        cout << "\n-----------------------------------";
        cout << "\nTransaction ID : " << transactionId;
        cout << "\nBook ID        : " << bookId;
        cout << "\nMember ID      : " << memberId;
        cout << "\nIssue Date     : " << issueDate;
        cout << "\nReturn Date    : " << returnDate;
        cout << "\nStatus         : " << status;
        cout << "\nFine           : Rs. " << fine;
        cout << "\n-----------------------------------\n";
    }
};


// ======================================================
// LIBRARY CLASS
// ======================================================

class Library {
private:

    vector<Book> books;
    vector<Member> members;
    vector<Transaction> transactions;

    int nextTransactionId;

public:

    Library() {
        nextTransactionId = 1;

        loadBooks();
        loadMembers();
        loadTransactions();
    }


    // ==================================================
    // BOOK FILE HANDLING
    // ==================================================

    void saveBooks() {

        ofstream file("books.txt");

        for (const auto &book : books) {

            file << book.getBookId() << "|"
                 << book.getTitle() << "|"
                 << book.getAuthor() << "|"
                 << book.getCategory() << "|"
                 << book.getQuantity()
                 << "\n";
        }

        file.close();
    }


    void loadBooks() {

        ifstream file("books.txt");

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {

            stringstream ss(line);

            string id;
            string title;
            string author;
            string category;
            string quantity;

            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, category, '|');
            getline(ss, quantity, '|');

            if (!id.empty()) {

                books.push_back(
                    Book(
                        stoi(id),
                        title,
                        author,
                        category,
                        stoi(quantity)
                    )
                );
            }
        }

        file.close();
    }


    // ==================================================
    // MEMBER FILE HANDLING
    // ==================================================

    void saveMembers() {

        ofstream file("members.txt");

        for (const auto &member : members) {

            file << member.getMemberId() << "|"
                 << member.getName() << "|"
                 << member.getContact() << "|"
                 << member.getIssuedBooks()
                 << "\n";
        }

        file.close();
    }


    void loadMembers() {

        ifstream file("members.txt");

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {

            stringstream ss(line);

            string id;
            string name;
            string contact;
            string issued;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, contact, '|');
            getline(ss, issued, '|');

            if (!id.empty()) {

                members.push_back(
                    Member(
                        stoi(id),
                        name,
                        contact,
                        stoi(issued)
                    )
                );
            }
        }

        file.close();
    }


    // ==================================================
    // TRANSACTION FILE HANDLING
    // ==================================================

    void saveTransactions() {

        ofstream file("transactions.txt");

        for (const auto &t : transactions) {

            file << t.getTransactionId() << "|"
                 << t.getBookId() << "|"
                 << t.getMemberId() << "|"
                 << t.getStatus()
                 << "\n";
        }

        file.close();
    }


    void loadTransactions() {

        ifstream file("transactions.txt");

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {

            stringstream ss(line);

            string tid;
            string bid;
            string mid;
            string status;

            getline(ss, tid, '|');
            getline(ss, bid, '|');
            getline(ss, mid, '|');
            getline(ss, status, '|');

            if (!tid.empty()) {

                nextTransactionId =
                    max(
                        nextTransactionId,
                        stoi(tid) + 1
                    );
            }
        }

        file.close();
    }


    // ==================================================
    // ADD BOOK
    // ==================================================

    void addBook() {

        int id;
        int quantity;

        string title;
        string author;
        string category;

        cout << "\nEnter Book ID: ";
        cin >> id;

        for (const auto &book : books) {

            if (book.getBookId() == id) {

                cout << "\nBook ID already exists!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (quantity < 0) {

            cout << "\nInvalid quantity!\n";
            return;
        }

        books.push_back(
            Book(
                id,
                title,
                author,
                category,
                quantity
            )
        );

        saveBooks();

        cout << "\nBook added successfully!\n";
    }


    // ==================================================
    // VIEW BOOKS
    // ==================================================

    void viewBooks() const {

        if (books.empty()) {

            cout << "\nNo books available.\n";
            return;
        }

        cout << "\n========== ALL BOOKS ==========\n";

        for (const auto &book : books) {

            book.displayBook();
        }
    }


    // ==================================================
    // SEARCH BOOK
    // ==================================================

    void searchBook() const {

        string keyword;

        bool found = false;

        cin.ignore();

        cout << "\nEnter title/author/category: ";
        getline(cin, keyword);

        for (const auto &book : books) {

            if (
                book.getTitle().find(keyword) != string::npos ||
                book.getAuthor().find(keyword) != string::npos ||
                book.getCategory().find(keyword) != string::npos
            ) {

                book.displayBook();

                found = true;
            }
        }

        if (!found) {

            cout << "\nBook not found!\n";
        }
    }


    // ==================================================
    // UPDATE BOOK
    // ==================================================

    void updateBook() {

        int id;

        cout << "\nEnter Book ID to update: ";
        cin >> id;

        for (auto &book : books) {

            if (book.getBookId() == id) {

                string title;
                string author;
                string category;
                int quantity;

                cin.ignore();

                cout << "Enter New Title: ";
                getline(cin, title);

                cout << "Enter New Author: ";
                getline(cin, author);

                cout << "Enter New Category: ";
                getline(cin, category);

                cout << "Enter New Quantity: ";
                cin >> quantity;

                if (quantity < 0) {

                    cout << "\nInvalid quantity!\n";
                    return;
                }

                book.updateBook(
                    title,
                    author,
                    category,
                    quantity
                );

                saveBooks();

                cout << "\nBook updated successfully!\n";

                return;
            }
        }

        cout << "\nBook not found!\n";
    }


    // ==================================================
    // DELETE BOOK
    // ==================================================

    void deleteBook() {

        int id;

        cout << "\nEnter Book ID to delete: ";
        cin >> id;

        for (auto it = books.begin();
             it != books.end();
             ++it) {

            if (it->getBookId() == id) {

                books.erase(it);

                saveBooks();

                cout << "\nBook deleted successfully!\n";

                return;
            }
        }

        cout << "\nBook not found!\n";
    }


    // ==================================================
    // ADD MEMBER
    // ==================================================

    void addMember() {

        int id;

        string name;
        string contact;

        cout << "\nEnter Member ID: ";
        cin >> id;

        for (const auto &member : members) {

            if (member.getMemberId() == id) {

                cout << "\nMember ID already exists!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        cout << "Enter Contact Number: ";
        getline(cin, contact);

        members.push_back(
            Member(
                id,
                name,
                contact
            )
        );

        saveMembers();

        cout << "\nMember registered successfully!\n";
    }


    // ==================================================
    // VIEW MEMBERS
    // ==================================================

    void viewMembers() const {

        if (members.empty()) {

            cout << "\nNo members registered.\n";
            return;
        }

        cout << "\n========== ALL MEMBERS ==========\n";

        for (const auto &member : members) {

            member.displayMember();
        }
    }


    // ==================================================
    // SEARCH MEMBER
    // ==================================================

    void searchMember() const {

        int id;

        cout << "\nEnter Member ID: ";
        cin >> id;

        for (const auto &member : members) {

            if (member.getMemberId() == id) {

                member.displayMember();

                return;
            }
        }

        cout << "\nMember not found!\n";
    }


    // ==================================================
    // UPDATE MEMBER
    // ==================================================

    void updateMember() {

        int id;

        cout << "\nEnter Member ID to update: ";
        cin >> id;

        for (auto &member : members) {

            if (member.getMemberId() == id) {

                string name;
                string contact;

                cin.ignore();

                cout << "Enter New Name: ";
                getline(cin, name);

                cout << "Enter New Contact: ";
                getline(cin, contact);

                member.updateMember(
                    name,
                    contact
                );

                saveMembers();

                cout << "\nMember updated successfully!\n";

                return;
            }
        }

        cout << "\nMember not found!\n";
    }


    // ==================================================
    // DELETE MEMBER
    // ==================================================

    void deleteMember() {

        int id;

        cout << "\nEnter Member ID to delete: ";
        cin >> id;

        for (auto it = members.begin();
             it != members.end();
             ++it) {

            if (it->getMemberId() == id) {

                if (it->getIssuedBooks() > 0) {

                    cout << "\nCannot delete member!\n";
                    cout << "Member has issued books.\n";

                    return;
                }

                members.erase(it);

                saveMembers();

                cout << "\nMember deleted successfully!\n";

                return;
            }
        }

        cout << "\nMember not found!\n";
    }


    // ==================================================
    // ISSUE BOOK
    // ==================================================

    void issueBook() {

        int bookId;
        int memberId;

        string issueDate;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        cin.ignore();

        cout << "Enter Issue Date (DD/MM/YYYY): ";
        getline(cin, issueDate);

        Book *selectedBook = nullptr;
        Member *selectedMember = nullptr;

        // Find book

        for (auto &book : books) {

            if (book.getBookId() == bookId) {

                selectedBook = &book;

                break;
            }
        }

        // Find member

        for (auto &member : members) {

            if (member.getMemberId() == memberId) {

                selectedMember = &member;

                break;
            }
        }

        if (selectedBook == nullptr) {

            cout << "\nBook not found!\n";
            return;
        }

        if (selectedMember == nullptr) {

            cout << "\nMember not found!\n";
            return;
        }

        if (selectedBook->getQuantity() <= 0) {

            cout << "\nBook is currently unavailable!\n";
            return;
        }

        // Maximum 3 books per member

        if (selectedMember->getIssuedBooks() >= 3) {

            cout << "\nMember cannot issue more than 3 books!\n";
            return;
        }

        // Issue book

        selectedBook->decreaseQuantity();

        selectedMember->increaseIssuedBooks();

        transactions.push_back(
            Transaction(
                nextTransactionId++,
                bookId,
                memberId,
                issueDate
            )
        );

        saveBooks();
        saveMembers();
        saveTransactions();

        cout << "\nBook issued successfully!\n";
    }


    // ==================================================
    // RETURN BOOK
    // ==================================================

    void returnBook() {

        int bookId;
        int memberId;

        string returnDate;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        cin.ignore();

        cout << "Enter Return Date (DD/MM/YYYY): ";
        getline(cin, returnDate);

        Book *selectedBook = nullptr;
        Member *selectedMember = nullptr;

        for (auto &book : books) {

            if (book.getBookId() == bookId) {

                selectedBook = &book;

                break;
            }
        }

        for (auto &member : members) {

            if (member.getMemberId() == memberId) {

                selectedMember = &member;

                break;
            }
        }

        if (selectedBook == nullptr) {

            cout << "\nBook not found!\n";
            return;
        }

        if (selectedMember == nullptr) {

            cout << "\nMember not found!\n";
            return;
        }

        // Find active transaction

        for (auto &transaction : transactions) {

            if (
                transaction.getBookId() == bookId &&
                transaction.getMemberId() == memberId &&
                transaction.getStatus() == "Issued"
            ) {

                int lateDays;

                cout << "Enter Late Days: ";
                cin >> lateDays;

                if (lateDays < 0) {

                    cout << "\nInvalid late days!\n";
                    return;
                }

                int fine = calculateFine(lateDays);

                selectedBook->increaseQuantity();

                selectedMember->decreaseIssuedBooks();

                transaction.returnBook(
                    returnDate,
                    fine
                );

                saveBooks();
                saveMembers();
                saveTransactions();

                cout << "\nBook returned successfully!\n";

                cout << "Fine: Rs. "
                     << fine
                     << "\n";

                return;
            }
        }

        cout << "\nNo active issue record found!\n";
    }


    // ==================================================
    // FINE CALCULATION
    // ==================================================

    int calculateFine(int lateDays) const {

        const int finePerDay = 5;

        return lateDays * finePerDay;
    }


    // ==================================================
    // TRANSACTION HISTORY
    // ==================================================

    void viewTransactions() const {

        if (transactions.empty()) {

            cout << "\nNo transaction records available.\n";

            return;
        }

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        for (const auto &transaction : transactions) {

            transaction.displayTransaction();
        }
    }


    // ==================================================
    // ADMIN MENU
    // ==================================================

    void adminMenu() {

        int choice;

        do {

            cout << "\n========================================";
            cout << "\n           ADMIN DASHBOARD";
            cout << "\n========================================";

            cout << "\n\nBOOK MANAGEMENT";
            cout << "\n1. Add Book";
            cout << "\n2. View Books";
            cout << "\n3. Search Book";
            cout << "\n4. Update Book";
            cout << "\n5. Delete Book";

            cout << "\n\nMEMBER MANAGEMENT";
            cout << "\n6. Add Member";
            cout << "\n7. View Members";
            cout << "\n8. Search Member";
            cout << "\n9. Update Member";
            cout << "\n10. Delete Member";

            cout << "\n\nTRANSACTION";
            cout << "\n11. Issue Book";
            cout << "\n12. Return Book";
            cout << "\n13. Transaction History";

            cout << "\n\n14. Logout";

            cout << "\n\nEnter your choice: ";
            cin >> choice;

            switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                viewBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                updateBook();
                break;

            case 5:
                deleteBook();
                break;

            case 6:
                addMember();
                break;

            case 7:
                viewMembers();
                break;

            case 8:
                searchMember();
                break;

            case 9:
                updateMember();
                break;

            case 10:
                deleteMember();
                break;

            case 11:
                issueBook();
                break;

            case 12:
                returnBook();
                break;

            case 13:
                viewTransactions();
                break;

            case 14:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
            }

        } while (choice != 14);
    }


    // ==================================================
    // USER MENU
    // ==================================================

    void userMenu() {

        int choice;

        do {

            cout << "\n========================================";
            cout << "\n             USER DASHBOARD";
            cout << "\n========================================";

            cout << "\n1. View Books";
            cout << "\n2. Search Book";
            cout << "\n3. Issue Book";
            cout << "\n4. Return Book";
            cout << "\n5. View Members";
            cout << "\n6. Transaction History";
            cout << "\n7. Logout";

            cout << "\n\nEnter your choice: ";
            cin >> choice;

            switch (choice) {

            case 1:
                viewBooks();
                break;

            case 2:
                searchBook();
                break;

            case 3:
                issueBook();
                break;

            case 4:
                returnBook();
                break;

            case 5:
                viewMembers();
                break;

            case 6:
                viewTransactions();
                break;

            case 7:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
            }

        } while (choice != 7);
    }
};


// ======================================================
// LOGIN FUNCTION
// ======================================================

bool login(string username, string password, string role) {

    if (role == "admin") {

        if (
            username == "admin" &&
            password == "admin123"
        ) {
            return true;
        }
    }

    if (role == "user") {

        if (
            username == "user" &&
            password == "user123"
        ) {
            return true;
        }
    }

    return false;
} 


// ======================================================
// MAIN FUNCTION
// ======================================================

int main() {

    Library library;

    int choice;

    string username;
    string password;

    cout << "\n============================================";
    cout << "\n       LIBRARY MANAGEMENT SYSTEM";
    cout << "\n============================================";

    do {

        cout << "\n\n1. Admin Login";
        cout << "\n2. User Login";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {

            cout << "\n===== ADMIN LOGIN =====\n";

            cout << "Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            if (
                login(
                    username,
                    password,
                    "admin"
                )
            ) {

                cout << "\nLogin successful!\n";

                library.adminMenu();

            } else {

                cout << "\nInvalid username or password!\n";
            }
        }

        else if (choice == 2) {

            cout << "\n===== USER LOGIN =====\n";

            cout << "Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            if (
                login(
                    username,
                    password,
                    "user"
                )
            ) {

                cout << "\nLogin successful!\n";

                library.userMenu();

            } else {

                cout << "\nInvalid username or password!\n";
            }
        }

        else if (choice == 3) {

            cout << "\nThank you for using";
            cout << " Library Management System!\n";
        }

        else {

            cout << "\nInvalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}