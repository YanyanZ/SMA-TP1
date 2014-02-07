# include <cstdlib>
# include <iostream>
# include <thread>
# include <fstream>
# include <utility>

# include <boost/asio.hpp>
# include <boost/algorithm/string.hpp>

# include "Server.hpp"

using boost::asio::ip::tcp;

int get_cotation(std::string name)
{
  boost::trim(name);

  if (name.compare("TC") == 0)
    return (*stocks)[0][(*stocks)[0].size() - 1].first;
  if (name.compare("TI") == 0)
    return (*stocks)[1][(*stocks)[1].size() - 1].first;
  if (name.compare("MM") == 0)
    return (*stocks)[2][(*stocks)[2].size() - 1].first;
  if (name.compare("TE") == 0)
    return (*stocks)[3][(*stocks)[3].size() - 1].first;
  if (name.compare("BI") == 0)
    return (*stocks)[4][(*stocks)[4].size() - 1].first;

  return 0;
}

int get_quantity(std::string name)
{
  boost::trim(name);

  if (name.compare("TC") == 0)
    return (*stocks)[0][(*stocks)[0].size() - 1].second;
  if (name.compare("TI") == 0)
    return (*stocks)[1][(*stocks)[1].size() - 1].second;
  if (name.compare("MM") == 0)
    return (*stocks)[2][(*stocks)[2].size() - 1].second;
  if (name.compare("TE") == 0)
    return (*stocks)[3][(*stocks)[3].size() - 1].second;
  if (name.compare("BI") == 0)
    return (*stocks)[4][(*stocks)[4].size() - 1].second;

  return 0;
}

bool sellprocess(std::string name, int quantity)
{
  boost::trim(name);

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

  mut.lock();
  (*stocks)[i].push_back(std::make_pair(
			(*stocks)[i][(*stocks)[i].size() - 1].first - 1,
			(*stocks)[i][(*stocks)[i].size() - 1].second + quantity));

  if ((*stocks)[i][(*stocks)[i].size() - 1].first <= 1)
    (*stocks)[i][(*stocks)[i].size() - 1].first = 1;
  mut.unlock();

  return true;
}

bool buyprocess(std::string name, int quantity)
{
  boost::trim(name);

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

  bool out = true;
  mut.lock();
  if ((*stocks)[i][(*stocks)[i].size() - 1].second - quantity > 0)
  {
    (*stocks)[i].push_back(std::make_pair(
			  (*stocks)[i][(*stocks)[i].size() - 1].first + 1,
			  (*stocks)[i][(*stocks)[i].size() - 1].second - quantity));
    if ((*stocks)[i][(*stocks)[i].size() - 1].second < 0)
      (*stocks)[i][(*stocks)[i].size() - 1].second = 0;
  }
  else
    out = false;
  mut.unlock();

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

      if (logmcpt > 30)
      {
	mut.lock();
	logmcpt = 0;
	logm.close();
	logm.open("../market_site/market.action");
	mut.unlock();
      }
      logmcpt++;

      if ((*stocks)[0].size() >= 7)
      {
	mut.lock();
	logtc.open("../market_site/tc.stock");
	std::stringstream ss;
	for (int i = 0; i < 7; i++)
	  ss << (*stocks)[0][i].first << " " <<  (*stocks)[0][i].second << std::endl;

	logtc << ss.str();
	logtc.close();
	(*stocks)[0].clear();
	mut.unlock();
      }

      if ((*stocks)[1].size() >= 7)
      {
	mut.lock();
	logtc.open("../market_site/ti.stock");
	std::stringstream ss;
	for (int i = 0; i < 7; i++)
	  ss << (*stocks)[1][i].first << " " <<  (*stocks)[1][i].second << std::endl;

	logtc << ss.str();
	logtc.close();
	(*stocks)[1].clear();
	mut.unlock();
      }

      if ((*stocks)[2].size() >= 7)
      {
	mut.lock();
	logtc.open("../market_site/mm.stock");
	std::stringstream ss;
	for (int i = 0; i < 7; i++)
	  ss << (*stocks)[2][i].first << " " <<  (*stocks)[2][i].second << std::endl;

	logtc << ss.str();
	logtc.close();
	(*stocks)[2].clear();
	mut.unlock();
      }

      if ((*stocks)[3].size() >= 7)
      {
	mut.lock();
	logtc.open("../market_site/te.stock");
	std::stringstream ss;
	for (int i = 0; i < 7; i++)
	  ss << (*stocks)[3][i].first << " " <<  (*stocks)[3][i].second << std::endl;

	logtc << ss.str();
	logtc.close();
	(*stocks)[3].clear();
	mut.unlock();
      }

      if ((*stocks)[4].size() >= 7)
      {
	mut.lock();
	logtc.open("../market_site/bi.stock");
	std::stringstream ss;
	for (int i = 0; i < 7; i++)
	  ss << (*stocks)[4][i].first << " " <<  (*stocks)[4][i].second << std::endl;

	logtc << ss.str();
	logtc.close();
	(*stocks)[4].clear();
	mut.unlock();
      }

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
	ss << data[0] << ((i == 4) ? " failed to " : " successed to ");
	ss << "buy " << quantity << " of " << stock_name << std::endl;

	mut.lock();
	logm << ss.str();
	logm.flush();
	mut.unlock();

	for (; i < length; i++)
	  data[i] = ' ';
      }
      else if (req[0] == 'S') // Sell action
      {
	int quantity = boost::lexical_cast<int>((req.substr(1, req.find("_") - 1)));

	std::string stock_name = req.substr(req.find("_") + 1);
	sellprocess(stock_name, quantity);

	data[0] = 'o';
	data[1] = 'k';

	std::stringstream ss;
	ss << data[0] << " successed to ";
	ss << "sell " << quantity << " of " << stock_name << std::endl;

	mut.lock();
	logm << ss.str();
	logm.flush();
	mut.unlock();

	for (int i = 2; i < length; i++)
	  data[i] = ' ';
      }
      else if (req[0] == 'G') // Get action
      {
	std::string stock_name = req.substr(2) + std::string("\0");
	if (req[1] == 'P') // Get Price
	{
	  int price = get_cotation(stock_name);
	  std::stringstream cv;
	  cv << price;
	  std::string sp = cv.str();

	  for (int i = 0; i < sp.size(); i++)
	    data[i] = sp[i];
	  for (int i = sp.size(); i < length; i++)
	    data[i] = ' ';

	  std::stringstream ss;
	  ss <<  data[0] << " request " << stock_name << "price ";
	  ss << "(" << price << "$)" << std::endl;

	  mut.lock();
	  logm << ss.str();
	  logm.flush();
	  mut.unlock();
	}
	else if (req[1] == 'Q') // Get quantity
	{
	  int quantity = get_cotation(stock_name);
	  std::stringstream cv;
	  cv << quantity;
	  std::string qt = cv.str();

	  for (int i = 0; i < qt.size(); i++)
	    data[i] = qt[i];
	  for (int i = qt.size(); i < length; i++)
	    data[i] = ' ';

	  std::stringstream ss;
	  ss << data[0] << " request " << stock_name << "quantity ";
	  ss << "(" << quantity << ")" << std::endl;

	  mut.lock();
	  logm << ss.str();
	  logm.flush();
	  mut.unlock();
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
  stocks = new std::vector<std::vector<std::pair<int, int> > >();
  stocks->resize(5);

  logm.open("../market_site/market.action");

  srand(time(NULL));
  for (unsigned int i = 0; i < stocks->size(); i++)
    (*stocks)[i].push_back(std::make_pair(rand() % 500 + 2000, rand() % 10000 + 100000));

  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    tcp::socket sock(io_service);
    a.accept(sock);
    std::thread(session, std::move(sock)).detach();
  }

  logm.close();
  logtc.close();
  logti.close();
  logmm.close();
  logte.close();
  logbi.close();
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
