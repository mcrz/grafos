#include <stdio.h>
#include <stdlib.h>
#include <grafo.h>

int direcionado(TG*g);
void pintarBack(TG * g,TNo* no, int cor, int controle);
int pintar(TG * g);

int main()
{
    TG *g = cria();
    int n,i;
    scanf("%d",&n);
    for(i=1; i<=n;i++){
        insere_no(g,i);
    }
    insere_aresta(g,1,2);
    insere_aresta(g,2,1);
    insere_aresta(g,1,3);
    insere_aresta(g,3,1);
    insere_aresta(g,4,8);
    insere_aresta(g,8,4);
    insere_aresta(g,7,6);
    insere_aresta(g,6,7);
    pintar(g);

    imprime(g);

    int dir = direcionado(g);
    if(dir) printf("direcionado");
    else printf("nao direcionado");

    printf("\n%d cores",g->cores);
}

int direcionado(TG*g){
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
    TNo * p = g->prim;
    pintarBack(g,p,1,p->id_no);
    return g->cores;
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
        v = v->prox_viz;
    }
    if(cor>g->cores) g->cores = cor;
    if(controle == no->id_no && no->prox_no) pintarBack(g, no->prox_no, cor+1, no->prox_no->id_no);
    else return;
}

