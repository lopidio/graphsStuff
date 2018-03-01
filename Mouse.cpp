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


#include "Mouse.h"




/** @brief Mouse
  *
  * @todo: document this function
  */
 Mouse::Mouse(ICursorControl* mouse_)
{
        mouse = mouse_;
        botaoEsquerdo = botaoEsquerdoAnterior = false;
        botaoDireito = botaoDireitoAnterior = false;
        botaoMeio = botaoMeioAnterior = false;
        mouseOcupado = false;
        over = false;
        bloqueado = false;
        pontoInicialRetangulo = NULL;
}


/** @brief ~Mouse
  *
  * @todo: document this function
  */
 Mouse::~Mouse()
{
        delete pontoInicialRetangulo;
        pontoInicialRetangulo = NULL;
}

/** @brief onRelease
  *
  * @todo: document this function
  */
bool Mouse::onRelease() const
{
        return !isLeftButtonDown() && botaoEsquerdoAnterior;
}

/** @brief onClick
  *
  * @todo: document this function
  */
bool Mouse::onClick() const
{
        return isLeftButtonDown() && !botaoEsquerdoAnterior;
}

/** @brief onRightClick
  *
  * @todo: document this function
  */
bool Mouse::onRightClick() const
{
        return isRightButtonDown() && !botaoDireitoAnterior;
}



/** @brief isMouseOcupado
  *
  * @todo: document this function
  */
bool Mouse::isMouseOcupado() const
{
        return mouseOcupado;
}

/** @brief setMouseOcupado
  *
  * @todo: document this function
  */
void Mouse::setMouseOcupado(bool insideGrafoObjeto_)
{
        mouseOcupado = insideGrafoObjeto_;
}

/** @brief getRetangulo
  *
  * @todo: document this function
  */
const rectf* Mouse::getRetangulo() const
{
        return (pontoInicialRetangulo)? (&core::rectf(pontoInicialRetangulo->X, pontoInicialRetangulo->Y,
                                                            posicaoAnterior.X, posicaoAnterior.Y)):NULL;
}

/** @brief getMovimento
  *
  * @todo: document this function
  */
const position2df & Mouse::getMovimento() const
{
        position2df retorno = posicaoAnterior;
        retorno.X -= getPosicao().X;
        retorno.Y -= getPosicao().Y;
        return retorno;
}

/** @brief update
  *
  * @todo: document this function
  */
void Mouse::update()
{
        if (onClick() && MENU != mO_criar && MENU != mO_deletar && MENU != mO_count && !over){
                pontoInicialRetangulo = new position2df(posicaoAnterior);
        }
        if (!isLeftButtonDown() && pontoInicialRetangulo)
        {
                delete pontoInicialRetangulo;
                pontoInicialRetangulo = NULL;
        }
        botaoMeioAnterior = botaoMeio;
        botaoEsquerdoAnterior = botaoEsquerdo;
        botaoDireitoAnterior = botaoDireito;
        posicaoAnterior = getPosicao();
}

/** @brief atualizarEvento
  *
  * @todo: document this function
  */
void Mouse::atualizarEvento(const SEvent::SMouseInput& mouse_)
{
        EMOUSE_INPUT_EVENT evento = mouse_.Event;
//         printf("tipo: %d\n", evento);
        ctrl = mouse_.Control;
        switch(evento)
        {
                case EMIE_LMOUSE_PRESSED_DOWN:
                                botaoEsquerdo = true;
                        break;

                case EMIE_LMOUSE_LEFT_UP:
                                botaoEsquerdo = false;
                        break;
                case EMIE_RMOUSE_PRESSED_DOWN:
                                botaoDireito = true;
                        break;

                case EMIE_RMOUSE_LEFT_UP:
                                botaoDireito = false;
                        break;

                case EMIE_MMOUSE_PRESSED_DOWN:
                                botaoMeio = true;
                        break;
                case EMIE_MMOUSE_LEFT_UP:
                                botaoMeio = false;
                        break;
                case EMIE_MOUSE_WHEEL:
                           //     Vertice::RADIUS +=  (mouse_.Wheel);
                        break;
                default:
                        break;
        }
}

/** @brief isLeftButtonDown
  *
  * @todo: document this function
  */
bool Mouse::isLeftButtonDown() const
{
        return bloqueado? false : botaoEsquerdo;
}

/** @brief isRightButtonDown
  *
  * @todo: document this function
  */
bool Mouse::isRightButtonDown() const
{
        return bloqueado? false : botaoDireito;
}


/** @brief getPosicao
  *
  * @todo: document this function
  */
const position2df & Mouse::getPosicao() const
{
        position2df posicaoMouse(mouse->getPosition().X, mouse->getPosition().Y);
        return posicaoMouse;
}

/** @brief setOver
  *
  * @todo: document this function
  */
bool Mouse::setOver(bool mouseOver_)
{
        return over = mouseOver_;
}

/** @brief isOver
  *
  * @todo: document this function
  */
bool Mouse::isOver() const
{
        return over;
}

/** @brief getControl
  *
  * @todo: document this function
  */
bool Mouse::getControl() const
{
        return ctrl;
}

/** @brief unBlock
  *
  * @todo: document this function
  */
void Mouse::unBlock()
{
        bloqueado = false;
}

/** @brief block
  *
  * @todo: document this function
  */
void Mouse::block()
{
        bloqueado = true;
}

/** @brief draw
  *
  * @todo: document this function
  */
void Mouse::draw() const
{
     //   printf("Mouse::draw %d, %d\n", mouse->getPosition().X,mouse->getPosition().Y);
        //printf("%d\n", isBlocked());
        if (pontoInicialRetangulo)
        {
                VIDEO->draw2DRectangleOutline (core::recti(pontoInicialRetangulo->X, pontoInicialRetangulo->Y,
                                                            posicaoAnterior.X, posicaoAnterior.Y));
        }
}

/** @brief isBlocked
  *
  * @todo: document this function
  */
bool Mouse::isBlocked() const
{
        return bloqueado;
}

/** @brief onMiddleButtonClick
  *
  * @todo: document this function
  */
bool Mouse::onMiddleButtonClick() const
{
        return !botaoMeio && botaoMeioAnterior;
}
