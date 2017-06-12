#include <stdio.h>
#include <stdlib.h>
#include <grafo.h>

int direcionado(TG*g);
void pintarBack(TG * g,TNo* no, int cor, int controle);
int pintar(TG * g);

int main()
{
    TG *g = cria();
    int n,i,tam;
    printf("Insira o tamanho do grafo:\n");
    scanf("%d",&tam);
    for(i=1; i<=tam;i++){
        insere_no(g,i);
    }
    pintar(g);

    while(1){
        printf(" 1 - Iserir aresta \n 2 - Inserir No \n 3 - Imprimir \n 4 - Confereir Caminho \n 0 - Sair\n");
        scanf("%d",&i);
        if(i == 0) break;
        else if(i == 1){
            printf("Inisira o no e o novo vizinho: \n");
            scanf("%d%d", &n, &i);
            insere_aresta(g,n, i);
        }
        else if(i == 2) insere_no(g, ++tam);
        else if(i == 3){
            imprime(g);
            if(direcionado(g)) printf("direcionado");
            else printf("nao direcionado");
            printf("\n%d cores\n",g->cores);

        }
        else if(i == 4){
            printf("Inseira um no de destino e outro de chegada: \n");
            scanf("%d%d", &n, &i);
            TNo * no1 = busca_no(g,n);
            TNo * no2 = busca_no(g, i);
            if(caminho(g, no1, no2)) printf("ha caminho\n");
            else printf("nao ha caminho\n");
        }
        pintar(g);
    }
}

int direcionado(TG*g){ //verifica se eh direcionado (1) ou nao direcionado(0)
    TNo * p = g->prim;

    while(p){
        TViz * v = p->prim_viz;
        while(v){
            TViz * ida = busca_aresta(g,p->id_no,v->id_viz);
            TViz * volta = busca_aresta(g,v->id_viz,p->id_no);
            if(ida == NULL || volta == NULL) return 0;
            v = v->prox_viz;
        }
        p = p->prox_no;
    }
    return 1;
}

int pintar(TG * g){
    descolorir(g);
    TNo * p = g->prim;
    g->cores = 0;
    //pintarBack(g,p,1,p->id_no);
    pinta2(g);
    return g->cores;
}
void descolorir(TG *g){
    TNo * p = g->prim;
    while(p){
        p->cor = 0;
        p = p->prox_no;
    }
}
void pintarBack(TG * g,TNo* no, int cor, int controle){
    if(!g || !no) return;

    if(no->cor != 0 ){
        if(no->prox_no) pintarBack(g,no->prox_no, cor, no->prox_no->id_no);
        return;
    }
    no->cor = cor;

    TViz * v = no->prim_viz;
    while(v){
        TNo * viz = busca_no(g, v->id_viz);
        if(viz->cor == 0)pintarBack(g, viz,cor, controle);
        else no->cor = viz->cor;
        v = v->prox_viz;
    }
    if(cor != no->cor) cor--;
    if(cor>g->cores) g->cores = cor;
    if(controle == no->id_no && no->prox_no) pintarBack(g, no->prox_no, cor+1, no->prox_no->id_no);
    else return;
}

void pinta2(TG *g){
    TNo *no = g->prim;
    int cor=1;
    while(no){
        TNo * no2 = g->prim;
        if(no->cor!=0){
            no = no->prox_no;
            continue;
        }
        no->cor = cor;
        while(no2){
            if(caminho(g,no, no2)){
                no2->cor = no->cor;
            }
            no2 = no2->prox_no;
        }
        cor++;
        no=no->prox_no;
    }
}

int caminho(TG *g, TNo * no1, TNo * no2){
    if (!g || !no1 || !no2) return 0;
    if(no2->id_no == no1->id_no) return 1;
    TViz *v = no1->prim_viz;
    while(v){
        TNo * aux = busca_no(g, v->id_viz);
        if(caminho(g,aux,no2))return 1;
        v = v->prox_viz;
    }
    return 0;
}

