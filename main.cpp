#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
// #include <boost/shared_ptr.hpp> // It's in <memory> since C++11 as std::shared_ptr
#include <boost/shared_array.hpp>
//#include <boost/weak_ptr.hpp> // It's in <memory> since C++11 as std::weak_ptr
#include <boost/intrusive_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <memory>

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

  void shared_ptr()
  {
    std::cout << "Example of std::shared_ptr :" << std::endl;

    std::vector<std::shared_ptr<int> > v;
    v.push_back(std::shared_ptr<int>(new int(123)));
    v.push_back(std::shared_ptr<int>(new int(456)));
    std::cout << "1. " << *v[0] << "," << *v[1] << std::endl;
    // 1. 123,456

    std::shared_ptr<int> a(new int(111));
    std::shared_ptr<int> b(a);
    std::cout << "2. " << *a << "," << *b << std::endl;
    // 2. 111,111

    a.reset(new int(222));
    std::cout << "3. " << *a << "," << *b << std::endl;
    // 3. 222,111

    std::cout << std::endl;
  }

  void shared_array()
  {
    std::cout << "Example of boost::shared_array :" << std::endl;

    boost::shared_array<int> a(new int[2] {111, 222});
    std::cout << "1. " << a[0] << "," << a[1] << std::endl;
    // 1. 111,222

    boost::shared_array<int> b(a);
    std::cout << "2. " << b[0] << "," << b[1] << std::endl;
    // 2. 111,222
    
    b[0] = 999;
    std::cout << "3. a contains: " << a[0] << "," << a[1] << std::endl;
    std::cout << "   b contains: " << b[0] << "," << b[1] << std::endl;
    // 3. 111,222
    //    999,222

    std::cout << std::endl;
  }

  void weak_ptr()
  {
    std::cout << "Example of std::weak_ptr :" << std::endl;
    std::cout << "It's used to break circular references of shared_ptr." << std::endl;


    std::shared_ptr<int> a(new int(111));
    std::weak_ptr<int> weak(a);

    if (auto weak_lock = weak.lock())
    {
      std::cout << "1. reference still extists so I can use weak_lock pointer" << std::endl;
      std::cout << "   " << *a << "," << *weak_lock << std::endl;
      // 111,111
    }
    else
    {
      std::cout << "1. reference doesn't exist so I can't use weak_lock pointer" << std::endl;
    }


    std::weak_ptr<int> weak2(a);
    a.reset(new int(222)); // <-- This one line is critical for weak_ptr understanding ;)

    if (auto weak2_lock = weak2.lock())
    {
      std::cout << "2. reference still extists so I can use weak2_lock pointer" << std::endl;
    }
    else
    {
      std::cout << "2. reference doesn't exist so I can't use weak2_lock pointer" << std::endl;
      std::cout << "   " << *a << std::endl;
      // 222
    }


    std::cout << std::endl;
  }

  void intrusive_ptr()
  {
    //TODO
  }

  void ptr_vector()
  {
    //TODO
  }
}

int main()
{
  std::cout << "Note I'm not using delete (or free). Smart pointers do it for me." << std::endl;
  std::cout << std::endl;

  Example::scoped_ptr();

  Example::scoped_array();

  Example::shared_ptr();

  Example::shared_array();

  Example::weak_ptr();

  //Example::intrusive_ptr();

  //Example::ptr_vector();

  std::cout << "Now you can check memory leaks:" << std::endl;
  std::cout << "valgrind --tool=memcheck ./main" << std::endl;
  std::cout << "Everything is correct if there are exactly as many allocs as frees." << std::endl;
}

