/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Menu
*
*  Arquivo gerado:              menu.c
*  Letras identificadoras:      MEN
*
*  Nome da base de software:
*  Arquivo da base de software:
*
*  Projeto: Sistema Acadêmico da turma 3WB
*  Gestor:  Grupo 1 / Grupo 2 / Grupo 5
*  Autores:   Bruce Marcellino (Grupo 1)
*			  Bruno Miranda Marinho (Grupo 2)
*             Cristiane Ramalho Guimarães (Grupo 5)
*             Flávio Thiago Franco Vaz (Grupo 2)
*             João Victor Cerqueira (Grupo 2)
*             Matheus Henrique Branco Zeitune (Grupo 2)
*             Vinícius Cortat (Grupo )
*
*  $HA Histórico de evolução:
*     Versão  Autor         Data		Observações
*     1.03    Cristiane  14/11/2017     Reestruturação
*     1.02    Cristiane  08/11/2017     Funções de leitura
*     1.01    Bruce	     07/10/2017     Reestruturação
*     1.00    Bruce	     06/10/2017	    Revisão/finalização
*     0.05    Bruce	     05/10/2017	    Modulo professor
*     0.04    Matheus    04/10/2017  	Revisão menu
*     0.03    Bruno	     02/10/2017	    Menu professor
*     0.02    Flávio     02/10/2017  	Revisão
*     0.01    Matheus    01/10/2017	    Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa o Menu do Sistema Acadêmico a ser desenvolvido.
*     O meu é a chamada dos modulos por interface.
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "menu.h"
#include "corpodiscente.h"
#include "aluno.h"
#include "corpoDocente.h"
#include "gradeCurricular.h"


/***** Declarações encapsuladas pelo módulo *****/

	#define MEN_TAM_STRING 81


/*****  Protótipos das funções encapsuladas no módulo  *****/

	void MEN_leSoLetra ( char * cad_carac ) ;
	void MEN_leCPF ( char * cpf ) ;
	void MEN_leData ( int * dia, int * mes, int * ano ) ;
	void MEN_leUF ( char * UF ) ;
	void MEN_leComplemento ( char * comp ) ;
	void MEN_leEmail ( char * email ) ;
	int MEN_leMatricula ( void ) ;
	int MEN_leNumero ( void ) ;
	int MEN_leTelefone ( void ) ;

/***********************************************************************
*
*  $FC Função: MEN_loginAdministrativo
*
*  $ED Descrição da função
*		Mostra o menu inicial.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retona 1, se os dados são validos.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	int MEN_loginAdministrativo()
	{
		char user[81];
		char senha[81];
		return 1;	// TODO retirar isto
		printf("\nLogin Administrador\n");

		printf("\t\t Dica: use \"admin\", \"admin\".\n");	// TODO retirar isto

		printf("\nDigite a user: ");
		scanf(" %s", user);

		printf("\nDigite a senha: ");
		scanf(" %s", senha);
	
		if(strcmp("admin", user) == 0 && strcmp("admin", senha) == 0 )
		{
			system("cls");
			return 1;
		}

		system("cls");
		return 0;
	}

/***********************************************************************
*
*  $FC Função: MEN_loginProfessor.
*
*  $ED Descrição da função
*		Realiza a busca no corpo docente, se a matricula.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retorna 1, caso econtre e 0, senao.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	int MEN_loginProfessor()
	{
		int mat;

		printf("\nLogin Professor\n");

		printf("\nDigite a matricula (8 digitos): ");
		mat = MEN_leMatricula();
		printf("\n");
		if(CDO_buscaPorMatricula(mat) == CDO_CondRetOk)
		{
			system("cls");
			return 1;
		}

		return 0;
	}

/***********************************************************************
*
*  $FC Função: MEN_loginAluno
*
*  $ED Descrição da função
*		Realiza a busca da matricula do aluno. (não implementado)
*
***********************************************************************/
/*Assertivas: Retorno da função: Rertona 1, se foi encontrado a matricula.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	int MEN_loginAluno(unsigned int *matricula)
	{
		int mat;
		Aluno* Al;

		printf("\nLogin Aluno\n");

		printf("\nDigite a matricula (8 digitos): ");
		mat = MEN_leMatricula();
		printf("\n");

		if(CDI_busca(mat,&Al) == CDI_CondRetAlunoNaoCadastrado)
		{
			printf("Matricula invalida\n");
			printf("Pressione ENTER para voltar ao menu principal...\n");
			getch();
			system("cls");
			return 0;
		}

		*matricula = mat;
		system("cls");
		return 1;
	}

/***********************************************************************
*
*  $FC Função: MEN_adicionaAluno
*
*  $ED Descrição da função
*		Mostra o menu inicial.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retona 1, se os dados são validos.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	void MEN_adicionaAluno()
	{
		char nome[81];
		int mat, telefone;
		Data nasc; 
		Endereco end;
		char cpf_completo[12];
		CPF cpf;
		CDI_tpCondRet retBusca;

		printf ("*********** CADASTRO DE ALUNO ***********\n\n");

		//adiciona aluno
		system("cls");
		printf("\nDigite o nome do aluno: \n");
		scanf(" %80s", nome);

		printf("\nDigite a matricula (8 digitos): \n");
		mat = MEN_leMatricula();
		printf("\n");

		printf("\nDigite o numero do telefone: \n");
		scanf("%d", &telefone);

		printf("\nDigite a data de nascimento: ");
		MEN_leData (&nasc.dia, &nasc.mes, &nasc.ano);
		printf("\n");

		printf("\nDigite o numero do CPF (11 digitos): \n");
		MEN_leCPF(cpf_completo);
		cpf.cod = atoi(cpf_completo+9);
		cpf_completo[9] = '\0';
		cpf.dig3 = atoi(cpf_completo+6);
		cpf_completo[6] = '\0';
		cpf.dig2 = atoi(cpf_completo+3);
		cpf_completo[3] = '\0';
		cpf.dig1 = atoi(cpf_completo);

		printf("\nDigite a sigla estado:\n");
		scanf(" %2s", end.estado);

		printf("\nDigite a cidade:\n");
		scanf(" %s", end.cidade);

		printf("\nDigite o bairro:\n");
		scanf(" %s", end.bairro);

		printf("\nDigite a rua:\n");
		scanf(" %s", end.rua);

		printf("\nDigite o complemento:\n");
		scanf(" %s", end.comp);

		retBusca = CDI_insere(nome, (unsigned int)mat, &cpf, telefone, &nasc, &end);

		if(retBusca == CDI_CondRetAlunoJaCadastrado)
			printf("Aluno ja cadastrado.");
		else
			if (retBusca == CDI_CondRetFaltouMemoria)
				printf("Erro de memoria ao cadastrar.");
			else
				printf("\nAluno cadastrado com sucesso!\n");
	
		printf("Pressione ENTER para voltar ao menu principal...\n");
		getch();
		system("cls");
		return;
	}

/***********************************************************************
*
*  $FC Função: MEN_modificaAluno
*
*  $ED Descrição da função
*		Mostra o menu inicial.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retona 1, se os dados são validos.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	void MEN_modificaAluno()
	{
		char nome[81], cpf_completo[12];
		int mat, telefone, matAnt;
		Data nasc; 
		Endereco end;
		CPF cpf;
		Aluno* Alu;
		int opcao;

		printf("*********** EDITAR DADOS DE PROFESSOR ***********\n\n");

		printf("Digite a matricula do aluno para alterar seus dados: ");
		scanf("%u",&matAnt);
		if (CDI_busca((unsigned int)matAnt,&Alu) != CDI_CondRetOK) 
		{
			printf("Aluno nao encontrado...\n");
			printf("Pressione ENTER para voltar ao menu principal...\n");
			getch();
			return;
		}

		printf("Escolha o dado a ser alterado: \n\n");
		printf("Digite 1: Nome\n");
		printf("Digite 2: Matricula\n");
		printf("Digite 3: Telefone\n");
		printf("Digite 4: Data de Nascimento\n");
		printf("Digite 5: CPF\n");
		printf("Digite 6: Endereco\n");
		scanf("%d",&opcao);

		system("cls");

		switch(opcao)
		{
			case 1: 
				printf("\nDigite o novo nome do aluno: \n");
				scanf(" %s", nome);
				CDI_altera(matAnt,nome,0,NULL,0,NULL,NULL);
				break;
			case 2:
				printf("\nDigite a nova matricula do aluno (8 digitos): \n");
				mat = MEN_leMatricula();
				CDI_altera(matAnt, NULL, (unsigned int)mat, NULL, 0, NULL, NULL);
				break;
			case 3:
				printf("\nDigite o novo telefone do aluno: \n");
				scanf(" %u", &telefone);
				CDI_altera(matAnt, NULL, 0, NULL,telefone, NULL, NULL);
				break;
			case 4:
				printf("\nDigite a nova data de nascimento do aluno: \n");
				MEN_leData (&nasc.dia, &nasc.mes, &nasc.ano);
				CDI_altera(matAnt, NULL, 0, NULL,0,&nasc, NULL);
				break;
			case 5:
				printf("\nDigite o novo CPF do aluno (11 digitos): \n");
				MEN_leCPF(cpf_completo);
				cpf.cod = atoi(cpf_completo+9);
				cpf_completo[9] = '\0';
				cpf.dig3 = atoi(cpf_completo+6);
				cpf_completo[6] = '\0';
				cpf.dig2 = atoi(cpf_completo+3);
				cpf_completo[3] = '\0';
				cpf.dig1 = atoi(cpf_completo);
				CDI_altera(matAnt, NULL, 0, &cpf, 0, NULL, NULL);
				break;
			case 6:
				printf("\nDigite a sigla do estado: \n");
				scanf(" %s", end.estado);
				printf("\nDigite a cidade: \n");
				scanf(" %s", end.cidade);
				printf("\nDigite o bairro: \n");
				scanf(" %s", end.bairro);
				printf("\nDigite a rua: \n");
				scanf(" %s", end.rua);
				printf("\nDigite o complemento:\n");
				scanf(" %s", end.comp);
				CDI_altera(matAnt, NULL,0,NULL,0, NULL, &end);
				break;
			default:
				printf("Opcao invalida...");
				break;
		}

		printf("\nDados alterados com sucesso!\n");
		printf("Pressione ENTER para voltar ao menu principal...\n");
		getch();
		system("cls");
		return;
	}

/***********************************************************************
*
*  $FC Função: MEN_adicionaProfessor
*
*  $ED Descrição da função
*		Mostra o menu inicial.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retona 1, se os dados são validos.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	void MEN_adicionaProfessor()
	{
		int rg, matricula, telefone;
		int dia, mes, ano;
		char nome[MEN_TAM_STRING], cpf[MEN_TAM_STRING], email[MEN_TAM_STRING];
		char pais[MEN_TAM_STRING], uf[MEN_TAM_STRING], cidade[MEN_TAM_STRING], bairro[MEN_TAM_STRING], rua[MEN_TAM_STRING], complemento[MEN_TAM_STRING];
		int numero;
		CDO_tpCondRet ret;

		system("cls");
		printf ("*********** CADASTRO DE PROFESSOR ***********\n\n");

		//Adiciona professor
		printf("Digite o nome: \n");
		scanf(" %80s", nome);

		printf("\nDigite o RG: \n");
		scanf("%d", &rg);

		printf("\nDigite o CPF (11 digitos): \n");
		MEN_leCPF(cpf);

		printf("\nDigite a matricula (8 digitos): \n");
		matricula = MEN_leMatricula();

		printf("\nDigite o telefone: \n");
		scanf("%d", &telefone);

		printf("\nDigite a data de nascimento: \n");
		MEN_leData (&dia, &mes, &ano);

		printf("\nDigite o pais: \n");
		scanf(" %s", pais);

		printf("\nDigite o email: \n");
		scanf(" %s", email);

		printf("\nDigite o estado:\n");
		scanf(" %2s", uf);

		printf("\nDigite a cidade:\n");
		scanf(" %s", cidade);
		
		printf("\nDigite o bairro:\n");
		scanf(" %s", bairro);

		printf("\nDigite a rua:\n");
		scanf(" %s", rua);

		printf("\nDigite a numero:\n");
		numero = MEN_leNumero();

		printf("\nDigite o complemento:\n");
		scanf(" %s", complemento);

		ret = CDO_cadastra(nome, rg, cpf, matricula, email, telefone, dia, mes, ano, pais, uf, cidade, bairro, rua, numero, complemento);
		if(ret == CDO_CondRetOk)
			printf("\nAlteracao realizada com sucesso!\n");
		else if(ret == CDO_CondRetFormatoInvalido)
			printf("\nERRO. Formato de dados invalido.\n");
		else if(ret == CDO_CondRetIdJaCriado)
			printf("\nERRO. Ja existe um professor com este valor de identificacao.\n");
		CDO_mostraAtual();
	}

/***********************************************************************
*
*  $FC Função: MEN_modificaProfessor
*
*  $ED Descrição da função
*		Mostra o menu inicial.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retona 1, se os dados são validos.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	void MEN_modificaProfessor()
	{
		char nomeFunc[][20] ={"sair",  "alterar o Nome", "alterar o RG","alterar o CPF","alterar a Matricula", "alterar o email", "alterar o Telefone", "alterar a Data", "alterar o Endereco"};
		int nAlteras = 9, i;
		CDO_alteraInt funcInt[] = {NULL, NULL, CDO_alteraRg, NULL, CDO_alteraMatricula, NULL,CDO_alteraTelefone, NULL, NULL};
		CDO_alteraString funcString[] = {NULL, CDO_alteraNome, NULL, CDO_alteraCpf, NULL, CDO_alteraEmail, NULL,NULL,NULL};
		int paramInt, dia, mes, ano;
		char paramString[MEN_TAM_STRING];
		char pais[MEN_TAM_STRING], uf[MEN_TAM_STRING], cidade[MEN_TAM_STRING], bairro[MEN_TAM_STRING], rua[MEN_TAM_STRING], complemento[MEN_TAM_STRING];
		int numero;
		CDO_tpCondRet ret;
		int opcao;

		system("cls");
		printf("\n*********** EDITAR DADOS DE PROFESSOR ***********\n");

		printf("Digite a matrícula do professor que deseja modificar (8 digitos):\n");
		paramInt = MEN_leMatricula();
		if(CDO_buscaPorMatricula(paramInt)!=CDO_CondRetOk){
			printf("Não existe professor cadastrado com este numero de matricula %d, por favor tente novamente\n", paramInt);
			return;
		}
		CDO_mostraAtual();
		do{
			for(i=0;i<nAlteras;i++)
				printf("Digite %d: %s.\n", i, nomeFunc[i]);
			scanf("%d", &opcao);
			if(opcao>=nAlteras || opcao<1) return;
			else if( opcao==nAlteras-2){//data
				printf("\nDigite a data de nascimento: \n");
				printf("Dia: \n");
				scanf("%d", &dia);
				printf("Mes: \n");
				scanf("%d", &mes);
				printf("Ano: \n");
				scanf("%d", &ano);
				ret = CDO_alteraDataNascimento(dia, mes, ano);
			} else if( opcao==nAlteras-1){//endereco
				printf("\nDigite o novo pais:\n");
				scanf(" %s", pais);
				printf("\nDigite o novo estado:\n");
				scanf(" %2s", uf);
				printf("\nDigite a nova cidade:\n");
				scanf(" %s", cidade);
				printf("\nDigite o novo bairro:\n");
				scanf(" %s", bairro);
				printf("\nDigite a nova rua:\n");
				scanf(" %s", rua);
				printf("\nDigite o novo numero:\n");
				numero = MEN_leNumero();
				printf("\nDigite o novo complemento:\n");
				scanf(" %s", complemento);
				ret = CDO_alteraEndereco(pais, uf, cidade, bairro, rua, numero, complemento);
			}
			else{
				printf("Digite o novo valor para %s.\n", nomeFunc[opcao]);
				if(funcInt[opcao]!= NULL){
					scanf("%d", &paramInt);
					ret = funcInt[opcao](paramInt);
				} else if (funcString[opcao]!= NULL){
					scanf(" %s", paramString);
					ret = funcString[opcao](paramString);
				} else break;
			}
			if(ret == CDO_CondRetOk)
				printf("Alteracao realizada com sucesso!\n");
			else if(ret == CDO_CondRetFormatoInvalido)
				printf("ERRO. Formato de dados invalido.\n");
			else if(ret == CDO_CondRetIdJaCriado)
				printf("ERRO. Ja existe um professor com este valor de identificacao.\n");
			CDO_mostraAtual();
		}while(opcao);
	}

/***********************************************************************
*
*  $FC Função: MEN_modificaProfessor
*
*  $ED Descrição da função
*		Mostra o menu inicial.
*
***********************************************************************/
/*Assertivas: Retorno da função: Retona 1, se os dados são validos.
/			 Parâmentros: Estruturas de ponteiros.
***********************************************************************/

	void MEN_menuGradeCurricular()
	{
		char nomeFunc[][40] ={"sair", "adicionar disciplina" , "mostrar a disciplina atual", "buscar outra disciplina", "mostrar todas as disciplinas", "inserir um Pre-Requisito", "remover todos os Pre-Requisitos", "Limpar a grade Curricular"};
		int nItens = 8, i;
		int creditos;
		char nome[MEN_TAM_STRING], codigo[MEN_TAM_STRING], bibliografia[MEN_TAM_STRING], ementa[MEN_TAM_STRING];
		GRC_tpCondRet ret;
		int opcao;

		printf("\nMenu Disciplina\n");
		do{
			for(i=0;i<nItens;i++)
				printf("Digite %d: %s.\n", i, nomeFunc[i]);
			scanf("%d", &opcao);

			switch(opcao){
				case 1:

					printf("\nDigite o nome:\n");
					scanf(" %s", nome);
					printf("\nDigite o codigo:\n");
					scanf(" %s", codigo);
					printf("\nDigite o numero de creditos:\n");
					scanf(" %d", &creditos);
					printf("\nDigite a bibliografia:\n");
					scanf(" %s", bibliografia);
					printf("\nDigite a ementa:\n");
					scanf(" %s", ementa);
					ret = GRC_cadastra(nome, codigo, creditos, bibliografia, ementa, 3);
					break;
				case 2:
					GRC_mostraAtual();
					break;
				case 3:
					printf("Digite o código da disciplina que deseja buscar:\n");
					scanf(" %s", codigo);
					ret = GRC_buscaPorCodigo(codigo);
					GRC_mostraAtual();
					break;
				case 4:
					GRC_mostraTodas();
					break;
				case 5:
					printf("Digite o código da disciplina que deseja configurar como pre-requisito:\n");
					scanf(" %s", codigo);
					ret = GRC_inserePreRequisito(codigo);
					break;
				case 6:
					GRC_removePreRequisitos();
					break;
				case 7:
					GRC_limpa();
					break;
				default:
					if(opcao)
						printf("Opcao inválida!\n");
					break;
			}
			if(ret == GRC_CondRetOk)
				printf("Operacao realizada com sucesso!\n");
			else if(ret == GRC_CondRetNaoHaMemoria)
				printf("ERRO. Nao ha memoria suficiente.\n");
			else if(ret == GRC_CondRetGradeCurricularVazia)
				printf("Ainda nao existe nenhuma disciplina cadastrada.\n");
			else if(ret == GRC_CondRetDisciplinaNaoEncontrada)
				printf("A disciplina solicitada nao foi encontrada.\n");
			else if(ret == GRC_CondRetIdJaCriado)
				printf("ERRO.Ja existe uma Disciplina com este codigo.\n");
			else if(ret == GRC_CondRetFormatoInvalido)
				printf("ERRO. Formato de dados invalido.\n");
			GRC_mostraAtual();
		}while(opcao);
	}

/***********************************************************************
*
*  $FC Função: MEN_leSoLetra
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar letras (maiúscula ou minúscula) e espaço (Space).
*     Limita a quantidade de caracteres em no máximo 80.
*     A cadeia de caracteres não pode ficar vazia.     
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/

	void MEN_leSoLetra ( char * cad_carac )
	{
		unsigned char a;
		int cont = 0 ;

		do
		{
			a = getch() ;
			
			if ( (isalpha(a) || a == ' ') && cont < MEN_TAM_STRING-1 )
			{			
				cad_carac [cont] = (char) a ;
				printf("%c", cad_carac[cont]) ;
				cont++ ;
			} 
			else 
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					cad_carac [cont] = '\0' ;
				} /* if */
		} while ( cont == 0 || (a != 13 && cont <= MEN_TAM_STRING-1) ) ; // 13 = Enter

		cad_carac[cont] = '\0' ;

		printf("\n");

	}
	
	
/***********************************************************************
*
*  $FC Função: MEN_leCPF
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar apenas números (1,2,3,4,5,6,7,8,9,0).
*     Só finaliza a leitura após digitar, obrigatoriamente, so 11 dígitos correspondentes ao CPF.
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/

	void MEN_leCPF ( char * cpf )
	{
		unsigned char a ;
		int cont = 0 ;

		do
		{
			a = getch() ;

			if ( isdigit(a) && cont < MEN_TAM_CPF-1 )
			{			
				cpf [cont] = (char) a ;
				printf("%c", cpf[cont]) ;
				cont++ ;
			} 
			else
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					cpf[cont] = '\0' ;
				} /* if */
		} while ( cont < MEN_TAM_CPF-1 || (a != 13 && cont == MEN_TAM_CPF-1) ); // 13 = Enter

		cpf[cont] = '\0' ;

		printf ("\n") ;
	}

/***********************************************************************
*
*  $FC Função: MEN_leData                       
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar apenas números (1,2,3,4,5,6,7,8,9,0).
*     Efetua a leitura do dia, obrigatoriamente, menor ou igual 31.
*     Efetua a leitura do mês, obrigatoriamente, menor ou igual 12.
*     Verifica se o dia informado ultrapassa o número de dias corresponde ao mês informado, 
*          caso ultrapasse solicita novamente o dia e o mês. 
*     Efetua a leitura do ano, obrigatoriamente, maior ou igual a 1850.
*     Verifica se o ano informado é menor que 1850, caso seja solicita o ano.      		
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/

	void MEN_leData ( int * dia, int * mes, int * ano )
	{
		static int maxDias[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ; 
		unsigned char a ;
		char D_dia[3], D_mes [3], D_ano [5] ; 
		int cont = 0 ;

		do // verifica se o número do dia corresponde ao número máximo de dias do mês informado
		{
			// DIA
			do // verifica se o dia é maior que 31
			{
				printf("   Dia: ") ; 
				do
				{
					a = getch() ;
					
					if ( isdigit(a) && cont < 2 )
					{			
						D_dia [cont] = (char) a ;
						printf("%c", D_dia[cont]) ;
						cont++ ;
					} 
					else
						if (a==8 && cont) // 8 = BackSpace
						{
							printf("\b \b") ;
							cont-- ;
							D_dia [cont] = '\0' ;
						} /* if */
				} while ( cont == 0 || (a != 13 && cont <= 2 ) ) ; // 13 = Enter

				D_dia[cont] = '\0' ;
				* dia = atoi(D_dia) ;
			
				if (* dia > 31)
				{
					printf ("\n   Dia inválido. Digite o dia novamente.\n") ;
					cont = 0 ;
				}
			} while ( * dia > 31 ) ;

			cont = 0 ;

			//MES
			do {
				printf("\n   Mes: "); 
				do
				{
					a = getch() ;

					if ( isdigit(a) && cont < 2 )
					{			
						D_mes [cont] = (char) a ;
						printf("%c", D_mes[cont]) ;
						cont++ ;
					} 
					else
						if ( a==8 && cont ) // 8 = BackSpace
						{
							printf("\b \b") ;
							cont-- ;
							D_mes[cont] = '\0' ;
						} /* if */
				} while ( cont == 0 || (a != 13 && cont <= 2 ) ) ; // 13 = Enter

				D_mes[cont] = '\0' ;
				* mes = atoi(D_mes) ;
			
				if (* mes > 12)
				{
					printf ("\n   Mes inválido. Digite o mes novamente.") ;
					cont = 0 ;
				}
			} while ( * mes > 12 ) ;

			if ( * dia > maxDias [* mes - 1])
			{
				printf ("\n   Dia invalido para o mes informado. Digite o dia e o mes novamente.\n") ;
				cont = 0 ;
			}

		} while ( * dia > maxDias [* mes - 1] ) ;

		cont = 0 ;
		
		//ANO
		do 
		{
			printf("\n   Ano: ") ; 
			do
			{
				a = getch() ;

				if ( isdigit(a) && cont < 4 )
				{			
					D_ano [cont] = (char) a ;
					printf("%c", D_ano[cont]) ;
					cont++ ;
				} 
				else
					if ( a==8 && cont ) // 8 = BackSpace
					{
						printf("\b \b") ;
						cont-- ;
						D_ano[cont] = '\0' ;
					} /* if */
			} while ( cont < 4 || (a != 13 && cont == 4) ) ; // 13 = Enter

			D_ano[cont] = '\0' ;
			* ano = atoi(D_ano) ;
		
			if ( * ano < MEN_MIN_ANO )
			{
				printf ("\n   Ano inválido. Digite o ano novamente.") ;
				cont = 0;
			}

		} while ( * ano < MEN_MIN_ANO ) ;

		printf("\n") ;

	}
	
/***********************************************************************
*
*  $FC Função: MEN_leUF
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar letras (maiúscula ou minúscula), 
*          caso seja digitado letra minúscula, troca-se para maniúscula. 
*     É obrigatório digitar as duas letras correspondentes a sigla de uma UF válida,
*          caso informe uma UF inválida solicita novamente a sigla da UF.	
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/
	
	void MEN_leUF ( char * UF )
	{
		unsigned char a ;
		int cont = 0, i;
		char estados [][3]= {"AC","AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS", "MG",
			"PA", "PB", "PR", "PE", "PI", "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"};

		do {
			do
			{
				a = getch() ;

				if (islower(a))
					a = toupper(a);

				if ( isupper(a) && cont < MEN_TAM_UF-1 )
				{			
					UF [cont] = (char) a ;
					printf("%c", UF[cont]) ;
					cont++ ;
				} 
				else
					if (a==8 && cont) // 8 = BackSpace
					{
						printf("\b \b") ;
						cont-- ;
						UF[cont] = '\0' ;
					} /* if */
			} while ( cont < MEN_TAM_UF-1 || (a != 13 && cont == MEN_TAM_UF-1 ) ) ; // 13 = Enter

		UF[cont] = '\0' ;

		i = 0 ;

		while ( i < MEN_QTD_EST && strcmp (UF, &estados [i][0]) )
		{
			i++ ;
		}

		if ( i == MEN_QTD_EST )
		{
			printf ("\nEsta sigla de estado não existe. Digite uma sigla correspondente a um estado brasileiro.\n\n") ;
			cont = 0 ;
		} /* if */

		} while ( i == MEN_QTD_EST ) ;

		printf("\n") ;

	}

/***********************************************************************
*
*  $FC Função: MEN_leComplemento
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar letras (maiúscula ou minúscula), números (1,2,3,4,5,6,7,8,9,0),
*          espaço (Space), ponto final (.), vírgula (,), ponto e vírgula (;), parênteses (()) e sinal de menos (-).
*     Limita a quantidade de caracteres em no máximo 80.
*     A cadeia de caracteres pode ficar vazia.     	
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/
	
	void MEN_leComplemento ( char * comp ) 
	{
		unsigned char a;
		int cont = 0 ;

		do
		{
			a = getch() ;
			
			if ( (isalpha(a) || isdigit(a) || a == ' ' || a == ',' || a == '.' || a == ';' || a == '(' ||
				a == ')' || a == '-') && cont < MEN_TAM_STRING-1 )
			{			
				comp [cont] = (char) a ;
				printf("%c", comp[cont]) ;
				cont++ ;
			} 
			else 
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					comp [cont] = '\0' ;
				} /* if */
		} while (a != 13 && cont <= MEN_TAM_STRING-1) ; // 13 = Enter

		comp[cont] = '\0' ;
		
		printf("\n") ;

	}
	
/***********************************************************************
*
*  $FC Função: MEN_leEmail
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar letras minúscula, números (1,2,3,4,5,6,7,8,9,0),
*          ponto final (.), vírgula (,), ponto e vírgula (;), parenteses (()) e sinal de menos (-).
*     Limita a quantidade de caracteres em no máximo 80.
*     A cadeia de caracteres não pode ficar vazia.     		
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/
	
	void MEN_leEmail ( char * email ) 
	{
		unsigned char a;
		int cont = 0 ;

		do
		{
			a = getch() ;
			
			if ( (islower(a) || isdigit(a) || a == '.' || a == '@' || a == '_' ||
				a == '-') && cont < MEN_TAM_STRING-1 )
			{			
				email [cont] = (char) a ;
				printf("%c", email[cont]) ;
				cont++ ;
			} 
			else 
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					email [cont] = '\0' ;
				} /* if */
		} while ( cont < 5 || (a != 13 && cont <= MEN_TAM_STRING-1) ) ; // 13 = Enter

		email[cont] = '\0' ;
		
		printf("\n") ;

	}

/***********************************************************************
*
*  $FC Função: MEN_leMatricula
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar apenas numeros (1,2,3,4,5,6,7,8,9,0).
*     Só finaliza a leitura após digitar, obrigatoriamente, os 8 digitos correspondentes a matricula.	
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/

	int MEN_leMatricula ( void )
	{
		unsigned char a ;
		char mat[MEN_TAM_MAT] ; 
		int cont = 0 ;

		do
		{
			a = getch() ;

			if ( isdigit(a) && cont < MEN_TAM_MAT-1 )
			{			
				mat [cont] = (char) a ;
				printf("%c", mat[cont]) ;
				cont++ ;
			} 
			else
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					mat[cont] = '\0' ;
				} /* if */
		} while ( cont < MEN_TAM_MAT-1 || (a != 13 && cont == MEN_TAM_MAT-1) ); // 13 = Enter

		mat[cont] = '\0' ;

		return atoi(mat) ;

	}

/***********************************************************************
*
*  $FC Função: MEN_leNumero
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar apenas numeros (1,2,3,4,5,6,7,8,9,0).
*     Só finaliza a leitura após digitar, obrigatoriamente, um número de até 8 casas.	
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/

	int MEN_leNumero ( void )
	{
		unsigned char a ;
		char num[9] ; 
		int cont = 0 ;

		do
		{
			a = getch() ;

			if ( isdigit(a) && cont < 8 )
			{			
				num [cont] = (char) a ;
				printf("%c", num[cont]) ;
				cont++ ;
			} 
			else
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					num[cont] = '\0' ;
				} /* if */
		} while ( cont == 0 || (a != 13 && cont <= 8 ) ) ; // 13 = Enter

		num[cont] = '\0' ;

		printf("\n") ;

		return atoi(num) ;

	}
	
/***********************************************************************
*
*  $FC Função: MEN_leTelefone
*
*  $ED Descrição da função
*	  Efetua a leitura do teclado permitindo digitar apenas numeros (1,2,3,4,5,6,7,8,9,0).
*     Só finaliza a leitura após digitar, obrigatoriamente, o número de telefone com 8 ou 9 dígitos.		
*
***********************************************************************/
/*Assertivas: 
/			 
***********************************************************************/
	
	int MEN_leTelefone ( void ) 
	{
		unsigned char a ;
		char num[MEN_TAM_TEL] ; 
		int cont = 0 ;

		do
		{
			a = getch() ;

			if ( isdigit(a) && cont < MEN_TAM_TEL-1 )
			{			
				num [cont] = (char) a ;
				printf("%c", num[cont]) ;
				cont++ ;
			} 
			else
				if (a==8 && cont) // 8 = BackSpace
				{
					printf("\b \b") ;
					cont-- ;
					num[cont] = '\0' ;
				} /* if */
		} while ( cont < MEN_TAM_TEL-2 || ( a != 13 && cont <= MEN_TAM_TEL-1 ) ) ; // 13 = Enter

		num[cont] = '\0' ;

		printf("\n");

		return atoi(num) ;
	
	}



	
	
	
	

