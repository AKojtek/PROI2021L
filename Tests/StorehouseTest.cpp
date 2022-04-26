#include "CppUnitTest.h"
#include "../StorehouseApp/Storehouse.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorehouseTest
{
	TEST_CLASS(StorehouseTest)
	{
	public:

		TEST_METHOD(TestShConstru)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });

			Assert::AreEqual(std::string("Magazyn"), sh.getName());
			Assert::AreEqual(24, sh.getSize().first);
			Assert::AreEqual(36, sh.getSize().second);
			Assert::AreEqual(0, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(0, static_cast<int>(sh.getProducts().products.size()));
		}

		TEST_METHOD(TestShDefaultConstru)
		{
			Storehouse sh = Storehouse();

			Assert::AreEqual(std::string(""), sh.getName());
			Assert::AreEqual(0, sh.getSize().first);
			Assert::AreEqual(0, sh.getSize().second);
			Assert::AreEqual(0, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(0, static_cast<int>(sh.getProducts().products.size()));
		}

		TEST_METHOD(TestAddClient)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });
			Client cli = Client(124, "Maciek", "Zakopane", "123456789");

			sh.addClient();
			Assert::AreEqual(1, static_cast<int>(sh.getClients().size()));
			sh.addClient(cli);
			Assert::AreEqual(2, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(124, sh.getClients()[1].getClientID());
		}

		TEST_METHOD(TestRemoveClient)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });
			Client cli0 = Client(124, "Maciek", "Zakopane", "123456789");
			Client cli1 = Client(320, "Stefan", "Warszawa", "333222111");

			sh.addClient(cli0);
			sh.addClient(cli1);
			Assert::AreEqual(2, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(124, sh.getClients()[0].getClientID());
			Assert::AreEqual(320, sh.getClients()[1].getClientID());

			sh.removeClient(cli1);
			Assert::AreEqual(1, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(124, sh.getClients()[0].getClientID());

			sh.addClient(cli1);
			Assert::AreEqual(2, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(124, sh.getClients()[0].getClientID());
			Assert::AreEqual(320, sh.getClients()[1].getClientID());

			sh.removeClient(124);
			Assert::AreEqual(1, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(320, sh.getClients()[0].getClientID());
		}

		TEST_METHOD(TestAddProduct)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });
			Client cli0 = Client(124, "Maciek", "Zakopane", "123456789");
			Client cli1 = Client(320, "Stefan", "Warszawa", "333222111");
			Client cli2 = Client(240, "Alfred", "Bydgoszcz", "987654321");

			sh.addClient(cli0);
			sh.addClient(cli1);
			sh.addClient(cli2);

			time_t start_date = castStringDate(std::string("11-10-2011"));
			time_t end_date = castStringDate(std::string("11-10-2034")); 
			Product* prod0 = new Exclusive(234, "potato", 12, 13, start_date, end_date, "password");
			Product* prod1 = new LongTerm(123, "pebble", 1, 2, start_date);
			Product* prod2 = new ShortTerm(345, "apple", 4, 3, start_date, end_date);

			Assert::IsTrue(sh.addProduct(prod0, "Exclusive", 124));
			Assert::AreEqual(1, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(12, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(23, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(24, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(36, sh.getProducts().products[0]->rightY);
			Assert::AreEqual(std::string("Exclusive"), sh.getProducts().products[0]->productType);
			Assert::AreEqual(124, sh.getProducts().products[0]->client->getClientID());

			Assert::IsTrue(sh.addProduct(prod1, "LongTerm", 320));
			Assert::AreEqual(2, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(0, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(2, sh.getProducts().products[1]->rightY);
			Assert::AreEqual(std::string("LongTerm"), sh.getProducts().products[1]->productType);
			Assert::AreEqual(320, sh.getProducts().products[1]->client->getClientID());

			Assert::IsTrue(sh.addProduct(prod2, "ShortTerm", 240));
			Assert::AreEqual(3, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(345, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[2]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(2, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(3, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(6, sh.getProducts().products[1]->rightY);
			Assert::AreEqual(std::string("ShortTerm"), sh.getProducts().products[1]->productType);
			Assert::AreEqual(240, sh.getProducts().products[1]->client->getClientID());

			Storehouse sh_tiny = Storehouse("Mini Magazyn", { 1, 1 });
			Client cli = Client(0, "Maciek", "Zakopane", "123456789");
			sh_tiny.addClient(cli);
			Product* prod_tiny = new LongTerm(123, "pebble", 1, 1, start_date);

			Assert::IsFalse(sh_tiny.addProduct(prod_tiny, "LongTerm", 3));
			Assert::IsTrue(sh_tiny.addProduct(prod_tiny, "LongTerm", 0));
			Assert::IsFalse(sh_tiny.addProduct(prod_tiny, "LongTerm", 0));
		}

		TEST_METHOD(TestAddProductInfo)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });
			Client cli0 = Client(124, "Maciek", "Zakopane", "123456789");
			Client cli1 = Client(320, "Stefan", "Warszawa", "333222111");
			Client cli2 = Client(240, "Alfred", "Bydgoszcz", "987654321");

			sh.addClient(cli0);
			sh.addClient(cli1);
			sh.addClient(cli2);

			time_t start_date = castStringDate(std::string("11-10-2011"));
			time_t end_date = castStringDate(std::string("11-10-2034"));
			Product* prod0 = new Exclusive(234, "potato", 12, 13, start_date, end_date, "password");
			Product* prod1 = new LongTerm(123, "pebble", 1, 2, start_date);
			Product* prod2 = new ShortTerm(345, "apple", 4, 3, start_date, end_date);
			ProductInfo* prodinfo0 = new ProductInfo;
			ProductInfo* prodinfo1 = new ProductInfo;
			ProductInfo* prodinfo2 = new ProductInfo;

			prodinfo0->product = prod0;
			prodinfo1->product = prod1;
			prodinfo2->product = prod2;
			prodinfo0->productType = "Exclusive";
			prodinfo1->productType = "LongTerm";
			prodinfo2->productType = "ShortTerm";

			Assert::IsTrue(sh.addProduct(prodinfo0, 124));
			Assert::AreEqual(1, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(12, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(23, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(24, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(36, sh.getProducts().products[0]->rightY);
			Assert::AreEqual(std::string("Exclusive"), sh.getProducts().products[0]->productType);
			Assert::AreEqual(124, sh.getProducts().products[0]->client->getClientID());

			Assert::IsTrue(sh.addProduct(prodinfo1, 320));
			Assert::AreEqual(2, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(0, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(2, sh.getProducts().products[1]->rightY);
			Assert::AreEqual(std::string("LongTerm"), sh.getProducts().products[1]->productType);
			Assert::AreEqual(320, sh.getProducts().products[1]->client->getClientID());

			Assert::IsTrue(sh.addProduct(prodinfo2, 240));
			Assert::AreEqual(3, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(345, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[2]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(2, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(3, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(6, sh.getProducts().products[1]->rightY);
			Assert::AreEqual(std::string("ShortTerm"), sh.getProducts().products[1]->productType);
			Assert::AreEqual(240, sh.getProducts().products[1]->client->getClientID());

			Storehouse sh_tiny = Storehouse("Mini Magazyn", { 1, 1 });
			Client cli = Client(0, "Maciek", "Zakopane", "123456789");
			sh_tiny.addClient(cli);
			Product* prod_tiny = new LongTerm(123, "pebble", 1, 1, start_date);
			ProductInfo* prodinfo_tiny = new ProductInfo;

			prodinfo_tiny->product = prod_tiny;
			prodinfo_tiny->productType = "LongTerm";

			Assert::IsFalse(sh_tiny.addProduct(prodinfo_tiny, 3));
			Assert::IsTrue(sh_tiny.addProduct(prodinfo_tiny, 0));
			Assert::IsFalse(sh_tiny.addProduct(prodinfo_tiny, 0));
		}

		TEST_METHOD(TestRemoveProduct)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });
			Client cli = Client(150, "Edward", "Gdynia", "123456789");

			sh.addClient(cli);

			time_t start_date = castStringDate(std::string("11-10-2011"));
			time_t end_date = castStringDate(std::string("11-10-2034"));
			Product* prod0 = new ShortTerm(234, "potato", 12, 13, start_date, end_date);
			Product* prod1 = new LongTerm(123, "pebble", 2, 1, start_date);

			sh.addProduct(prod0, "ShortTerm", 150);
			sh.addProduct(prod1, "LongTerm", 150);
			Assert::AreEqual(2, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(0, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(12, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(13, sh.getProducts().products[0]->rightY);
			Assert::AreEqual(123, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(13, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(15, sh.getProducts().products[1]->rightY);

			sh.removeProduct(*prod1);
			Assert::AreEqual(1, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(0, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(12, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(13, sh.getProducts().products[0]->rightY);

			prod1 = new LongTerm(123, "pebble", 2, 1, start_date);
			sh.addProduct(prod1, "LongTerm", 150);
			Assert::AreEqual(2, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(13, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(15, sh.getProducts().products[1]->rightY);

			sh.removeProduct(234);
			Assert::AreEqual(1, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(123, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(13, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(15, sh.getProducts().products[0]->rightY);

			sh.removeProduct(*prod1);
			Assert::AreEqual(0, static_cast<int>(sh.getProducts().products.size()));
		}

		TEST_METHOD(TestRearrange)
		{
			Storehouse sh = Storehouse("Magazyn", { 24, 36 });
			Client cli0 = Client(124, "Maciek", "Zakopane", "123456789");
			Client cli1 = Client(320, "Stefan", "Warszawa", "333222111");
			Client cli2 = Client(240, "Alfred", "Bydgoszcz", "987654321");

			sh.addClient(cli0);
			sh.addClient(cli1);
			sh.addClient(cli2);

			time_t start_date = castStringDate(std::string("11-10-2011"));
			time_t end_date = castStringDate(std::string("11-10-2034"));
			Product* prod0 = new Exclusive(234, "potato", 12, 13, start_date, end_date, "password");
			Product* prod1 = new LongTerm(123, "pebble", 1, 2, start_date);
			Product* prod2 = new ShortTerm(345, "apple", 4, 3, start_date, end_date);

			Assert::IsTrue(sh.addProduct(prod0, "Exclusive", 124));
			Assert::AreEqual(12, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(23, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(24, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(36, sh.getProducts().products[0]->rightY);

			Assert::IsTrue(sh.addProduct(prod1, "LongTerm", 320));
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(0, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(2, sh.getProducts().products[1]->rightY);

			Assert::IsTrue(sh.addProduct(prod2, "ShortTerm", 240));
			Assert::AreEqual(3, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(345, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[2]->product->getID());
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(2, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(3, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(6, sh.getProducts().products[1]->rightY);

			sh.rearrange();

			Assert::AreEqual(3, static_cast<int>(sh.getProducts().products.size()));
			Assert::AreEqual(234, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(345, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(123, sh.getProducts().products[2]->product->getID());
			Assert::AreEqual(12, sh.getProducts().products[0]->leftX);
			Assert::AreEqual(23, sh.getProducts().products[0]->leftY);
			Assert::AreEqual(24, sh.getProducts().products[0]->rightX);
			Assert::AreEqual(36, sh.getProducts().products[0]->rightY);
			Assert::AreEqual(0, sh.getProducts().products[1]->leftX);
			Assert::AreEqual(0, sh.getProducts().products[1]->leftY);
			Assert::AreEqual(3, sh.getProducts().products[1]->rightX);
			Assert::AreEqual(4, sh.getProducts().products[1]->rightY);
			Assert::AreEqual(0, sh.getProducts().products[2]->leftX);
			Assert::AreEqual(4, sh.getProducts().products[2]->leftY);
			Assert::AreEqual(1, sh.getProducts().products[2]->rightX);
			Assert::AreEqual(6, sh.getProducts().products[2]->rightY);
		}

		TEST_METHOD(TestInOut)
		{
			Storehouse sh;
			std::string inp = "Magazyn\t32\t64\n";
			inp += "Cost Information:\nHow_Long_is_ShortTerm:\t98\nPenalty_multiplier:\t5\n";
			inp += "LongTerm:\t15\nShorterm:\t5\nExclusive:\t64\nWholesale:\t2\n";
			inp += "Clients:\n";
			inp += "1\tEdward\tWarszawa\t123456789\n";
			inp += "2\tHenryk\tSzczecin\t987654321\n";
			inp += "Products:\n";
			inp += "1\t0\t0\t3\t4\tExclusive\t11\tSamochód\t3\t4\t13-05-2021\t13-06-2021\tPassword12\n";
			inp += "1\t3\t0\t5\t2\tLongTerm\t12\tZ³oto\t2\t2\t10-02-2010\n";
			inp += "2\t5\t0\t6\t2\tShortTerm\t13\tZabawka\t1\t2\t05-05-2021\t10-05-2021\n";
			inp += "2\t6\t0\t7\t1\tWholesale\t14\tD³ugopis\t1\t1\t03-02-2019\t20-04-2022\n";

			std::istringstream istrstr(inp);
			istrstr >> sh;
			Assert::AreEqual(std::string("Magazyn"), sh.getName());
			Assert::AreEqual(32, sh.getSize().first);
			Assert::AreEqual(64, sh.getSize().second);
			Assert::AreEqual(2, static_cast<int>(sh.getClients().size()));
			Assert::AreEqual(4, static_cast<int>(sh.getProducts().products.size()));

			Assert::AreEqual(1, sh.getClients()[0].getClientID());
			Assert::AreEqual(2, sh.getClients()[1].getClientID());

			Assert::AreEqual(11, sh.getProducts().products[0]->product->getID());
			Assert::AreEqual(12, sh.getProducts().products[1]->product->getID());
			Assert::AreEqual(13, sh.getProducts().products[2]->product->getID());
			Assert::AreEqual(14, sh.getProducts().products[3]->product->getID());

			std::ostringstream outp;
			outp << sh;
			Assert::AreEqual(inp, outp.str());
		}

		TEST_METHOD(TestTakenSpace)
		{
			Storehouse sh = Storehouse("Magazyn", { 3, 3 });
			Client cli = Client(0, "Yvonne", "Philadelphia", "123456789");
			sh.addClient(cli);

			time_t start_date = castStringDate(std::string("11-10-2011"));
			Product* prod = new LongTerm(123, "pebble", 1, 2, start_date);

			Assert::AreEqual(std::string("...\n...\n...\n"), sh.getTakenSpaceString());
			
			sh.addProduct(prod, "LongTerm", 0);
			Assert::AreEqual(std::string("##.\n...\n...\n"), sh.getTakenSpaceString());
		}
	};
}
