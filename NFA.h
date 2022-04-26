#ifndef FL_PRACTIC1_DFA_H
#define FL_PRACTIC1_DFA_H
#include <vector>
#include <string>
#include <map>

class Vertex {
public:
  Vertex(int32_t num, bool term);
  std::vector<int32_t> getEdges(char c);
  bool isTerm();
  int32_t getNum();
  void addEdge(int32_t vertex, char c);
  void makeTerm();
  void makeNotTerm();
private:
      bool _term;
  int32_t _num;
  std::vector<std::vector<int32_t> > _to;

};

class NFA {
public:
  NFA() = default;
  NFA(int32_t numStart, int32_t numFinish, char c);
  // возвраает количество
  int32_t getSize();

  // возвращает номер стартовую вершину
  int32_t getStart();

  // возвращает вершину по номеру(имени)
  Vertex getVertex(int32_t num);

  // возвращает список состояний
  std::vector<int32_t> getNumVertices();

  // возвращает список терминальных вершин
  std::vector<int32_t> getNumTerm();

  // newStart - номер новой стартовой вершины
  void changeStart(int32_t newStart);

  // добавляем переход <first, c> -> second
  void addEdge(int32_t first, int32_t second, char c);

  // возвращает вершину по номеру
  void addVertex(int32_t num);

  // вершину с номером num делаем терминальной
  void makeTerm(int32_t num);

  // вершину с номером num делаем нетерминальной
  void makeNotTerm(int32_t num);

  // складываем наш автомат с addNFA,
  // num - номер(имя) вершины которую надо будет создать
  void add(NFA& addNFA, int32_t num);

  // умножаем наш автомат с mulNFA
  void mul(NFA& mulNFA);

  // делаем замыкание клини,
  // num - - номер(имя) вершины которую надо будет создать
  void kleene(int32_t num);

  // создаём автомат по регулярке
    void build(std::string& Reg);

    void clear();

    void modificate();

private:
  int32_t _start;
  std::map<int32_t, Vertex> _vertices;
  int32_t _size;

};


int32_t lenMaxRead(NFA& myNFA, int32_t numVertex, int32_t pos, int32_t len, std::vector<std::vector <int32_t> >&used, int32_t iter);

int32_t getAns(std::string& Reg, std::string& str);

#endif //FL_PRACTIC1_DFA_H
