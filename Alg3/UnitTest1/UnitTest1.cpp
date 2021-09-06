#include "pch.h"
#include "CppUnitTest.h"
#include "../Alg3/lab3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab3UnitTests
{
	TEST_CLASS(lab3UnitTests)
	{
	public:

		TEST_METHOD(constructor_exception1)
		{
			string msg;
			string expected = "Could not open file F";
			try
			{
				OrGraph G("F");
			}
			catch (exception& e)
			{
				msg = e.what();
			}
			Assert::AreEqual(expected, msg);
		}

		TEST_METHOD(constructor_exception2)
		{
			ofstream test("routes.txt");
			test.close();
			string msg;
			string expected = "Incorrect input";
			try
			{
				OrGraph G("routes.txt");
			}
			catch (exception& e)
			{
				msg = e.what();
			}
			Assert::AreEqual(expected, msg);
		}

		TEST_METHOD(shortest_way_exception)
		{
			ofstream test("routes.txt");
			test << "A;B;1";
			test.close();
			string msg;
			string expected = "There are no such elements";
			try
			{
				OrGraph G("routes.txt");
				G.get_shortest_way("A", "C");
			}
			catch (exception& e)
			{
				msg = e.what();
			}
			Assert::AreEqual(expected, msg);
		}

		TEST_METHOD(shortest_way1)
		{
			ofstream test("routes.txt");
			test << "A;B;1";
			test.close();
			OrGraph G("routes.txt");

			Assert::AreEqual(1, G.get_shortest_way("A", "B"));
			Assert::AreEqual(INT_MAX, G.get_shortest_way("B", "A"));
		}

		TEST_METHOD(shortest_way2)
		{
			ofstream test("routes.txt");
			test << "A;B;1\nA;C;10\nB;D;20\nC;D;10\nE;F;1\nF;G;2\nG;E;3";
			test.close();
			OrGraph G("routes.txt");

			Assert::AreEqual(20, G.get_shortest_way("A", "D"));
			Assert::AreEqual(INT_MAX, G.get_shortest_way("A", "E"));
			Assert::AreEqual(5, G.get_shortest_way("F", "E"));
		}
	};
}
