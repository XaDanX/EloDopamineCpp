#pragma once
#include <cmath>

struct Vector2 {
    Vector2() = default;
    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    }

    float x{};
    float y{};

    [[nodiscard]] float length() const {
        return static_cast<float>(sqrt(x*x + y * y));
    }

    [[nodiscard]] float distance(const Vector2& o) const {
        return static_cast<float>(sqrt(pow(x - o.x, 2) + pow(y - o.y, 2)));
    }

    [[nodiscard]] Vector2 vscale(const Vector2& s) const {
        return {x*s.x, y*s.y};
    }

    [[nodiscard]] Vector2 scale(float s) const {
        return {x*s, y*s};
    }

    [[nodiscard]] Vector2 normalize() const {
        float l = length();
        return {x / l, y / l};
    }

    [[nodiscard]] Vector2 add(const Vector2& o) const {
        return {x + o.x, y + o.y};
    }

    [[nodiscard]] Vector2 sub(const Vector2& o) const {
        return {x - o.x, y - o.y};
    }

    [[nodiscard]] Vector2 clone() const {
        return {x, y};
    }
};

struct Vector3 {
    Vector3() = default;;
    Vector3(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    float x{};
    float y{};
    float z{};

    [[nodiscard]] float length() const {
        return sqrt(x*x + y*y + z*z);
    }

    [[nodiscard]] float distance(const Vector3& o) const {
        return static_cast<float>(sqrt(pow(x - o.x, 2) + pow(y - o.y, 2) + pow(z - o.z, 2)));
    }

    [[nodiscard]] Vector3 rotate_x(float angle) const {
        return {
                x,
                y * cos(angle) - z * sin(angle),
                y * sin(angle) + z * cos(angle)
        };
    }

    [[nodiscard]] Vector3 rotate_y(float angle) const {
        return {
                x * cos(angle) + z * sin(angle),
                y,
                -x * sin(angle) + z * cos(angle)
        };
    }

    [[nodiscard]] Vector3 rotate_z(float angle) const {
        return {
                x * cos(angle) - y * sin(angle),
                x * sin(angle) + y * cos(angle),
                z
        };
    }

    [[nodiscard]] Vector3 vscale(const Vector3& s) const {
        return {x*s.x, y*s.y, z*s.z};
    }

    [[nodiscard]] Vector3 scale(float s) const {
        return {x*s, y*s, z*s};
    }

    [[nodiscard]] Vector3 normalize() const {
        float l = length();
        return {x / l, y / l, z / l};
    }

    [[nodiscard]] Vector3 add(const Vector3& o) const {
        return {x + o.x, y + o.y, z + o.z};
    }

    [[nodiscard]] Vector3 sub(const Vector3& o) const {
        return {x - o.x, y - o.y, z - o.z};
    }
    [[nodiscard]] Vector3 mult(const float multip) const {
        return {x * multip, y * multip, z * multip};
    }

    [[nodiscard]] Vector3 clone() const {
        return {x, y, z};
    }
};

struct Vector4 {
    Vector4() = default;;
    Vector4(float _x, float _y, float _z, float _w) {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    float x{};
    float y{};
    float z{};
    float w{};

    [[nodiscard]] float length() const {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    [[nodiscard]] float distance(const Vector4& o) const {
        return static_cast<float>(sqrt(pow(x - o.x, 2) + pow(y - o.y, 2) + pow(z - o.z, 2) + pow(w - o.w, 2)));
    }

    [[nodiscard]] Vector4 vscale(const Vector4& s) const {
        return {x*s.x, y*s.y, z*s.z, w*s.w};
    }

    [[nodiscard]] Vector4 scale(float s) const {
        return {x*s, y*s, z*s, w*s};
    }

    [[nodiscard]] Vector4 normalize() const {
        float l = length();
        return {x / l, y / l, z / l, w / l};
    }

    [[nodiscard]] Vector4 add(const Vector4& o) const {
        return {x + o.x, y + o.y, z + o.z, w + o.w};
    }

    [[nodiscard]] Vector4 sub(const Vector4& o) const {
        return {x - o.x, y - o.y, z - o.z, w - o.w};
    }

    [[nodiscard]] Vector4 clone() const {
        return {x, y, z, w};
    }
};