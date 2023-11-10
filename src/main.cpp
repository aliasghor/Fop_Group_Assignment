#include <iostream>
#include <fstream>

using namespace std;

class User {
    private:
        string name;

    public:
        User(const string& name) {
            this->name = name;
        }

        virtual string get_name() const {
            return this->name;
        }

        friend class PaymentUser;
};

class PaymentUser : public User {
    private:
        string m_bank_name;

    public:
        PaymentUser(const string& name, const string& bank_name) : User(name), m_bank_name(bank_name) {}

        string get_name() const override {
            return this->name + " " + this->m_bank_name;
        }
};

class DataBase {
    private:
        string filename;
        string line;
        ofstream write;
        ifstream read;

    public:
        DataBase(const string& filename) {
            this->filename = filename;
        }

        void write_file(User* data) {
            this->write.open(this->filename,ios::app);

            this->write << data->get_name() << endl;

            this->write.close();

            show_name(data);
        }

        void show_name(User* data) const {
            cout << "Account succesfully created" << endl;
            cout << "Here's your name that you've just created" << endl;
            cout << data->get_name() << endl;
        }

        virtual void read_file() {
            this->read.open(this->filename);
            int index = 1;
            
            this->read.peek();
            if (this->read.eof()) {
                cout << "Seats are still empty please book your seats first!!" << endl;
            }

            else if (!this->read.is_open()) {
                cout << "Seats are still empty please book your seats first!!" << endl;
            }

            else {
                respond();
                while (getline(this->read, this->line)) {
                    cout << "Row: " << index++ << " Name: " << this->line << endl;
                }
            }
            this->read.close();
        }

        virtual void respond() const {
            cout << "Here's your users rows and name's that is already booked the tickets" << endl;
        }

        friend class ViewPayment;
};

class ViewPayment : public DataBase {
    private:
        string m_bank_name;
        User* data;

    public:
        ViewPayment(const string& filename) : DataBase(filename) {}

        void write_file_to_different_file(ViewPayment* data_payment) {
            this->write.open(this->filename,ios::app);

            this->write << data->get_name() << data_payment->m_bank_name << endl;

            this->write.close();

            show_name_and_bank_account(data_payment);
        }

        void show_name_and_bank_account(ViewPayment* show_data) {
            cout << "Name and Bank's account succesfully created" << endl;
            cout << "Here's your name and your bank account name's" << endl;
            cout << data->get_name() << show_data->m_bank_name << endl;
        }

        void read_file() override {
            this->read.open(this->filename);
            int index = 1;

            this->read.peek();

            if (this->read.eof()) {
                cout << "There aren't any names nor bank's name" << endl;
            }

            else if (!this->read.is_open()) {
                cout << "There aren't any names nor bank's name" << endl;
            }

            else {
                respond();
                while (getline(this->read, this->line)) {
                    cout << index++  << ". " << this->line << endl;
                }
            }

            this->read.close();
        }

        void respond() const override {
            cout << "Here's your name and your bank's name" << endl;
        }
};

int main(int argc, char const *argv[])
{
    User* user_input;
    PaymentUser* payment_user;

    DataBase* data_base = new DataBase(".\\bin\\seats.txt");
    ViewPayment* view_payment_data_base = new ViewPayment(".\\bin\\banks.txt");

    int choice;
    string name, bank_name;

    while (true) {
        system("cls");
        first_display:
            cout << "Please select a user" << endl;
            cout << "1.Administrator" << endl;
            cout << "2.Manage" << endl;
            cout << "3.Exit-Program" << endl;
            cout << '\n';

            cout << "Choose your option here: ";
            cin >> choice;
            cin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");

            cout << "Logged in as Administrator" << endl;
            second_display:
                cout << "1.Book Seats" << endl;
                cout << "2.View price list" << endl;
                cout << "3.View details of bookings" << endl;
                cout << "4.Add details of payment" << endl;
                cout << "5.View payment details" << endl;
                cout << "6.Logout" << endl;
                cout << '\n';

                cout << "Choose your option here: ";
                cin >> choice;
                cin.ignore();

            if (choice == 1) {
                system("cls");
                cout << "Great you want to book a seats" << endl;
                cout << "Please enter your name so that we can book your seats" << endl;
                cout << '\n';

                cout << "Enter your name: ";
                getline(cin,name);

                user_input = new User(name);

                data_base->write_file(user_input);
                system("pause");

                delete user_input;

                system("cls");

                goto second_display;
            }

            else if (choice == 2) {
                system("cls");
                cout << "Here's the price of our seats cost" << endl;
                cout << "RM 25" << endl;
                system("pause");
                goto second_display;
            }

            else if (choice == 3) {
                system("cls");
                data_base->read_file();
                system("pause");
                system("cls");
                goto second_display;
            }

            else if (choice == 4) {
                system("cls");
                cout << "Great you want to add a payment method" << endl;
                cout << "Please fill your name and your bank's name" << endl;
                cout << '\n';

                cout << "Please enter your name: ";
                getline(cin,name);

                cout << "Please enter your bank's name: ";
                getline(cin,bank_name);

                payment_user = new PaymentUser(name,bank_name);

                view_payment_data_base->write_file(payment_user);
                system("pause");

                delete payment_user;

                system("cls");
            }

            else if (choice == 5) {
                system("cls");
                view_payment_data_base->read_file();
                system("pause");
                system("cls");
                goto second_display;
            }

            else if (choice == 6) {
                system("cls");
                goto first_display;
            }

            else {
                system("cls");
                cout << "Error invalid option!!! please try again" << endl;
                goto second_display;
            }

            break;

        case 3:
            system("cls");
            cout << "Thanks for trying our project" << endl;
            delete data_base;
            delete view_payment_data_base;
            return 0;
        
        default:
            system("cls");
            cout << "Error invalid option!!!please try again" << endl;
            system("pause");
            break;
        }
    }

    cin.get();
    return 0;
}
