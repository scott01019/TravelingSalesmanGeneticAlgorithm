#ifndef TS_GA_H_
#define TS_GA_H_

#include "city.h"
#include "ts_genotype.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

//  we define values for number of generations,
//  mutation rate (between 0 and 1), and population
//  size
#define GENERATIONS 10000
#define MUTATION_RATE 0.0500
#define POPULATION_SIZE 200

class TS_GA {
public:
  //  constructors
  TS_GA();

  //  methods
  void AppendBestFitness(const string &) const;
  float BestFitness() const;
  void EvolveNormal(int);
  void EvolveWithKillOff(int);
  float Fitness(const TS_Genotype &) const;
  void KillWeakest(vector<TS_Genotype> &, int);
  void MutatePopulation();
  void PrintBest();
  void PrintBestPathToFile(const string &) const;
  void TournamentSelect();
  void TournamentSelectWithKillOff();

  //  getters
  const vector<City> &cities() const { return this->cities_; }
  const vector<TS_Genotype> &population() const { return this->population_; }

  //  setters
  void set_cities(const vector<City> &cities) { this->cities_ = cities; }
  void set_population(const vector<TS_Genotype> &population) { this->population_ = population; }
private:
  vector<TS_Genotype> population_;  //  population of genotypes to evolve
  vector<City> cities_;             //  cities to be visited by the salesman
};

#endif  //  TS_GA_H_