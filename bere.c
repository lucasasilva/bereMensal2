#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//esta struct torna o armazenamento e varredura dos produtos que a berê vende
// mais fáceis de manusear
typedef struct
{
    int codigo;
    float preco;
}Produtos;

/****************************Funçoes de menu************************/
void fMenu(); // Menu inicial
//void fAberturaCaixa();
//void fFechaCaixa();

/****************************Processamento da venda*****************/
//MATERIAIS DE LIMPEZA
void fMateriaisLimpeza();
float fRetornaTotalMatLimpeza(int produto, int quantidade);
//PADARIA

//Alimentos e Bebidas
    void fPadaria();
    float fRetornaTotalPadaria(int produto, int quantidade);
//A&B
void fAlimentoseBebidas();
float fRetornaTotalAlimentos(int produto, int quantidade);

/****************************Processamento pagamento****************/
void fExibeTotalCompraAtual(float iExibeTotaisCompraAtual[]);//exibe menu de pagamento
float fRetornaTotalBrutoCompra(float iVetorVendaAtual[]); //prepara a somatória do que será usado para o pagamento

/*-----calculo de desconto---------------*/
float fCalculaDescontoMenor(float iTotalCompra);
float fCalculaDescontoMaior(float iTotalCompra, float iPercentDescont);

/*Processa o pagamento, zera variáveis, condiciona totais por forma de pagamento*/
void fProcessaPagamento(int iFormapag);

void main () {
    /*Armazena os totais por categoria sendo a seguinte lógica:
    vetor[0] = Materiais de limpeza
    vetor[1] = Padaria
    vetor[2] = A&B
    Como ocorrerão atribuições mais a frente, inicia todas as posições com zero
    para evitar lixo na memória*/

    float vArmazenaTotaisVendas[3]={0};// Este armazena os totais para o fechamento de caixa
    float vArmazetaTotaisVendaAtual[4]={0}; //Este armazena o total da venda atual, e é zerado após o informe do pagamento

    /*armazena os totais pagos, para exibir no fechamento;
    vetor[0] = Valor a pagar na compra atual,
    vetor[1] = Total pago em dinheiro até agora,
    vetor[2] = Total pago em cartão até agora

    vetor[0] deverá ser zerado após cada pagamento*/
    float vArmazenaTotaisFPag[3]={0};

    int vMenu, vFPag;
    int vProduto = 0;
    int vQuantidade = 0;
    float vValorPagar;
    float vDesconto;
    fMenu();
    fscanf(stdin,"%d",&vMenu);
    do
    {
        switch (vMenu)
        {
        case 1: /*Seleção de Menu de Materiais de Limpeza*/
            do{
                fMateriaisLimpeza();
                fscanf(stdin,"%d",&vProduto);
                if (vProduto <= 6)
                    break;
                printf("Agora informe a quantidade:\n");
                getchar();
                fscanf(stdin,"%d",&vQuantidade);
                vArmazenaTotaisVendas[0] += fRetornaTotalMatLimpeza(vProduto, vQuantidade);
                vArmazetaTotaisVendaAtual[0] += fRetornaTotalMatLimpeza(vProduto, vQuantidade);
                vArmazetaTotaisVendaAtual[3] += fRetornaTotalMatLimpeza(vProduto, vQuantidade);//armazena aqui para que seja posssível usar na forma de pagamento, mais tarde
                getchar();
            } while(vProduto >6);
            break;
        case 2:/*Seleção de Menu de Alimentos e Bebidas*/
            do{
                fAlimentoseBebidas();
                fscanf(stdin,"%d",&vProduto);
                if (vProduto <= 6)
                    break;
                printf("Agora informe a quantidade:\n");
                getchar();
                fscanf(stdin,"%d", &vQuantidade);
                vArmazenaTotaisVendas[2] += fRetornaTotalAlimentos(vProduto, vQuantidade);
                vArmazetaTotaisVendaAtual[2] += fRetornaTotalAlimentos(vProduto, vQuantidade);
                vArmazetaTotaisVendaAtual[3] += fRetornaTotalAlimentos(vProduto, vQuantidade);//Armazena para a forma de pagamento.
                getchar();
            } while (vProduto >6);
            break;
        case 3:
            do{
                fPadaria();
                fscanf(stdin,"%d",&vProduto);
                if (vProduto <= 6){
                    break;}

                   if(vProduto == 32){
                    printf("produto sem estoque\n");
                    system("pause");
                    break;
                }

                printf("Agora informe a quantidade:\n");
                getchar();
                fscanf(stdin,"%d",&vQuantidade);
                vArmazenaTotaisVendas[0] += fRetornaTotalPadaria(vProduto, vQuantidade);
                vArmazetaTotaisVendaAtual[0] += fRetornaTotalPadaria (vProduto, vQuantidade);
                vArmazetaTotaisVendaAtual[3] += fRetornaTotalPadaria (vProduto, vQuantidade);//armazena aqui para que seja posssível usar na forma de pagamento, mais tarde
                getchar();

            } while(vProduto >6);

            break;
        case 4:/*Seleção de Menu Pagamentos*/
            do
            {
                float vPercDesconto =0;
                fExibeTotalCompraAtual(vArmazetaTotaisVendaAtual);
                fscanf(stdin,"%d",&vFPag);
                getchar();
                if (vFPag==6)
                break;
                printf("Agora o valor que deseja pagar\n");
                fscanf(stdin,"%f",&vValorPagar);
                getchar();
                //so lê o desconto se for maior que 200 e o valor a pagar for maior que o total a receber
                if (vFPag == 1 && vValorPagar >=vArmazetaTotaisVendaAtual[3]&& vArmazetaTotaisVendaAtual[3]>=200)
                {
                    do{
                        printf("Informe o total de desconto que o cliente tem direito ser extorquido nesta mercearia super faturada\n");
                        fscanf(stdin,"%f",&vPercDesconto);
                    }while (vPercDesconto <=10);
                    //descontar o valor pago do vetor
                    //zerar variáveis locais para iniciar nova venda
                    //exibir troco (caso valor pago > que valor a receber)

                } else if (vFPag ==1 && vValorPagar >=vArmazetaTotaisVendaAtual[3]&& vArmazetaTotaisVendaAtual[3]<200)
                {
                   //desconto de 5 ou 10%
                }



            } while (vArmazenaTotaisFPag[0]>0);
            break;
        case 5: /*Seleção de Menu de Abertura de Caixa*/


            break;
        case 6: /*Seleção de Menu de Fechamento de caixa*/
            break;
        default:
            fMenu();
            fscanf(stdin,"%d",&vMenu);
            break;
        }


        fMenu();
        fscanf(stdin,"%d",&vMenu);
    } while (vMenu < 500);

}

/*----------------MENU PRINCIPAL-----------------------------------------------------*/
void fMenu()
{
    system("cls");
    printf("==========================================\n");
    printf("============      BERE'S      ============\n");
    printf("==========================================\n");
    printf("\tEscolha uma das opcoes\n");
    printf("== 1.   MATERIAIS DE LIMPEZA            ==\n");
    printf("== 2.   ALIMENTOS E BEBIDAS             ==\n");
    printf("== 3.   PARARIA                         ==\n");
    printf("== 4.   FECHAR A VENDA                  ==\n");
    printf("==                                      ==\n");
    printf("== 6.   ABERTURA DE CAIXA               ==\n");
    printf("== 7.   FECHAMENTO DE CAIXA             ==\n");
    printf("==                                      ==\n");
    printf("== 0.   ENCERRAR O DEADLOCKS - PDV      ==\n");
    printf("==========================================\n");
    printf("== Deadlocks Solucoes Empresariais      ==\n");
    printf("==========================================\n");
}

/*----------------- MATERIAL DE LIMPEZA----------------------------------------------*/
void fMateriaisLimpeza()
{
    system("cls");
    printf("==========================================\n");
    printf("============ ITENS DE LIMPEZA ============\n");
    printf("==========================================\n");
    printf("== COD     ITEM                VALOR    ==\n");
    printf("== 11      DETERGENTE          R$ 01,99 ==\n");
    printf("== 12      SABAO EM PO (1Kg)   R$ 08,99 ==\n");
    printf("== 13      ESPONJA             R$ 01,50 ==\n");
    printf("== 14      AMACIANTE (1Lt)     R$ 15,00 ==\n");
    printf("== 15      Bucha de pia");
    printf("           (Kit c/3)           R$ 4,99 ==\n");
    printf("== 16      DESINFETANTE (1Lt)  R$ 7,88 ==\n");
    printf("== 17      SABAO EM BARRA (UN) R$ 1,00 ==\n");
    printf("==                                      ==\n");
    printf("==  6   VOLTAR AO MENU PRINCIPAL        ==\n");
    printf("==========================================\n");
    printf("==========================================\n");
    printf("Informe o Produto ou tecle 5 para retornar\n");

}

/*----------------- Alimentos e Bebidas----------------------------------------------*/
void fAlimentoseBebidas()
{
    system("cls");
    printf("==========================================\n");
    printf("============ ITENS DE LIMPEZA ============\n");
    printf("==========================================\n");
    printf("== COD     ITEM                  VALOR  ==\n");
    printf("== 21      CAFE                R$ 19,99 ==\n");
    printf("== 22      LEITE (CX)           R$ 5,90 ==\n");
    printf("== 23      ARROZ (1KG)          R$ 4,50 ==\n");
    printf("== 24      FEIJAO PRETO (1KG)   R$ 8,00 ==\n");
    printf("== 25      ACUCAR (1KG)         R$ 5,00 ==\n");
    printf("== 26      SAL (1KG)            R$ 2,00 ==\n");
    printf("== 27      FARINHA DE TRIGO(1KG)R$ 5,00 ==\n");
    printf("==                                      ==\n");
    printf("==  6   VOLTAR AO MENU PRINCIPAL        ==\n");
    printf("==========================================\n");
    printf("==========================================\n");
    printf("Informe o Produto ou tecle 5 para retornar\n");
}
/*----------------- PADDARIA ----------------------------------------------*/
void fPadaria()
{
    system("cls");
    printf("==========================================\n");
    printf("============ ITENS DE PADARIA ============\n");
    printf("==========================================\n");
    printf("== COD     ITEM                VALOR    ==\n");
    printf("== 31      Pao de Forma        R$ 09,50 ==\n");
    printf("== 32   Pao Interal(S/Estoque) R$ 12,50 ==\n");
    printf("== 33      Pao Frances         R$ 01,50 ==\n");
    printf("== 34      Sonho               R$ 15,00 ==\n");
    printf("== 35      Biscoito(kg)        R$ 12,50 ==\n");
    printf("== 36      Pao doce(Un)        R$ 02,50 ==\n");
    printf("== 37      Salgado(Un)         R$ 17,50 ==\n");
    printf("==                                      ==\n");
    printf("==  6   VOLTAR AO MENU PRINCIPAL        ==\n");
    printf("==========================================\n");
    printf("==========================================\n");
    printf("Informe o Produto ou tecle 6 para retornar\n");

}





/*------------------------------------------MATERIAIS DE LIMPEZA, RETORNO DE CALCULO DE QUANTIDADE x VALOR--------------------------------------------------*/
// O i ANTES DO NOME DAS VARIÁVEIS DE ARGUMENTO É DE "INPUT", ERA PARA SER e, DE "entrada", MAS SÓ PERCEBI TARDE DEMAIS E FIQUEI COM PREGUIÇA DE TROCAR UwU
float fRetornaTotalMatLimpeza(int iProduto, int iQuantidade){
    /*Vetor do "tipo" Produto, iniciado com o código e o preço de cada produto, de cada categoria*/
    Produtos vMateriaisLimpeza[7]= {{11, 1.99}, {12, 08.99},{13, 1.50},{14, 15.00},{15, 4.99},{16, 7.99},{17, 1.00}};
    float vArmazenaTotaisProduto =0;
    for (int i = 0; i < 7; i++)
    {   /*Percorre o vetor com a variável i e checa se o código do produto na posição [valor de i]
          bate com o que o usuário colocou. Se sim, retorna o total comprado, evitando um swit{case()} para cada produto*/
        if (vMateriaisLimpeza[i].codigo == iProduto)
        {
            vArmazenaTotaisProduto = ((float)iQuantidade * vMateriaisLimpeza[i].preco);
        }
    }
    return vArmazenaTotaisProduto;
}

// O i ANTES DO NOME DAS VARIÁVEIS DE ARGUMENTO É DE "INPUT", ERA PARA SER e, DE "entrada", MAS SÓ PERCEBI TARDE DEMAIS E FIQUEI COM PREGUIÇA DE TROCAR UwU
float fRetornaTotalPadaria(int iProduto, int iQuantidade){
    /*Vetor do "tipo" Produto, iniciado com o código e o preço de cada produto, de cada categoria*/
    Produtos vPadaria[7]= {{31, 09.50}, {32, 12.50},{33,01.50},{34,15.00},{35,12.50},{36,02.50},{37,17.50}};
    float vArmazenaTotaisProduto =0;
    for (int i = 0; i < 7; i++)
    {   /*Percorre o vetor com a variável i e checa se o código do produto na posição [valor de i]
          bate com o que o usuário colocou. Se sim, retorna o total comprado, evitando um swit{case()} para cada produto*/
        if (vPadaria[i].codigo == iProduto)
        {
            vArmazenaTotaisProduto = ((float)iQuantidade * vPadaria[i].preco);

            if(vPadaria[i].codigo == 32){

                printf("Voce esta sem estoque sua velha :) /n");

            }
        }
    }
    return vArmazenaTotaisProduto;
}
float fRetornaTotalAlimentos(int iProduto, int iQuantidade){
    /*Vetor do "tipo" Produto, iniciado com o código e o preço de cada produto, de cada categoria*/
    Produtos vAlimentosBebidas[7]= {{21, 19.99},{22, 5.90},{23, 4.50},{24, 8.00},{25, 5.00},{26, 2.00},{27, 5.00}};
    float vArmazenaTotaisProduto =0;
    for (int i=0; i<7; i++)
    {/*Percorre o vetor com a variável i e checa se o código do produto na posição [valor de i]
       bate com o que o usuário colocou. Se sim, retorna o total comprado, evitando um swit{case()} para cada produto*/
        if(vAlimentosBebidas[i].codigo == iProduto)
        {
            vArmazenaTotaisProduto = ((float)iQuantidade * vAlimentosBebidas[i].preco);
        }
    }
    return vArmazenaTotaisProduto;
}



/*----------------- FORMA DE PAGAMENTO-----------------------------------------------*/
float fCalculaDescontoMenor(float iTotalCompra){
    if (iTotalCompra <=50)
    {
        return iTotalCompra * 0.05;
    }
    else if (iTotalCompra >50 && iTotalCompra <200)
    {
        return iTotalCompra *0.10;
    }
    return 0;
}
/* Como a bere agora inventou de querer ser --||PRIME||-- no desconto, alternativa mais fácil é quebrar o desconto em duas partes*/
float fCalculaDescontoMaior (float iTotalCompra, float iPercentDescont){
    return iTotalCompra *(iPercentDescont/100);
}

/*Percorre o vetor que contém o total bruto de cada categoria para retornar o totalizador geral da compra atual*/
float fRetornaTotalBrutoCompra (float iVetorVendaAtual[]){
    float soma =0;
    for (int i = 0; i < 3; i++)
    {
        soma+= iVetorVendaAtual[i];
    }
    return soma;
}

/*Apenas o menu quando a pessoa escolhe pagar*/
void fExibeTotalCompraAtual(float iExibeTotaisCompraAtual[]){
    float somaTotalBruto = fRetornaTotalBrutoCompra(iExibeTotaisCompraAtual);
    printf("Valor Total Itens de Limpeza: %.2f\n", iExibeTotaisCompraAtual[0]);
    printf("Valor Total Padaria: %.2f\n",iExibeTotaisCompraAtual[1]);
    printf("Valor Total em Alimentos e Bebidas: %.2f\n",iExibeTotaisCompraAtual[2]);
    printf("Valor Total compra: %.2f\n",somaTotalBruto);
    if (somaTotalBruto < 200)
    {
        printf("Sua compra de %.2f lhe da direito a um desconto de: %.2f\n",somaTotalBruto,fCalculaDescontoMenor(somaTotalBruto));
    }
    else{//Nota: %% porque % (sozinho) é uma passagem de parâmetro, %% é a impressao do sinal de porcentagem
        printf("Sua compra lhe da direito a um desconto maior que 10%%, que sera escolhido pelo Sra. Berenice!\n");
    }
    printf("Por gentileza, selecione a forma de pagamento\n");
    printf("1 - Para dinheiro;\n");
    printf("2 - Para cartao\n");
    printf("6 - para retornar ao menu principal\n");
}

float fProcessaPagamentoDinheiro (float vValorTotalCompra[],float vValorPagar,  float vDesconto){
    vValorTotalCompra[0] -=(vValorPagar - vDesconto);
    if (vValorTotalCompra <0)
    {
        return 0;
    }
    else{
        return vValorTotalCompra[0];
    }


}
