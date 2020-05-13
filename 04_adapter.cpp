#include <iostream>
// General purpose is that you have class but you want to change some of the features of it.
// Adapter pattern wraps the old class with interface which has the member functions that you want to change
// Inside of the new function calls new staffs and old staffs together.


using namespace std;

typedef int Coordinate;
typedef int Dimension;

// Desired interface
class Rectangle {
 public:
  virtual void draw() = 0;
};

// Legacy component
class LegacyRectangle {
 public:
  LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2) {
    x1_ = x1;
    y1_ = y1;
    x2_ = x2;
    y2_ = y2;
    cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
         << x2_ << "," << y2_ << ")" << endl;
  }
  void oldDraw() const {
    cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ <<
         ") => (" << x2_ << "," << y2_ << ")" << endl;
  }
 private:
  Coordinate x1_;
  Coordinate y1_;
  Coordinate x2_;
  Coordinate y2_;
};

// Adapter wrapper
class RectangleAdapter : public Rectangle, private LegacyRectangle {
 public:
  RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h) :
      LegacyRectangle(x, y, x + w, y + h) {
    cout << "RectangleAdapter: create.  (" << x << "," << y <<
         "), width = " << w << ", height = " << h << endl;
  }
  void draw() override {
    cout << "RectangleAdapter: draw." << endl;
    oldDraw();
  }
};

int main() {
  Rectangle *r = new RectangleAdapter(120, 200, 60, 40);
  r->draw();
}