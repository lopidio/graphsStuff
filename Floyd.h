#ifndef FLOYD_H
#define FLOYD_H

#include "Algoritmos.h"


class Floyd: public Algoritmos
{
        public:
                Floyd();
                virtual ~Floyd();
        protected:
                virtual const std::string getNome() const;
                virtual bool needOrigem() const;
                virtual Grafo* execute();
                virtual bool especificCondition() const;
        private:
                int ** matrizRetorno;
                Grafo* createGraph();
};

#endif // FLOYD_H
