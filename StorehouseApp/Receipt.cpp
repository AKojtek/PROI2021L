#include "Receipt.h"
#include <cmath>

void Receipt::setValues(int days, int fine_mult, int LT, int ST, int Ex, int WS) {
    short_term = days * 84000;
    fine_multiplier = fine_mult;
    cost_LT = LT;
    cost_ST = ST;
    cost_Ex = Ex;
    cost_WS = WS;
}

std::istream& operator>> (std::istream& is, Receipt& rec) {
    std::string line;
    std::string temp;
    int days;
    std::time_t value;

    // number of days
    std::getline(is, line);
    std::istringstream iss(line);

    iss >> temp >> days;
    value = days * 86400;
    rec.short_term = value;

    iss.str("");
    iss.clear();

    std::getline(is, line);
    iss.str(line);

    iss >> temp >> rec.fine_multiplier;

    iss.str("");
    iss.clear();

    std::getline(is, line);
    iss.str(line);

    iss >> temp >> rec.cost_LT;

    iss.str("");
    iss.clear();

    std::getline(is, line);
    iss.str(line);

    iss >> temp >> rec.cost_ST;

    iss.str("");
    iss.clear();

    std::getline(is, line);
    iss.str(line);

    iss >> temp >> rec.cost_Ex;

    iss.str("");
    iss.clear();

    std::getline(is, line);
    iss.str(line);

    iss >> temp >> rec.cost_WS;

    return is;
}

std::ostream& operator<< (std::ostream& os, const Receipt& rec) {
    os << "How_Long_is_ShortTerm:\t" << int(rec.short_term) / 86400 << "\n";
    os << "Penalty_multiplier:\t" << rec.fine_multiplier << "\n";
    os << "LongTerm:\t" << rec.cost_LT << "\n";
    os << "Shorterm:\t" << rec.cost_ST << "\n";
    os << "Exclusive:\t" << rec.cost_Ex << "\n";
    os << "Wholesale:\t" << rec.cost_WS << '\n';

    return os;
}

std::string prepareForFile (const Receipt& rec) {
    std::string out = "How_Long_is_ShortTerm:\t" + std::to_string(int(rec.short_term) / 86400) + "\n";
    out += "Penalty_multiplier:\t" + std::to_string(rec.fine_multiplier) + "\n";
    out += "LongTerm:\t" + std::to_string(rec.cost_LT) + "\n";
    out += "Shorterm:\t" + std::to_string(rec.cost_ST) + "\n";
    out += "Exclusive:\t" + std::to_string(rec.cost_Ex) + "\n";
    out += "Wholesale:\t" + std::to_string(rec.cost_WS) + '\n';

    return out;
}

void Receipt::addProduct(ProductInfo* info) {
    rec_products.emplace_back(info);
}

void Receipt::removeProduct(int id) {
    int i = 0;
    while (i < rec_products.size()) {
        if (rec_products[i]->product->getID() == id) {
            rec_products.erase(rec_products.begin() + i);
            break;
        }

        i++;
    }
}

Client* Receipt::getClientPtr() {
    return client;
}

void Receipt::changeClient(Client* client_ptr) {
    rec_products.clear();
    client = client_ptr;
}

std::vector<ProductInfo*>* Receipt::getReceiptList() {
    return &rec_products;
}

int Receipt::getProductValue(ProductInfo* info) {
    int area = info->product->getHeight() * info->product->getWidth();
    int value = 0;
    time_t now = time(NULL);
    time_t s_date = info->product->getDate();
    time_t date_sum = short_term + s_date;
    int days = ceil((now - s_date) / 86400);
    std::string type = info->productType;
    if (type == "Exclusive") {
        auto* ex_ptr = dynamic_cast<Exclusive*>(info->product);
        value = cost_Ex * area;
        if (now > ex_ptr->getDateEnd())
            value *= fine_multiplier;
    }
    else if (type == "LongTerm") {
        auto* ex_ptr = dynamic_cast<LongTerm*>(info->product);
        value = cost_LT * area;
        if (date_sum < now)
            value *= fine_multiplier;
    }
    else if (type == "ShortTerm") {
        auto* ex_ptr = dynamic_cast<ShortTerm*>(info->product);
        value = cost_ST * area;
        if (now > ex_ptr->getDateEnd())
            value *= fine_multiplier;
    }
    else if (type == "Wholesale") {
        auto* ex_ptr = dynamic_cast<Wholesale*>(info->product);
        value = cost_WS * area;
        if (now > ex_ptr->getDateEnd())
            value *= fine_multiplier;
    }
    return value * days;
}

int Receipt::getReceiptValue() {
    int sum = 0;
    for (auto info : rec_products) {
        sum += getProductValue(info);
    }
    return sum;
}

void Receipt::clearProducts() {
    rec_products.clear();
}

bool Receipt::isInReceipt(int prod_id) {
    for (auto info : rec_products) {
        if (info->product->getID() == prod_id)
            return true;
    }
    return false;
}

std::time_t Receipt::getShortTerm() {
    return short_term;
}

std::string Receipt::prepareReceipt(std::string sh_name) {
    std::string bill;
    bill += sh_name + "\t\t\t\t\t\t\t\t" + castDateString(time(NULL)) + "\n\nCLIENT:\t" + client->getName() +
        "\nADDRESS:\t" + client->getCity() + "\nPHONE:\t" + client->getPhone() + "\nINVOICE\n\n";
    for (auto& info : rec_products) {
        bill += info->product->getName() + " " + castDateString(info->product->getDate()) + " " +
            std::to_string(getProductValue(info)) + "\n";
    }
    bill += "\n\nTOTAL:\t" + std::to_string(getReceiptValue());

    return bill;
}
