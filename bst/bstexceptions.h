/**
	@file bstexceptions.h
	
	@brief Dichiarazione e definizione delle classi di eccezioni custom
	relative ad un bst
*/

// Guardie del file header

#ifndef BSTEXCEPTIONS_H
#define BSTEXCEPTIONS_H

// Direttive per il pre-compilatore

#include <string> // std::string

/**
	@brief Eccezione di valore duplicato nell'albero
	
	Classe eccezione custom.
	Viene lanciata quando si prova ad inserire un valore duplicato
	all'interno di un albero.
	
	@param T tipo dei dati dell'albero
*/
template <typename T>
class bst_duplicated_value_exception {
	
	std::string message; ///< messaggio di errore
	
	T _duplicated_value; ///< valore duplicato nell'albero

public:
	
	/**
		@brief Costruttore
		
		Costruttore che prende un messaggio d'errore e il valore duplicato.
	*/
	bst_duplicated_value_exception(const std::string &message, T duplicated_value) :
		message(message), _duplicated_value(duplicated_value) {} // initialization list
	
	/**
		@brief Messaggio di errore
		
		Ritorna il messaggio di errore.
		
		@return messaggio di errore
	*/
	std::string what(void) const {
		return message;
	}
	
	/**
		@brief Valore duplicato
		
		Ritorna il valore duplicato.
		
		@return valore duplicato
	*/
	T get_duplicated_value(void) const {
		return _duplicated_value;
	}
};


/**
	@brief Eccezione di valore non presente nell'albero
	
	Classe eccezione custom.
	Viene lanciata quando si prova ad eseguire un'operazione
	un valore non presente nell'albero.
	
	@param T tipo dei dati dell'albero
*/
template <typename T>
class bst_value_not_found_exception {
	
	std::string message; ///< messaggio di errore
	
	T _not_found_value; ///< valore non presente nell'albero
	
public:
	
	/**
		@brief Costruttore
		
		Costruttore che prende un messaggio d'errore e il valore non presente.
	*/
	bst_value_not_found_exception(const std::string &message, T not_found_value) :
		message(message), _not_found_value(not_found_value) {} // initialization list
	
	/**
		@brief Messaggio di errore
		
		Ritorna il messaggio di errore.
		
		@return messaggio di errore
	*/
	std::string what(void) const {
		return message;
	}

	/**
		@brief Valore non presente
		
		Ritorna il valore non presente
		
		@return valore non presente
	*/
	T get_not_found_value(void) const {
		return _not_found_value;
	}
};

#endif

// Fine guardie del file header

// Fine file header bstexceptions.h

