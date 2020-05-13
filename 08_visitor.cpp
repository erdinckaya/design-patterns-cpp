#define BEFORE 0
#include <iostream>

using namespace std;

#if BEFORE
class Color {
 public:
  virtual void count() = 0;
  virtual void call() = 0;
  static void report_num() {
    cout << "Reds " << s_num_red << ", Blus " << s_num_blu << '\n';
  }
 protected:
  static int s_num_red, s_num_blu;
};
int Color::s_num_red = 0;
int Color::s_num_blu = 0;

class Red : public Color {
 public:
  void count() override {
    ++s_num_red;
  }
  void call() override {
    eye();
  }
  static void eye() {
    cout << "Red::eye\n";
  }
};

class Blu : public Color {
 public:
  void count() override {
    ++s_num_blu;
  }
  void call() override {
    sky();
  }
  static void sky() {
    cout << "Blu::sky\n";
  }
};

int main() {
  Color *set[] =
      {
          new Red, new Blu, new Blu, new Red, new Red, 0
      };
  for (int i = 0; set[i]; ++i) {
    set[i]->count();
    set[i]->call();
  }
  Color::report_num();
}
#else
class Color {
 public:
  virtual void accept(class Visitor *) = 0;
};

class Red : public Color {
 public:
  void accept(Visitor *) override;
  void eye() {
    cout << "Red::eye\n";
  }
};
class Blu : public Color {
 public:
  void accept(Visitor *) override;
  void sky() {
    cout << "Blu::sky\n";
  }
};

class Visitor {
 public:
  virtual void visit(Red *) = 0;
  virtual void visit(Blu *) = 0;
};

class CountVisitor : public Visitor {
 public:
  CountVisitor() {
    m_num_red = m_num_blu = 0;
  }
  void visit(Red *) override {
    ++m_num_red;
  }
  void visit(Blu *) override {
    ++m_num_blu;
  }
  void report_num() const {
    cout << "Reds " << m_num_red << ", Blus " << m_num_blu << '\n';
  }
 private:
  int m_num_red, m_num_blu;
};

class CallVisitor : public Visitor {
 public:
  void visit(Red *r) override {
    r->eye();
  }
  void visit(Blu *b) override {
    b->sky();
  }
};

void Red::accept(Visitor *v) {
  v->visit(this);
}

void Blu::accept(Visitor *v) {
  v->visit(this);
}

int main() {
  Color *set[] =
      {
          new Red, new Blu, new Blu, new Red, new Red, nullptr
      };
  CountVisitor count_operation;
  CallVisitor call_operation;
  for (int i = 0; set[i]; i++) {
    set[i]->accept(&count_operation);
    set[i]->accept(&call_operation);
  }
  count_operation.report_num();
}
#endif
