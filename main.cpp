/* 
 * File:   main.cpp
 * Author: Axel Huaripata Trujillo
 * Code:   20190388
 *
 * Created on 5 June 2024, 18:21
 */

#include "GRASP.hpp"

/*
 * 
 */



int main(int argc, char** argv) {
    Loom loom_1('a', 5),
            loom_2('b', 4),
            loom_3('c', 6),
            loom_4('d', 2),
            loom_5('e', 7),
            loom_6('f', 3);
         
    vector<Loom> looms = 
            {loom_1, loom_2, loom_3, loom_4, loom_5};
    
    Material material_1(10),
            material_2(7),
            material_3(9),
            material_4(12),
            material_5(6),
            material_6(2),
            material_7(7),
            material_8(8);
    
    vector<Material> materials = 
            {material_1, material_2, material_3, 
            material_4, material_5, material_6};
            //material_7, material_8};

    relax_parameter = 0.8;
    total_iterations = 100000;

    show_vector<Loom>(looms); cout << endl;
    show_vector<Material>(materials); cout << endl;
    
    grasp(looms, materials);
    
    return 0;
}
