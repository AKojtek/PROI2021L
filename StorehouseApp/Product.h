#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>

class Product {
protected:
    int m_id;
    int dimensions[2]{};
    std::string m_name;
    std::time_t start_date;
public:
    std::time_t getDate() const;
    int getID() const;
    std::string getName() const;
    int getWidth() const;
    int getHeight() const;
    void rotate();

    Product(int id = 0, std::string name = "", int x = 0, int y = 0, std::time_t date_s = 0);
    virtual ~Product();

};

std::string castDateString(std::time_t date);
std::time_t castStringDate(std::string date);

class Exclusive : public Product {
    std::time_t end_date;
    std::string verification;
public:
    Exclusive(int id = 0, std::string name = "", int x = 0, int y = 0, std::time_t date_s = 0, std::time_t date_e = 0,
        std::string password = "");
    bool verifyOwnership(const std::string& password) const;
    std::time_t getDateEnd(void) const;
    std::string getPassword(void) const;

    friend std::istream& operator>> (std::istream& is, Exclusive& product);
    friend std::ostream& operator<< (std::ostream& os, const Exclusive& product);
    friend std::string prepareForFile(const Exclusive& product);
};

class Wholesale : public Product {
    std::time_t end_date;
public:
    Wholesale(int id = 0, std::string name = "", int x = 0, int y = 0, std::time_t date_s = 0, std::time_t date_e = 0);
    std::time_t getDateEnd(void) const;

    friend std::istream& operator>> (std::istream& is, Wholesale& product);
    friend std::ostream& operator<< (std::ostream& os, const Wholesale& product);
    friend std::string prepareForFile(const Wholesale& product);
};

class ShortTerm : public Product {
    std::time_t end_date;
public:
    ShortTerm(int id = 0, std::string name = "", int x = 0, int y = 0, std::time_t date_s = 0, std::time_t date_e = 0);
    //std::time_t possibleEndDate(void);
    std::time_t getDateEnd(void) const;

    friend std::istream& operator>> (std::istream& is, ShortTerm& product);
    friend std::ostream& operator<< (std::ostream& os, const ShortTerm& product);
    friend std::string prepareForFile(const ShortTerm& product);
};

class LongTerm : public Product {
public:
    LongTerm(int id = 0, std::string name = "", int x = 0, int y = 0, std::time_t date_s = 0);

    friend std::istream& operator>> (std::istream& is, LongTerm& product);
    friend std::ostream& operator<< (std::ostream& os, const LongTerm& product);
    friend std::string prepareForFile(const LongTerm& product);
};
