#include <cstdlib>
#include <iostream>
#include <thread>
# include <fstream>
#include <utility>

#include <boost/asio.hpp>

# include "Server.hpp"

using boost::asio::ip::tcp;

int get_cotation(std::string name)
{
  if (name.compare("TC") == 0)
    return stocks[0][stocks[0].size() - 1].first;
  if (name.compare("TI") == 0)
    return stocks[1][stocks[1].size() - 1].first;
  if (name.compare("MM") == 0)
    return stocks[2][stocks[2].size() - 1].first;
  if (name.compare("TE") == 0)
    return stocks[3][stocks[3].size() - 1].first;
  if (name.compare("BI") == 0)
    return stocks[4][stocks[4].size() - 1].first;
  return -1;
}

int get_quantity(std::string name)
{
  if (name.compare("TC") == 0)
    return stocks[0][stocks[0].size() - 1].second;
  if (name.compare("TI") == 0)
    return stocks[1][stocks[1].size() - 1].second;
  if (name.compare("MM") == 0)
    return stocks[2][stocks[2].size() - 1].second;
  if (name.compare("TE") == 0)
    return stocks[3][stocks[3].size() - 1].second;
  if (name.compare("BI") == 0)
    return stocks[4][stocks[4].size() - 1].second;
  return -9999;
}

bool sellprocess(std::string name, int quantity)
{
  int i = 0;
  if (name.compare("TC") == 0)
    i = 0;
  if (name.compare("TI") == 0)
    i = 1;
  if (name.compare("MM") == 0)
    i = 2;
  if (name.compare("TE") == 0)
    i = 3;
  if (name.compare("BI") == 0)
    i = 4;

  std::mutex m;
  m.lock();
  stocks[i][stocks[i].size() - 1].second += quantity;
  stocks[i][stocks[i].size() - 1].first -= (quantity / 100);
  if (stocks[i][stocks[i].size() - 1].first <= 1)
    stocks[i][stocks[i].size() - 1].first = 1;
  m.unlock();

  return true;
}

bool buyprocess(std::string name, int quantity)
{
    int i = 0;
  if (name.compare("TC") == 0)
    i = 0;
  if (name.compare("TI") == 0)
    i = 1;
  if (name.compare("MM") == 0)
    i = 2;
  if (name.compare("TE") == 0)
    i = 3;
  if (name.compare("BI") == 0)
    i = 4;

  std::mutex m;
  bool out = true;
  m.lock();
  if (stocks[i][stocks[i].size() - 1].second - quantity > 0)
  {
    stocks[i][stocks[i].size() - 1].second -= quantity;
    stocks[i][stocks[i].size() - 1].first += (quantity / 100);
  }
  else
    out = false;
  m.unlock();

  return out;
}

const int max_length = 1024;

void session(tcp::socket sock)
{
  try
  {
    for (;;)
    {
      char data[max_length];
      char out[max_length];
      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::string tmp(data);
      std::string req = tmp.substr(tmp.find("#") + 1);

      if (req[0] == 'B')  // Buy action
      {
	int quantity = boost::lexical_cast<int>((req.substr(1, req.find("_") - 1)));

	std::string stock_name = req.substr(req.find("_") + 1);
	int i = 2;
	if (buyprocess(stock_name, quantity) == true)
	{
	  data[0] = 'o';
	  data[1] = 'k';
	}
	else
	{
	  data[0] = 'f';
	  data[1] = 'a';
	  data[2] = 'i';
	  data[3] = 'l';
	  i = 4;
	}

	std::stringstream ss;
	ss << "Agent " << tmp.substr(0, 1);
	ss << (i == 2 ? " successed " : " failed ") << "to buy ";
	ss << quantity << " of " << stock_name;
	logAction.push_back(ss.str());

	for (; i < length; i++)
	  data[i] = ' ';
      }
      else if (req[0] == 'S') // Sell action
      {
	int quantity = boost::lexical_cast<int>((req.substr(1, req.find("_") - 1)));

	std::string stock_name = req.substr(req.find("_") + 1);
	//std::cout << " > Sell " << quantity << " of " << stock_name << std::endl;

	sellprocess(stock_name, quantity);

	std::stringstream ss;
	ss << "Agent " << tmp.substr(0, 1);
	ss << " successed " << "to sell ";
	ss << quantity << " of " << stock_name;
	logAction.push_back(ss.str());

	data[0] = 'o';
	data[1] = 'k';
	for (int i = 2; i < length; i++)
	  data[i] = ' ';
      }
      else if (req[0] == 'G') // Get action
      {
	std::string stock_name = req.substr(2);
	if (req[1] == 'P') // Get Price
	{
	  int price = get_cotation(stock_name);
	  std::stringstream cv;
	  cv << price;
	  std::string sp = cv.str();

	  for (int i = 0; i < sp.length(); i++)
	    data[i] = sp[i];
	  for (int i = sp.length(); i < length; i++)
	    data[i] = ' ';

	  std::stringstream ss;
	  ss << "Agent " << tmp.substr(0, 1);
	  ss << " ask the price of ";
	  ss << stock_name << " (" << sp << "$)";
	  logAction.push_back(ss.str());
	}
	else if (req[1] == 'Q') // Get quantity
	{
	  int quantity = get_cotation(stock_name);
	  std::stringstream cv;
	  cv << quantity;
	  std::string qt = cv.str();

	  for (int i = 0; i < qt.length(); i++)
	    data[i] = qt[i];
	  for (int i = qt.length(); i < length; i++)
	    data[i] = ' ';

	  std::stringstream ss;
	  ss << "Agent " << tmp.substr(0, 1);
	  ss << " ask the quantity of ";
	  ss << stock_name << " (" << qt << ")";
	  logAction.push_back(ss.str());
	}
      }

      boost::asio::write(sock, boost::asio::buffer(data, length));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
  stocks.resize(5);
  srand(time(NULL));
  for (unsigned int i = 0; i < stocks.size(); i++)
    stocks[i].push_back(std::make_pair(rand() % 500, rand() % 100000 + 1000));

  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    tcp::socket sock(io_service);
    a.accept(sock);
    std::thread(session, std::move(sock)).detach();

    mut.lock();
    if (logAction.size() >= 10)
    {
      std::ofstream file("../market_site/market.action");

      for (std::string s : logAction)
	file << s << std::endl;

      logAction.clear();
      file.close();
    }

    if ((stocks[0].size() >= 7) ||
	(stocks[1].size() >= 7) ||
	(stocks[2].size() >= 7) ||
	(stocks[3].size() >= 7) ||
	(stocks[4].size() >= 7))
    {
      std::ofstream tc("../market_site/tc.stock");
      std::ofstream ti("../market_site/ti.stock");
      std::ofstream mm("../market_site/mm.stock");
      std::ofstream te("../market_site/te.stock");
      std::ofstream bi("../market_site/bi.stock");

      for (int i = stocks[0].size() - 1; i > stocks[0].size() - 8;
	   i--)
	tc << stocks[0][i].second << std::endl;

      for (int i = stocks[1].size() - 1; i > stocks[1].size() - 8;
	   i--)
	ti << stocks[1][i].second << std::endl;

      for (int i = stocks[2].size() - 1; i > stocks[2].size() - 8;
	   i--)
	mm << stocks[2][i].second << std::endl;

      for (int i = stocks[3].size() - 1; i > stocks[3].size() - 8;
	   i--)
	te << stocks[3][i].second << std::endl;

      for (int i = stocks[4].size() - 1; i > stocks[4].size() - 8;
	   i--)
	bi << stocks[4][i].second << std::endl;

      stocks[0].clear();
      stocks[1].clear();
      stocks[2].clear();
      stocks[3].clear();
      stocks[4].clear();
      tc.close();
      ti.close();
      mm.close();
      te.close();
      bi.close();
    }
    mut.unlock();
  }
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server(io_service, std::atoi(argv[1]));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
