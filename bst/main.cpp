/**
	@file main.cpp
	
	@brief Test dei metodi fondamentali e d'uso della classe binary_search_tree
*/

// Direttive per il pre-compilatore

#include <iostream> // std::cout, std::endl
#include "bst.h" // binary_search_tree
#include <cassert> // assert
#include <string> // std::string
#include <list> // std::list

/**
	@brief Funtore per il confronto tra interi
	
	Funtore per il confronto tra interi.
*/
struct compare_int {
	bool operator()(int a, int b) const {
		return a < b;
	}
};

/**
	@brief Funtore per l'uguaglianza tra interi
	
	Funtore per l'uguaglianza tra interi.
*/
struct equal_int {
	bool operator()(int a, int b) const {
		return a == b;
	}
};

/**
	@brief Funtore per il confronto tra float
	
	Funtore per il confronto tra float.
*/
struct compare_float {
	bool operator()(float a, float b) const {
		return a < b;
	}
};

/**
	@brief Funtore per l'uguaglianza tra float
	
	Funtore per l'uguaglianza tra float.
*/
struct equal_float {
	bool operator()(float a, float b) const {
		return a == b;
	}
};

/**
	@brief Funtore per il confronto tra booleani
	
	Funtore per il confronto tra booleani.
*/
struct compare_bool {
	bool operator()(bool a, bool b) const {
		return a < b;
	}
};

/**
	@brief Funtore per l'uguaglianza tra booleani
	
	Funtore per l'uguaglianza tra booleani.
*/
struct equal_bool {
	bool operator()(bool a, bool b) const {
		return a == b;
	}
};

/**
	@brief Funtore per il confronto tra stringhe
	
	Funtore per il confronto tra stringhe. La valutazione e' fatta
	sulla lunghezza. Ritorna true se la prima stringa e' piu' corta
	della seconda.
*/
struct compare_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return (a.size() < b.size());
	} 
};

/**
	@brief Funtore per l'uguaglianza tra stringhe
	
	Funtore per l'uguaglianza tra stringhe. La valutazione e' fatta
	sulla lunghezza. Ritorna true se le due stringhe hanno la stessa
	lunghezza.
*/
struct equal_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return (a.size() == b.size());
	} 
};

/**
	@brief Struct complex che implementa un numero complesso
	
	Struct complex che implementa un numero complesso.
*/
struct complex {
	int re; ///< parte reale del numero
	int im; ///< parte immaginaria del numero

	/**
		@brief Costruttore
		
		Costruttore che prende una parte reale e una immaginaria.
	*/
	complex(int real, int imaginary) : re(real), im(imaginary) {} // initialization list
};

/**
	@brief Funtore per il confronto di due numeri complessi
	
	Funtore per il confronto di due numeri complessi.
*/
struct compare_complex {
	bool operator()(const complex &c1, const complex &c2) const {
		if(c1.re != c2.re)
			return (c1.re < c2.re);
		return (c1.im < c2.im);
	} 
};

/**
	@brief Funtore per il confronto di uguaglianza di due numeri complessi
	
	Funtore per il confronto di uguaglianza tra due numeri complessi.
*/
struct equal_complex {
	bool operator()(const complex &c1, const complex &c2) const {
		return (c1.re == c2.re) && (c1.im == c2.im);
	} 
};

/**
	@brief Ridefinizione dell'operatore di stream << per un numero complesso
	
	Necessaria per l'operatore di stream << della classe binary_search_tree.
*/
std::ostream &operator<<(std::ostream &os, const complex &c) {
	std::cout << "(" << c.re << ", " << c.im << ")";
	return os;
}

/**
	@brief Struct employee che implementa un impiegato
	
	Struct employee che implementa un impiegato.
*/
struct employee {
	std::string name; ///< nome dell'impiegato
	std::string surname; ///< cognome dell'impiegato
	unsigned int salary; ///< salario dell'impiegato

	/**
		@brief Costruttore
		
		Costruttore che prende un nome, un cognome e un salario.
	*/
	employee(std::string n, std::string sur, unsigned int sal) :
		name(n), surname(sur), salary(sal) {} // initialization list
};

/**
	@brief Funtore per il confronto di due impiegati.
	
	Funtore per il confronto di due impiegati.
	Il confronto avviene, in ordine, su salario, cognome e nome.
*/
struct compare_employee {
	bool operator()(const employee &e1, const employee &e2) const {
		if(e1.salary != e2.salary)
			return (e1.salary < e2.salary);
		
		if(e1.surname.compare(e2.surname) != 0) {
			if(e1.surname.compare(e2.surname) < 0)
				return true;
			return false;
		}
		
		if(e1.name.compare(e2.name) < 0)
			return true;
		return false;
	} 
};

/**
	@brief Funtore per il confronto di uguaglianza di due impiegati.
	
	Funtore per il confronto di uguaglianza tra due impiegati.
	Il confronto avviene su nome e cognome.
*/
struct equal_employee {
	bool operator()(const employee &e1, const employee &e2) const {
		return (e1.name.compare(e2.name) == 0 && e1.surname.compare(e2.surname) == 0);
	} 
};

/**
	@brief Ridefinizione dell'operatore di stream << per un impiegato
	
	Necessaria per l'operatore di stream << della classe binary_search_tree.
*/
std::ostream &operator<<(std::ostream &os, const employee &e) {
	std::cout << "[" << e.name << " " << e.surname << ": " << e.salary << "]";
	return os;
}

/**
	@brief Definizione di un tipo di dato per alberi di interi
	
	Definizione di un tipo di dato per alberi di interi.
*/
typedef binary_search_tree<int, compare_int, equal_int> bst_int;

/**
	@brief Funtore per il confronto di due alberi di interi.
	
	Funtore per il confronto di due alberi di interi.
	Il confronto avviene nell'ordine degli iteratori.
*/
struct compare_bst_int {
	bool operator()(const bst_int &bst1, const bst_int &bst2) const {
		
		bst_int::const_iterator i1, ie1;
		i1 = bst1.begin();
		ie1 = bst1.end();
		
		bst_int::const_iterator i2, ie2;
		i2 = bst2.begin();
		ie2 = bst2.end();
		
		while(i1 != ie1 && i2 != ie2) {
			if(*i1 != *i2)
				return *i1 < *i2;
			
			++i1;
			++i2;
		}
		
		if(i1 == ie1 && i2 != ie2)
			return true;
		
		return false;
	} 
};

/**
	@brief Funtore per il confronto di uguaglianza di due alberi di interi.
	
	Funtore per il confronto di uguaglianza tra due alberi di interi.
	Il confronto avviene nell'ordine degli iteratori.
*/
struct equal_bst_int {
	bool operator()(const bst_int &bst1, const bst_int &bst2) const {
		
		if(bst1.size() != bst2.size())
			return false;
		
		bst_int::const_iterator i1, ie1;
		i1 = bst1.begin();
		ie1 = bst1.end();
		
		bst_int::const_iterator i2, ie2;
		i2 = bst2.begin();
		ie2 = bst2.end();
		
		while(i1 != ie1 && i2 != ie2) {
			if(*i1 != *i2)
				return false;
			
			++i1;
			++i2;
		}
		
		return true;
	}
};

template <typename T, typename C>
struct less_than {
	
	T value; ///< valore su cui eseguire il confronto
	
	/**
		@brief Costruttore
		
		Costruttore che prende un valore su cui eseguire il confronto.
	*/
	less_than(T v) : value(v) {} // initialization list
	
	bool operator()(const T &other) const {
		C compare;
		return compare(other, value);
	}
};

template <typename T, typename C>
struct greater_or_equal_than {
	
	T value; ///< valore su cui eseguire il confronto
	
	/**
		@brief Costruttore
		
		Costruttore che prende un valore su cui eseguire il confronto.
	*/
	greater_or_equal_than(T v) : value(v) {} // initialization list
	
	bool operator()(const T &other) const {
		C compare;
		return !compare(other, value);
	}
};

template <typename T>
bool even (const T &value) {
	return value % 2 == 0;
}

template <>
bool even (const float &value) {
	return static_cast<int>(value) % 2 == 0;
}

template <>
bool even (const std::string &value) {
	return value.size() % 2 == 0;
}

template <>
bool even (const complex &value) {
	return value.re % 2 == 0;
}

template <>
bool even (const employee &value) {
	return value.salary % 2 == 0;
}

template <>
bool even (const bst_int &value) {
	return *value.begin() % 2 == 0;
}

template <typename T>
bool odd (const T &value) {
	return !even<T>(value);
}

template <typename C, typename E, typename T>
void test_bst(const T *values, unsigned int size) {
	
	typedef binary_search_tree<T, C, E> bst;
	
	std::cout << "******** Test dei metodi fondamentali ********" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Costruttore di default:" << std::endl;
	bst tree;
	std::cout << tree << std::endl;
	unsigned int tree_size = tree.size();
	std::cout << "Numero totale di dati inseriti nell'albero: " << tree_size << std::endl;
	assert(tree_size == 0);
	std::cout << std::endl;
	
	std::cout << "insert (non e' un metodo fondamentale, ma necessario per testarli):" << std::endl;
	std::cout << "Inserimento dei valori: ";
	for(unsigned int i = 0; i < size - 1; ++i) {
		std::cout << values[i];
		tree.insert(values[i]);
		if(i + 1 < size -1)
			std::cout << ", ";
	}
	std::cout << std::endl;
	
	tree_size = tree.size();
	std::cout << "Numero totale di dati inseriti nell'albero: " << tree_size << std::endl;
	assert(tree_size == size - 1);
	std::cout << std::endl;

	std::cout << "Copy Constructor:" << std::endl;
	bst tree2(tree);
	std::cout << tree2 << std::endl;
	assert(tree2.size() == tree_size);
	std::cout << std::endl;

	std::cout << "Operatore di assegnamento (operator=):" << std::endl;
	bst tree3;
	tree3 = tree;
	std::cout << tree3 << std::endl;
	assert(tree3.size() == tree_size);
	
	std::cout << std::endl;
	std::cout << "******** Test dei metodi d'uso dell'interfaccia pubblica ********" << std::endl;
	std::cout << std::endl;
	
	std::cout << "insert:" << std::endl;
	assert(size > 0);
	std::cout << "Inserimento del valore duplicato " << values[0] << ":" << std::endl;
	try {
		tree.insert(values[0]);
	}
	catch(bst_duplicated_value_exception<T> &e) {
		std::cout << e.what() << e.get_duplicated_value() << std::endl;
	}
	std::cout << std::endl;
	
	std::cout << "operator<<:" << std::endl;
	std::cout << "Stampa in riga con operator<<:" << std::endl;
	std::cout << tree << std::endl << std::endl;
	
	std::cout << "const_iterator:" << std::endl;
	std::cout << "Stampa in colonna con iteratori:" << std::endl;
	typename bst::const_iterator i, ie;
	for(i = tree.begin(), ie = tree.end(); i != ie; ++i)
		std::cout << *i << std::endl;
	std::cout << std::endl;
	
	std::cout << "size:" << std::endl;
	tree_size = tree.size();
	std::cout << "Numero totale di dati inseriti nell'albero: " << tree_size << std::endl;
	assert(tree_size == size - 1);
	std::cout << std::endl;
	
	std::cout << "exists:" << std::endl;
	for(unsigned int i = 0; i < size; ++i) {
		bool val_exists = tree.exists(values[i]);
		std::cout << "Il valore " << values[i];
		if(!val_exists)
			std::cout << " non";
		std::cout << " e' presente nell'albero." << std::endl;
		if(i < tree_size)
			assert(val_exists);
		else
			assert(!val_exists);
	}
	std::cout << std::endl;
	
	std::cout << "subtree:" << std::endl;
	for(unsigned int i = 0; i < size; ++i) {
		std::cout << "Subtree con radice " << values[i] << ":" << std::endl;
		try {
			bst sub_tree = tree.subtree(values[i]);
			std::cout << sub_tree << std::endl;
		}
		catch(bst_value_not_found_exception<T> &e) {
				std::cout << e.what() << e.get_not_found_value() << std::endl;
		}
	}
	std::cout << std::endl;
	
	std::cout << "printIF:" << std::endl;
	for(unsigned int i = 0; i < size; ++i) {
		std::cout << "printIF < " << values[i] << ":" << std::endl;		
		printIF(tree, less_than<T, C>(values[i]));
	}
	std::cout << std::endl;
	
	for(unsigned int i = 0; i < size; ++i) {
		std::cout << "printIF >= " << values[i] << ":" << std::endl;		
		printIF(tree, greater_or_equal_than<T, C>(values[i]));
	}
	std::cout << std::endl;
	
	std::cout << "printIF pari:" << std::endl;		
	printIF(tree, even<T>);
	std::cout << std::endl;
	
	std::cout << "printIF dispari:" << std::endl;		
	printIF(tree, odd<T>);
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero costante ********" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Costruttore di default:" << std::endl;
	const bst empty_const_tree;
	std::cout << empty_const_tree << std::endl;
	unsigned int empty_const_tree_size = empty_const_tree.size();
	std::cout << "Numero totale di dati inseriti nell'albero: " << empty_const_tree_size << std::endl;
	assert(empty_const_tree_size == 0);
	std::cout << std::endl;
	
	// insert non e' chiamabile su un albero const
	
	std::cout << "Copy Constructor:" << std::endl;
	const bst const_tree(tree);
	std::cout << const_tree << std::endl;
	assert(const_tree.size() == tree_size);
	std::cout << std::endl;

	// L'operatore di assegnamento (operator=) non e' chiamabile su un albero const
	
	std::cout << "operator<<:" << std::endl;
	std::cout << "Stampa in riga con operator<<:" << std::endl;
	std::cout << const_tree << std::endl << std::endl;
	
	std::cout << "const_iterator:" << std::endl;
	std::cout << "Stampa in colonna con iteratori:" << std::endl;
	for(i = const_tree.begin(), ie = const_tree.end(); i != ie; ++i)
		std::cout << *i << std::endl;
	std::cout << std::endl;
	
	std::cout << "size:" << std::endl;
	unsigned int const_tree_size = const_tree.size();
	std::cout << "Numero totale di dati inseriti nell'albero: " << const_tree_size << std::endl;
	assert(const_tree_size == tree_size);
	std::cout << std::endl;
	
	std::cout << "exists:" << std::endl;
	for(unsigned int i = 0; i < size; ++i) {
		bool val_exists = const_tree.exists(values[i]);
		std::cout << "Il valore " << values[i];
		if(!val_exists)
			std::cout << " non";
		std::cout << " e' presente nell'albero." << std::endl;
		if(i < const_tree_size)
			assert(val_exists);
		else
			assert(!val_exists);
	}
	std::cout << std::endl;
	
	std::cout << "subtree:" << std::endl;
	for(unsigned int i = 0; i < size; ++i) {
		std::cout << "Subtree con radice " << values[i] << ":" << std::endl;
		try {
			bst sub_tree = const_tree.subtree(values[i]);
			std::cout << sub_tree << std::endl;
		}
		catch(bst_value_not_found_exception<T> &e) {
				std::cout << e.what() << e.get_not_found_value() << std::endl;
		}
	}
	std::cout << std::endl;
	
	std::cout << "printIF:" << std::endl;
	for(unsigned int i = 0; i < size; ++i) {
		std::cout << "printIF < " << values[i] << ":" << std::endl;		
		printIF(const_tree, less_than<T, C>(values[i]));
	}
	std::cout << std::endl;
	
	for(unsigned int i = 0; i < size; ++i) {
		std::cout << "printIF >= " << values[i] << ":" << std::endl;		
		printIF(const_tree, greater_or_equal_than<T, C>(values[i]));
	}
	std::cout << std::endl;
	
	std::cout << "printIF pari:" << std::endl;		
	printIF(const_tree, even<T>);
	std::cout << std::endl;
	
	std::cout << "printIF dispari:" << std::endl;		
	printIF(const_tree, odd<T>);
}

void test_bst_int(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di interi ********" << std::endl;
	std::cout << std::endl;
	
	int values[8] = {42, 17, 50, 23, 90, -10, 69, 45};
	
	test_bst<compare_int, equal_int>(values, 8);
}

void test_bst_float(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di float ********" << std::endl;
	std::cout << std::endl;
	
	float values[7] = {42.0f, 17.3f, 50.6f, 23.0f, 90.3f, -10.65f, 69.7f};
	
	test_bst<compare_float, equal_float>(values, 7);
}

void test_bst_bool(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di booleani ********" << std::endl;
	std::cout << std::endl;
	
	bool values[2] = {false, true};
	
	test_bst<compare_bool, equal_bool>(values, 2);
}

void test_bst_string(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di stringhe ********" << std::endl;
	std::cout << std::endl;
	
	std::string values[8] = {"12345", "C++", "narvalo", "ciao", "Programmazione", "il", "Gianluigi", "QWERTY"};
	
	test_bst<compare_string, equal_string>(values, 8);
}

void test_bst_complex(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di numeri complessi ********" << std::endl;
	std::cout << std::endl;
	
	complex c1(2, 3);
	complex c2(2, 4);
	complex c3(5, 7);
	complex c4(-3, 6);
	complex c5(-5, -7);
	complex c6(4, 4);
	complex c7(3, 1);
	complex c8(0, -1);
	complex c9(2, -3);
	complex c10(10, 50);
	
	complex values[10] = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10};
	
	test_bst<compare_complex, equal_complex>(values, 10);
}

void test_bst_employee(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di impiegati ********" << std::endl;
	std::cout << std::endl;
	
	employee e1("Andrea", "Tassi", 300);
	employee e2("a", "b", 200);
	employee e3("a", "f", 401);
	employee e4("b", "b", 200);
	employee e5("Andrea", "Sassi", 300);
	
	employee values[5] = {e1, e2, e3, e4, e5};
	
	test_bst<compare_employee, equal_employee>(values, 5);
}

void test_bst_bst_int(void) {
	
	std::cout << std::endl;
	std::cout << "******** Test su un albero di alberi di interi ********" << std::endl;
	std::cout << std::endl;
	
	bst_int tree1;
	tree1.insert(0);
	tree1.insert(1);
	tree1.insert(-1);
	
	bst_int tree2;
	tree2.insert(0);
	tree2.insert(1);
	tree2.insert(-1);
	tree2.insert(3);
	
	bst_int tree3;
	tree3.insert(1);
	tree3.insert(10);
	tree3.insert(5);
	
	bst_int tree4;
	tree4.insert(1);
	tree4.insert(-2);
	
	bst_int values[4] = {tree1, tree2, tree3, tree4};
	
	test_bst<compare_bst_int, equal_bst_int>(values, 4);
}

void test_continue(void) {
	
	std::cout << std::endl;
	std::cout << "******** Fine test precedente ********" << std::endl;
}

void test(void) {
	
	std::cout << "**************** INIZIO TEST ****************" << std::endl << std::endl;
	
	std::cout << "Premere Invio per avviare il primo test..." << std::endl;
	test_bst_int();
	
	test_continue();
	test_bst_float();
	
	test_continue();
	test_bst_bool();
	
	test_continue();
	test_bst_string();
	
	test_continue();
	test_bst_complex();
	
	test_continue();
	test_bst_employee();
	
	test_continue();
	test_bst_bst_int();
	
	std::cout << std::endl << "**************** FINE TEST ****************" << std::endl;
}

int main() {
	
	test();
	
	return 0;
}

// Fine file main.cpp

