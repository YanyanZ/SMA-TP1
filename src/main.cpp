# include <iostream>
# include <thread>

# include <boost/thread.hpp>
# include <boost/bind.hpp>

# include <agent/Agent.hpp>
# include <agent/Banker.hpp>

# include <threadpool.hpp>
# include <boost/lexical_cast.hpp>

int main(int argc, char* argv[])
{
  int nb_thread = 3; //boost::thread::hardware_concurrency();
  boost::threadpool::prio_pool worker_pool (nb_thread);

  std::cout << " > Will launch " << nb_thread<< " agents" << std::endl;
  std::cout << std::endl;
  std::cout << "############################################" << std::endl;
  std::cout << "> Init simulation" << std::endl;
  std::cout << "> Launch web UI" << std::endl;
  system("firefox src/market/market_site/index.html");
  std::cout << "> Create agents" << std::endl;
  for (int i = 0; i < nb_thread; i++)
  {
    std::stringstream ss;
    ss << i;

    Banker agent = Banker(ss.str(),
			 {rand() % 10000 + 5000, rand() % 10000 + 5000, rand() % 10000 + 5000},
			 rand() % 50000 + 10000);
    worker_pool.schedule (boost::threadpool::prio_task_func (1, boost::bind(&Banker::run, agent)));
    std::cout << " > Agent at work" << std::endl;
  }
  worker_pool.wait();

  return 0;
}
