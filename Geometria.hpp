#ifndef GEOMETRIA_HPP
#define GEOMETRIA_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class Punto3D {
private:
    double x, y, z;
    unsigned char color[3]; 

public:
    Punto3D() : x(0.0), y(0.0), z(0.0) {
        color[0] = color[1] = color[2] = 0;
    }

    Punto3D(double x_arg, double y_arg, double z_arg, unsigned char r, unsigned char g, unsigned char b) 
        : x(x_arg), y(y_arg), z(z_arg) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    void setX(double val) { x = val; }
    void setY(double val) { y = val; }
    void setZ(double val) { z = val; }

    unsigned char getR() const { return color[0]; }
    unsigned char getG() const { return color[1]; }
    unsigned char getB() const { return color[2]; }
    void setColor(unsigned char r, unsigned char g, unsigned char b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    double distancia(const Punto3D& otro) const {
        double dx = x - otro.x;
        double dy = y - otro.y;
        double dz = z - otro.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    bool operator==(const Punto3D& otro) const {
        return (std::abs(x - otro.x) < 1e-6 &&
                std::abs(y - otro.y) < 1e-6 &&
                std::abs(z - otro.z) < 1e-6 &&
                color[0] == otro.color[0] &&
                color[1] == otro.color[1] &&
                color[2] == otro.color[2]);
    }

    friend std::ostream& operator<<(std::ostream& out, const Punto3D& p) {
        out << "(" << p.x << ", " << p.y << ", " << p.z << ") ["
            << (int)p.color[0] << ", " << (int)p.color[1] << ", " << (int)p.color[2] << "]";
        return out;
    }
};

class Mivector {
private:
    Punto3D* datos;
    int tamano;
    int capacidad;

    void redimensionar() {
        capacidad = (capacidad == 0) ? 1 : capacidad * 2;
        Punto3D* nuevos_datos = new Punto3D[capacidad];
        for (int i = 0; i < tamano; ++i) {
            nuevos_datos[i] = datos[i];
        }
        delete[] datos;
        datos = nuevos_datos;
    }

public:
    Mivector() : tamano(0), capacidad(10) {
        datos = new Punto3D[capacidad];
    }

    Mivector(int cap) : tamano(0), capacidad(cap) {
        if (capacidad < 1) capacidad = 1;
        datos = new Punto3D[capacidad];
    }

    ~Mivector() {
        delete[] datos;
    }

    Mivector(const Mivector& otro) : tamano(otro.tamano), capacidad(otro.capacidad) {
        datos = new Punto3D[capacidad];
        for (int i = 0; i < tamano; ++i) {
            datos[i] = otro.datos[i];
        }
    }

    Mivector& operator=(const Mivector& otro) {
        if (this != &otro) {
            delete[] datos;
            tamano = otro.tamano;
            capacidad = otro.capacidad;
            datos = new Punto3D[capacidad];
            for (int i = 0; i < tamano; ++i) {
                datos[i] = otro.datos[i];
            }
        }
        return *this;
    }

    void push_back(Punto3D val) {
        if (tamano == capacidad) {
            redimensionar();
        }
        datos[tamano] = val;
        tamano++;
    }

    int size() const {
        return tamano;
    }

    int capacity() const {
        return capacidad;
    }

    Punto3D& operator[](int index) {
        return datos[index];
    }

    const Punto3D& operator[](int index) const {
        return datos[index];
    }

    bool operator==(const Mivector& otro) const {
        if (tamano != otro.tamano) return false;
        for (int i = 0; i < tamano; ++i) {
            if (!(datos[i] == otro.datos[i])) return false;
        }
        return true;
    }

    Mivector operator-(const Mivector& otro) const {
        Mivector resultado;
        // usados[j] indica si el elemento j de otro ya fue emparejado
        std::vector<bool> usados(otro.tamano, false);
        for (int i = 0; i < tamano; i++) {
            bool encontrado = false;
            for (int j = 0; j < otro.tamano && !encontrado; j++) {
                if (!usados[j] && datos[i] == otro.datos[j]) {
                    resultado.push_back(datos[i]);
                    usados[j] = true;
                    encontrado = true;
                }
            }
        }
        return resultado;
    }

    friend std::ostream& operator<<(std::ostream& out, const Mivector& v) {
        out << "[";
        for (int i = 0; i < v.tamano; ++i) {
            out << v.datos[i] << (i == v.tamano - 1 ? "" : ", ");
        }
        out << "]";
        return out;
    }
};

#endif
