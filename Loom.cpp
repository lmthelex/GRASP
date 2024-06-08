/* 
 * File:   Loom.cpp
 * Author: Axel Huaripata Trujillo
 * Code:   20190388
 * 
 * Created on 5 June 2024, 21:22
 */

#include "Loom.hpp"

//Material class
Material::Material()
{
    this->lenght = 0;
}

Material::Material(double lenght)
{
    this->lenght = lenght;
}

Material::Material(const Material &orig)
{
    (*this) = orig;
}

void Material::operator =(const Material &orig)
{
    this->lenght = orig.lenght;
}

bool Material::operator <(const Material &orig) const
{
    return this->lenght < orig.lenght;
}

bool Material::operator >(const Material &orig) const
{
    return this->lenght > orig.lenght;
}

ostream & operator <<(ostream &os, Material const &orig)
{
    os << "(" << orig.lenght << " m)";
    
    return os;
}

bool longest_material(const Material& material_a, const Material& material_b)
{
    return material_a > material_b;
}
//Loom class
Loom::Loom()
{
    this->code = '-';
    this->avalible = true;
    this->speed = 0;
    this->busy_time = 0;
}

Loom::Loom(char code)
{
    this->code = code;
    this->avalible = true;
    this->speed = 0;
    this->busy_time = 0;
}

Loom::Loom(char code, double speed)
{
    this->code = code;
    this->speed = speed;
    this->avalible = true;
    this->busy_time = 0;
}

Loom::Loom(const Loom &orig)
{
    (*this) = orig;
}

void Loom::operator =(const Loom &orig)
{
    this->avalible = orig.avalible;
    this->code = orig.code;
    this->speed = orig.speed;
    this->busy_time = orig.busy_time;
    this->current_material = orig.current_material;
}

bool Loom::operator <(const Loom &orig) const
{
    return this->speed < orig.speed;
}

bool Loom::operator >(const Loom &orig) const
{
    return this->speed > orig.speed;
}

ostream & operator <<(ostream &os, Loom const &orig)
{
    os << "{" << orig.code << " ";
    os << orig.speed << "h/m ";
    
    if(orig.avalible == true)
    {
        os << "yes}";
    }else{
        os << orig.current_material << "}";
    }
    return os;
}

bool speedest_loom(const Loom& loom_a, const Loom& loom_b)
{
    return loom_a > loom_b;
}

bool shortest_material_loom(const Loom& loom_a, const Loom& loom_b)
{
    double time_a, time_b;
    
    time_a = loom_a.current_material.lenght * loom_a.speed;
    time_b = loom_b.current_material.lenght * loom_b.speed;
    
    return time_a < time_b;
}

bool lowest_code_loom(const Loom& loom_a, const Loom& loom_b)
{ 
    return loom_a.code < loom_b.code;
}

