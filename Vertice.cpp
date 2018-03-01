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


#include "Vertice.h"

ITexture* Vertice::image = NULL;

Vertice::Vertice(int  id_, position2df& posicao_): GrafoObjeto(tG_vertice)
{
        loadImage();
        id = id_;
        posicao = posicao_;
        valor = MAIN->StringToWString(MAIN->IntToString(id));
}
/** @brief Vertice
  *
  * @todo: document this function
  */
 Vertice::Vertice(int id_, FILE* fp): GrafoObjeto(tG_vertice)
{
     //   printf("Lendo vertice\n");
        char valor_[20];
        fscanf(fp, "%f %f %s\n", &posicao.X, &posicao.Y, &valor_);
        id = id_;
        valor = Principal::StringToWString(valor_);
        loadImage();
}

/** @brief Vertice
  *
  * @todo: document this function
  */
 Vertice::Vertice(int id_, Vertice* outro): GrafoObjeto(tG_vertice)
{
        loadImage();
        id = id_;
        posicao = outro->posicao;
        valor = outro->valor;
}



Vertice::~Vertice()
{
        printf("DESTRUIU VERTICE\n");
        //Atualiza o estado do mouse
//        position2df pMouse = MOUSE->getPosicao();
//        bool mouseOverNow = pow(posicao.X - pMouse.X,2) + pow(posicao.Y- pMouse.Y, 2) <= raio*raio;
//        if (!mouseOver && mouseOverNow)
//                MOUSE->setOver(true);
        if (mouseOver)
                MOUSE->setOver(false);
}


/** @brief mover
  *
  * @todo: document this function
  */
void Vertice::mover(float offsetX, float offsetY)
{
        posicao.X -= offsetX;
        posicao.Y -= offsetY;
}

/** @brief draw
  *
  * @todo: document this function
  */
void Vertice::draw() const
{
//        printf("Vertice::draw: %d \n", image);
        SColor corNova = (selecionado)? cor : SColor(255,255,255,0);
        if (mouseOver)
                corNova = SColor(255,0,0,128);
        if (image)
                VIDEO->draw2DImage (image, position2d<int>(posicao.X - RADIUS,posicao.Y - RADIUS), rect<int>(0,0,30,30),
                                    0, corNova, true);
//        printf("Vertice::draw4\n");
        FONTE->draw(valor.c_str(), core::rect<s32>(posicao.X - RADIUS,posicao.Y - RADIUS,posicao.X + RADIUS,posicao.Y + RADIUS),
					video::SColor(255,0,0,0), true, true);
}

/** @brief update
  *
  * @todo: document this function
  */
void Vertice::update()
{
        mouseCollision();
        dimension2d<u32> tela = VIDEO->getScreenSize();
        if (posicao.X < 0)
                posicao.X = 0;
        if (posicao.X > tela.Width)
                posicao.X = tela.Width;
        if (posicao.Y < 10)
                posicao.Y = 10;
        if (posicao.Y > tela.Height)
                posicao.Y = tela.Height;
}

/** @brief getId
  *
  * @todo: document this function
  */
int Vertice::getId() const
{
        return id;
}

/** @brief setId
  *
  * @todo: document this function
  */
void Vertice::setId(int id_)
{
        if (Principal::StringToInt(Principal::WStringToString(valor)) == id)
                valor = MAIN->StringToWString(MAIN->IntToString(id_));
        id = id_;
}

/** @brief getRaio
  *
  * @todo: document this function
  */
float Vertice::getRaio() const
{
        return RADIUS;
}
/** @brief getPosicao
  *
  * @todo: document this function
  */
const position2df& Vertice::getPosicao() const
{
        return posicao;
}

/** @brief isCriado
  *
  * @todo: document this function
  */
bool Vertice::isCriado() const
{
        return valor.size() > 0;
}

/** @brief editarValor
  *
  * @todo: document this function
  */
void Vertice::editarValor(const wstring& valor_)
{
        valor = valor_;
}


/** @brief mouseCollision
  *
  * @todo: document this function
  */
void Vertice::mouseCollision()
{
        //Verifica se o mouse está sobre o vértice
        position2df pMouse = MOUSE->getPosicao();
        bool mouseOverNow = (pow(posicao.X - pMouse.X,2) + pow(posicao.Y- pMouse.Y, 2) < RADIUS*RADIUS) &&(!MOUSE->isOver() || mouseOver); //Pra estar em cima de mim não pode tá em cima de nenhum outro
        if (!mouseOver && mouseOverNow)
        {
                MOUSE->setOver(true);
                mouseOver = true;
        }
        if (mouseOver && !mouseOverNow && !MOUSE->isLeftButtonDown()) //A última condição é pra evitar que o mouse corra mto rápido
        {
                MOUSE->setOver(false);
                mouseOver = false;
        }

        if (MOUSE->isRightButtonDown())
                desselecionar();

        if (MOUSE->onClick())
                onClick();

        verificaRetangulo();

        //Menu MOVER
        if (selecionado && MOUSE->isLeftButtonDown() && MENU == mO_mover && MOUSE->isOver() && !MOUSE->getRetangulo())
        {
                position2df ponto = MOUSE->getMovimento();
                mover(ponto.X, ponto.Y);
        }

        if (selecionado && MOUSE->isLeftButtonDown() && MENU == mO_deletar)
        {
                MAIN->deleteVertice(this);
        }
}

/** @brief salvar
  *
  * @todo: document this function
  */
void Vertice::salvar(FILE* fp, int inutil) const
{
        fprintf(fp, "%f %f %s\n",posicao.X, posicao.Y, Principal::WStringToString(valor).c_str());
}

/** @brief LoadImage
  *
  * @todo: document this function
  */
void Vertice::loadImage()
{
        if (!image)
        {
                image = VIDEO->getTexture("Resources/Vertice.PNG");
                VIDEO->makeColorKeyTexture(image, core::position2d<s32>(0,0));
        }
}

/** @brief isInsideRetangulo
  *
  * @todo: document this function
  */
bool Vertice::isInsideRetangulo() const
{
        if (MOUSE->getRetangulo())
        {

                const rectf* r = MOUSE->getRetangulo();
                position2df UL = r->UpperLeftCorner;
                position2df LR = r->LowerRightCorner;

                float esq = min(UL.X, LR.X);
                float cim = min(UL.Y, LR.Y);
                float dir = max(UL.X, LR.X);
                float baixo= max(UL.Y, LR.Y);
                rectf novo(esq, cim, dir, baixo);
                //printf("%f, %f               %f, %f \n", esq,cim, esq + r->getWidth(), cim + r->getHeight());
                return novo.isPointInside(posicao);
        }
        return false;
}


