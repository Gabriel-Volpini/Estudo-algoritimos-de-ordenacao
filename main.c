#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
/*Para o codigo funcionar corretamente deve existir uma pasta chamada data junto ao executavel*/
/*
    dentro da pasta data devem existir 7 pastas com os seguintes nomes:
    bubble
    selection
    insertion
    sell
    merge
    quick
    personalizado
*/
struct Local{
    long int room_id, host_id;
    int reviews, accommodates;
    char room_type[20], coutry[20], city[20], neighborhood[20], property_type[20];
    float overall_satisfaction, bedrooms, price;
};
typedef struct{
    char nome[30];
}String;

double get_memory_used_MB()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}
struct Local* aloca(int n){
    struct Local *l=(struct Local*)malloc(n*sizeof(struct Local));
    return l;
}
void selecionaArquivo(char nomeArquivo[], int k, int w){
    switch(k){
        case 0:
            strcpy(nomeArquivo, "data/dados_airbnb.txt");
        break;
        case 1:
            strcpy(nomeArquivo, "data/organizado.txt");
        break;
        case 2:
            if(w!=4){
                strcpy(nomeArquivo, "data/pior_caso.txt");
            }else{
                strcpy(nomeArquivo, "data/pior_caso_selecet.txt");
            }
        break;
    }
}
void carrega(struct Local l[], int n, char nomeA[]){
    FILE *arquivo= fopen(nomeA, "r");
    char lixo[200];
    int i;
    if(arquivo){
        fscanf(arquivo,"%200[^\n]\n",lixo);
         for(i=0; i<n;i++){
            fscanf(arquivo,"%li\t", &l[i].room_id);
            fscanf(arquivo,"%li\t", &l[i].host_id);
            fscanf(arquivo,"%99[^\t]\t",l[i].room_type);
            fscanf(arquivo,"%99[^\t]\t",l[i].coutry);
            fscanf(arquivo,"%99[^\t]\t",l[i].city);
            fscanf(arquivo,"%99[^\t]\t",l[i].neighborhood);
            fscanf(arquivo,"%d\t",&l[i].reviews);
            fscanf(arquivo,"%f\t", &l[i].overall_satisfaction);
            fscanf(arquivo,"%d\t",&l[i].accommodates);
            fscanf(arquivo,"%f\t",&l[i].bedrooms);
            fscanf(arquivo,"%f\t",&l[i].price);
            fscanf(arquivo,"%99[^\n]\n", l[i].property_type);
        }
    }else{
        printf("ERROR, arquivo nao encontrado\n");
    }
    fclose(arquivo);
}

void escreve(struct Local l[], int n){
    FILE *arquivo= fopen("./data/teste.txt", "w+");
    int i;
    for(i=0; i<n;i++){
        fprintf(arquivo,"%li\t", l[i].room_id);
        fprintf(arquivo,"%li\t", l[i].host_id);
        fprintf(arquivo,"%s\t", l[i].room_type);
        fprintf(arquivo,"%s\t", l[i].coutry);
        fprintf(arquivo,"%s\t", l[i].city);
        fprintf(arquivo,"%s\t", l[i].neighborhood);
        fprintf(arquivo,"%d\t", l[i].reviews);
        fprintf(arquivo,"%.1f\t", l[i].overall_satisfaction);
        fprintf(arquivo,"%d\t", l[i].accommodates);
        fprintf(arquivo,"%.1f\t", l[i].bedrooms);
        fprintf(arquivo,"%.1f\t", l[i].price);
        fprintf(arquivo,"%s\n", l[i].property_type);
    }
    fclose(arquivo);
}
void swap(int p1, int p2, struct Local l[]){
    struct Local aux;
    aux=l[p1];
    l[p1]=l[p2];
    l[p2]=aux;
}
void bubble(struct Local l[], int n){
    int i, j;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-1-i; j++){
            if(l[j].room_id<l[j+1].room_id){
                swap(j, j+1, l);
            }
        }
    }
}
void quick_sort(struct Local *a, int left, int right) {
    int i, j, x;
    struct Local y;
    i = left;
    j = right;
    x = a[(left + right) / 2].room_id;

    while(i <= j) {
        while(a[i].room_id < x && i < right) {
            i++;
        }
        while(a[j].room_id > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}
void merge(struct Local l[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    struct Local *lAux;
    lAux = (struct Local*)malloc(tam * sizeof(struct Local));

    while(com1 <= meio && com2 <= fim){
        if(l[com1].room_id < l[com2].room_id) {
            lAux[comAux] = l[com1];
            com1++;
        } else {
            lAux[comAux] = l[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  /*Caso ainda haja elementos na primeira metade*/
        lAux[comAux] = l[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   /*Caso ainda haja elementos na segunda metade*/
        lAux[comAux] = l[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    /*Move os elementos de volta para o vetor original*/
        l[comAux] = lAux[comAux-comeco];
    }

    free(lAux);
}


void mergeSort(struct Local l[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;
        mergeSort(l, comeco, meio);
        mergeSort(l, meio+1, fim);
        merge(l, comeco, meio, fim);
    }
}
void shell(struct Local l[], int n){
    int i , j;
    struct Local value;

        int gap = 1;
        while(gap < n) {
            gap = 3*gap+1;
        }
        while (gap > 0) {
            for(i = gap; i < n; i++) {
                value = l[i];
                j = i;
                while (j > gap-1 && value.room_id <= l[j - gap].room_id) {
                    l[j] = l [j - gap];
                    j = j - gap;
                }
                l [j] = value;
            }
            gap = gap/3;
        }
}
void InsertionSort(struct Local l[], int n){
    int i, j;
    struct Local temp;
    for (i=1; i<n; i++){
        temp = l[i];
        for (j=i; j>0 && temp.room_id < l[j-1].room_id; j--)
            l[j] = l[j-1];
        l[j] = temp;
    }
}
void SelectionSort(struct Local l[], int n){
    int i, j, min;
    for (i=0; i<n-1; i++){
        for (j=i+1, min = i; j<n; j++)
            if (l[min].room_id > l[j].room_id)
                min = j;
        swap(i, min, l);
    }
}
void SelectionSortDuplo(struct Local l[], int n){
    int i,k, j, min, max;
    for (i=0, k=n-1; i<n-1; i++, k--){
        for (j=i+1, min = i, max=k; j<n-i; j++){
            if (l[min].room_id > l[j].room_id)
                min = j;
            if (l[max].room_id < l[j].room_id)
                max = j;
        }
        swap(i, min, l);
        swap(k, max, l);
    }
}
void menuOrganiza(int op, struct Local l[], int n){
    switch(op){
        case 1:
            bubble(l, n);
        break;

        case 2:
            SelectionSort(l, n);
        break;

        case 3:
            InsertionSort(l,n);
        break;

        case 4:
            shell(l,n);
        break;

        case 5:
            mergeSort(l, 0, n);
        break;

        case 6:
            quick_sort(l,0,n-1);
        break;

        case 7:
            SelectionSortDuplo(l, n);
        break;
    }
}
/*salva cada um dos 5 teste em um arquivo especifco*/
void salva(double memo, double tempo, int teste, int caso, int algoritmo, int n){
    FILE *arquivo;
    char nomeTeste[50];
    switch(algoritmo){
        case 1:
            strcat(nomeTeste, "data/bubble/");
        break;
        case 2:
            strcat(nomeTeste, "data/selection/");
        break;
        case 3:
            strcat(nomeTeste, "data/insertion/");
        break;
        case 4:
            strcat(nomeTeste, "data/shell/");
        break;
        case 5:
            strcat(nomeTeste, "data/merge/");
        break;
        case 6:
            strcat(nomeTeste, "data/quick/");
        break;
        case 7:
            strcat(nomeTeste, "data/personalizado/");
        break;
    }
    switch(caso){
        case 1:
            strcat(nomeTeste, "medio_");
        break;
        case 2:
            strcat(nomeTeste, "melhor_");
        break;
        case 3:
            strcat(nomeTeste, "pior_");
        break;
    }
    switch(teste){
        case 1:
            strcat(nomeTeste, "teste1.txt");
        break;
        case 2:
            strcat(nomeTeste, "teste2.txt");
        break;
        case 3:
            strcat(nomeTeste, "teste3.txt");
        break;
        case 4:
            strcat(nomeTeste, "teste4.txt");
        break;
        case 5:
            strcat(nomeTeste, "teste5.txt");
        break;
    }
    arquivo=fopen(nomeTeste, "a");
    if(!arquivo){
        arquivo=fopen(nomeTeste, "w");
    }
    fprintf(arquivo,"%lf\t", tempo);
    fprintf(arquivo,"%lf\t", memo);
    fprintf(arquivo,"%d\n", n);

    fclose(arquivo);

}
/*descobre o maior valor de um vetor e retorna sua posicao; Começa a busca pelo incio do vetor*/
int maior(double vet[], int n){
    int posiMaior=0, i;
    double maior=vet[0];
    for(i=1;i<n;i++){
        if(maior<vet[i]&&vet[i]!=0.0){
            maior=vet[i];
            posiMaior=i;
        }
    }
    return posiMaior;
}
/*descobre o menor valor de um vetor e retorna sua posicao; Começa pelo fim do vetor*/
int menor(double vet[], int n){
    int posiMenor=n-1,i;
    double menor=vet[n-1];
    for(i=n-2;i>=0;i--){
        if(menor>vet[i]&&vet[i]!=0.0){
            menor=vet[i];
            posiMenor=i;
        }
    }
    return posiMenor;
}
/*
Os dois codigos acima começam em pontos diferentes do vetor
para caso todos os valores sejam iguais nao acabem retornando
a mesma posicao
*/

void media(int tamanho, int op, int algoritmo){
    double memo[5], time[5], mediaMemo, mediaTemp;
    int n, i,j;
    String nomeArquivo[5], respostaArquivo;
    /*abre todos os arquivos onde foram salvos os testes e o arquivo onde sera salvo a resposta final*/
    FILE *arquivo1, *arquivo2, *arquivo3, *arquivo4, *arquivo5, *resposta;
    switch(algoritmo){
        case 1:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/bubble/");
            }
            strcpy(respostaArquivo.nome,"data/bubble/");
        break;
        case 2:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/selection/");
            }
            strcpy(respostaArquivo.nome,"data/selection/");
        break;
        case 3:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/insertion/");
            }
            strcpy(respostaArquivo.nome,"data/insertion/");
        break;
        case 4:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/shell/");
            }
            strcpy(respostaArquivo.nome,"data/shell/");
        break;
        case 5:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/merge/");
            }
            strcpy(respostaArquivo.nome,"data/merge/");
        break;
        case 6:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/quick/");
            }
            strcpy(respostaArquivo.nome,"data/quick/");
        break;
        case 7:
            for(i=0;i<5;i++){
                strcpy(nomeArquivo[i].nome,"data/personalizado/");
            }
            strcpy(respostaArquivo.nome,"data/personalizado/");
        break;
    }

    switch(op){
        case 1:
            for(i=0;i<5;i++){
                strcat(nomeArquivo[i].nome,"medio_teste");
            }
            strcat(respostaArquivo.nome,"medio_teste_");
        break;
        case 2:
            for(i=0;i<5;i++){
                strcat(nomeArquivo[i].nome,"melhor_teste");
            }
            strcat(respostaArquivo.nome,"melhor_teste_");
        break;
        case 3:
            for(i=0;i<5;i++){
                strcat(nomeArquivo[i].nome,"pior_teste");
            }
            strcat(respostaArquivo.nome,"pior_teste_");
        break;
    }
    strcat(nomeArquivo[0].nome,"1.txt");
    strcat(nomeArquivo[1].nome,"2.txt");
    strcat(nomeArquivo[2].nome,"3.txt");
    strcat(nomeArquivo[3].nome,"4.txt");
    strcat(nomeArquivo[4].nome,"5.txt");
    strcat(respostaArquivo.nome,"R.txt");

    arquivo1=fopen(nomeArquivo[0].nome,"r");
    arquivo2=fopen(nomeArquivo[1].nome,"r");
    arquivo3=fopen(nomeArquivo[2].nome,"r");
    arquivo4=fopen(nomeArquivo[3].nome,"r");
    arquivo5=fopen(nomeArquivo[4].nome,"r");
    resposta=fopen(respostaArquivo.nome,"w");

    for(i=0; i<tamanho;i++){
        mediaMemo=0.0, mediaTemp=0.0;
        n=0;
        /*salva o N em uma variavel e Tempo e memoria em vetores*/

        /*le tempo*/
        fscanf(arquivo1,"%lf\t",&time[0]);
        fscanf(arquivo2,"%lf\t",&time[1]);
        fscanf(arquivo3,"%lf\t",&time[2]);
        fscanf(arquivo4,"%lf\t",&time[3]);
        fscanf(arquivo5,"%lf\t",&time[4]);
        /*le memoria*/
        fscanf(arquivo1,"%lf\t",&memo[0]);
        fscanf(arquivo2,"%lf\t",&memo[1]);
        fscanf(arquivo3,"%lf\t",&memo[2]);
        fscanf(arquivo4,"%lf\t",&memo[3]);
        fscanf(arquivo5,"%lf\t",&memo[4]);
        /*le n*/
        fscanf(arquivo1,"%d\n",&n);
        fscanf(arquivo2,"%d\n",&n);
        fscanf(arquivo3,"%d\n",&n);
        fscanf(arquivo4,"%d\n",&n);
        fscanf(arquivo5,"%d\n",&n);
        /*zera o meior e o menor valores dos vetores de Memoria e Tempo*/
        memo[maior(memo, 5)]=0.0;
        memo[menor(memo, 5)]=0.0;
        time[maior(time, 5)]=0.0;
        time[menor(time, 5)]=0.0;
        /*faz a somatoria do tempo e memoria*/
        for(j=0; j<5;j++){
            mediaTemp+=time[j];
            mediaMemo+=memo[j];
        }

        /*faz a media dos valores adquiridos*/
        mediaTemp/=3.0;
        mediaMemo/=3.0;
        /*escreve as medias em um arquivo separado*/
        fprintf(resposta, "%lf\t", mediaTemp);
        fprintf(resposta, "%lf\t", mediaMemo);
        fprintf(resposta, "%d\n", n);

    }

    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivo3);
    fclose(arquivo4);
    fclose(arquivo5);
    fclose(resposta);
}


int main(int argc, char *argv[]){
    struct Local *l;
    int j, n, k;
    char nomeArquivo[30];
    //w=1;2<=7
    for(int w=7;w<=7;w++){
        for(k=1; k<=3; k++){
            selecionaArquivo(nomeArquivo, k, w);
            for(j=1;j<=5;j++){
                for(n=2000;n<=128000;n*=2){

                    l=aloca(n);
	                clock_t start_time, end_time;
				    double cpu_time_used, memory_used;
				    size_t peakSize;

                    start_time = clock();
                    carrega(l, n, nomeArquivo);
                    menuOrganiza(w, l, n);

                    end_time = clock();
                    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
                    memory_used = get_memory_used_MB();

                    free(l);
                    salva(memory_used,cpu_time_used, j, k, w, n);
                }
            }
            media(7, k, w);
        }
    }
}
