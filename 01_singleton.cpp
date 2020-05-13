#include <iostream>

#define CPP03 0

class Singleton {
 public:
  static Singleton &getInstance() {
    static Singleton instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
  }
 private:
  Singleton() = default;                    // Constructor? (the {} brackets) are needed here.

#if CPP03
  // C++ 03
    // ========
    // Don't forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    Singleton(Singleton const &);              // Don't Implement
    void operator=(Singleton const &); // Don't implement
#else
  // C++ 11
  // =======
  // We can use the better technique of deleting the methods
  // we don't want.
 public:
  // Remove copy
  Singleton(Singleton const &) = delete;
  void operator=(Singleton const &) = delete;

  // Remove move
  Singleton(Singleton  &&) = delete;
  void operator=(Singleton &&) = delete;
#endif

  // Note: Scott Meyers mentions in his Effective Modern
  //       C++ book, that deleted functions should generally
  //       be public as it results in better error messages
  //       due to the compilers behavior to check accessibility
  //       before deleted status
};

int main() {
  Singleton &instance = Singleton::getInstance();

  // See the errors
  Singleton singleton;
  singleton = instance;
  singleton = std::move(instance);

  return 0;
}