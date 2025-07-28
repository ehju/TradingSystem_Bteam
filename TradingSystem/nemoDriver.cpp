#include "StockBrockerDriver.cpp"
#include "nemo_api.cpp"

class NemoDriver : public IStockerBrocker {
	NemoDriver(NemoAPI* api) : nemoAPI{ api }, isLoggedIn{ false } {}
	// IStockerBrocker을(를) 통해 상속됨
	void login(std::string id, std::string password) override
	{
		nemoAPI->certification(id, password);
		isLoggedIn = true;
	}
	void buy(std::string code, int price, int amount) override
	{
		nemoAPI->purchasingStock(code, price, amount);
	}
	void sell(std::string code, int price, int amount) override
	{
		nemoAPI->sellingStock(code, price, amount);
	}
	int getPrice(std::string code) override
	{
		nemoAPI->getMarketPrice(code, 0);
	}
	bool isLoggedin() override
	{
		return isLoggedIn;
	}
private:
	NemoAPI* nemoAPI;
	bool isLoggedIn;
};