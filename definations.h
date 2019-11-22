#include<iostream>
#include <bits/stdc++.h>
#include<string>
#include<vector>

using namespace std;


class User;
class Item;
class Inventory;
class Order;
class DeliverySlot;
class Transaction;
vector<User> user_list;
vector<Order> order_list;
vector<DeliverySlot> slot_list;


class Inventory{
    
    public:
        vector<int> quantity;
        vector<Item> item_list;
        ////////////////////////
        void add(Item _item);
        //search_item(name)
        //display_inventory()
        //is_present(item)
        //filter(category)
};

Inventory inventory;

class Item{
    
    protected:
        string name, category, description;
        int price, vendor_id, discount, item_id;
    public:
        static int total_items;
        Item(string _name, string _category, string _description, int _price, int _vendor_id){
            name = _name;
            category = _category;
            description = _description;
            price = _price;
            vendor_id = _vendor_id;
            discount = 0;
            item_id = ++total_items;
            inventory.add(*this);
        }
        string get_name() {return name;}
        void set_name(string _name) {name = _name;}
        string get_category() {return category;}
        void set_category(string _category) {category = _category;}
        string get_description() {return description;}
        void set_description(string _description) {description = _description;}
        int get_price() {return price;}
        void set_price(int _price) {price = _price;}
        int get_vendor_id() {return vendor_id;}
        int get_discount() {return discount;}
        void set_discount(int _discount) {discount = _discount;}
        int get_item_id() {return item_id;}
        ////////////////////////
        bool is_available() {return inventory.quantity[item_id] != 0;}
};
int Item::total_items = 0;


class Cart{
    
    private:
        vector<int> items;
        vector<int> quantity;
        int total_price;
    public:
        Cart(){
            total_price = 0;
        }
        int get_total_price() { return total_price;}
        vector<int> get_items() {return items;}
        vector<int> get_quantity() {return quantity;}
        ////////////////////////
        void add_to_cart(int _item_id, int _quantity){
            items.push_back(_item_id);
            quantity.push_back(_quantity);
            total_price += inventory.item_list[_item_id].get_price()*_quantity;
        }
        void clear_cart(){
            items.clear();
            quantity.clear();
            total_price = 0;
        }
        void delete_item(int _item_id){
            vector<int>::iterator it = find(items.begin(), items.end(), _item_id);
            if(it != items.end()){
                items.erase(it);
            }
        }
        void change_quantity(int _item_id, int _quantity){
            vector<int>::iterator it = find(items.begin(), items.end(), _item_id);
            *it = _quantity;
        }
        // void checkout(){}
        // void print_cart(){}
};


class User{
    
    protected:
        string name, pass, email_id;
        int user_id;
    public:
        static int total_users;
        User(string _name, string _pass, string _email){
            name = _name;
            pass = _pass;
            email_id = _email;
            user_id = ++total_users;
            user_list.push_back(*this);
        }
        string get_name() {return name;}
        void set_name(string _name) {name = _name;}
        string get_email_id() {return email_id;}
        void set_email_id(string _email) {email_id = _email;}
        bool validate(string _pass) {return (pass == _pass);}
        int get_user_id(){return user_id;}
        void set_password(string _pass){pass = _pass;};
        ////////////////////////
        void print_user(){
            cout<<"ID: "<<user_id<<'\n'<<"NAME: "<<name<<'\n'<<"EMAIL: "<<email_id<<'\n'<<endl;
        }
        bool operator==(User another){
            return this->user_id == another.get_user_id();
        }
};
int User::total_users = 0;


class Customer : public User{
    
    protected:
        string address;
        int phone, type;
        bool is_registered;
        vector<int> orders; // orders-reference-list
        Cart cart;
    public:
        Customer(string _name, string _pass, string _email, string _address, int _phone, int _type):User(_name, _pass, _email)
        {
            address = _address;
            phone = _phone;
            type = _phone;
            is_registered = false; //email-verification
        }
        string get_address() {return address;}
        void set_address(string _address) {address = _address;}
        int get_phone() {return phone;}
        void set_phone(int _phone) {phone = _phone;}
        void set_registered() {is_registered = true;}
};


void Inventory::add(Item _item){
    item_list.push_back(_item);
    quantity.push_back(0);
}

class Order{
    
    private:
        int order_id, customer_id, vendor_id, item_id, quantity, netprice, slot_id;
        string status;
        //payment_reference
    public:
        static int total_orders;
        Order(int _customer_id, int _vendor_id, int _item_id, int _quantity, int _net_price, int _slot_id){
            customer_id = _customer_id;
            vendor_id = _vendor_id;
            item_id = _item_id;
            quantity = _quantity;
            netprice = _net_price;
            slot_id = _slot_id;
            status = "Docking";
            order_id = ++total_orders;
            order_list.push_back(*this);
        }
        int get_order_id() {return order_id;}
        int get_customer_id() {return customer_id;}
        int get_vendor_id() {return vendor_id;}
        int get_item_id() {return item_id;}
        int get_quantity() {return quantity;}
        int get_netprice() {return netprice;}
        int get_slot_id() {return slot_id;}
        string get_status() {return status;}
        ////////////////////////
        void cancel(){status = "cancelation requested";}
        void confirm_cancellation(){status = "cancelled";}
        //void refund()
        //print_order()
};
int Order::total_orders = 0;


class Vendor : public User{
    
    protected:
        int bank_account, phone;
        string address;
        vector<int> items; //item-reference-list
        vector<int> orders; //order-reference-list
    public:
        Vendor(string _name, string _pass, string _email, int _account, int _phone, string _address):User(_name, _pass, _email){
            bank_account = _account;
            phone = _phone;
            address = _address;
        }
        int get_bank_account() {return bank_account;}
        void set_bank_account(int _bank_account) {bank_account = _bank_account;}
        string get_address() {return address;}
        void set_address(string _address) {address = _address;}
        ////////////////////////
        void add_new_item(string _name, string _category, string _description, int _price){
            Item new_item(_name, _category, _description, _price, user_id);
            items.push_back(new_item.get_item_id());
        }
        //update_existing_item(){}
        //view_order_list(){}
        //view_item_list(){}
};


class DeliverySlot{
    
    private:
        int slot_id;
        string time_slot, name;
    public:
        static int total_slots;
        DeliverySlot(string _name, string _time_slot){
            name = _name;
            time_slot = _time_slot;
            slot_id = ++total_slots;
            slot_list.push_back(*this);
        }
        string get_name() {return name;}
        string get_time_slot() {return time_slot;}
        void set_time_slot(string _time_slot) {time_slot = _time_slot;}
};
int DeliverySlot::total_slots = 0;


class Admin : public User{
    
    public:
        void create_vendor(string _name, string _pass, string _email, int _account, int _phone, string _address){
            Vendor new_vendor(_name, _pass, _email, _account, _phone, _address);
        }
        void create_slot(string _name, string _time_slot){
            DeliverySlot new_slot(_name, _time_slot);
        }
};


class Transaction{
    
    protected:
        int transaction_id;
        Cart ordered_cart;
        bool is_confirmed;
    public:
        Transaction(int _order_id, Cart _ordered_cart){
            ordered_cart = _ordered_cart;
        }
        void confirm_payment(){ is_confirmed = true; }
        // void view_receipt(){}
};


class COD: public Transaction{
    
    public:
        void collect_cash(){
            confirm_payment();
        }
};


class OnlineTransaction: public Transaction{
    
    private:
        int transaction_provider_id, bank_id;
    public:
        void call_online_transaction(){}
};