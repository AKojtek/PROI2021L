#include "ProductsContainer.h"

bool cmpProdInfoPtr(ProductInfo* product_info, ProductInfo* other)
{
    if (product_info->client->getClientID() < other->client->getClientID()) {
        return true;
    }
    else if (product_info->client->getClientID() == other->client->getClientID()) {
        int size_product = product_info->product->getWidth() * product_info->product->getHeight();
        int size_other = other->product->getWidth() * other->product->getHeight();
        return size_product > size_other;
    }
    return false;
}

int ProductsContainer::findSmallestMissing(int array[], int start, int end) {
    if (start > end)
        return end + 1;

    if (start != array[start - 1])
        return start;

    int mid = (start + end) / 2;

    if (array[mid - 1] == mid)
        return findSmallestMissing(array, mid + 1, end);

    return findSmallestMissing(array, start, mid);
}

int ProductsContainer::findSmallestMissingCli() {
    int n = (*clients_ptr).size();
    int* tab = new int[n]();
    for (int i = 0; i < n; i++) {
        tab[i] = (*clients_ptr)[i].getClientID();
    }
    std::sort(tab + 0, tab + n);
    int value = findSmallestMissing(tab, 1, n);
    delete[] tab;
    return value;
}

int ProductsContainer::findSmallestMissingProd() {
    int n = products.size();
    int* tab = new int[n]();
    for (int i = 0; i < n; i++) {
        tab[i] = products[i]->product->getID();
    }
    std::sort(tab + 0, tab + n);
    int value = findSmallestMissing(tab, 1, n);
    delete[] tab;
    return value;
}

std::istream& operator>> (std::istream& is, ProductInfo& product_info)
{
    is >> product_info.productType;

    if (product_info.productType == "Exclusive") {
        auto* newProduct = new Exclusive;
        is >> *newProduct;
        product_info.product = newProduct;
    }
    else if (product_info.productType == "Wholesale") {
        auto* newProduct = new Wholesale;
        is >> *newProduct;
        product_info.product = newProduct;
    }
    else if (product_info.productType == "ShortTerm") {
        auto* newProduct = new ShortTerm;
        is >> *newProduct;
        product_info.product = newProduct;
    }
    else if (product_info.productType == "LongTerm") {
        auto* newProduct = new LongTerm;
        is >> *newProduct;
        product_info.product = newProduct;
    }

    return is;
}

std::ostream& operator<< (std::ostream& os, const ProductInfo& product_info)
{
    os << product_info.productType << '\t';
    if (product_info.productType == "Exclusive") {
        auto* product_ptr = static_cast<Exclusive*>(product_info.product);
        os << *(product_ptr);
    }
    else if (product_info.productType == "Wholesale") {
        auto* product_ptr = static_cast<Wholesale*>(product_info.product);
        os << *(product_ptr);
    }
    else if (product_info.productType == "ShortTerm") {
        auto* product_ptr = static_cast<ShortTerm*>(product_info.product);
        os << *(product_ptr);
    }
    else if (product_info.productType == "LongTerm") {
        auto* product_ptr = static_cast<LongTerm*>(product_info.product);
        os << *(product_ptr);
    }

    return os;
}

std::string prepareForFile(const ProductInfo& product_info)
{
    std::string out = product_info.productType + '\t';
    if (product_info.productType == "Exclusive") {
        auto* product_ptr = static_cast<Exclusive*>(product_info.product);
        out += prepareForFile(*(product_ptr));
    }
    else if (product_info.productType == "Wholesale") {
        auto* product_ptr = static_cast<Wholesale*>(product_info.product);
        out += prepareForFile(*(product_ptr));
    }
    else if (product_info.productType == "ShortTerm") {
        auto* product_ptr = static_cast<ShortTerm*>(product_info.product);
        out += prepareForFile(*(product_ptr));
    }
    else if (product_info.productType == "LongTerm") {
        auto* product_ptr = static_cast<LongTerm*>(product_info.product);
        out += prepareForFile(*(product_ptr));
    }

    return out;
}

ProductInfo::~ProductInfo() {
    delete product;
}

void ProductsContainer::sortContainer() {
    std::sort(products.begin(), products.end(), cmpProdInfoPtr);
}

int ProductsContainer::findClientPart(int clientID) {
    for (int i = 0; i < products.size(); i++) {
        if (products[i]->client->getClientID() == clientID)
            return i;
    }
    return -1;
}

int ProductsContainer::findClientPartLength(int index) {
    int id = products[index]->client->getClientID();
    int counter = 0;
    while (products[index]->client->getClientID() == id) {
        ++index;
        ++counter;
        if (index >= products.size())
            return counter;
    }
    return counter;
}

Client* ProductsContainer::findClientPointer(int id) const {
    for (int i = 0; i < clients_ptr->size(); i++)
    {
        if ((*clients_ptr)[i].getClientID() == id)
            return &((*clients_ptr)[i]);
    }
    return nullptr;
}

std::ostream& operator<< (std::ostream& os, const ProductsContainer& products_container) {
    for (auto& product : products_container.products) {
        os << product->client->getClientID() << '\t' <<
            product->leftX << '\t' << product->leftY << '\t' <<
            product->rightX << '\t' << product->rightY << '\t' << *(product);
    }
    return os;
}

std::string prepareForFile(const ProductsContainer& products_container) {
    std::string out = "";
    for (auto& product : products_container.products) {
        out += std::to_string(product->client->getClientID()) + '\t' +
            std::to_string(product->leftX) + '\t' + std::to_string(product->leftY) + '\t' +
                std::to_string(product->rightX) + '\t' + std::to_string(product->rightY) + '\t';
        out += prepareForFile(*(product));
    }
    return out;
}

std::istream& operator>> (std::istream& is, ProductsContainer& products_container) {
    std::string line;
    int client_id;

    while (is.peek() != EOF) {
        std::getline(is, line);
        if (line.empty())
            return is;
        std::istringstream iss(line);
        auto* info = new ProductInfo;
        iss >> client_id >> info->leftX >> info->leftY >>
            info->rightX >> info->rightY >> *info;
        info->client = products_container.findClientPointer(client_id);
        products_container.products.emplace_back(info);
    }

    return is;
}

ProductInfo* ProductsContainer::getProdInfoPos(int position) {
    return products[position];
}

ProductInfo* ProductsContainer::getProdInfo(int id) {
    for (auto& info : products) {
        if (info->product->getID() == id)
            return info;
    }
    return nullptr;
}

std::string ProductsContainer::getReceiptProductInfo(ProductInfo* info) {
    if (info->productType == "Exclusive") {
        auto* ptr = dynamic_cast<Exclusive*>(info->product);
        return std::to_string(ptr->getID()) + " " + info->productType + " " + ptr->getName() + " " +
            castDateString(ptr->getDate()) + " " + castDateString(ptr->getDateEnd()) + "\n";
    }
    else if (info->productType == "ShortTerm") {
        auto* ptr = dynamic_cast<ShortTerm*>(info->product);
        return std::to_string(ptr->getID()) + " " + info->productType + " " + ptr->getName() + " " +
            castDateString(ptr->getDate()) + " " + castDateString(ptr->getDateEnd()) + "\n";
    }
    else if (info->productType == "LongTerm") {
        auto* ptr = dynamic_cast<LongTerm*>(info->product);
        return std::to_string(ptr->getID()) + " " + info->productType + " " + ptr->getName() + " " +
            castDateString(ptr->getDate()) + "\n";
    }
    else if (info->productType == "Wholesale") {
        auto* ptr = dynamic_cast<Wholesale*>(info->product);
        return std::to_string(ptr->getID()) + " " + info->productType + " " + ptr->getName() + " " +
            castDateString(ptr->getDate()) + " " + castDateString(ptr->getDateEnd()) + "\n";
    }
}
