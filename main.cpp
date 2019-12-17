/***
*
* Project name: Shop
        * File: main.cpp
        * Project was created by Chicha Olexandr on 21.11.19
        * Year: 2-nd
        * Specialization: Computer mathematics
        * Taras Shevchenko National University of Kyiv
        * e-mail: sashachicha13gmail.com
        * phone number: +380957519417
*
***/

#include <iostream>
#include <string>
#include "main_repo/types/Customer.cpp"
#include "main_repo/types/Seller.cpp"
#include "main_repo/types/Shop.cpp"
#include "main_repo/types/Product.cpp"
#include "main_repo/types/strParsing.cpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(){
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Ввод с консоли или файла?" << endl << "1 - консоль, 2 - файл" << endl;    //вибираємо спосіб вводу
    cin >> n;
    string name;
    vector<Seller> sellerZ;
    vector<Product> productZ;
    vector<Customer> customerZ;
    Shop* s = new Shop(name, sellerZ, productZ, customerZ);
    if(n == 1)
    {
        string name;
        cout << "Введите название магазина: ";        //вводимо дані
        cin >> name;
        vector<Seller> sellers_;
        vector<Product> products_;
        vector<Customer> customers_;
        cout << "Введите количество товаров" << endl;
        int products_count;
        cin >> products_count;
        for(int i = 0; i < products_count; i++){
            cout <<  endl;
            cout << "Имя товара: ";
            cin >> name;
            cout << endl << "Стоимость: ";
            double price;
            cin >> price;
            cout << endl << "Оптоваю стоимость: ";
            double opt_price;
            cin >> opt_price;
            s->setProduct(Product(name, price, 0.0, opt_price));
        }
        cout << "Введите количество продавцов" << endl;
        int sellers_count;
        cin >> sellers_count;
        int age_;
        int salary_;
        for(int i = 0; i < sellers_count; i++){
            cout << endl << "1: " << endl;
            cout << "Имя продавца: ";
            cin >> name;
            cout << endl << "Возраст: ";
            cin >> age_;
            cout << endl << "Зарплата: ";
            cin >> salary_;
            s->setSeller(Seller(name, age_, salary_));
        }
        cout << "Введите количество покупателей" << endl;
        int customers_count;
        cin >> customers_count;
        for(int i = 0; i < customers_count; i++){
            cout << endl << "1: " << endl;
            cout << "Имя покупателя: ";
            cin >> name;
            cout << endl << "Возраст: ";
            cin >> age_;
            cout << endl << "Деньги: ";
            double money_;
            cin >> money_;
            s->setCustomer(Customer(name, age_, money_));
        }
    }
    else if(n == 2)
    {
        string r;

        ifstream file("/home/sashachicha/C-Project/main_repo/types/name.txt");
        getline(file, r);
        s->setName(get_two_words(r)[1]);

        ifstream file1("/home/sashachicha/C-Project/main_repo/types/products.txt"); // файл из которого читаем (для линукс путь будет так)
        vector<string> product_list;

        while(getline(file1, r)){
            product_list.push_back(r);
        }

        for (int i = 0; i < (product_list.size());i+=4){
            string product_name = get_two_words(product_list[i])[1];
            double product_sale = atof(get_two_words(product_list[i+1])[1].c_str());
            double product_price = atof(get_two_words(product_list[i+2])[1].c_str());
            double product_optPrice = atof(get_two_words(product_list[i+3])[1].c_str());
            s->setProduct(Product(product_name, product_price, product_sale, product_optPrice));
        }

        ifstream file2("/home/sashachicha/C-Project/main_repo/types/sellers.txt"); // файл из которого читаем (для линукс путь будет так)
        vector <string> sellers_list;

        while(getline(file2, r)){
            sellers_list.push_back(r);
        }

        for (int i = 0; (i< sellers_list.size());i+=3) {
            string seller_name = get_two_words(sellers_list[i])[1];
            int seller_age = atoi(get_two_words(sellers_list[i + 1])[1].c_str());
            double seller_salary = atof(get_two_words(sellers_list[i + 2])[1].c_str());
            s->setSeller(Seller(seller_name, seller_age, seller_salary));
        }

        ifstream file3("/home/sashachicha/C-Project/main_repo/types/customers.txt"); // файл из которого читаем (для линукс путь будет так)
        vector <string> customers_list;

        while(getline(file3, r)){
            customers_list.push_back(r);
        }

        for (int i = 0; i< customers_list.size();i+=3) {
            string customer_name = get_two_words(customers_list[i])[1];
            int customer_age = atoi(get_two_words(customers_list[i + 1])[1].c_str());
            double customer_salary = atof(get_two_words(customers_list[i + 2])[1].c_str());
            s->setCustomer(Customer(customer_name, customer_age, customer_salary));
        }

        file.close();
        file1.close();
        file2.close();
        file3.close();
    }
    s->show();

    cout << "Введите количество дней" << endl;
    int time_count;
    cin >> time_count;
    cout << endl;

    for (int i = 0;i<time_count;i++){
        vector<Product> allProducts = s->getProducts();
        Product randomProduct = allProducts[(rand()%allProducts.size())];
        vector<Customer> allCostumers = s->getCustomers();
        Customer *randomCustomer = allCostumers[(rand()%(allCostumers.size()))];
        auto r = s->sellProduct(randomProduct, randomCustomer);
        if (r){
            cout<<"Покупець "<<randomCustomer.getName()<<" купив товар "<<randomProduct.getName()<<endl;
        }
        cout<< "Стан магазину після цього : " <<endl;
        s->show();
    }
}

