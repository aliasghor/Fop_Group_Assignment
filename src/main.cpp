#include <iostream>
#include <fstream>

using namespace std;


class UserSeats {
    protected:
        string m_name;
        int m_row;
        int m_payment;

    public:
        UserSeats(const string& name, const int& row, const int& payment) : m_name(name), m_row(row), m_payment(payment) {}

        friend class DatabaseSeats;
};

class UserPayments : public UserSeats {
    protected:
        string m_banks_name;

    public:
        UserPayments(const string& name, const int& row, const int& payment ,const string& banks_name) : UserSeats(name, row, payment), m_banks_name(banks_name) {}

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
            if (!check_name(user_seats_data->m_name) && !check_seats_row(user_seats_data->m_row)) {
                this->write.open(m_filename,ios::app);

                this->write << user_seats_data->m_name << " " << user_seats_data->m_row << " " << user_seats_data->m_payment << endl;

                this->write.close();

                show_name_and_row(user_seats_data);
            }
        }

        inline void show_name_and_row(UserSeats* user_seats) const {
            cout << "Account successfully created" << endl;
            cout << "Here's your name and your seats row" << endl;
            cout << '\n';

            cout << "Name\t " << "     Seats Row" << "\t\t" << " Has Paid For About" << endl;
            cout << user_seats->m_name << "\t\t" << user_seats->m_row << "\t\t\t" << user_seats->m_payment << " RM" << endl;
        }

        virtual void view_details_bookings() {
            this->read.open(m_filename);
            string temp_name;
            int temp_seats;
            int temp_payment;
            int index = 1;

            cout << "Row " << " Name\t " << "  Seats Row\t " <<  " Has Paid For About\t " << " Taken Seats" <<endl;
            while (this->read >> temp_name >> temp_seats >> temp_payment)
            {
                cout << index++ << ". " << "  " << temp_name << "\t\t" << temp_seats << "\t\t" << temp_payment  << " RM" << "\t\t" << "    #" <<endl;
                if (index == 15) {
                    cerr << "Error you already reached your limits!!" << endl;
                    return;
                }
            }
            if (this->read.eof()) {
                while (index <= 15) {
                    cout << index++ << ". " << " \t\t\t\t\t\t\t    @" << endl;
                } 
            }
            
            this->read.close();
        }

        inline bool check_empty_name() {
            this->read.open(m_filename);

            if (!this->read.is_open()) {
                return false;
            }

            this->read.close();
            return true;
        }

        bool check_name(const string& name) {
            this->read.open(m_filename);
            string temp_name;
            int temp_seats;

            while (this->read >> temp_name >> temp_seats)
            {
                if (temp_name == name) 
                {
                    this->read.close();
                    return true;
                }
            }
            this->read.close();
            return false;
        }

        bool check_seats_row(const int& seats_row) {
            this->read.open(m_filename);
            string temp_name;
            int temp_seats;

            while (this->read >> temp_name >> temp_seats)
            {
                if (temp_seats == seats_row)
                {
                    this->read.close();
                    return true;
                }
            }
            this->read.close();
            return false;
        }

        inline bool check_empty_view_details_bookings() {
            this->read.open(m_filename);

            if (!this->read.is_open()) {
                return false;
            }

            this->read.close();
            return true;
        }
};

class DatabasePayments : public DatabaseSeats {
    public:
        DatabasePayments(const string& filename) : DatabaseSeats(filename) {}

        void write_file_payments(UserPayments* user_payment) {
            this->write.open(m_filename);

            this->write << user_payment->m_name << " " << user_payment->m_row << " " << user_payment->m_banks_name << endl;

            this->write.close();

            show_name_and_seats_row_and_banks_name(user_payment);
        }

        inline void show_name_and_seats_row_and_banks_name(UserPayments* user_payment_data) const {
            cout << "Account successfully created" << endl;
            cout << "Here's your name, seats row and your banks name" << endl;
            cout << '\n';

            cout << "Name\t " << "   Seats Row\t " << "   Banks Name" << endl;
            cout << user_payment_data->m_name << "\t\t" << user_payment_data->m_row << "\t\t" << user_payment_data->m_banks_name << endl;
        }

        bool check_previous_name(const string& name) {
            this->read.open(m_filename);
            string temp_name;
            int temp_age;

            while (this->read >> temp_name >> temp_age)
            {
                if (temp_name == name) {
                    return true;
                }
            }

            this->read.close();
            return false;
        }

        bool is_empty_file_payments() {
            this->read.open(m_filename);

            if (!this->read.is_open()) {
                return true;
            }

            this->read.close();
            return false;
        }


        void view_details_bookings() override {
            this->read.open(m_filename);
            string temp_name;
            int temp_seats;
            int temp_payment;
            string temp_banks_name;
            int index = 1;

            cout << "Row " << " Name\t " << "  Seats Row\t " <<  " Has Paid For About\t " << " Banks Name\t " <<" Taken Seats" <<endl;
            while (this->read >> temp_name >> temp_seats >> temp_payment >> temp_banks_name)
            {
                cout << index++ << ". " << "  " << temp_name << "\t\t" << temp_seats << "\t\t" << temp_payment  << " RM" << temp_banks_name << "\t\t" << "    #" <<endl;
                if (index == 15) {
                    cerr << "Error you already reached your limits!!" << endl;
                    return;
                }
            }
            if (this->read.eof()) {
                while (index <= 15) {
                    cout << index++ << ". " << " \t\t\t\t\t\t\t    @" << endl;
                } 
            }
            
            this->read.close();
        }
};


int main(int argc, char const *argv[])
{
    DatabaseSeats* data_base_seats = new DatabaseSeats(".\\bin\\seats.txt");
    DatabasePayments* data_base_payments = new DatabasePayments(".\\bin\\payments.txt");

    UserPayments* user_payments;
    UserSeats* user_seats;

    string name, banks_name;
    int choice, seats_row, payment;
    
    while (true)
    {
        system("cls");
        first_display:
            system("cls");
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
            cout << "Logged in as: Administrator" << endl;
            second_display:
                system("cls");
                cout << "1. Book seats" << endl;
                cout << "2. View price list"  << endl;
                cout << "3. View details bookings" << endl;
                cout << "4. Add details payment" << endl;
                cout << "5. View payment details" << endl;
                cout << "6. Logout" << endl;
                cout << '\n';

                cout << "Choose your options here: ";
                cin >> choice;
                cin.ignore();

            if (choice == 1) {
                system("cls");
                cout << "Great you want to book a seats" << endl;
                cout << "Please fill your name and your row seats" << endl;
                cout << '\n';

                try_name1:
                    cout << "Please enter your name: ";
                    getline(cin,name);

                if (name.empty()) {
                    system("cls");
                    cerr << "Error you cannot just skipped the name!!!" << endl;
                    cerr << "Please input your name!!" << endl;
                    goto try_name1;
                }

                else if (data_base_seats->check_name(name)) {
                    system("cls");
                    cerr << "Error that name is already in the database!!!" << endl;
                    cerr << "Please pick another name!!" << endl;
                    goto try_name1;
                }

                try_seats1:
                    cout << "Please enter your seats row (1-30) ";
                    cin >> seats_row;

                if (seats_row < 1 || seats_row > 30) {
                    system("cls");
                    cerr << "Error invalid seats row!!!" << endl;
                    cerr << "Please choose a seats row from (1-30)!!" << endl;
                    goto try_seats1;
                }

                else if (data_base_seats->check_seats_row(seats_row)) {
                    system("cls");
                    cerr << "Error that seats row is already in the database!!!" << endl;
                    cerr << "Please pick another seats row!!" << endl;
                    goto try_seats1;
                }

                try_payments1:
                    cout << "Please add your payment(20-10-5) RM: ";
                    cin >> payment;

                if (payment != 20 && payment != 10 && payment != 5) {
                    system("cls");
                    cerr << "Error invalid payment!!" << endl;
                    cerr << "Please try again!!" << endl;

                    goto try_payments1;
                }

                else {
                    user_seats = new UserSeats(name, seats_row, payment);

                    data_base_seats->write_file_seats(user_seats);
                    system("pause");

                    delete user_seats;

                    goto second_display;
                }
            }

            else if (choice == 2) {
                system("cls");
                cout << "Here's all of the price list" << endl;
                cout << "1.20RM" << endl;
                cout << "2.10RM" << endl;
                cout << "3.5RM" << endl;
                system("pause");
                goto second_display;
            }

            else if (choice == 3) {
                system("cls");
                if (!data_base_seats->check_empty_view_details_bookings()) {
                    system("cls");
                    cerr << "Error you haven't booked the seats!!" << endl;
                    cerr << "You must book your seats first if you want to choose this option!!" << endl;
                    system("pause");
                    goto second_display;
                }

                else {
                    system("cls");
                    cout << "Here's the users that already booked" << endl;
                    data_base_seats->view_details_bookings();
                    system("pause");
                    goto second_display;
                }
            }

            else if (choice == 4) {
                system("cls");
                cout << "Great you want to add your payment details" << endl;
                cout << "Please fill your previous seats row, name and your bank's name" << endl;
                cout << '\n';

                cout << "Here's our banks name that are available.please choose one these of the names" << endl;
                cout << "- RHB" << endl;
                cout << "- Maybank" << endl;
                cout << "- CIMB" << endl;
                cout << '\n';

                try_name2:
                    cout << "Please enter your previous name: ";
                    getline(cin,name);

                if (name.empty()) {
                    system("cls");
                    cerr << "Error you cannot just skipped the name!!" << endl;
                    cerr << "Please try again" << endl;
                    goto try_name2;
                }

                else if (!data_base_seats->check_empty_name()) {
                    system("cls");
                    cerr << "Error you haven't registered your names yet!!" << endl;
                    cerr << "You must register your names first!!" << endl;
                    system("pause");
                    goto second_display;
                }
                
                else if (!data_base_seats->check_name(name)) {
                    system("cls");
                    cerr << "Error that name is not in the database!!!" << endl;
                    cerr << "Please input your previous name!!" << endl;
                    goto try_name2;
                }

                try_seats2:
                    cout << "Please enter your previous seats row(1-30): ";
                    cin >> seats_row;
                    cin.ignore();

                if (seats_row < 0 || seats_row > 30) {
                    system("cls");
                    cerr << "Error invalid seats row!!" << endl;
                    cerr << "Please try again" << endl;
                    goto try_seats2;
                }

                else if (!data_base_seats->check_seats_row(seats_row)) {
                    system("cls");
                    cerr << "Error that seats row is not in the database!!!" << endl;
                    cerr << "Please input your previous seats row!!" << endl;
                    goto try_seats2;
                }

                try_payments2:
                    cout << "Please enter your previous payment: ";
                    cin >> payment;

                if (payment == '\n') {
                    system("cls");
                    cerr << "Error you cannot just skipped the question!!" << endl;
                    cerr << "Please try again!!" << endl;

                    goto try_payments2;
                }

                else if (payment != 20 && payment != 10 && payment != 5) {
                    system("cls");
                    cerr << "Error please enter your valid payment!!" << endl;
                    cerr << "Please try again!!" << endl;

                    goto try_payments2;
                }

                try_banks_name:
                    cout << "Please enter your bank's name: "; 
                    getline(cin,banks_name);

                if (banks_name.empty()) {
                    system("cls");
                    cerr << "Error you cannot just skipped the banks name!!" << endl;
                    cerr << "Please try again" << endl;
                    goto try_banks_name;
                }

                else if (banks_name != "RHB" && banks_name != "Maybank" && banks_name != "CIMB") {
                    system("cls");
                    cerr << "Error invalid bank's name!!" << endl;
                    cerr << "Please try again" << endl;
                    goto try_banks_name;
                }

                else {
                    user_payments = new UserPayments(name, seats_row, payment, banks_name);

                    data_base_payments->write_file_payments(user_payments);
                    system("pause");

                    delete user_payments;

                    goto second_display;
                }
            }

            else if (choice == 5) {
                system("cls");
                data_base_payments->is_empty_file_payments();
                cout << "Here's your payment details" << endl;
                data_base_payments->view_details_bookings();
                system("pause");
                goto second_display;
            }

            else if (choice == 6) {
                goto first_display;
            }

            else {
                system("cls");
                cerr << "Invalid option!!!" << endl;
                cerr << "Please try again!!" << endl;
                system("pause");
                goto second_display;
            }
            break;

        case 2:
            system("cls");
            third_display:
                system("cls");
                cout << "Logged in as manager" << endl;
                cout << "1.View overall payments collected" << endl;
                cout << "2.View seats sold available" << endl;
                cout << "3.Logout" << endl;
                cout << '\n';

                cout << "Choose your options here: ";
                cin >> choice;

            if (choice == 2) {
                if (!data_base_seats->check_empty_view_details_bookings()) {
                    system("cls");
                    cerr << "Error you haven't created the name and your seats row!!" << endl;
                    cerr << "Please fill your name and your seats row first!!" << endl;
                    system("pause");
                    goto second_display;
                }

                else {
                    system("cls");
                    data_base_seats->view_details_bookings();
                    system("pause");  
                }
            }

            else if (choice == 3) {
                goto first_display;
            }

            else {
                system("cls");
                cout << "Error invalid option!!!" << endl;
                cout << "Please try again" << endl;
                system("pause");
                goto third_display;
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
            cout << "Error invalid choice!!!" << endl;
            system("pause");
            break;
        }
    }
    

    cin.get();
    return 0;
}
