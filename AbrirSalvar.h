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
	Criar m�todo: apertarDesapertarBotoes //De acordo com a opcaoSelecionada
	Criar m�todo: editarGrafoObjeto();
	Criar menu: Arquivo (Novo, Abrir, Salvar, SalvarMatriz, - , Sair), Ferramentas (barra de ferramentas (auto checking))
					, Algoritmos (-), Ajuda (Sobre)
	Criar m�todo: verificar se pretende salvar antes de (novo, abrir e sair)
	criar m�todo: naoEArquivoValido() e erro ao abrir arquivo //Extens�o desconhecida e arquivo corrompido;
	criar atributo: foiModificado; //Responde se o arquivo atual j� foi modificado desde a sua �ltima "salvagem"
	Ajeitar m�todo: editarValor da aresta (permitir negativos?)
	Ajeitar barra de editar: inserir raio (V�rtice) e tipo (aresta);
	Criar seta para arestas;
	Desenhar c�rculos carregados da mem�ria ao inv�s de usar primitivas
	Mudar fonte;
	Criar m�todo: atualizarMatriz;
	Aumentar raio dos v�rtices ao usar o scrolling do mouse
