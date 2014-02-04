#ifndef WALLET_HPP
# define WALLET_HPP

# include <vector>

class Wallet
{
public:
  int value;
  std::vector<Action>* actions;
};

#endif
