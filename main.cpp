#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <bits/stdc++.h>

using namespace std;
std::stringstream ss;

// Constantes utilizadas no algoritmo
const vector<int> RANGE_RANDOM_NUMBER = {0, 9};
const int CROMOSSOMO_SIZE = 9;
const int INITIAL_POPULATION_SIZE = 20;

// Tipos e Classes utilizados
typedef vector<int> Cromossomo;

class Node
{
private:
  int v;
  int x;
  int y;

public:
  void setV(int v)
  {
    this->v = v;
  }

  void setX(int x)
  {
    this->x = x;
  }

  void setY(int y)
  {
    this->y = y;
  }

  int getV()
  {
    return this->v;
  }

  int getX()
  {
    return this->x;
  }

  int getY()
  {
    return this->y;
  }
};

// Todos os auxiliares para log
void print_node_set(vector<Node> node_set)
{
  for (int i = 0; i < node_set.size(); i++)
  {
    cout << "v: " << node_set[i].getV() << " ";
    cout << "x: " << node_set[i].getX() << " ";
    cout << "y: " << node_set[i].getY() << " ";
    cout << endl;
  }
}

void print_population(vector<Cromossomo> population)
{
  for (int i = 0; i < population.size(); i++)
  {
    for (int j = 0; j < CROMOSSOMO_SIZE; j++)
    {
      cout << population[i][j] << ' ';
    }
    cout << endl;
  }
}

vector<int> split(const string &str, char delim = ' ')
{
  stringstream ss(str);
  string tok;
  vector<int> vec;
  while (getline(ss, tok, delim))
  {
    if (!tok.empty())
      vec.push_back(stoi(tok));
  }
  return vec;
}

vector<Node> import_data(string PATH)
{

  vector<Node> node_set;

  string line;
  ifstream file(PATH);

  if (file.is_open())
  {
    while (!file.eof())
    {
      getline(file, line);
      vector<int> node_vec = split(line);

      if (node_vec.size() != 3)
      {
        cout << "Arquivo de dados corrompido" << endl;
        return node_set;
      }

      Node node;
      node.setV(node_vec[0]);
      node.setX(node_vec[1]);
      node.setY(node_vec[2]);

      node_set.push_back(node);
    }
    file.close();
    return node_set;
  }

  cout << "Erro ao abrir o arquivo";
  return node_set;
}

vector<Cromossomo> generate_population(int population_size, int cromossomo_size)
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(RANGE_RANDOM_NUMBER[0], RANGE_RANDOM_NUMBER[1]);

  vector<Cromossomo> population;

  for (int i = 0; i < population_size; i++)
  {
    Cromossomo cromossomo;
    for (int i = 0; i < cromossomo_size; i++)
    {
      cromossomo.push_back(distr(gen));
    }
    population.push_back(cromossomo);
  }

  return population;
}

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    cout << "Necessário passar a rota do arquivo de entrada (ex: data/a280.txt)" << endl;
    return 0;
  }

  string PATH = argv[1];
  vector<Node> node_set;
  vector<Cromossomo> population;

  // Importação dos dados;
  node_set = import_data(PATH);

  // Gera a população inicial
  population = generate_population(INITIAL_POPULATION_SIZE, CROMOSSOMO_SIZE);

  print_population(population);

  return 0;
}