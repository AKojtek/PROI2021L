#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Product.h"

class Client {
    // client personal data
    int m_id;
    std::string m_name;
    std::string m_city;
    std::string m_phone;
public:
    Client(int id=0, std::string name="", std::string city="", std::string phone="");
    int getClientID() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getPhone() const;


    friend std::istream& operator>> (std::istream& is, Client& client);
    friend std::ostream& operator<< (std::ostream& os, const Client& client);
    friend std::string prepareForFile (const Client& client);
};

bool operator< (const Client& client, const Client& other);
std::istream& operator>> (std::istream& is, std::vector<Client>& clients);
std::ostream& operator<< (std::ostream& os, const std::vector<Client>& clients);