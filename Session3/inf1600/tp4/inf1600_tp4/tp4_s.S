#include "tp4.hpp"

//------------------------------------------------------------
.globl _Z13nouveauCercle5Coordjj 		//nouveauCercle
_Z13nouveauCercle5Coordjj:
pushl %ebp
movl %esp, %ebp

pushl $32 					//Espace pour le cercle
call _Znwj 					//call new
pop %edx

pushl 20(%ebp)					//ecraser 32 avec couleur
pushl 16(%ebp)					//rayon
pushl 12(%ebp)					//centre
pushl 8(%ebp)					//centre
pushl %eax					//this

call _ZN6CercleC1E5Coordjj			// constructeur

pop %eax
addl $20, %esp					

leave
ret

//------------------------------------------------------------
.globl	_Z11faireDessinPP5Formej		//faire dessin
_Z11faireDessinPP5Formej:
pushl %ebp
movl %esp, %ebp

//formes = 8, n = 12

//Canevas* c = new Canevas(LARGEUR_CANEVAS, HAUTEUR_CANEVAS,  COULEUR_CANEVAS);
pushl $12 					//Espace pour le canevas
call _Znwj 					//call new
pop %edx

pushl $COULEUR_CANEVAS				//ecraser 12 avec COULEUR_CANEVAS
pushl $HAUTEUR_CANEVAS				//HAUTEUR_CANEVAS
pushl $LARGEUR_CANEVAS				//LARGEUR_CANEVAS
pushl %eax					//this

call _ZN7CanevasC1Ejjj				// constructeur

pop %edx					//this
addl $16, %esp					//depiler

//    for(int i=0; i< n; i++)
//    {
//        c->dessinerForme(formes[i]);
//    }

push $0						//i = 0
debutboucle:

movl -4(%ebp), %ecx 
cmp %ecx, 12(%ebp)
jz finboucle

	//movl %ecx, %eax
	//movl $4, %ecx
	//mul %ecx
	movl 8(%ebp), %eax				//eax <- 4*i
	lea (%eax, %ecx, 4), %eax

	//movl 8(%ebp), %ecx			//formes dans edx
	//movl (%ecx), %ecx			//adresse du tableau formes
	//addl %ecx, %eax				//eax <- adresse de formes[i]

	push %eax				//donner le parametre forme
	push %edx				//donner l'instance apellant "le c"
	call _ZN7Canevas13dessinerFormeEP5Forme	//caller la fonction
	addl $8, %esp				//depiler le parametre et le c


addl $1, -4(%ebp)
jmp debutboucle
finboucle:

//this<-ecrireFrame(c);
pushl (%eax)					//push le parametre
pushl 8(%ebp)					//push this
call	_Z11ecrireFramePK7Canevas		//caller ecrire frame

//this<-delete(c);
//call _ZN5CanevasD1Ev				//appeller le destructeur

addl $12, %esp					//depiler le parametre, le this et i

leave
ret

//------------------------------------------------------------
.globl	_ZN7Canevas13dessinerFormeEP5Forme		//dessiner forme
_ZN7Canevas13dessinerFormeEP5Forme:
pushl %ebp
movl %esp, %ebp

movl 12(%ebp), %eax						//recuperer forme
movl 12(%ebp), %ecx						//garder forme dans ecx
movl (%eax), %eax						//recuperer l'adresse de forme

push 8(%ebp)							//donner le parametre caneva (this)
push %ecx							//donner l'instance apellant la fonction this de forme

call *8(%eax)							//caller la fonction

addl $8, %esp							//depiler le parametre et le this de forme

leave
ret

//------------------------------------------------------------
.globl	_ZN7Canevas13assignerPixelEiij		//assigner pixel
_ZN7Canevas13assignerPixelEiij:
pushl %ebp
movl %esp, %ebp

//x = 12, y = 16, couleur = 20
//_h = 8, _w = 4, _canevas = 0

movl 8(%ebp), %eax					//this

//x >= this->_w 
movl 4(%eax), %ecx					//_w
movl 12(%ebp), %edx					//x
cmp %ecx, %edx						//x-_w
jae fin

//y >= this->_h
movl 8(%eax), %ecx					//_h
movl 16(%ebp), %edx					//y
cmp %ecx, %edx						//y-_h
jae fin

//x < 0 
movl 12(%ebp), %edx					//x
cmp $0, %edx						//x-0
js fin

//y < 0
movl 16(%ebp), %edx					//y
cmp $0, %edx						//y-0
js fin

//this->_canevas[y*this->_w+x] = couleur;
movl 4(%eax), %eax					//w dans eax
mul %edx						//eax <- y*w
addl 12(%ebp), %eax					//eax <- y*w + x
movl $4, %edx
mul %edx						//eax <- (y*w + x)*4

movl 8(%ebp), %ecx
movl (%ecx), %ecx
addl %eax, %ecx

movl 20(%ebp), %edx
movl %edx, (%ecx)				//_canevas[y*this->_w+x] = couleur

fin:

leave
ret

//------------------------------------------------------------
.globl _Z15desallouerFormeP5Forme 		//desallouerForme
_Z15desallouerFormeP5Forme:
pushl %ebp
movl %esp, %ebp

pushl 8(%ebp)					//push forme pour l'appel du destructeur
movl 8(%ebp), %eax				//adresse de forme dans eax
movl (%eax), %eax				//adresse de vtable dans eax
call *4(%eax)					//destructeur
add $4, %esp					//de poper le pointeur

leave
ret
