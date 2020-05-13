#define BEFORE 1

#include <iostream>
#include <vector>

#if BEFORE
class Stooge {
 public:
  virtual void slap_stick() = 0;
  virtual ~Stooge() = default;
};

class Larry : public Stooge {
 public:
  void slap_stick() override {
    std::cout << "Larry: poke eyes\n";
  }
};
class Moe : public Stooge {
 public:
  void slap_stick() override {
    std::cout << "Moe: slap head\n";
  }
};
class Curly : public Stooge {
 public:
  void slap_stick() override {
    std::cout << "Curly: suffer abuse\n";
  }
};

int main() {
  std::vector<Stooge *> roles;
  int choice;

  while (true) {
    std::cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
    std::cin >> choice;
    if (choice == 0)
      break;
    else if (choice == 1)
      roles.push_back(new Larry);
    else if (choice == 2)
      roles.push_back(new Moe);
    else
      roles.push_back(new Curly);
  }
  for (auto &role : roles)
    role->slap_stick();
  for (auto &role : roles)
    delete role;
}
#else

class Stooge {
 public:
  // Factory Method
  static Stooge *make_stooge(int choice);
  virtual void slap_stick() = 0;
  virtual ~Stooge() = default;
};



class Larry : public Stooge {
 public:
  void slap_stick() override {
    std::cout << "Larry: poke eyes\n";
  }
};
class Moe : public Stooge {
 public:
  void slap_stick() override {
    std::cout << "Moe: slap head\n";
  }
};
class Curly : public Stooge {
 public:
  void slap_stick() override {
    std::cout << "Curly: suffer abuse\n";
  }
};

Stooge *Stooge::make_stooge(int choice) {
  if (choice == 1)
    return new Larry;
  else if (choice == 2)
    return new Moe;
  else
    return new Curly;
}

int main() {
  std::vector<Stooge *> roles;
  int choice;
  while (true) {
    std::cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
    std::cin >> choice;
    if (choice == 0)
      break;
    roles.push_back(Stooge::make_stooge(choice));
  }
  for (auto &role : roles)
    role->slap_stick();
  for (auto &role : roles)
    delete role;
}
#endif