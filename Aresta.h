#ifndef ARESTA_H
#define ARESTA_H
#include <Irrlicht.h>
#include "GrafoObjeto.h"
#include "Vertice.h"

#define ERROR 5.f

using namespace irr;
using namespace core;

class Vertice;

enum eTipoAresta {tA_unidirecional, tA_bidirecional};
class Aresta: public GrafoObjeto
{
        public:
                Aresta(Vertice *,Vertice *);
                virtual ~Aresta();
                virtual void update();
                virtual void draw() const;
                virtual bool isCriado() const; //Responde se foi completamente criado
		virtual const position2df & getPosicao() const; //
		virtual void editarValor(const wstring&); //Label ou Custo
		const Vertice* getVerticeOrigem() const;
		const Vertice* getVerticeDestino() const;
                bool operator==(const Aresta &outra) const; //Através dos id’s dos
                bool eDoVertice(const Vertice*);
                virtual void salvar(FILE*, int) const;
                bool isBidirecional() const;
                virtual bool isInsideRetangulo() const;
                void mudarTipo();
                float getFloatValor() const;
        private:
                virtual void loadImage();
                static ITexture* setaImagem;
                virtual void mouseCollision(); //Responde se o mouse está dentro ou se o objeto está no retângulo de seleção (muda a cor também)
                Vertice* origem,* destino;
		eTipoAresta tipo; //Adjacente por default
		//static Imagem setaImagem;
};

#endif // ARESTA_H
