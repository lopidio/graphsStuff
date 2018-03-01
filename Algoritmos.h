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
                static Algoritmos* getAlgoritmoFromID(short); //Padrão factory, os filhos serão criados a partir desse método
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
                virtual Grafo* execute() = 0; //Método a ser sobrecarregado SEMPRE CRIAR VÉRTICES ANTES DAS ARESTAS!
                Grafo* grafo;
        private:
                void getOrigem();
                void getDestino();
};

#endif // ALGORITMOS_H
