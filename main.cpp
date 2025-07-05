// NO AI USED IN WRITING THIS CODE. Osama Tharwat
#include <bits/stdc++.h>
using namespace std;

class Product {
    string name;
    double price;
    int quantity;
    bool shippable;
    int weight;
    bool perishable;
    int remaining_days;
public:
    Product() {
        name = "";
        price = 0.0;
        quantity = 0;
        shippable = false;
        perishable = false;
    }
    Product(string name, double price, int quantity, bool shippable, bool perishable) {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
        this->shippable = shippable;
        this->perishable = perishable;
    }
    string getName() {
        return name;
    }
    double getPrice() {
        return price;
    }
    ////////////////////
    int getQuantity() {
        return quantity;
    }
    ///////////////////
    bool getShippable() {
        return shippable;
    }
    void setWeight(double weight) {
        if (this->shippable)
            this->weight = weight;
    }
    double getWeight() {
        return weight;
    }
    /////////////////
    bool getPerishable() {
        return perishable;
    }
    void setRemainingDays(int remaining_days) {
        if (perishable) {
            this->remaining_days = remaining_days;
        }
    }
    int getRemainingDays() {
        return remaining_days;
    }
};

class Customer {
    string name;
    double balance;
    public:
    Customer() {
        name = "";
        balance = 0.0;
    }
    Customer(string name, double balance) {
        this->name = name;
        this->balance = balance;
    }
    string getName() {
        return name;
    }
    double getBalance() {
        return balance;
    }
    void debit(double amount) {
        balance -= amount;
    }
};
struct Cart {
    vector<pair<Product, int>> products;

    void addProduct(Product product, int quantity) {
        products.push_back({product, quantity});
    }
    void getProducts() {
        for (int i = 0; i < products.size(); i++) {
            cout << products[i].first.getName() << " " << products[i].second << endl;
        }
    }
    int getTotalPrices() {
        int sum = 0;
        for (int i = 0; i < products.size(); i++) {
            sum += products[i].second * products[i].first.getPrice();
        }
        return sum;
    }
};
pair<double, double> ShippingService(vector<pair<Product, int>> lst) {
    cout << "** Shipment Notice **" << endl;
    double totalWeight = 0;
    for (auto &i : lst) {
        cout << i.second << "x " << i.first.getName() << " " << i.first.getWeight()*i.second << "gm"<< endl;
        totalWeight += i.second*i.first.getWeight();
    }
    cout << "Total Package Weight: " << totalWeight/1000 << "kg" << endl;
    double price = max(10.0, totalWeight/1000*10);
    return make_pair(totalWeight/1000, price);
}
void checkout(Customer &customer, Cart cart) {
    vector<pair<Product,int>> Shipment;
    int shipping = 0;
    for (int i = 0; i < cart.products.size(); i++) {
        if (cart.products[i].second > cart.products[i].first.getQuantity()) {
            cout << "Error, Only " << cart.products[i].first.getQuantity() << ' ' << cart.products[i].first.getName() << " Available." << endl;
            cout << "*********************************************\n";

            return;
        }
        if (cart.products[i].first.getPerishable() && cart.products[i].first.getRemainingDays() <= 0) {
            cout << "Error, Expired " << cart.products[i].first.getName() << endl;
            cout << "*********************************************\n";

            return;
        }
    }
    if (customer.getBalance() < cart.getTotalPrices()){
        cout << "Error, Insufficient Funds\n";
        cout << "*********************************************\n";

        return;
    }

    for (int i = 0; i < cart.products.size(); i++) {
        if (cart.products[i].first.getShippable()) {
            Shipment.push_back(cart.products[i]);
        }
    }
    pair <double,double>p;
    if (Shipment.size() > 0) {
        p = ShippingService(Shipment);
    }

    cout << "** Checkout Reciept **" << endl;
    for (auto &i : cart.products) {
        cout << i.second << "x " << i.first.getName() << " " << i.first.getPrice() * i.second << endl;
    }
    cout << "--------" << endl;
    cout << "Subtotal " << cart.getTotalPrices() << endl;
    if (Shipment.size()) cout << "Shipment " << p.second << endl;
    cout << "Amount " << cart.getTotalPrices() + p.second << endl;
    customer.debit(cart.getTotalPrices()+p.second);
    cout << "*********************************************\n";
}
int main() {
    Product cheese("Cheese", 250.00, 20, true, true);
    cheese.setWeight(1000);
    cheese.setRemainingDays(14);

    Product tv("tv", 8000.00, 5, true, false);
    tv.setWeight(10000);

    Product milk("Milk", 20, 5, true, true);
    milk.setWeight(1000);
    milk.setRemainingDays(0);

    Product scratchCard ("ScratchCard", 10, 100, false, true);
    scratchCard.setRemainingDays(30);

    Customer customer("Ahmed", 20000.00);

    Cart cart1, cart2, cart3, cart4, cart5;

    cart1.addProduct(cheese, 5);
    cart1.addProduct(tv, 1);
    cart1.addProduct(scratchCard, 1);
    checkout(customer, cart1);// test case containing shipment

    cart2.addProduct(scratchCard, 1);
    checkout(customer, cart2);// test case doesn't contain shipment

    cart3.addProduct(cheese, 50); // out of stock
    checkout(customer, cart3);

    cart4.addProduct(milk, 1); //expired
    checkout(customer, cart4);

    cart5.addProduct(tv, 5);
    checkout(customer, cart5);// test case when the balance of the customer is less than the amount

    cout << customer.getBalance(); // to view the balance of the customer is affected after each transaction
}