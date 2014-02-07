#ifndef BANKER_HPP
# define BANKER_HPP

# include "Agent.hpp"

using boost::asio::ip::tcp;

class Banker : public Agent
{
  public:
  Banker(std::string n, std::vector<int> start, int money)
    : Agent(n, start, money)
  {
    happy = rand() % 50 + 20;
    crazy = 10;
  };
  virtual ~Banker(){};

public:
  virtual void run();

private:
  std::string getObjectif();
  std::string getStatus();
};

#endif
