#include <iostream>
#include <fstream>

using namespace std;

class UserSeats {
    protected:
        string m_name;
        int m_row;

    public:
        UserSeats(const string& name, const int& row) : m_name(name), m_row(row) {}

        friend class DatabaseSeats;
};

class UserPayments : public UserSeats {
    protected:
        int m_banks_name;

    public:
        UserPayments(const string& name, const int& row, const int& banks_name) : UserSeats(name, row), m_banks_name(banks_name) {}

        friend class DatabasePayments;
};

class DatabaseSeats {
    protected:
        string m_filename;
        ofstream write;
        ifstream read;

    public:
        DatabaseSeats(const string& filename) : m_filename(filename) {}

        void write_file_seats(UserSeats* user_seats_data) {
            if (!check_name(user_seats_data->m_name) && !check_row_seats(user_seats_data->m_row)) {
                this->write.open(m_filename,ios::app);

                this->write << user_seats_data->m_name << " " << user_seats_data->m_row << endl;

                this->write.close();
                show_seats_and_name(user_seats_data);
            }
        }

        void show_seats_and_name(UserSeats* user_seats_data) const {
            cout << "Account and Seats Row sucessfully created" << endl;
            cout << "Here's your name and your seats row that you've just made" << endl;
            cout << '\n';

            cout << "Name\t " << " Seats" << endl;
            cout << user_seats_data->m_name << "\t" << "    " <<  user_seats_data->m_row << endl;
        }

        bool check_name(const string& name) {
            this->read.open(m_filename);
            string temp_name;
            int temp_age;

            while (this->read >> temp_name >> temp_age)
            {
                if (temp_name == name) {
                    this->read.close();
                    return true;
                }
            }
            this->read.close();
            return false;
        }

        bool check_row_seats(const int& row) {
            this->read.open(m_filename);
            string temp_name;
            int temp_row;

            while (this->read >> temp_name >> temp_row)
            {
                if (temp_row == row) {
                    this->read.close();
                    return true;
                }
            }
            this->read.close();
            return false;
        }
};

class DatabasePayments : public DatabaseSeats {
    public:
        DatabasePayments(const string& filename) : DatabaseSeats(filename) {}

        void write_file_payments(UserPayments* user_payment) {
            this->write.open(m_filename,ios::app);

            this->write << user_payment->m_name << " " << user_payment->m_row << " " << user_payment->m_banks_name << endl;

            this->write.close();
        }
        
};

int main(int argc, char const *argv[])
{
    DatabaseSeats* data_base_seats = new DatabaseSeats(".\\bin\\seats.txt");
    DatabasePayments* data_base_payments = new DatabasePayments(".\\bin\\payments.txt");

    UserSeats* user_seats;
    UserPayments* user_payments;

    string name, banks_name;
    int choice, seats, banks_number;

    while (true)
    {
        system("cls");
        first_display:
            cout << "Please select a user" << endl;
            cout << "1.Administrator" << endl;
            cout << "2.Manager" << endl;
            cout << "3.Exit-Program" << endl;
            cout << '\n';

            cout << "Choose your options here: ";
            cin >> choice;
            cin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "Logged in as Administrator" << endl;
            second_display:
                system("cls");
                cout << "1.Book Seats" << endl;
                cout << "2.View Price List" << endl;
                cout << "3.View Details Of Payment" << endl;
                cout << "4.Add Details Of Payment" << endl;
                cout << "5.View Payment Details" << endl;
                cout << "6.Logout" << endl;
                cout << '\n';

                cout << "Choose your options here: ";
                cin >> choice;
                cin.ignore();

            if (choice == 1) {
                system("cls");
                cout << "Great you want to book a seats" << endl;
                cout << "Please fill your name and your row seats" << endl;
                cout << '\n';

                name:
                    cout << "Please enter your name: ";
                    getline(cin,name);

                if (data_base_seats->check_name(name)) {
                    system("cls");
                    cout << "Error that name is already in the database!!!" << endl;
                    cout << "Please pick another name" << endl;
                    goto name;
                }

                seats:
                    cout << "Please enter your row seats: ";
                    cin >> seats;

                if (data_base_seats->check_row_seats(seats)) {
                    system("cls");
                    cout << "Error that seats row is already in the database!!!" << endl;
                    cout << "Please pick another seats row" << endl;
                    goto seats;
                }

                user_seats = new UserSeats(name,seats);

                data_base_seats->write_file_seats(user_seats);
                system("pause");

                goto second_display;

                delete user_seats;
            }


            else if (choice == 3) {
                system("cls");
                cout << "Here's the details of the payment that you can use" << endl;
                cout << "1.RHB" << endl;
                cout << "2.Maybank" << endl;
                cout << "3.CIMB" << endl;
                system("pause");
                goto second_display;
            }

            else if (choice == 4) {
                system("cls");
                cout << "Great you want to add details of your payment" << endl;
                cout << "Please fill your previous name and seats row and your bank's name that you want to create" << endl;
                cout << '\n';

                cout << "Available Bank's name" << endl;
                cout << "1.RHB" << endl;
                cout << "2.Maybank" << endl;
                cout << "3.CIMB" << endl;
                cout << '\n';

                cout << "Please enter your previous name: ";
                getline(cin,name);
                cout << "Please enter your previous seats row: ";
                cin >> seats;
                cout << "Please choose the banks number: ";
                cin >> banks_number;

                user_payments = new UserPayments(name, seats, banks_number);

                delete user_payments;
            }

            else if (choice == 6) {
                system("cls");
                goto first_display;
            }

            else {
                system("cls");
                cout << "Error invalid option!!!" << endl;
                cout << "Please try again" << endl;
                system("pause");
                goto second_display;
            }
            break;

        case 3:
            system("cls");
            cout << "Thankyou for trying our project" << endl;
            delete data_base_seats;
            delete data_base_payments;
            return 0;
        
        default:
            system("cls");
            cout << "Error invalid option!!!" << endl;
            break;
        }
    }
    

    cin.get();
    return 0;
}
