#ifndef DETALHES_H
#define DETALHES_H

#include <iostream>
#include <Irrlicht.h>
#include "GrafoObjeto.h"
#include <list>
#include "Vertice.h"
#include "Aresta.h"

using namespace irr;
using namespace video;
using namespace gui;
using namespace std;

class Vertice;
class Aresta;
class Mouse;
class Grafo;

class Detalhes
{
        public:
                Detalhes(IGUIWindow*, IGUIStaticText*);
                virtual ~Detalhes();
                void update();
                void setVisibilidade(bool);
                bool isVisivel() const;
        protected:
        private:
                void nadaSelecionado();
                void verticesOnly(); //numVertices
                void arestasOnly(); //numArestas, soma dos pesos, média dos pesos
                void umVertice(); //label, posição, arestas adjacentes, arestas incidentes
                void umaAresta(); //label, id dos vertices, tipo (adjacente ou misto)
                void totalGrafo(); //Se todo o grafo tá selecionado
                void verticesAndArestas();
                IGUIWindow* janela;
                IGUIStaticText* campoTexto;
};

#endif // DETALHES_H
