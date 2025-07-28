
#include "gmock/gmock.h"
using namespace testing;

TEST(TS1, TC2) {
	EXPECT_EQ(1, 1);
}

class MockDriver : public StockBrockerDriver {
public:
	MOCK_METHOD(void, login, (std::string id, std::string password), (override));
	MOCK_METHOD(void, buy, (int code, int price, int amount), (override));
	MOCK_METHOD(void, sell, (int code, int price, int amount), (override));
	MOCK_METHOD(int, getPrice, (int code), (override));
};

TEST(LOGINTEST, TC1) {
	NiceMock<MockDriver> mock;
	std::string id = "wrongid";
	std::string password = "password";
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, login(id, password))
		.Times(1);
	app.login(id, password);
}

