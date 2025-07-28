#include "StockBrockerDriver.cpp"
#include "kiwer_api.cpp"

class KiwerDriver : public IStockerBrocker {
	KiwerDriver(KiwerAPI* api) : kiwerAPI { api }, isLoggedIn{ false } {}
	// IStockerBrocker을(를) 통해 상속됨
	void login(std::string id, std::string password) override
	{
		kiwerAPI->login(id, password);
		isLoggedIn = true;
	}
	void buy(std::string code, int price, int amount) override
	{
		kiwerAPI->buy(code, amount, price);
	}
	void sell(std::string code, int price, int amount) override
	{
		kiwerAPI->sell(code, amount, price);
	}
	int getPrice(std::string code) override
	{
		kiwerAPI->currentPrice(code);
	}
	bool isLoggedin() override
	{
		return isLoggedIn;
	}
private:
	KiwerAPI* kiwerAPI;
	bool isLoggedIn;
};