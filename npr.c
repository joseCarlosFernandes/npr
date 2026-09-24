#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct pilha{
    char itens;
    struct pilha *next;
    struct pilha *back;
}pilha;

struct pilha *topo = NULL;
struct pilha *corrente = NULL;


void empilha(char c){
    if(topo == NULL){ //primeiro item da pilha
	    corrente = (pilha*)malloc(sizeof(pilha));
        corrente->next = NULL;
        corrente->back = NULL;
        corrente->itens = c;
        topo = corrente;
    }else{
	    corrente = (pilha*)malloc(sizeof(pilha));
        corrente->back = topo; //coloca na frente do topo (aponta as costas dele pro antigo topo)
        topo->next = corrente; //aponta a frente do antigo topo pro item que esta sendo inserido
        corrente->next = NULL; //aponta a frente do item pra ninguém
        corrente->itens = c;   //define o iten dentro do nó como o valor passado por toNPR()
        topo = corrente;       //desloca o ponteiro do topo p/ o item que acabou de ser inserido
    }
}

char desempilha(){
        if(topo == NULL){
    	    return '\0';
        }else{
    
            if(topo->back == NULL){   //caso seja o ultimo item da pilha, não tem ninguém nas costas
                char c = topo->itens; //recupera o valor que esta no nó
                free(topo);           //limpa o ponteiro
                topo = NULL;         
                return c;             //retorna o valor q ocupava o topo para ser inserido na variável npr[]
            }else{
                corrente = topo;      
            	char c = corrente->itens; //recupera o valor que ocupa o topo
                topo = corrente->back;    //topo vira o valor q antes antecedia o topo
            	
            	if(topo != NULL){      //se topo não for NULL (não existir) aponta a frente dele para nada (pois ele é o topo)
            	   topo->next = NULL;
            	}
            	free(corrente);        //limpa o endereço do antigo topo
                return c;              //retorna o valor que ocupava o antigo topo para ser inserido em npr[]
                }
            }
}

char olhaTopo(){
    if (topo == NULL){ //se não existir topo (pilha vazia)
        return '\0';
    }
    return topo->itens;//retorna o valor que ocupa atualmente o topo
}

int precedencia(char op){ //retorna a precedencia do operador
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2; 
    return 0;
}

void toNPR(char *infixo, char *npr){
    char c;
    int i = 0, j = 0;
    
    while((c = infixo[i]) != '\0'){
        if(isalnum(c)){ //verifica se é operando (letra/numero)
            npr[j++] = c;
        }
        else if(c == '('){ //verifica se é ( ou seja, começo da expressão
            empilha(c);
        }
        else if(c == ')'){ //verifica se é ) ou seja, final da expressão
            while(olhaTopo() != '('){
                npr[j++] = desempilha();
            }
            desempilha(); //remove o ( da pilha que fica sobrando
            
        }else{ //se não for os anteriores é operador
            while(topo != NULL && olhaTopo() != '(' && precedencia(olhaTopo()) >= precedencia(c)){
                npr[j++] = desempilha();               //se o operador que estiver no topo da pilha tiver um retorno maior que o dentro de c (caracter do momento da iteração)
                                                       //ele será adicionado a expressão npr
            }                                          //caso ele seja menor, ele sera adicionado depois que o operador contido em c, pois assim respeitamos as regras matemáticas de prioridade das operações, onde * e / devem ser executados antes de + e -
            empilha(c);
        }
        i++;
    }
    
    while(topo != NULL){
        npr[j++] = desempilha();
    }
    
    npr[j] = '\0';
}


int main()
{
    char infixo[100];
    char npr[100];
    
    printf("Digite em formato infixo: \n");
    scanf("%s", infixo);
    
    toNPR(infixo, npr);
    
    printf("NPR: %s \n", npr);
    
    return 0;
}
