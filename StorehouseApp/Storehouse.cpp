#include "Storehouse.h"
#include <utility>

Storehouse::Storehouse(std::string m_name, std::pair<int, int> m_size)
{
	name = std::move(m_name);
	size = m_size;
	prodcont.clients_ptr = &clients;
}

Storehouse::~Storehouse() {
	for (auto info : prodcont.products)
		delete info;
}

std::string Storehouse::getName() const
{
	return name;
}

std::pair<int, int> Storehouse::getSize() const
{
	return size;
}

std::vector<Client> Storehouse::getClients() const
{
	return clients;
}

void Storehouse::setClients(std::istream& data) {
	data >> clients;
	prodcont.clients_ptr = &clients;
}

void Storehouse::setProducts(std::istream& data) {
	data >> prodcont;
	for (auto pinfo : prodcont.products)
	{
		for (int i = pinfo->leftX; i < pinfo->rightX; i++)
		{
			for (int j = pinfo->leftY; j < pinfo->rightY; j++)
				taken_space[i][j] = true;
		}
	}
}

void Storehouse::setStorehouse(std::istream& data)
{
	std::string line;
	std::getline(data, line);
	std::istringstream istrstr(line);
	char curr_char;

	istrstr.get(curr_char);
	while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
		istrstr.get(curr_char);
	if (curr_char == '[')
	{
		name = "";
		istrstr.get(curr_char);
		while (curr_char != ']')
		{
			name += curr_char;
			istrstr.get(curr_char);
		}
	}
	else
	{
		istrstr.unget();
		istrstr >> name;
	}

	istrstr >> size.first >> size.second;

	std::getline(data, line);	// Header "Cost Information:"
	std::string bill_str;
	std::getline(data, line);
	while (!line.empty() && line != "Clients:")
	{
		bill_str += line + '\n';
		std::getline(data, line);
	}

	std::istringstream bill_iss(bill_str);
	bill_iss >> bill;

	std::string clients_str;
	std::getline(data, line);
	while (!line.empty() && line != "Products:")
	{
		clients_str += line + '\n';
		std::getline(data, line);
	}

	std::istringstream clients_iss(clients_str);
	setClients(clients_iss);
	setProducts(data);
}

void Storehouse::setReceiptValues(int days, int fine_mult, int lt, int st, int ex, int ws)
{
	bill.setValues(days, fine_mult, lt, st, ex, ws);
}

ProductsContainer Storehouse::getProducts() const
{
	return prodcont;
}

Receipt Storehouse::getReceipt() const {
	return bill;
}

std::string Storehouse::getTakenSpaceString() const
{
	std::string ts_str;

	for (int i = 0; i < size.first; i++)
	{
		for (int j = 0; j < size.second; j++)
		{
			if (taken_space[i][j])
				ts_str += '#';
			else
				ts_str += '.';
		}
		ts_str += '\n';
	}

	return ts_str;
}

bool Storehouse::isExclusive(int product_id)
{
	std::vector<ProductInfo*>::iterator prod_it = findProduct(product_id);

	if (prod_it == prodcont.products.end())
		return false;
	if ((*prod_it)->productType == "Exclusive")
		return true;
	return false;
}

bool Storehouse::shouldVerifyOwnership(int product_id)
{
	std::vector<ProductInfo*>::iterator prod_it = findProduct(product_id);

	if (prod_it == prodcont.products.end() || bill.getClientPtr() == nullptr)
		return false;
	if ((*prod_it)->productType == "Exclusive" &&
		(*prod_it)->client->getClientID() == bill.getClientPtr()->getClientID())
		return true;
	return false;
}

bool Storehouse::verifyOwnership(int product_id, std::string entered_password)
{
	std::vector<ProductInfo*>::iterator prod_it = findProduct(product_id);
	return static_cast<Exclusive*>((*prod_it)->product)->verifyOwnership(entered_password);
}

void Storehouse::addClient(const Client& cli)
{
	// If clients can contain more objects, add client at the end
	if (clients.capacity() > clients.size()) {
		clients.push_back(cli);
	}
	// Otherwise, change pointers in products.
	else {
		std::vector<Client> temp_vector;
		temp_vector.assign(clients.begin(), clients.end());
		temp_vector.emplace_back(cli);
		for (auto& info : prodcont.products) {
			for (auto& tmp_client : temp_vector) {
				if (info->client->getClientID() == tmp_client.getClientID()) {
					info->client = &tmp_client;
					break;
				}
			}
		}
		prodcont.clients_ptr = &clients;
		clients.swap(temp_vector);
	}
	// Ta linia jest chyba nie potrzebna, pozycja vectora sie nie zmienila
	//prodcont.clients_ptr = &clients;
}

std::vector<Client>::iterator Storehouse::findClient(int client_id)
{
	std::vector<Client>::iterator it = clients.begin();

	while (it != clients.end())
	{
		if ((*it).getClientID() == client_id)
			return it;
		it++;
	}
	return it;
}

std::vector<Client>::iterator Storehouse::findClient(const Client& cli)
{
	return findClient(cli.getClientID());
}

bool Storehouse::removeClient(int client_id)
{
	std::vector<Client>::iterator cli_it = findClient(client_id);
	if (cli_it == clients.end())
		return false;
	// create receipt for client who will be deleted
	changeReceiptClient(client_id);
	prodcont.sortContainer();
	int index = prodcont.findClientPart(client_id);
	if (index != -1)
	{
		int length = prodcont.findClientPartLength(index);
		for (int i = index; i < index + length; i++) {
			bill.addProduct(prodcont.products[i]);
		}
		createReceipt();
	}


	// he should be without products now
	// we get id of last client
	int l_id = clients[clients.size() - 1].getClientID();
	if (l_id != client_id) {
		// find part of products that belongs to last client
		int l_index = prodcont.findClientPart(l_id);

		// swap elements in vector clients
		std::iter_swap(findClient(client_id), --clients.end());
		// now we should point products where is their owner now after last client relocation

		// if l_index == -1 then there is no products to relocate
		if (l_index != -1) {
			int l_length = prodcont.findClientPartLength(l_index);
			std::vector<Client>::iterator client_it = findClient(l_id);
			for (int i = l_index; i < l_index + l_length; i++) {
				prodcont.products[i]->client = &(*(client_it));
			}
		}
		// delete last client - client we wanted to delete
		clients.pop_back();
	}
	else clients.pop_back();
	return true;
}

bool Storehouse::removeClient(const Client& cli)
{
	std::vector<Client>::iterator it = findClient(cli);

	if (it != clients.end())
	{
		clients.erase(it);
		return true;
	}
	return false;
}

bool Storehouse::productFits(int x, int y, const Product& prod)
{
	for (int i = x; i < x + prod.getWidth(); i++)
	{
		for (int j = y; j < y + prod.getHeight(); j++)
		{
			if (taken_space[i][j])
				return false;
		}
	}

	return true;
}

std::tuple<int, int, int, int> Storehouse::firstSpaceForProduct(Product prod)
{
	for (int i = 0; i + prod.getWidth() <= size.first; i++)
	{
		for (int j = 0; j + prod.getHeight() <= size.second; j++)
		{
			if (productFits(i, j, prod))
				return std::make_tuple(i, j, i + prod.getWidth(), j + prod.getHeight());
			// TODO: Decide how to choose best place
		}
	}

	return std::make_tuple(-1, -1, -1, -1);
}

std::tuple<int, int, int, int> Storehouse::lastSpaceForProduct(Product prod)
{
	for (int i = size.first - prod.getWidth(); i >= 0; i--)
	{
		for (int j = size.second - prod.getHeight(); j >= 0; j--)
		{
			if (productFits(i, j, prod))
				return std::make_tuple(i, j, i + prod.getWidth(), j + prod.getHeight());
			// TODO: Decide how to choose best place
		}
	}

	return std::make_tuple(-1, -1, -1, -1);
}

std::tuple<int, int, int, int> Storehouse::bestSpaceForProduct(Product prod, std::string prod_type)
{
	if (prod.getHeight() < prod.getWidth())
		prod.rotate();
	
	std::tuple<int, int, int, int> space;

	if (prod_type == "Exclusive")
	{
		space = lastSpaceForProduct(prod);

		if (std::get<0>(space) != -1)
			return space;

		prod.rotate();

		return lastSpaceForProduct(prod);
	}

	space = firstSpaceForProduct(prod);

	if (std::get<0>(space) != -1)
		return space;

	prod.rotate();

	return firstSpaceForProduct(prod);
}

std::vector<ProductInfo*>::iterator Storehouse::findProduct(int product_id)
{
	std::vector<ProductInfo*>::iterator it = prodcont.products.begin();

	while (it != prodcont.products.end())
	{
		if ((*it)->product->getID() == product_id)
			return it;
		it++;
	}
	return it;
}

std::vector<ProductInfo*>::iterator Storehouse::findProduct(const Product& prod)
{
	return findProduct(prod.getID());
}

void Storehouse::markSpace(std::tuple<int, int, int, int> space, bool mark)
{
	for (int i = std::get<0>(space); i < std::get<2>(space); i++)
	{
		for (int j = std::get<1>(space); j < std::get<3>(space); j++)
			taken_space[i][j] = mark;
	}
}

bool Storehouse::addProduct(Product* prod, std::string prod_type, int client_id)
{
	// Returns whether placement was possible

	std::tuple<int, int, int, int> space = bestSpaceForProduct(*prod, prod_type);
	std::vector<Client>::iterator client_it = findClient(client_id);
	if ((std::get<0>(space) == -1) || (client_it == clients.end()))
		return false;

	auto* prod_info = new ProductInfo;
	prod_info->product = prod;
	prod_info->productType = std::move(prod_type);
	prod_info->client = &(*(client_it));

	prod_info->leftX = std::get<0>(space);
	prod_info->leftY = std::get<1>(space);
	prod_info->rightX = std::get<2>(space);
	prod_info->rightY = std::get<3>(space);
	prodcont.products.push_back(prod_info);
	markSpace(space, true);
	prodcont.sortContainer();
	return true;
}

bool Storehouse::addProduct(ProductInfo* product_info, int client_id)
{
	auto* prod_info = new ProductInfo;
	prod_info->product = product_info->product;
	prod_info->productType = product_info->productType;

	std::tuple<int, int, int, int> space = bestSpaceForProduct(*(prod_info->product), prod_info->productType);
	std::vector<Client>::iterator client_it = findClient(client_id);
	if ((std::get<0>(space) == -1) || (client_it == clients.end()))
		return false;

	prod_info->client = &(*(client_it));
	prod_info->leftX = std::get<0>(space);
	prod_info->leftY = std::get<1>(space);
	prod_info->rightX = std::get<2>(space);
	prod_info->rightY = std::get<3>(space);
	prodcont.products.push_back(prod_info);
	markSpace(space, true);
	prodcont.sortContainer();
	return true;
}

bool Storehouse::removeProduct(std::vector<ProductInfo*>::iterator prod_info_it)
{
	if (prod_info_it != prodcont.products.end())
	{
		std::tuple<int, int, int, int> space = std::make_tuple(
			(*prod_info_it)->leftX,
			(*prod_info_it)->leftY,
			(*prod_info_it)->rightX,
			(*prod_info_it)->rightY
		);
		markSpace(space, false);
		delete (*prod_info_it);
		prodcont.products.erase(prod_info_it);

		return true;
	}
	return false;
}

bool Storehouse::removeProduct(int product_id)
{
	std::vector<ProductInfo*>::iterator it = findProduct(product_id);

	return removeProduct(it);
}

bool Storehouse::removeProduct(const Product& prod)
{
	std::vector<ProductInfo*>::iterator it = findProduct(prod);

	return removeProduct(it);
}

void Storehouse::rearrange()
{
	prodcont.sortContainer();
	
	std::tuple<int, int, int, int> space;
	markSpace(std::make_tuple(0, 0, size.first, size.second), false);
	for (auto prod_info : prodcont.products)
	{
		space = bestSpaceForProduct(*(prod_info->product), prod_info->productType);
		prod_info->leftX = std::get<0>(space);
		prod_info->leftY = std::get<1>(space);
		prod_info->rightX = std::get<2>(space);
		prod_info->rightY = std::get<3>(space);
		markSpace(space, true);
	}
}

std::istream& operator>> (std::istream& is, Storehouse& sh)
{
	std::string line;

	std::getline(is, line);
	if (line.empty()) return is;

	std::istringstream istrstr(line);
	char curr_char;

	istrstr.get(curr_char);
	while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
		istrstr.get(curr_char);
	if (curr_char == '[')
	{
		sh.name = "";
		istrstr.get(curr_char);
		while (curr_char != ']')
		{
			sh.name += curr_char;
			istrstr.get(curr_char);
		}
	}
	else
	{
		istrstr.unget();
		istrstr >> sh.name;
	}

	istrstr >> sh.size.first >> sh.size.second;

	std::getline(is, line);
	is >> sh.bill;

	std::getline(is, line);  // Header "Clients:"

	std::getline(is, line);
	while (!line.empty() && line != "Products:")
	{
		std::istringstream ss(line);
		Client cli;
		ss >> cli;  // TODO: Check if works properly after Client is finished
		sh.addClient(cli);

		std::getline(is, line);
	}

	is >> sh.prodcont;

	return is;
}


std::ostream& operator<< (std::ostream& os, const Storehouse& sh)
{
	os << sh.name << '\t' << sh.size.first << '\t' << sh.size.second << '\n';
	
	os << "Cost Information:\n";
	os << sh.bill;

	os << "Clients:\n";
	for (int i = 0; i < sh.clients.size(); i++)
		os << sh.clients[i];

	os << "Products:\n";
	os << sh.prodcont;

	return os;
}

std::string prepareForFile(const Storehouse& sh)
{
	std::string out = '[' + sh.name + "]\t" +
		std::to_string(sh.size.first) + '\t' + std::to_string(sh.size.second) + '\n';

	out += "Cost Information:\n";
	out += prepareForFile(sh.bill);

	out += "Clients:\n";
	for (int i = 0; i < sh.clients.size(); i++)
		out += prepareForFile(sh.clients[i]);

	out += "Products:\n";
	out += prepareForFile(sh.prodcont);

	return out;
}

Client* Storehouse::findClientPointer(int id) {
	for (auto& client : clients) {
		if (client.getClientID() == id)
			return &client;
	}
	return nullptr;
}

void Storehouse::changeReceiptClient(int id) {
	bill.changeClient(findClientPointer(id));
}

void Storehouse::addReceiptProduct(int id) {
	bool flag = true;
	ProductInfo* ptr = prodcont.getProdInfo(id);
	if (ptr == nullptr)
		return;
	if (ptr->client->getClientID() != bill.getClientPtr()->getClientID()) {
		flag = false;
	}

	if (flag)
		bill.addProduct(ptr);
}

void Storehouse::removeReceiptProduct(int id) {
	bill.removeProduct(id);
}

void Storehouse::createReceipt() {
	std::time_t date = std::time(0);   // get time now
	struct tm timeinfo;
	localtime_s(&timeinfo, &date);

	char string_date[21];
	std::strftime(string_date, 21, "%F_%H-%M-%S", &timeinfo);
	
	std::string file_name = "[" + bill.getClientPtr()->getName() + "]_" + string_date + ".txt";
	std::ofstream os(file_name);
	std::string text = bill.prepareReceipt(name);
	os << text;
	os.close();
	ProductsContainer container = getProducts();
	int st_index = container.findClientPart(bill.getClientPtr()->getClientID());
	if (st_index != -1) {
		int length = container.findClientPartLength(st_index);
		for (int i = st_index; i < st_index + length; i++) {
			int prod_id = prodcont.getProdInfoPos(i)->product->getID();
			if (bill.isInReceipt(prod_id)) {
				bill.removeProduct(prod_id);
				removeProduct(prod_id);
				--i;
				--length;
			}
		}
	}
	bill.changeClient(nullptr);
	bill.clearProducts();
}

std::string Storehouse::InReceipt() {
	Client* cl_ptr = bill.getClientPtr();
	std::string list;
	if (cl_ptr == nullptr)
		return list;

	int index = prodcont.findClientPart(cl_ptr->getClientID());
	if (index != -1) {
		int length = prodcont.findClientPartLength(index);
		for (int i = index; i < index + length; i++) {
			if (bill.isInReceipt(prodcont.products[i]->product->getID()))
				list += prodcont.getReceiptProductInfo(prodcont.products[i]);
		}
	}
	return list;
}

std::string Storehouse::NotInReceipt() {
	Client* cl_ptr = bill.getClientPtr();
	std::string list;
	if (cl_ptr == nullptr)
		return list;

	int index = prodcont.findClientPart(cl_ptr->getClientID());
	if (index != -1) {
		int length = prodcont.findClientPartLength(index);
		for (int i = index; i < index + length; i++) {
			if (!bill.isInReceipt(prodcont.products[i]->product->getID()))
				list += prodcont.getReceiptProductInfo(prodcont.products[i]);
		}
	}
	return list;
}

bool Storehouse::isClientSet() {
	if (bill.getClientPtr() == nullptr)
		return false;
	return true;
}
