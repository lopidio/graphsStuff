#ifndef ANIMACAO_H
#define ANIMACAO_H

#include <iostream>
#include <Irrlicht.h>
#include "GrafoObjeto.h"
#include <vector>
//#include <list>
#include "GrafoObjeto.h"


using namespace irr;
using namespace video;
using namespace gui;
using namespace std;

enum eAction {eA_select, eA_deselect};

class Animacao
{
        public:
                Animacao();
                virtual ~Animacao();
                void update();
                void addStep(GrafoObjeto*, eAction);
                void start();
                void pause();
                void resume();
                void stop();
                void setStepCount(int );
                bool isRunning() const;
                void setAnimationTime(int);
                bool isPauseActive() const;
                bool isResumeActive() const;
                void setLooping(bool);
                bool isGravando() const;
                void comecarAGravar();
                void pararGravacao();
                void zerarSelecoesEmUmStep();
                void zerar();
                void deleteAllReferences(GrafoObjeto*);
                int getStepCount() const;
                int size() const;
        protected:
        private:
                struct AnimationStep
                {
                        GrafoObjeto* objeto;
                        eAction action;
                };
                vector<AnimationStep> lista;
                int stepCount;
                int lastTime;
                int animationTime;
                bool animando;
                bool loop;
                bool gravando;
                void deleteLastStep();
};

#endif // ANIMACAO_H
