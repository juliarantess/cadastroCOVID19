//Bibliotecas
#include <stdio.h> /* I/O */
#include <stdlib.h> /* system() */
#include <locale.h> /* acentuação */
#include <string.h> /* manipulação de strings */
#define QUANTIDADE 5 /* quantidade de registros (linhas) aceitos */
#define USUARIO 2
#define ANOATUAL 2020


//vars: Globais
char nome[QUANTIDADE][50];
char CPF[QUANTIDADE][12];
char telefone[QUANTIDADE][15];
char email[QUANTIDADE][50];
char dataDiagnostico[QUANTIDADE][11];

//vars: endereco completo
char rua[QUANTIDADE][50];
int numero[QUANTIDADE];
char bairro[QUANTIDADE][50];
char cidade[QUANTIDADE][50];
char estado[QUANTIDADE][50];
char CEP[QUANTIDADE][10];

//vars: data nascimento
int nascDia[QUANTIDADE];
int nascMes[QUANTIDADE];
int nascAno[QUANTIDADE];
int idade[QUANTIDADE];

//vars:comorbidade
int comorbidadeFlag[QUANTIDADE];
char comorbidade[QUANTIDADE][100];
int grupoRisco[QUANTIDADE];

//vars: login sistema
char nomeUsuario[USUARIO][50];
char usuario[USUARIO][20];
char senha[USUARIO][16];

//vars: Auxiliares
int opcao;

//vars: ARQUIVO
FILE *arq; //ponteiro de nome arq tipo FILE: armazenará o endereço de um arquivo


//Protótipo das funções
void cadastrarUsuario();
void logarSistema();
void menu();
void cadastrarPaciente();
void listarPacientes();
void buscarPaciente();
int gerarArquivoCadastro(int i);
int validarGrupoRisco(int i);
int gerarArquivoGrupoRisco(int i);


//FUNÇÃO PRINCIPAL
int main(void)
{
    //acentuação
    setlocale(LC_ALL, "Portuguese");

    //início do programa
    cadastrarUsuario();
    logarSistema();

} //Fim main()


//Definição das funções
void cadastrarUsuario()
{
    printf("\n------------------CADASTRAR USUÁRIO------------------\n");
    printf("\nDigite o nome: ");
    scanf(" %[^\n]s", &nomeUsuario);

    printf("\nDigite o usuário: ");
    scanf(" %[^\n]s", &usuario);

    printf("\nDigite a senha: ");
    scanf(" %[^\n]s", &senha);

    printf("\nUsuário cadastrado com sucesso!\n");
    system("pause");
} //Fim cadastrarUsuario()

void logarSistema()
{
    char buscaUsuario[20], buscaSenha[16];
    int i;

    system("cls");

    printf("\n------------------LOGIN DO USUÁRIO------------------\n");
    printf("\nDigite o usuário de login: ");
    scanf(" %[^\n]s", &buscaUsuario);

    printf("\nDigite a senha: ");
    scanf(" %[^\n]s", &buscaSenha);

    for(i=0; i<USUARIO; i++)
    {
        if(strcmp(usuario[i], buscaUsuario) == 0 && strcmp(senha[i], buscaSenha) == 0)
        {
            printf("\nLogin realizado com sucesso!\n");
            system("pause");

            menu();
            return 0;
        }else{
            printf("\nLogin ou senha incorretos! Tente novamente!\n");
            system("pause");

            logarSistema();
            return 1;
        }
    }
} //Fim logarSistema()

void menu()
{
    do{
            system("cls");
            printf("\n------------------MENU------------------\n");
            printf("\n1 - Cadastrar paciente\n2 - Listar todos pacientes\n3 - Pesquisar paciente\n4 - Sair\n");
            scanf("%d", &opcao);

            switch(opcao)
            {
            case 1:
                cadastrarPaciente();
                break;
            case 2:
                listarPacientes();
                break;
            case 3:
                buscarPaciente();
                break;
            case 4:
                system("exit");
                break;
            default:
                printf("\nOpção inválida!\n");
                system("pause");
            }
    }while(opcao !=4 ); //continua executando o programa
} //Fim menu()

void cadastrarPaciente()
{
    //static: nunca perderá seu valor independente de onde é utilizada
    static int registro;

    do{
        system("cls");

        printf("\n------------------CADASTRAR PACIENTE------------------\n");
        printf("\nDigite o nome: ");
        scanf(" %[^\n]s", &nome[registro]);

        printf("\nDigite o CPF: ");
        scanf("%s", &CPF[registro]);

        printf("\nDigite o telefone: ");
        scanf("%s", &telefone[registro]);

        printf("\nA seguir, informe o endereço completo: \n");
        printf("Rua: ");
        scanf(" %[^\n]s", &rua[registro]);
        printf("\nNúmero: ");
        scanf("%d", &numero[registro]);
        printf("\nBairro: ");
        scanf(" %[^\n]s", &bairro[registro]);
        printf("\nCidade: ");
        scanf(" %[^\n]s", &cidade[registro]);
        printf("\nEstado: ");
        scanf(" %[^\n]s", &estado[registro]);
        printf("\nCEP: ");
        scanf("%s", &CEP[registro]);

        printf("\nA seguir, informe sobre a data de nascimento: ");
        printf("\nDia: ");
        scanf("%d", &nascDia[registro]);
        printf("\nMês: ");
        scanf("%d", &nascMes[registro]);
        printf("\nAno: ");
        scanf("%d", &nascAno[registro]);

        printf("\nDigite o e-mail: ");
        scanf("%s", &email[registro]);

        printf("\nDigite a data do diagnóstico (DD/MM/AAAA): ");
        scanf("%s", &dataDiagnostico[registro]);

        printf("\nPossui alguma comorbidade:\n1-SIM       2-NÃO\n");
        scanf("%d", &comorbidadeFlag[registro]);

        if(comorbidadeFlag[registro] == 1)
        {
            printf("\nSe sim, qual(s)? ");
            scanf(" %[^\n]s", &comorbidade[registro]);
        }else{
            printf("Não há nenhuma comorbidade\n");
        }

        //arquivo com TODOS os dados do paciente
        gerarArquivoCadastro(registro);

        //verificação: idade e inclusão no grupo de risco
        validarGrupoRisco(registro);

        printf("\nDigite 1 para continuar cadastrando ou 2 para voltar ao menu\n");
        scanf("%d", &opcao);

        //incrementar: gerar novo registro do paciente
        registro++;
    }while(opcao == 1);
} //Fim cadastrarPaciente()

void listarPacientes()
{
    int i;

    system("cls");
    printf("\n------------------LISTAR PACIENTES------------------\n\n");

    for(i=0; i<QUANTIDADE; i++)
    {
        if(strlen(CPF[i]) > 0)
        {
            printf("Nome: %s\
                       \nCPF: %s\
                       \nTelefone: %s\
                       \nData de nascimento: %d\/%d/%d\
                       \nEndereço: %s, número: %d, %s - Cidade: %s, %s - CEP: %s\
                       \nE-mail: %s\
                       \nData do diagnóstico: %s\
                       \nComorbidade: %s\n-----------------------\n", nome[i], CPF[i], telefone[i], nascDia[i], nascMes[i], nascAno[i], rua[i], numero[i], bairro[i], cidade[i], estado[i], CEP[i], email[i], dataDiagnostico[i], comorbidade[i]);
        }else{
            break;
        }
    }

    system("pause");
} //Fim listarPacientes()

void buscarPaciente()
{
    char buscaCPF[12];
    int i;

    do{
        system("cls");

        printf("\n------------------PESQUISAR PACIENTE------------------\n");
        printf("\nDigite o CPF do paciente desejado: ");
        scanf("%s", buscaCPF);

        for(i=0; i<QUANTIDADE; i++)
        {
            if(strcmp(CPF[i], buscaCPF) == 0)
            {
                printf("Nome: %s\
                       \nCPF: %s\
                       \nTelefone: %s\
                       \nData de nascimento: %d\/%d/%d\
                       \nEndereço: %s, número: %d, %s - Cidade: %s, %s - CEP: %s\
                       \nE-mail: %s\
                       \nData do diagnóstico: %s\
                       \nComorbidade: %s\n-----------------------\n", nome[i], CPF[i], telefone[i], nascDia[i], nascMes[i], nascAno[i], rua[i], numero[i], bairro[i], cidade[i], estado[i], CEP[i], email[i], dataDiagnostico[i], comorbidade[i]);
            }
        }

        printf("\nDigite 1 para continuar pesquisando ou 2 para voltar ao menu\n");
        scanf("%d", &opcao);

    }while(opcao == 1);
} //Fim buscarPaciente()


int gerarArquivoCadastro(int i)
{
    //aqui serão incluídos TODOS os dados do paciente

    arq = fopen("dadosPacienteCOMPLETO.txt", "a"); //modos: r = gravação, w = leitura, a = adicionar dados;

    //verificar se o arquivo está funcionando
    if(arq == NULL)
    {
        printf("Erro ao acessar. Tente novamente!\n");
        return 1; //erro na execução
    }else{
        if(strlen(CPF[i]) > 0) //salva no arquivo somente os registros existentes
            {
                fprintf(arq, "Nome: %s\nCPF: %s\nTelefone: %s\
                        \nEndereço: %s, número %d, %s - %s, %s - CEP: %s\
                        \nData de nascimento: %d/%d/%d\nE-mail: %s\nData do diagnóstico: %s\
                        \nComorbidade: %s\n------------------\n", nome[i], CPF[i], telefone[i], rua[i], numero[i], bairro[i], cidade[i], estado[i], CEP[i], nascDia[i], nascMes[i], nascAno[i], email[i], dataDiagnostico[i], comorbidade[i]);
            }
        }

    printf("\nDados gravados com sucesso!\n");

    fclose(arq);
    return 0; //sucesso na execução;
} //Fim gerarArquivoCadastro()


int validarGrupoRisco(int i)
{
    if(strlen(CPF[i]) > 0)
    {
        //calcular idade
        idade[i] = (ANOATUAL - nascAno[i]);
        //printf("Idade: %d\n", idade[i]);

        //valida grupo de risco
        if (idade[i] > 65 || comorbidadeFlag[i] == 1)
        {
            printf("\nATENÇÃO: o paciente faz parte do grupo de risco. Um arquivo incluindo os dados do paciente será gerado.\n");
            gerarArquivoGrupoRisco(i);
        }else{
            printf("\nO paciente não faz parte do grupo de risco.\n");
        }
    }

    system("pause");
    return 0;
} //Fim validarGrupoRisco()

int gerarArquivoGrupoRisco(int i)
{
    //aqui serão incluídos SOMENTE CEP e idade do paciente

    arq = fopen("dadosGrupoRisco.txt", "a"); //modos: r = gravação, w = leitura, a = adicionar dados;

    //verificar se o arquivo está funcionando
    if(arq == NULL)
    {
        printf("Erro ao acessar. Tente novamente!\n");
        return 1; //erro na execução
    }else{
        if(strlen(CPF[i]) > 0) //salva no arquivo somente os registros existentes
        {
            fprintf(arq, "Nome: %s\nCEP: %s\nIdade: %d\n------------------\n", nome[i], CEP[i], idade[i]);
        }
    }

    printf("\nDados gravados com sucesso!\n");

    fclose(arq);
    return 0; //sucesso na execução;
} //Fim gerarArquivoGrupoRisco()
