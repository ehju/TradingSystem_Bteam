#pragma once
#include <iostream>
#include "StockBrockerDriver.cpp"
class AutoTradingSystem {
public:
	AutoTradingSystem(IStockerBrocker* brocker) : brocker{ brocker } {}
	
	void login(std::string id, std::string password) {
		brocker->login(id, password);
		return;
	}

	void buy(const std::string& code, int price, int amount) {
		brocker->buy(code, price, amount);
		return;
	}

	void sell(std::string code, int price, int amount) {
		brocker->sell(code,price, amount);
		return;
	}

	int getPrice(std::string code) {
		return brocker->getPrice(code);
	}

	void sellNiceTiming(std::string code, int amount) {
		int current_price = brocker->getPrice(code);
		for (int i = 0; i < 2; ++i) {
			delay(200);
			current_price = brocker->getPrice(code);
		}
	}

private:
	void delay(int ms) {
		for (int i = 0; i < ms; ++i) {
			for (int j = 0; j < 1000; ++j);
		}
	}
	IStockerBrocker* brocker;
};