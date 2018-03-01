#ifndef GRAFOOBJETO_H
#define GRAFOOBJETO_H
#include <Irrlicht.h>
#include <iostream>

using namespace irr;
using namespace video;
using namespace std;

enum eTipoGrafo {tG_vertice, tG_aresta};
class GrafoObjeto
{
        public:
                GrafoObjeto();
                GrafoObjeto(eTipoGrafo);
                virtual void update() = 0;
                virtual void draw() const = 0;
		virtual bool isSelecionado() const; //Quando t� selecionado, ele se move com as teclas ou com o mouse
		bool isMarcadoParaRemocao() const;
		void desselecionar();
		void selecionar();
		void setCores(const SColor& cor, const SColor& corTexto);
		void marcarParaRemover();
                virtual bool isCriado() const = 0; //Responde se foi completamente criado
		virtual const core::position2d<float>& getPosicao() const = 0; //
		virtual void editarValor(const wstring& valor_) = 0; //Label ou Custo
		const wstring& getValor() const; //Label ou Custo
		eTipoGrafo getTipo() const;
		virtual void salvar(FILE*, int) const = 0;
                virtual bool isInsideRetangulo() const = 0;
        protected:
                virtual void loadImage() = 0;
                SColor cor, corTexto;
                wstring valor;
                virtual void mouseCollision() = 0; //Responde se o mouse est� dentro ou se o objeto est� no ret�ngulo de sele��o (muda a cor tamb�m)
                bool selecionado; //muda cor na impress�o, opera��es s�o em cima dos selecionados
                bool mouseOver;
                void onClick();
                void verificaRetangulo();
        private:
                eTipoGrafo tipoGrafo;
                bool paraRemover;
};

#endif // GRAFOOBJETO_H
