#pragma once
#include "ProductsContainer.h"
#include "Product.h"
#include "Client.h"
#include "Receipt.h"
#include <tuple>

class Storehouse
{
private:
	std::string name;
	std::pair<int, int> size;
	std::vector<Client> clients;
	ProductsContainer prodcont;
	Receipt bill;
	bool taken_space[200][200] = { false };  // Choose better way or verify max size

	std::vector<Client>::iterator findClient(int client_id);
	std::vector<Client>::iterator findClient(const Client& cli);
	bool productFits(int x, int y, const Product& prod);
	std::tuple<int, int, int, int> firstSpaceForProduct(Product prod);
	std::tuple<int, int, int, int> lastSpaceForProduct(Product prod);
	std::tuple<int, int, int, int> bestSpaceForProduct(Product prod, std::string prod_type);
	std::vector<ProductInfo*>::iterator findProduct(int product_id);
	std::vector<ProductInfo*>::iterator findProduct(const Product& prod);
	void markSpace(std::tuple<int, int, int, int> space, bool mark);

public:
	Storehouse(std::string m_name = "", std::pair<int, int> m_size = std::make_pair(0, 0));
	~Storehouse();

	std::string getName() const;
	std::pair<int, int> getSize() const;
	std::vector<Client> getClients() const;
	void setClients(std::istream& data);
	void setProducts(std::istream& data);
	void setStorehouse(std::istream& data);
	void setReceiptValues(int days, int fine_mult, int lt, int st, int ex, int ws);
	ProductsContainer getProducts() const;
	std::string getTakenSpaceString() const;
	Receipt getReceipt() const;
	bool isExclusive(int product_id);
	bool shouldVerifyOwnership(int product_id);
	bool verifyOwnership(int product_id, std::string entered_password);
	bool isClientSet();

	Client* findClientPointer(int id);
	void changeReceiptClient(int id);
	void addReceiptProduct(int id);
	void removeReceiptProduct(int id);
	void createReceipt();
	std::string InReceipt();
	std::string NotInReceipt();

	void addClient(const Client& cli);
	bool removeClient(int client_id);
	bool removeClient(const Client& cli);
	bool addProduct(Product* prod, std::string prod_type, int client_id);
	bool addProduct(ProductInfo* prod_info, int client_id);
	bool removeProduct(std::vector<ProductInfo*>::iterator prod_info);
	bool removeProduct(int product_id);
	bool removeProduct(const Product& prod);
	void rearrange();

	friend std::istream& operator>> (std::istream& is, Storehouse& sh);
	friend std::ostream& operator<< (std::ostream& os, const Storehouse& sh);
	friend std::string prepareForFile (const Storehouse& sh);
};
