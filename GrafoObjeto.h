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
		virtual bool isSelecionado() const; //Quando tá selecionado, ele se move com as teclas ou com o mouse
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
                virtual void mouseCollision() = 0; //Responde se o mouse está dentro ou se o objeto está no retângulo de seleção (muda a cor também)
                bool selecionado; //muda cor na impressão, operações são em cima dos selecionados
                bool mouseOver;
                void onClick();
                void verificaRetangulo();
        private:
                eTipoGrafo tipoGrafo;
                bool paraRemover;
};

#endif // GRAFOOBJETO_H
