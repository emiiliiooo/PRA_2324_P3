#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
	BSNode<T> *root;

	BSNode<T>* search(BSNode<T>* n, T e) const{
		if(n == nullptr){
			throw std::runtime_error("Element not found!");
		}

		else if(n->elem < e){
			return search(n->right, e);
		}
		
		else if(n->elem > e){
			return search(n->left, e);
 		}
		
		else
			return n;
	}



	BSNode<T>* insert(BSNode<T>* n, T e){
		if(n == nullptr){
                        n = new BSNode(e);
                }

		else if(n->elem == e){
			throw std::runtime_error("Duplicated element!");
		}

                else if(n->elem < e){
                      	n->right = insert(n->right, e);
                }

                else if(n->elem > e){
                        n->left = insert(n->left, e);
                }
        	
		return n;
        }



	void print_inorder(std::ostream &out, BSNode<T>* n) const{
		if(n->left != nullptr){
			print_inorder(out, n->left);
		}

		out << n->elem << " ";

		if(n->right != nullptr){
			print_inorder(out, n->right);
		}
	}


	BSNode<T>* remove(BSNode<T>* n, T e){
		if(n == nullptr){
			throw std::runtime_error("Element not found!");
		}

		else if(n->elem < e){
			n->right = remove(n->right, e);
		}
		else if(n->elem > e){
			n->left = remove(n->left, e);
		}

		else{
			if(n->left != nullptr && n->right != nullptr){
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			}
			
			else{
				if(n->left != nullptr)
					n = n->left;

				else
					n = n->right;
			}
		}
	
		return n;
	}	


	T max(BSNode<T>* n) const{
		if(n == nullptr){
			throw std::runtime_error("");
		}

		else if(n->right != nullptr){
			return max(n->right);
		}

		else{
			return n->elem;
		}
	}



	BSNode<T>* remove_max(BSNode<T>* n){
		if(n->right == nullptr){
			return n->left;
		}

		else{
			n->right = remove_max(n->right);
			return n;
		}
	}

	
	void delete_cascade(BSNode<T>* n){
		if(n == nullptr){	// ???????????
			return;
		}

		delete_cascade(n->left);
		delete_cascade(n->right);
		delete n;
	}

    public:
	BSTree(){
		nelem = 0;
		root = nullptr;
	}

	int size() const{
		return nelem;
	}


	// BUSQUEDA DE ELEMENTOS

	T search(T e) const{   // Actua com función lanzadera de la función "search recursiva".
			       // En esta función se llama a la función recuersiva.
		
		BSNode<T>* aux = search(root, e);    
// La función search (recuersiva) devuelve el nodo donde esta el elemnto "e"
		
		return aux->elem; 	// Devuelve el elemento del nodo.
	}


	T operator[](T e) const{
		return search(e);
	}


	// INSERCIÓN DE ELEMENTOS
	
	void insert(T e){
		root = insert(root, e);
		nelem ++;
	}
		

	// RECORRIDO E IMPRESIÓN DEL ÁRBOL
	
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		if (bst.root != nullptr){
			bst.print_inorder(out, bst.root);
		}

		return out;
	}


	// ELIMINACIÓN DE ELEMENTOS
	
	void remove(T e){
		remove(root, e);
		nelem --;
	}
	

	// DESTRUCCIÓN
	
	~BSTree(){
		delete_cascade(root);
	}

};

#endif
