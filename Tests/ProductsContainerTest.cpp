#include "CppUnitTest.h"
#include "../StorehouseApp/ProductsContainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProductsContainerTest
{
    TEST_CLASS(ProductInfoTest)
    {
    public:

        TEST_METHOD(TestProdInfoExInOut)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            ProductInfo prodinfo;
            std::string inp = "Exclusive\t12\tNaszyjnik\t1\t2\t11-10-2011\t11-10-2034\tqwerty123\n";

            std::istringstream istrstr(inp);
            istrstr >> prodinfo;

            Assert::AreEqual(std::string("Exclusive"), prodinfo.productType);
            Assert::AreEqual(12, prodinfo.product->getID());
            Assert::AreEqual(std::string("Naszyjnik"), prodinfo.product->getName());
            Assert::AreEqual(1, prodinfo.product->getWidth());
            Assert::AreEqual(2, prodinfo.product->getHeight());
            Assert::AreEqual(start_date, prodinfo.product->getDate());
            Assert::AreEqual(end_date, static_cast<Exclusive*>(prodinfo.product)->getDateEnd());
            Assert::AreEqual(std::string("qwerty123"),
                static_cast<Exclusive*>(prodinfo.product)->getPassword());

            std::ostringstream outp;
            outp << prodinfo;
            Assert::AreEqual(inp, outp.str());
        }

        TEST_METHOD(TestProdInfoLtInOut)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            ProductInfo prodinfo;
            std::string inp = "LongTerm\t12\tFotel\t1\t2\t11-10-2011\n";

            std::istringstream istrstr(inp);
            istrstr >> prodinfo;

            Assert::AreEqual(std::string("LongTerm"), prodinfo.productType);
            Assert::AreEqual(12, prodinfo.product->getID());
            Assert::AreEqual(std::string("Fotel"), prodinfo.product->getName());
            Assert::AreEqual(1, prodinfo.product->getWidth());
            Assert::AreEqual(2, prodinfo.product->getHeight());
            Assert::AreEqual(start_date, prodinfo.product->getDate());

            std::ostringstream outp;
            outp << prodinfo;
            Assert::AreEqual(inp, outp.str());
        }

        TEST_METHOD(TestProdInfoCmp)
        {
            Client cli1 = Client(1), cli2 = Client(2);
            Product* prod1 = new Exclusive(11), *prod2 = new LongTerm(12);
            ProductInfo prodinfo1, prodinfo2;
            prodinfo1.client = &cli1;
            prodinfo1.product = prod2;
            prodinfo2.client = &cli2;
            prodinfo2.product = prod1;

            Assert::IsTrue(cmpProdInfoPtr(&prodinfo1, &prodinfo2));
            Assert::IsFalse(cmpProdInfoPtr(&prodinfo2, &prodinfo1));
        }
    };

    TEST_CLASS(ProductsContainerTest)
    {
    public:

        TEST_METHOD(TestFindClientPointer)
        {
            std::vector<Client> dummy_clients;
            Client cli1 = Client(1), cli2 = Client(2);
            dummy_clients.emplace_back(cli1);
            dummy_clients.emplace_back(cli2);

            ProductsContainer prodcont;
            prodcont.clients_ptr = &dummy_clients;

            Assert::AreEqual(int(&(dummy_clients[0])), int(prodcont.findClientPointer(1)));
            Assert::AreEqual(int(&(dummy_clients[1])), int(prodcont.findClientPointer(2)));
            Assert::IsNull(prodcont.findClientPointer(16));
        }

        TEST_METHOD(TestProdContInOut)
        {
            std::vector<Client> dummy_clients;
            Client cli1 = Client(1), cli2 = Client(2);
            dummy_clients.emplace_back(cli1);
            dummy_clients.emplace_back(cli2);

            ProductsContainer prodcont;
            prodcont.clients_ptr = &dummy_clients;

            std::string inp = "2\t2\t4\t3\t6\tExclusive\t12\tNaszyjnik\t1\t2\t11-10-2011\t11-10-2034\tqwerty123\n";
            inp += "1\t16\t17\t19\t21\tLongTerm\t13\tFotel\t3\t4\t11-10-2011\n";

            std::istringstream istrstr(inp);
            istrstr >> prodcont;

            Assert::AreEqual(2, static_cast<int>(prodcont.products.size()));
            Assert::AreEqual(12, prodcont.products[0]->product->getID());
            Assert::AreEqual(13, prodcont.products[1]->product->getID());

            std::ostringstream outp;
            outp << prodcont;
            Assert::AreEqual(inp, outp.str());
        }

        TEST_METHOD(TestProdContSort)
        {
            std::vector<Client> dummy_clients;
            Client cli1 = Client(1), cli2 = Client(2), cli0 = Client(0);
            dummy_clients.emplace_back(cli1);
            dummy_clients.emplace_back(cli2);
            dummy_clients.emplace_back(cli0);

            ProductsContainer prodcont;
            prodcont.clients_ptr = &dummy_clients;

            std::string inp = "2\t2\t4\t3\t6\tExclusive\t12\tNaszyjnik\t1\t2\t11-10-2011\t11-10-2034\tqwerty123\n";
            inp += "0\t0\t0\t1\t1\tLongTerm\t13\tDywan\t1\t1\t11-10-2011\n";
            inp += "1\t16\t17\t19\t21\tLongTerm\t18\tFotel\t3\t4\t11-10-2011\n";

            std::istringstream istrstr(inp);
            istrstr >> prodcont;

            Assert::AreEqual(12, prodcont.products[0]->product->getID());
            Assert::AreEqual(2, prodcont.products[0]->client->getClientID());
            Assert::AreEqual(13, prodcont.products[1]->product->getID());
            Assert::AreEqual(0, prodcont.products[1]->client->getClientID());
            Assert::AreEqual(18, prodcont.products[2]->product->getID());
            Assert::AreEqual(1, prodcont.products[2]->client->getClientID());

            prodcont.sortContainer();

            Assert::AreEqual(13, prodcont.products[0]->product->getID());
            Assert::AreEqual(0, prodcont.products[0]->client->getClientID());
            Assert::AreEqual(18, prodcont.products[1]->product->getID());
            Assert::AreEqual(1, prodcont.products[1]->client->getClientID());
            Assert::AreEqual(12, prodcont.products[2]->product->getID());
            Assert::AreEqual(2, prodcont.products[2]->client->getClientID());
        }

        TEST_METHOD(TestFindClientPart)
        {
            std::vector<Client> dummy_clients;
            Client cli2 = Client(2), cli0 = Client(0);
            dummy_clients.emplace_back(cli2);
            dummy_clients.emplace_back(cli0);

            ProductsContainer prodcont;
            prodcont.clients_ptr = &dummy_clients;

            std::string inp = "0\t2\t4\t3\t6\tExclusive\t12\tNaszyjnik\t1\t2\t11-10-2011\t11-10-2034\tqwerty123\n";
            inp += "2\t0\t0\t1\t1\tLongTerm\t13\tDywan\t1\t1\t11-10-2011\n";
            inp += "0\t16\t17\t19\t21\tLongTerm\t18\tFotel\t3\t4\t11-10-2011\n";

            std::istringstream istrstr(inp);
            istrstr >> prodcont;

            prodcont.sortContainer();

            Assert::AreEqual(0, prodcont.findClientPart(0));
            Assert::AreEqual(2, prodcont.findClientPart(2));
            Assert::AreEqual(-1, prodcont.findClientPart(1));
        }

        TEST_METHOD(TestFindClientPartLength)
        {
            std::vector<Client> dummy_clients;
            Client cli2 = Client(2), cli0 = Client(0);
            dummy_clients.emplace_back(cli2);
            dummy_clients.emplace_back(cli0);

            ProductsContainer prodcont;
            prodcont.clients_ptr = &dummy_clients;

            std::string inp = "0\t2\t4\t3\t6\tExclusive\t12\tNaszyjnik\t1\t2\t11-10-2011\t11-10-2034\tqwerty123\n";
            inp += "2\t0\t0\t1\t1\tLongTerm\t13\tDywan\t1\t1\t11-10-2011\n";
            inp += "0\t16\t17\t19\t21\tLongTerm\t18\tFotel\t3\t4\t11-10-2011\n";

            std::istringstream istrstr(inp);
            istrstr >> prodcont;

            prodcont.sortContainer();

            Assert::AreEqual(2, prodcont.findClientPartLength(0));
            Assert::AreEqual(1, prodcont.findClientPartLength(1));
        }
    };
}
