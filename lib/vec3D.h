#ifndef vec3D_H
#define vec3D_H

#include <cmath>

struct vec3D {
    // Składowe wektora
    float x, y, z, w;

    // Konstruktory
    vec3D();                                    // Domyślny konstruktor
    vec3D(float x, float y, float z);  // Konstruktor z parametrami
    vec3D(float x, float y, float z, float w);  // Konstruktor z parametrami

    // Operatory arytmetyczne (const methods)
    vec3D operator+(const vec3D& v) const;
    vec3D operator+(float val) const;
    vec3D operator-(const vec3D& v) const;
    vec3D operator-(float val) const;
    vec3D operator*(const vec3D& v) const;
    vec3D operator*(float val) const;

    vec3D operator/(const vec3D& v) const;
    vec3D operator/(float val) const;

    // Operatory przypisania
    vec3D& operator+=(const vec3D& v);
    vec3D& operator+=(float val);
    vec3D& operator-=(const vec3D& v);
    vec3D& operator-=(float val);
    vec3D& operator*=(const vec3D& v);
    vec3D& operator*=(float val);
    vec3D& operator/=(const vec3D& v);
    vec3D& operator/=(float val);

    // Operator przypisania (kopiujący)
    vec3D& operator=(const vec3D& v);

    // Metody narzędziowe
    void normalize(); // Normalizacja wektora
};



#endif //vec3D_H
