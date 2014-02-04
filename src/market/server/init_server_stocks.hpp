#ifndef INIT_SERVER_STOCKS_HPP
# define INIT_SERVER_STOCKS_HPP

# include <random>
# include <iostream>
# include <fstream>

namespace http
{
  namespace server3
  {
    class ServerStocks
    {
    private:
      const int refresh_size;
      std::vector<std::vector<double> > stock;

    public:
      ServerStocks(void) : refresh_size (30)
      {
	stock.resize(5);
	stock[0].resize(refresh_size);
	stock[1].resize(refresh_size);
	stock[2].resize(refresh_size);
	stock[3].resize(refresh_size);
	stock[4].resize(refresh_size);
      };
      ~ServerStocks(void){};

    public:
      void init(void);
    };
  }
}

#endif
