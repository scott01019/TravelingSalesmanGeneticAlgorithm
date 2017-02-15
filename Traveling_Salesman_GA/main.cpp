#include "ts_ga.h"

#include <chrono>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std::chrono;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

//  THIS MAIN FUNCTION IS USED FOR BASIC UI
int main() {
  srand(time(NULL));
  int selection = -1;
  while (selection != 3) {
    cout << "Traveling Salesman Genetic Aglorithm" << endl;
    cout << "Population Size: " << POPULATION_SIZE << endl;
    cout << "Numer of Generations: " << GENERATIONS << endl;
    cout << "Mutation Rate: " << MUTATION_RATE << endl;
    cout << "1. Run Evolution Without Kill Off" << endl;
    cout << "2. Run Evolution With Kill Off" << endl;
    cout << "3. Exit" << endl << endl;
    cin >> selection;

    if (selection == 1) {
      int unique;
      cout << "Please enter a unique integer value for file output purposes." << endl;
      cin >> unique;

      TS_GA ga;
      string current_run = "path_for_run_" + to_string(unique) + ".txt";
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      cout << endl << "Run " << unique << ":" << endl;
      ga.EvolveNormal(unique);
      ga.AppendBestFitness("results" + to_string(unique) + ".txt");
      ga.PrintBestPathToFile(current_run);
      cout << "Done with: " << unique << endl;
      high_resolution_clock::time_point t2 = high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
      cout << "Execution time: " << duration << endl;
      cout << "The 'results*.txt' file will contain the best fitness of the final generation." << endl;
      cout << "The 'path_for_run_*.txt' file will have the best path of the final generation." << endl;
      cout << "The 'fitness_over_time_for_run_*.txt' file will have the best fitness every 250 generations." << endl << endl;
    } else if (selection == 2) {
      int unique;
      cout << "Please enter a unique integer value for file output purposes." << endl;
      cin >> unique;

      TS_GA ga;
      string current_run = "path_for_run_" + to_string(unique) + ".txt";
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      cout << endl << "Run " << unique << ":" << endl;
      ga.EvolveWithKillOff(unique);
      ga.AppendBestFitness("results" + to_string(unique) + ".txt");
      ga.PrintBestPathToFile(current_run);
      cout << "Done with: " << unique << endl;
      high_resolution_clock::time_point t2 = high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
      cout << "Execution time: " << duration << endl;
      cout << "The 'results*.txt' file will contain the best fitness of the final generation." << endl;
      cout << "The 'path_for_run_*.txt' file will have the best path of the final generation." << endl;
      cout << "The 'fitness_over_time_for_run_*.txt' file will have the best fitness every 250 generations." << endl << endl;
    }
  }
  return 0;
}

//  THIS MAIN FUNCTION IS USED FOR SIMULATION WITH NO KILL OFF
/*int main() {
  srand(time(NULL));
  string results_fn = "results1.txt";
  for (unsigned int i = 0; i < 50; ++i) {
    TS_GA ga;
    string current_run = "path_for_run_" + to_string(i) + ".txt";
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    cout << endl << "Run " << i << ":" << endl;
    ga.EvolveNormal(i);
    ga.AppendBestFitness(results_fn);
    ga.PrintBestPathToFile(current_run);
    cout << "Done with: " << i << endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    cout << "Execution time: " << duration << endl;
  }
  return 0;
}*/

//  THIS MAIN FUNCTION IS USED FOR SIMULATION WITH KILL OFF OF BOTTOM HALF OF POPULATION
//  OF EVERY GENERATION
/*int main() {
  srand(time(NULL));
  string results_fn = "results2.txt";
  for (unsigned int i = 58; i < 59; ++i) {
    TS_GA ga;
    string current_run = "path_for_run_" + to_string(i) + ".txt";
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    cout << endl << "Run " << i << ":" << endl;
    ga.EvolveWithKillOff(i);
    ga.AppendBestFitness(results_fn);
    ga.PrintBestPathToFile(current_run);
    cout << "Done with: " << i << endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    cout << "Execution time: " << duration << endl;
  }
  return 0;
}*/