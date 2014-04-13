#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#include <iostream>

namespace Example
{
  void scoped_ptr()
  {
    std::cout << "Example of boost::scoped_ptr :" << std::endl;

    boost::scoped_ptr<int> i(new int);
    std::cout << "1. " << *i << std::endl;
    // 1. garbage

    *i = 123;
    std::cout << "2. " << *i << std::endl;
    // 2. 123

    *i.get() = 789; // Note that it is not i->get() = ...
    std::cout << "3. " << *i << std::endl;
    // 3. 789

    i.reset(new int);
    std::cout << "4. " << *i << std::endl;
    // 4. garbage

    std::cout << "boost::scoped_ptr deletes itself when quitting scope" << std::endl;

    std::cout << std::endl;
  }

  void scoped_array()
  {
    std::cout << "Example of boost::scoped_array :" << std::endl;

    boost::scoped_array<int> i(new int[2]);
    std::cout << "1. " << i[0] << "," << i[1] << std::endl;
    // 1. garbage,garbage

    *i.get() = 123;
    std::cout << "2. " << i[0] << "," << i[1] << std::endl;
    // 2. 123,garbage

    i[1] = 789;
    std::cout << "3. " << i[0] << "," << i[1] << std::endl;
    // 3. 123,789

    i.reset(new int[3]);
    std::cout << "4. " << i[0] << "," << i[1] << "," << i[2] << std::endl;
    // 4. garbage,garbage,garbage

    std::cout << "boost::scoped_array deletes itself when quitting scope" << std::endl;

    std::cout << std::endl;
  }
}

int main()
{
  std::cout << "Note I'm not using delete (or free). Smart pointers do it for me." << std::endl;
  std::cout << std::endl;

  Example::scoped_ptr();

  Example::scoped_array();

  std::cout << "Now you can check memory leaks:" << std::endl;
  std::cout << "valgrind --tool=memcheck --quiet ./main" << std::endl;
  std::cout << "There shouldn't be any. :)" << std::endl;
}

