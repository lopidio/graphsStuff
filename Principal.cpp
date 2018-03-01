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


#include "Principal.h"

Principal* Principal::instance = NULL;

Principal::Principal()
{
        mouse = NULL;
        animationPlayer = NULL;
	device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 32, false, false, false, this); //Cores, fullscreen, stencilbuffer, vsync, receiver
	device->setWindowCaption(L"Grafos App");
	device->setResizable(true);
        ambiente = device->getGUIEnvironment();
        ambiente->loadGUI(L"Resources/environment.xml");
        font =  ambiente->getFont("Century10.xml");
        if (font)
                ambiente->getSkin()->setFont(font);
        mouse = new Mouse(device->getCursorControl());
        abaAtual = 0;
        detalhes = NULL;
        grafos.push_back(new Grafo());
        setUpEnvironment();
}

Principal::~Principal()
{
        delete animationPlayer;
        device->drop();
        printf("destrutor principal\n");
        while(grafos.size())
        {
                delete grafos.front();
                grafos.erase(grafos.begin());
        }
        delete menuEditar;
        //deletar todos os grafos das abas!!
}

/** @brief OnEvent
  *
  * @todo: document this function
  */
bool Principal::OnEvent(const SEvent& event)
{
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
             //   printf("MOUSE: %d\n", event.MouseInput);
                mouse->atualizarEvento(event.MouseInput); //Atualizando o estado do mouse
        }
        else if (event.EventType == EET_GUI_EVENT) //Se for um evento GUI
        {
                int id = (int)event.GUIEvent.Caller->getID();
                gui::EGUI_EVENT_TYPE tipo = event.GUIEvent.EventType;
                if (animationPlayer) //Redireciona para a animação
                {
                        if (id >= animationPlayer->getMinIdObject() && id <= animationPlayer->getMaxIdObject())
                        {
                                animationPlayer->onEvent(id, tipo);
                        }
                }
                if (tipo == EGET_EDITBOX_CHANGED) //Campo de texto do menu editar
                {
                        menuEditar->textChangedEvent();
                }
                else if (tipo == EGET_BUTTON_CLICKED) //Se for um botão sendo pressionado
                {
                        botaoClicado(id);
                }
                else if (tipo == EGET_MENU_ITEM_SELECTED)
                {
                        menuItemSelecionado( static_cast<IGUIContextMenu*>(event.GUIEvent.Caller ));
                }
                else if (tipo == EGET_FILE_SELECTED || tipo == EGET_DIRECTORY_SELECTED )
                {
                        printf("Selecionou arquivo\n");
                        IGUIFileOpenDialog* dialog = (IGUIFileOpenDialog*)event.GUIEvent.Caller;

                        if (tipoDaDialogFile == dO_salvar)
                        {
                                IGUIEditBox* campoTexto =  dynamic_cast<IGUIEditBox*>(dialog->getElementFromId(gO_salvarCampoTexto, true));
                                stringw diretorio = dialog->getDirectoryName();
                                grafos[abaAtual]->setNome(campoTexto->getText());
                                tabBar->getTab(abaAtual)->setText(campoTexto->getText());
                                diretorio.append(campoTexto->getText());

                                std::string nomeArquivoSalvar = WStringToString(diretorio.c_str());
//                                printf("Nome: %s\n", WStringToString(campoTexto->getText()).c_str());
 //                               printf("Nome arquivo salvar: %s\n", nomeArquivoSalvar.c_str());
                                tipoDaDialogFile = dO_desconhecido;
                                dialog->setVisible(false); //Gambis
                                grafos[abaAtual]->salvarArquivo(nomeArquivoSalvar);
                        }
                        else if (tipoDaDialogFile == dO_abrir)
                        {
                                stringw nomeAbrir = dialog->getFileName();
                                std::string nomeArquivoAbrir = WStringToString(nomeAbrir.c_str());
//                                printf("Nome arquivo abrir: %s\n", nomeArquivoAbrir.c_str());
                                Grafo* novoGrafo = grafos[abaAtual];
                                if (!grafos[abaAtual]->isVazio())
                                {
                                        novoGrafo = new Grafo();
                                        novaAbaComGrafo(novoGrafo);
                                }

                                novoGrafo->abrirArquivo(nomeArquivoAbrir);
                                size_t found = nomeArquivoAbrir.find_last_of("/\\");
                                std::string nomeSohDoArquivo = nomeArquivoAbrir.substr(found+1);
                                nomeSohDoArquivo = nomeSohDoArquivo.substr(0, nomeSohDoArquivo.length() - 6); // nome - ".grafo"

                                stringw WnomeSohDoArquivo = StringToWString(nomeSohDoArquivo).c_str();
                                novoGrafo->setNome(WnomeSohDoArquivo.c_str());
                                //tabBar->getTab(abaAtual)->setText(WnomeSohDoArquivo.c_str());
                                tipoDaDialogFile = dO_desconhecido;
                                nomeAbaModificado();
                        }
                }
                else if (tipo == EGET_TAB_CHANGED )
                {
                        tabBarEvent();
                }
                else if (tipo == EGET_ELEMENT_LEFT )
                        mouse->unBlock();
                else if (tipo == EGET_ELEMENT_HOVERED)
                        mouse->block();
                else if (tipo != EGET_ELEMENT_FOCUS_LOST )
                {
                        opcaoSelecionada = mO_count;
                        apertarDesapertarBotoesBarraFerramentas();
                }
        }
        else if (event.EventType == EET_KEY_INPUT_EVENT && !menuEditar->estaAtivo())
        {
                int tecla = event.KeyInput.Key;
                switch (tecla)
                {
                        case KEY_KEY_Q:
                                        botaoClicado(mO_criar);
                                break;
                        case KEY_KEY_W:
                                        botaoClicado(mO_editar);
                                break;
                        case KEY_KEY_A:
                                        botaoClicado(mO_deletar);
                                break;
                        case KEY_KEY_S:
                                        botaoClicado(mO_mover);
                                break;

                }
        }
        return false;
}

void Principal::botaoClicado(int id)
{
        if (id >= mO_criar && id < mO_count + mO_criar) //Botões da barra de ferramenta
        {
                menuEditar->terminar();

                switch((eMenuOpcao)id)
                {
                        case mO_editar:
                        case mO_criar:
                        case mO_deletar:
                                        limparListaDeSelecao();
                        default:
                                opcaoSelecionada = (eMenuOpcao)id;//Atualiza o menu
                }
                apertarDesapertarBotoesBarraFerramentas();
        }
        if (id == gO_editarOk) //Botão OK do editar
        {
                menuEditar->okButton();
                if (!menuEditar->estaAtivo())
                {
                        opcaoSelecionada = mO_count;
                        apertarDesapertarBotoesBarraFerramentas();
                }
        }
}

void Principal::tabBarEvent()
{
        abaAtual = tabBar->getActiveTab();
        int numTabs = tabBar->getTabCount();
        if (abaAtual == numTabs - 1) //Se a última aba (+) tiver sido clicada
                novaAbaComGrafo(NULL);
        if (animationPlayer)
                animationPlayer->setAnimacao(&grafos[abaAtual]->getAnimacao()); //Atualiza a animação corrente
        detalhes->update();
}

/** @brief novaAbaComNome
  *
  * @todo: document this function
  */
void Principal::novaAbaComGrafo(Grafo* novo)
{
//        int abaAntiga = abaAtual;
        int numTabs = tabBar->getTabCount();
        abaAtual = numTabs - 1;
        if (!novo)
        {
//                printf("Passa pelo else\n");
                novo = new Grafo();
                std::string nome = "Nova aba ";
                nome.append(IntToString(abaAtual + 1));
                novo->setNome(StringToWString(nome).c_str());
        }
        //printf("dispara evento?\n");
//        tabBar->setActiveTab(abaAtual); //Comentar pq dispara um evento e dá um pau mto louco!
        //printf("//dispara evento?\n");

        grafos.push_back(novo);
        tabBar->addTab(L"+");

        printf("numAbas: %d  grafosSize:%d\n ", numTabs, grafos.size());

        nomeAbaModificado();
}


/** @brief getInstance
  *
  * @todo: document this function
  */
Principal* Principal::getInstance()
{
        if (!instance)
                instance = new Principal();
        return instance;
}

void Principal::run()
{
        IVideoDriver* video = getVideo();
        int i = 0;
        while (device->run() && video)
        {
                (++i)%=100;
                video->beginScene(true, true, video::SColor(255,100,100,100));
                update();
                draw();
                ambiente->drawAll();
                video->endScene();
        }
        delete this;
}

/** @brief nomeAbaModificado
  *
  * @todo: document this function
  */
void Principal::nomeAbaModificado(int aba)
{
        IGUITab* abaAtual =  tabBar->getTab(aba);
        abaAtual->setText(grafos[aba]->getNome().c_str());
}

/** @brief nomeAbaModificado
  *
  * @todo: document this function
  */
void Principal::nomeAbaModificado()
{
        for (int i = 0; i < (int)grafos.size(); i++)
        {
                IGUITab* abaAtual =  tabBar->getTab(i);
                abaAtual->setText(grafos[i]->getNome().c_str());
        }

}




/** @brief getMouse
  *
  * @todo: document this function
  */
Mouse* Principal::getMouse() const
{
        return mouse;
}

/** @brief getVideo
  *
  * @todo: document this function
  */
IVideoDriver* Principal::getVideo() const
{
        return device->getVideoDriver();
}

/** @brief getTimer
  *
  * @todo: document this function
  */
ITimer* Principal::getTimer()
{
        return device->getTimer();
}



/** @brief getFonte
  *
  * @todo: document this function
  */
IGUIFont* Principal::getFonte() const
{
        return font;
}

/** @brief getAmbiente
  *
  * @todo: document this function
  */
IGUIEnvironment* Principal::getAmbiente() const
{
        return ambiente;
}

/** @brief update
  *
  * @todo: document this function
  */
void Principal::update()
{
        nomeAbaModificado();
        //Atualiza o grafo atual
        grafos[abaAtual]->update();
        if (animationPlayer)
                animationPlayer->update();

        if (mouse)
        {
                if (opcaoSelecionada == mO_criar) //MENU CRIAR
                {
                         if (mouse->onClick())
                        {
                                if (!mouse->isOver()) //Cria um novo vértice
                                {
                                        unsigned int id = grafos[abaAtual]->getNumVertices();
                                        position2df mousePosicao = mouse->getPosicao();
                                                //printf("Vertice::draw2: %d, %d\n", posicao.X - RADIUS,posicao.Y - RADIUS);
                                        grafos[abaAtual]->addVertice(new Vertice(id, mousePosicao));
                                }
                                if (grafos[abaAtual]->getNumVertices() >= 2)    // Verifica a criação de uma aresta
                                {
                                        grafos[abaAtual]->addAresta();
                                }
                        }
                        else if (grafos[abaAtual]->getSelecionados().size() > 0 && !mouse->isBlocked())// && mouse->isOver())//Desenha uma linha simbolizando uma aresta
                        {
                                Vertice * origem = static_cast<Vertice*>(grafos[abaAtual]->getSelecionados().front());
                                irr::core::vector2d<int> ini(origem->getPosicao().X, origem->getPosicao().Y);
                                irr::core::vector2d<int> fim(mouse->getPosicao().X, mouse->getPosicao().Y);
                                VIDEO->draw2DLine (ini, fim, SColor(255,255,255,255));
                        }
                }
                if (mouse->isRightButtonDown() && !mouse->isOver()) //Mover todos os vértices
                {
                        grafos[abaAtual]->mover();
                }
                if (opcaoSelecionada == mO_editar)
                {
                        if (mouse->onRelease())
                        {
                                menuEditar->iniciar(grafos[abaAtual]->getSelecionados());
                        }
                }
                mouse->update();
        }
}
/** @brief draw
  *
  * @todo: document this function
  */
void Principal::draw() const
{
//        printf("Principal::draw\n");

        grafos[abaAtual]->draw();
        if (mouse)
                mouse->draw();
//        printf("Principal::draw fim\n");

}

/** @brief addGrafoALista
  *
  * @todo: document this function
  */
void Principal::addGrafoALista(GrafoObjeto* objeto)
{
        //O próprio objeto chama esse método
        grafos[abaAtual]->selecionarGrafoObjeto(objeto);
        detalhes->update();
//        if (opcaoSelecionada == mO_editar && !mouse->isLeftButtonDown())
//                menuEditar->iniciar(grafos[abaAtual]->getSelecionados());
}

/** @brief limparListaDeSelecao
  *
  * @todo: document this function
  */
void Principal::limparListaDeSelecao() //desselecionarTodos
{
        menuEditar->terminar();
        grafos[abaAtual]->limparListaDeSelecao();
}

/** @brief getMenuOpcao
  *
  * @todo: document this function
  */
eMenuOpcao Principal::getMenuOpcao() const
{
        return opcaoSelecionada;
}

/** @brief setUpEnvironment
  *
  * @todo: document this function
  */
void Principal::setUpEnvironment()
{
        IGUIElement* raiz = ambiente->getRootGUIElement();

        IGUIButton * criar =  dynamic_cast<IGUIButton*>(raiz->getElementFromId(mO_criar, true));
        criar->setPressed(true);

        {// Criando MENU
                gui::IGUIContextMenu* menu = ambiente->addMenu();
                gui::IGUIContextMenu* submenu;
                { //Arquivo
                        menu->addItem(L"Arquivo", -1, true, true);
                        submenu = menu->getSubMenu(0);
                        submenu->addItem(L"Novo", gO_novoArquivo);
                        submenu->addItem(L"Abrir", gO_abrirArquivo);
                        submenu->addItem(L"Salvar", gO_salvarComoArquivo);
                        submenu->addSeparator();
                        submenu->addItem(L"Sair", gO_sair);
                }

                { //Editar
                        menu->addItem(L"Editar", -1, true, true);
                        submenu = menu->getSubMenu(1);
                        submenu->addItem(L"Selecionar Tudo", gO_selecionarTudo);
                        submenu->addItem(L"Desselecionar Tudo", gO_desselecionarTudo);
                        submenu->addSeparator();
                        submenu->addItem(L"Selecionar Todos os Vertices", gO_selecionarTodosVertices);
                        submenu->addItem(L"Selecionar Todas as Arestas", gO_selecionarTodasArestas);
                }

                { //Ferramentas
                        menu->addItem(L"Ferramentas", -1, true, true);
                        submenu = menu->getSubMenu(2);
                        submenu->addItem(L"Barra de Ferramentas", gO_exibirBarraFerramentas, true, false, true); //Auto checking
                        submenu->addItem(L"Janela de Detalhes", gO_detalhes,true, false, false); //Auto checking
                        submenu->addItem(L"Tocador de Animacao", gO_tocadorDeAnimacao ,true, false, false); //Auto checking
                }

                { //Algoritmos
                        menu->addItem(L"Algoritmos", -1, true, true);
                        submenu = menu->getSubMenu(3);
                        submenu->addItem(L"Busca", -1, true, true);
                        submenu->addItem(L"Menor Caminho", -1, true, true);
                        submenu->addItem(L"AGM", -1, true, true);
                        { //Algoritmos de busca
                                gui::IGUIContextMenu* busca =  submenu->getSubMenu(0);
                                busca->addItem(L"Busca em Profundidade", gO_algoritmos + aID_buscaProfundidade);
                                busca->addItem(L"Busca em Largura", gO_algoritmos + aID_buscaLargura);
                        }
                        { //Algoritmos de Menor Caminho
                                gui::IGUIContextMenu* busca =  submenu->getSubMenu(1);
                                busca->addItem(L"Dijkstra", gO_algoritmos + aID_dijkstra);
                                busca->addItem(L"Floyd", gO_algoritmos + aID_floyd);
                        }
                        { //Algoritmos de AGM
                                gui::IGUIContextMenu* busca =  submenu->getSubMenu(2);
                                busca->addItem(L"Kruskal", gO_algoritmos + aID_kruskal);
                                busca->addItem(L"Prim", gO_algoritmos + aID_prim);
                        }
                }

                { //Ajuda
                        menu->addItem(L"Ajuda", -1, true, true);
                        submenu = menu->getSubMenu(4);
                        submenu->addItem(L"Sobre", gO_sobre);
                }
	}

        { //Menu editar
                IGUIWindow* janela =  dynamic_cast<IGUIWindow*>(raiz->getElementFromId(gO_editarWindow, true));
                IGUIEditBox* campoTexto =  dynamic_cast<IGUIEditBox*>(raiz->getElementFromId(gO_editarCampoTexto, true));
                menuEditar = new MenuEditar(janela, campoTexto);
        }

        { //Controle de abas
                ambiente->addWindow (rect<s32>(-5,20,2000,58))->setDrawTitlebar(false);
                tabBar =ambiente->addTabControl(rect<s32>(-5,20,2000,58));
                tabBar->addTab(L"");
                nomeAbaModificado();
                tabBar->addTab(L"+");
        }

        { //Tocador de animacao

                  IGUIWindow* janela =  dynamic_cast<IGUIWindow*>(raiz->getElementFromId(APJanela, true));

                //Todos esses elementos tão dentro da janela
                IGUIButton* rec =  dynamic_cast<IGUIButton*>(janela->getElementFromId(APRec, true));
                IGUIButton* stop =  dynamic_cast<IGUIButton*>(janela->getElementFromId(APStop, true));
                IGUIButton* playPause =  dynamic_cast<IGUIButton*>(janela->getElementFromId(APPlayPause, true));
                IGUIButton* loop =  dynamic_cast<IGUIButton*>(janela->getElementFromId(APLoop, true));
                IGUIScrollBar* progresso =  dynamic_cast<IGUIScrollBar*>(janela->getElementFromId(APProgresso, true));
                IGUIScrollBar* velocidadeAnimacao =  dynamic_cast<IGUIScrollBar*>(janela->getElementFromId(APVelocidade, true));

                if (!rec || ! stop || !playPause || !loop || !progresso || !velocidadeAnimacao || !janela)
                        AMBIENTE->addMessageBox(L"Tocador de animacao", L"Tocador de animacao invalido");
                else
                {
                        animationPlayer = new AnimationPlayer(rec, stop,  playPause, loop, progresso, velocidadeAnimacao, janela);
                        animationPlayer->setAnimacao(&grafos[abaAtual]->getAnimacao());
                }
        }

        //{ Detalhes
                if (!detalhes)
                {
                        IGUIWindow* janela = dynamic_cast<IGUIWindow*>(raiz->getElementFromId(gO_detalhes, true));
                        IGUIStaticText* campoTexto = ambiente->addStaticText(L"", core::rect< s32 > (05,20,200,200), false, true, janela);
                        detalhes = new Detalhes(janela, campoTexto);
                }
        //}
}

/** @brief getSelecionados
  *
  * @todo: document this function
  */
const std::list<GrafoObjeto*> & Principal::getSelecionados() const
{
        return grafos[abaAtual]->getSelecionados();
}

/** @brief numArestasDoVertice
  *
  * @todo: document this function
  */
int Principal::numArestasDoVertice(int id) const
{
        return grafos[abaAtual]->numArestasDoVertice(id);
}



/** @brief deleteGrafoALista
  *
  * @todo: document this function
  */
void Principal::deleteGrafoALista(GrafoObjeto* obj)
{
        grafos[abaAtual]->desselecionarGrafoObjeto(obj);
        detalhes->update();
        menuEditar->terminar();
}


/** @brief menuItemSelecionado
  *
  * @todo: document this function
  */
void Principal::menuItemSelecionado(IGUIContextMenu* menu)
{
        s32 id = menu->getItemCommandId(menu->getSelectedItem());
        IGUIFileOpenDialog* caixa;
        IGUIEditBox* texto;
        if (id >= gO_algoritmos && id < gO_algoritmos + aID_algotimosCount)
                executarAlgoritmo(id - gO_algoritmos);
        switch(id)
        {
                case gO_tocadorDeAnimacao:
                                animationPlayer->setVisivel(!animationPlayer->isVisivel());
                                menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
                        break;
                case gO_selecionarTodasArestas:
                                grafos[abaAtual]->selecionarTodasArestas();
                        break;
                case gO_selecionarTodosVertices:
                                grafos[abaAtual]->selecionarTodosVertices();
                        break;
                case gO_selecionarTudo:
                                grafos[abaAtual]->selecionarTudo();
                        break;
                case gO_desselecionarTudo:
                                grafos[abaAtual]->limparListaDeSelecao();
                        break;
		case gO_salvarComoArquivo: //
                                tipoDaDialogFile = dO_salvar;
                                caixa = ambiente->addFileOpenDialog(L"Escolha o nome e o diretorio");
                                texto = ambiente->addEditBox(L"", rect< s32 > (10,30,260,50), true, caixa, gO_salvarCampoTexto);
                                texto->setText(grafos[abaAtual]->getNome().c_str());
			break;
		case gO_sair: //
                                device->closeDevice();
                        break;
		case gO_abrirArquivo: //
                                tipoDaDialogFile = dO_abrir;
                                ambiente->addFileOpenDialog(L"Escolha o nome e o diretorio");
			break;
		case gO_novoArquivo: //
                                grafos[abaAtual]->novoArquivo();
			break;
		case gO_sobre: //
                                ambiente->addMessageBox(L"Sobre", L"Teoria dos Grafos - UECE 2011.1\n-Davi Teles\n-Guilherme Moraes\n-Thais de Almeida");
                        break;
		case gO_detalhes: //
                                detalhes->setVisibilidade(!detalhes->isVisivel());
                                menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
                        break;
                case gO_exibirBarraFerramentas:
                                IGUIElement* raiz = ambiente->getRootGUIElement();
                                IGUIWindow* janela =  dynamic_cast<IGUIWindow*>(raiz->getElementFromId(gO_barraFerramenta, true));
                                janela->setVisible(!janela->isVisible());
                                menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
                        break;
        }
}

/** @brief executarAlgoritmo
  *
  * @todo: document this function
  */
void Principal::executarAlgoritmo(int id)
{
        printf("Principal:: Algoritmo numero: %d\n", id);
        Algoritmos* algoritmo = Algoritmos::getAlgoritmoFromID(id);
        if (algoritmo)
        {
                Grafo* novoGrafo = algoritmo->executeFromGrafo(grafos[abaAtual]);
                delete algoritmo;
                if (novoGrafo)
                        novaAbaComGrafo(novoGrafo);
//                else
//                        ambiente->addMessageBox(L"Algoritmo executadp", L"-");
        }
}



/** @brief apertarDesapertarBotoesBarraFerramentas
  *
  * @todo: document this function
  */
void Principal::apertarDesapertarBotoesBarraFerramentas()
{
        for (int i = mO_criar; i < mO_count + mO_criar; i++) //Percorro todos os botões da barra de ferramentas
        {
                IGUIButton* botao =  dynamic_cast<IGUIButton*>(ambiente->getRootGUIElement()->getElementFromId(i, true));
                if (botao)
                {
                        //Posso utilizar o operador ternário também
                        if (i != opcaoSelecionada)
                                botao->setPressed(false); //Desaperto todos os outros
                        else
                                botao->setPressed(true); //Aperto o chamador do evento (mesmo que o evento tenha sido chamado por desapertá-lo)
                }
        }
}


void Principal::deleteVertice(Vertice* vertice)
{
        grafos[abaAtual]->deleteVertice(vertice);
}

void Principal::deleteAresta(Aresta* aresta)
{
        grafos[abaAtual]->deleteAresta(aresta);
}


/** @brief numVertices
  *
  * @todo: document this function
  */
int Principal::numVertices() const
{
        return grafos[abaAtual]->getNumVertices();
}

/** @brief isTodoGrafoSelecionado
  *
  * @todo: document this function
  */
bool Principal::isTodoGrafoSelecionado() const
{
        return grafos[abaAtual]->isTodoSelecionado();
}


/** @brief getGrafo
  *
  * @todo: document this function
  */
Grafo* Principal::getGrafo() const
{
        return grafos[abaAtual];
}

/** @brief atualizarMatriz
  *
  * @todo: document this function
  */
void Principal::atualizarMatriz()
{
        grafos[abaAtual]->atualizarMatriz();
        detalhes->update();
}















//MÉTODOS ESTÁTICOS!!



void Principal::Draw2DImage(ITexture* texture , rect<int> sourceRect, position2d<int> position, position2d<int> rotationPoint, f32 rotation, vector2df scale, bool useAlphaChannel, SColor color)
{
   IVideoDriver *driver = VIDEO;
   SMaterial material;

   // Store and clear the projection matrix
   matrix4 oldProjMat = driver->getTransform(ETS_PROJECTION);
   driver->setTransform(ETS_PROJECTION,matrix4());

   // Store and clear the view matrix
   matrix4 oldViewMat = driver->getTransform(ETS_VIEW);
   driver->setTransform(ETS_VIEW,matrix4());

   // Store and clear the world matrix
   matrix4 oldWorldMat = driver->getTransform(ETS_WORLD);
   driver->setTransform(ETS_WORLD, matrix4());

   // Find the positions of corners
   vector2df corner[4];

   corner[0] = vector2df(position.X,position.Y);
   corner[1] = vector2df(position.X+sourceRect.getWidth()*scale.X,position.Y);
   corner[2] = vector2df(position.X,position.Y+sourceRect.getHeight()*scale.Y);
   corner[3] = vector2df(position.X+sourceRect.getWidth()*scale.X,position.Y+sourceRect.getHeight()*scale.Y);

   // Rotate corners
   if (rotation != 0.0f)
      for (int x = 0; x < 4; x++)
         corner[x].rotateBy(rotation,vector2df(rotationPoint.X, rotationPoint.Y));


   // Find the uv coordinates of the sourceRect
   vector2df uvCorner[4];
   uvCorner[0] = vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
   uvCorner[1] = vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
   uvCorner[2] = vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
   uvCorner[3] = vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   for (int x = 0; x < 4; x++) {
      float uvX = uvCorner[x].X/(float)texture->getSize().Width;
      float uvY = uvCorner[x].Y/(float)texture->getSize().Height;
      uvCorner[x] = vector2df(uvX,uvY);
   }

   // Vertices for the image
   S3DVertex vertices[4];
   u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };

   // Convert pixels to world coordinates
   float screenWidth = driver->getScreenSize().Width;
   float screenHeight = driver->getScreenSize().Height;
   for (int x = 0; x < 4; x++) {
      float screenPosX = ((corner[x].X/screenWidth)-0.5f)*2.0f;
      float screenPosY = ((corner[x].Y/screenHeight)-0.5f)*-2.0f;
      vertices[x].Pos = vector3df(screenPosX,screenPosY,1);
      vertices[x].TCoords = uvCorner[x];
      vertices[x].Color = color;
   }

   material.Lighting = false;
   material.ZWriteEnable = false;
   material.ZBuffer = false;
   material.TextureLayer[0].Texture = texture;
   material.MaterialTypeParam = pack_texureBlendFunc(EBF_SRC_ALPHA, EBF_ONE_MINUS_SRC_ALPHA, EMFN_MODULATE_1X, EAS_TEXTURE | EAS_VERTEX_COLOR);

   if (useAlphaChannel)
      material.MaterialType = EMT_ONETEXTURE_BLEND;
   else
      material.MaterialType = EMT_SOLID;

   driver->setMaterial(material);
   driver->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);

   // Restore projection and view matrices
   driver->setTransform(ETS_PROJECTION,oldProjMat);
   driver->setTransform(ETS_VIEW,oldViewMat);
   driver->setTransform(ETS_WORLD,oldWorldMat);
}

/** @brief WStringToString
  *
  * @todo: document this function
  */
std::string Principal::WStringToString(const std::wstring& s)
{
        std::string temp(s.length(), ' ');
        std::copy(s.begin(), s.end(), temp.begin());
        return temp;
}

/** @brief StringToWString
  *
  * @todo: document this function
  */
wstring Principal::StringToWString(const std::string & s)
{
        std::wstring temp(s.length(),L' ');
        std::copy(s.begin(), s.end(), temp.begin());
        return temp;
}

/** @brief intToString
  *
  * @todo: document this function
  */
std::string Principal::IntToString(int numero)
{
        stringstream conversor;
        conversor<<numero;
        return conversor.str();
}

/** @brief intToString
  *
  * @todo: document this function
  */
std::string Principal::FloatToString(float numero)
{
        stringstream conversor;
        conversor<<numero;
        return conversor.str();
}

/** @brief StringToInt
  *
  * @todo: document this function
  */
int Principal::StringToInt(const std::string& s)
{
        return atoi(s.c_str());
}

/** @brief StringToInt
  *
  * @todo: document this function
  */
float Principal::StringToFloat(const std::string& s)
{
        return atof(s.c_str());
}
