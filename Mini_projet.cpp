//VANG Amanda p2104130//
#include<Grapic.h>
#include <iostream>

using namespace grapic;
using namespace std;

const int DIMW = 800;
const int MAX_C = 50;
const int CASE = 16;
const int AFF = 750; //coord y pour position les nb espèces

/*********************************************************************************************************************/

struct jeu_vie
{
    int posx, posy;
    int duree_vie;
    int alive;
};

struct population
{
    jeu_vie grille[MAX_C][MAX_C];
    int journee;
    int lap; //1
    int ren; //2
    int cha; //3
    int pol; //4
    int totale;
};

/*********************************************************************************************************************/

void init_grille(population &pp)
{
    int i,j;

    for (i=0; i<=CASE+2; i++)
    {
        for (j=0; j<=CASE+2; j++)
        {
            pp.grille[i][j].alive = 0;
        }
    }
}

void init_pop(population &pp) //choisit aleatoirement le nb initial des lapins et des renards
{
    int i,j;
    int x, y;

    int lap = pp.lap = irand(15,20);
    int ren = pp.ren = irand(7,9);
    pp.journee = 0;
    pp.totale = 0;
    pp.cha = 0;
    pp.pol = 0;
    pp.totale = lap + ren;
    cout<<pp.lap<<"lap ren"<<pp.ren<<endl;

}
void init_pos(population &pp) //initialise la position des lapins et renards
{
    int i,j;
    int x,y;

    for (i=0; i<pp.lap; i++)
    {
        x = rand()%CASE+1;
        y = rand()%CASE+1;
        pp.grille[x][y].posx = x;
        pp.grille[x][y].posy = y;
        pp.grille[x][y].alive = 1;
    }

    for (i=0; i<pp.ren; i++)
    {
        do{
            x = rand()%CASE+1;
            y = rand()%CASE+1;
        }while(pp.grille[x][y].alive != 0);
        pp.grille[x][y].posx = x;
        pp.grille[x][y].posy = y;
        pp.grille[x][y].alive = 2;
    }
}

/*********************************************************************************************************************/


void ajoute(population &pp) //ajoute un chasseur et un policier selon la journee
{
    int x, y;
    population pp_prec;
    pp_prec = pp;
    int verif = pp.journee%7;

    if((verif == 0))
    {
        do{

            x = rand()%CASE+1;
            y = rand()%CASE+1;
        }while(pp_prec.grille[x][y].alive != 0);
        pp.grille[x][y].alive = 3;

        pp.cha ++;
    }

    if((pp_prec.cha < pp.cha)&&(pp.pol < 6))
    {
        do{
            x = rand()%CASE+1;
            y = rand()%CASE+1;
        }while(pp_prec.grille[x][y].alive != 0);
        pp.grille[x][y].alive = 4;

        pp.pol ++;
    }


}

void ajoute_animal(population &pp) //ajoute une espece lorque celle-ci s'est eteinte
{
    int i;
    int x,y;

    if(pp.lap<=1)
    {
        pp.lap = 3;

        for(i=0; i<pp.lap; i++)
        {
            do{
                x = rand()%CASE+1;
                y = rand()%CASE+1;
            }while(pp.grille[x][y].alive != 0);
            pp.grille[x][y].posx = x;
            pp.grille[x][y].posy = y;
            pp.grille[x][y].alive = 1;
        }
    }

    if(pp.ren<=1)
    {
        pp.ren = 3;

        for(i=0; i<pp.ren; i++)
        {
            do{
                x = rand()%CASE+1;
                y = rand()%CASE+1;
            }while(pp.grille[x][y].alive != 0);
            pp.grille[x][y].posx = x;
            pp.grille[x][y].posy = y;
            pp.grille[x][y].alive = 2;
        }
    }
}

void nb_voisin(population pp, int i, int j, int &lap, int &ren, int &cha, int &pol)
{
    int x, y;
    lap = 0;
    ren = 0;
    cha = 0;
    pol = 0;

    for (x=(i-1);x<=(i+1);x++)
    {
        for (y=(j-1);y<=(j+1);y++)
        {
            if(pp.grille[x][y].alive == 1)
                lap++;

            if(pp.grille[x][y].alive == 2)
                ren++;

            if(pp.grille[x][y].alive == 3)
                cha++;

            if(pp.grille[x][y].alive == 4)
                pol++;
        }
    }
}

void naissance(population &pp, int posx, int posy, int aliv)
{
    pp.grille[posx][posy].alive = aliv;
    pp.grille[posx][posy].duree_vie = 0;
    pp.grille[posx][posy].posx = posx;
    pp.grille[posx][posy].posy = posy;
}

void mort(population &pp, int posx, int posy, int aliv)
{
    pp.grille[posx][posy].alive = aliv;
}

void part(population &pp) //depart des policiers lorsqu'il n'y a plus de chasseurs
{
    int i, j;

    if(pp.cha == 0)
    {
        for(i=0; i<CASE+1; i++)
        {
            for(j=0; j<CASE+1; j++)
            {
                if(pp.grille[i][j].alive == 4)
                    mort(pp, i, j, 0);
            }
        }
        pp.pol = 0;
    }
}

/*********************************************************************************************************************/

void etat_suivant_dep(population &pp) //deplacement aleatoire
{
    int indx, indy;
    int i, j;
    int x, y;
    int nbv;
    int aliv;

    population pp_prec;

    for(i=0; i<CASE+1; i++)
    {
        for(j=0; j<CASE+1; j++)
        {
            if(pp.grille[i][j].alive != 0)
            {
                pp_prec = pp;

                indx = 0 ; indy = 0;
                indx=i; indy=j;
                x = rand()%3-1;     //permet de choisir une nouvelle position
                y = rand()%3-1;
                indx += x; indy += y;

                if ((pp.grille[indx][indy].alive == 0) && (indx>0) && (indx<CASE+1) && (indy>0) && (indy<CASE+1))
                {
                    pp.grille[indx][indy].alive = pp_prec.grille[i][j].alive;
                    pp.grille[i][j].alive = 0;
                }
            }
        }
    }
}

void etat_suivant(population &pp)  //evolution du systeme
{
    int k, l;
    int x, y;
    int i, j;
    int lap, ren, cha, pol;
    lap = 0; ren = 0; cha = 0; pol = 0;
    int chass = 0;
    int lapi = 0;
    int rena = 0;
    int indk = 0, indl = 0;
    int indi, indj;
    i = indi, j = indj;

    population pp_prec;

    ajoute(pp);
    ajoute_animal(pp);

    for(i=1; i<CASE+1; i++)
    {
        for(j=0; j<CASE+1; j++)
        {
            pp_prec = pp ;

            //provoque des naissances
            if (pp_prec.grille[i][j].alive == 0) //naissance
            {
                nb_voisin(pp_prec, i, j, lap, ren, cha, pol);
                if((lap == 3)&&(ren == 0))
                {
                    naissance(pp, i, j , 1);
                    pp.lap ++;
                }

                if(ren == 3)
                {
                    naissance(pp, i, j , 2);
                    pp.ren ++;
                }
            }

            if (pp_prec.grille[i][j].alive == 1)    //update lapin
            {
                nb_voisin(pp_prec, i, j, lap, ren, cha, pol); //renard mange le lapin

                if(lap>4)
                {
                    mort(pp, i, j, 0);
                    pp.lap --;
                }


                if((ren>0) || (cha>0))
                {
                    mort(pp, i ,j , 0);
                    pp.lap --;
                }
            }

            if (pp_prec.grille[i][j].alive == 2)    //update renard
            {

                if(lap>4)
                {
                    mort(pp, i, j, 0);
                    pp.lap --;
                }

                for(x=i-2; x<=i+2; x++)             //le chasseur provoque une mort de 2 blocs grace à un "fusil"
                {
                    for(y=j-2; y<=j+2; y++)
                    {
                        if(pp_prec.grille[x][y].alive == 3)
                        {
                            chass ++;
                        }
                    }
                }

                if(chass>0)
                {
                    mort(pp, i, j, 0);
                    pp.ren --;
                }
            }

            if (pp_prec.grille[i][j].alive == 3)    //update chasseur
            {
                nb_voisin(pp_prec ,i ,j , lap, ren, cha, pol);

                if(pol==1)
                {
                    mort(pp, i, j, 0);
                    pp.cha --;
                }
            }
        }
    }
    part(pp);
}

/*********************************************************************************************************************/

void affiche_nb(population &pp)
{
    fontSize(25);
    color(0,0,0);
    print(30,AFF,"journee:");
    print(120,AFF,pp.journee);
    print(170,AFF,"lapins:");
    print(250,AFF,pp.lap);
    print(300,AFF,"renards:");
    print(400,AFF,pp.ren);
    print(450,AFF,"chasseurs:");
    print(580,AFF,pp.cha);
    print(630,AFF,"policier:");
    print(720,AFF,pp.pol);

    fontSize(15);
    print(420, 30, "appuyez 'fleche haut' pour suivre l'evolution");
    print(420, 15, "appuyez 'fleche gauche' pour passer 5 etapes");
}

void drawgrille()
{
    color(0,150,0);
    grid(0,0,DIMW-1,DIMW-1,CASE,CASE);
}

void draw(population pp)
{
    int i, j;
    int nb_alive;
    int dim = DIMW/CASE;

    for (i=1; i<CASE+1; i++)
    {
        for(j=1; j<CASE+1; j++)
        {
            nb_alive = pp.grille[i][j].alive;
            switch(nb_alive)
            {
                case 1 :{
                    color(200,200,200);             //gris
                    rectangleFill(i*dim-dim, j*dim-dim, i*dim + (dim*2), j*dim + (dim*2));
                }break;

                case 2 :{
                    color(230,127,0);               //orange
                    rectangleFill(i*dim-dim, j*dim-dim, i*dim + (dim*2), j*dim + (dim*2));
                }break;

                case 3 :{
                    color(0,0,0);                   //noir
                    rectangleFill(i*dim-dim, j*dim-dim, i*dim + (dim*2), j*dim + (dim*2));
                }break;

                case 4 :{
                    color(0,0,255);                 //rectangle bleu gauche et rect rouge droite
                    rectangleFill(i*dim-dim, j*dim-dim, i*dim-dim + (dim/2), j*dim + (dim*2));
                    color(255,0,0);
                    rectangleFill(i*dim-dim + (dim/2), j*dim-dim, i*dim + (dim*2), j*dim + (dim*2));
                }break;

                default :{
                        color(0,220,0);             //vert
                        rectangleFill(i*dim-dim, j*dim-dim, i*dim + (dim*2), j*dim + (dim*2));
                }break;
            }
        }
    }
}

/*********************************************************************************************************************/

void compte_grille(population pp)
{
    int i,j;
    int lap, ren, cha, pol;

    cout<<"compte_grille"<<endl;

    for (j=CASE+1; j>=0; j--)
    {
        for (i=0; i<CASE+2; i++)
        {
            cout<<pp.grille[i][j].alive<<" ";
        }
        cout<<endl;
    }

    cout<<"nb_voisin |lap ren|"<<endl;
    for (j=CASE+1; j>=0; j--)
    {
        for(i=0; i<CASE+2; i++)
        {
            nb_voisin(pp, i, j, lap, ren, cha, pol);
            cout<<lap<<" "<<ren;
        }
        cout<<endl;
    }
}

/*********************************************************************************************************************/

int main(int , char**)
{
    int i, j, nb, ind;
    Menu m;
    bool stop = false;
    bool fin = false;
	winInit("Mini_projet",DIMW,DIMW);
	backgroundColor(255,255,255);

	menu_add(m, "RUN");
	menu_add(m, "INITIALISATION");

	population pp;
	init_grille(pp);
	init_pop(pp);
	init_pos(pp);
	compte_grille(pp);

	while(!stop)
    {
        winClear();

        if(isKeyPressed(SDLK_UP))
        {
            etat_suivant(pp);
            etat_suivant_dep(pp);

            pp.journee ++;

            delay(100);
            compte_grille(pp);
        }

        if(isKeyPressed(SDLK_LEFT))
        {
            for(int k=0; k<5; k++)
            {
                winClear();

                etat_suivant(pp);
                etat_suivant_dep(pp);
                pp.journee ++;

                draw(pp);
                drawgrille();
                affiche_nb(pp);
                delay(200);
                compte_grille(pp);

                winDisplay();
            }
        }

        draw(pp);
        drawgrille();
        color(255,0,0);

        affiche_nb(pp);

        menu_draw(m, 20, 20, 130, 80);
        if (menu_select(m)!=0)
        {
            switch(menu_select(m))
            {
                case 0 : {

                }; break;

                case 1 :{
                    init_grille(pp);
                    init_pop(pp);
                    init_pos(pp);       //init

                default: ; break;
                }
            }
            menu_setSelect(m,0);
        }

        stop = winDisplay();
    }
	winQuit();
	return 0;
}
