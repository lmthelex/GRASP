/* 
 * File:   GRASP.cpp
 * Author: Axel Huaripata Trujillo
 * Code:   20190388
 *
 * Created on 5 June 2024, 20:52
 */

#include "GRASP.hpp"

Candidate::Candidate()
{
    this->time = 0;
}

Candidate::Candidate(const Candidate &orig)
{
    (*this) = orig;
}

Candidate::Candidate(const Loom &loom, const Material &material)
{
    this->loom = loom;
    this->material = material;
    
    this->calculate_time();
}

void Candidate::operator =(const Candidate &orig)
{
    this->loom = orig.loom;
    this->material= orig.material;
    this->time = orig.time;
}

bool Candidate::operator <(const Candidate &orig) const
{
    return this->time < orig.time;
}

bool Candidate::operator >(const Candidate &orig) const
{
    return this->time > orig.time;
}

void Candidate::calculate_time()
{
    this->time = this->loom.speed * this->material.lenght;
}

char Candidate::get_loom_code() const
{
    return this->loom.code;
}

ostream &operator <<(ostream &os, Candidate const &orig)
{
    os << "[";
    os <<orig.loom << orig.material;
    os << " <- " << orig.time << "h]";
}

bool biggest_time_candidate(const Candidate &candidate_a,
        const Candidate &candidate_b)
{
    return candidate_a.time > candidate_b.time;
}

double relax_parameter;
int total_iterations;

void grasp(vector<Loom> &looms, vector<Material> &materials)
{     
    Solution solution;
    vector<vector<Candidate>> solutions;
    int best_time = INT_MAX, best_index;
    
    sort(looms.begin(), looms.end(), speedest_loom);
    sort(materials.begin(), materials.end(), longest_material);
    
    for(int i = 0; i != total_iterations; i++)
    {
        int total_time;
        vector<Candidate> detail;
        
        detail = constructor(total_time, looms, materials);
        solutions.push_back(detail);
        total_time = evaluate(looms, detail);
        
        if(total_time < best_time)
        {
            best_time = total_time;
            best_index = i;
        }
    }
    
    print_solution(looms, solutions[best_index], best_time);
}

vector<Candidate> constructor(int &total_time, 
        vector<Loom> looms, vector<Material> materials)
{
    int assignations;
    Candidate selected;
    vector<Candidate> solution;
    
    total_time = assignations = 0;

    for(Material material : materials)
    {
        if(assignations == looms.size())
        {
            total_time += unassign(looms, assignations);
        }
        
        assign(selected, looms, material, assignations);
        solution.push_back(selected);
    }
    
    return solution;
}

void assign(Candidate &selected, vector<Loom> &looms,
        Material &material, int &assignations)
{
    vector<Candidate> candidates;

    for(const Loom loom : looms)
    {
        Candidate candidate(loom, material);

        candidates.push_back(candidate);
    }

    selected = select_candidate(candidates);
    update_availability(looms, selected, material);

/*
    if(assignations == looms.size())
    {
        Candidate empty;
        
        selected = empty;
    }
    else
    {
        vector<Candidate> candidates;

        for(const Loom loom : looms)
        {
            if(loom.avalible == true)
            {
                Candidate candidate(loom, material);

                candidates.push_back(candidate);
            }
        }
        
        assignations++;
        selected = select_candidate(candidates);
        update_availability(looms, selected, material);
    }
*/
}

Candidate &select_candidate(vector<Candidate> &candidates)
{
    int restricted_index, random_index;

    sort(candidates.begin(), candidates.end(), biggest_time_candidate);
    restricted_index = calculate_restricted_index(candidates);
    random_index = generate_random_integer(0, restricted_index);

    return candidates[random_index];
}

int calculate_restricted_index(vector<Candidate> &candidates)
{
    int lower_index, upper_index, restricted_index;
    double upper_limit;
    Candidate worst, better;
    
    lower_index = 0;
    upper_index = candidates.size() - 1;
    restricted_index = -1;
    better = candidates[lower_index];
    worst = candidates[upper_index];
    upper_limit = better.time - relax_parameter * (better.time - worst.time);

    for(const Candidate candidate : candidates)
    {
        if(candidate.time >= upper_limit)
        {
            restricted_index++;
        }
    }
        
    return restricted_index;
}

int generate_random_integer(int upper_limit, int lower_limit)
{
    static int counter = 0;
    static default_random_engine engine(SEED);
    uniform_int_distribution<int> distribution(upper_limit, lower_limit);

    if(counter == 0){
        distribution(engine);
    }
    
    counter++;
    
    return distribution(engine);
}

void update_availability(vector<Loom> &looms, Candidate &selected,
        Material &current_material)
{
/*
    int index = 0;

    for(Loom loom : looms)
    {
        if(loom.code == selected.get_loom_code())
        {
            looms[index].current_material = current_material;
            looms[index].busy_time = current_material.lenght * loom.speed;
        }
        
        index++;
    }
*/

    int index = 0;

    for(Loom loom : looms)
    {
        if(loom.code == selected.get_loom_code())
        {
            looms[index].avalible = false;
            looms[index].current_material = current_material;
            looms[index].busy_time = current_material.lenght * loom.speed;
        }
        
        index++;
    }

/*
    for(int index = 0; index != looms.size(); index++)
    {
        if(looms[index].code == selected.get_loom_code())
        {
            looms[index].avalible = false;
            looms[index].current_material = current_material;
            looms[index].busy_time = current_material.lenght * looms[index].speed;
        }
    }
*/
}

double unassign(vector<Loom> &looms, int &assignations)
{
    int index = 0;
    double passed_time = 0;
    Material empty_material;
    
    sort(looms.begin(), looms.end(), shortest_material_loom);
    
    for(const Loom loom : looms)
    {
        if(loom.busy_time > 0){
            passed_time = loom.busy_time;
            break;
        }
    }

    for(Loom loom : looms)
    {
        looms[index].busy_time -= passed_time; 
        
        if(looms[index].busy_time == 0)
        {
            assignations--;
            looms[index].avalible = true;
            looms[index].current_material = empty_material;  
        }
        
        index++;
    }
    
    return passed_time;
/*
    for(int index = 0; index != looms.size(); index++)
    {
        looms[index].busy_time -= passed_time; 
        
        if(looms[index].busy_time == 0)
        {
            assignations--;
            looms[index].avalible = true;
            looms[index].current_material = empty_material;    
        }
    }
*/
}

double evaluate(vector<Loom> looms, vector<Candidate> &solution)
{
    int index;
    double max_time = INT_MIN, current_time;
    
    for(Loom loom : looms)
    {
        current_time = 0;
        
        for(Candidate assignation : solution)
        {
            if(loom.code == assignation.loom.code)
            {
                current_time+= assignation.time;
                
                if(current_time > max_time)
                {
                    max_time = current_time;
                }
            }
        }
    }

    return max_time;
}

void print_solution(vector<Loom> looms, vector<Candidate> &solution,
        int total_time)
{
    double time;
    
    sort(looms.begin(), looms.end(), lowest_code_loom);
    
    for(Loom loom : looms)
    {
        cout << loom << " with ";
        
        for(Candidate assignation : solution)
        {
            if(loom.code == assignation.loom.code)
            {
                cout << assignation.material;
            }
        }
        cout << endl;
    }
    
    cout << "Total time " << total_time << endl;
}