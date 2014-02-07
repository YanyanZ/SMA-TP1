# include "Banker.hpp"

void Banker::run()
{
  try
  {
    std::string ip = "127.0.0.1";
    std::string port = "8080";

    boost::asio::io_service io_service;
    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);

    boost::asio::connect(s, resolver.resolve({ip.c_str(), port.c_str()}));
    for (;;)
    {
      // Wait
      sleep(1);

      // Get current cotation and quantity for stocks
      std::vector<int> current_price;
      current_price.resize(5);
      current_price[0] = getCotation("TC", &s);
      current_price[1] = getCotation("TI", &s);
      current_price[2] = getCotation("MM", &s);
      current_price[3] = getCotation("TE", &s);
      current_price[4] = getCotation("BI", &s);

      std::vector<int> current_qty;
      current_qty.resize(5);
      current_qty[0] = getQuantity("TC", &s);
      current_qty[1] = getQuantity("TI", &s);
      current_qty[2] = getQuantity("MM", &s);
      current_qty[3] = getQuantity("TE", &s);
      current_qty[4] = getQuantity("BI", &s);

      std::vector<int> cpy_actions = actions_own;

      // Get min/max of own actions
      int min_quantity = min(cpy_actions);
      int max_quantity = max(cpy_actions);

      // Get min/max price
      int min_price = min(current_price);
      int max_price = max(current_price);

      int old_wallet = wallet;

      if (objectif == BUY)
      {
	happy += 7;
	crazy += 1;

	std::string id = cpy[min_price];
	if (current_price[min_price] == 0)
	  current_price[min_price] = 1;
	int qty = wallet / current_price[min_price];
	if (qty > current_qty[min_price])
	{
	  happy -= 2;
	  qty = current_qty[min_price];
	}

	std::string res = buy(id, qty, &s);
	if (res.compare("ok"))
	{
	  wallet += qty * current_price[min_price];
	  actions_own[min_price] -= qty;
	}
	else
	  happy -= 5;

      }
      else if (objectif == SELL)
      {
	happy += 10;
	crazy += 1;

	int i;
	std::string id;
	int qty = 0;
	if (actions_own[max_price] > 5)
	  i = max_price;
	else
	  i = max_quantity;

	id = cpy[i];
	qty = actions_own[i];
	sell(id, qty, &s);
	wallet += qty * current_price[i];
	actions_own[i] -= qty;

      }
      else if (objectif == STOCK)
      {
	std::string id = cpy[max_quantity];
	int qty = wallet / current_price[max_quantity];

	sell(id, qty, &s);
	wallet += qty * current_price[max_quantity];
	actions_own[max_quantity] -= qty;

	happy -= 5;
	crazy += 1;
      }
      else if (objectif == STANDBY)
      {
	happy -= 5;
	crazy += 5;
      }
      else if (objectif == RANDOM)
      {
	happy += 1;
	crazy += 10;

	if (rand() % 2 == 1)
	{
	  int r = rand() % 6;
	  std::string id = cpy[r];
	  int qty = rand() % actions_own[r];

	  std::string res = buy(id, qty, &s);
	  if (res.compare("ok"))
	  {
	    wallet += qty * current_price[r];
	    actions_own[r] -= qty;
	  }
	  else
	    happy -= 5;
	}
	else
	{
	  int r = rand() % 6;
	  std::string id = cpy[r];
	  int qty = rand() % actions_own[r];

	  sell(id, qty, &s);
	  wallet += qty * current_price[r];
	  actions_own[r] -= qty;
	}
      }

      if (old_wallet < wallet)
	happy += 5;

      if (happy == 0)
      {
	status = SAD;
	objectif = STANDBY;
	happy = rand() % 100 == 50 ? 50 : 0;
	crazy = 0;
      }
      else if (crazy == 0)
      {
	status = SAD;
	objectif = STOCK;
	crazy += rand() % 2 == 1 ? 10 : 0;
      }
      if (happy > crazy)
      {
	status = HAPPY;
	objectif = (rand() % 2 == 0) ? BUY : SELL;
	crazy = (happy == 4 * crazy) ? 4 * crazy : crazy;
      }
      else if (crazy > happy)
      {
	status = CRAZY;
	objectif = RANDOM;
	crazy -= rand() % 4 == 2 ? 2 : 1;
      }

      std::string filename = std::string("src/market/market_site/agent") +
	name + std::string(".info");
      std::ofstream log(filename);
      log << "> Agent status = " << getStatus() << std::endl;
      log << "> Agent objectif = " << getObjectif() << std::endl;
      log << "> Currents actions quantity:" << std::endl;
      log << " > TC = " << actions_own[0] << std::endl;
      log << " > TI = " << actions_own[1] << std::endl;
      log << " > MM = " << actions_own[2] << std::endl;
      log << " > TE = " << actions_own[3] << std::endl;
      log << " > BI = " << actions_own[4] << std::endl;
      log << "> Wallet = " << wallet << "$" <<std::endl;
      log.close();
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

std::string Banker::getObjectif()
{
  if (objectif == STOCK)
    return "Stock";
  else if (objectif == SELL)
    return "Sell";
  else if (objectif == BUY)
    return "Buy";
  else if (objectif == STANDBY)
    return "Standby";
  else if (objectif == RANDOM)
    return "Random";
  return "Unknown";
}

std::string Banker::getStatus()
{
  if (status == HAPPY)
    return "Happy";
  else if (status == SAD)
    return "Sad";
  else if (status == CRAZY)
    return "Crazy";
  return "Unknown";
}
