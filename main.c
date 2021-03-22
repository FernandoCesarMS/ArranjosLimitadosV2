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
/*
 esse erro ocorre quando os métodos get e set são invocados com um índice 
 negativo. 
*/
class negativeError : public  std::exception{
public:
  virtual const char *errorMessage(){
    return "Erro: indice negativo.";
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
/*
esse erro ocorre quando os métodos get e set são invocados com um índice maior
ou igual ao parâmetro N da classe.
*/
class uninitializedError : public std::exception{
public:
  virtual const char *errorMessage(){
    return "Erro: indice nao inicializado.";
  }
};
template <class T, int N> class BoundedArray{
private:
  T buf[N];
  std::vector<int> uninitialized;
public:
  BoundedArray(){
    for (int i = 0; i <= N-1; i++){
      uninitialized.push_back(0);
    }
  }
  T get(int posicao){
    if (!(posicao >= 0)){
      throw negativeError();  
    }
    else if (!(posicao < N)){
      throw biggerError(); 
    }
    else if (uninitialized[posicao] == 0){
      throw uninitializedError();
    }
    else{
      return buf[posicao];   
    }
  }
  void set(int posicao, T valor){
    if (posicao >= 0 && posicao < N){
        uninitialized[posicao]++; 
        buf[posicao] = valor;
    }
    else if (!(posicao >= 0)){
      throw negativeError();  
    }
    else{
      throw biggerError();  
    }
  }
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