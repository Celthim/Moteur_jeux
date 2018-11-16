#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "quadtree.h"

using namespace std;

QuadTree::QuadTree(){

}

void QuadTree::init(VertexData* vertices, int sizex, int sizey){

    cout << sizex << "|" << sizey << endl;
    cout << " | (" << vertices[0].position.x() <<"," << vertices[0].position.y() << ")" << endl;
    cout << " | (" << vertices[sizex-1].position.x() <<"," << vertices[sizex-1].position.y() << ")" << endl;
    cout << " | (" << vertices[sizex*(sizey-1)].position.x() <<"," << vertices[sizex*(sizey-1)].position.y() << ")" << endl;
    cout << " | (" << vertices[sizex*sizey-1].position.x() <<"," << vertices[sizex*sizey-1].position.y() << ")" << endl;
    this->value[0] = vertices[0];
    this->value[1] = vertices[sizex-1];
    this->value[2] = vertices[sizex*(sizey-1)];
    this->value[3] = vertices[sizex*sizey-1];

    if(sizex <=2 || sizey <=2){
        this->f1 = NULL;
        this->f2 = NULL;
        this->f3 = NULL;
        this->f4 = NULL;
    }
    else{

        int i1 = 0;
        int i2 = 0;
        int i3 = 0;
        int i4 = 0;

        int sizex1;
        int sizex2;
        int sizex3;
        int sizex4;

        int sizey1;
        int sizey2;
        int sizey3;
        int sizey4;

        int xcoupe = ceil(((float)sizex)/2);
        int ycoupe = ceil(((float)sizey)/2);

        //size x impair
        if(((float)sizex)/2!=sizex/2){
            sizex1 = xcoupe;
            sizex2 = xcoupe;
            sizex3 = xcoupe;
            sizex4 = xcoupe;
        }
        //size x pair
        else{
            sizex1 = xcoupe+1;
            sizex2 = xcoupe;
            sizex3 = xcoupe+1;
            sizex4 = xcoupe;
        }

        if(((float)sizey)/2!=sizey/2){
            sizey1 = ycoupe;
            sizey2 = ycoupe;
            sizey3 = ycoupe;
            sizey4 = ycoupe;
        }
        else{
            sizey1 = ycoupe+1;
            sizey2 = ycoupe+1;
            sizey3 = ycoupe;
            sizey4 = ycoupe;
        }

        VertexData* vertices1 = (VertexData*)malloc(sizex1*sizey1*sizeof (VertexData));
        VertexData* vertices2 = (VertexData*)malloc(sizex2*sizey2*sizeof (VertexData));
        VertexData* vertices3 = (VertexData*)malloc(sizex3*sizey3*sizeof (VertexData));
        VertexData* vertices4 = (VertexData*)malloc(sizex4*sizey4*sizeof (VertexData));

        for(int index = 0;index<sizex*sizey;index++){
            int i = index%sizex;
            int j = index/sizex;
            if(i<=sizex/2){
                if(j<=sizey/2){
                    vertices1[i1]=vertices[index];
                    i1++;

                }
                if(j>=sizey/2){
                    vertices2[i2]=vertices[index];
                    i2++;

                }
            }
            if(i>=sizex/2){
                if(j<=sizey/2){
                    vertices3[i3]=vertices[index];
                    i3++;

                }
                if(j>=sizey/2){
                    vertices4[i4]=vertices[index];
                    i4++;

                }
            }
        }
        cout << " | " << i1 << "=" << sizex1 << "*" << sizey1 << endl;
        cout << " | " << i2 << "=" << sizex2 << "*" << sizey2<< endl;
        cout << " | " << i3 << "=" << sizex3 << "*" << sizey3<< endl;
        cout << " | " << i4 << "=" << sizex4 << "*" << sizey4<< endl;
        this->f1 = compute(vertices1,sizex1,sizey1);
        this->f2 = compute(vertices2,sizex2,sizey2);
        this->f3 = compute(vertices3,sizex3,sizey3);
        this->f4 = compute(vertices4,sizex4,sizey4);
    }
}



QuadTree* QuadTree::compute(VertexData* vertices, int sizex, int sizey){
    QuadTree* quadfather = new QuadTree();

    cout << sizex << "|" << sizey << endl;
    cout << " | (" << vertices[0].position.x() <<"," << vertices[0].position.y() << ")" << endl;
    cout << " | (" << vertices[sizex-1].position.x() <<"," << vertices[sizex-1].position.y() << ")" << endl;
    cout << " | (" << vertices[sizex*(sizey-1)].position.x() <<"," << vertices[sizex*(sizey-1)].position.y() << ")" << endl;
    cout << " | (" << vertices[sizex*sizey-1].position.x() <<"," << vertices[sizex*sizey-1].position.y() << ")" << endl;
    quadfather->value[0] = vertices[0];
    quadfather->value[1] = vertices[sizex-1];
    quadfather->value[2] = vertices[sizex*(sizey-1)];
    quadfather->value[3] = vertices[sizex*sizey-1];

    if(sizex <=2 || sizey <=2){
        quadfather->f1 = NULL;
        quadfather->f2 = NULL;
        quadfather->f3 = NULL;
        quadfather->f4 = NULL;
    }
    else{

        int i1 = 0;
        int i2 = 0;
        int i3 = 0;
        int i4 = 0;

        int sizex1;
        int sizex2;
        int sizex3;
        int sizex4;

        int sizey1;
        int sizey2;
        int sizey3;
        int sizey4;

        int xcoupe = ceil(((float)sizex)/2);
        int ycoupe = ceil(((float)sizey)/2);

        //size x impair
        if(((float)sizex)/2!=sizex/2){
            sizex1 = xcoupe;
            sizex2 = xcoupe;
            sizex3 = xcoupe;
            sizex4 = xcoupe;
        }
        //sizex pair
        else{
            sizex1 = xcoupe+1;
            sizex2 = xcoupe;
            sizex3 = xcoupe+1;
            sizex4 = xcoupe;
        }

        if(((float)sizey)/2!=sizey/2){
            sizey1 = ycoupe;
            sizey2 = ycoupe;
            sizey3 = ycoupe;
            sizey4 = ycoupe;
        }
        else{
            sizey1 = ycoupe+1;
            sizey2 = ycoupe+1;
            sizey3 = ycoupe;
            sizey4 = ycoupe;
        }

        VertexData* vertices1 = (VertexData*)malloc(sizex1*sizey1*sizeof (VertexData));
        VertexData* vertices2 = (VertexData*)malloc(sizex2*sizey2*sizeof (VertexData));
        VertexData* vertices3 = (VertexData*)malloc(sizex3*sizey3*sizeof (VertexData));
        VertexData* vertices4 = (VertexData*)malloc(sizex4*sizey4*sizeof (VertexData));

        for(int index = 0;index<sizex*sizey;index++){
            int i = index%sizex;
            int j = index/sizex;
            if(i<=sizex/2){
                if(j<=sizey/2){
                    vertices1[i1]=vertices[index];
                    i1++;

                }
                if(j>=sizey/2){
                    vertices2[i2]=vertices[index];
                    i2++;

                }
            }
            if(i>=sizex/2){
                if(j<=sizey/2){
                    vertices3[i3]=vertices[index];
                    i3++;

                }
                if(j>=sizey/2){
                    vertices4[i4]=vertices[index];
                    i4++;

                }
            }
        }
        quadfather->f1 = compute(vertices1,sizex1,sizey1);
        quadfather->f2 = compute(vertices2,sizex2,sizey2);
        quadfather->f3 = compute(vertices3,sizex3,sizey3);
        quadfather->f4 = compute(vertices4,sizex4,sizey4);
        free(vertices);
    }
    return quadfather;
}


