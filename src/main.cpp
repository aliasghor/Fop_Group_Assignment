#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class UserInput {
    private:
        string name;

    public:
        UserInput(const string& name) {
            this->name = name;
        }

        string get_name() const {
            return this->name + '\n';
        }
};

class DataBase {
    private:
        string filename;
        string line;
        ofstream write;
        ifstream read;
        vector<UserInput> user;
    public:
        DataBase(const string& filename) {
            this->filename = filename;
        }

        void write_file(UserInput* data) {
            this->write.open(this->filename,ios::app);

            this->write << data->get_name();

            this->write.close();
            show_user_name(data);
        }

        void show_user_name(UserInput* data) {
            cout << "Data successfully stroed" << endl;
            cout << "Here's your name that you've just made" << endl;
            cout << data->get_name();
        }

        void view_details_of_bookings() {
            this->read.open(this->filename);
            int index = 1;

            while (getline(this->read, this->line)) {
                cout << "Row: " << index++ << " Name: " << this->line << endl;
            }

            this->read.close();
        }
};

int main(int argc, char const *argv[])
{
    DataBase* data_base = new DataBase(".\\bin\\data.txt");
    UserInput* user;
    string name;
    int choice;

    while (true) {
        system("cls");
        first_display:
            cout << "Please selecet a user" << endl;
            cout << "1.Administrator" << endl;
            cout << "2.Manager" << endl;
            cout << "3.Exit program" << endl;
            cout << '\n';

            cout << "Please select your choice here: ";
            cin >> choice;
            cin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");
            second_display:
                cout << "Logged in as Administrator" << endl;
                cout << "1.Book seats" << endl;
                cout << "2.View price list" << endl;
                cout << "3.View details of bookings" << endl;
                cout << "4.Add details of payment" << endl;
                cout << "5.View payment details" << endl;
                cout << "6.Logout" << endl;
                cout << '\n';

                cout << "Please select your choice here: ";
                cin >> choice;
                cin.ignore();

            if (choice == 1) {
                system("cls");
                cout << "Great you want to book a seats" << endl;
                cout << "Please fill your name to book the seats" << endl;
                cout << '\n';

                cout << "Please enter your name: ";
                getline(cin,name);

                user = new UserInput(name);
                
                data_base->write_file(user);
                system("pause");

                delete user;
            }

            else if (choice == 2) {
                cout << "Here's the price of the seats" << endl;
                cout << "RM 25" << endl;
            }

            else if (choice == 3) {
                system("cls");
                data_base->view_details_of_bookings();
                system("pause");
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
            cout << "Thankyou for trying our simple project" << endl;
            delete data_base;
            return 0;
        
        default:
            system("cls");
            cout << "Error invalid option!! please try again" << endl;
            system("pause");
            break;
        }
    }

    cin.get();
    return 0;
}
