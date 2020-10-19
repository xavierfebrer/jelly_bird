#ifndef VEC_4_H
#define VEC_4_H

#include <cmath>

template<typename T = double>
class Vec4 {
public:
    T x;
    T y;
    T z;
    T w;

    Vec4();

    Vec4(T xValue, T yValue, T zValue, T wValue);

    Vec4(const Vec4 & v);

    Vec4(const Vec4 * v);

    ~Vec4();

    void Set(T xValue, T yValue, T zValue, T wValue);

    T Length() const;

    T LengthSquared() const;

    T Distance(const Vec4 & v) const;

    T DistanceSquared(const Vec4 & v) const;

    Vec4 & Normalize();

    //ASSINGMENT AND EQUALITY OPERATIONS
    inline Vec4 & operator=(const Vec4 & v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    inline Vec4 & operator=(const T & f) {
        x = f;
        y = f;
        z = f;
        w = f;
        return *this;
    }

    inline Vec4 & operator-() {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
        return *this;
    }

    inline bool operator==(const Vec4 & v) const {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }

    inline bool operator!=(const Vec4 & v) const {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }

    //Vec4 TO Vec4 OPERATIONS
    inline const Vec4 operator+(const Vec4 & v) const {
        return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    inline const Vec4 operator-(const Vec4 & v) const {
        return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    inline const Vec4 operator*(const Vec4 & v) const {
        return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    inline const Vec4 operator/(const Vec4 & v) const {
        return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    //Vec4 TO THIS OPERATIONS
    inline Vec4 & operator+=(const Vec4 & v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    inline Vec4 & operator-=(const Vec4 & v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    inline Vec4 & operator*=(const Vec4 & v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    inline Vec4 & operator/=(const Vec4 & v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    //SCALER TO Vec4 OPERATIONS
    inline const Vec4 operator+(T v) const { return Vec4(x + v, y + v, z + v, w + v); }

    inline const Vec4 operator-(T v) const { return Vec4(x - v, y - v, z - v, w - v); }

    inline const Vec4 operator*(T v) const { return Vec4(x * v, y * v, z * v, w * v); }

    inline const Vec4 operator/(T v) const { return Vec4(x / v, y / v, z / v, w / v); }

    //SCALER TO THIS OPERATIONS
    inline Vec4 & operator+=(T v) {
        x += v;
        y += v;
        z += v;
        w += v;
        return *this;
    }

    inline Vec4 & operator-=(T v) {
        x -= v;
        y -= v;
        z -= v;
        w -= v;
        return *this;
    }

    inline Vec4 & operator*=(T v) {
        x *= v;
        y *= v;
        z *= v;
        w *= v;
        return *this;
    }

    inline Vec4 & operator/=(T v) {
        x /= v;
        y /= v;
        z /= v;
        w /= v;
        return *this;
    }
};

template<typename T>
Vec4<T>::Vec4() {}

template<typename T>
Vec4<T>::Vec4(T xValue, T yValue, T zValue, T wValue) : x(xValue), y(yValue), z(zValue),
                                                        w(wValue) {}

template<typename T>
Vec4<T>::Vec4(const Vec4 & v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

template<typename T>
Vec4<T>::Vec4(const Vec4 * v) : x(v->x), y(v->y), z(v->z), w(v->w) {}

template<typename T>
Vec4<T>::~Vec4() {}

template<typename T>
void Vec4<T>::Set(T xValue, T yValue, T zValue, T wValue) {
    x = xValue;
    y = yValue;
    z = zValue;
    w = wValue;
}

template<typename T>
T Vec4<T>::Length() const { return sqrt(x * x + y * y + z * z + w * w); }

template<typename T>
T Vec4<T>::LengthSquared() const { return x * x + y * y + z * z + w * w; }

template<typename T>
T Vec4<T>::Distance(const Vec4 & v) const {
    return sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)) + ((z - v.z) * (z - v.z)) +
                ((w - v.w) * (w - v.w)));
}

template<typename T>
T Vec4<T>::DistanceSquared(const Vec4 & v) const {
    return ((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)) + ((z - v.z) * (z - v.z)) +
           ((w - v.w) * (w - v.w));
}

template<typename T>
Vec4<T> & Vec4<T>::Normalize() {
    if(Length() != 0) {
        T length = LengthSquared();
        x /= length;
        y /= length;
        z /= length;
        w /= length;
        return *this;
    }
    x = y = z = w = 0;
    return *this;
}

#endif