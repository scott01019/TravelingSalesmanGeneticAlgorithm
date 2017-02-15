#include "city.h"
#include "comparators.h"
#include "functions.h"
#include "ts_ga.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
using std::cout;
using std::endl;
using std::ofstream;
using std::pair;
using std::string;
using std::vector;

//  Default constructor for TS_GA
TS_GA::TS_GA() {
  //  Generate 100 City objects with coordinates from 0 to 1000
  for (unsigned int i = 0; i < 100; ++i) {
    this->cities_.push_back(City(rand() % 1001, rand() % 1001));
  }
  //  Generate TS_Genotypes, calculate their fitness, and add them to population
  for (unsigned int i = 0; i < POPULATION_SIZE; ++i) {
    TS_Genotype new_geneotype;
    new_geneotype.set_fitness(this->Fitness(new_geneotype));
    this->population_.push_back(new_geneotype);
  }
  //  Sort population by fitness so most fit is at the front
  std::sort(this->population_.begin(), this->population_.end(), fitness_comp);
}

//  Name: AppendBestFitness
//  Puprose: Append the best fitness in a population to the textfile specified by parameter string
//  Input: const string reference fname - name of file to append fitness to
void TS_GA::AppendBestFitness(const string &fname) const {
  ofstream file;
  file.open(fname, std::ios::app);
  file << this->BestFitness() << "\n";
  file.close();
}

//  Name: BestFitnees
//  Purpose: Return most fit genotype in population
//  Output: Returns float value of best fitness in population
float TS_GA::BestFitness() const {
  return this->population_.front().fitness();
}

//  Name: EvolveNormal
//  Purpose: Runs the genetic algorithm without kill off
//  Input: int run_num - used to define name of text file
void TS_GA::EvolveNormal(int run_num) {
  //  for the number of generations
  for (unsigned int i = 0; i < GENERATIONS; ++i) {
    //  mutate population
    this->MutatePopulation();

    //  select for reproduction
    this->TournamentSelect();

    //  print fitness to file (every 250 generations)
    if (i == 0 || i % 250 == 0 || i == GENERATIONS - 1) {
      cout << "Generation: " << i << endl;
      this->PrintBest();
      ofstream file;
      file.open(string("fitness_over_time_run_") + std::to_string(run_num) + string(".txt"), std::ios::app);
      file << i << " " << this->BestFitness() << "\n";
      file.close();
    }
  }
}

//  Name: EvolveWithKillOff
//  Purpose: Runs the genetic algorithm with kill off
//  Input: int run_num - used to define name of text file
void TS_GA::EvolveWithKillOff(int run_num) {
  for (unsigned int i = 0; i < GENERATIONS; ++i) {
    //  mutate population
    this->MutatePopulation();

    //  select for reproduction with kill off
    this->TournamentSelectWithKillOff();

    //  print fitness to file (every 250 generations)
    if (i == 0 || i % 250 == 0 || i == GENERATIONS - 1) {
      cout << "Generation: " << i << endl;
      this->PrintBest();
      ofstream file;
      file.open(string("fitness_over_time_run_") + std::to_string(run_num) + string(".txt"), std::ios::app);
      file << i << " " << this->BestFitness() << "\n";
      file.close();
    }
  }
}

//  Name: Fitness
//  Purpose: Calculates the fitness of the given genotype
//  Inputs: const TS_Genotype reference genotype for the fitness to be calculated
//  Ouput: float representing calculated fitness
float TS_GA::Fitness(const TS_Genotype &genotype) const {
  //  construct vector of pairs int, float where float is fitness
  //  and int corresponds to the index of city in cities_ vector
  vector<pair<int, float>> city_order_visited;

  //  get the genotype
  vector<float> genes = genotype.genes();

  //  break each gene into pair object and push it onto order vector
  for (unsigned int i = 0; i < genes.size(); ++i) {
    city_order_visited.push_back(pair<int, float>(i, genes[i]));
  }

  //  sort the order vector
  std::sort(city_order_visited.begin(), city_order_visited.end(), pair_order_comp);

  //  get the distance between the first and last city
  float distance = this->cities_[city_order_visited.front().first].Distance(
    this->cities_[city_order_visited.back().first]);

  //  for each city except last get the distance from itself to the next city
  //  and add it to distance
  for (vector<pair<int, float>>::const_iterator it = city_order_visited.begin();
    it != city_order_visited.end() - 1; ++it) {
    distance += this->cities_[it->first].Distance(this->cities_[(it + 1)->first]);
  }

  //  return distance
  return distance;
}

//  Name: KillWeakest
//  Purpose: Kill the weakest num_kill members of the given population
//  Inputs: reference to vector of TS_Genotype - the population to kill from
//  int num_kill - the number of members to kill
//  Assumption: The population is ordered from strongest to weakest
void TS_GA::KillWeakest(vector<TS_Genotype> &population, int num_kill) {
  population.erase(population.end() - num_kill, population.end());
}

//  Name: MutatePopulation
//  Purpose: Determine which members of population will be mutated, and call mutate
//  method for those members
void TS_GA::MutatePopulation() {
  for (vector<TS_Genotype>::iterator it = this->population_.begin();
    it != this->population_.end(); ++it) {
    if (RandomFloat(0, 1) < MUTATION_RATE) it->Mutate();
  }
}

//  Name: PrintBest
//  Purpose: Print best fitness to console
void TS_GA::PrintBest() {
  this->population_.front().PrintFitness();
}

//  Name: PrintBestPathToFile
//  Purpose: Print the best path in the population to a file
//  Inputs: const string reference fname - name of file to print path to
void TS_GA::PrintBestPathToFile(const string &fname) const {
  //  construct vector of pairs int, float where float is fitness
  //  and int corresponds to the index of city in cities_ vector
  vector<pair<int, float>> city_order_visited;

  //  get the genotype of best member of population
  vector<float> genes = this->population_.front().genes();

  //  break each gene into pair object and push it onto order vector
  for (unsigned int i = 0; i < genes.size(); ++i) {
    city_order_visited.push_back(pair<int, float>(i, genes[i]));
  }

  //  sort the order vector
  std::sort(city_order_visited.begin(), city_order_visited.end(), pair_order_comp);

  //  print the coordinates of the path to file
  ofstream file;
  file.open(fname);
  file << city_order_visited.size() << "\n";
  for (vector<pair<int, float>>::const_iterator it = city_order_visited.begin();
    it != city_order_visited.end(); ++it) {
    file << this->cities_[it->first].x() << " " << this->cities_[it->first].y() << "\n";
  }
  file.close();
}

//  Name: TournamentSelect
//  Purpose: Selection algorithm for reproduction
void TS_GA::TournamentSelect() {
  vector<TS_Genotype> new_population;
  while (new_population.size() < POPULATION_SIZE) {
    
    //  select 4 from the current population
    vector<TS_Genotype> selected;
    for (unsigned int i = 0; i < 4; ++i) {
      int j = rand() % this->population_.size();
      selected.push_back(this->population_[j]);
    }

    //  sort selected and kill the weakest 2
    std::sort(selected.begin(), selected.end(), fitness_comp);
    this->KillWeakest(selected, 2);

    //  Breed Selected and add them to selected
    selected.push_back(selected.front().Breed(selected.back()));
    selected.back().set_fitness(this->Fitness(selected.back()));
    selected.push_back(selected.back().Breed(selected.front()));
    selected.back().set_fitness(this->Fitness(selected.back()));

    //  add selected to new population
    new_population.insert(new_population.end(), selected.begin(), selected.end());

    //  if new population is too large kill off random until it reaches POPULATION_SIZE
    while (new_population.size() > POPULATION_SIZE)
      new_population.erase(new_population.end() - 1);
  }

  //  set population to new population
  this->population_ = new_population;
  std::sort(this->population_.begin(), this->population_.end(), fitness_comp);
}

//  Name: TournamentSelectWithKillOff
//  Purpose: Selection algorithm for reproduction. Kills off weakest half of population
//  before selection begins.
void TS_GA::TournamentSelectWithKillOff() {
  vector<TS_Genotype> new_population;

  //  kill off bottom half of the population
  this->KillWeakest(this->population_, this->population_.size() / 2);

  while (new_population.size() < POPULATION_SIZE) {

    //  select 4 from the current population
    vector<TS_Genotype> selected;
    for (unsigned int i = 0; i < 4; ++i) {
      int j = rand() % this->population_.size();
      selected.push_back(this->population_[j]);
    }

    //  sort selected and kill the weakest 2
    std::sort(selected.begin(), selected.end(), fitness_comp);
    this->KillWeakest(selected, 2);

    //  Breed Selected and add them to selected
    selected.push_back(selected.front().Breed(selected.back()));
    selected.back().set_fitness(this->Fitness(selected.back()));
    selected.push_back(selected.back().Breed(selected.front()));
    selected.back().set_fitness(this->Fitness(selected.back()));

    //  add selected to new population
    new_population.insert(new_population.end(), selected.begin(), selected.end());

    //  if new population is too large kill off random until it reaches POPULATION_SIZE
    while (new_population.size() > POPULATION_SIZE)
      new_population.erase(new_population.end() - 1);
  }

  //  set population to new population
  this->population_ = new_population;
  //  sort by fitness
  std::sort(this->population_.begin(), this->population_.end(), fitness_comp);
}