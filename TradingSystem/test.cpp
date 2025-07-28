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
	MOCK_METHOD(bool, isLoggedin, (), (override));

};

class TradeItem : public Test {
public:
	NiceMock<MockDriver> mock;
	std::string code = "itemcode";
	std::string id = "id";
	std::string password = "password";
};


TEST_F(TradeItem, CallApiTest_LOGIN) {
	
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, login(id, password))
		.Times(1);
	app.login(id, password);

	EXPECT_CALL(mock, isLoggedin())
		.WillRepeatedly(Return(true));
	EXPECT_EQ(true, app.isLoggedin());
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

TEST_F(TradeItem, getSetTotalAccountMoney) {
	int myTotalAccount = 20000;
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };

	EXPECT_CALL(mock, getPrice(code))
		.Times(0);

	app.setTotalAccount(myTotalAccount);
	EXPECT_EQ(myTotalAccount, app.getTotalAccount());
}

TEST_F(TradeItem, getMyStockCount) {
	int myTotalAccount = 20000;
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };

	app.buy(code, 1000, 3); // buy 3 stock
	EXPECT_EQ(3, app.getMyStock(code)); // check if 3 stock is in my account
}

TEST_F(TradeItem, buyNiceTiming_CallGetPriceThreeTimes) {
	int totalPrice = 10000;
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, getPrice(code))
		.Times(3)
		.WillOnce(Return(1))
		.WillOnce(Return(2))
		.WillOnce(Return(3));

	app.buyNiceTiming(code, totalPrice);
}

TEST_F(TradeItem, sellNiceTiming_CallGetPriceThreeTimes) {
	int totalPrice = 10000;
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	EXPECT_CALL(mock, getPrice(code))
		.Times(3);

	app.sellNiceTiming(code, totalPrice);
}



TEST_F(TradeItem, buyNiceTiming_SUCCESS) {
	int totalPrice = 10000;
	int myTotalAccount = 20000;
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };

	app.setTotalAccount(myTotalAccount); 

	EXPECT_CALL(mock, getPrice(code))
		.Times(3)
		.WillOnce(Return(1000))
		.WillOnce(Return(2000))
		.WillOnce(Return(3000)); // rising


	app.buyNiceTiming(code, totalPrice); // buy 3000 *3 stock

	int expectedStockCount = 3;
	int expectedRemainAccount = 11000;
	EXPECT_EQ(expectedStockCount, app.getMyStock(code));
	EXPECT_EQ(expectedRemainAccount, app.getTotalAccount());
}

TEST_F(TradeItem, buyNiceTiming_FAIL) {
	int totalPrice = 10000;
	int myTotalAccount = 20000;
	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };

	app.setTotalAccount(myTotalAccount);

	EXPECT_CALL(mock, getPrice(code))
		.Times(3)
		.WillOnce(Return(1000))
		.WillOnce(Return(3000))
		.WillOnce(Return(1000)); // fail


	app.buyNiceTiming(code, totalPrice); // buy nothing

	int expectedStockCount = 0;
	int expectedRemainAccount = 20000;
	EXPECT_EQ(expectedStockCount, app.getMyStock(code));
	EXPECT_EQ(expectedRemainAccount, app.getTotalAccount());
}


TEST_F(TradeItem, CallApiTest_BUYFAIL) {

	int price = 1000;
	int amount = 1;
	AutoTradingSystem app{ &mock };
	app.setTotalAccount(0);
	
	EXPECT_THROW(app.buy(code, price, amount), std::exception);
}


TEST_F(TradeItem, CallApiTest_BUY_NICETIMING_FAIL) {

	int price = 1000;
	int amount = 1;
	int totalPrice = 10000;
	int myTotalAccount = 20000;
	AutoTradingSystem app{ &mock };
	app.setTotalAccount(myTotalAccount);
	
	EXPECT_THROW(app.buyNiceTiming(code, totalPrice), std::exception);
}


TEST_F(TradeItem, CallApiTest_SELLFAIL) {

	int price = 1000;
	int amount = 3;
	int myTotalAccount = 20000;
	AutoTradingSystem app{ &mock };

	// precondition
	app.setTotalAccount(myTotalAccount);
	app.buy(code, price, amount); // buy 3 stock
	EXPECT_EQ(3, app.getMyStock(code)); // check if 3 stock is in my account


	EXPECT_THROW(app.sell(code, price, amount+1), std::exception); // try to sell more than i have
}


TEST_F(TradeItem, CallApiTest_SELL_NICETIMING_FAIL) {

	int price = 1000;
	int amount = 3;
	int totalPrice = 10000;
	int myTotalAccount = 20000;
	AutoTradingSystem app{ &mock };
	app.setTotalAccount(myTotalAccount);

	EXPECT_THROW(app.sellNiceTiming(code, amount+1), std::exception);
}

