#include <math.h>
#include <stdio.h>
#include  <stdlib.h>

/*--------------------------------------------Structure de donnees---------------------------------------------------------*/

typedef struct valeur {
    int degree ;
    double scalaire;
}valeur_t;

typedef struct ElementPoly{
    valeur_t *valeur;
    struct ElementPoly *precedent;
    struct ElementPoly *suivant;
}element_t;

typedef struct Polynome{
    int largeur;
    struct ElementPoly *premier;
}polynomme_t;

//-----------------------------------------fonctions---------------------------------------------------------------------------

void get_element(element_t *p){
    printf("donnez le degree :\n");
    scanf("%d",&(p->valeur->degree));
    printf("donnze scalaire :\n ");
    scanf("%lf",&(p->valeur->scalaire));
}

void init_element(element_t *p){
    p->suivant=NULL;
    p->precedent=NULL;
}

void init_polynome(polynomme_t *poly){

    poly->largeur=0;
    poly->premier=NULL;
}

void affichier_polynome(polynomme_t *poly){
    element_t ** conteur= &(poly->premier);
    while ((*conteur) != NULL){
        if((*conteur)->suivant == NULL){
            printf("%lf * x^%d\n",(*conteur)->valeur->scalaire,(*conteur)->valeur->degree);
            break;
        }
        if((*conteur)->suivant->valeur->scalaire <0){
            printf("%lf * x^%d",(*conteur)->valeur->scalaire,(*conteur)->valeur->degree);
            conteur=&((*conteur)->suivant);
        } else{
            printf("%lf * x^%d+",(*conteur)->valeur->scalaire,(*conteur)->valeur->degree);
            conteur=&((*conteur)->suivant);
        }
        }
}

void saisir_element(polynomme_t *poly,element_t *p){
    if(poly->premier == NULL){
        poly->premier=p;
        poly->largeur+=1;
    } else{
        element_t ** conteur= &(poly->premier);
        while ((*conteur) != NULL){
            if((*conteur)->valeur->degree > p->valeur->degree){
                p->suivant=(*conteur);
                if((*conteur)->precedent != NULL){
                    p->precedent =(*conteur)->precedent;
                    ((*conteur)->precedent)->suivant=p;
                } else{
                    poly->premier=p;
                }
                (*conteur)->precedent=p;
                poly->largeur+=1;
                break;
            }
            if ((*conteur)->valeur->degree == p->valeur->degree){
                (*conteur)->valeur->scalaire += p->valeur->scalaire;
                break;
            }
            if ((*conteur)->suivant == NULL){
                p->precedent=(*conteur);
                (*conteur)->suivant =p;
                poly->largeur+=1;
                break;
            }
            conteur=&((*conteur)->suivant);
        }
    }
}

void remplirePolynome(polynomme_t *poly){
    int remplir=1;
    init_polynome(poly);
    printf("remplisage de votre polynome\n");
    do{
        element_t *p=(element_t *) malloc(sizeof(element_t));
        p->valeur=(valeur_t *) malloc(sizeof(valeur_t));
        init_element(p);
        get_element(p);
        saisir_element(poly,p);
        printf("Est que vous voulez ajouter un nouveau element a votre polynome\n1.OUI (cliquez sur 1)\n2. NO (cliquez sur 0)\n");
        scanf("%d",&remplir);

    } while (remplir != 0);
}

int test(element_t *p,element_t *q){
    if ( p != NULL && q != NULL) {
        return 1;
    }
    if (p == NULL && q != NULL){
        return 1;
    }
    if(p != NULL && q == NULL){
        return 1;
    }
    return 0;
}

void sommePolynome (polynomme_t * poly1,polynomme_t *poly2,polynomme_t *somme){
    init_polynome(somme);
    element_t ** conteur1 = &(poly1->premier);
    element_t ** conteur2 = &(poly2->premier);

    while (test((*conteur1),(*conteur2))==1){

        if((*conteur1) == NULL || (*conteur2) == NULL){
            if((*conteur1)==NULL){
                while ((*conteur2) != NULL){
                    element_t *p=(element_t *) malloc(sizeof(element_t));
                    p->valeur = (valeur_t *) malloc(sizeof(valeur_t));
                    init_element(p);
                    p->valeur->degree=(*conteur2)->valeur->degree;
                    p->valeur->scalaire = (*conteur2)->valeur->scalaire;
                    saisir_element(somme,p);
                    conteur2=&((*conteur2)->suivant);
                }
                break;
            }
            if((*conteur2)==NULL){
                while ((*conteur1) != NULL){
                    element_t *p=(element_t *) malloc(sizeof(element_t));
                    p->valeur = (valeur_t *) malloc(sizeof(valeur_t));
                    init_element(p);
                    p->valeur->degree=(*conteur1)->valeur->degree;
                    p->valeur->scalaire = (*conteur1)->valeur->scalaire;
                    saisir_element(somme,p);
                    conteur1=&((*conteur1)->suivant);
                }
                break;
            }
        } else{
            if((*conteur1)->valeur->degree == (*conteur2)->valeur->degree){

                element_t *p= (element_t *) malloc(sizeof(element_t));
                p->valeur=(valeur_t *) malloc(sizeof(valeur_t));
                init_element(p);

                p->valeur->degree = (*conteur1)->valeur->degree;
                p->valeur->scalaire = (*conteur1)->valeur->scalaire + (*conteur2)->valeur->scalaire;


                saisir_element(somme,p);

                conteur2= &((*conteur2)->suivant);
                conteur1= &((*conteur1)->suivant);
            } else {
                if((*conteur1)->valeur->degree > (*conteur2)->valeur->degree){

                    element_t *p= (element_t *) malloc(sizeof(element_t));
                    p->valeur=(valeur_t *) malloc(sizeof(valeur_t));
                    init_element(p);

                    p->valeur->degree = (*conteur2)->valeur->degree;
                    p->valeur->scalaire = (*conteur2)->valeur->scalaire ;

                    saisir_element(somme,p);

                    conteur2= &((*conteur2)->suivant);
                } else{
                    element_t *p= (element_t *) malloc(sizeof(element_t));
                    p->valeur=(valeur_t *) malloc(sizeof(valeur_t));
                    init_element(p);

                    p->valeur->degree = (*conteur1)->valeur->degree;
                    p->valeur->scalaire = (*conteur1)->valeur->scalaire ;

                    saisir_element(somme,p);

                    conteur1= &((*conteur1)->suivant);
                }
            }
        }
    }

}

void ChangementDeSinge(polynomme_t *poly){
    element_t **conteur;
    conteur= &((*poly).premier);
    while ((*conteur) != NULL){
        (*conteur)->valeur->scalaire = -((*conteur)->valeur->scalaire);
        conteur =&((*conteur)->suivant);
    }
}

void soustraction(polynomme_t *poly1 ,polynomme_t *poly2 , polynomme_t *soustractionPoly){
    ChangementDeSinge(poly2);
    sommePolynome(poly1,poly2,soustractionPoly);
    ChangementDeSinge(poly2);
}

void comparision(polynomme_t *poly1,polynomme_t *poly2){
    printf("la comparision de votre deux polynomes est : ");
    if(poly1->largeur != poly2->largeur){
        printf("Ne sont pas egaux\n");
    } else{
        int i=0;
        element_t ** conteur1;
        element_t ** conteur2;
        conteur1= &((*poly1).premier);
        conteur2= &((*poly2).premier);
        while ((*conteur1) != NULL && (*conteur2) != NULL){
            if((*conteur1)->valeur->scalaire != (*conteur2)->valeur->scalaire){
                printf("Ne sont pas egaux\n");
                i=1;
                break;
            }
            conteur1=&((*conteur1)->suivant);
            conteur2=&((*conteur2)->suivant);
        }
        if(i==0){
            printf("Sont egaux\n");
        }
    }
}

void derivee(polynomme_t *poly1,polynomme_t *poly2){
    element_t ** conteur ;
    conteur =&((*poly1).premier);
    init_polynome(poly2);
    while ((*conteur) != NULL){
        if((*conteur)->valeur->degree ==0){
            conteur=&((*conteur)->suivant);
            continue;
        }
        element_t *p=(element_t *) malloc(sizeof(element_t));
        p->valeur = (valeur_t *) malloc(sizeof(valeur_t));
        init_element(p);
        p->valeur->degree=((*conteur)->valeur->degree)-1;
        p->valeur->scalaire = ((*conteur)->valeur->degree)*((*conteur)->valeur->scalaire);
        saisir_element(poly2,p);
        conteur=&((*conteur)->suivant);
    }
}

double valeur(polynomme_t *poly,double x){
    double val=0;
    element_t **conteur;
    conteur = &((*poly).premier);
    while ((*conteur) != NULL){
        val+= ((*conteur)->valeur->scalaire) * pow(x,((*conteur)->valeur->degree));
        conteur=&((*conteur)->suivant);
    }
    return val;
}

void graphe(polynomme_t *poly,double a,double b){
    double pas;
    FILE *f;
    if(b<a){
        double c;
        c=a;
        a=b;
        b=c;
    }
    pas=a;
    f = fopen("graphe.txt","wt");
    while ( pas <= b ){
        fprintf(f,"%lf\t%lf\n",pas, valeur(poly,pas));
        pas+=(b-a)/1000;
    }
    fclose(f);
    system("start gnuplot -persist -e \"plot 'graphe.txt' w l \"");
}

void graphetriple(polynomme_t *poly1,polynomme_t *poly2,polynomme_t *somme,double a,double b){
    sommePolynome(poly1,poly2,somme);
    double pas;
    FILE *f1;
    FILE *f2;
    FILE *f3;

    //remplir file F1
    pas=a;
    f1 = fopen("graphe1.txt","wt");
    while (pas <= b ){
        fprintf(f1,"%lf\t%lf\n",pas, valeur(poly1,pas));
        pas+=(b-a)/1000;
    }
    fclose(f1);

    //remplir F2
    pas=a;
    f2 = fopen("graphe2.txt","wt");
    while (pas <= b  ){
        fprintf(f2,"%lf\t%lf\n",pas, valeur(poly2,pas));
        pas+=(b-a)/1000;
    }
    fclose(f2);

    //remplir F3
    pas=a;
    f3 = fopen("graphe3.txt","wt");
    while (pas <= b ){
        fprintf(f3,"%lf\t%lf\n",pas, valeur(somme,pas));
        pas+=(b-a)/1000;
    }
    fclose(f3);

    //tracer

    system("start gnuplot -persist -e \"plot 'graphe1.txt' with lines title \\\"premier polynome\\\" ,'graphe2.txt' with lines title \\\"deusieme polynome\\\" , 'graphe3.txt' with lines title \\\"somme\\\" \"");

}

void Parite1(void){
    int j=1;
    while(j!=0){
        int i=0;
        printf("-----------------------------Partie 1 de tp de POLYNOME---------------------------------------\nI.Opreration sur un suel polynome\n\n 0.calculer p(x) (cliquez sur 0)\n 1.Remplir un polynome (cliquez sur 1)\n 2.afficher une polynome (cliquez sur 2)\n 3.dervee un polynome (cliquez sur 3)\n 4.changer la singe d'un polynome (cliquez sur 4)\n 5.tracer un polynome  (cliquez sur 5)\n\nII.Operation sur deux polynomes\n\n 6.somme de deux polynomes (cliquez sur 6)\n 7.soustraction de deux polynomes (cliquez sur 7)\n 8.tracer les deux polynomes et leur somme (cliquez sur 8)\n    choisir :\n");
        scanf("%d",&i);

        if(i==0){
            polynomme_t *poly=(polynomme_t *) malloc(sizeof(polynomme_t));
            double x;
            printf("donnez x\n");
            scanf("%lf",&x);
            printf("remplir votre polynome \n");
            remplirePolynome(poly);
            printf("la valeur de x est: %lf", valeur(poly,x));

        }

        if(i==1){
            polynomme_t *poly=(polynomme_t *) malloc(sizeof(polynomme_t));
            remplirePolynome(poly);
            printf("votre polynomes :\t");
            affichier_polynome(poly);
        }
        if(i==2){
            polynomme_t *poly=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir polynome qui vous voulez afficher\n");
            remplirePolynome(poly);
            printf("votre polynomes :\t");
            affichier_polynome(poly);
        }
        if(i==3){
            polynomme_t *poly1=(polynomme_t *) malloc(sizeof(polynomme_t));
            polynomme_t *poly2=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir polynome qui vous voulez afficher\n");
            remplirePolynome(poly1);
            derivee(poly1,poly2);
            printf("polynome direvee est :\t");
            affichier_polynome(poly2);
        }
        if(i==4){
            polynomme_t *poly=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir votre polynome");
            remplirePolynome(poly);
            ChangementDeSinge(poly);
            printf("votre polynome sera : \t");
            affichier_polynome(poly);
        }
        if(i==5){
            polynomme_t *poly=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir votre polynome");
            remplirePolynome(poly);
            double a,b;
            printf("donnez la borne inferieur de votre intervalle \n");
            scanf("%lf",&a);
            printf("donnez la borne superieur de votre intervalle \n");
            scanf("%lf",&b);
            graphe(poly,a,b);

        }
        if(i==6){
            polynomme_t *poly1=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir la 1er polynome");
            remplirePolynome(poly1);
            polynomme_t *poly2=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir la 2eme polynome");
            remplirePolynome(poly2);
            polynomme_t *somme=(polynomme_t *) malloc(sizeof(polynomme_t));
            sommePolynome(poly1,poly2,somme);
            printf("la somme :\t");
            affichier_polynome(somme);
        }
        if(i==7){
            polynomme_t *poly1=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir la 1er polynome");
            remplirePolynome(poly1);
            polynomme_t *poly2=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir la 2eme polynome");
            remplirePolynome(poly2);
            polynomme_t *sous=(polynomme_t *) malloc(sizeof(polynomme_t));
            soustraction(poly1,poly2,sous);
            printf("la somme :\t");
            affichier_polynome(sous);
        }
        if(i==8){
            polynomme_t *poly1=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir la 1er polynome");
            remplirePolynome(poly1);
            polynomme_t *poly2=(polynomme_t *) malloc(sizeof(polynomme_t));
            printf("remplir la 2eme polynome");
            remplirePolynome(poly2);
            polynomme_t *somme=(polynomme_t *) malloc(sizeof(polynomme_t));
            double a,b;
            printf("donnez la borne inferieur de votre intervalle \n");
            scanf("%lf",&a);
            printf("donnez la borne superieur de votre intervalle \n");
            scanf("%lf",&b);
            graphetriple(poly1,poly2,somme,a,b);
        }

        printf("\n\n-----------------------------------------------------------------------\nvous voulez faire une operation?\n1.OUI (cliquez sur 1) \n2.NO et passer a la partie 2  (cliquez sur 0)\n");
        scanf("%d",&j);
    }

}

void Partie2 (void){
    printf("---------------------------------Partie2 de tp POLYNOME---------------------------------------------------\n");

    polynomme_t *poly1 = (polynomme_t *) malloc(sizeof(polynomme_t));
    printf("remplir votre polynome de test \n");
    remplirePolynome(poly1);
    polynomme_t *poly2= (polynomme_t *) malloc(sizeof(polynomme_t));
    derivee(poly1,poly2);
    double r,pas;
    int test=0;      //flag

    printf("donnez la valeur initiale\n");
    scanf("%lf",&r);
    pas=r;
    printf("polynomme :  ");
    affichier_polynome(poly1);
    printf("derivee :  ");
    affichier_polynome(poly2);

    for(int i=0;i<20;i++){
        printf("k = %d\tx%d = %lf\tp(x%d) = %lf\n",i,i,pas,i, valeur(poly1,pas));
        if(valeur(poly1,pas) <0.00001 && valeur(poly1,pas) > -0.00001){
            printf("la racine de votre polynome est : %lf\t (remarque : ce solution est en precision 10^-3)\n",pas);
            test=1;
            break;
        }
        pas=pas-(valeur(poly1,pas)/ valeur(poly2,pas));
    }
    if(test==0){
        printf("20 iteration pas suffisant pour trouver racine ou votre polynome ne s'annule pas\n");
    }
}




int main() {
    Parite1();
    Partie2();
    return 0;
}