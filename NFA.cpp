#include "NFA.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <algorithm>

Vertex::Vertex(int32_t num = 0, bool term = false) : _term(term), _num(num) {
  _to.resize(4);
}

bool Vertex::isTerm() {
  return _term;
}

int32_t Vertex::getNum() {
  return _num;
}

void Vertex::makeTerm() {
  _term = true;
}

void Vertex::makeNotTerm() {
  _term = false;
}

std::vector<int32_t> Vertex::getEdges(char c) {
  if (c == 'e')
    return _to[0];

  return _to[c - 'a' + 1];
}

void Vertex::addEdge(int32_t vertex, char c) {
  if (c == 'e')
    _to[0].push_back(vertex);
  else
    _to[c - 'a' + 1].push_back(vertex);
}

NFA::NFA(int32_t numStart, int32_t numFinish, char c) : _start(numStart), _size(2) {
  Vertex start(numStart, false), finish(numFinish, true);
  start.addEdge(numFinish, c);
  _vertices[numStart] = start;
  _vertices[numFinish] = finish;
}

int32_t NFA::getSize() {
  return _size;
}

int32_t NFA::getStart() {
  return _start;
}

Vertex NFA::getVertex(int32_t num) {
  return _vertices[num];
}

void NFA::changeStart(int32_t newStart) {
  _start = newStart;
}

void NFA::addEdge(int32_t first, int32_t second, char c) {
  _vertices[first].addEdge(second, c);
}

void NFA::addVertex(int32_t num) {
  _size++;
  _vertices[num] = Vertex(num, false);
}

std::vector<int32_t> NFA::getNumVertices() {
  std::vector<int32_t> numVertices;

  for (auto it : _vertices) {
    numVertices.push_back(it.first);
  }

  return numVertices;
}

std::vector<int32_t> NFA::getNumTerm() {
  std::vector<int32_t> numTerm;

  for (auto it : _vertices) {
    if (it.second.isTerm())
      numTerm.push_back(it.first);
  }

  return numTerm;
}

void NFA::makeTerm(int32_t num) {
  _vertices[num].makeTerm();
}

void NFA::makeNotTerm(int32_t num) {
  _vertices[num].makeNotTerm();
}

void NFA::add(NFA& addNFA, int32_t num) {
  // addNFA - автомат который мы прибавляем к нашему
  // num - номер(имя) новая вершины
  int32_t numStart = num;

  addVertex(numStart);

  std::vector<int32_t> list = addNFA.getNumVertices();
  _size += addNFA.getSize();

  for (int32_t num : list) {
    _vertices[num] = addNFA.getVertex(num);
  }

  int32_t num1 = getStart();
  int32_t num2 = addNFA.getStart();
  addEdge(numStart, num1, 'e');
  addEdge(numStart, num2, 'e');
  changeStart(numStart);
}

void NFA::mul(NFA& mulNFA) {
  std::vector<int32_t> prevTerm = getNumTerm();
  std::vector<int32_t> list = mulNFA.getNumVertices();

  _size += mulNFA.getSize();
  for (int32_t num : list) {
    _vertices[num] = mulNFA.getVertex(num);
  }

  for (int32_t num : prevTerm) {
    addEdge(num, mulNFA.getStart(), 'e');
    makeNotTerm(num);
  }
}

void NFA::kleene(int32_t num) {
  int32_t newStart = num;
  addVertex(newStart);
  std::vector<int32_t> prevTerm = getNumTerm();
  addEdge(newStart, getStart(), 'e');
  changeStart(newStart);

  for (int32_t num : prevTerm) {
    addEdge(num, newStart, 'e');
    makeNotTerm(num);
  }

  makeTerm(newStart);
}

void NFA::build(string& Reg) {
  std::stack<NFA> st;
  int32_t kVertices = 0;
  for (char c : Reg) {
    if (c >= 'a' && c <= 'c') {
      st.push(NFA(kVertices, kVertices + 1, c));
      kVertices += 2;
      continue;
    }

    if (c == '+') {
      NFA second = st.top();
      st.pop();
      NFA first = st.top();
      st.pop();
      first.add(second, kVertices);
      kVertices++;
      st.push(first);
    }

    if (c == '.') {
      NFA second = st.top();
      st.pop();
      NFA first = st.top();
      st.pop();
      first.mul(second);
      st.push(first);
    }

    if (c == '*') {
      NFA first = st.top();
      st.pop();
      first.kleene(kVertices);
      kVertices++;
      st.push(first);
    }
  }

  *this = st.top();
  st.pop();
}

void NFA::clear() {
  _start = 0;
  _vertices.clear();
  _size = 0;
}

void NFA::modificate() {
  int32_t newStart = getSize();
  std::vector<int32_t> list = getNumVertices();
  addVertex(newStart);
  changeStart(newStart);

  for (int32_t num : list) {
    if (num != newStart)
      addEdge(newStart, num, 'e');
  }
}

int32_t lenstd::maxRead(NFA& myNFA,
                    int32_t numVertex,
                    string& str,
                    int32_t pos,
                    int32_t len,
                    std::vector<std::vector<int32_t> >& used,
                    int32_t iter) {
  if (pos == str.size())
    return len;

  used[numVertex][pos] = iter;

  int32_t ans = len;
  Vertex vertex = myNFA.getVertex(numVertex);
  std::vector<int32_t> epsEdge = vertex.getEdges('e');
  std::vector<int32_t> litterEdge = vertex.getEdges(str[pos]);

  for (int32_t to : litterEdge) {
    if (used[to][pos + 1] != iter)
      ans = std::max(
          ans, lenstd::maxRead(myNFA, to, str, pos + 1, len + 1, used, iter));
  }

  for (int32_t to : epsEdge) {
    if (used[to][pos] != iter)
      ans =
          std::max(ans, lenstd::maxRead(myNFA, to, str, pos, len, used, iter));
  }

  return ans;
}

int32_t getAns(string& Reg, string& str) {
  NFA myNFA;
  myNFA.build(Reg);
  // myNFA.print32_t();
  myNFA.modificate();
  // myNFA.print32_t();
  std::vector<std::vector<int32_t> > used(myNFA.getSize(),
                                      std::vector<int32_t>(str.size() + 1, 0));
  int32_t ans = 0;

  for (int32_t i = 0; i < str.size(); ++i) {
    int32_t pos = i, iter = i + 1;
    int32_t cur = lenstd::maxRead(myNFA, myNFA.getStart(), str, pos, 0, used, iter);
    ans = std::max(ans, cur);
  }
    myNFA.clear();
    return ans;
}
