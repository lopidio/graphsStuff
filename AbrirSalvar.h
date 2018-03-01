void abrirArquivo(const wchar fileName)
{

}




void salvarArquivoAntes()
{
	modificado = false;
	ambiente->addWindow(modal, 3 botoes); //Salvar matriz, salvar grafo e nao salvar
	while (janela->isvisible)
	{
	}
}


//TODO
	Criar método: apertarDesapertarBotoes //De acordo com a opcaoSelecionada
	Criar método: editarGrafoObjeto();
	Criar menu: Arquivo (Novo, Abrir, Salvar, SalvarMatriz, - , Sair), Ferramentas (barra de ferramentas (auto checking))
					, Algoritmos (-), Ajuda (Sobre)
	Criar método: verificar se pretende salvar antes de (novo, abrir e sair)
	criar método: naoEArquivoValido() e erro ao abrir arquivo //Extensão desconhecida e arquivo corrompido;
	criar atributo: foiModificado; //Responde se o arquivo atual já foi modificado desde a sua última "salvagem"
	Ajeitar método: editarValor da aresta (permitir negativos?)
	Ajeitar barra de editar: inserir raio (Vértice) e tipo (aresta);
	Criar seta para arestas;
	Desenhar círculos carregados da memória ao invés de usar primitivas
	Mudar fonte;
	Criar método: atualizarMatriz;
	Aumentar raio dos vértices ao usar o scrolling do mouse
