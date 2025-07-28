#pragma once
#include <iostream>
#include "StockBrockerDriver.cpp"
#include <thread>
#include <chrono>

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

	void buyNiceTiming(std::string code, int totalPrice) {
		int prevPrice = brocker->getPrice(code);
		int currPrice;
		
		for (int i = 0; i < 2; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			currPrice = brocker->getPrice(code);
			if (currPrice <= prevPrice) {
				std::cout << "Not Buying" << std::endl;
				return;
			}
			else {
				prevPrice = currPrice;
			}
		}
		
		buy(code, currPrice, totalPrice / currPrice);
		return;
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
		for (int i = 0; i < ms; ++i) {
			for (int j = 0; j < 1000; ++j);
		}
	}
	IStockerBrocker* brocker;
	int deposit{ 0 };
};