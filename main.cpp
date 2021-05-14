#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <bits/stdc++.h>

using namespace std;
std::stringstream ss;

// Constantes utilizadas no algoritmo
const vector<int> RANGE_RANDOM_NUMBER = {0, 9};

// Tipos e Classes utilizados
class Node
{
private:
  int v;
  float x;
  float y;
  bool visited;

public:
  Node(int v, float x, float y, bool visited)
  {
    this->setV(v);
    this->setX(x);
    this->setY(y);
    this->setVisited(visited);
  }

  void setV(int v)
  {
    this->v = v;
  }

  void setX(float x)
  {
    this->x = x;
  }

  void setY(float y)
  {
    this->y = y;
  }

  void setVisited(bool visited)
  {
    this->visited = visited;
  }

  int getV()
  {
    return this->v;
  }

  float getX()
  {
    return this->x;
  }

  float getY()
  {
    return this->y;
  }

  bool getVisited()
  {
    return this->visited;
  }
};

class Solution
{
private:
  vector<Node> path;
  float distance;
  bool isCalculated;

public:
  Solution()
  {
    this->path = {};
    this->distance = 0;
    this->isCalculated = 0;
  }

  void setPath(vector<Node> path)
  {
    this->path = path;
  }

  void setDistance(float d)
  {
    this->distance = d;
  }

  void setIsCalculated(bool isCalculated)
  {
    this->isCalculated = isCalculated;
  }

  vector<Node> getPath()
  {
    return this->path;
  }

  float getDistance()
  {
    return this->distance;
  }

  bool getIsCalculated()
  {
    return this->isCalculated;
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

void print_solution(Solution solution)
{
  cout << "Distancia: " << solution.getDistance() << endl;
  cout << "Caminho: ";
  for (int i = 0; i < solution.getPath().size(); i++)
  {
    cout << solution.getPath()[i].getV() << " ";
  }
  cout << endl;
  cout << endl;
}

vector<float> split(const string &str, char delim = ' ')
{
  stringstream ss(str);
  string tok;
  vector<float> vec;
  while (getline(ss, tok, delim))
  {
    if (!tok.empty())
      vec.push_back(stof(tok));
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
      vector<float> node_vec = split(line);

      if (node_vec.size() != 3)
      {
        cout << "Arquivo de dados corrompido" << endl;
        return node_set;
      }

      Node node(
          node_vec[0],
          node_vec[1],
          node_vec[2],
          true);
      node_set.push_back(node);
    }
    file.close();
    return node_set;
  }

  cout << "Erro ao abrir o arquivo";
  return node_set;
}

float distanceXY(Node a, Node b)
{
  float x = pow(b.getX() - a.getX(), 2);
  float y = pow(b.getY() - a.getY(), 2);
  return sqrt(x + y);
}

int random_number(int from, int to)
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(from, to);
  return distr(gen);
}

vector<Solution> evaluate(vector<Solution> population)
{
  vector<Solution> new_population = population;
  for (int i = 0; i < population.size(); i++)
  {
    Solution solution = population[i];

    if (!solution.getIsCalculated())
    {
      for (int j = 1; j <= solution.getPath().size(); j++)
      {
        Node a = solution.getPath()[j - 1];
        Node b = solution.getPath()[j];
        float distance = distanceXY(a, b);
        float newDistance = solution.getDistance() + distance;
        solution.setDistance(newDistance);
        solution.setIsCalculated(true);
      }
    }

    new_population[i] = solution;
  }

  return new_population;
}

vector<Solution> create_initial_population(vector<Node> set)
{
  vector<Solution> solutions;
  const int INITIAL_NODES_QUANTITY = 2;
  for (int i = 0; i < INITIAL_NODES_QUANTITY; i++)
  {

    Solution solution;

    int random_node_position = random_number(0, set.size() - 1);
    Node initial_node(
        set[random_node_position].getV(),
        set[random_node_position].getX(),
        set[random_node_position].getY(),
        true);

    vector<Node> newPath = solution.getPath();
    newPath.push_back(initial_node);
    solution.setPath(newPath);
    while (solution.getPath().size() < set.size())
    {
      for (int j = 0; j < set.size(); j++)
      {
        Node node_set = set[j];
        bool visited = false;
        for (int k = 0; k < solution.getPath().size(); k++)
        {
          if (solution.getPath()[k].getV() == node_set.getV())
          {
            visited = true;
          }
        }
        if (!visited)
        {
          // insere o vértice no conjunto de solução
          newPath = solution.getPath();
          newPath.push_back(node_set);

          // calcula a distancia
          Node b = node_set;
          Node a = solution.getPath()[solution.getPath().size() - 1];
          float distance = distanceXY(a, b);

          solution.setPath(newPath);
          solution.setDistance(solution.getDistance() + distance);
          solution.setIsCalculated(true);

          /*
          if (newPath.size() == set.size())
          {
            //Retornar a primeira posição
            a = newPath[0];
            newPath.push_back(a);
            distance = distanceXY(a, b);

            solution.setPath(newPath);
            solution.setDistance(solution.getDistance() + distance);
          }
          */
        }
      }
    }
    solutions.push_back(solution);
  }

  return solutions;
}

bool orderByDistance(Solution a, Solution b)
{
  return a.getDistance() < b.getDistance();
}

bool contains(Node node, vector<Node> nodes)
{
  bool isContained = false;
  for (int j = 0; j < nodes.size(); j++)
  {
    if (nodes[j].getV() == node.getV())
    {
      isContained = true;
    }
  }

  return isContained;
}

vector<Solution> crossover(Solution father, Solution mother)
{
  vector<Solution> solutions;
  Solution first_child;
  Solution second_child;
  vector<Node> first_path;
  vector<Node> second_path;

  const int half_size = father.getPath().size() / 2;
  const int size = father.getPath().size();

  for (int i = 0; i < size; i++)
  {
    Node init(-1, -1, -1, false);
    if (i >= half_size)
    {
      first_path.push_back(init);
      second_path.push_back(mother.getPath()[i]);
    }
    else
    {
      first_path.push_back(father.getPath()[i]);
      second_path.push_back(init);
    }
  }

  for (int i = 0; i < size; i++)
  {
    if (i >= half_size)
    {
      Node node = mother.getPath()[i];
      if (!contains(node, first_path))
      {
        first_path[i].setV(node.getV());
        first_path[i].setX(node.getX());
        first_path[i].setY(node.getY());
      }
      else
      {
        for (int j = 0; j < father.getPath().size(); j++)
        {
          if (!contains(father.getPath()[j], first_path))
          {
            first_path[i] = father.getPath()[j];
          }
        }
      }

      second_path[i].setV(node.getV());
      second_path[i].setX(node.getX());
      second_path[i].setY(node.getY());
    }
    else
    {
      Node node = father.getPath()[i];
      if (!contains(node, second_path))
      {
        second_path[i].setV(node.getV());
        second_path[i].setX(node.getX());
        second_path[i].setY(node.getY());
      }
      else
      {
        for (int j = 0; j < mother.getPath().size(); j++)
        {
          if (!contains(mother.getPath()[j], second_path))
          {
            second_path[i] = mother.getPath()[j];
          }
        }
      }

      first_path[i].setV(node.getV());
      first_path[i].setX(node.getX());
      first_path[i].setY(node.getY());
    }
  }

  first_child.setPath(first_path);
  second_child.setPath(second_path);

  solutions.push_back(first_child);
  solutions.push_back(second_child);
  return solutions;
}

vector<Solution> mutation(vector<Solution> population, int tx_mutation)
{
  vector<Solution> mutation_pop;
  for (int i = 0; i < population.size(); i++)
  {

    int size = population[i].getPath().size() - 1;
    Solution solution = population[i];

    for (int j = 0; j < tx_mutation; j++)
    {
      int random_number_v1 = random_number(0, size);
      int random_number_v2 = random_number(0, size);

      vector<Node> new_nodes = solution.getPath();
      Node aux = solution.getPath()[random_number_v1];
      new_nodes[random_number_v1] = solution.getPath()[random_number_v2];
      new_nodes[random_number_v2] = aux;

      solution.setDistance(0);
      solution.setPath(new_nodes);
    }

    mutation_pop.push_back(solution);
  }

  return mutation_pop;
}

Solution localSearch(Solution solution)
{

  Solution new_solution = solution;

  int size = solution.getPath().size() - 1;
  int random_node_position = random_number(1, size);
  Node x1 = solution.getPath()[random_node_position];
  Node x2 = solution.getPath()[random_node_position - 1];
  float x1_x2_distance = distanceXY(x1, x2);

  for (int m = 0; m < size - 1; m++)
  {
    bool stop = false;
    if (m != random_node_position && m != random_node_position - 1)
    {
      int n = m + 1;
      Node i = solution.getPath()[m];
      Node j = solution.getPath()[n];

      float i_j_distance = distanceXY(i, j);
      float x1_i_distance = distanceXY(x1, i);
      float x2_j_distance = distanceXY(x2, j);

      float current_distance = x1_x2_distance + i_j_distance;
      float new_distance = x1_i_distance + x2_j_distance;

      if (new_distance < current_distance)
      {
        vector<Node> new_nodes = solution.getPath();
        cout << new_distance << endl;

        Node aux = solution.getPath()[random_node_position];
        new_nodes[random_node_position] = solution.getPath()[n];
        new_nodes[n] = aux;

        new_solution.setPath(new_nodes);
        stop = true;
        break;
      }
    }

    if (stop)
    {
      break;
    }
  }

  return new_solution;
}

int main(int argc, char *argv[])
{

  if (argc < 4)
  {
    cout << "Necessário passar a rota do arquivo de entrada, taxa de mutação e o tamanho máximo da população (ex: data/a280.txt 100 1000)" << endl;
    return 0;
  }

  const int MAX_GENERATION = stoi(argv[3]);
  const int TX_MUTATION = stoi(argv[2]);
  string PATH = argv[1];
  vector<Node> node_set;
  vector<Solution> population;
  vector<Solution> children;
  time_t start, end;

  time(&start);

  // Importação dos dados;
  node_set = import_data(PATH);
  population = create_initial_population(node_set);

  print_solution(population[0]);

  while (population.size() < MAX_GENERATION)
  {
    //Avaliação da População
    population = evaluate(population);

    // Seleção por classificação
    sort(population.begin(), population.end(), orderByDistance);

    //print_solution(population[0]);
    // cout << "SIZE: " << population.size() << endl;

    // Crossover
    children = crossover(population[0], population[1]);

    // Mutação
    children = mutation(children, TX_MUTATION);

    //busca local
    children[0] = localSearch(children[0]);
    children[1] = localSearch(children[1]);

    //Atualização da População
    population.push_back(children[0]);
    population.push_back(children[1]);
  }

  //Avaliação da População
  population = evaluate(population);

  // Seleção por classificação
  sort(population.begin(), population.end(), orderByDistance);

  cout << "BEST SOLUTION" << endl;
  print_solution(population[0]);

  cout << "WORST SOLUTION" << endl;
  print_solution(population[population.size() - 1]);

  time(&end);

  // Calculating total time taken by the program.
  double time_taken = double(end - start);
  cout << "Tempo de execução do programa : " << fixed
       << time_taken << setprecision(5);
  cout << " sec " << endl;
  return 0;
}