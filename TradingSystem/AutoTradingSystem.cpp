#pragma once
#include <iostream>
#include "StockBrockerDriver.cpp"
#include <thread>
#include <chrono>
#include <map>
#include <stdexcept>

class AutoTradingSystem {
public:
	AutoTradingSystem(IStockerBrocker* brocker) : brocker{ brocker } {}
	
	void login(std::string id, std::string password) {
		brocker->login(id, password);
		return;
	}
	bool isLoggedin() {
		
		return brocker->isLoggedin();
	}
	void buy(const std::string& code, int price, int amount) {

		if (price * amount > deposit)
		{
			throw std::exception("You don't have enough money");
		}

		brocker->buy(code, price, amount);
		myStock[code] += amount;
		deposit -= (price * amount);
		return;
	}

	void sell(std::string code, int price, int amount) {
		if (amount > getMyStock(code)) {
			throw(std::exception("You don't have enough amount"));
		}
		brocker->sell(code,price, amount);
		myStock[code] -= amount;
		deposit += (price * amount);
		return;
	}

	int getPrice(std::string code) {
		return brocker->getPrice(code);

	}

	void sellNiceTiming(std::string code, int amount) {
		int sellPrice = 0;
		int flag = isSellCondition(code, sellPrice);
		if (amount > getMyStock(code)) {
			throw(std::exception("You don't have enough amount"));
		}
		if (flag) {

			sell(code, sellPrice, amount);
		}
	}

	void buyNiceTiming(std::string code, int totalPrice) {
		int buyPrice= -1;
		
		if (isBuyCondition(code, buyPrice)) {
			buy(code, buyPrice, totalPrice / buyPrice);
		}
		return;
	}

	int getMyStock(std::string code) {
		if (hasStock(code)) {
			return myStock[code];
		}
		else {
			return 0;
		}
	}
	void setTotalAccount(int money)
	{
		deposit = money;
	}

	int getTotalAccount()
	{
		return deposit;
	}

private:
	void delay(int ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	bool hasStock(std::string code)
	{
		auto it = myStock.find(code);
		return it != myStock.end();
	}

	bool isBuyCondition(const std::string& code, int& buyPrice)
	{
		int prevPrice = getPrice(code);

		for (int i = 0; i < 2; i++) {
			delay(200);
			int currPrice = getPrice(code);
			if (currPrice <= prevPrice) {
				return false;
			}
			else {
				prevPrice = currPrice;
			}
		}
		buyPrice = prevPrice;
		return true;
	}

	bool isSellCondition(const std::string& code, int& sellPrice)
	{
		int prevPrice = getPrice(code);
		bool decreased = true;
		for (int i = 0; i < 2; i++) {
			delay(200);
			int currPrice = getPrice(code);
			if (currPrice >= prevPrice) {
				decreased = false;
			}
			else {
				prevPrice = currPrice;
			}
		}
		if (decreased) {
			sellPrice = prevPrice;
		} else {
			sellPrice = -1;
		}
		return decreased;
	}

	IStockerBrocker* brocker;
	std::map<std::string, int> myStock;
	int deposit{ 0 };
};