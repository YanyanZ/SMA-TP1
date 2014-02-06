# include "Dummy.hpp"

using boost::asio::ip::tcp;

void Dummy::run()
{
  try
  {
    std::string ip = "127.0.0.1";
    std::string port = "4242";

    boost::asio::io_service io_service;

    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    boost::asio::connect(s, resolver.resolve({ip.c_str(), port.c_str()}));

    for (int i = 0; i < 20; i++)
    {
      char request[max_length] = "1#S100_TC";

      size_t request_length = std::strlen(request);
      boost::asio::write(s, boost::asio::buffer(request, request_length));

      char reply[max_length];
      size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_length));

      std::cout << reply << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}
