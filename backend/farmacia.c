#include <stdio.h>
#include <string.h>
#include <windows.h>
FILE *arquivo;
FILE *arq_produto;
FILE *arq_funcionario;

//STRUCT PARA GERENCIAMENTO DE CLIENTES
typedef struct {
    char cl_nome[50], cl_email[100], cl_nasc[12], cl_cpf[20];
}CLIENTES;
//STRUCT PARA GERENCIAMENTO DE PRODUTOS POR CATEGORIA
typedef struct {
    char pr_nome[50],pr_cat[50]; //gerenciamento categoria
    int pr_cod, pr_quant;
    float pr_preco;
}PRODUTOS;
//STRUCT PARA GERENCIAMENTO DE FORNECEDORES
typedef struct {
	int cod, CNPJ;
	char nome[50];
}FORNECEDORES;
//STRUCT PARA GERENCIAMENTO DE LABORATORIOS
typedef struct {
 char nome[50];
 int cod;
}LABORATORIO;
typedef struct {
	char nome[50], email[50], funcao[30];
	int nascimento, cpf, cod;
	float salario;
}FUNCIONARIOS;
typedef struct {
	char cpf[20];
	int cod_v, qntd_p;
	float valor;
}VENDAS;

int menus(){
    int opcao;
	printf("===============Gerenciamento===============");
	printf("\n1-Clientes");
	printf("\n2-Produtos");
	printf("\n3-Laboratios");
	printf("\n4-Fornecedores ");
	printf("\n5-Funcionarios ");
	printf("\n6-Venda de produtos ");
	printf("\n0-Sair ");	
    scanf("%d",&opcao);
    return opcao;
}
int menu_cliente(){
    int opcao;
	printf("\n\n===============Gerenciamento-Clientes===============");
	printf("\n1-Adicionar Clientes");
	printf("\n2-Listar Clientes");
	printf("\n3-Alterar");
	printf("\n4-Excluir Clientes");
	printf("\n5-Ordenar Clientes");
	printf("\n0-Retornar ");
    scanf("%d",&opcao);
    return opcao;
}
int menu_produto(){
    int opcao;
	printf("\n\n===============Gerenciamento-Produtos===============");
	printf("\n1-Adicionar Produtos ");
	printf("\n2-Listar ");
	printf("\n3-Alterar ");
	printf("\n4-Excluir Produtos ");
	printf("\n5-listar por categorias ");
	printf("\n0-Retornar ");
    scanf("%d",&opcao);
    return opcao;
}
int menu_lab(){
    int opcao;
	printf("\n\n===============Gerenciamento-Laboratorios===============");
	printf("\n1-Cadastrar Laboratorio");
	printf("\n2-Lista de Laboratorios Cadastrados");
	printf("\n3-Alterar Laboratorio");
	printf("\n4-excluir Laboratorio");
	printf("\n0-Retornar ");
    scanf("%d",&opcao);
    return opcao;
}
int menu_fornecedores(){
    int opcao;
	printf("\n\n===============Gerenciamento-Fornecedores===============");
	printf("\n1-Cadastrar Fornecedor ");
	printf("\n2-Listar ");
	printf("\n3-Alterar ");
	printf("\n4-Excluir ");
	printf("\n0-Retornar ");
    scanf("%d",&opcao);
    return opcao;
}

int menu_cat(){
	int menu_lis;
	
	printf("\n\n===============Lista-Categorias===============");
    printf("\nDigite o numero da Categoria para ver os produtos cadastrados");
	printf("\n\n1-Medicamentos");
	printf("\n2-Suplementos");
	printf("\n3-Cosmeticos");
    printf("\n4-Higiene");
	printf("\n5-Infantil");
	printf("\n0-Retornar ");
	scanf("%d",&menu_lis);
	return menu_lis;
}

int menu_funcionario(){
	int opcao;
	printf("\n\n===============Gerenciamento-Funcionarios===============");
	printf("\n1-Adicionar Funcionario ");
	printf("\n2-Listar ");
	printf("\n3-Alterar ");
	printf("\n4-Excluir ");
	printf("\n0-Retornar ");
	scanf("%d",&opcao);
	return opcao;
}

int menu_venda(){
	int op;
	printf("\n\n===============Vendas=================");
	printf("\n1-Fazer uma venda ");
	printf("\n2-Lista de pedidos ");
	printf("\n3-Excluir pedido");
	printf("\n0-Retornar ");
	scanf("%d",&op);
	return op;
}
//GERENCIAMENTO DE CLIENTES====================================================================================================
int busca(char cpf[]){
	int pos=0;
	CLIENTES cl;
	rewind(arquivo);
	//arquivo=fopen("clientes.bin","rb+");
	while(fread(&cl,sizeof(CLIENTES),1,arquivo)==1){
		if(stricmp(cpf,cl.cl_cpf)==0)
			return pos;
		pos=ftell(arquivo);
	}
	return -1;
}

void adicionar_cliente() {
	CLIENTES cl;
	int pos;
	arquivo=fopen("clientes.bin","ab+");
	if(arquivo==NULL)
		printf("Erro ao abrir arquivo");
    else
	{
		printf("Informe o CPF do cliente: "); fflush(stdin);
		fgets(cl.cl_cpf,sizeof(cl.cl_cpf),stdin);
		pos=busca(cl.cl_cpf);
		if(pos==-1){
			printf("Informe o nome do cliente: "); fflush(stdin);
			fgets(cl.cl_nome,sizeof(cl.cl_nome),stdin);
			printf("Informe o e-mail do cliente: ");
			fgets(cl.cl_email, sizeof(cl.cl_email),stdin);
			printf("Informe a data de nascimento(dd/mm/aaaa): ");
			fgets(cl.cl_nasc,sizeof(cl.cl_nasc),stdin);
		
			fwrite(&cl, sizeof(CLIENTES), 1, arquivo);
			printf("\nCliente cadastrado!");
		}
		else
			printf("\nCliente ja cadastrado!");
		fclose(arquivo);
		system("pause");
		system("cls");
	}

}

void listar_clientes(){
	CLIENTES cl;
	arquivo = fopen("clientes.bin","rb");
	if(arquivo==NULL)
		printf("Erro ao abrir o arquivo!");
	else
	{
		while(fread(&cl, sizeof(CLIENTES),1,arquivo)==1)
		{
			printf("\n-----------------------\n");
			printf("\nNome: %s",cl.cl_nome);
			printf("\nE-mail: %s", cl.cl_email);
			printf("\nNascimento: %s", cl.cl_nasc);
            printf("\nCPF: %s", cl.cl_cpf);
		}
		fclose(arquivo);
		system("pause");
		system("cls");
	}
}

void alterar_cliente(){
	CLIENTES cl;
	int pos,op;
	arquivo=fopen("clientes.bin","rb+");
	printf("\nDigite o nome: ");fflush(stdin);
	fgets(cl.cl_nome,sizeof(cl.cl_nome),stdin);
	pos=busca(cl.cl_nome);
	if(pos==-1)
		printf("\nCliente nao econtrado!");
	else{
		fseek(arquivo,pos,SEEK_SET);
		fread(&cl,sizeof(CLIENTES),1,arquivo);
		printf("\n-----------------------\n");
		printf("\nNome: %s",cl.cl_nome);
		printf("\nE-mail: %s", cl.cl_email);
		printf("\nData de nascimento: %s", cl.cl_nasc);
		printf("\nCPF: %s", cl.cl_cpf);
		printf("\n-----------------------\n");
		printf("\nO que deseja alterar?");
		printf("\n1-Nome");
		printf("\n2-E-mail");
		printf("\n3-Data de nascimento");
		printf("\n4-CPF");
		printf("\n0-Cancelar");
		scanf("%d",&op);
		if( op==1){
			printf("\n NOVO nome: "); fflush(stdin);
			fgets(cl.cl_nome,sizeof(cl.cl_nome),stdin);
			fseek(arquivo,pos,0);
			fwrite(&cl,sizeof(CLIENTES),1,arquivo);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if( op==2){
			printf("\n NOVO e-mail: "); fflush(stdin);
			fgets(cl.cl_email,sizeof(cl.cl_email),stdin);
			fseek(arquivo,pos,0);
			fwrite(&cl,sizeof(CLIENTES),1,arquivo);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if( op==3){
			printf("\n NOVA data de nascimento: "); fflush(stdin);
			fgets(cl.cl_nasc,sizeof(cl.cl_nasc),stdin);
			fseek(arquivo,pos,0);
			fwrite(&cl,sizeof(CLIENTES),1,arquivo);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if( op==4){
			printf("\n NOVO CPF: "); fflush(stdin);
			fgets(cl.cl_cpf,sizeof(cl.cl_cpf),stdin);
			fseek(arquivo,pos,0);
			fwrite(&cl,sizeof(CLIENTES),1,arquivo);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
	}
	fclose(arquivo);
}

void excluir_cliente(){
	CLIENTES cl;
	int pos;
	char op, nome[50];
	
	arquivo=fopen("clientes.bin","rb+");
	if(arquivo==NULL)
		printf("\nErro ao abrir arquivo!");
	printf("\nNome: "); fflush(stdin);
	fgets(nome,sizeof(nome),stdin);
	if(strcmp(nome,"\0")!=0){
		pos=busca(nome);
		if(pos==-1)
			printf("\nCliente nao encontrado!");
		else{
			fseek(arquivo,pos,SEEK_SET);
			fread(&cl,sizeof(CLIENTES),1,arquivo);
			printf("\n-----------------------\n");
			printf("\nNome: %s",cl.cl_nome);
			printf("\nE-mail: %s", cl.cl_email);
			printf("\nNascimento: %s", cl.cl_nasc);
			printf("\nCPF: %s", cl.cl_cpf);
			printf("\n-----------------------\n");
			printf("\nExcluir? S/N ");
			scanf(" %c",&op);
			if(op=='s' || op=='S'){
				FILE *temp;
				temp=fopen("temp.bin","wb");
				if(temp==NULL){
					printf("\nErro ao abrir arquivo!");
				}
					
				else{
					rewind(arquivo);
					while(fread(&cl,sizeof(CLIENTES),1,arquivo)==1){
						if(stricmp(nome,cl.cl_nome)!=0){
							fwrite(&cl,sizeof(CLIENTES),1,temp);
						}
					}
					fclose(arquivo);
					fclose(temp);
					remove("clientes.bin");
					rename("temp.bin","clientes.bin");
					printf("\nCliente removido com sucesso!");
				}
			}
		}	
	}
	fclose(arquivo);
	system("pause");
	system("cls");
}

void ordenar_clientes(){
	CLIENTES cl1, cl2;
	int i, j, tamanho;
	
	arquivo=fopen("clientes.bin","rb+");
	if(arquivo==NULL)
		printf("\nErro ao abrir arquivo!");
	else{
		fseek(arquivo,0,SEEK_END);
		tamanho=ftell(arquivo)/sizeof(CLIENTES);
		
		for(i=0;i<tamanho-1;i++){
			for(j=0;j<tamanho-i-1;j++){
				fseek(arquivo,j*sizeof(CLIENTES),SEEK_SET);
				fread(&cl1,sizeof(CLIENTES),1,arquivo);
				fread(&cl2,sizeof(CLIENTES),1,arquivo);
				
				if(stricmp(cl1.cl_nome,cl2.cl_nome)>0){
					fseek(arquivo,j*sizeof(CLIENTES),SEEK_SET);
					fwrite(&cl2,sizeof(CLIENTES),1,arquivo);
					fwrite(&cl1,sizeof(CLIENTES),1,arquivo);
				}
			}
		}
		printf("\nClientes ordenados por nome com sucesso!");
		fclose(arquivo);
		system("pause");
		system("cls");
	}
}

//GERENCIAMENTO DE PRODUTOS====================================================================================================
int buscar_produto(int cod){
	PRODUTOS pr;
	rewind(arq_produto);
	while(fread(&pr,sizeof(PRODUTOS),1,arq_produto)==1){
		if(cod==pr.pr_cod)
			return ftell(arq_produto)-sizeof(PRODUTOS);
	}
	return -1;
}

void adicionar_produto(){
	PRODUTOS pr;
	arq_produto=fopen("produtos.bin","ab+");
	int pos,op_cat;
	if(arq_produto==NULL)
		printf("Erro ao abrir arquivo");
	else{
		printf("\nInforme o codigo do produto: ");
		scanf("%d",&pr.pr_cod);
		pos=buscar_produto(pr.pr_cod);
		if(pos==-1){
			printf("\nNome do produto: "); fflush(stdin);
			fgets(pr.pr_nome,sizeof(pr.pr_nome),stdin);
			printf("\nQual dessas Categorias se encaixaria o produto? ");
			printf("\n1-Medicamentos\n2-Suplementos\n3-Cosmeticos\n4-Higiene\n5-Infantil\n");
			scanf("%d",&op_cat);
			if(op_cat==1)
				strcpy(pr.pr_cat, "Medicamento");
			else if(op_cat==2)
				strcpy(pr.pr_cat, "Suplemento");
			else if(op_cat==3)
				strcpy(pr.pr_cat, "Cosmetico");
			else if(op_cat==4)
				strcpy(pr.pr_cat, "higiene");
			else if(op_cat==5)
				strcpy(pr.pr_cat, "Infantil");
			
			printf("\nPreco: ");
			scanf("%f",&pr.pr_preco);
			printf("\nQuantidade: ");
			scanf("%d",&pr.pr_quant);

			fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);
			printf("\nProduto cadastrado!");
		}
		else
			printf("\nProduto ja cadastrado!");
		fclose(arq_produto);
		system("pause");
		system("cls");
	}
}

void listar_produto(){
	PRODUTOS pr;
	arq_produto=fopen("produtos.bin","rb");
	if(arq_produto==NULL)
		printf("Erro ao abrir arquivo");
	else{
		while(fread(&pr,sizeof(PRODUTOS),1,arq_produto)==1){
			printf("\n-----------------------\n");
			printf("\nCodigo do produto: %d", pr.pr_cod);
			printf("\nNome: %s",pr.pr_nome);
			printf("\nCategoria: %s", pr.pr_cat);
			printf("\nPreco: %.2f", pr.pr_preco);
			printf("\nQuantidade: %d", pr.pr_quant);
		
		}
		fclose(arq_produto);
	}
}

void alterar_produto(){
	int pos,op;
	PRODUTOS pr;
	arq_produto=fopen("produtos.bin","rb+");
	if(arq_produto==NULL)
		printf("\nErro ao abrir arquivo!");
	printf("Digite o codigo do produto: ");
	scanf("%d",&pr.pr_cod);
	pos=buscar_produto(pr.pr_cod);
	if(pos==-1)
		printf("\nProduto nao encontrado!");
	else{
		fseek(arq_produto,pos,SEEK_SET);
		fread(&pr,sizeof(PRODUTOS),1,arq_produto);
		printf("\n-----------------------\n");
		printf("\nCodigo do produto: %d", pr.pr_cod);
		printf("\nNome: %s",pr.pr_nome);
		printf("\nCategoria: %s", pr.pr_cat);
		printf("\nPreco: %.2f", pr.pr_preco);
		printf("\nQuantidade: %d", pr.pr_quant);
		printf("\n-----------------------\n");
		printf("\nO que deseja alterar?");
		printf("\n1-Codigo ");
		printf("\n2-Nome ");
		printf("\n3-categoria ");
		printf("\n4-Preco ");
		printf("\n5-Qunatidade ");
		printf("\n0-Cancelar");
		scanf("%d",&op);
		if(op==1){
			printf("\n NOVO codigo: ");
			scanf("%d",&pr.pr_cod);
			fseek(arq_produto,pos,SEEK_SET);
			fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if(op==2){
			printf("\n NOVO nome: "); fflush(stdin);
			fgets(pr.pr_nome,sizeof(pr.pr_nome),stdin);
			fseek(arq_produto,pos,SEEK_SET);
			fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if(op==3){
			printf("\n NOVA categoria: "); fflush(stdin);
			fgets(pr.pr_cat,sizeof(pr.pr_cat),stdin);
			fseek(arq_produto,pos,SEEK_SET);
			fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if(op==4){
			printf("\n NOVO preco: ");
			scanf("%f",&pr.pr_preco);
			fseek(arq_produto,pos,SEEK_SET);
			fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
		if(op==5){
			printf("\n NOVA quantidade: ");
			scanf("%d",&pr.pr_quant);
			fseek(arq_produto,pos,SEEK_SET);
			fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);
			printf("Registro Atualizado!\n");
			system("pause");
			system("cls");
		}
	}
	fclose(arq_produto);
}

void excluir_produto(){
	PRODUTOS pr;
	int pos, cod;
	char op;
	arq_produto=fopen("produtos.bin","rb+");
	if(arq_produto==NULL)
		printf("\nErro ao abrir arquivo!");
	printf("\nCodigo do pruduto: ");
	scanf("%d",&cod);
	pos=buscar_produto(cod);
	if(pos==-1)
		printf("\nProduto nao cadastrado!");
	else{
		fseek(arq_produto,pos,SEEK_SET);
		fread(&pr,sizeof(PRODUTOS),1,arq_produto);
		printf("\n-----------------------\n");
		printf("\nCodigo do produto: %d", pr.pr_cod);
		printf("\nNome: %s",pr.pr_nome);
		printf("\nCategoria: %s", pr.pr_cat);
		printf("\nPreco: %.2f", pr.pr_preco);
		printf("\nQuantidade: %d", pr.pr_quant);
		printf("\nExcluir? S/N ");
		scanf(" %c",&op);
		if(op=='s' || op=='S'){
			FILE *temp;
			temp=fopen("temp.bin","wb");
			if(temp==NULL)
				printf("\nErro ao abrir arquivo!");
			else{
				rewind(arq_produto);
				while(fread(&pr,sizeof(PRODUTOS),1,arq_produto)==1){
					if(cod!=pr.pr_cod)
						fwrite(&pr,sizeof(PRODUTOS),1,temp);
				}
				fclose(arq_produto);
				fclose(temp);
				remove("produtos.bin");
				rename("temp.bin","produtos.bin");
				printf("\nProduto removido com sucesso!");
			}
		}
	}
	fclose(arq_produto);
	system("pause");
	system("cls");
}

//GERENCIAMENTO DE FORNECEDORES================================================================================================
int busca_forne(FILE *arq_fornecedor, int cod) {
    FORNECEDORES fn;
    rewind(arq_fornecedor);
    
    while (fread(&fn, sizeof(FORNECEDORES), 1, arq_fornecedor) == 1) {
        if (fn.cod == cod) {
            return ftell(arq_fornecedor) - sizeof(FORNECEDORES);
        }
    }
    
    return -1;
}
void adicionar_fornecedor(){
	FILE *arq_fornecedor;
	FORNECEDORES fn;
	arq_fornecedor=fopen("arq_fornecedor.bin","ab+");
	int pos, cont;
	if(arq_fornecedor==NULL)
		printf("\nErro no arquivo");
	else{
		do{
			printf("\nDigite o codigo do fornecedor: ");
			scanf("%d",&fn.cod);
			pos=busca_forne(arq_fornecedor,fn.cod);
			if(pos==-1){
				printf("\nDigite o nome da empresa fornecedora: "); fflush(stdin);
				gets(fn.nome);
				printf("\nDigite o CNPJ da empresa fornecedora: ");
				scanf("%d",&fn.CNPJ);
				
				fwrite(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
			}else
				printf("\nCodigo de fornecedor ja existente");
				
			printf("\nDeseja continuar cadastrando fornecedores?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
		}while(cont!=2);
		printf("\nFornecedor(es) Cadastrado(s)\n");
		fclose(arq_fornecedor);
		system("pause");
		system("cls");
	}
}

void listar_fornecedor(){
	FILE *arq_fornecedor;
	FORNECEDORES fn;
	arq_fornecedor=fopen("arq_fornecedor.bin","rb");
	if(arq_fornecedor==NULL)
		printf("\nErro no arquivo");
	else{
		printf("\n===========Lista de fornecedores===========\n");
		
		while(fread(&fn, sizeof(FORNECEDORES), 1, arq_fornecedor) == 1){
			printf("\nCodigo do fornecedor: %d",fn.cod);
			printf("\nNome do fornecedor: %s",fn.nome);
			printf("\nCNPJ do fornecedor: %d",fn.CNPJ);
			printf("\n\n---------------------------------------------\n\n");
		}
		fclose(arq_fornecedor);
		system("pause");
		system("cls");
		
	}
}

void alterar_fornecedor(){
	FILE *arq_fornecedor;
	FORNECEDORES fn;
	arq_fornecedor=fopen("arq_fornecedor.bin","rb+");
	int pos, op;
	if(arq_fornecedor==NULL)
		printf("\nErro no arquivo");
	else{
		printf("\nDigite o cod do fornecedor que deseja alterar: ");
		scanf("%d",&fn.cod);
		pos=busca_forne(arq_fornecedor,fn.cod);
		if(pos==-1)
			printf("\nCodigo nao encontrado");
		else{
			fseek(arq_fornecedor,pos,0);
			fread(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
			printf("\n\n---------------------------------------------");
			printf("\nCodigo do fornecedor: %d",fn.cod);
			printf("\nNome do fornecedor: %s",fn.nome);
			printf("\nCNPJ do fornecedor: %d",fn.CNPJ);
			printf("\n---------------------------------------------\n");
			printf("\nOque Deseja alterar?");
			printf("\n1-Nome\n2-CNPJ\n");
			scanf("%d",&op);
			if(op==1){
				printf("\nDigite o novo nome do fornecedor: "); fflush(stdin);
				gets(fn.nome);
				fseek(arq_fornecedor,pos,0);
				fwrite(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
				system("pause");
				system("cls");	
			}
			if(op==2){
				printf("\nDigite o novo CNPJ do fornecedor: ");
				scanf("%d",&fn.CNPJ);
				fseek(arq_fornecedor,pos,0);
				fwrite(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
				system("pause");
				system("cls");	
			}
			
		}
		fclose(arq_fornecedor);
	}
}

void excluir_fornecedor(){
	FILE *arq_fornecedor;
	FORNECEDORES fn;
	arq_fornecedor=fopen("arq_fornecedor.bin","rb");
	int pos, cod, cont,op;
	if(arq_fornecedor==NULL)
		printf("\nErro no arquivo");
	else{
		do{
			printf("\nDigite o codigo do fornecedor que deseja excluir: ");
			scanf("%d",&cod);
			pos=busca_forne(arq_fornecedor,cod);
			if(pos==-1)
				printf("\nCodigo nao econtrado");
			else{
				fseek(arq_fornecedor,pos,0);
				fread(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
				printf("\n\n---------------------------------------------");
				printf("\nCodigo do fornecedor: %d",fn.cod);
				printf("\nNome do fornecedor: %s",fn.nome);
				printf("\nCNPJ do fornecedor: %d",fn.CNPJ);
				printf("\n---------------------------------------------\n");
				printf("\nDeseja excluir?");
				printf("\n1-Sim\n2-Nao\n");
				scanf("%d",&op);
				
				if(op==1){
					FILE *temp;
					temp=fopen("temp.bin","wb");
					rewind(arq_fornecedor);
					fread(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
					while(!feof(arq_fornecedor)){
						if(cod!=fn.cod)
							fwrite(&fn,sizeof(FORNECEDORES),1,temp);
						fread(&fn,sizeof(FORNECEDORES),1,arq_fornecedor);
					}
				fclose(arq_fornecedor);
				fclose(temp);
				remove("arq_fornecedor.bin");
				rename("temp.bin","arq_fornecedor.bin");
				}
			}
			printf("\nDeseja excluir outro fornecedor?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
			if(cont==1)
				arq_fornecedor=fopen("arq_fornecedor.bin","rb");
		}while(cont!=2);
	}
	fclose(arq_fornecedor);
	getch(); 
	system("cls");
}

//GERENCIAMENTO DE FUNCIONARIOS================================================================================================
int busca_func(FILE *arq_funcionario, int cpf) {
	FUNCIONARIOS fc;
	rewind(arq_funcionario);
	
	while (fread(&fc, sizeof(FUNCIONARIOS), 1, arq_funcionario) == 1) {
		if (fc.cod == cpf) {
			return ftell(arq_funcionario) - sizeof(FUNCIONARIOS);
		}
	}
	
	return -1;
}

void adicionar_funcionario(){
	FILE *arq_funcionario;
	FUNCIONARIOS fc;
	arq_funcionario=fopen("arq_funcionario.bin","ab+");
	int pos, cont;
	if(arq_funcionario==NULL)
		printf("\nErro no arquivo");
	else{
		do{
			printf("\nDigite o CPF do funcionario: ");
			scanf("%d",&fc.cod);
			pos=busca_func(arq_funcionario,fc.cod);
			if(pos==-1){
				printf("\nDigite o nome do funcionario: "); fflush(stdin);
				gets(fc.nome);
				printf("\nDigite o e-mail do funcionario: "); fflush(stdin);
				gets(fc.email);
				printf("\nDigite a funcao do funcionario: "); fflush(stdin);
				gets(fc.funcao);
				printf("\nDigite o salario do funcionario: ");
				scanf("%f",&fc.salario);
				
				fwrite(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
			}else
				printf("\nCPF ja existente");
				
			printf("\nDeseja continuar cadastrando funcionarios?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
		}while(cont!=2);
		printf("\nFuncionario(s) Cadastrado(s)\n");
		fclose(arq_funcionario);
		system("pause");
		system("cls");
	}
}

void listar_funcionario(){
	FILE *arq_funcionario;
	FUNCIONARIOS fc;
	arq_funcionario=fopen("arq_funcionario.bin","rb");
	if(arq_funcionario==NULL)
		printf("\nErro no arquivo");
	else{
		printf("\n===========Lista de funcionarios===========\n");
		
		while(fread(&fc, sizeof(FUNCIONARIOS), 1, arq_funcionario) == 1){
			printf("\nCPF do funcionario: %d",fc.cod);
			printf("\nNome do funcionario: %s",fc.nome);
			printf("\nE-mail do funcionario: %s",fc.email);
			printf("\nFuncao do funcionario: %s",fc.funcao);
			printf("\nSalario do funcionario: %.2f",fc.salario);
			printf("\n\n---------------------------------------------\n\n");
		}
		fclose(arq_funcionario);
		system("pause");
		system("cls");
		
	}
}

void alterar_funcionario(){
	FUNCIONARIOS fc;
	int pos,op;
	arq_funcionario=fopen("arq_funcionario.bin","rb+");
	if(arq_funcionario==NULL)
		printf("\nErro no arquivo");
	printf("\nDigite o CPF do funcionario: ");
	scanf("%d",&fc.cod);
	pos=busca_func(arq_funcionario,fc.cod);
	if(pos==-1)
		printf("\nFuncionario nao encontrado!");
	else{
		fseek(arq_funcionario,pos,0);
		fread(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
		printf("\n\n---------------------------------------------");
		printf("\nCPF do funcionario: %d",fc.cod);
		printf("\nNome do funcionario: %s",fc.nome);
		printf("\nE-mail do funcionario: %s",fc.email);
		printf("\nFuncao do funcionario: %s",fc.funcao);
		printf("\nSalario do funcionario: %.2f",fc.salario);
		printf("\n---------------------------------------------\n");
		printf("\nOque Deseja alterar?");
		printf("\n1-Nome\n2-E-mail\n3-Funcao\n4-Salario\n");
		scanf("%d",&op);
		if(op==1){
			printf("\nDigite o novo nome do funcionario: "); fflush(stdin);
			gets(fc.nome);
			fseek(arq_funcionario,pos,0);
			fwrite(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
			system("pause");
			system("cls");	
		}
		if(op==2){
			printf("\nDigite o novo e-mail do funcionario: "); fflush(stdin);
			gets(fc.email);
			fseek(arq_funcionario,pos,0);
			fwrite(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
			system("pause");
			system("cls");	
		}
		if(op==3){
			printf("\nDigite a nova funcao do funcionario: "); fflush(stdin);
			gets(fc.funcao);
			fseek(arq_funcionario,pos,0);
			fwrite(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
			system("pause");
			system("cls");	
		}
		if(op==4){
			printf("\nDigite o novo salario do funcionario: ");
			scanf("%f",&fc.salario);
			fseek(arq_funcionario,pos,0);
			fwrite(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
			system("pause");
			system("cls");	
		}
		
	}
	fclose(arq_funcionario);
}

void excluir_funcionario(){
	FILE *arq_funcionario;
	FUNCIONARIOS fc;
	arq_funcionario=fopen("arq_funcionario.bin","rb");
	int pos, cpf, cont,op;
	if(arq_funcionario==NULL)
		printf("\nErro no arquivo");
	else{
		do{
			printf("\nDigite o CPF do funcionario que deseja excluir: ");
			scanf("%d",&cpf);
			pos=busca_func(arq_funcionario,cpf);
			if(pos==-1)
				printf("\nCPF nao econtrado");
			else{
				fseek(arq_funcionario,pos,0);
				fread(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
				printf("\n\n---------------------------------------------");
				printf("\nCPF do funcionario: %d",fc.cod);
				printf("\nNome do funcionario: %s",fc.nome);
				printf("\nE-mail do funcionario: %s",fc.email);
				printf("\nFuncao do funcionario: %s",fc.funcao);
				printf("\nSalario do funcionario: %.2f",fc.salario);
				printf("\n---------------------------------------------\n");
				printf("\nDeseja excluir?");
				printf("\n1-Sim\n2-Nao\n");
				scanf("%d",&op);
				
				if(op==1){
					FILE *temp;
					temp=fopen("temp.bin","wb");
					rewind(arq_funcionario);
					fread(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
					while(!feof(arq_funcionario)){
						if(cpf!=fc.cod)
							fwrite(&fc,sizeof(FUNCIONARIOS),1,temp);
						fread(&fc,sizeof(FUNCIONARIOS),1,arq_funcionario);
					}
				fclose(arq_funcionario);
				fclose(temp);
				remove("arq_funcionario.bin");
				rename("temp.bin","arq_funcionario.bin");
				}
			}
			printf("\nDeseja excluir outro funcionario?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
			if(cont==1)
				arq_funcionario=fopen("arq_funcionario.bin","rb");
		}while(cont!=2);
	}
	fclose(arq_funcionario);
	getch(); 
	system("cls");
}
//GERENCIAMENTO DE LABORATORIOS================================================================================================
int busca_lab(FILE *arq_lab, int cod) {
	LABORATORIO lab;
	rewind(arq_lab);
	
	while (fread(&lab, sizeof(LABORATORIO), 1, arq_lab) == 1) {
		if (lab.cod == cod) {
			return ftell(arq_lab) - sizeof(LABORATORIO);
		}
	}
	return -1;
}
void inserir_lab(){
	FILE *arq_lab;
	LABORATORIO lab;
	int pos, cont;
	arq_lab=fopen("arq_lab.bin","ab+");
	if(arq_lab==NULL)
		printf("\nErro");
	else{
		do{
			printf("\nDigite o Codigo do laboratorio: ");
			scanf("%d",&lab.cod);
			pos=busca_lab(arq_lab,lab.cod);
			if(pos==-1){
				printf("\nDigite o nome do laboratorio: "); fflush(stdin);
				gets(lab.nome);
				
				fwrite(&lab,sizeof(LABORATORIO),1,arq_lab);
			}else{
				printf("\nLaboratorio ja cadastrado");
			}
			printf("\nDeseja continuar?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
		}while(cont!=2);
		fclose(arq_lab);
	}
}
void listar_lab(){
	FILE *arq_lab;
	LABORATORIO lab;
	arq_lab=fopen("arq_lab.bin","rb");
	if(arq_lab==NULL)
		printf("\nErro");
	else{
		while(fread(&lab,sizeof(LABORATORIO),1,arq_lab)==1){
			printf("\nCodigo do Laboratorio: %d",lab.cod);
			printf("\nNome do Laboratorio: %s",lab.nome);
			printf("\n=========================================");
		}
	}
	fclose(arq_lab);
}
void alterar_lab(){
	FILE *arq_lab;
	LABORATORIO lab;
	int pos, cont;
	arq_lab=fopen("arq_lab.bin","rb+");
	if(arq_lab==NULL)
		printf("\nErro");
	else{
		printf("\nDigite o codigo do laboratorio desejado: ");
		scanf("%d",&lab.cod);
		pos=busca_lab(arq_lab,lab.cod);
		if(pos==-1)
			printf("\nLaboratorio nao encontrado");
		else{
			fseek(arq_lab,pos,0);
			fread(&lab,sizeof(LABORATORIO),1,arq_lab);
			
			printf("\n=========================");
			printf("\nCodigo: %d",lab.cod);
			printf("\nNome: %s",lab.nome);
			printf("\n=========================");
			printf("\nDeseja alterar o nome do laboratorio?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
			
			if(cont==1){
				fseek(arq_lab,pos,0);
				printf("\nDigite o novo nome: "); fflush(stdin);
				gets(lab.nome);
				fwrite(&lab,sizeof(LABORATORIO),1,arq_lab);
				printf("\nAlteracao concluida");
			}
		}
		fclose(arq_lab);
	}
}
void excluir_lab(){
	FILE *arq_lab;
	LABORATORIO lab;
	int pos, cod_t, cont;
	arq_lab=fopen("arq_lab.bin","rb");
	if(arq_lab==NULL)
		printf("\nErro");
	else{
		do{
			
			printf("\ndigite o codigo do laboratorio a ser excluido: ");
			scanf("%d",&cod_t);
			pos=busca_lab(arq_lab,cod_t);
			if(pos==-1)
				printf("\nLaboratorio não cadastrado");
			else{
				fseek(arq_lab,pos,0);
				fread(&lab,sizeof(LABORATORIO),1,arq_lab);
				
				printf("\n=========================");
				printf("\nCodigo: %d",lab.cod);
				printf("\nNome: %s",lab.nome);
				printf("\n=========================");
				printf("\nDeseja excluir o laboratorio?\n1-Sim\t2-Nao\n");
				scanf("%d",&cont);
				
				if(cont==1){
					FILE *temp;
					temp=fopen("temp.bin","wb");
					rewind(arq_lab);
					fread(&lab,sizeof(LABORATORIO),1,arq_lab);
					while(!feof(arq_lab)){
						if(cod_t!=lab.cod)
						fwrite(&lab,sizeof(LABORATORIO),1,temp);
						fread(&lab,sizeof(LABORATORIO),1,arq_lab);
					}
				fclose(arq_lab);
				fclose(temp);
				remove("arq_lab.bin");
				rename("temp.bin","arq_lab.bin");
				}
			}
			printf("\nDeseja excluir outro Laboratorio?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
			if(cont==1)
				arq_lab=fopen("arq_lab.bin","rb");
		}while(cont!=2);
		fclose(arq_lab);
	}		
}
//MENU DE CATEGORIAS================================================================================================
void lista_cat(int op_cat){
	char op[60];
	if(op_cat==1){
		strcpy(op, "Medicamento");
	}else if(op_cat==2){
		strcpy(op, "Suplemento");
	}else if(op_cat==3){
		strcpy(op, "Cosmetico");
	}else if(op_cat==4){
		strcpy(op, "higiene");
	}else if(op_cat==5){
		strcpy(op, "Infantil");
	}
	
	PRODUTOS pr;
	arq_produto=fopen("produtos.bin","rb");
	if(arq_produto==NULL)
		printf("Erro ao abrir arquivo");
	else{
		while(fread(&pr,sizeof(PRODUTOS),1,arq_produto)==1){
			if(stricmp(op,pr.pr_cat)==0){
				printf("\n-----------------------\n");
				printf("\nCodigo do produto: %d", pr.pr_cod);
				printf("\nNome: %s",pr.pr_nome);
				printf("\nCategoria: %s", pr.pr_cat);
				printf("\nPreco: %.2f", pr.pr_preco);
				printf("\nQuantidade: %d", pr.pr_quant);
			}
		}
		fclose(arq_produto);
	}
}
//MENU DE VENDAS================================================================================================
int busca_venda(FILE *arq_venda,int cod){
	VENDAS v;
	rewind(arq_venda);
	
	while (fread(&v, sizeof(VENDAS), 1, arq_venda) == 1) {
		if (v.cod_v == cod) {
			return ftell(arq_venda) - sizeof(VENDAS);
		}
	}
	return -1;
}
int buscar_produto_t(FILE *arq_produto,int cod){
	PRODUTOS pr;
	rewind(arq_produto);
	
	while (fread(&pr, sizeof(PRODUTOS), 1, arq_produto) == 1) {
		if (pr.pr_cod == cod) {
			return ftell(arq_produto) - sizeof(PRODUTOS);
		}
	}
	return -1;
}
void vender(){
	FILE *arq_venda;
	VENDAS v;
	CLIENTES cl;
	PRODUTOS pr;
	int pos,cont,qntde_temp,cod_validado;
	arq_venda=fopen("vendas.bin","ab+");
	arq_produto=fopen("produtos.bin","rb+");
	arquivo=fopen("clientes.bin","rb+");
	if(arq_venda==NULL && arq_produto==NULL && arquivo==NULL)
		printf("\nErro");
	else{
		do{
			v.qntd_p=0;
			v.valor=0;
			system("cls");
			printf("\nPara comecar uma venda digite o cpf do cliente que esta comprando:\n"); fflush(stdin);
			fgets(cl.cl_cpf,sizeof(cl.cl_cpf),stdin);
			pos=busca(cl.cl_cpf);
			if(pos==-1)
				printf("\nCliente nao cadastrado");
			else{
				cod_validado=0;
				v.cod_v=0;
				while(cod_validado!=1){
					v.cod_v+=1;
					pos=busca_venda(arq_venda,v.cod_v);
					if(pos==-1)
						cod_validado=1;
				}
				printf("\nO codigo da venda e: %d",v.cod_v);
				
				do{
					strcpy(v.cpf,cl.cl_cpf);
					printf("\nDigite o codigo do produto que deseja comprar: ");
					scanf("%d",&pr.pr_cod);
					pos=buscar_produto(pr.pr_cod);
					if(pos==-1){
						printf("\nProduto nao encontrado");
					}else{
						fseek(arq_produto, pos, 0);
						fread(&pr,sizeof(PRODUTOS),1,arq_produto);
						printf("\n=======================================");
						printf("\nNome: %s",pr.pr_nome);
						printf("\nValor unitario: %.2f",pr.pr_preco);
						printf("\ndeseja quantas unidades deste produto?");
						scanf("%d",&qntde_temp);
						
						v.qntd_p+=qntde_temp;
						pr.pr_quant=pr.pr_quant-qntde_temp;
						v.valor+=(qntde_temp*pr.pr_preco);
						
						fseek(arq_produto, pos, 0);
						fwrite(&pr,sizeof(PRODUTOS),1,arq_produto);	
					}
					printf("\nDeseja comprar outro produto?\n1-sim\t2-nao\n");
					scanf("%d",&cont);
					system("cls");
				}while(cont!=2);
				if(v.qntd_p>0)
					fwrite(&v,sizeof(VENDAS),1,arq_venda);				
				else{
					printf("\nImpossivel salvar a venda, descartando por falta de informacoes\n");
					return;
				}
				printf("\n==================================");
				printf("\nVenda finalizada");
			} 
			printf("\nDeseja vender para outro cliente?\n1-sim\t2-nao\n");
			scanf("%d",&cont);
		}while(cont!=2);
		fclose(arq_venda);
		fclose(arq_produto);
		fclose(arquivo);
	}
}

void lista_venda(){
	FILE *arq_venda;
	VENDAS v;
	arq_venda=fopen("vendas.bin","rb");
	if(arq_venda==NULL)
		printf("\nErro");
	else{
		while(fread(&v,sizeof(VENDAS),1,arq_venda)==1){
			printf("\nCPF: %s",v.cpf);
			printf("\nCodigo da venda: %d",v.cod_v);
			printf("\nQuantidade de produtos: %d",v.qntd_p);
			printf("\nValor total da venda: %.2f",v.valor);
			printf("\n============================================\n");
		}
		fclose(arq_venda);
	}
}

void excluir_venda(){
	FILE *arq_venda;
	VENDAS v;
	int pos, cod_t, cont;
	arq_venda=fopen("vendas.bin","rb");
	if(arq_venda==NULL)
		printf("\nErro");
	else{
		do{
			
			printf("\ndigite o codigo da venda a ser excluida: ");
			scanf("%d",&cod_t);
			pos=busca_venda(arq_venda,cod_t);
			if(pos==-1)
				printf("\nvenda nao existente");
			else{
				fseek(arq_venda,pos,0);
				fread(&v,sizeof(VENDAS),1,arq_venda);
				
				printf("\n=========================");
				printf("\nCPF: %s",v.cpf);
				printf("\nCodigo da venda: %d",v.cod_v);
				printf("\nQuantidade de produtos: %d",v.qntd_p);
				printf("\nValor total da venda: %.2f",v.valor);
				printf("\n=========================");
				printf("\nDeseja excluir a venda?\n1-Sim\t2-Nao\n");
				scanf("%d",&cont);
				
				if(cont==1){
					FILE *temp;
					temp=fopen("temp.bin","wb");
					rewind(arq_venda);
					fread(&v,sizeof(VENDAS),1,arq_venda);
					while(!feof(arq_venda)){
						if(cod_t!=v.cod_v)
						fwrite(&v,sizeof(VENDAS),1,temp);
						fread(&v,sizeof(VENDAS),1,arq_venda);
					}
				fclose(arq_venda);
				fclose(temp);
				remove("vendas.bin");
				rename("temp.bin","vendas.bin");
				}
			}
			printf("\nDeseja excluir outra venda?\n1-Sim\t2-Nao\n");
			scanf("%d",&cont);
			if(cont==1)
				arq_venda=fopen("vendas.bin","rb");
		}while(cont!=2);
		fclose(arq_venda);
	}		
}

int main() {   
    int opcao, opcao_cliente, opcao_produto, opcao_lab, opcao_fornecedor, opcao_funcionario,op_cat,op_venda;
    do{
        opcao=menus();
        switch(opcao){
            case 1: //CLIENTES
                    do{
                        opcao_cliente=menu_cliente();
                        switch(opcao_cliente) {
                            case 1: adicionar_cliente();
                                break;
                            case 2: listar_clientes();
                                break;
                            case 3: alterar_cliente();
                                break;
                            case 4: excluir_cliente();
                                break;
							case 5: ordenar_clientes();
								break;
                            case 0:
                                break;
                            default:
                            printf("\nOpcao Invalida!");
                        }
                    }while(opcao_cliente!=0);
                break;//FIm DO CASO 1
            case 2:
                    do{
                        opcao_produto=menu_produto();
                        switch(opcao_produto) {
                            case 1: adicionar_produto();
                                break;
                            case 2: listar_produto();
                                break;
                            case 3: alterar_produto();
                                break;
                            case 4: excluir_produto();
                                break;
                            case 5: //Menu categorias
								do{
									op_cat=menu_cat();
									switch(op_cat){
										case 1: lista_cat(op_cat);
											break;
										case 2:	lista_cat(op_cat);
											break;
										case 3:	lista_cat(op_cat);
											break;
										case 4:	lista_cat(op_cat);
											break;
										case 5:	lista_cat(op_cat);
											break;
										case 0:
											break;
										default:
											printf("\nOpcao Invalida!");
									}
								}while(op_cat!=0);
								 	
								break;//FIM menu categorias
                            case 0:
                                break;
                            default:
                                printf("\nOpcao Invalida!");
                        }
                    }while(opcao_produto!=0);
                    break;
                case 3: //LABORATORIOS
                    do{
                        opcao_lab=menu_lab();
                        switch(opcao_lab) {
                            case 1: //GERENCIAR LABORATORIO
                                inserir_lab();
                                break;
                            case 2: //
                                listar_lab();
                                break;
                            case 3: //
                                alterar_lab();
                                break;
                            case 4:
                            	excluir_lab();
                            	break;
                            case 0:
                                break;
                            default:
                                printf("\nOpcao Invalida!");
                        }
                        system("pause");
                        system("cls");
                    }while(opcao_lab!=0);
                    break;//FIM DO CASO 3
                case 4:
                    do{
                        opcao_fornecedor=menu_fornecedores();
                        switch(opcao_fornecedor){
                            case 1: adicionar_fornecedor();
                                break;
                            case 2: listar_fornecedor();
                                break;
                            case 3: alterar_fornecedor();
                                break;
                            case 4: excluir_fornecedor();
                                break;
                            case 0:
                                break;
                            default:
                                printf("\nOpcao Invalida!");
                        }
                    }while(opcao_fornecedor!=0);
                    break;
				case 5: //FUNCIONARIOS
					do{
						opcao_funcionario=menu_funcionario();
						switch(opcao_funcionario){
							case 1: 
								adicionar_funcionario();
								break;
							case 2: 
								listar_funcionario();
								break;
							case 3: 
								alterar_funcionario();
								break;
							case 4: 
								excluir_funcionario();
								break;
							case 0:
								break;
							default:
								printf("\nOpcao Invalida!");
						}
					}while(opcao_funcionario!=0);
					break;//FIM DO CASO 5
				case 6:
					do{
						op_venda=menu_venda();
						switch(op_venda){
							case 1: vender();
								break;
							case 2: lista_venda();
								break;
							case 3: excluir_venda();
								break;
							case 0:
								break;
							default:
								printf("\nOpcao Invalida!");
						}
						system("pause");
						system("cls");
					}while(op_venda!=0);
					break;//FIM DO CASO 6
			case 0:
				break;
			default:
				printf("\nOpcao Invalida!");
        }
        system("pause"); // pressione uma tecla para continuar.
  		system("cls"); //Limpa a tela.
    }while(opcao!=0);
    printf("\nAte Logo!");
}
