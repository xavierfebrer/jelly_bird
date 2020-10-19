#ifndef VEC_3_H
#define VEC_3_H

#include <cmath>

template<typename T = double>
class Vec3 {
public:
    T x;
    T y;
    T z;

    Vec3();

    Vec3(T xValue, T yValue, T zValue);

    Vec3(const Vec3 & v);

    Vec3(const Vec3 * v);

    ~Vec3();

    void Set(T xValue, T yValue, T zValue);

    T Length() const;

    T LengthSquared() const;

    T Distance(const Vec3 & v) const;

    T DistanceSquared(const Vec3 & v) const;

    Vec3 & Normalize();

    //ASSINGMENT AND EQUALITY OPERATIONS
    inline Vec3 & operator=(const Vec3 & v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    inline Vec3 & operator=(const T & f) {
        x = f;
        y = f;
        z = f;
        return *this;
    }

    inline Vec3 & operator-() {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    inline bool operator==(const Vec3 & v) const { return (x == v.x) && (y == v.y) && (z == v.z); }

    inline bool operator!=(const Vec3 & v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

    //Vec3 TO Vec3 OPERATIONS
    inline const Vec3 operator+(const Vec3 & v) const { return Vec3(x + v.x, y + v.y, z + v.z); }

    inline const Vec3 operator-(const Vec3 & v) const { return Vec3(x - v.x, y - v.y, z - v.z); }

    inline const Vec3 operator*(const Vec3 & v) const { return Vec3(x * v.x, y * v.y, z * v.z); }

    inline const Vec3 operator/(const Vec3 & v) const { return Vec3(x / v.x, y / v.y, z / v.z); }

    //Vec3 TO THIS OPERATIONS
    inline Vec3 & operator+=(const Vec3 & v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vec3 & operator-=(const Vec3 & v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    inline Vec3 & operator*=(const Vec3 & v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    inline Vec3 & operator/=(const Vec3 & v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    //SCALER TO Vec3 OPERATIONS
    inline const Vec3 operator+(T v) const { return Vec3(x + v, y + v, z + v); }

    inline const Vec3 operator-(T v) const { return Vec3(x - v, y - v, z - v); }

    inline const Vec3 operator*(T v) const { return Vec3(x * v, y * v, z * v); }

    inline const Vec3 operator/(T v) const { return Vec3(x / v, y / v, z / v); }

    //SCALER TO THIS OPERATIONS
    inline Vec3 & operator+=(T v) {
        x += v;
        y += v;
        z += v;
        return *this;
    }

    inline Vec3 & operator-=(T v) {
        x -= v;
        y -= v;
        z -= v;
        return *this;
    }

    inline Vec3 & operator*=(T v) {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }

    inline Vec3 & operator/=(T v) {
        x /= v;
        y /= v;
        z /= v;
        return *this;
    }
};

template<typename T>
Vec3<T>::Vec3() {}

template<typename T>
Vec3<T>::Vec3(T xValue, T yValue, T zValue) : x(xValue), y(yValue), z(zValue) {}

template<typename T>
Vec3<T>::Vec3(const Vec3 & v) : x(v.x), y(v.y), z(v.z) {}

template<typename T>
Vec3<T>::Vec3(const Vec3 * v) : x(v->x), y(v->y), z(v->z) {}

template<typename T>
Vec3<T>::~Vec3() {}

template<typename T>
void Vec3<T>::Set(T xValue, T yValue, T zValue) {
    x = xValue;
    y = yValue;
    z = zValue;
}

template<typename T>
T Vec3<T>::Length() const { return sqrt(x * x + y * y + z * z); }

template<typename T>
T Vec3<T>::LengthSquared() const { return x * x + y * y + z * z; }

template<typename T>
T Vec3<T>::Distance(const Vec3 & v) const {
    return sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)) + ((z - v.z) * (z - v.z)));
}

template<typename T>
T Vec3<T>::DistanceSquared(const Vec3 & v) const {
    return ((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)) + ((z - v.z) * (z - v.z));
}

template<typename T>
Vec3<T> & Vec3<T>::Normalize() {
    if(Length() != 0) {
        T length = LengthSquared();
        x /= length;
        y /= length;
        z /= length;
        return *this;
    }
    x = y = z = 0;
    return *this;
}

#endif