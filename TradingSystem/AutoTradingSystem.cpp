#pragma once
#include <iostream>
class AutoTradingSystem {
public:
	AutoTradingSystem(IStockerBrocker* brocker) : brocker{ brocker } {}
	
	void login(std::string id, std::string password) {
		return;
	}

	void buy(const std::string& code, int price, int amount) {
		return;
	}

	void sell(std::string code, int price, int amount) {
		return;
	}

private:
	IStockerBrocker* brocker;
};