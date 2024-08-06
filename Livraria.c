#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIVROS "Livros.dat"
#define CLIENTES "Clientes.dat"
#define VENDAS "Vendas.dat"
#define AUTORES "Autores.dat"

struct reg_livro{
	int codigo;
	char titulo[30];
	float preco;
	int codautor;     // codigo do autor
	char autor_nome[50];
};

struct reg_cliente{
	int codigo;
	char nome[50];
	char email[30];	
};

struct reg_venda{
	int codvenda; //codigo da venda
	int codcliente; //codigo do cliente que comprou
	int codlivro; //codigo do livro comprado
	int qtde; //qtde. vendida deste livro	
};

struct reg_autor{
    int codigo;
    char nome[50];
};


struct reg_autor localizarAutor(int codaut){
    FILE *fpautores;
    struct reg_autor autor;
    int achou=0;

    fpautores = fopen(AUTORES,"rb");

    while((achou==0)&&(fread(&autor,sizeof(autor),1,fpautores)==1)){
        if(autor.codigo==codaut){
            achou=1;
        }
    }
    fclose(fpautores);

    if (achou==0){ //NÃO Localizou o autor
        autor.codigo=-1; // Retorna um autor com código -1 caso não encontre
    }

    return autor; // Retorna a estrutura do autor encontrada
}

void cadastrar(){
    FILE *fplivros;
    struct reg_livro livro;
    int codautor;
    struct reg_autor autor;

    // Entrada de dados do novo Livro
    printf("\nDigite o Codigo: ");
    fflush(stdin); scanf("%i",&livro.codigo);
    printf("Digite o Titulo: ");
    fflush(stdin); gets(livro.titulo);
    printf("Digite o Preco: ");
    fflush(stdin); scanf("%f",&livro.preco);

    // Solicitar o código do autor
    printf("\nDigite o codigo do Autor: ");
    fflush(stdin); scanf("%i",&codautor);

   // Localizar o autor
    autor = localizarAutor(codautor); // Atribua o valor retornado a autor
    if (autor.codigo == -1){
        printf("\nAutor NAO Localizado!!!");
        return; // Retorna ao Menu Principal
    }

    // Atribuir o código e o nome do autor ao livro
    livro.codautor = codautor;
    strcpy(livro.autor_nome, autor.nome); // Copia o nome do autor para o livro

    // Abrir o Arquivo
    fplivros = fopen("livros.dat","ab");
    // Gravar
    fwrite(&livro,sizeof(livro),1,fplivros);
    // Fechar o Arquivo
    fclose(fplivros);

    printf("\nLivro Cadastrado com Sucesso.\n");
}

void relatorioTodosLivros(){
    FILE *fplivros;
    struct reg_livro livro;

    // Abrir o Arquivo
    fplivros = fopen(LIVROS,"rb");

    printf("\n # # #   Livraria Tech Info   # # # ");
    printf("\nCodigo Titulo                    Preco Autor");
    // Ler livro por livro e mostrar na tela
    while(fread(&livro,sizeof(livro),1,fplivros)==1){
        // Localizar e mostrar o nome do autor
        // struct reg_autor autor = localizarAutor(livro.codautor); // Não precisa mais chamar localizarAutor aqui
        if (livro.codautor != -1) {
            printf("\n%-6i %-25s %5.2f %-30s",livro.codigo,livro.titulo,livro.preco, livro.autor_nome); // Imprime o nome do autor do livro
        }
    }

    // Fechar o Arquivo
    fclose(fplivros);
}


struct reg_cliente localizarCliente(int codcli){
	FILE *fpcliente;
	struct reg_cliente cliente;
	int achou=0;
	
	fpcliente = fopen(CLIENTES,"rb");
	
	while((achou==0)&&(fread(&cliente,sizeof(cliente),1,fpcliente)==1)){
		if(cliente.codigo==codcli){
			achou=1;
		}
	}
	fclose(fpcliente);
	
	if (achou==0){ //NÃO Localizou o cliente
		cliente.codigo=-1;
	}
	
	return cliente;
	
}//Fim localizarCliente()

struct reg_livro localizarLivro(int codliv){
	FILE *fplivro;
	struct reg_livro livro;
	int achou=0;
	
	fplivro = fopen(LIVROS,"rb");
	
	while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivro)==1)){
		if(livro.codigo==codliv){
			achou=1;
		}
	}
	fclose(fplivro);
	
	if (achou==0){//NÃO localizou o livro
		livro.codigo=-1;
	}
	
	return livro;
	
}//Fim localizarLivro()

void consultarLivroPeloCodigo(){
	FILE *fplivros;
	struct reg_livro livro;
	int cod,achou;
	
	//Entar com o código do livro
	printf("\nDigite o Codigo do Livro a ser Localizado: ");
	fflush(stdin); scanf("%i",&cod);
	
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
		
	//Localizar o registro do Livro e mostrar os dados
	achou=0;
	while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		//printf("\nProcessando Livro codigo: %i",livro.codigo);
		if(livro.codigo==cod){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %.2f",livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nLivro NAO Localizado!");
	}
	
	//Fechar o Arquivo
	fclose(fplivros);
}//Fim consultarLivroPeloCodigo()

void consultarLivroPeloTitulo(){
	FILE *fplivros;
	struct reg_livro livro;
	int achou;
	char tit[30];
	
	//Entar com o Titulo do livro
	printf("\nDigite o Titulo do Livro a ser Localizado: ");
	fflush(stdin); gets(tit);
	
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
		
	//Localizar o registro do Livro e mostrar os dados
	achou=0;
	while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		if(strcmp(livro.titulo,tit)==0){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %.2f",livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nLivro NAO Localizado!");
	}
	
	//Fechar o Arquivo
	fclose(fplivros);
}//Fim consultarLivroPeloTitulo()

void consultarLivroPalavraChaveTitulo(){
	FILE *fplivros;
	struct reg_livro livro;
	int achou;
	char palavra[30];
	
	//Entar com o Titulo do livro
	printf("\nDigite a Palavra-Chave: ");
	fflush(stdin); gets(palavra);
	
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
		
	//Localizar o registro do Livro e mostrar os dados
	achou=0;
	printf("\nCodigo Titulo                    Preco");
	while(fread(&livro,sizeof(livro),1,fplivros)==1){
		if(strstr(livro.titulo,palavra)!=NULL){ //Achei o Livro
			printf("\n%-6i %-25s %5.2f",livro.codigo,livro.titulo,livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nNenhum Livro contem a Palavra %s no Titulo!",palavra);
	}
	
	//Fechar o Arquivo
	fclose(fplivros);
}//Fim consultarLivroPalavraChaveTitulo()

void alterarLivro(){
	FILE *fplivros;
	struct reg_livro livro;
	int cod,achou;
	char opc; //Opção
	
	//Solicitar o código do Livro a ser Alterado
	printf("\nDigite o Codigo do Livro a ser Alterado: ");
	fflush(stdin); scanf("%i",&cod);
	
	//Localizar o Livro e mostrar os dados
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb+");
		
	//Localizar o registro do Livro e mostrar os dados
	achou=0;
	while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		//printf("\nProcessando Livro codigo: %i",livro.codigo);
		if(livro.codigo==cod){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %.2f",livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){//NÃO achou nenhum Livro com o código
		printf("\nLivro NAO Localizado!");
		return; //Volta para o menu principal
	}	
	
	//Pedir confirmação
	printf("\nConfirma o Livro?(S/N) ");
	fflush(stdin); scanf("%c",&opc);
	if((opc!='S')&&(opc!='s')){ //NÃO confirmou
		printf("\nLivro Nao Confirmado!");
		return; //Volta para o menu principal
	}
	
	//Se confirmou, então continua
	//Solicitar os novos dados (Título,Preço)
	printf("\nDeseja alterar o Titulo?(S/N) ");
	fflush(stdin); scanf("%c",&opc);
	if((opc=='S')||(opc=='s')){ //confirmou
		printf("\nDigite o novo Titulo: ");
		fflush(stdin); gets(livro.titulo);
	}
	printf("\nDeseja alterar o Preco?(S/N) ");
	fflush(stdin); scanf("%c",&opc);
	if((opc=='S')||(opc=='s')){ //confirmou
		printf("\nDigite o novo Preco: ");
		fflush(stdin); scanf("%f",&livro.preco);
	}	
	
	//Pedir Confirmação
	printf("\nGravar Alteracao?(S/N) ");
	fflush(stdin); scanf("%c",&opc);
	if((opc!='S')&&(opc!='s')){ //NÃO confirmou
		printf("\nOperacao Cancelada!");
		return; //Volta para o menu principal
	}	
	
	//Voltar o ponteiro para o registro anterior
	fseek(fplivros,(long)-sizeof(livro),1);
	
	//Gravar o registro com as Alterações
	fwrite(&livro,sizeof(livro),1,fplivros);
	
	//Fechar o Arquivo
	fclose(fplivros);
	
	printf("\nLivro Alterado com Sucesso.");
	
}//Fim alterarLivro()

void excluirLivro(){
	FILE *fplivros,*fplivrosnew;
	struct reg_livro livro;
	int cod,achou;
	char opc; //Opção
	
	//Solicitar o código do Livro a ser Excluído
	printf("\nDigite o Codigo do Livro a ser Excluido: ");
	fflush(stdin); scanf("%i",&cod);	

	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
	
	//Localizar e Mostrar dados do Livro
	achou=0;
	while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		if(livro.codigo==cod){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %.2f",livro.preco);
			achou=1;
		}
	}
	fclose(fplivros);
		
	if (achou==0){
		printf("\nLivro NAO Localizado!");
		return; //Volta para o menu principal
	}	
		
	//Pedir confirmação
	printf("\nConfirma o Livro?(S/N) ");
	fflush(stdin); scanf("%c",&opc);
	if((opc!='S')&&(opc!='s')){ //NÃO confirmou
		printf("\nLivro Nao Confirmado!");
		return; //Volta para o menu principal
	}	
		
	//Criar um arquivo Auxiliar
	fplivros = fopen(LIVROS,"rb"); //Arquivo Original
	fplivrosnew = fopen("livrosnew.dat","wb"); //Arquivo Auxiliar
	
	//Ler registro por registro do arquivo Original
	// e gravar no arquivo Auxiliar, menos o regitro que será excluído
	while (fread(&livro,sizeof(livro),1,fplivros)==1){ //Ler do arquivo Original
		if (livro.codigo!=cod){ 
			fwrite(&livro,sizeof(livro),1,fplivrosnew); //Grava no arq. Auxiliar
		}
	}
	fclose(fplivros);
	fclose(fplivrosnew);
	
	//Excluir o arquivo Original
	system("del Livros.dat");
	
	//Renomear o arquivo Auxiliar
	system("rename livrosnew.dat Livros.dat");
	
	printf("\nLivro Excluido com Sucesso.");
	
}//Fim excluirLivro()

void cadastrarCliente(){
	FILE *fpclientes;
	struct reg_cliente cliente;
	char op;
	
	//Fazer a Entrada dos dados do cliente
	printf("\nDigite o Codigo: ");
	fflush(stdin); scanf("%i",&cliente.codigo);
	
	printf("Nome: ");
	fflush(stdin); gets(cliente.nome);
	
	printf("Email: ");
	fflush(stdin); gets(cliente.email);
	
	printf("\nSalvar Cliente(S/N)? ");
	fflush(stdin); scanf("%c",&op);
	
	if ((op=='n')||(op=='N')){
		printf("\nOperacao Cancelada!");
		return;  //retorna para o Menu Principal
	}
	
	//Abrir o Arquivo
	fpclientes = fopen(CLIENTES,"ab");
	
	//Salvar no Arquivo
	fwrite(&cliente,sizeof(cliente),1,fpclientes);
	
	fclose(fpclientes);
	
	printf("\nCliente Cadastrado com Sucesso.");
}//Fim cadastrarCliente()

void listarClientes(){
	FILE *fpclientes;
	struct reg_cliente cliente;
	
	//Abrir o Arquivo de Clientes
	fpclientes = fopen(CLIENTES,"rb");
	
	printf("\n# # # # #   Livraria Tech Info   # # # # #");
	printf("\n     Relatorio de Todos os Clientes");
	printf("\nCodigo Nome                           Email");
	//Ler registro por registro e mostrar na tela
	while (fread(&cliente,sizeof(cliente),1,fpclientes)==1){	
		printf("\n%-6i %-30s %s",cliente.codigo,cliente.nome,cliente.email);
  }
	
	//Fechar o Arquivo
	fclose(fpclientes);
}//Fim listarClientes()

void efetuarVenda(){
	FILE *fpvendas;
	struct reg_venda venda;
	struct reg_livro livro;
	struct reg_cliente cliente;
	int codcli, codliv;
	char opcao;	
	
	//Solicitar o codigo da Venda
	printf("\nDigite o Codigo da Venda: ");
	fflush(stdin); scanf("%i",&venda.codvenda);
	
	//Solicitar o codigo do cliente
	printf("\nDigite o codigo do Cliente: ");
  	fflush(stdin); scanf("%i",&codcli);
	
	//Localizar e mostrar os dados do cliente
	cliente = localizarCliente(codcli);
  	if (cliente.codigo==-1){
  		printf("\nCliente NAO Localizado!!!");
  		return; //Retorna ao Menu Principal
	}
	
	printf("\nCodigo: %i - Nome: %s",cliente.codigo,cliente.nome);
	printf("\nConfirma Cliente?(S/N) ");
	fflush(stdin); scanf("%c",&opcao);
	if ((opcao=='N')||(opcao=='n')){
		printf("\nCliente NAO Confirmado.");
		return; //Retorna ao Menu Principal
	}	
	
	//Solicitar o codigo do Livro
	printf("\nDigite o codigo do Livro: ");
  	fflush(stdin); scanf("%i",&codliv);
  	
	//Localizar e mostrar os dados do Livro
  	livro = localizarLivro(codliv);
  	if (livro.codigo==-1){
  		printf("\nLivro NAO Localizado!!!");
  		return; //Retorna ao Menu Principal
	}	
	
	printf("\nCodigo: %i Titulo: %s Preco: %.2f",livro.codigo,livro.titulo, livro.preco);
	printf("\nConfirma Livro?(S/N) ");
	fflush(stdin); scanf("%c",&opcao);
	if ((opcao=='N')||(opcao=='n')){
		printf("\nLivro NAO Confirmado.");
		return; //Retorna ao Menu Principal
	}  
	
	//Solicitar a qtde
	printf("\nDigite a qtde: ");
  	fflush(stdin); scanf("%i",&venda.qtde);
  
  	//Confirmar Venda
  	printf("\nGravar Venda?(S/N) ");
  	fflush(stdin); scanf("%c",&opcao);
  	if ((opcao=='N')||(opcao=='n')){
		printf("\nOperacao Cancelada!");
		return; //Retorna ao Menu Principal
	}  
  	
	//Gravar a Venda
  	venda.codcliente = cliente.codigo;
  	venda.codlivro = livro.codigo;
  
	fpvendas = fopen(VENDAS,"ab");	
	fwrite(&venda,sizeof(venda),1,fpvendas);
	fclose(fpvendas);
	
	printf("\nVenda realizada com sucesso.");	
}//Fim efetuarVenda()

void listarVendas(){
	FILE *fpvendas;
	struct reg_venda venda;
	
	fpvendas = fopen(VENDAS,"rb");
	
	printf("\nListagem das Vendas:\n");
	
	while (fread(&venda,sizeof(venda),1,fpvendas)==1){
		printf("\nCodigo Venda: %i",venda.codvenda);
		printf("\nCodigo Cliente: %i",venda.codcliente);
		printf("\nCodigo Livro: %i",venda.codlivro);
		printf("\nQtde: %i",venda.qtde);
		printf("\n---------------------------------------------");
	}
	fclose(fpvendas);
	
}//Fim listarVendas()

// Função para cadastrar um novo autor
	
void cadastrarAutor(){
    FILE *fpautores;
    struct reg_autor autor;
    char op;

    printf("\nDigite o Codigo do Autor: ");
    fflush(stdin); scanf("%i",&autor.codigo);

    printf("Nome do Autor: ");
    fflush(stdin); gets(autor.nome);

    printf("\nSalvar Autor(S/N)? ");
    fflush(stdin); scanf("%c",&op);

    if ((op=='n')||(op=='N')){
        printf("\nOperacao Cancelada!");
        return;  //retorna para o Menu Principal
    }

    // Abrir o Arquivo
    fpautores = fopen(AUTORES,"ab");

    // Salvar no Arquivo
    fwrite(&autor,sizeof(autor),1,fpautores);

    fclose(fpautores);

    printf("\nAutor Cadastrado com Sucesso.");
}


// Função para listar todos os autores
void listarAutores(){
    FILE *fpautores;
    struct reg_autor autor;

    // Abrir o Arquivo de Autores
    fpautores = fopen(AUTORES,"rb");

    printf("\n# # # # #   Livraria Tech Info   # # # # #");
    printf("\n     Relatorio de Todos os Autores");
    printf("\nCodigo Nome");
    // Ler registro por registro e mostrar na tela
    while (fread(&autor,sizeof(autor),1,fpautores)==1){
        printf("\n%-6i %-30s",autor.codigo,autor.nome);
    }

    // Fechar o Arquivo
    fclose(fpautores);
}
		
	
	
//relatorio livros por autor
	
		void relatorioLivrosAutor(){
    FILE *fplivros;
    struct reg_livro livro;
    int codautor;
    struct reg_autor autor;

    // Solicitar o código do autor
    printf("\nDigite o codigo do Autor: ");
    fflush(stdin); scanf("%i", &codautor);

    // Localizar o autor
    autor = localizarAutor(codautor);
    if (autor.codigo == -1){
        printf("\nAutor NAO Localizado!!!");
        return; // Retorna ao Menu Principal
    }

    // Mostrar o nome do autor
    printf("\nNome do Autor: %s\n", autor.nome);

    // Abrir o arquivo de livros
    fplivros = fopen(LIVROS, "rb");
    if (fplivros == NULL) {
        printf("\nErro ao abrir o arquivo Livros.dat!\n");
        return;
    }

    // Mostrar os livros do autor
    printf("\nLivros do Autor:\n");
    printf("\nCodigo Titulo                    Preco");
    while(fread(&livro, sizeof(livro), 1, fplivros) == 1){
        if (livro.codautor == codautor) {
            printf("\n%-6i %-25s %5.2f", livro.codigo, livro.titulo, livro.preco);
        }
    }

    // Fechar o arquivo de livros
    fclose(fplivros);
}

		
// livro mais caro
	void livroMaisCaro(){
    FILE *fplivros;
    struct reg_livro livro, livroMaisCaro;
    float precoMaximo = 0.0;
    int achouPrimeiro = 0;

    // Abrir o arquivo de livros
    fplivros = fopen(LIVROS, "rb");
    if (fplivros == NULL) {
        printf("\nErro ao abrir o arquivo Livros.dat!\n");
        return;
    }

    // Encontrar o livro mais caro
    while(fread(&livro, sizeof(livro), 1, fplivros) == 1){
        if (!achouPrimeiro || livro.preco > precoMaximo) {
            precoMaximo = livro.preco;
            livroMaisCaro = livro;
            achouPrimeiro = 1;
        }
    }

    // Fechar o arquivo de livros
    fclose(fplivros);

    // Mostrar o livro mais caro
    if (achouPrimeiro) {
        printf("\nLivro(s) mais caro(s):\n");
        printf("\nCodigo: %i", livroMaisCaro.codigo);
        printf("\nTitulo: %s", livroMaisCaro.titulo);
        printf("\nPreco: %.2f\n", livroMaisCaro.preco);
    } else {
        printf("\nNenhum livro encontrado no arquivo Livros.dat!\n");
    }
}


//clientes Que Compraram Livro
void clientesQueCompraramLivro() {
    FILE *fpvendas, *fpcliente;
    struct reg_venda venda;
    struct reg_livro livro;
    struct reg_cliente cliente;
    int codlivro;
    int achouLivro = 0;

    // Solicitar o código do livro
    printf("\nDigite o codigo do Livro: ");
    fflush(stdin); scanf("%i", &codlivro);

    // Localizar o livro
    livro = localizarLivro(codlivro);
    if (livro.codigo == -1){
        printf("\nLivro NAO Localizado!!!");
        return; // Retorna ao Menu Principal
    }

    // Mostrar o título do livro
    printf("\nTitulo do Livro: %s\n", livro.titulo);

    // Abrir o arquivo de vendas
    fpvendas = fopen(VENDAS, "rb");
    if (fpvendas == NULL) {
        printf("\nErro ao abrir o arquivo Vendas.dat!\n");
        return;
    }

    // Mostrar os clientes que compraram o livro
    printf("\nClientes que compraram o livro:\n");
    printf("\nCodigo nome");
    while(fread(&venda, sizeof(venda), 1, fpvendas) == 1){
        if (venda.codlivro == codlivro) {
            // Localizar o cliente
            cliente = localizarCliente(venda.codcliente);
            if (cliente.codigo != -1) {
                printf("\n%-6i %-30s", cliente.codigo, cliente.nome);
            }
        }
    }

    // Fechar o arquivo de vendas
    fclose(fpvendas);
}
			

int main(){
  int op;
  
  do{
  	
  	printf("\n\n\n# # # #   Livraria Tech Info   # # # #");
  	printf("\n#                                      #");
  	printf("\n# 1) Cadastrar Livro                   #");
  	printf("\n# 2) Relatorio Todos Livros            #");
  	printf("\n# 3) Consultar Livro pelo Codigo       #");
  	printf("\n# 4) Consultar Livro pelo Titulo       #");
  	printf("\n# 5) Consultar Palavra-chave no Titulo #");
  	printf("\n# 6) Alterar/Editar dados do Livro     #");
  	printf("\n# 7) Excluir Livro                     #");
	printf("\n# 8) Cadastrar Cliente                 #");
	printf("\n# 9) Listar Todos os Clientes          #");  
	printf("\n# 10) Efetuar Venda                    #");
	printf("\n# 11) Listar Vendas                    #");
	printf("\n# 12) Cadastrar Autor                  #");
	printf("\n# 13) Listar Autores                   #");
	printf("\n# 14) Relatorio livro por Autores      #");
	printf("\n# 15) livro mais caro                  #");
	printf("\n# 16) clientes Que Compraram Livro     #");
  	printf("\n# 0) Sair                              #");
  	printf("\nOpcao-> ");
  	
  	fflush(stdin); scanf("%i",&op);
  	switch(op){
		case 1: //Cadastrar um novo Produto
			cadastrar();
			break;
		case 2: //Relatório de todos os Produtos Cadastrados
			relatorioTodosLivros();
			break;
		case 3: //Consultar Livro Pelo Código
			consultarLivroPeloCodigo();
			break;	
		case 4: //Consultar Livro Pelo Título
			consultarLivroPeloTitulo();
			break;			
		case 5: //Consultar Livro por Palavra-chave no Título
			consultarLivroPalavraChaveTitulo();
			break;			
		case 6: //Alterar/Editar dados do Livro
			alterarLivro();
			break;
		case 7: //Excluir Livro
			excluirLivro();
			break;
		case 8: //Cadastrar um Cliente
			cadastrarCliente();
			break;
		case 9: //Listar clientes
			listarClientes();
			break;
		case 10: //Efetuar Venda de Livros para Clientes
			efetuarVenda();
			break;
		case 11: //Listar Vendas
			listarVendas();
			break;	
		case 12: // Cadastrar um autor
            cadastrarAutor();
            break;
        case 13: // Listar autores
            listarAutores();
            break;	
		case 14: // Relatório de Livros de um Autor
            relatorioLivrosAutor();
            break;	
            case 15: // Livro mais caro
            livroMaisCaro();
            break;
        case 16: // Clientes que compraram um livro
        	clientesQueCompraramLivro();
            break;
		case 0: //Sair
			printf("\n\nObrigado por utilizar nosso sistema.");  
	}
  }while (op!=0);	
	
	
}//Fim main()