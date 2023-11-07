#include <iostream>
#include <fstream>

using namespace std;

class UserInput {
    private:
        string username;
        string password;

    public:
        UserInput(const string& username, const string& password) {
            this->username = username;
            this->password = password;
        }

        string get_data() const {
            return this->username + " " + this->password + "\n";
        }

        string show_data() const {
            return this->username + "\t\t" + " " + this->password;
        }
};

class Database {
    private:
        string filename;
        ofstream write;
        ifstream read;
        string line;
        string file_username;
        string file_password;

    public:
        Database(const string& filename) {
            this->filename = filename;
        }

        void read_file(UserInput* data) {
            this->write.open(this->filename,ios::app);

            this->write << data->get_data();

            this->write.close();
        }

        void show(UserInput* data) {
            cout << "Account successfully created" << endl;
            cout << "Here's your username and password" << endl;
            cout << '\n';

            cout << "Username\t " << " Password" << endl;
            cout << data->show_data() << endl;
        }

        bool user_exist(const string& username, const string& password) {
            this->read.open(this->filename);

            while (getline(this->read,this->line)) {
                this->file_username = this->line.substr(0,this->line.find(' '));
                this->file_password = this->line.substr(this->line.find(' ') + 1);

                if (this->file_username == username && this->file_password == password) {
                    this->read.close();
                    return true;
                }
            }
            this->read.close();
            return false;
        }
};

int main(int argc, char const *argv[])
{
    UserInput* user;
    Database* data_base = new Database(".\\bin\\data.txt");
    string username, passsword;
    int choice;

    while (true)
    {
        system("cls");
        cout << "Please selecet a user" << endl;
        cout << "1.Administrator" << endl;
        cout << "2.Sign-Up As Administrator" << endl;
        cout << "3.Manager" << endl;
        cout << "4.Exit-Program" << endl;
        cout << '\n';

        cout << "Please enter your choice here: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "Great you want to logged in as administrator" << endl;
            cout << "Please fill this username and password that you've just made earlier" << endl;
            cout << '\n';

            cout << "Please enter your username: ";
            getline(cin,username);

            cout << "Please enter your passowrd: ";
            getline(cin,passsword);

            if (data_base->user_exist(username,passsword)) {
                cout << "Succesfully logged in " << username <<endl;
                system("pause");
            }
            else {
                cout << "Error invalid username or password" << endl;
                system("pause");
            }

            break;

        case 2:
            system("cls");
            cout << "Great you want to sign up as administrator" << endl;
            cout << "Please fill this username and password" << endl;
            cout << '\n';

            cout << "Please enter your username: ";
            getline(cin,username);

            cout << "Please enter your password: ";
            getline(cin,passsword);
            

            user = new UserInput(username,passsword);

            data_base->read_file(user);
            data_base->show(user);
            system("pause");
            delete user;

            break;

        case 4:
            system("cls");
            cout << "Thankyou for trying our simple database project" << endl;
            delete data_base;
            return 0;
        
        default:
            cout << "Error invalid option please try again!!" << endl;
            break;
        } 
    }

    cin.get();
    return 0;
}
