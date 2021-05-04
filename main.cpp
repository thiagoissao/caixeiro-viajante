#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;
std::stringstream ss;

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

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    cout << "Necessário passar a rota do arquivo de entrada (ex: data/a280.txt)" << endl;
    return 0;
  }

  string PATH = argv[1];
  vector<Node> node_set = import_data(PATH);

  print_node_set(node_set);

  return 0;
}