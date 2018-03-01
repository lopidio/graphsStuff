#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Algoritmos.h"

class Dijkstra: public Algoritmos
{
        public:
                Dijkstra();
                virtual ~Dijkstra();
        protected:
                virtual bool needOrigem() const;
                virtual Grafo* execute();
                virtual bool especificCondition() const;
                virtual const std::string getNome() const;
        private:
                struct Caminho
                {
                        Caminho (int pai_, int custoTotal_, int id_);
                        int pai;
                        int custoTotal;
                        int id;
                };
                static int compareCaminho(const Caminho& a, const Caminho& b);
                void stepExecute();
                vector<Caminho> verticesVisitados;
                std::list<Caminho> verticesParaVisitar;
                bool verificaVisitados(int ) const;
                Grafo* createGraph();
                Caminho* searchAndReturnAVisitar(int);
};

#endif // DIJKSTRA_H
