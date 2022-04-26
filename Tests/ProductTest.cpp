#include "CppUnitTest.h"
#include "../StorehouseApp/Product.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProductTest
{
	TEST_CLASS(ExclusiveProductTest)
	{
	public:

		TEST_METHOD(TestExProdConstru)
		{
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            Exclusive prod = Exclusive(12, "Naszyjnik", 1, 2, start_date, end_date, "qwerty123");

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("Naszyjnik"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
            Assert::AreEqual(end_date, prod.getDateEnd());
            Assert::AreEqual(std::string("qwerty123"), prod.getPassword());
		}

		TEST_METHOD(TestExProdDefualtConstru)
		{
            Exclusive prod = Exclusive();

            Assert::AreEqual(0, prod.getID());
            Assert::AreEqual(std::string(""), prod.getName());
            Assert::AreEqual(0, prod.getWidth());
            Assert::AreEqual(0, prod.getHeight());
            Assert::AreEqual(time_t(0), prod.getDate());
            Assert::AreEqual(time_t(0), prod.getDateEnd());
            Assert::AreEqual(std::string(""), prod.getPassword());
		}

		TEST_METHOD(TestExProdInOut)
		{
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            Exclusive prod;
            std::string inp = "12\tNaszyjnik\t1\t2\t11-10-2011\t11-10-2034\tqwerty123\n";

            std::istringstream istrstr(inp);
            istrstr >> prod;

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("Naszyjnik"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
            Assert::AreEqual(end_date, prod.getDateEnd());
            Assert::AreEqual(std::string("qwerty123"), prod.getPassword());

			std::ostringstream outp;
			outp << prod;
			Assert::AreEqual(inp, outp.str());
		}

        TEST_METHOD(TestExVerifyOwnership)
        {
            // TODO: Add test when implemented
        }
	};

    TEST_CLASS(WholesaleProductTest)
    {
    public:

        TEST_METHOD(TestWsProdConstru)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            Wholesale prod = Wholesale(12, "But", 1, 2, start_date, end_date);

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("But"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
            Assert::AreEqual(end_date, prod.getDateEnd());
        }

        TEST_METHOD(TestWsProdDefualtConstru)
        {
            Wholesale prod = Wholesale();

            Assert::AreEqual(0, prod.getID());
            Assert::AreEqual(std::string(""), prod.getName());
            Assert::AreEqual(0, prod.getWidth());
            Assert::AreEqual(0, prod.getHeight());
            Assert::AreEqual(time_t(0), prod.getDate());
            Assert::AreEqual(time_t(0), prod.getDateEnd());
        }

        TEST_METHOD(TestWsProdInOut)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            Wholesale prod;
            std::string inp = "12\tBut\t1\t2\t11-10-2011\t11-10-2034\n";

            std::istringstream istrstr(inp);
            istrstr >> prod;

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("But"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
            Assert::AreEqual(end_date, prod.getDateEnd());

            std::ostringstream outp;
            outp << prod;
            Assert::AreEqual(inp, outp.str());
        }
    };

    TEST_CLASS(ShortTermProductTest)
    {
    public:

        TEST_METHOD(TestStProdConstru)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            ShortTerm prod = ShortTerm(12, "Mas這", 1, 2, start_date, end_date);

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("Mas這"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
            Assert::AreEqual(end_date, prod.getDateEnd());
        }

        TEST_METHOD(TestStProdDefualtConstru)
        {
            ShortTerm prod = ShortTerm();

            Assert::AreEqual(0, prod.getID());
            Assert::AreEqual(std::string(""), prod.getName());
            Assert::AreEqual(0, prod.getWidth());
            Assert::AreEqual(0, prod.getHeight());
            Assert::AreEqual(time_t(0), prod.getDate());
            Assert::AreEqual(time_t(0), prod.getDateEnd());
        }

        TEST_METHOD(TestStProdInOut)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            time_t end_date = castStringDate(std::string("11-10-2034"));
            ShortTerm prod;
            std::string inp = "12\tMas這\t1\t2\t11-10-2011\t11-10-2034\n";

            std::istringstream istrstr(inp);
            istrstr >> prod;

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("Mas這"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
            Assert::AreEqual(end_date, prod.getDateEnd());

            std::ostringstream outp;
            outp << prod;
            Assert::AreEqual(inp, outp.str());
        }
    };

    TEST_CLASS(LongTermProductTest)
    {
    public:

        TEST_METHOD(TestLtProdConstru)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            LongTerm prod = LongTerm(12, "Fotel", 1, 2, start_date);

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("Fotel"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());
        }

        TEST_METHOD(TestLtProdDefualtConstru)
        {
            LongTerm prod = LongTerm();

            Assert::AreEqual(0, prod.getID());
            Assert::AreEqual(std::string(""), prod.getName());
            Assert::AreEqual(0, prod.getWidth());
            Assert::AreEqual(0, prod.getHeight());
            Assert::AreEqual(time_t(0), prod.getDate());
        }

        TEST_METHOD(TestLtProdInOut)
        {
            time_t start_date = castStringDate(std::string("11-10-2011"));
            LongTerm prod;
            std::string inp = "12\tFotel\t1\t2\t11-10-2011\n";

            std::istringstream istrstr(inp);
            istrstr >> prod;

            Assert::AreEqual(12, prod.getID());
            Assert::AreEqual(std::string("Fotel"), prod.getName());
            Assert::AreEqual(1, prod.getWidth());
            Assert::AreEqual(2, prod.getHeight());
            Assert::AreEqual(start_date, prod.getDate());

            std::ostringstream outp;
            outp << prod;
            Assert::AreEqual(inp, outp.str());
        }
    };
}
