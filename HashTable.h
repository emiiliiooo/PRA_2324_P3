#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../Pract1/PRA_2324_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	
	int h(std::string key){
		int suma = 0;
        	for(int i = 0 ; i < key.length() ; i++){
			char c = key.at(i);
			int s = int(c);	
			suma += s;
		}

		int clave = suma % max;

		return clave;	// Devuelve la posición en la tabla
	}


    public:
	HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n = 0;
		max = size;
	}

	~HashTable(){
		for(int i=0 ; i<max ; i++){
			table[i].~ListLinked();		// Borra la lista en cada posición
		}
		delete[] table;				// Borra el espacio de la tabla
	}

	int capacity(){
		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
		out<< "==============" << endl;

		for(int i=0 ; i<th.max ; i++){
			out << endl << "== Cubeta " << i << " ==" << endl;
			out << endl << th.table[i] << endl;
		}
		
		out << "==============" << endl << endl;

		return out;	
	}

	V operator[](std::string key){
		int pos = h(key);

		if(pos < 0 || pos >= max){
			throw std::runtime_error("Posición fuera de la tabla");
		}

		V valor = search(key);

		return valor;
	}
        

	// Métodos clase Dict<V>
	
	virtual void insert(std::string key, V value){
		int pos = h(key);
		int poslista = table[pos].search(key);
		std::cout << poslista;
		if(poslista != -1){ 		// Si se encuentra
			string mensaje = "Key ' " + key + " ' already exists!";
			throw std::runtime_error(mensaje);
		}

		else{
			TableEntry<V> newEntry(key, value);   // ???????
			table[pos].prepend(newEntry);
			n++;
		}
	}

	virtual V search(std::string key){
		int pos = h(key);
                int poslista = table[pos].search(key);

		if(poslista == -1){             // Si no se encuentra
                        string mensaje = "Key ' " + key + " ' not found!";
                        throw std::runtime_error(mensaje);
                }

		else{
			std::cout << poslista;
			return table[pos].get(poslista).value;
		}
	}

	virtual V remove(std::string key){
		int pos = h(key);
                int poslista = table[pos].search(key);

                if(poslista == -1){             // Si no se encuentra
                        string mensaje = "Key ' " + key + " ' not found!";
                        throw std::runtime_error(mensaje);
                }

		else{
			n--;
			return table[pos].remove(poslista).value;
		}
	}

	virtual int entries(){
		int ent = 0;

		for( int i=0 ; i<capacity() ; i++){
			ent += table[i].size();
		}

		return ent;
	}

};

#endif
