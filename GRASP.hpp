/* 
 * File:   GRASP.hpp
 * Author: Axel Huaripata Trujillo
 * Code:   20190388
 *
 * Created on 5 June 2024, 20:52
 */

#ifndef GRASP_HPP
#define GRASP_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <ctime>

#include "Loom.hpp"

#define INT_MAX 100000
#define INT_MIN 0

using namespace std;

template<typename element_type>
void show_vector(vector<element_type> &elements)
{
    for(element_type element : elements)
    {
        cout << element << " ";
    }
}

class Candidate
{
public:
    Loom loom;
    Material material;
    double time;
    
    Candidate();
    Candidate(const Candidate &orig);
    Candidate(const Loom &loom, const Material &material);
    
    void operator =(const Candidate &orig);
    bool operator <(const Candidate &orig) const;
    bool operator >(const Candidate &orig) const;
    
    void calculate_time();
    char get_loom_code() const;
};

ostream &operator <<(ostream &os, Candidate const &orig);
bool biggest_time_candidate(const Candidate &candidate_a,
        const Candidate &candidate_b);

typedef struct
{
    double total_time;
    vector<Candidate> detail;
}
Solution;

#define SEED 18//time(nullptr)

extern double relax_parameter;
extern int total_iterations;

void grasp(vector<Loom> &looms, vector<Material> &materials);
vector<Candidate> constructor(int &total_time, 
        vector<Loom> looms, vector<Material> materials);
void assign(Candidate &selected, vector<Loom> &looms,
                Material &material, int &assignations);
Candidate &select_candidate(vector<Candidate> &candidates);
int calculate_restricted_index(vector<Candidate> &candidates);
int generate_random_integer(int upper_limit, int lower_limit);
void update_availability(vector<Loom> &looms, Candidate &selected,
                Material &current_material);
double unassign(vector<Loom> &looms, int &assignations);
double evaluate(vector<Loom> looms, vector<Candidate> &solution);
void print_solution(vector<Loom> looms, vector<Candidate> &solution,
        int total_time);
#endif /* GRASP_HPP */

