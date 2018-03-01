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


#include "AnimationPlayer.h"
#include "Principal.h"

AnimationPlayer::AnimationPlayer(     gui::IGUIButton * rec_,
                                                                gui::IGUIButton * stop_,
                                                                gui::IGUIButton * playPause_,
                                                                gui::IGUIButton * loop_,
                                                                gui::IGUIScrollBar* progresso_,
                                                                IGUIScrollBar* velocidadeAnimacao_,
                                                                IGUIWindow* janela_)
{
        janela =  janela_;
        rec =  rec_;
        stop =  stop_;
        playPause =  playPause_;
        loop =  loop_;
        progresso =  progresso_;
        velocidadeAnimacao =  velocidadeAnimacao_;

        rec->setPressed(true);
        setVisivel(false);
        velocidadeAnimacao->setMax(2000);
        velocidadeAnimacao->setMin(200);
        velocidadeAnimacao->setPos(1000);
        velocidadeAnimacao->setSmallStep(100);
        velocidadeAnimacao->setLargeStep(500);
        progresso->setMax(0);
        progresso->setMin(0);
        progresso->setPos(0);
        progresso->setSmallStep(1);
        progresso->setLargeStep(5);
        //ctor
}

AnimationPlayer::~AnimationPlayer()
{
        //dtor
}


/** @brief setAnimacao
  *
  * @todo: document this function
  */
void AnimationPlayer::setAnimacao(Animacao* nova)
{
        animacaoCorrente = nova;
        atualizaBotoes();
        atualizarProgressoScroll();
        //Atualizar os estados dos botões
}

/** @brief update
  *
  * @todo: document this function
  */
void AnimationPlayer::update()
{
        if (!isVisivel())
        {
                rec->setPressed(false);
                animacaoCorrente->pararGravacao();
                return;
        }

        if (animacaoCorrente)
                animacaoCorrente->update();
        atualizaBotoes();
        atualizarProgressoScroll();
}

/** @brief atualizarScrolls
  *
  * @todo: document this function
  */
void AnimationPlayer::atualizarProgressoScroll()
{
        progresso->setEnabled(!animacaoCorrente->isRunning());
        progresso->setMax(animacaoCorrente->size() - 1);
        progresso->setPos(animacaoCorrente->getStepCount());
}

/** @brief atualizaBotoes
  *
  * @todo: document this function
  */
void AnimationPlayer::atualizaBotoes()
{
        if (animacaoCorrente->isRunning())
                rec->setPressed(false);
}




/** @brief isVisivel
  *
  * @todo: document this function
  */
bool AnimationPlayer::isVisivel() const
{
        return janela->isVisible();
}

/** @brief setVisivel
  *
  * @todo: document this function
  */
void AnimationPlayer::setVisivel(bool b)
{
        janela->setVisible(b);
}

/** @brief getMaxIdObject
  *
  * @todo: document this function
  */
int AnimationPlayer::getMaxIdObject() const
{
        return APCount;
}

/** @brief getMinIdObject
  *
  * @todo: document this function
  */
int AnimationPlayer::getMinIdObject() const
{
        return APProgresso;
}

/** @brief onEvent
  *
  * @todo: document this function
  */
void AnimationPlayer::onEvent(int id, gui::EGUI_EVENT_TYPE tipo)
{
        if (tipo == EGET_BUTTON_CLICKED) //Evento dos botões
        {
                switch (id)
                {
                        case APRec:
                                        if (!animacaoCorrente->isGravando())
                                                animacaoCorrente->comecarAGravar();
                                        else
                                                animacaoCorrente->pararGravacao();
                                break;
                        case APPlayPause:
                                        if (animacaoCorrente->isRunning())
                                                animacaoCorrente->pause();
                                        else
                                                animacaoCorrente->resume();
                                break;
                        case APStop:
                                        if (animacaoCorrente->isRunning())
                                                animacaoCorrente->stop();
                                break;
                        case APLoop:
                                        animacaoCorrente->setLooping(loop->isPressed());
                                break;

                }
        }
        else if (tipo == EGET_SCROLL_BAR_CHANGED )
        {
                switch(id)
                {
                        case APVelocidade:
                                        animacaoCorrente->setAnimationTime(velocidadeAnimacao->getPos());
                                break;
//                        case APJanela:
//                                break;
                        case APProgresso:
                                        animacaoCorrente->setStepCount(progresso->getPos());
                                break;
                }
        }
}


