#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
using namespace std;

class book {
    char bno[6]; 
    char bname[30]; 
    char aname[20];
public:
    void createbook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nENTER BOOK NO.: ";
        cin >> bno;
        cout << "\nENTER BOOK NAME: ";
        cin.ignore();
        cin.getline(bname, 30);
        cout << "\nENTER AUTHOR NAME: ";
        cin.getline(aname, 20);
        cout << "\n\n\nBook Created..";
    }

    void display() {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nBook Author Name: " << aname;
    }

    void modifybook() {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name: ";
        cin.ignore();
        cin.getline(bname, 50);
        cout << "\nModify Author's Name: ";
        cin.getline(aname, 20);
    }


    char* return_book_no() {
        return bno;
    }

    void report() {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class student {
    char admno[6]; // admission number
    char name[20];
    char stbno[6]; 
    int token; 
public:
    void new_student() {
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No.: ";
        cin >> admno;
        cout << "Enter The Student Name: ";
        cin.ignore();
        cin.getline(name, 20);
        token = 0;
        stbno[0] = '\0';
        cout << "\n\nStudent Record Created...";
    }

    void showstudent() {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nNo of Book Issued: " << token;
        if (token == 1) {
            cout << "\nBook Number: " << stbno;
        }
    }

    void modifystudent() {
        cout << "\nAdmission No.: " << admno;
        cout << "\nModify Student Name: ";
        cin.ignore();
        cin.getline(name, 20);
    }

    char* retadmno() {
        return admno;
    }

    char* retstbno() {
        return stbno;
    }

    int rettoken() {
        return token;
    }

    void addtoken() {
        token = 1;
    }

    void resettoken() {
        token = 0;
    }

    void getstbno(char t[]) {
        strcpy(stbno, t);
    }

    void report() {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
};

fstream fp, fp1; // file stream objects
book bk; // book class object
student st; // student class object

void writebook() {
    char ch;
    fp.open("book.dat", ios::out | ios::app); // write and append data
    do {
        bk.createbook();
        fp.write(reinterpret_cast<char*>(&bk), sizeof(book)); // size of class
        cout << "\n\nDo you want to add more records...(y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writestudent() {
    char ch;
    fp.open("student.dat", ios::out | ios::app); // write and append data
    do {
        st.new_student();
        fp.write(reinterpret_cast<char*>(&st), sizeof(student)); // size of class
        cout << "\n\nDo you want to add more records...(y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displayspb(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0; // book not found
    fp.open("book.dat", ios::in); // read data
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(book))) {
        if (strcmp(bk.return_book_no(), n) == 0) {
            bk.display();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) { // book not found
        cout << "\n\nBook does not exist";
    }
}

void displaysps(char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0; // student not found
    fp.open("student.dat", ios::in); // read data
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        if (strcmp(st.retadmno(), n) == 0) {
            st.showstudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) { // student not found
        cout << "\n\nStudent does not exist";
    }
}

void modifybook() {
    char n[6];
    int found = 0; // search book of given data
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(book)) && found == 0) {
        if (strcmp(bk.return_book_no(), n) == 0) {
            bk.display();
            cout << "\nEnter the new details of book: ";
            bk.modifybook();
            int pos = -1 * static_cast<int>(sizeof(bk));
            fp.seekp(pos, ios::cur); // back from current position
            fp.write(reinterpret_cast<char*>(&bk), sizeof(book));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\n\nRecord Not Found";
    }
}

void modifystudent() {
    char n[6];
    int found = 0; // search student of given data
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), n) == 0) {
            st.showstudent();
            cout << "\nEnter the new details of student: ";
            st.modifystudent();
            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, ios::cur); // back from current position
            fp.write(reinterpret_cast<char*>(&st), sizeof(student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\n\nRecord Not Found";
    }
}

void deletestudent() {
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        if (strcmp(st.retadmno(), n) != 0) {
            fp2.write(reinterpret_cast<char*>(&st), sizeof(student));
        } else {
            flag = 1; // student found
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat"); // data after deletion moved to temp
    if (flag == 1) {
        cout << "\n\n\tRecord Deleted..";
    } else {
        cout << "\n\nRecord not Found";
    }
}

void deletebook() {
    char n[6]; // book number
    int flag = 0;
    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter the Book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2; // New object
    fp2.open("Temp.dat", ios::out); // temp having data else than that to be deleted
    fp.seekg(0, ios::beg); // beginning of book.dat
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(book))) {
        if (strcmp(bk.return_book_no(), n) != 0) {
            fp2.write(reinterpret_cast<char*>(&bk), sizeof(book));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat"); // delete book
    rename("Temp.dat", "book.dat");
    if (flag == 1) {
        cout << "\n\n\tRecord Deleted..";
    } else {
        cout << "\n\nRecord not Found";
    }
}

void displayalls() {
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go to Entry Menu to create File";
        cout << "\n\n\nProgram is closing ....";
        return;
    }
    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "========================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "========================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student))) {
        st.report();
    }
    fp.close();
}

void displayallb() {
    fp.open("book.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go to Entry Menu to create File";
        cout << "\n\n\nProgram is closing ....";
        return;
    }
    cout << "\n\n\t\tBOOK LIST\n\n";
    cout << "========================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    cout << "========================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(book))) {
        bk.report();
    }
    fp.close();
}

void bookissue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission Number: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), sn) == 0) {
            found = 1;
            if (st.rettoken() == 0) {
                cout << "\n\n\tEnter The Book Number: ";
                cin >> bn;
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(book)) && flag == 0) {
                    if (strcmp(bk.return_book_no(), bn) == 0) {
                        bk.display();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.return_book_no());
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(student));
                        cout << "\n\n\tBook Issued Successfully\n\nPlease Note: Write the current date in backside of your book and submit within 15 days. Fine Rs. 1 for each day after the due date.";
                    }
                }
                if (flag == 0) {
                    cout << "Book no does not exist";
                }
            } else {
                cout << "You have not returned the last book";
            }
        }
    }
    if (found == 0) {
        cout << "Student record does not exist...";
    }
    fp.close();
    fp1.close();
}

void bookdeposit() {
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission Number: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), sn) == 0) {
            found = 1;
            if (st.rettoken() == 1) {
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(book)) && flag == 0) {
                    if (strcmp(bk.return_book_no(), st.retstbno()) == 0) {
                        bk.display();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days: ";
                        cin >> day;
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine has to be deposited Rs. " << fine;
                        }
                        st.resettoken();
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(student));
                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if (flag == 0) {
                    cout << "Book no does not exist";
                }
            } else {
                cout << "No book is issued";
            }
        }
    }
    if (found == 0) {
        cout << "Student record does not exist...";
    }
    fp.close();
    fp1.close();
}

void intro() {
    cout << "\n\n\n\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\n\tMADE BY: ABC";
    cout << "\n\n\tSCHOOL : XYZ";
    cin.get();
}

void adminmenu() {
    int ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1. CREATE STUDENT RECORD";
    cout << "\n\n\t2. DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3. DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\n\t4. MODIFY STUDENT RECORD";
    cout << "\n\n\t5. DELETE STUDENT RECORD";
    cout << "\n\n\t6. CREATE BOOK ";
    cout << "\n\n\t7. DISPLAY ALL BOOKS ";
    cout << "\n\n\t8. DISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t9. MODIFY BOOK ";
    cout << "\n\n\t10. DELETE BOOK ";
    cout << "\n\n\t11. BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11): ";
    cin >> ch2;
    switch (ch2) {
    case 1:
        writestudent();
        break;
    case 2:
        displayalls();
        break;
    case 3: {
        char num[6];
        cout << "\n\n\tPlease Enter Admission No.: ";
        cin >> num;
        displaysps(num);
        break;
    }
    case 4:
        modifystudent();
        break;
    case 5:
        deletestudent();
        break;
    case 6:
        writebook();
        break;
    case 7:
        displayallb();
        break;
    case 8: {
        char num[6];
        cout << "\n\n\tPlease Enter Book No.: ";
        cin >> num;
        displayspb(num);
        break;
    }
    case 9:
        modifybook();
        break;
    case 10:
        deletebook();
        break;
    case 11:
        return;
    default:
        cout << "\a";
    }
    adminmenu();
}

int main() {
    char ch;
    intro();
    do {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. BOOK ISSUE";
        cout << "\n\n\t02. BOOK DEPOSIT";
        cout << "\n\n\t03. ADMIN MENU";
        cout << "\n\n\t04. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-4): ";
        cin.ignore();
        
        cin>>ch;
        switch (ch) {
        case '1':
            bookissue();
            break;
        case '2':
            bookdeposit();
            break;
        case '3':
            adminmenu();
            break;
        case '4':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '4');
    return 0;
}
