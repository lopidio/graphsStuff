/* *********************************************/
/********************************************  /
//
// @date -
//
// Project -
//
//  if (!bug)
//	@author Lopídio (I love America)
//  else
//	@author Unkwonn
//
//
//  Good Luck!
** *********************************/
/* *******************************/


#include "MenuEditar.h"
#include "Vertice.h"

MenuEditar::MenuEditar()
{
        //ctor
}

MenuEditar::MenuEditar(irr::gui::IGUIWindow* janela_, irr::gui::IGUIEditBox* campoTexto_) //Procura e mapeia a janela e o compo de texto //Procura e mapeia a janela e o compo de texto
{
        janela = janela_;
        janela->setDraggable(true);
        campoTexto = campoTexto_;
}


MenuEditar::~MenuEditar()
{
        //dtor
}

/** @brief esvaziarLista
  *
  * @todo: document this function
  */
void MenuEditar::esvaziarLista()
{
        while (selecionados.size() > 0)
        {
                selecionados.remove(selecionados.front());
        }
}

/** @brief iniciar
  *
  * @todo: document this function
  */
void MenuEditar::iniciar(std::list<GrafoObjeto*> selecionados_)
{
        esvaziarLista();
        selecionados = selecionados_;
        if (!selecionados.size())
        {
                terminar();
        }
        else
                update();
}

/** @brief update
  *
  * @todo: document this function
  */
void MenuEditar::update()
{
        GrafoObjeto*& atual = selecionados.front();

        wstring titleBar;
        titleBar = atual->getTipo() == tG_aresta? L"Aresta: " : L"Vertice: ";
        titleBar.append(atual->getValor());
        janela->setText(titleBar.c_str());


        position2di posicao; //Posição em que a jenala vai aparecer na tela
        posicao.X =atual->getPosicao().X;
        posicao.Y = atual->getPosicao().Y;
//printf("Editar %d, %d\n", posicao.X,posicao.Y);
        posicao.Y += posicao.Y > (int)VIDEO->getScreenSize().Height/2 ?
                                        - RADIUS - janela->getAbsoluteClippingRect().getHeight() :
                                        + RADIUS;
        janela->setRelativePosition(posicao);
        janela->setVisible(true);
}

/** @brief textChangedEvent
  *
  * @todo: document this function
  */
void MenuEditar::textChangedEvent()
{
        if (selecionados.size() && janela->isVisible())
        {
                selecionados.front()->editarValor(campoTexto->getText());
        }
}

/** @brief setarVisibilidade
  *
  * @todo: document this function
  */
void MenuEditar::terminar()
{
        if (janela->isVisible())
        {
                janela->setVisible(false);
                esvaziarLista();
        }
}

/** @brief okButton
  *
  * @todo: document this function
  */
void MenuEditar::okButton()
{
        wstring texto = campoTexto->getText();
        if (texto.size() > 0)
                selecionados.front()->editarValor(texto);
        campoTexto->setText(L"");
        selecionados.remove(selecionados.front());

        if (selecionados.size() == 0) //Se não existir mais o que editar
                terminar();
        else
                update();
}

/** @brief estaAtivo
  *
  * @todo: document this function
  */
bool MenuEditar::estaAtivo() const
{
        return selecionados.size();
}

