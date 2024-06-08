/* 
 * File:   Loom.hpp
 * Author: Axel Huaripata Trujillo
 * Code:   20190388
 *
 * Created on 5 June 2024, 21:22
 */

#ifndef LOOM_HPP
#define LOOM_HPP

#include <iostream>

using namespace std;

class Material
{
public:
    double lenght;
    
    Material();
    Material(double lenght);
    Material(const Material &orig);
    
    void operator =(const Material &orig);
    bool operator <(const Material &orig) const;
    bool operator >(const Material &orig) const;
};

ostream &operator <<(ostream &os, Material const &orig);
bool longest_material(const Material &material_a, const Material &material_b);

class Loom
{
public:
    bool avalible;
    char code;
    double speed, busy_time;
    Material current_material;
    
    Loom();
    Loom(char code);
    Loom(char code, double speed);
    Loom(const Loom& orig);
    
    void operator =(const Loom& orig);
    bool operator <(const Loom& orig) const;
    bool operator >(const Loom& orig) const;
};

ostream &operator <<(ostream &os, Loom const &orig);
bool speedest_loom(const Loom& loom_a, const Loom& loom_b);
bool shortest_material_loom(const Loom& loom_a, const Loom& loom_b);
bool lowest_code_loom(const Loom& loom_a, const Loom& loom_b);

#endif /* LOOM_HPP */

