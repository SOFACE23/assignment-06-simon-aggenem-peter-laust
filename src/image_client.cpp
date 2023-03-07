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
#include <fstream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

//Image size found by inspecting image.
constexpr size_t image_size = 17618;

void save_image(char* data, size_t len)
{
  //Create a steam to write the file to.
  std::ofstream filetoWrite;

  //We're gonna write to a file called copycat.jpg
  //It's most likely not there and will be created.
  filetoWrite.open("copycat.jpg");

  for (int i = 0; i < image_size; i++){
    //The data char array contains the whole image so we can just loop over it and add it to the file
    filetoWrite << data[i];
    }

  //Be a good boy and close the file again.
  filetoWrite.close();
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while(true)
    {
      boost::array<char, image_size> buf;
      boost::system::error_code error;

      // read until buffer is full
      boost::asio::read(socket,boost::asio::buffer(buf));

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      save_image(buf.data(),image_size);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}