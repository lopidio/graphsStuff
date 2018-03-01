#ifndef MOUSE_H
#define MOUSE_H

#include <irrlicht.h>
#include "Principal.h"

using namespace irr;
using namespace gui;
using namespace core;


class Mouse
{
        friend class Principal;
        public:
                Mouse(ICursorControl*);
                virtual ~Mouse();
		void update();
		const position2df& getPosicao() const;
		const position2df& getMovimento() const;
		const rectf* getRetangulo() const;
		bool isLeftButtonDown() const;
		bool isRightButtonDown() const;
                void setMouseOcupado(bool insideGrafoObjeto_); //Os GrafoObjetos utilizam, para que os outros GrafoObjetos tomem conhecimento
		bool isMouseOcupado() const; //A partir disso os GrafoObjetos sabem se se movem ou não.
		bool onClick() const; //True no primeiro instante do clique
		bool onRightClick() const; //True no primeiro instante do clique
		bool onMiddleButtonClick() const;
		bool isOver() const;
		bool setOver(bool);
		bool onRelease() const;
		bool getControl() const;
		void draw() const;
		bool isBlocked() const;
        protected:
        private:
                void block();
                void unBlock();
                bool botaoMeio, botaoMeioAnterior;
                bool botaoEsquerdo, botaoEsquerdoAnterior;
                bool botaoDireito, botaoDireitoAnterior;
                bool over, ctrl, bloqueado;
                void atualizarEvento(const SEvent::SMouseInput&);
		ICursorControl* mouse; //Ponteiro para o mouse da API
		position2df posicaoAnterior;
		position2df *pontoInicialRetangulo; //Quando “seleção” estiver habilitado
		bool mouseOcupado; //Mudar o cursor, false em cada iteração
};

#endif // MOUSE_H
