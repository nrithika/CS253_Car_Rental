#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class User
{
private:
    string password;

public:
    string name;
    string id;
    enum User_Type
    {
        MANAGER,
        EMPLOYEE,
        CUSTOMER
    } user_type;

    User(string name, string id, string password)
    {
        this->name = name;
        this->id = id;
        this->password = password;
    }
    bool match_password(string password)
    {
        return (this->password == password);
    }
    void update_password(string password)
    {
        this->password = password;
    }
};

class Car
{
public:
    string car_name;
    string model;
    string condition;
    int cost_per_day;
    bool is_available;
    string issued_to;
    time_t issued_on = time(0);
    int number_of_days;

    Car(string car_name, string model, string condition, int cost_per_day, bool is_available, int number_of_days)
    {
        this->car_name = car_name;
        this->model = model;
        this->condition = condition;
        this->cost_per_day = cost_per_day;
        this->is_available = is_available;
        this->number_of_days = number_of_days;
    }
};

class Employee : public User {
public:
    static const int FINE_PER_DAY = 700;
    static const int INITIAL_REWARD_POINTS = 100;
    static const int REWARD_POINTS_NEEDED_PER_CAR = 10;
    static const int FINE_POINTS = 5;

    int pending_fine = 0;
    vector<Car *> car_list;
    int pay;
    int reward_points;

    Employee(string name, string id, string password) : User(name, id, password), reward_points(INITIAL_REWARD_POINTS) {
        this->user_type = EMPLOYEE;
    }

    int calculate_fine(string car_name){
        int fine = 0;
        for (int i = 0; i < car_list.size(); i++){
            if (car_list[i]->car_name == car_name){
                time_t now = time(0);
                int number_of_days = car_list[i]->number_of_days;
                int days_extra = difftime(now, car_list[i]->issued_on) / (60 * 60 * 24);
                days_extra = max(days_extra - number_of_days, 0);
                fine = days_extra * FINE_PER_DAY;
            }
        }
        return fine;
    };

    void clear_fine(){
        pending_fine = 0;
    }

};

class Customer : public User {
public:
    static const int FINE_PER_DAY = 1000;
    static const int INITIAL_REWARD_POINTS = 80;
    static const int REWARD_POINTS_NEEDED_PER_CAR = 10;
    static const int FINE_POINTS = 5;

    int pending_fine = 0;
    vector<Car *> car_list;
    int pay;
    int reward_points;

    Customer(string name, string id, string password) : User(name, id, password), reward_points(INITIAL_REWARD_POINTS) {
        this->user_type = CUSTOMER;
    }

    int calculate_fine(string car_name){
        int fine = 0;
        for (int i = 0; i < car_list.size(); i++){
            if (car_list[i]->car_name == car_name){
                time_t now = time(0);
                int number_of_days = car_list[i]->number_of_days;
                int days_extra = difftime(now, car_list[i]->issued_on) / (60 * 60 * 24);
                days_extra = max(days_extra - number_of_days, 0);
                fine = days_extra * FINE_PER_DAY;
            }
        }
        return fine;
    };

    void clear_fine(){
        pending_fine = 0;
    }

};

class Manager : public User
{
public:
    Manager(string name, string id, string password) : User(name, id, password)
    {
        this->user_type = MANAGER;
    }
};

class User_Database
{
public:
    vector<Customer> customer_list;
    vector<Employee> employee_list;
    vector<Manager> manager_list;
    vector<Car> car_list;

    void add_user(string name, string id, string password, User::User_Type user_type)
    {
        if (user_type == User::EMPLOYEE)
        {
            employee_list.push_back(Employee(name, id, password));
        }
        else if (user_type == User::CUSTOMER)
        {
            customer_list.push_back(Customer(name, id, password));
        }
        else if (user_type == User::MANAGER)
        {
            manager_list.push_back(Manager(name, id, password));
        }
        else
        {
            cout << "Invalid user type" << endl;
        }
    }

    void update_user(User *user, string id)
    {
        if (id != "")
            user->id = id;
    }

    void delete_user(User *user)
    {
        for (int i = 0; i < customer_list.size(); i++)
        {
            if (customer_list[i].id == user->id)
            {
                customer_list.erase(customer_list.begin() + i);
            }
        }
        for (int i = 0; i < employee_list.size(); i++)
        {
            if (employee_list[i].id == user->id)
            {
                employee_list.erase(employee_list.begin() + i);
            }
        }
        for (int i = 0; i < manager_list.size(); i++)
        {   
            if(manager_list.size() == 1){
                cout << "\tManager can be deleted only if there are more than one" << endl;
                return;
            }
            if (manager_list.size() > 1 && manager_list[i].id == user->id)
            {
                manager_list.erase(manager_list.begin() + i);
            }
        }
    }
    
    User *search(string id)
    {
        for (int i = 0; i < customer_list.size(); i++)
        {
            if (customer_list[i].id == id || customer_list[i].name == id)
            {
                return &customer_list[i];
            }
        }
        for (int i = 0; i < employee_list.size(); i++)
        {
            if (employee_list[i].id == id || employee_list[i].name == id)
            {
                return &employee_list[i];
            }
        }
        for (int i = 0; i < manager_list.size(); i++)
        {
            if (manager_list[i].id == id || manager_list[i].name == id)
            {
                return &manager_list[i];
            }
        }
        return nullptr;
    }

    void print_user_list()
    {
        cout << "----------------------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tUser List\n"
             << endl;
        int cnt = 1;
        for (int i = 0; i < customer_list.size(); i++)
        {
            cout << cnt++ << ".      Name: " << customer_list[i].name << endl;
            cout << "\tID: " << customer_list[i].id << endl;
            cout << "\tType: Customer" << endl;
            cout << endl;
        }
        for (int i = 0; i < employee_list.size(); i++)
        {
            cout << cnt++ << ".      Name: " << employee_list[i].name << endl;
            cout << "\tID: " << employee_list[i].id << endl;
            cout << "\tType: Employee" << endl;
            cout << endl;
        }
        for (int i = 0; i < manager_list.size(); i++)
        {
            cout << cnt++<< ".      Name: " << manager_list[i].name << endl;
            cout << "\tID: " << manager_list[i].id << endl;
            cout << "\tType: Manager" << endl;
            cout << endl;
        }
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
};

class Car_Database
{
public:
    vector<Car> car_list;

    void add_car(string car_name, string model, string condition, int cost_per_day){
        car_list.push_back(Car(car_name, model, condition, cost_per_day, true, 0));
    }

    void update_car(Car *car, string car_name, string model, string condition, int cost_per_day){
        if (car_name != "")
            car->car_name = car_name;
        if (model != "")
            car->model = model;
        if (condition != "")
            car->condition = condition;
        if (cost_per_day != 0)
            car->cost_per_day = cost_per_day;
    }

    void delete_car(Car *car){
        for (int i = 0; i < car_list.size(); i++){
            if (car_list[i].car_name == car->car_name){
                extern User_Database user_database;
                User *user = user_database.search(car->issued_to);
                if (user != nullptr)
                    return_car(car->car_name, user);
                car_list.erase(car_list.begin() + i);
                break;
            }
        }
    }

    Car *search(string query){
        for (int i = 0; i < car_list.size(); i++){
            if (car_list[i].car_name == query ||
                car_list[i].condition == query||
                std::to_string(car_list[i].cost_per_day) == query)
            {
                return &car_list[i];
            }
        }
        return nullptr;
    }

    void issue_car(string car_name, User *user, int number_of_days){
        for (int i = 0; i < car_list.size(); i++){
            if (car_list[i].car_name == car_name){
                car_list[i].is_available = false;
                car_list[i].issued_to = user->name;
                car_list[i].issued_on = time(0);
                car_list[i].number_of_days = number_of_days;
                if (user->user_type == User::User_Type::CUSTOMER){
                    Customer *customer = (Customer *)user;
                    customer->car_list.push_back(&car_list[i]);
                }
                else{
                    Employee *employee = (Employee *)user;
                    employee->car_list.push_back(&car_list[i]);
                }
                break;
            }
        }
    }

    bool return_car(string car_name, User *user){
        bool car_returned = false;
        vector<Car *> *car_list;
        int FINE_PER_DAY;
        if (user->user_type == User::User_Type::CUSTOMER){
            Customer *customer = (Customer *)user;
            car_list = &customer->car_list;
            FINE_PER_DAY= Customer::FINE_PER_DAY;
        }
        else{
            Employee *employee = (Employee *)user;
            car_list = &employee->car_list;
            FINE_PER_DAY = Employee::FINE_PER_DAY;
        }
        for (int j = 0; j < car_list->size(); j++){
            if ((*car_list)[j]->car_name == car_name){
                (*car_list)[j]->is_available = true;
                (*car_list)[j]->issued_to = "";
                car_returned = true;
                car_list->erase(car_list->begin() + j);
                break;
            }
        }
        return car_returned;
    }

    void print_car_list(bool man = false){
        extern User_Database user_database;
        cout << "----------------------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tCars List\n"
             << endl;
        for (int i = 0; i < car_list.size(); i++){
                cout << i + 1 << ".      car_name: " << car_list[i].car_name << endl;
                cout << "\tmodel: " << car_list[i].model << endl;
                cout << "\tcondition: " << car_list[i].condition << endl;
                cout << "\tcost_per_day: " << car_list[i].cost_per_day << endl;
                cout << "\tAvailable: " << (car_list[i].is_available ? "Yes" : "No") << endl;
            if (man && !car_list[i].is_available)
            {   
                cout << "\tIssued to: " << car_list[i].issued_to << endl;
                cout << "\tIssued on: " << ctime(&car_list[i].issued_on);
                cout << "\tNumber of days: " << car_list[i].number_of_days << endl;
                time_t due_date;
                due_date = car_list[i].issued_on + car_list[i].number_of_days * 24 * 60 * 60;
                cout << "\tDue date: " << ctime(&due_date) << endl;
            }
            cout << endl;
        }
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }

    void print_issued_cars(User *user, bool cls = true)
    {
        if (cls)
        {
            cout << "----------------------------------------";
            cout << "---------------------\n\n";
            cout << "\t\tIssued cars\n"
                 << endl;
        }
        vector<Car *> car_list;
        if (user->user_type == User::User_Type::CUSTOMER)
        {
            Customer *customer = (Customer *)user;
            car_list = customer->car_list;
        }
        else
        {
            Employee *employee = (Employee *)user;
            car_list = employee->car_list;
        }
        for (int i = 0; i < car_list.size(); i++)
        {
            cout << i + 1 << ".      Car Name: " << car_list[i]->car_name << endl;
            cout << "\tModel: " << car_list[i]->model << endl;
            cout << "\tCondition: " << car_list[i]->condition << endl;
            cout << "\tCost per day: " << car_list[i]->cost_per_day << endl;
            cout << "\tIssued on: " << ctime(&car_list[i]->issued_on);
            cout << "\tNumber of days: " << car_list[i]->number_of_days << endl; 
            time_t due_date = car_list[i]->issued_on + (car_list[i]->number_of_days) * 24 * 60 * 60;
            cout << "\tDue date: " << ctime(&due_date);
            cout << endl;
        }
        if (car_list.size() == 0)
            cout << "\n\tNo cars have been issued." << endl;
        return;
    }

    void print_available_car_list()
    {
        cout << "----------------------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tAvailable cars List\n"
             << endl;
        int cnt = 1;
        for (int i = 0; i < car_list.size(); i++)
        {
            if (car_list[i].is_available)
            {
                cout << cnt << ".      Car Name: " << car_list[i].car_name << endl;
                cout << "\tModel: " << car_list[i].model << endl;
                cout << "\tCondition: " << car_list[i].condition << endl;
                cout << "\tCost per day: " << car_list[i].cost_per_day << '\n'
                     << endl;
                cnt++;
            }
        }
        if (cnt == 1)
        {
            cout << "\tNo cars are available." << endl;
        }
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
};

// Global Variables
User_Database user_database;
Car_Database car_database;

void populate_database()
{
    // add users
    user_database.add_user("John Doe", "johnd", "john123", User::CUSTOMER);
    user_database.add_user("Jane Smith", "janes", "jane456", User::CUSTOMER);
    user_database.add_user("Tom Brown", "tomb", "tom789", User::CUSTOMER);
    user_database.add_user("Mike Johnson", "mikej", "mike101", User::EMPLOYEE);
    user_database.add_user("Emily Davis", "emilyd", "emily202", User::EMPLOYEE);
    user_database.add_user("Sarah Miller", "sarahm", "sarah303", User::MANAGER);

    // add cars
    car_database.add_car("Toyota Camry", "2022", "Excellent", 4000);
    car_database.add_car("Honda Civic", "2020", "Good", 3500);
    car_database.add_car("Ford Mustang", "2018", "Fair", 4500);
    car_database.add_car("BMW X5", "2021", "Excellent", 9000);
    car_database.add_car("Chevrolet Cruze", "2019", "Good", 4000);
    car_database.add_car("Maruti Suzuki Swift", "2021", "Good", 3500);
    car_database.add_car("Hyundai Creta", "2020", "Fair", 5000);

    // issue cars
    User *user = user_database.search("johnd");
    car_database.issue_car("Ford Mustang", user, 7);
    struct tm a = {0, 0, 0, 29, 1, 124}; /* February 29, 2024 */
    car_database.search("Ford Mustang")->issued_on = mktime(&a);
    car_database.issue_car("Maruti Suzuki Swift", user, 5);
    struct tm b = {0, 0, 0, 20, 1, 124}; /* February 10, 2024 */
    car_database.search("Maruti Suzuki Swift")->issued_on = mktime(&b);

    user = user_database.search("mikej");
    car_database.issue_car("BMW X5", user, 3);
    struct tm c = {0, 0, 0, 1, 2, 124}; /* March 1, 2024 */
    car_database.search("BMW X5")->issued_on = mktime(&c);
}

User *login()
{
    string id, password;
    cout << "----------------------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tLOGIN INTO YOUR ACCOUNT!!!\n"
         << endl;
    cout << "\tEnter your id: ";
    cin >> id;
    User *user = user_database.search(id);
    if (!user)
    {
        cout << "\n\tUser not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return nullptr;
    }

    cout << "\tEnter your password: ";
    cin >> password;
    if (!user->match_password(password))
    {
        cout << "\n\tIncorrect password. Please try again.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return nullptr;
    }

    cout << "\n\tLogin successful.\n";
    cout << "\tWelcome " << user->name << "!\n"
         << endl;
    cout << "\tPress enter to continue...";
    getchar();
    return user;
}

User *welcome_screen()
{
    User *user = nullptr;
    while (!user)
    {
        cout << "----------------------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tWELCOME TO CAR RENTAL!!!\n"
             << endl;
        cout << "\t1. Login\n";
        cout << "\t2. Exit\n\n";
        cout << "\tEnter your choice: ";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            user = login();
            break;
        case 2:
            cout << "\033[2J\033[1;1H";
            exit(0);
            break;
        default:
            cout << "\tPlease choose a valid choice!\n\n";
            getchar();
            break;
        }
    }
    return user;
}

string search_car_menu(bool man = false)
{
    cout << "----------------------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tSEARCH CARS!!!\n"
         << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter car name or condition or cost per day: ";
    string search_string;
    getline(cin, search_string);
    Car *car = car_database.search(search_string);
    if (car == nullptr)
    {
        cout << "\n\tNo cars found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return "";
    }
    cout << "\n\tcar found:\n\n";
    cout << "\tCar Name: " << car->car_name << endl;
    cout << "\tModel: " << car->model << endl;
    cout << "\tCondition: " << car->condition << endl;
    cout << "\tCost Per Day: " << car->cost_per_day << endl;
    cout << "\tAvailable: " << (car->is_available ? "Yes" : "No") << endl;
    if (man && !car->is_available)
    {
        cout << "\tIssued to: " << car->issued_to << endl;
        cout << "\tIssued on: " << ctime(&car->issued_on) << endl;
        cout << "\tNumber of days: " << car->number_of_days << endl; 
        time_t due_date;
        due_date = car->issued_on + car->number_of_days * 24 * 60 * 60;
        cout << "\tDue date: " << ctime(&due_date) << endl;
    }
    cout << endl;
    if (car->is_available && !man)
    {
        while (true)
        {
            cout << "\t1. Issue this car\n";
            cout << "\t2. Return to previous menu\n\n";
            cout << "\tEnter your choice: ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                return car->car_name;
            case 2:
                return "";
            default:
                cout << "\tPlease choose a valid choice!\n\n";
                getchar();
                break;
            }
        }
    }
    else
    {
        if (!man)
            cout << "\tThis car is not available.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return "";
    }
    return "";
}

void issue_car_menu(User::User_Type user_type, User *user)
{
    vector<Car> car_list = car_database.car_list;
    while (true)
    {
        cout << "----------------------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tISSUE CAR!!!\n"
             << endl;

        if (user->user_type == User::CUSTOMER)
        {
            Customer *customer = (Customer *)user;
            if (customer->car_list.size() == (customer->reward_points)/(Customer::REWARD_POINTS_NEEDED_PER_CAR))
            {
                cout << "\n\tYou have already issued " << (customer->reward_points)/(Customer::REWARD_POINTS_NEEDED_PER_CAR) << " cars.\n";
                cout << "\tPress enter to continue...";
                getchar();
                return;
            }
        }
        else
        {
            Employee *employee = (Employee *)user;
            if (employee->car_list.size() == (employee->reward_points)/(Employee::REWARD_POINTS_NEEDED_PER_CAR))
            {
                cout << "\n\tYou have already issued " << (employee->reward_points)/(Employee::REWARD_POINTS_NEEDED_PER_CAR) << " cars.\n";
                cout << "\tPress enter to continue...";
                getchar();
                return;
            }
        }

        cout << "\t1. See available cars list\n";
        cout << "\t2. Search for a car\n";
        cout << "\t3. Return to previous menu\n\n";
        cout << "\tEnter your choice: ";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
        {
            car_database.print_available_car_list();
            break;
        }
        case 2:
        {
            string car_name = search_car_menu();
            if (car_name != "")
            {   
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tEnter number of days you wish to rent: ";
                int number_of_days;
                cin >> number_of_days;
                int cost_per_day;
                for(int i = 0; i<car_list.size(); i++){
                    if(car_list[i].car_name == car_name)
                        cost_per_day = car_list[i].cost_per_day;
                }
                if(user_type == User::CUSTOMER)
                {
                    Customer *customer = (Customer *)user;
                    int amount_to_pay = number_of_days * cost_per_day;
                    cout << "\n\tPay amount " << amount_to_pay << endl;
                    int pay;
                    cout << "\tEnter the amount: " ;
                    cin >> pay;
                    if(amount_to_pay == pay)
                    {
                        car_database.issue_car(car_name, user, number_of_days);
                        cout << "\n\tCar issued successfully.\n";
                        cout << "\tPress enter to continue...";
                    }
                    else
                        cout << "\n\tPay complete amount" << endl;
                }
                
                else if(user_type == User::EMPLOYEE)
                {
                    Employee *employee = (Employee *)user;
                    int amount_to_pay = number_of_days * cost_per_day * 0.85;
                    cout << "\n\tPay amount " << amount_to_pay << endl;
                    int pay;
                    cout << "\tEnter the amount: " ;
                    cin >> pay;
                    if(amount_to_pay == pay)
                    {
                        car_database.issue_car(car_name, user, number_of_days);
                        cout << "\n\tCar issued successfully.\n";
                        cout << "\tPress enter to continue...";
                    }
                    else
                        cout << "\n\tPay complete amount" << endl;
                }

                else
                {
                    cout << "\n\tCar not found.\n";
                    cout << "\tPress enter to continue...";
                    getchar();
                }    
            }
            break;
        }
        case 3:
        {
            return;
        }
        default:
        {
            cout << "\tPlease choose a valid choice!\n\n";
            getchar();
            break;
        }
        }
    }
}

void return_car_menu(User::User_Type user_type, User *user)
{
    cout << "----------------------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tRETURN CAR!!!\n"
         << endl;

    bool cars_found = true;
    if (user->user_type == User::CUSTOMER)
    {
        Customer *customer = (Customer *)user;
        if (customer->car_list.size() == 0)
            cars_found = false;
    }
    else
    {
        Employee *employee = (Employee *)user;
        if (employee->car_list.size() == 0)
            cars_found = false;
    }
    if (!cars_found)
    {
        cout << "\n\tYou have no cars to return.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }

    car_database.print_issued_cars(user);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\tEnter the car name to return: ";
    string car_name;
    getline(cin, car_name);
    Car *car = car_database.search(car_name);
    if (car == nullptr)
        car_name = "";
    else
        car_name = car->car_name;
       
    if(user_type == User::CUSTOMER)
    {
        Customer *customer = (Customer *)user;
        int fine_to_pay = customer->calculate_fine(car_name);
        cout << "\n\tPay fine " << fine_to_pay << endl;
        int pay;
        cout << "\tEnter the amount: " ;
        cin >> pay;
        if(fine_to_pay == pay)
        {
            customer->clear_fine();
            car_database.return_car(car_name, user);
            cout << "\n\tCar returned successfully.\n";
            cout << "\tPress enter to continue...";
        }
        else
            cout << "\n\tPay complete fine" << endl;
    }
    else if(user_type == User::EMPLOYEE)
    {
        Employee *employee = (Employee *)user;
        int fine_to_pay = employee->calculate_fine(car_name);
        cout << "\n\tPay fine " << fine_to_pay << endl;
        int pay;
        cout << "\tEnter the amount: " ;
        cin >> pay;
        if(fine_to_pay == pay)
        {
            employee->clear_fine();
            car_database.return_car(car_name, user);
            cout << "\n\tCar returned successfully.\n";
            cout << "\tPress enter to continue...";
        }
        else
            cout << "\n\tPay complete fine" << endl;
    } 
    else
    {
        cout << "\n\tCar not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
    }
}

bool fine_paid = false;

bool pay_fine_menu(User::User_Type user_type, User *user){
    vector<Car> car_list = car_database.car_list;
    int fine = 0;
    if (user_type == User::CUSTOMER)
    {
        Customer *customer = (Customer *)user;
        for(int i=0; i<car_list.size(); i++){
            if(car_list[i].issued_to == user->name){
                fine += customer->calculate_fine(car_list[i].car_name);
            }
        }
    }
    else
    {
        Employee *employee = (Employee *)user;
        for(int i=0; i<car_list.size(); i++){
            if(car_list[i].issued_to == user->name){
                fine += employee->calculate_fine(car_list[i].car_name);
            }   
        }
    }
    cout << "\n\tPending fine: " << fine << '\n'<< endl;
    cout << "\t1. Pay fine\n";
    cout << "\t2. Return to previous menu\n\n";
    cout << "\tEnter your choice: ";
    int a;
    cin >> a;
    switch(a)
    {
        case 1:
        {
            cout << "\n\tPay amount " << fine << endl;
            int pay;
            cout << "\tEnter the amount: " ;
            cin >> pay;
            if(fine == pay)
            {
                if(user_type == User::CUSTOMER)
                {
                    Customer *customer = (Customer *)user;
                    customer->clear_fine();
                }
                else if(user_type == User::EMPLOYEE)
                {
                    Employee *employee = (Employee *)user;
                    employee->clear_fine();
                }
                fine = 0;
                fine_paid = true;
                cout << "\n\tFine cleared.\n";
                cout << "\tPress enter to continue...";
            }
            else
                cout << "\n\tPay complete amount" << endl;
            break;
        }
        case 2:
            return false;
        default:
        {
            cout << "\tPlease choose a valid choice!\n\n";
            // fflush(stdin);
            getchar();
            break;
        }
    }
    getchar();
    return fine_paid;
}

void show_cust_emp_menu(User::User_Type user_type, User *user)
{
    vector<Car> car_list = car_database.car_list;
    while (true)
    {
        cout << "-------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tMAIN MENU\n"<< endl;
        cout << "\t1. View available cars\n";
        cout << "\t2. View issued cars\n";
        cout << "\t3. Issue car\n";
        cout << "\t4. Return car\n";
        cout << "\t5. View pending fine\n";
        cout << "\t6. Logout\n\n";
        cout << "\tEnter your choice: ";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            car_database.print_available_car_list();
            break;
        case 2:
            car_database.print_issued_cars(user);
            cout << "\tPress enter to continue...";
            getchar();
            break;
        case 3:
            issue_car_menu(user_type, user);
            break;
        case 4:
            return_car_menu(user_type, user);
            break;
        case 5:
            if(fine_paid) 
                cout << "\n\tPending fine: 0" <<endl;
            else
                fine_paid = pay_fine_menu(user_type, user);

            break;
        case 6:
            return;
        default:
            cout << "\tPlease choose a valid choice!\n\n";
            getchar();
            break;
        }
    }
}

void add_car_menu()
{
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tADD CAR\n"
         << endl;
    string car_name, model, condition;
    int cost_per_day;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the car name: ";
    getline(cin, car_name);
    cout << "\tEnter the car model: ";
    getline(cin, model);
    cout << "\tEnter the car condition: ";
    getline(cin, condition);
    while(true) {
        cout << "\tEnter the car cost per day: ";
        if(cin >> cost_per_day) {
            break; 
        } else {
            cout << "\tInvalid input. Please enter a valid integer for cost per day." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    car_database.add_car(car_name, model, condition, cost_per_day);
    cout << "\n\tCar added successfully.\n";
    cout << "\tPress enter to continue...";
    getchar();
}

void update_car_menu()
{
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tUPDATE CAR\n" << endl;
    string car_name, model, condition;
    int cost_per_day;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the car name or cost per day or condition to find the car to update: ";
    getline(cin, car_name);
    Car *car = car_database.search(car_name);
    if (car == nullptr)
    {
        cout << "\n\tCar not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
    cout << "\tCar Name: " << car->car_name << endl;
    cout << "\tModel: " << car->model << endl;
    cout << "\tCondition: " << car->condition << endl;
    cout << "\tCost Per Day: " << car->cost_per_day << endl;
    cout << "\n\tEnter the new car details to change. Leave a field empty to retain current information.\n\n";
    cout << "\tEnter the new car car_name: ";
    getline(cin, car_name);
    cout << "\tEnter the new car model: ";
    getline(cin, model);
    cout << "\tEnter the new car condition: ";
    getline(cin, condition);
    while(true) {
        cout << "\tEnter the new cost per day of car(enter the previous cost if you dont wanna change): ";
        if(cin >> cost_per_day) {
            break; 
        } else {
            cout << "\tInvalid input. Please enter a valid integer for cost per day." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    car_database.update_car(car, car_name, model, condition, cost_per_day);
    cout << "\n\tCar updated successfully.\n";
    cout << "\tPress enter to continue...";
    getchar();
}

void delete_car_menu()
{
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tDELETE CAR\n"
         << endl;
    string car_name, model, condition;
    int cost_per_day;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the car name to find the car to remove: ";
    getline(cin, car_name);
    Car *car = car_database.search(car_name);
    if (car == nullptr)
    {
        cout << "\n\tCar not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
    cout << "\tCar Name: " << car->car_name << endl;
    cout << "\tModel: " << car->model << endl;
    cout << "\tCondition: " << car->condition << endl;
    cout << "\tCost per day: " << car->cost_per_day << endl;
    cout << "\n\tAre you sure you want to remove this car? (y/n): ";
    string s;
    cin >> s;
    if (s[0] == 'y' || s[0] == 'Y')
    {
        car_database.delete_car(car);
        cout << "\n\tCar removed successfully.\n";
    }
    else if (s[0] == 'n' || s[0] == 'N')
    {
        cout << "\n\tCar not removed.\n";
    }
    else
    {
        cout << "\n\tInvalid input. Car not removed.\n";
    }
    cout << "\tPress enter to continue...";
    getchar();
}

void modify_car_menu()
{
    while (true)
    {
        cout << "-------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tMODIFY CAR\n" << endl;
        cout << "\t1. Add car\n";
        cout << "\t2. Update car\n";
        cout << "\t3. Delete car\n";
        cout << "\t4. Return to previous menu\n\n";
        cout << "\tEnter your choice: ";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            add_car_menu();
            break;
        case 2:
            update_car_menu();
            break;
        case 3:
            delete_car_menu();
            break;
        case 4:
            return;
        default:
            cout << "\tPlease choose a valid choice!\n\n";
            getchar();
            break;
        }
    }
}

void add_user_menu()
{
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tADD USER\n"
         << endl;
    string user_type, name, id, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the user type (customer/employee/manager): ";
    getline(cin, user_type);
    cout << "\tEnter the user name: ";
    getline(cin, name);
    cout << "\tEnter the user id: ";
    getline(cin, id);
    cout << "\tEnter the password: ";
    getline(cin, password);
    if (user_type == "customer")
        user_database.add_user(name, id, password, User::CUSTOMER);
    else if (user_type == "employee")
        user_database.add_user(name, id, password, User::EMPLOYEE);
    else if (user_type == "manager")
        user_database.add_user(name, id, password, User::MANAGER);
    else
    {
        cout << "\tInvalid user type.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
    cout << "\n\tUser added successfully.\n";
    cout << "\tPress enter to continue...";
    getchar();
}

void update_user_menu()
{
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tUPDATE USER\n"
         << endl;
    string user_type, name, id, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the user id/name to find the user to update: ";
    getline(cin, id);
    User *user = user_database.search(id);
    if (user == nullptr)
    {
        cout << "\n\tUser not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
    cout << "\tUser found.\n";
    cout << "\tUser type: ";
    if (user->user_type == User::CUSTOMER)
        cout << "customer\n";
    else if (user->user_type == User::EMPLOYEE)
        cout << "employee\n";
    else
        cout << "manager\n";
    cout << "\tUser name: " << user->name << endl;
    cout << "\tUser id: " << user->id << endl;
    cout << "\n\tEnter the new user details to change. Leave a field empty to retain current information.\n\n";
    cout << "\tEnter the new user id: ";
    fflush(stdin);
    getline(cin, id);
    user_database.update_user(user, id);
    cout << "\n\tUser updated successfully.\n";
    cout << "\tPress enter to continue...";
    fflush(stdin);
    getchar();
}

void delete_user_menu()
{
    vector<Car> car_list = car_database.car_list;
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tDELETE USER\n" << endl;
    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the user name to find the user to remove (ensure you enter user name and not user id): ";
    getline(cin, id);
    User *user = user_database.search(id);
    if (user == nullptr)
    {
        cout << "\n\tUser not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
    for(int i = 0; i<car_list.size(); i++){
        if(car_list[i].issued_to == id){
            cout << "\nUser has an issued car. You can only delete user after he returns the car." << endl;
            return;
        }
    }
    cout << "\tUser found.\n";
    cout << "\tUser type: " << user->user_type << endl;
    cout << "\tUser name: " << user->name << endl;
    cout << "\tUser id: " << user->id << endl;
    cout << "\n\tAre you sure you want to remove this user? (y/n): ";
    string s;
    cin >> s;
    if (s[0] == 'y' || s[0] == 'Y')
    {
        user_database.delete_user(user);
        if(user->user_type == User::MANAGER)
            cout << "\n\tUser not removed.\n" << endl;
        else
            cout << "\n\tUser removed successfully.\n" << endl;
    }
    else if (s[0] == 'n' || s[0] == 'N')
    {
        cout << "\n\tUser not removed.\n";
    }
    else
    {
        cout << "\n\tInvalid input. User not removed.\n";
    }
    cout << "\tPress enter to continue...";
    getchar();
}

void modify_user_menu()
{
    while (true)
    {
        cout << "-------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tMODIFY USER\n"
             << endl;
        cout << "\t1. Add user\n";
        cout << "\t2. Update user\n";
        cout << "\t3. Delete user\n";
        cout << "\t4. Return to previous menu\n\n";
        cout << "\tEnter your choice: ";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            add_user_menu();
            break;
        case 2:
            update_user_menu();
            break;
        case 3:
            delete_user_menu(); 
            break;
        case 4:
            return;
        default:
            cout << "\tPlease choose a valid choice!\n\n";
            getchar();
            break;
        }
    }
}

void search_user_menu()
{
    cout << "-------------------------";
    cout << "---------------------\n\n";
    cout << "\t\tSEARCH USER\n"
         << endl;
    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\tEnter the user id/name to find the user: ";
    getline(cin, id);
    User *user = user_database.search(id);
    if (user == nullptr)
    {
        cout << "\n\tUser not found.\n";
        cout << "\tPress enter to continue...";
        getchar();
        return;
    }
    cout << "\tUser found.\n\n";
    if (user->user_type == User::CUSTOMER)
        cout << "\tUser type: customer\n";
    else if (user->user_type == User::EMPLOYEE)
        cout << "\tUser type: employee\n";
    else
        cout << "\tUser type: manager\n";
    cout << "\tUser name: " << user->name << endl;
    cout << "\tUser id: " << user->id << endl;
    if (user->user_type != User::MANAGER)
    {
        cout << "\n\tCars issued to this user:\n\n";
        car_database.print_issued_cars(user, false);
    }
    cout << "\n\tPress enter to continue...";
    getchar();
}

void show_manager_menu()
{
    while (true)
    {
        cout << "-------------------------";
        cout << "---------------------\n\n";
        cout << "\t\tMAIN MENU\n"
             << endl;
        cout << "\t1. Add/Update/Delete Cars\n";
        cout << "\t2. Add/Update/Delete Users\n";
        cout << "\t3. View all cars\n";
        cout << "\t4. View all users\n";
        cout << "\t5. Find User that issued the car\n";
        cout << "\t6. Find cars issued to the User\n";
        cout << "\t7. Logout\n\n";
        cout << "\tEnter your choice: ";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            modify_car_menu();
            break;
        case 2:
            modify_user_menu();
            break;
        case 3:
            car_database.print_car_list(true);
            break;
        case 4:
            user_database.print_user_list();
            break;
        case 5:
            search_car_menu(true);
            break;
        case 6:
            search_user_menu();
            break;
        case 7:
            return;
        default:
            cout << "\tPlease choose a valid choice!\n\n";
            getchar();
            break;
        }
    }
}

int main(){
    populate_database();
    while (true)
    {
        User *user = welcome_screen();
        if (user->user_type == User::User_Type::MANAGER)
        {
            show_manager_menu();
        }
        else
        {
            show_cust_emp_menu(user->user_type, user);
        }
    }
    return 0;
}
