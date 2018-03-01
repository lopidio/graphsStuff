#ifndef MENUEDITAR_H
#define MENUEDITAR_H

#include <iostream>
#include <Irrlicht.h>
#include <sstream>
#include "GrafoObjeto.h"
#include <list>

using namespace irr;
using namespace video;
using namespace gui;
using namespace std;

class GrafoObjeto;

class MenuEditar
{
        public:
                MenuEditar();
                MenuEditar(irr::gui::IGUIWindow* janela_, irr::gui::IGUIEditBox* campoTexto_); //Procura e mapeia a janela e o compo de texto
                virtual ~MenuEditar();
                void okButton();
                void textChangedEvent();
                void update(); //Atualizar GrafoObjeto a ser selecionado!
                void iniciar(std::list<GrafoObjeto*> selecionados_); //Não pode ser referência
                void terminar();
                bool estaAtivo() const;
        protected:
        private:
                void esvaziarLista();
                IGUIWindow* janela;
                IGUIEditBox* campoTexto;
                std::list<GrafoObjeto*> selecionados;
};

#endif // MENUEDITAR_H
