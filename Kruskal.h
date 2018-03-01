#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Algoritmos.h"
#include "Principal.h"

class Kruskal: public Algoritmos
{
        public:
                Kruskal();
                virtual ~Kruskal();
                virtual const std::string getNome() const;
        protected:
                virtual bool especificCondition() const; // Tem que ser conexo!
                virtual Grafo* execute();
        private:
                struct SemiComponente
                {
                        vector<int> verticesInclusos;
                        void addComponente(SemiComponente& a);
                        bool verificaVertice(int id);
                };
                Grafo* criarNovoGrafo();
                void selecionarArestas();
                void criarSemiComponentes();
                void mergeComponente(SemiComponente& a, SemiComponente& b);
                vector<SemiComponente> componentes;
                int verificaVertice(int id);
                std::list<Aresta*> arestasSelecionadas;
};

#endif // KRUSKAL_H
