#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
/*
    Para o codigo funcionar corretamente deve existir uma pasta chamada data junto ao executavel
*/
struct Local{
    long int room_id, host_id;
    int reviews, accommodates;
    char room_type[20], coutry[20], city[20], neighborhood[20], property_type[20];
    float overall_satisfaction, bedrooms, price;
};

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
void executa(char nomeA[], int tipoArquivo){
        switch(tipoArquivo){
            case 0:
                strcpy(nomeA, "melhorCaso.txt");
            break;
            case 1:
                strcpy(nomeA, "piorCaso.txt");
            break;
            case 2:
                strcpy(nomeA, "melhorCaso.txt");
            break;
        }
}
void carrega(struct Local l[], int n, char nomeA[]){
    FILE *arquivo= fopen(nomeA, "r");
    char lixo[200];
    if(arquivo){
        fscanf(arquivo,"%200[^\n]\n",lixo);
    	 for(int i=0; i<n;i++){
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
    FILE *arquivo= fopen("data/teste.txt", "w+");
    for(int i=0; i<n;i++){
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
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1-i; j++){
            if(l[j].room_id>l[j+1].room_id){
                swap(j, j+1, l);
            }
        }
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
void menuOrganiza(int op, struct Local l[], int n){
    switch(op){
        case 1:
            bubble(l, n);
        break;
        case 2:
            shell(l,n);
        break;
        case 3:
            InsertionSort(l,n);
        break;
        case 4:
            SelectionSort(l,n);
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}
//salva cada um dos 5 teste em um arquivo especifco
void salva(double memo, double tempo, int teste, int n){
    FILE *arquivo;
    switch(teste){
        case 1:
            arquivo=fopen("data/teste1.txt","a");
            if(!arquivo){
                arquivo=fopen("data/teste1.txt","w");
            }
        break;

        case 2:
            arquivo=fopen("data/teste2.txt","a");
            if(!arquivo){
                arquivo=fopen("data/teste2.txt","w");
            }
        break;

        case 3:
            arquivo=fopen("data/teste3.txt","a");
            if(!arquivo){
                arquivo=fopen("data/teste3.txt","w");
            }
        break;

        case 4:
            arquivo=fopen("data/teste4.txt","a");
            if(!arquivo){
                arquivo=fopen("data/teste4.txt","w");
            }
        break;

        case 5:
            arquivo=fopen("data/teste5.txt","a");
            if(!arquivo){
                arquivo=fopen("data/teste5.txt","w");
            }
        break;

    }

    fprintf(arquivo,"%lf\t", tempo);
    fprintf(arquivo,"%lf\t", memo);
    fprintf(arquivo,"%d\n", n);

    fclose(arquivo);

}
//descobre o maior valor de um vetor e retorna sua posicao; Começa a busca pelo incio do vetor
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
//descobre o menor valor de um vetor e retorna sua posicao; Começa pelo fim do vetor
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

void media(int tamanho){
    double memo[5], time[5], mediaMemo, mediaTemp;
    int n;
    //abre todos os arquivos onde foram salvos os testes e o arquivo onde sera salvo a resposta final
    FILE *arquivo1, *arquivo2, *arquivo3, *arquivo4, *arquivo5, *resposta;
    arquivo1=fopen("data/teste1.txt","r");
    arquivo2=fopen("data/teste2.txt","r");
    arquivo3=fopen("data/teste3.txt","r");
    arquivo4=fopen("data/teste4.txt","r");
    arquivo5=fopen("data/teste5.txt","r");
    resposta=fopen("data/resposta.txt","w");
    for(int i=0; i<tamanho;i++){
        mediaMemo=0.0, mediaTemp=0.0;
        n=0;
        //salva o N em uma variavel e Tempo e memoria em vetores

        //le tempo
        fscanf(arquivo1,"%lf\t",&time[0]);
        fscanf(arquivo2,"%lf\t",&time[1]);
        fscanf(arquivo3,"%lf\t",&time[2]);
        fscanf(arquivo4,"%lf\t",&time[3]);
        fscanf(arquivo5,"%lf\t",&time[4]);
        //le memoria
        fscanf(arquivo1,"%lf\t",&memo[0]);
        fscanf(arquivo2,"%lf\t",&memo[1]);
        fscanf(arquivo3,"%lf\t",&memo[2]);
        fscanf(arquivo4,"%lf\t",&memo[3]);
        fscanf(arquivo5,"%lf\t",&memo[4]);
        //le n
        fscanf(arquivo1,"%d\n",&n);
        fscanf(arquivo2,"%d\n",&n);
        fscanf(arquivo3,"%d\n",&n);
        fscanf(arquivo4,"%d\n",&n);
        fscanf(arquivo5,"%d\n",&n);
        //zera o meior e o menor valores dos vetores de Memoria e Tempo
        memo[maior(memo, 5)]=0.0;
        memo[menor(memo, 5)]=0.0;
        time[maior(time, 5)]=0.0;
        time[menor(time, 5)]=0.0;
        //faz a somatoria do tempo e memoria
        for(int i=0; i<5;i++){
            mediaTemp+=time[i];
            mediaMemo+=memo[i];
        }

        //faz a media dos valores adquiridos
        mediaTemp/=3.0;
        mediaMemo/=3.0;
        //escreve as medias em um arquivo separado
        fprintf(resposta, "%d\t", n);
        fprintf(resposta, "%lf\t", mediaTemp);
        fprintf(resposta, "%lf\n", mediaMemo);

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
    int j, n=10;
    //for(k=0; k<3; k++){
        //for(j=1;j<=5;j++){
            //for(n=2000;n<=128000;n*=2){
                l=aloca(n);
                /*
                clock_t start_time, end_time;
                size_t peakSize;
                start_time = clock();*/

                carrega(l, n, "data/dados_airbnb.txt");
                menuOrganiza(4, l, n);
                escreve(l, n);


                /*
                end_time = clock();
                cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
                memory_used = get_memory_used_MB();
                salva(memory_used,cpu_time_used,j,n);*/
            //}
        //}
    //}
    //media(100);
}
