# Real_Estate_Management-using-C++
Overview
This project is a Realestate Management System implemented in C++ that allows users to manage different types of real estate properties through a console interface. It supports multiple property types with detailed attributes and enables functionalities such as adding, displaying, sorting, saving, loading, updating, and comparing properties.

Features
Supports multiple property types:

Residential Properties (Villa, Apartment)

Commercial Properties (Office)

Add new properties with specific attributes for each type:

Villas with garden area and pool info

Apartments with floor number and maintenance fee

Offices with office space and parking spaces

Display all properties with detailed information

Sort properties by price

Save properties to a file (properties.txt)

Load and display properties from a file

Update property details (price, owner, address)

Compare prices of two properties

Robust input validation with exception handling

Technologies Used
C++ language features including:

Object-oriented programming with inheritance and polymorphism

Standard Template Library (STL) for vectors and algorithms

Smart pointers (shared_ptr) for memory management

File I/O for saving and loading properties

Exception handling for invalid input

Navigate to the project directory:
cd realestate-management
Compile the program:
g++ main.cpp -o realestate -std=c++11
Run the executable:
./realestate
Usage
Choose from the menu options to add, display, sort, save, load, update, or compare properties.

Follow prompts to enter specific details for each property type.

Property data is saved in properties.txt for persistence.

Project Structure
/realestate-management
│
├── main.cpp       # Main source code containing all classes and main function
├── properties.txt # Data file to save property details (created after saving)
└── README.md      # This documentation file
Code Highlights
Class Hierarchy:

Property (abstract base)
├── ResidentialProperty
│   ├── Villa
│   └── Apartment
└── CommercialProperty
    └── Office
PropertyManager class for modifying property attributes and comparing prices.

Use of polymorphism and operator overloading to handle and display properties uniformly.

Exception handling ensures invalid inputs (negative prices, negative bedrooms, etc.) are caught.


License
This project is licensed under the MIT License.

Contact
For questions or feedback, reach out:

Email: yashdessai2811mail@gmail.com

GitHub: YashsaiDessai
