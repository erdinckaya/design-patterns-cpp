#define BEFORE 0
#include <iostream>
#include <vector>

using namespace std;

#if BEFORE
class DivObserver {
  int m_div;
 public:
  explicit DivObserver(int div) {
    m_div = div;
  }
  void update(int val) const {
    cout << val << " div " << m_div << " is " << val / m_div << '\n';
  }
};

class ModObserver {
  int m_mod;
 public:
  explicit ModObserver(int mod) {
    m_mod = mod;
  }
  void update(int val) const {
    cout << val << " mod " << m_mod << " is " << val % m_mod << '\n';
  }
};

class Subject {
  int m_value{};
  DivObserver m_div_obj;
  ModObserver m_mod_obj;
 public:
  Subject() : m_div_obj(4), m_mod_obj(3) {}
  void set_value(int value) {
    m_value = value;
    notify();
  }
  void notify() {
    m_div_obj.update(m_value);
    m_mod_obj.update(m_value);
  }
};

int main() {
  Subject subj;
  subj.set_value(14);
}
#else

class Observer {
 public:
  virtual void update(int value) = 0;
};

class Subject {
  int m_value{};
  vector<Observer *> m_views;
 public:
  void attach(Observer *obs) {
    m_views.push_back(obs);
  }
  void set_val(int value) {
    m_value = value;
    notify();
  }
  void notify() {
    for (auto &m_view : m_views) {
      m_view->update(m_value);
    }
  }
};

class DivObserver : public Observer {
  int m_div;
 public:
  DivObserver(Subject *model, int div) {
    model->attach(this);
    m_div = div;
  }
  void update(int v) override {
    cout << v << " div " << m_div << " is " << v / m_div << '\n';
  }
};

class ModObserver : public Observer {
  int m_mod;
 public:
  ModObserver(Subject *model, int mod) {
    model->attach(this);
    m_mod = mod;
  }
  void update(int v) override {
    cout << v << " mod " << m_mod << " is " << v % m_mod << '\n';
  }
};

int main() {
  Subject subj;
  DivObserver divObs1(&subj, 4);
  DivObserver divObs2(&subj, 3);
  ModObserver modObs3(&subj, 3);
  subj.set_val(14);
}
#endif