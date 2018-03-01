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


#include "Animacao.h"
#include "Principal.h"

Animacao::Animacao()
{
        stepCount = 0;
        animationTime = 1000;
        animando = false;
        loop = false;
        gravando = true;
}

Animacao::~Animacao()
{
        zerar();
}

/** @brief setAnimationTime
  *
  * @todo: document this function
  */
void Animacao::setAnimationTime(int newTime)
{
        animationTime = newTime;
}

/** @brief isRunning
  *
  * @todo: document this function
  */
bool Animacao::isRunning() const
{
        return animando;
}

/** @brief stop
  *
  * @todo: document this function
  */
void Animacao::stop()
{
        printf("Animacao::stop()\n");
        animando = false;
        stepCount = 0;
}

/** @brief resume
  *
  * @todo: document this function
  */
void Animacao::resume()
{
//        if (stepCount >= lista.size() - 1)
//                stepCount = 0;
        printf("Animacao::resume()\n");
        animando = true;
        lastTime = TIMER->getTime();
}

/** @brief size
  *
  * @todo: document this function
  */
int Animacao::size() const
{
        return lista.size();
}

/** @brief getStepCount
  *
  * @todo: document this function
  */
int Animacao::getStepCount() const
{
        return stepCount;
}

/** @brief setCountStep
  *
  * @todo: document this function
  */
void Animacao::setStepCount(int novo)
{
        if (novo >=0  && novo < (int)lista.size())
        {
                stepCount = novo;
//                if (abs(novo - stepCount) <= 1)
//                {
//                        if (lista[stepCount].action == eA_select)
//                                lista[stepCount].objeto->selecionar();
//                        else
//                                lista[stepCount].objeto->desselecionar();
//                }
        }
}



/** @brief pause
  *
  * @todo: document this function
  */
void Animacao::pause()
{
        printf("Animacao::pause()\n");
        animando = false;
}

/** @brief start
  *
  * @todo: document this function
  */
void Animacao::start()
{
        pararGravacao();
        printf("Animacao::start() tam:%d\n", lista.size());
        lastTime = TIMER->getTime();
        animando = true;
        stepCount = 0;
}

/** @brief deleteLastStep
  *
  * @todo: document this function
  */
void Animacao::deleteLastStep()
{
  //      printf("Animacao::delete()\n");
        if (lista.size())
        {
                lista.pop_back();
                if (stepCount >= (int)lista.size())
                        stepCount--;
        }
}

/** @brief addStep
  *
  * @todo: document this function
  */
void Animacao::addStep(GrafoObjeto* obj, eAction acao)
{
        if (!gravando)
                return;
   //     printf("Animacao::add(): %d\n", stepCount);
        animando = false;
        //Deletar todos que estão depois do passo atual
        for (unsigned int i = stepCount + 1; i < lista.size(); i++)
                deleteLastStep();
        stepCount++; //Reposiciona para que delete todas as casas futuras
        AnimationStep novo;
        novo.action = acao;
        novo.objeto = obj;
        lista.push_back(novo);
}

/** @brief update
  *
  * @todo: document this function
  */
void Animacao::update()
{
        if ((int)TIMER->getTime() - lastTime > animationTime && animando && lista.size() > 0) //in seconds
        {
                if (stepCount == 0) //reinicia toda a animação
                        zerarSelecoesEmUmStep();

                lastTime = TIMER->getTime();

                if (stepCount < (int)lista.size())
                {
                        if (lista[stepCount].action == eA_select)
                                lista[stepCount].objeto->selecionar();
                        else
                                lista[stepCount].objeto->desselecionar();

                        stepCount++;
                }
                if (stepCount >= (int)lista.size()) //Não pode ser else, pq o stepCount é incrementado
                {
                        stepCount = 0;
                        if (!loop)
                                animando=false;
                }
        }
        //printf("----------  Animacao::fim update()  %d\n", stepCount);
}

/** @brief setLooping
  *
  * @todo: document this function
  */
void Animacao::setLooping(bool loop_)
{
        printf("Animacao::setLooping: %d\n", loop_);
        loop = loop_;
}

/** @brief isResumeActive
  *
  * @todo: document this function
  */
bool Animacao::isResumeActive() const
{
        return !animando && stepCount != 0;
}

/** @brief isPauseActive
  *
  * @todo: document this function
  */
bool Animacao::isPauseActive() const
{
        return animando && stepCount != 0;
}

/** @brief pararGravacao
  *
  * @todo: document this function
  */
void Animacao::pararGravacao()
{
        gravando = false;
}

/** @brief comecarAGravar
  *
  * @todo: document this function
  */
void Animacao::comecarAGravar()
{
        printf("Animacao::comecarAGravar\n");
        gravando = true;
        zerar();
}

/** @brief isGravando
  *
  * @todo: document this function
  */
bool Animacao::isGravando() const
{
        return gravando;
}

/** @brief zerar
  *
  * @todo: document this function
  */
void Animacao::zerar()
{
        lista.clear();
        stepCount = 0;
}

/** @brief deleteAllReferences
  *
  * @todo: document this function
  */
void Animacao::deleteAllReferences(GrafoObjeto* obj)
{
        //Deleta todas as aparições de obj na lista de animação
        for (int i = 0; i < (int)lista.size(); i++)
        {
//                printf("End: %d\n", lista[i].objeto);
                if (lista[i].objeto == obj)
                {
                        printf("Animacao::deleteAllReference, size: %d\n", lista.size());
                        //printf("Deletou um da animacao\n");
                        lista.erase(lista.begin() + i);
                        stepCount = 0;
                        return deleteAllReferences(obj);
                }
        }
}

/** @brief zerarSelecoesEmUmStep
  *
  * @todo: document this function
  */
void Animacao::zerarSelecoesEmUmStep()
{
        pararGravacao();
        for (unsigned int i = 0; i < lista.size(); i++)
        {
                if (lista[i].action == eA_select)
                        lista[i].objeto->desselecionar(); //Desseleciona todos que um dia já foram selecionados
                        //O método desselecionar do GrafoObjeto previne qualquer erro
        }
        //Acha todos os grafoobjetos que estão selecionados e desseleciona
}

