//
// Created by michal on 27.01.25.
//

#ifndef RGB_H
#define RGB_H

struct RGB {
  int r;
  int g;
  int b;

  RGB& operator=(const RGB& other) {
    if (this != &other) { // Sprawdzenie samoprzypisania
      r = other.r;
      g = other.g;
      b = other.b;
    }
    return *this;
  }
};


#endif //RGB_H
