#ifndef BFS_H
#define BFS_H

#include "Algoritmos.h"

class BFS: public Algoritmos
{
        public:
                BFS();
                virtual ~BFS();
                virtual const std::string getNome() const;
                virtual bool needOrigem() const;
                virtual bool needDestino() const;
        protected:
                virtual Grafo* execute();
        private:
                Grafo* createNewGraph();
                bool stepExecute();
                std::list<int> verticesAvisitar;
                std::list<int> verticesVisitados;
                bool listsSearch(int) const; //Procura se tá em uma das duas listas
};

#endif // BFS_H
