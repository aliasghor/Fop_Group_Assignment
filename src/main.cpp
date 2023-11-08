#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class UserInput {
    private:
        string username;

    public:
        UserInput(const string& username) {
            this->username = username;
        }

        string get_data() const {
            return this->username + '\n';
        }
};

class DataBase {
    private:
        string filename;
        ofstream write;
        ifstream read;
        vector<UserInput> user;

    public:
        DataBase(const string& filename) {
            this->filename = filename;
        }

        void read_data(UserInput* data) {
            this->write.open(this->filename,ios::app);

            this->write << data->get_data();

            this->write.close();

            this->user.push_back(*data);
            loop_user(this->user);
        }

        void loop_user(vector<UserInput>& array_vector) {
            for (int i = 0; i < array_vector.size(); i++) {
                cout << "Row: " << i + 1 << " Name: " << array_vector[i].get_data() << endl;
            }
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
        go_back_again:
            cout << "Please select a user" << endl;
            cout << "1.Book seats" << endl;
            cout << "2.View price list" << endl;
            cout << "3.View details of bookings" << endl;
            cout << "4.Add details of payment" << endl;
            cout << "5.View payment details" << endl;
            cout << "6.Logout" << endl;
            cout << '\n';

        cout << "Choose your options here: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "Logged in as Administrator" << endl;
            cout << "1.Book seats" << endl;
            cout << "2.View price list" << endl;
            cout << "3.View details of bookings" << endl;
            cout << "4.Add details of payment" << endl;
            cout << "5.View payment details" << endl;
            cout << "6.Log-Out" << endl;
            cout << '\n';
            
            cout << "Choose your choice here: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                system("cls");
                cout << "Great you want to book a seats" << endl;
                cout << "Please fill your name to book the seats" << endl;
                cout << '\n';

                cout << "Enter your name here: ";
                getline(cin,name);

                user = new UserInput(name);

                data_base->read_data(user);
                system("pause");

                delete user;
            }

            if (choice == 6) {
                goto go_back_again;
            }
            break;


        case 6:
            cout << "Thankyou for trying our project" << endl;
            delete data_base;
            return 0; 
        
        default:
            break;
        }
    }

    cin.get();
    return 0;
}
