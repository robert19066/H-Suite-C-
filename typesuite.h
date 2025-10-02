// typesuite.h : TypesSuite - Extra useful data types for C++
//
// Contains: InfInt (arbitrary integer), Vertex (2D/3D point),
// Matrix, Range (Python-style range), Timer, Cmd (execute shell commands)

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>

using namespace std;

// ===================== InfInt =====================
class InfInt {
private:
    vector<int> digits;
public:
    InfInt(int n = 0) {
        if (n == 0) digits.push_back(0);
        while (n > 0) {
            digits.insert(digits.begin(), n % 10);
            n /= 10;
        }
    }
    InfInt(const string& s) {
        for (char c : s) digits.push_back(c - '0');
    }

    int to_int() const {
        int val = 0;
        for (int d : digits) val = val * 10 + d;
        return val;
    }

    string to_string() const {
        string s;
        for (int d : digits) s += char('0' + d);
        return s;
    }

    void print() const { cout << to_string() << endl; }

    InfInt add(const InfInt& other) const {
        vector<int> res;
        int carry = 0;
        int i = digits.size() - 1;
        int j = other.digits.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += digits[i--];
            if (j >= 0) sum += other.digits[j--];
            res.insert(res.begin(), sum % 10);
            carry = sum / 10;
        }
        InfInt r;
        r.digits = res;
        return r;
    }
};

// ===================== Vertex =====================
template<typename T>
class Vertex {
public:
    T x, y, z;
    Vertex(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}

    double distance_to(const Vertex& other) const {
        return sqrt(pow(x - other.x, 2) +
            pow(y - other.y, 2) +
            pow(z - other.z, 2));
    }

    Vertex operator+(const Vertex& other) const {
        return Vertex(x + other.x, y + other.y, z + other.z);
    }

    void print() const { cout << "(" << x << "," << y << "," << z << ")" << endl; }
};

// ===================== Matrix =====================
class Matrix {
private:
    vector<vector<double>> data;
public:
    Matrix(int rows, int cols, double init = 0.0) {
        data.assign(rows, vector<double>(cols, init));
    }
    int rows() const { return data.size(); }
    int cols() const { return data[0].size(); }

    vector<double>& operator[](int i) { return data[i]; }
    const vector<double>& operator[](int i) const { return data[i]; }

    Matrix transpose() const {
        Matrix m(cols(), rows());
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                m[j][i] = data[i][j];
        return m;
    }

    void print() const {
        for (auto& row : data) {
            for (auto& v : row) cout << v << " ";
            cout << endl;
        }
    }
};

// ===================== Range =====================
class Range {
    int start, stop, step;
public:
    class Iterator {
        int val, step;
    public:
        Iterator(int v, int s) : val(v), step(s) {}
        int operator*() const { return val; }
        Iterator& operator++() { val += step; return *this; }
        bool operator!=(const Iterator& other) const {
            return step > 0 ? val < other.val : val > other.val;
        }
    };

    Range(int stop) : start(0), stop(stop), step(1) {}
    Range(int start, int stop, int step = 1) : start(start), stop(stop), step(step) {}

    Iterator begin() const { return Iterator(start, step); }
    Iterator end() const { return Iterator(stop, step); }
};

// ===================== Timer =====================
class Timer {
    chrono::time_point<chrono::high_resolution_clock> start_time;
public:
    void start() { start_time = chrono::high_resolution_clock::now(); }
    long long elapsed_ms() const {
        auto now = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - start_time).count();
    }
};

// ===================== Cmd =====================
class Cmd {
public:
    static string run(const string& command) {
        array<char, 128> buffer;
        string result;
#ifdef _WIN32
        unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
#else
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
#endif
        if (!pipe) throw runtime_error("popen() failed!");
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
};
