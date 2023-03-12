//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    //Needs a server ip.
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    //Takes the host (server ip stored as an argument) and a port("daytime" corresponding to port 13).
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while(true)
    {
      //Array to store recieved data I.E. the date and time.
      boost::array<char, 128> buf;

      //Error handler.
      boost::system::error_code error;

      //read the data from the socket.
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      //If we recieve and end of file message it means the whole message was transmitted correctly
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      //Otherwise we need to return an error.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      //Write the daytime to the terminal.
      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}