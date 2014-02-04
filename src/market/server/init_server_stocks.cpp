# include "init_server_stocks.hpp"

using namespace http::server3;

void ServerStocks::init(void)
{
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(50, 100);
  const std::vector<std::string> files =
    {"../market_site/stock1/stock1.txt",
     "../market_site/stock2/stock2.txt",
     "../market_site/stock3/stock3.txt",
     "../market_site/stock4/stock4.txt",
     "../market_site/stock5/stock5.txt"};

  for (unsigned int i = 0; i < stock.size(); i++)
    for (int j = 0; j < refresh_size; j++)
      stock[i][j] = distribution(generator);

  for (unsigned int i = 0; i < files.size(); i++)
  {
    std::ofstream out;
    out.open(files[i]);

    for (int j = 0; j < refresh_size; j++)
      out << stock[i][j] << std::endl;

    out.close();
  }
}
