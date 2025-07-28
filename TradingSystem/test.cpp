#include "gmock/gmock.h"
#include "StockBrockerDriver.cpp"
#include "AutoTradingSystem.cpp"

using namespace testing;

TEST(TS1, TC2) {
	EXPECT_EQ(1, 1);
}

class MockDriver : public StockBrockerDriver {
public:
	MOCK_METHOD(void, login, (std::string id, std::string password), (override));
	MOCK_METHOD(void, buy, (std::string code, int price, int amount), (override));
	MOCK_METHOD(void, sell, (std::string code, int price, int amount), (override));
	MOCK_METHOD(int, getPrice, (std::string code), (override));
};


TEST(LOGINTEST, CallApiTest_BUY) {
	NiceMock<MockDriver> mock;
	std::string id = "id";
	std::string password = "password";
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, login(id, password))
		.Times(1);
	app.login(id, password);
}

TEST(BUYTEST, CallApiTest_BUY) {
	NiceMock<MockDriver> mock;
	std::string code = "code";

	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, buy( code, price, amount))
		.Times(1);
	app.buy(code, price, amount);
}

TEST(SELLTEST, CallApiTest_SELL) {
	NiceMock<MockDriver> mock;
	std::string code = "code";
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, sell(code, price, amount))
		.Times(1);
	app.sell(code, price, amount);
}

TEST(GETPRICETEST, CallApiTest_GETPRICE) {
	NiceMock<MockDriver> mock;
	std::string code = "code";
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, getPrice(code))
		.Times(1)
		.WillRepeatedly(Return(1000));

	int ret = app.getPrice(code);
}

TEST(GETPRICETEST, CheckGetPriceReturnValue) {
	NiceMock<MockDriver> mock;
	std::string code = "code";
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, getPrice(code))
		.Times(1)
		.WillRepeatedly(Return(1000));

	int ret = app.getPrice(code);
	EXPECT_EQ(ret,1000);
}
