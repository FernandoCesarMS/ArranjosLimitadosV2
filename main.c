#include <iostream>
#include <exception>
#include <vector>
/*
esse erro ocorre quando os métodos get e set são invocados com um índice maior 
ou igual ao parâmetro N da classe. 
*/
class biggerError : public  std::exception{
public:
  virtual const char *errorMessage(){
    return "Erro: indice maior que arranjo.";
  }
};
template <class T, int N> class BoundedArray {
  public:
    void set(int index, T value) {
      buf[index] = value;
    }
    T get(int index) {
      return buf[index];
    }
  private:
    T buf[N];
};

template <class T> void testArray() {
  BoundedArray<T, 8> a;
  char action;
  while (std::cin >> action) {
    int index;
    std::cin >> index;
    try {
      if (action == 's') {
        T value;
        std::cin >> value;
        a.set(index, value);
      } else if (action == 'g') {
        std::cout << a.get(index) << std::endl;
      }
    } catch (...) {
      std::cerr << "Erro desconhecido." << std::endl;
    }
  }
}

int main() {
  char type;
  std::cin >> type;
  switch(type) {
    case 'd':
      testArray<double>();
      break;
    case 'i':
      testArray<int>();
      break;
    case 's':
      testArray<std::string>();
      break;
  }
  return 0;
}