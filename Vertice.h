#ifndef VERTICE_H
#define VERTICE_H
#include <Irrlicht.h>
#include <math.h>
#include "Principal.h"
#include "GrafoObjeto.h"
#include "Aresta.h"

#define RADIUS 15.f

using namespace irr;
using namespace video;
using namespace core;


class Vertice: public GrafoObjeto
{
        //friend class Vertice;
        public:
                Vertice(int, position2df&);
                Vertice(int, FILE*);
                Vertice (int, Vertice*); //Construtor de cópia
                virtual ~Vertice();
		float getRaio() const;
		void setId(int id_);
		int getId() const;
                virtual void update();
                virtual void draw() const;
                virtual bool isCriado() const; //Responde se foi completamente criado
		const position2df& getPosicao() const; //
		virtual void editarValor(const wstring& valor_); //Label ou Custo
                virtual void salvar(FILE*, int) const;
		void mover(float offsetX, float offsetY);
                virtual bool isInsideRetangulo() const;
        private:
                virtual void loadImage();
                static ITexture* image;
                void mouseCollision();
                position2df posicao;
//                const float raio;
                int id;
};

#endif // VERTICE_H
