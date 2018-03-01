#ifndef PRINCIPAL_H
#define PRINCIPAL_H


#include <iostream>
#include <Irrlicht.h>
#include <sstream>
#include "Mouse.h"
#include "MenuEditar.h"
#include "GrafoObjeto.h"
#include <vector>
#include <list>
#include "Vertice.h"
#include "Grafo.h"
#include "Detalhes.h"
#include "Algoritmos.h"
#include "AnimationPlayer.h"


#define MAIN Principal::getInstance()
#define MOUSE MAIN->getMouse()
#define AMBIENTE MAIN->getAmbiente()
#define MENU MAIN->getMenuOpcao()
#define VIDEO MAIN->getVideo()
#define FONTE MAIN->getFonte()
#define TIMER MAIN->getTimer()
#define MAX_ABAS 10

using namespace irr;
using namespace video;
using namespace gui;
using namespace std;

class Vertice;
class Aresta;
class Mouse;
class Grafo;
class Detalhes;

enum eDialogType {dO_abrir, dO_salvar, dO_desconhecido};
enum eMenuOpcao {mO_criar, mO_selecao, mO_deletar,mO_mover, mO_editar, mO_detalhes, mO_count}; //mO_count = Nothing tb!
enum eGUIObject {gO_barraFerramenta = 20, gO_editarWindow, gO_editarCampoTexto, gO_editarOk,
                                gO_novoArquivo, gO_abrirArquivo, gO_salvarComoArquivo, gO_sair,
                                gO_exibirBarraFerramentas, gO_sobre, gO_salvarCampoTexto, gO_selecionarTudo, gO_desselecionarTudo,
                                gO_selecionarTodosVertices, gO_selecionarTodasArestas, gO_tocadorDeAnimacao, gO_detalhes = 200, gO_algoritmos};
class Principal: IEventReceiver
{
        public:
                virtual ~Principal();
                static Principal* getInstance();
                void run();
                ITimer* getTimer();
                IVideoDriver* getVideo() const;
                Mouse* getMouse() const;
                eMenuOpcao getMenuOpcao() const;
                IGUIEnvironment* getAmbiente() const;
                void nomeAbaModificado();

                void limparListaDeSelecao();
                void addGrafoALista(GrafoObjeto*);
                void deleteGrafoALista(GrafoObjeto*);
                void deleteAresta(Aresta*);
                void deleteVertice(Vertice*);
                void novaAbaComGrafo(Grafo*);
                const std::list<GrafoObjeto*>& getSelecionados() const;
                int numArestasDoVertice(int) const;
                int numVertices() const;
                bool isTodoGrafoSelecionado() const;
                Grafo* getGrafo() const;
                void atualizarMatriz();


                IGUIFont* getFonte() const;
                static void Draw2DImage(ITexture*  , rect<int> , position2d<int> , position2d<int> , f32 , vector2df , bool , SColor );
                static std::wstring StringToWString(const std::string&);
                static std::string WStringToString(const std::wstring&);
                static std::string FloatToString(float);
                static std::string IntToString(int);
                static float StringToFloat(const std::string&);
                static int StringToInt(const std::string&);
        protected:
                Principal();
        private:
                vector<Grafo*> grafos;
                Detalhes* detalhes;

                int abaAtual;
                eDialogType tipoDaDialogFile;
                Mouse* mouse;
                eMenuOpcao opcaoSelecionada;
                IGUIEnvironment* ambiente;
                IrrlichtDevice* device;
                IGUIFont* font;
                IGUITabControl* tabBar;
                MenuEditar* menuEditar;
                AnimationPlayer* animationPlayer;
                void tabBarEvent();
                void nomeAbaModificado(int);
                void executarAlgoritmo(int id);
                void menuItemSelecionado( IGUIContextMenu*);
                void apertarDesapertarBotoesBarraFerramentas();
                void botaoClicado(int);
                virtual bool OnEvent(const SEvent& event); //Sobrecarrega da classe IEventReceiver
                void update();
                void draw() const;
                void setUpEnvironment();
                static Principal* instance;
};

#endif // PRINCIPAL_H
