#pragma once
#include "Product.h"
#include "Client.h"
#include <algorithm>
#include <sstream>

struct ProductInfo {
public:
    Client* client;
    Product* product;
    std::string productType;
    int leftX;
    int leftY;
    int rightX;
    int rightY;
    ~ProductInfo();
};

bool cmpProdInfoPtr (ProductInfo* product_info, ProductInfo* other);
std::istream& operator>> (std::istream& is, ProductInfo& product_info);
std::ostream& operator<< (std::ostream& os, const ProductInfo& product_info);
std::string prepareForFile (const ProductInfo& product_info);

class ProductsContainer {
public:
    std::vector<Client>* clients_ptr;
    std::vector<ProductInfo*> products;

    void sortContainer();
    int findClientPart(int clientID);
    int findClientPartLength(int partStart);
    int findSmallestMissingProd();
    int findSmallestMissingCli();
    int findSmallestMissing(int array[], int start, int end);
    Client* findClientPointer(int id) const;
    ProductInfo* getProdInfoPos(int position);
    ProductInfo* getProdInfo(int id);
    std::string getReceiptProductInfo(ProductInfo* info);

};

std::istream& operator>> (std::istream& is, ProductsContainer& products_container);
std::ostream& operator<< (std::ostream& os, const ProductsContainer& products_container);
std::string prepareForFile (const ProductsContainer& products_container);
