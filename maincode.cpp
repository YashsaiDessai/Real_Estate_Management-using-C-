#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <iomanip>
using namespace std;
class PropertyManager;
class Property
{
protected:
string address;
double price;
string owner_name;
public:
Property(string addr, double p, string owner) : address(addr), price(p), owner_name(owner) {
if (price < 0) {
throw invalid_argument("Price cannot be negative!");
}
}
// Virtual function for displaying property details
virtual void display(ostream &os) const = 0;
// Operator overload for '<<' to print property details
friend ostream &operator<<(ostream &os, const Property &p) {
p.display(os);
return os;
}
// Operator overload for comparing two properties (==)
bool operator==(const Property &other) const {
return (address == other.address && price == other.price && owner_name ==
other.owner_name);
}
// Operator overload for comparing two properties (!=)
bool operator!=(const Property &other) const {
return !(*this == other);
}
friend class PropertyManager;
virtual ~Property() {
cout << "Property object destroyed." << endl;
}
double getPrice() const {
return price;
}
string getAddress() const {
return address;
}
};
class PropertyManager {
public:
void changeOwner(Property &p, const string &new_owner) {
p.owner_name = new_owner;
cout << "Owner changed to: " << new_owner << endl;
}
void changePrice(Property &p, double new_price) {
if (new_price < 0) {
throw invalid_argument("Price cannot be negative.");
}
p.price = new_price;
cout << "Price changed to: $" << new_price << endl;
}
void changeAddress(Property &p, const string &new_address) {
p.address = new_address;
cout << "Address changed to: " << new_address << endl;
}
void comparePrices(Property &p1, Property &p2) {
if (p1.getPrice() > p2.getPrice()) {
cout << p1.getAddress() << " is more expensive than " << p2.getAddress()
<< endl;
}
else if (p1.getPrice() < p2.getPrice()) {
cout << p1.getAddress() << " is cheaper than " << p2.getAddress() << endl;
}
else {
cout << p1.getAddress() << " and " << p2.getAddress() << " have the same
price." << endl;
}
}
};
// Template function to print details of properties
template <class T>
void printPropertyDetails(const vector<shared_ptr<T>> &properties) {
for (const auto &property : properties) {
cout << *property << endl; // Use overloaded '<<' operator to display property details
}
}
// Residential Property Class
class ResidentialProperty : public Property {
protected:
int bedrooms;
int bathrooms;
public:
ResidentialProperty(string addr, double p, string owner, int beds, int baths)
: Property(addr, p, owner), bedrooms(beds), bathrooms(baths) {
if (bedrooms < 0 || bathrooms < 0) {
throw invalid_argument("Bedrooms and bathrooms cannot be negative.");
}
}
void display(ostream &os) const override {
os << "Residential Property:\n"
<< "Address: " << address << "\n"
<< "Owner: " << owner_name << "\n"
<< "Price: $" << price << "\n"
<< "Bedrooms: " << bedrooms << ", Bathrooms: " << bathrooms << endl;
}
~ResidentialProperty() {
cout << "Residential Property object destroyed." << endl;
}
};
// Commercial Property Class
class CommercialProperty : public Property {
protected:
double office_space;
int parking_spaces;
public:
CommercialProperty(string addr, double p, string owner, double office, int parking)
: Property(addr, p, owner), office_space(office), parking_spaces(parking) {
if (office_space < 0 || parking_spaces < 0) {
throw invalid_argument("Office space and parking spaces cannot be
negative.");
}
}
void display(ostream &os) const override {
os << "Commercial Property:\n"
<< "Address: " << address << "\n"
<< "Owner: " << owner_name << "\n"
<< "Price: $" << price << "\n"
<< "Office Space: " << office_space << " sq ft, Parking: " << parking_spaces
<< " spaces" << endl;
}
~CommercialProperty() {
cout << "Commercial Property object destroyed." << endl;
}
};
// Office class inheriting from CommercialProperty
class Office : public CommercialProperty {
public:
Office(string addr, double p, string owner, double office, int parking)
: CommercialProperty(addr, p, owner, office, parking) {}
void display(ostream &os) const override {
os << "Office Property:\n"
<< "Address: " << address << "\n"
<< "Owner: " << owner_name << "\n"
<< "Price: $" << price << "\n"
<< "Office Space: " << office_space << " sq ft, Parking: " << parking_spaces
<< " spaces" << endl;
}
~Office() {
cout << "Office object destroyed." << endl;
}
};
// Apartment class inheriting from ResidentialProperty
class Apartment : public ResidentialProperty {
protected:
int floor_number;
double maintenance_fee;
public:
Apartment(string addr, double p, string owner, int beds, int baths, int floor, double fee)
: ResidentialProperty(addr, p, owner, beds, baths), floor_number(floor),
maintenance_fee(fee) {
if (floor_number < 0 || maintenance_fee < 0) {
throw invalid_argument("Floor number and maintenance fee cannot be
negative.");
}
}
void display(ostream &os) const override {
os << "Apartment Property:\n"
<< "Address: " << address << "\n"
<< "Owner: " << owner_name << "\n"
<< "Price: $" << price << "\n"
<< "Bedrooms: " << bedrooms << ", Bathrooms: " << bathrooms << "\n"
<< "Floor: " << floor_number << ", Maintenance Fee: $" <<
maintenance_fee << endl;
}
~Apartment() {
cout << "Apartment Property object destroyed." << endl;
}
};
// Villa class inheriting from ResidentialProperty
class Villa : public ResidentialProperty {
protected:
double garden_area;
bool has_pool;
public:
Villa(string addr, double p, string owner, int beds, int baths, double garden, bool pool)
: ResidentialProperty(addr, p, owner, beds, baths), garden_area(garden),
has_pool(pool) {
if (garden_area < 0) {
throw invalid_argument("Garden area cannot be negative.");
}
}
void display(ostream &os) const override {
os << "Villa Property:\n"
<< "Address: " << address << "\n"
<< "Owner: " << owner_name << "\n"
<< "Price: $" << price << "\n"
<< "Bedrooms: " << bedrooms << ", Bathrooms: " << bathrooms << "\n"
<< "Garden Area: " << garden_area << " sq ft, Pool: " << (has_pool ? "Yes" :
"No") << endl;
}
~Villa() {
cout << "Villa Property object destroyed." << endl;
}
};
// Helper function to ask the user for property details
void inputCommonDetails(string &address, double &price, string &owner) {
cout << "Enter property address: ";
cin.ignore(); // Clears the buffer
getline(cin, address);
cout << "Enter property price: ";
cin >> price;
cout << "Enter owner name: ";
cin.ignore(); // Clear the buffer
getline(cin, owner);
}
void savePropertyToFile(const Property &property) {
ofstream file("properties.txt", ios::app);
if (!file) {
throw runtime_error("Error opening file for writing.");
}
file << property; // Using overloaded '<<' operator
file.close();
}
void loadPropertiesFromFile() {
ifstream file("properties.txt");
if (!file) {
throw runtime_error("Error opening file for reading.");
}
string line;
while (getline(file, line)) {
cout << line << endl;
}
file.close();
}
template <typename T>
void sortPropertiesByPrice(vector<shared_ptr<T>> &properties) {
sort(properties.begin(), properties.end(), [](const shared_ptr<T> &a, const shared_ptr<T>
&b) { return a->getPrice() < b->getPrice(); });
}
void printMenu() {
cout << endl;
cout << setfill('-');
cout << setw(35) << "Real Estate Management System" << setfill('-') << setw(23);
cout << "\n1. Add Property\n"
<< "2. Display All Properties\n"
<< "3. Sort Properties by Price\n"
<< "4. Save Properties to File\n"
<< "5. Load Properties from File\n"
<< "6. Update Property Information\n"
<< "7. Compare Property Prices\n"
<< "8. Exit\n";
cout << setfill('-') << setw(62);
cout << "\nEnter your choice: ";
}
int main() {
try {
vector<shared_ptr<Property>> properties;
PropertyManager manager;
int choice;
do {
printMenu();
cin >> choice;
switch (choice) {
case 1: {
int propertyType;
cout << "\nSelect property type:\n1. Residential\n2.
Commercial\nEnter your choice: ";
cin >> propertyType;
string address, owner;
double price;
if (propertyType == 1) {
int resType;
cout << "\nSelect Residential Property type:\n1. Villa\n2.
Apartment\nEnter your choice: ";
cin >> resType;
if (resType == 1) {
int bedrooms, bathrooms;
double garden_area;
bool has_pool;
inputCommonDetails(address, price, owner);
cout << "Enter number of bedrooms: ";
cin >> bedrooms;
cout << "Enter number of bathrooms: ";
cin >> bathrooms;
cout << "Enter garden area (sq ft): ";
cin >> garden_area;
cout << "Has pool (1 for Yes, 0 for No): ";
cin >> has_pool;
properties.push_back(make_shared<Villa>(address,
price, owner, bedrooms, bathrooms, garden_area, has_pool));
cout << "Villa added!\n";
}
else if (resType == 2) {
int bedrooms, bathrooms, floor;
double maintenance_fee;
inputCommonDetails(address, price, owner);
cout << "Enter number of bedrooms: ";
cin >> bedrooms;
cout << "Enter number of bathrooms: ";
cin >> bathrooms;
cout << "Enter floor number: ";
cin >> floor;
cout << "Enter maintenance fee: ";
cin >> maintenance_fee;
properties.push_back(make_shared<Apartment>(address, price, owner, bedrooms,
bathrooms, floor, maintenance_fee));
cout << "Apartment added!\n";
}
}
else if (propertyType == 2) {
double office_space;
int parking_spaces;
inputCommonDetails(address, price, owner);
cout << "Enter office space (sq ft): ";
cin >> office_space;
cout << "Enter number of parking spaces: ";
cin >> parking_spaces;
properties.push_back(make_shared<Office>(address, price,
owner, office_space, parking_spaces));
cout << "Office added!\n";
}
break;
}
case 2: {
printPropertyDetails(properties);
break;
}
case 3: {
sortPropertiesByPrice(properties);
cout << "Properties sorted by price.\n";
break;
}
case 4: {
for (const auto &prop : properties) {
savePropertyToFile(*prop);
}
cout << "Properties saved to file.\n";
break;
}
case 5: {
loadPropertiesFromFile();
break;
}
case 6: {
cout << "Enter property index to update (starting from 0): ";
int idx;
cin >> idx;
if (idx >= 0 && idx < properties.size()) {
manager.changePrice(*properties[idx], 400000);
}
else {
cout << "Invalid property index.\n";
}
break;
}
case 7: {
if (properties.size() >= 2) {
manager.comparePrices(*properties[0], *properties[1]);
}
else {
cout << "Not enough properties to compare.\n";
}
break;
}
case 8: {
cout << "Exiting...\n";
break;
}
default: {
cout << "Invalid choice. Try again.\n";
break;
}
}
} while (choice != 8);
}
catch (const exception &e) {
cout << "Exception caught: " << e.what() << endl;
}
return 0;
}
