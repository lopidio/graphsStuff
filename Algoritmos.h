#ifndef ALGORITMOS_H
#define ALGORITMOS_H

class Grafo;
class Vertice;

#include <list>
#include "GrafoObjeto.h"
//#include "Grafo.h"
#include <iostream>
#include "Animacao.h"
#include "Vertice.h"

using namespace std;


enum eAlgoritmoID{aID_buscaProfundidade, aID_buscaLargura, aID_dijkstra, aID_kruskal, aID_prim, aID_floyd, aID_algotimosCount};

class Algoritmos
{
        public:
                virtual ~Algoritmos();
                static Algoritmos* getAlgoritmoFromID(short); //Padr�o factory, os filhos ser�o criados a partir desse m�todo
                virtual bool needOrigem() const;
                virtual bool needDestino() const;
                virtual bool especificCondition() const;
                virtual const  std::string getNome() const;
                Grafo* executeFromGrafo(Grafo*);
        protected:
                Vertice*origem, *destino;
                int ** matriz;
                int numVertices;
                Animacao* animacao;
                virtual Grafo* execute() = 0; //M�todo a ser sobrecarregado SEMPRE CRIAR V�RTICES ANTES DAS ARESTAS!
                Grafo* grafo;
        private:
                void getOrigem();
                void getDestino();
};

#endif // ALGORITMOS_H
