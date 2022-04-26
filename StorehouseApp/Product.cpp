#include "Product.h"

std::string Product::getName() const {
    return m_name;
}

int Product::getID() const {
    return m_id;
}

int Product::getWidth() const {
    return dimensions[0];
}

int Product::getHeight() const {
    return dimensions[1];
}

void Product::rotate() {
    int temp = dimensions[0];
    dimensions[0] = dimensions[1];
    dimensions[1] = temp;
}

std::time_t Product::getDate() const {
    return start_date;
}

std::time_t ShortTerm::getDateEnd() const {
    return end_date;
}

std::time_t Wholesale::getDateEnd() const {
    return end_date;
}

std::time_t Exclusive::getDateEnd() const {
    return end_date;
}

std::string Exclusive::getPassword() const {
    return verification;
}

Product::Product(int id, std::string name, int x, int y, std::time_t date_s) : m_name(std::move(name)) {
    m_id = id;
    dimensions[0] = x;
    dimensions[1] = y;
    start_date = date_s;
}

Product::~Product() noexcept = default;

Exclusive::Exclusive(int id, std::string name, int x, int y, std::time_t date_s, std::time_t date_e,
    std::string password) : Product(id, std::move(name), x, y, date_s) {
    end_date = date_e;
    verification = std::move(password);
}

Wholesale::Wholesale(int id, std::string name, int x, int y, std::time_t date_s, std::time_t date_e)
    : Product(id, std::move(name), x, y, date_s) {
    end_date = date_e;
}

ShortTerm::ShortTerm(int id, std::string name, int x, int y, std::time_t date_s, std::time_t date_e)
    : Product(id, std::move(name), x, y, date_s) {
    end_date = date_e;
}

LongTerm::LongTerm(int id, std::string name, int x, int y, std::time_t date_s)
    : Product(id, std::move(name), x, y, date_s) {}

std::string castDateString(std::time_t date) {
    std::tm t{};
    gmtime_s(&t, &date);
    char string_date[11];
    std::strftime(string_date, 11, "%d-%m-%Y", &t);
    return string_date;
}

std::time_t castStringDate(std::string date) {
    std::tm time{};
    std::istringstream ss(date);
    ss >> std::get_time(&time, "%d-%m-%Y");
    time.tm_hour = 6;
    return mktime(&time);
}

std::istream& operator>> (std::istream& is, Exclusive& product) {
    is >> product.m_id;
    char curr_char;
    is.get(curr_char);
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
        is.get(curr_char);
    if (curr_char == '[')
    {
        product.m_name = "";
        is.get(curr_char);
        while (curr_char != ']')
        {
            product.m_name += curr_char;
            is.get(curr_char);
        }
    }
    else
    {
        is.unget();
        is >> product.m_name;
    }
    is >> product.dimensions[0] >> product.dimensions[1];
    std::string string_date;
    std::time_t date;
    is >> string_date;
    date = castStringDate(string_date);
    product.start_date = date;
    is >> string_date;
    date = castStringDate(string_date);
    product.end_date = date;
    is >> product.verification;
    return is;
}

std::istream& operator>> (std::istream& is, Wholesale& product) {
    is >> product.m_id;
    char curr_char;
    is.get(curr_char);
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
        is.get(curr_char);
    if (curr_char == '[')
    {
        product.m_name = "";
        is.get(curr_char);
        while (curr_char != ']')
        {
            product.m_name += curr_char;
            is.get(curr_char);
        }
    }
    else
    {
        is.unget();
        is >> product.m_name;
    }
    is >> product.dimensions[0] >> product.dimensions[1];
    std::string string_date;
    std::time_t date;
    is >> string_date;
    date = castStringDate(string_date);
    product.start_date = date;
    is >> string_date;
    date = castStringDate(string_date);
    product.end_date = date;
    return is;
}

std::istream& operator>> (std::istream& is, ShortTerm& product) {
    is >> product.m_id;
    char curr_char;
    is.get(curr_char);
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
        is.get(curr_char);
    if (curr_char == '[')
    {
        product.m_name = "";
        is.get(curr_char);
        while (curr_char != ']')
        {
            product.m_name += curr_char;
            is.get(curr_char);
        }
    }
    else
    {
        is.unget();
        is >> product.m_name;
    }
    is >> product.dimensions[0] >> product.dimensions[1];
    std::string string_date;
    std::time_t date;
    is >> string_date;
    date = castStringDate(string_date);
    product.start_date = date;
    is >> string_date;
    date = castStringDate(string_date);
    product.end_date = date;
    return is;
}

std::istream& operator>> (std::istream& is, LongTerm& product) {
    is >> product.m_id;
    char curr_char;
    is.get(curr_char);
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
        is.get(curr_char);
    if (curr_char == '[')
    {
        product.m_name = "";
        is.get(curr_char);
        while (curr_char != ']')
        {
            product.m_name += curr_char;
            is.get(curr_char);
        }
    }
    else
    {
        is.unget();
        is >> product.m_name;
    }
    is >> product.dimensions[0] >> product.dimensions[1];
    std::string string_date;
    std::time_t date;
    is >> string_date;
    date = castStringDate(string_date);
    product.start_date = date;
    return is;
}

std::ostream& operator<< (std::ostream& os, const Exclusive& product) {
    os << product.getID() << '\t' << product.getName() << '\t' << product.getWidth() <<
        '\t' << product.getHeight() << '\t' << castDateString(product.getDate()) << '\t' <<
        castDateString(product.getDateEnd()) << '\t' << product.getPassword() << '\n';
    return os;
}

std::ostream& operator<< (std::ostream& os, const Wholesale& product) {
    os << product.getID() << '\t' << product.getName() << '\t' << product.getWidth() <<
        '\t' << product.getHeight() << '\t' << castDateString(product.getDate()) << '\t' <<
        castDateString(product.getDateEnd()) << '\n';
    return os;
}

std::ostream& operator<< (std::ostream& os, const ShortTerm& product) {
    os << product.getID() << '\t' << product.getName() << '\t' << product.getWidth() <<
        '\t' << product.getHeight() << '\t' << castDateString(product.getDate()) << '\t' <<
        castDateString(product.getDateEnd()) << '\n';
    return os;
}

std::ostream& operator<< (std::ostream& os, const LongTerm& product) {
    os << product.getID() << '\t' << product.getName() << '\t' << product.getWidth() <<
        '\t' << product.getHeight() << '\t' << castDateString(product.getDate()) << '\n';
    return os;
}

std::string prepareForFile (const Exclusive& product) {
    std::string out = std::to_string(product.getID()) + "\t[" + product.getName() + "]\t" +
        std::to_string(product.getWidth()) + '\t' + std::to_string(product.getHeight()) + '\t' +
        castDateString(product.getDate()) + '\t' + castDateString(product.getDateEnd()) + '\t' +
        product.getPassword() + '\n';
    return out;
}

std::string prepareForFile (const Wholesale& product) {
    std::string out = std::to_string(product.getID()) + "\t[" + product.getName() + "]\t" +
        std::to_string(product.getWidth()) + '\t' + std::to_string(product.getHeight()) + '\t' +
        castDateString(product.getDate()) + '\t' + castDateString(product.getDateEnd()) + '\n';
    return out;
}

std::string prepareForFile (const ShortTerm& product) {
    std::string out = std::to_string(product.getID()) + "\t[" + product.getName() + "]\t" +
        std::to_string(product.getWidth()) + '\t' + std::to_string(product.getHeight()) + '\t' +
        castDateString(product.getDate()) + '\t' + castDateString(product.getDateEnd()) + '\n';
    return out;
}

std::string prepareForFile (const LongTerm& product) {
    std::string out = std::to_string(product.getID()) + "\t[" + product.getName() + "]\t" +
        std::to_string(product.getWidth()) + '\t' + std::to_string(product.getHeight()) + '\t' +
        castDateString(product.getDate()) + '\n';
    return out;
}

bool Exclusive::verifyOwnership(const std::string& password) const {
    return password == getPassword();
}
