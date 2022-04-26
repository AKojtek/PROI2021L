#include "CppUnitTest.h"
#include "../StorehouseApp/Client.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientTest
{
	TEST_CLASS(ClientTest)
	{
	public:

		TEST_METHOD(TestCliConstru)
		{
			Client cli = Client(12, "Adam Nowak", "Warszawa", "123456789");

			Assert::AreEqual(12, cli.getClientID());
			// TODO: Should getters for name, city and phone be implemented?
		}

		TEST_METHOD(TestCliDefualtConstru)
		{
			Client cli = Client();

			Assert::AreEqual(0, cli.getClientID());
			// TODO: Should getters for name, city and phone be implemented?
		}

		TEST_METHOD(TestInOutSimple)
		{
			Client cli;
			std::string inp = "12\tNowak\tWarszawa\t123456789\n";

			std::istringstream istrstr(inp);
			istrstr >> cli;
			Assert::AreEqual(12, cli.getClientID());
			// TODO: Check name, city, phone if getters implemented

			std::ostringstream outp;
			outp << cli;
			Assert::AreEqual(inp, outp.str());
		}

		TEST_METHOD(TestInOutMultipleWords)
		{
			// TODO: Allow name and city with multiple words
			
			Client cli;
			std::string inp = "12\t   [Adam Nowak]\t\t\t\t[Grodzisk Mazowiecki]\t\t\t\t123456789\n";
			std::string outp = "12\tAdam Nowak\tGrodzisk Mazowiecki\t123456789\n";

			std::istringstream istrstr(inp);
			istrstr >> cli;
			Assert::AreEqual(12, cli.getClientID());
			// TODO: Check name, city, phone if getters implemented

			std::ostringstream outp_str;
			outp_str << cli;
			Assert::AreEqual(outp, outp_str.str());
		}

		TEST_METHOD(TestCliComp)
		{
			Client cli1 = Client(12, "Adam Nowak", "Warszawa", "123456789");
			Client cli2 = Client(6, "Bartosz Kowalski", "Warszawa", "123456789");

			Assert::IsTrue(cli2 < cli1);
			Assert::IsFalse(cli1 < cli2);
		}

		TEST_METHOD(TestVecInOut)
		{
			std::vector<Client> clients;
			std::string inp = "12\tZofia\tWarszawa\t123456789\n";
			inp += "6\tYvonne\tWarszawa\t987654321\n";

			std::istringstream istrstr(inp);
			istrstr >> clients;
			Assert::AreEqual(2, static_cast<int>(clients.size()));
			Assert::AreEqual(12, clients[0].getClientID());
			Assert::AreEqual(6, clients[1].getClientID());

			std::ostringstream outp;
			outp << clients;
			Assert::AreEqual(inp, outp.str());
		}
	};
}
