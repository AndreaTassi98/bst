/**
	@file bst.h 
	
	@brief Dichiarazione e definizione della classe binary_search_tree
*/

// Guardie del file header

#ifndef BST_H
#define BST_H

// Direttive per il pre-compilatore

#include <ostream> // std::ostream
#include <iterator> // std::forward_iterator_tag
#include <cstddef> // std::ptrdiff_t
#include "bstexceptions.h" // bst_duplicated_value_exception, bst_value_not_found_exception

/**
	@brief ALbero binario di ricerca
	
	Classe che implementa un albero binario di ricerca di dati generici T.
	L’albero è formato da un insieme di elementi T contenuti in nodi connessi
	in una struttura gerarchica padre-figlio e non permette l'inserimento
	di dati duplicati.
	E' possibile per l'utente scegliere la strategia usata per confrontare
	due dati T: l'ordinamento nell'albero e' effettuato utilizzando
	un funtore di comparazione C.
	Di default, il funtore usa l'ordinamento naturale dei dati, indotto dagli
	operatori di confronto standard. 
	
	@param T tipo dei dati
	@param O funtore di confronto di ordinamento (<) di due dati
	@param E funtore di confronto di uguaglianza (==) di due dati
*/
template <typename T, typename O, typename E>
class binary_search_tree {
	
	/**
		@brief Nodo dell'albero
		
		Struttura di supporto interna che implementa un nodo dell'albero.
	*/
	struct node {
		T value; ///< dato inserito nell'albero
		node *left; ///< puntatore al nodo figlio sinistro nell'albero
		node *right; ///< puntatore al nodo figlio destro nell'albero
		node *parent; ///< puntatore al nodo padre nell'albero
		
		/**
			@brief Costruttore di default
			
			Costruttore di default per istanziare un nodo vuoto.
			E' l'unico costruttore che puo' essere utilizzato per istanziare
			un eventuale array di nodi.
		*/
		node() : left(nullptr), right(nullptr), parent(nullptr) {} // initialization list
		
		/**
			@brief Costruttore secondario
			
			Costruttore secondario che permette di istanziare un nodo,
			inizializzandolo con il suo valore.
			
			@param v valore del dato
		*/
		node(const T &v) :
			value(v), left(nullptr), right(nullptr), parent(nullptr) {} // initialization list
		
		/**
			@brief Costruttore secondario
			
			Costruttore secondario che permette di istanziare un nodo,
			inizializzandolo con il suo valore e con i puntatori
			ai suoi nodi figli sinistro, destro e al suo nodo padre.
			
			@param v valore del dato
			@param l puntatore al nodo figlio sinistro
			@param r puntatore al nodo figlio destro
			@param p puntatore al nodo padre
		*/
		node(const T &v, node *l, node *r, node *p) :
			value(v), left(l), right(r), parent(p) {} // initialization list

		// Gli altri metodi fondamentali coincidono con quelli di default
		
		/**
			@brief Distruttore
			
			Distruttore. Rimuove la memoria allocata da un nodo.
		*/
		~node() {
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}		
	}; // struct node
	
	node *_root; ///< puntatore alla radice dell'albero
	
	typedef unsigned int size_type; ///< tipo per identificare il numero di dati inseriti nell'albero
	size_type _size; ///< numero totale di dati inseriti nell'albero
	
	O _order; ///< oggetto funtore per il confronto di ordinamento (<) di due dati
	E _equals; ///< oggetto funtore per il confronto di uguaglianza (==) di due dati
	
	/**
		@brief Inserimento degli elementi di un albero in quello corrente
		
		Inserisce ricorsivamente gli elementi di un albero in quello corrente,
		secondo l'ordinamento definito dal funtore di confronto
		di ordinamento (<) _order, di tipo O.
		Gli elementi dell'albero da inserire sono identificati dal puntatore
		alla radice dell'albero di cui fanno parte.

		@pre Nessuno dei valori da inserire dev'essere gia' presente
			 all'interno dell'albero
		
		@param root puntatore al nodo radice dell'albero che contiene
			   gli elementi da inserire in quello corrente

		@throw bst_duplicated_value_exception se uno dei valori da inserire
			   e' gia' presente all'interno dell'albero corrente
		@throw eccezione di allocazione di memoria
	*/
	void insert_tree(const node *root) {	
		if(root != nullptr) {
			insert(root->value);
			insert_tree(root->left);
			insert_tree(root->right);
		}
	}
	
	/**
		@brief Eliminazione dell'intero contenuto dell'albero
		
		Funzione privata che elimina tutti i nodi dell'albero.
	*/
	void clear() {
		clear_tree(_root);
	}
	
	/**
		@brief Eliminazione ricorsiva di un albero
		
		Funzione privata helper per l'eliminazione dei nodi di un albero,
		tramite l'eliminazione ricorsiva dei suoi sottoalberi.
		Elimina un albero data la sua radice.

		@param root puntatore al nodo radice dell'albero da eliminare
	*/
	void clear_tree(node *root) {
		if(root != nullptr) {
			clear_tree(root->left);
			clear_tree(root->right);
			delete root;
			root = nullptr;	
			_size--;
		}
	}
	
	/**
		@brief Nodo con un certo valore
		
		Funzione privata helper che cerca se esiste nell'albero un nodo
		con un certo valore cercato e, in caso affermativo,
		ritorna un puntatore al nodo stesso.
		L'uguaglianza e' definita dal funtore di confronto di uguaglianza (==)
		_equals, di tipo E.

		@param value valore del nodo da cercare

		@return puntatore al nodo che ha il valore cercato,
				nullptr se non esiste nessun nodo che ha il valore cercato
	*/
	node *search(const T &value) const {
		node *current = _root;
		
		while(current != nullptr && !_equals(current->value, value))
			if(_order(value, current->value))
				current = current->left;
			else
				current = current->right;
		
		return current;
	}

public:
	
	// Metodi fondamentali
	
	/**
		@brief Costruttore di default (METODO FONDAMENTALE)
		
		Costruttore di default per istanziare un albero vuoto.
		E' l'unico costruttore che puo' essere utilizzato per istanziare
		un eventuale array di alberi.
	*/
	binary_search_tree() : _root(nullptr), _size(0) {} // initialization list

	/**
		@brief Costruttore di copia/Copy Constructor (METODO FONDAMENTALE)
		
		Costruttore di copia/Copy Constructor.
		Permette di istanziare un albero con i valori presi da un altro albero.

		@param other albero da copiare per creare quello corrente
		
		@throw eccezione di allocazione di memoria
	*/
	binary_search_tree(const binary_search_tree &other) : _root(nullptr), _size(0) { // initialization list
		try {
			insert_tree(other._root);
		}
		catch(...) {
			clear();
			throw;
		}
	}

	/**
		@brief Operatore di assegnamento (METODO FONDAMENTALE)
		
		Operatore di assegnamento. Permette la copia tra alberi.
		
		@param other albero come sorgente da copiare (operando di destra)
		
		@return reference a this

		@throw eccezione di allocazione di memoria
	*/
	binary_search_tree &operator=(const binary_search_tree &other) {
		
		// Per evitare l'auto-assegnamento (this = this)
		if(this != &other) {
			binary_search_tree tmp(other);
			std::swap(_root,tmp._root);
			std::swap(_size,tmp._size);
		}
		return *this;
	}

	/**
		@brief Distruttore (METODO FONDAMENTALE)
		
		Distruttore. Rimuove la memoria allocata da un albero.
	*/
	~binary_search_tree() {
		clear();
	}
	
	// Fine metodi fondamentali
	
	// Ulteriori metodi pubblici

	/**
		@brief Inserimento di un elemento nell'albero
		
		Inserisce un elemento nell'albero, secondo l'ordinamento definito
		dal funtore di confronto di ordinamento (<) _order, di tipo O.

		@pre Il valore da inserire non dev'essere gia' presente
			 all'interno dell'albero
		
		@param value valore dell'elemento da inserire

		@throw bst_duplicated_value_exception se il valore da inserire
			   e' gia' presente all'interno dell'albero
		@throw eccezione di allocazione di memoria
	*/
	void insert(const T &value) {	
		node *current = _root;
		node *previous = nullptr;
		
		while(current != nullptr) {
			previous = current;
			if(_equals(value, current->value))
				throw bst_duplicated_value_exception<T>("Valore duplicato: ", value);
			if(_order(value, current->value))			
				current = current->left;
			else
				current = current->right;
		}
		
		node *tmp = new node(value);
		
		tmp->parent = previous;
		
		if(previous == nullptr)
			_root = tmp;
		else
			if(_order(value, previous->value))
				previous->left = tmp;
			else
				previous->right = tmp;
		
		_size++;
	}
	
	/**
		@brief Numero totale di dati inseriti nell'albero
		
		Ritorna il numero totale di dati inseriti nell'albero

		@return numero totale di dati inseriti nell'albero
	*/
	size_type size() const {
		return _size;
	}

	/**
		@brief Controllo di esistenza di un elemento nell'albero
		
		Controlla se esiste un elemento di tipo T nell'albero.
		L'uguaglianza e' definita dal funtore di confronto di uguaglianza (==)
		_equals, di tipo E.

		@param value valore da cercare

		@return true se esiste l'elemento, false altrimenti
	*/
	bool exists(const T &value) const {
		return search(value) != nullptr;
	}
	
	/**
		@brief Sottoalbero
		
		Metodo che, passato un dato d dello stesso tipo T dei dati contenuti
		nell'albero, ritorna un nuovo albero, che corrisponde al sottoalbero
		avente come radice il nodo con il valore d.
		
		@pre Il valore d dev'essere presente all'interno dell'albero
		
		@param d valore del nodo radice del sottoalbero
		
		@return sottoalbero avente come radice il nodo con il valore d
		
		@throw bst_value_not_found_exception se il valore d non e' presente
			   all'interno dell'albero
		@throw eccezione di allocazione di memoria
	*/
	binary_search_tree subtree(const T &d) const {
		binary_search_tree sub_bst;
		
		node *sub_root = search(d);
		if(sub_root == nullptr)
			throw bst_value_not_found_exception<T>("Valore non trovato: ", d);
		
		try {
			sub_bst.insert_tree(sub_root);
		}
		catch(...) {
			sub_bst.clear();
			throw;
		}
		
		return sub_bst;
	}

	/**
		@brief Iteratore costante di tipo forward dell'albero
		
		Iteratore a sola lettura (costante) di tipo forward
		per accedere ai dati presenti nell'albero.
		Iteratore da usarsi su oggetti const (non modifica i dati puntati).
	*/
	class const_iterator {
		const node *_n; ///< puntatore a un nodo dell'albero

	public:
		typedef std::forward_iterator_tag iterator_category; ///< categoria dell'iteratore: forward
		typedef T                         value_type; ///< tipo dei dati puntati: T
		typedef ptrdiff_t                 difference_type; ///< tipo della differenza tra iteratori: ptrdiff_t
		typedef const T*                  pointer; ///< tipo di puntatore (costante) ai dati: const T*
		typedef const T&                  reference; ///< tipo di riferimento (costante) dei dati: const T&
		
		/**
			@brief Costruttore di default
			
			Costruttore di default per istanziare un iteratore costante
			che punta a nullptr.
		*/
		const_iterator() : _n(nullptr) { // initialization list
		}
		
		/**
			@brief Costruttore di copia/Copy Constructor
			
			Costruttore di copia/Copy Constructor per l'iteratore costante.
			Permette di istanziare un iteratore costante
			con i valori presi da un altro iteratore costante.
			
			@param other iteratore costante da copiare per creare quello corrente
		*/
		const_iterator(const const_iterator &other) : _n(other._n) {} // initialization list

		/**
			@brief Operatore di assegnamento
			
			Operatore di assegnamento per l'iteratore costante.
			Permette la copia tra iteratori costanti.
			
			@param other iteratore costante come sorgente da copiare
				   (operando di destra)
			
			@return reference a this
		*/
		const_iterator &operator=(const const_iterator &other) {
			_n = other._n;
			return *this;
		}

		/**
			@brief Distruttore
			
			Distruttore per l'iteratore costante.
			Rimuove la memoria allocata da un iteratore costante.
		*/
		~const_iterator() {}

		/**
			@brief Operatore di dereferenziamento
			
			Operatore di dereferenziamento per l'accesso in lettura dei dati.
			
			@return dato riferito dall'iteratore costante
		*/
		reference operator*() const {
			return _n->value;
		}

		/**
			@brief Operatore di accesso ai dati
			
			Operatore di accesso in lettura ai dati.
			
			@return puntatore al dato riferito dall'iteratore
		*/
		pointer operator->() const {
			return &(_n->value);
		}
		
		/**
			@brief Operatore di iterazione pre-incremento
			
			Operatore di iterazione pre-incremento per l'iteratore costante.
			
			@return reference all'iteratore incrementato
		*/
		const_iterator &operator++() {
			// ha figli
			if(_n->left != nullptr) // ha un figlio sinistro
				_n = _n->left;
			else // non ha un figlio sinistro
				if(_n->right != nullptr) // ha un figlio destro
					_n = _n->right;
				else { // non ha un figlio destro
					// non ha figli
					while(_n->parent != nullptr) // ha un padre
						if(_n == _n->parent->left) { // e' figlio sinistro
							_n = _n->parent;
							if(_n->right != nullptr) { // ha un figlio destro
								_n = _n->right;
								return *this;
							}
						}
						else // è figlio destro
							_n = _n->parent;
					
					// se si esce dal corpo del ciclo while,
					// l'iteratore ora punta alla radice e ha visitato tutti i nodi
					
					_n = nullptr;
				}
			
			// se non si entra nel corpo dell'else,
			// l'iteratore ora punta a un figlio sinistro o destro da visitare
			
			return *this;
		}
		
		/**
			@brief Operatore di iterazione post-incremento
			
			Operatore di iterazione post-incremento per l'iteratore costante.
			
			@param int parametro fittizio per distinguere l'operatore
				   di post-incremento da quello di pre-incremento
			
			@return copia dell'iteratore prima di essere incrementato
		*/
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++this;
			return tmp;
		}

		/**
			@brief Operatore di uguaglianza
			
			Operatore di uguaglianza per l'iteratore costante.
			
			@param other iteratore da confrontare con this
			
			@return true se gli iteratori this e other puntano allo stesso nodo,
					false altrimenti
		*/
		bool operator==(const const_iterator &other) const {
			return (_n == other._n);
		}
		
		/**
			@brief Operatore di diversità
			
			Operatore di diversità per l'iteratore costante.
			
			@param other iteratore da confrontare con this
			
			@return true se gli iteratori this e other puntano a nodi diversi,
					false altrimenti
		*/
		bool operator!=(const const_iterator &other) const {
			return (_n != other._n);
		}

	private:
		
		// Dati membro

		// La classe container (binary_search_tree) dev'essere dichiarata friend
		// dell'iteratore per concederle l'accesso al costruttore privato
		// di inizializzazione nei metodi begin ed end.
		friend class binary_search_tree; 

		/**
			@brief Costruttore privato
			
			Costruttore privato di inizializzazione utilizzato
			dalla classe container (binary_search_tree) nei metodi begin ed end.
			
			@param n puntatore a un nodo dell'albero
		*/
		const_iterator(const node *n) : _n(n) {} // initialization list
		
	}; // class const_iterator
	
	// Funzioni membro per l'utilizzo degli iteratori
	// da parte della classe container (binary_search_tree)
	
	/**
		@brief Iteratore che punta all'inizio dell'albero
		
		Funzione membro che ritorna un iteratore
		che punta all'inizio dell'albero (alla sua radice).
	
		@return iteratore che punta all'inizio dell'albero
	*/
	const_iterator begin() const {
		return const_iterator(_root);
	}
	
	/**
		@brief Iteratore che punta alla fine dell'albero
		
		Funzione membro che ritorna un iteratore
		che punta alla fine dell'albero.
	
		@return iteratore che punta alla fine dell'albero
	*/
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	
	// Fine funzioni membro per l'utilizzo degli iteratori
	
	// Fine ulteriori metodi pubblici

}; // class binary_search_tree

/**
	@brief Ridefinizione operatore di stream <<
	
	Ridefinizione dell'operatore di stream << per la stampa del contenuto
	dell'albero.

	@param os oggetto stream di output
	@param tree albero da stampare

	@return reference allo stream di output
*/
template <typename T, typename O, typename E>
std::ostream &operator<<(std::ostream &os, const binary_search_tree<T, O, E> &tree) {
	
	/* La keyword typename e' necessaria per specificare che const_iterator
	   non e' un dato membro della classe template binary_search_tree,
	   bensì un tipo (in questo caso, classe) definito al suo interno.
	*/
	typename binary_search_tree<T, O, E>::const_iterator i, ie;
	
	os << "[";
	for(i = tree.begin(), ie = tree.end(); i != ie; ++i) {
		os << *i;
		typename binary_search_tree<T, O, E>::const_iterator i_tmp = i;
		if(++i_tmp != ie)
			os << ", ";
	}
	os << "]";
	
	return os;
}

/**
	@brief Stampa dei valori che soddisfano un predicato
	
	Funzione globale che, dato un albero binario di tipo generico T
	e un predicato P, stampa a schermo tutti i valori contenuti
	nell'albero che soddisfano il predicato.
	
	@param tree albero di tipo T in cui cercare i valori da stampare a schermo
	@param predicate il predicato che i valori dell'albero devono soddisfare
		   per essere stampati a schermo
*/
template <typename T, typename O, typename E, typename P>
void printIF(const binary_search_tree<T, O, E> &tree, P predicate) {
	
	/* La keyword typename e' necessaria per specificare che const_iterator
	   non e' un dato membro della classe template binary_search_tree,
	   bensì un tipo (in questo caso, classe) definito al suo interno.
	*/
	typename binary_search_tree<T, O, E>::const_iterator i, ie;

	for(i = tree.begin(), ie = tree.end(); i != ie; ++i)
		if(predicate(*i))
			std::cout << *i << " ";
	
	std::cout << std::endl;
}

#endif

// Fine guardie del file header

// Fine file header bst.h

