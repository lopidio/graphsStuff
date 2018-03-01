#ifndef BUSCAPROFUNDIDADE_H
#define BUSCAPROFUNDIDADE_H

#include "Algoritmos.h"
#include <stack>

class BuscaProfundidade: public Algoritmos
{
        public:
                BuscaProfundidade();
                virtual ~BuscaProfundidade();
                virtual bool needOrigem() const;
                virtual bool needDestino() const;
                virtual const std::string getNome() const;
        protected:
                virtual Grafo* execute(); //M�todo a ser sobrecarregado SEMPRE CRIAR V�RTICES ANTES DAS ARESTAS!
        private:
                std::list<int> visitados;
                stack<Vertice*> pilha;
                bool verificaExistenciaNaLista(int);
                bool stepExecute(int id);
};

#endif // BUSCAPROFUNDIDADE_H
