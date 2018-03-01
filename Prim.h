#ifndef PRIM_H
#define PRIM_H

#include "Algoritmos.h"

class Prim: public Algoritmos
{
        public:
                Prim();
                virtual ~Prim();
                virtual const std::string getNome() const;
                virtual bool needOrigem() const;
        protected:
                virtual bool especificCondition() const; // Tem que ser conexo!
                virtual Grafo* execute();
        private:
                Grafo* criarNovoGrafo();
                void selecionarArestas();
                bool verificaVertice(int id);
                std::list<int> verticesInclusos;
                std::list<Aresta*> arestasSelecionadas;
};

#endif // PRIM_H
