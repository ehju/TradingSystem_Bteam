#pragma once
#include <string>
using std::string;

// Interface class for StockBrockerDriver
class IStockerBrocker {
public:
	virtual void login(std::string id, std::string password) = 0;
	virtual void buy(std::string code, int price, int amount) = 0;
	virtual void sell(std::string code, int price, int amount) = 0;
	virtual int getPrice(std::string code) = 0;
};

class StockBrockerDriver : public IStockerBrocker {
public:
	void login(std::string id, std::string password) override {
	
	}

	void buy(std::string code, int price, int amount) override {
	
	}

	void sell(std::string code, int price, int amount) override {
	
	}

	int getPrice(std::string code) override {
		return 0;
	}
};