#pragma once
#include "ProductsContainer.h"
#include "Product.h"
#include "Client.h"

class Receipt {
    std::vector<ProductInfo*> rec_products;
    Client* client;
    // Fine if client takes back his items :
    // 1) for Long Term     start_time + short_term < now()
    // 2) for Short Term    now() > end_time
    // 3) for Exclusive     now() > end_time
    // 4) for Wholesale     now() > end_time
    std::time_t short_term;
    // by which value will be price multiplied
    int fine_multiplier;
    // Long term price
    int cost_LT;
    // Short term price
    int cost_ST;
    // Exclusive price
    int cost_Ex;
    // Wholesale price
    int cost_WS;
public:
    void setValues(int days, int fine_mult, int LT, int ST, int Ex, int WS);

    std::string prepareReceipt(std::string sh_name);
    void addProduct(ProductInfo* info);
    void removeProduct(int product_id);
    void changeClient(Client* client_ptr); // client products should be cleared first
    void clearProducts();
    bool isInReceipt(int prod_id);
    int  getProductValue(ProductInfo* info);
    int  getReceiptValue();
    std::time_t getShortTerm();
    Client* getClientPtr();
    std::vector<ProductInfo*>* getReceiptList();

    friend std::istream& operator>> (std::istream& is, Receipt& rec);
    friend std::ostream& operator<< (std::ostream& os, const Receipt& rec);
    friend std::string prepareForFile(const Receipt& sh);
};
