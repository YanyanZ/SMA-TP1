#include "Agent.hpp"

Agent::Agent(std::string n, std::vector<int> start, int money)
  : name (n), actions_own (start), wallet (money)
{
}

Agent::~Agent(void)
{
}

int Agent::min(std::vector<int> v)
{
  int min_pos = 1;
  int tmp = actions_own[0];

  for (int i = 0; i < v.size(); i++)
    if (tmp > v[i])
    {
      tmp = v[i];
      min_pos = i;
    }

  return min_pos;
}

int Agent::max(std::vector<int> v)
{
  int max_pos = 1;
  int tmp = actions_own[0];

  for (int i = 0; i < v.size(); i++)
    if (tmp < v[i])
    {
      tmp = v[i];
      max_pos = i;
    }

  return max_pos;
}



int Agent::getCotation(std::string cn, tcp::socket* s)
{
  std::string gp = "#GP";
  std::string req = name + gp + cn;

  size_t request_length = req.size();
  boost::asio::write(*s, boost::asio::buffer(req.c_str(), request_length));

  char reply[max_length];
  size_t reply_length = boost::asio::read(*s, boost::asio::buffer(reply, request_length));

  char* tmp = (char*) malloc(10 * sizeof(char));
  int i = 0;

  while ((reply[i] >= '0') && (reply[i] <= '9') && (i < std::strlen(reply)))
  {
    tmp[i] = reply[i];
    i++;
  }
  tmp[i] = '\0';

  int value = boost::lexical_cast<int>(tmp);
  free(tmp);

  return value;
}

int Agent::getQuantity(std::string cn, tcp::socket* s)
{
  std::string gq = "#GQ";
  std::string req = name + gq + cn;

  size_t request_length = req.size();
  boost::asio::write(*s, boost::asio::buffer(req, request_length));

  char reply[max_length];
  size_t reply_length = boost::asio::read(*s, boost::asio::buffer(reply, request_length));

  char* tmp = (char*) malloc(10 * sizeof(char));
  int i = 0;
  while ((reply[i] >= '0') && (reply[i] <= '9') && (i < std::strlen(reply)))
  {
    tmp[i] = reply[i];
    i++;
  }
  tmp[i] = '\0';

  int value = boost::lexical_cast<int>(tmp);
  free(tmp);

  return value;
}

std::string Agent::sell(std::string cn, int quantity, tcp::socket* s)
{
  std::string tmp = boost::lexical_cast<std::string>(quantity);
  std::string req = name + std::string("#S") + tmp + std::string("_") + cn;

  size_t request_length = req.size();
  boost::asio::write(*s, boost::asio::buffer(req, request_length));

  char reply[max_length];
  size_t reply_length = boost::asio::read(*s, boost::asio::buffer(reply, request_length));

  return std::string(reply);
}

std::string Agent::buy(std::string cn, int quantity, tcp::socket* s)
{
  std::string tmp = boost::lexical_cast<std::string>(quantity);
  std::string req = name + std::string("#B") + tmp + std::string("_") + cn;

  size_t request_length = req.size();
  boost::asio::write(*s, boost::asio::buffer(req, request_length));

  char reply[max_length];
  size_t reply_length = boost::asio::read(*s, boost::asio::buffer(reply, request_length));

  return std::string(reply);
}
