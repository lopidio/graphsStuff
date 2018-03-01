#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include <irrlicht.h>
#include "Animacao.h"

using namespace irr;
using namespace video;
using namespace gui;

enum APItems {APProgresso = 400, APRec, APPlayPause, APStop , APLoop, APVelocidade, APJanela, APCount};

class AnimationPlayer
{
        public:
                AnimationPlayer(        gui::IGUIButton * rec,
                                                        gui::IGUIButton * stop,
                                                        gui::IGUIButton * playPause,
                                                        gui::IGUIButton * loop,
                                                        gui::IGUIScrollBar* progresso,
                                                        IGUIScrollBar* velocidadeAnimacao,
                                                        IGUIWindow* janela);
                virtual ~AnimationPlayer();
                void update(); //Atualizar GrafoObjeto a ser selecionado!
                void setAnimacao(Animacao*);
                int getMinIdObject() const;
                int getMaxIdObject() const;
                void setVisivel(bool);
                bool isVisivel() const;
                void onEvent(int id, gui::EGUI_EVENT_TYPE tipo);
        protected:
        private:
                void atualizaBotoes();
                void atualizarProgressoScroll();
                Animacao* animacaoCorrente;
                gui::IGUIButton * rec;
                gui::IGUIButton * stop;
                gui::IGUIButton * playPause;
                gui::IGUIButton * loop;
                gui::IGUIScrollBar* progresso;
                IGUIScrollBar* velocidadeAnimacao;
                IGUIWindow* janela;
};

#endif // ANIMATIONPLAYER_H
