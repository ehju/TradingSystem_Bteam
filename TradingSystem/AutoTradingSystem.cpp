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
		return;
	}

	void sell(std::string code, int price, int amount) {
		brocker->sell(code,price, amount);
		return;
	}

	int getPrice(std::string code) {
		return -1;
	}

private:
	IStockerBrocker* brocker;
};