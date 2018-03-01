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


#include "Aresta.h"

bool proximoAoIntervalo(float x, float a, float b)
{
        if (a < b)
                return x > a - ERROR && x < b + ERROR;
        return x > b - ERROR && x < a + ERROR;
}

ITexture* Aresta::setaImagem = NULL;

Aresta::Aresta(Vertice * origem_, Vertice * destino_): GrafoObjeto(tG_aresta), origem(origem_), destino(destino_)
{
        tipo = tA_unidirecional;
        destino->desselecionar();
        loadImage();
}


Aresta::~Aresta()
{
      //  printf("destruiu aresta\n");
        if (mouseOver)
                MOUSE->setOver(false);
}

void drawSuperLine(const vector2d<int>& ori, const vector2d<int>& dest, const SColor& cor)
{
        VIDEO->draw2DLine (ori, dest, cor); //Primeira linha
        VIDEO->draw2DLine (vector2d<int>(ori.X +1, ori.Y +1), vector2d<int>(dest.X+1, dest.Y+1), cor); //Deixa a linha mais grossa
        VIDEO->draw2DLine (vector2d<int>(ori.X +1, ori.Y +1), vector2d<int>(dest.X-1, dest.Y-1), cor); //Deixa a linha mais grossa ainda
        VIDEO->draw2DLine (vector2d<int>(ori.X -1, ori.Y +1), vector2d<int>(dest.X+1, dest.Y+1), cor); //Deixa a linha mais grossa ainda
}

/** @brief draw
  *
  * @todo: document this function
  */
void Aresta::draw() const
{
        SColor corNova = (selecionado)? cor : SColor(255,0,0,0);
        if (mouseOver)
                corNova = SColor(255,0,0,128);
        vector2d<int> ori(origem->getPosicao().X, origem->getPosicao().Y);
        vector2d<int> dest(destino->getPosicao().X, destino->getPosicao().Y);
        drawSuperLine (ori, dest, corNova); //Primeira linha
//printf("Aresta draw %f, %f\n", getPosicao().X,getPosicao().Y);

        FONTE->draw(valor.c_str(), core::rect<s32>(getPosicao().X - 10,getPosicao().Y - 10,getPosicao().X + 10,getPosicao().Y + 10),
					video::SColor(255,255,255,255), true, true);

        if (tipo == tA_unidirecional)
        {
                f64 alfa;
                float numerador = -(destino->getPosicao().Y - origem->getPosicao().Y);
                float denominador = destino->getPosicao().X - origem->getPosicao().X;
                if (denominador == 0)
                        denominador = 0.00000001f; //Um valor bem próximo de 0
                alfa = atan(numerador/denominador);

                //Ajeitando o quadrante correto
                if (denominador < 0 )
                        alfa += M_PI;
                else if (numerador < 0)
                        alfa += 2*M_PI;
                alfa = 2*M_PI - alfa;

                //Cria os pontos
                vector2d<int> ponto;
                ponto.X = destino->getPosicao().X - destino->getRaio()*cos(alfa);
                ponto.Y = destino->getPosicao().Y - destino->getRaio()*sin(alfa);

                vector2d<int> pontoS1;
                pontoS1.X = ponto.X -  round ((10)*cos(alfa+M_PI_4));
                pontoS1.Y = ponto .Y-  round ((10)*sin(alfa+M_PI_4));
                vector2d<int> pontoS2;
                pontoS2.X = ponto.X -  round ((10)*cos(alfa-M_PI_4));
                pontoS2.Y = ponto.Y -  round ((10)*sin(alfa-M_PI_4));

                //Desenha
                drawSuperLine(pontoS1, ponto, corNova);
                drawSuperLine(pontoS2, ponto, corNova);
        }

}

/** @brief update
  *
  * @todo: document this function
  */
void Aresta::update()
{
        mouseCollision();
}

/** @brief mouseCollision
  *
  * @todo: document this function
  */
void Aresta::mouseCollision()
{
        position2df pMouse = MOUSE->getPosicao();
        float distancia = ERROR;
        vector2d<int> pontoOrigem;
        vector2d<int> pontoDestino;
        { //Calcula os pontos extremos visíveis (que não são cobertos pelos vérticves)
                f64 alfa;
                float numerador = -(destino->getPosicao().Y - origem->getPosicao().Y);
                float denominador = destino->getPosicao().X - origem->getPosicao().X;
                if (denominador == 0)
                        denominador = 0.00000001f; //Um valor bem próximo de 0
                alfa = atan(numerador/denominador);

                //Ajeitando o quadrante correto
                if (denominador < 0 )
                        alfa += M_PI;
                else if (numerador < 0)
                        alfa += 2*M_PI;
                alfa = 2*M_PI - alfa;

                //Cria os pontos
                pontoDestino.X = destino->getPosicao().X - destino->getRaio()*cos(alfa);
                pontoDestino.Y = destino->getPosicao().Y - destino->getRaio()*sin(alfa);
                pontoOrigem.X = origem->getPosicao().X + origem->getRaio()*cos(alfa);
                pontoOrigem.Y = origem->getPosicao().Y + origem->getRaio()*sin(alfa);
        }
        if (proximoAoIntervalo(pMouse.X, pontoOrigem.X, pontoDestino.X) &&
                                                proximoAoIntervalo(pMouse.Y, pontoOrigem.Y, pontoDestino.Y))
        {
                //Calculando a equação geral da reta
                float a = origem->getPosicao().Y - destino->getPosicao().Y;
                float b = destino->getPosicao().X - origem->getPosicao().X;
                float c = origem->getPosicao().X*destino->getPosicao().Y - destino->getPosicao().X*origem->getPosicao().Y;
                float numerador = abs(a*pMouse.X + b*pMouse.Y + c);
                float denominador = sqrt(a*a + b*b);
                distancia = numerador/denominador;
        }

        //Verifica se o mouse está sobre a aresta
        bool mouseOverNow = (distancia < ERROR) &&(!MOUSE->isOver() || mouseOver);
        //Pra estar em cima de mim não pode tá em cima de nenhum outro;
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
    //    mouseOver = mouseOverNow;

        if (MOUSE->onClick())
        {
                onClick(); //método da classe pai
        }

        verificaRetangulo();

        if (selecionado && MOUSE->isLeftButtonDown() && MENU == mO_deletar)
                MAIN->deleteAresta(this);
        if (mouseOver && MOUSE->onRightClick())
                mudarTipo();
}

/** @brief editarValor
  *
  * @todo: document this function
  */
void Aresta::editarValor(const wstring& valor_)
{
        valor = Principal::StringToWString(Principal::IntToString(Principal::StringToInt(Principal::WStringToString(valor_))));
}

/** @brief getPosicao
  *
  * @todo: document this function
  */
const position2df & Aresta::getPosicao() const
{
        position2df retorno;
        retorno.X = (origem->getPosicao().X + destino->getPosicao().X)/2;
        retorno.Y = (origem->getPosicao().Y + destino->getPosicao().Y)/2;
        return retorno;
        //Retorna o ponto médio dos vértices
}

/** @brief isCriado
  *
  * @todo: document this function
  */
bool Aresta::isCriado() const
{
        return valor.size() > 0;
}

/** @brief getFloatValor
  *
  * @todo: document this function
  */
float Aresta::getFloatValor() const
{
        return  MAIN->StringToFloat(MAIN->WStringToString(valor));
}



/** @brief operator==
  *
  * @todo: document this function
  */
bool Aresta::operator==(const Aresta &outra) const
{
        if (origem->getId() == outra.origem->getId() && destino->getId() == outra.destino->getId())
                return true;
        if (destino->getId() == outra.origem->getId() && origem->getId() == outra.destino->getId())
                return true;

        return false;
}

/** @brief eDoVertice
  *
  * @todo: document this function
  */
bool Aresta::eDoVertice(const Vertice* vertice)
{
        if (vertice)
        {
                return (origem->getId() == vertice->getId() || destino->getId() == vertice->getId());
        }
        return false;
}

/** @brief getVerticeDestino
  *
  * @todo: document this function
  */
const Vertice* Aresta::getVerticeDestino() const
{
        return destino;
}

/** @brief getVerticeOrigem
  *
  * @todo: document this function
  */
const Vertice* Aresta::getVerticeOrigem() const
{
        return origem;
}

/** @brief salvar
  *
  * @todo: document this function
  */
void Aresta::salvar(FILE* fp, int origemId) const
{
        std::string novoValor =  Principal::WStringToString(valor).c_str();
        if (novoValor.size() == 0)
                novoValor.append("0");
        int idImpresso = destino->getId() == origemId ? origem->getId(): destino->getId(); //Caso seja bidirecional também
        fprintf(fp, "%d %s ", idImpresso, novoValor.c_str());
}

/** @brief mudarTipo
  *
  * @todo: document this function
  */
void Aresta::mudarTipo()
{
        tipo = (tipo == tA_bidirecional)? tA_unidirecional: tA_bidirecional;
        if (tipo == tA_unidirecional)
        {
                Vertice* aux = origem;
                origem = destino;
                destino = aux;
        }
        MAIN->atualizarMatriz();
}

/** @brief isBidirecional
  *
  * @todo: document this function
  */
bool Aresta::isBidirecional() const
{
        return tipo == tA_bidirecional;
}

/** @brief isInsideRetangulo
  *
  * @todo: document this function
  */
bool Aresta::isInsideRetangulo() const
{
        return origem->isInsideRetangulo() && destino->isInsideRetangulo();
}

/** @brief unLoadImage
  *
  * @todo: document this function
  */
void Aresta::loadImage()
{
        if (!setaImagem)
        {
//                setaImagem = VIDEO->getTexture("Resources/Seta.PNG");
//                VIDEO->makeColorKeyTexture(setaImagem, core::position2d<s32>(0,0));
        }
}
