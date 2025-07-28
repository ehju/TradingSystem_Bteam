#include "gmock/gmock.h"
#include "StockBrockerDriver.cpp"
#include "AutoTradingSystem.cpp"

using namespace testing;


class MockDriver : public StockBrockerDriver {
public:
	MOCK_METHOD(void, login, (std::string id, std::string password), (override));
	MOCK_METHOD(void, buy, (std::string code, int price, int amount), (override));
	MOCK_METHOD(void, sell, (std::string code, int price, int amount), (override));
	MOCK_METHOD(int, getPrice, (std::string code), (override));
};

class TradeItem : public Test {
public:
	NiceMock<MockDriver> mock;
	std::string code = "code";
	std::string id = "id";
	std::string password = "password";
};


TEST_F(TradeItem, CallApiTest_LOGIN) {
	
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, login(id, password))
		.Times(1);
	app.login(id, password);
}

TEST_F(TradeItem, CallApiTest_BUY) {

	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, buy( code, price, amount))
		.Times(1);
	app.buy(code, price, amount);
}

TEST_F(TradeItem, CallApiTest_SELL) {
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, sell(code, price, amount))
		.Times(1);
	app.sell(code, price, amount);
}

TEST_F(TradeItem, CallApiTest_GETPRICE) {
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, getPrice(code))
		.Times(1)
		.WillRepeatedly(Return(1000));

	int ret = app.getPrice(code);
}

TEST_F(TradeItem, CheckGetPriceReturnValue) {

	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, getPrice(code))
		.Times(1)
		.WillRepeatedly(Return(1000));

	int ret = app.getPrice(code);
	EXPECT_EQ(ret,1000);
}

