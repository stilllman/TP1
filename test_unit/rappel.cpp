
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

// ----
// Rappel C++
// ----

// ----
// Définition d'une classe :
// ----
class Exemple
{
}; // <-- /!\ Le point virgule est obligatoire (erreur classique n°1)

void exempleInstantiation()
{
	// Allocation sur la pile (stack) :
	[[maybe_unused]] Exemple premiereInstance; // La memoire est libérée en sortie du scope automatiquement
	[[maybe_unused]] Exemple deuxiemeInstance{}; // Equivalent à la ligne précédente
	// Note :
	// Exemple exemple(); => Erreur de compilation
	// "Bug" horrible du langage : un constructeur vide ne prends pas de parentheses (erreur classique n°2)

	// Allocation sur le tas (heap, allocation dynamique) :
	auto* ptrExempleSurInstance3 = new Exemple; // La memoire n'est jamais libérée automatiquement
	delete ptrExempleSurInstance3; // On le fait manuellement via un delete
	// J'utilise auto pour ne pas dupliquer le type de l'objet
	// Toujours typé fortement, je ne peux mettre qu'un type dans un objet auto.
	// Ici, auto est déduit en Exemple

	// En réalité, on ne fait jamais ces allocations via new et delete dans du code de prod',
	// c'est trop risqué d'oublier le delete
	// Allocation sur le tas (heap, allocation dynamique) via un smart pointer lui alloué sur la pile (stack) :
	auto smartPtrExemple = std::make_unique<Exemple>();
	// Le smart pointeur est créée sur la pile, il alloue un objet Exemple sur le tas.
	// La memoire est liberée quand le smart pointeur est detruit.
	// Ici auto est équivalent à std::unique_ptr<Exemple>
} // smartPtrExemple est detruit ici, le destructeur est appele
// premiereInstance et deuxiemeInstance sont aussi detruits ici, le destructeur est appele



// ----
// Définition d'une classe avec un attribut d'instance :
// ----
class ExempleAvecAttribut
{
	public:
		ExempleAvecAttribut(int attribut)
			: mAttribut(attribut)
		// Pour les constructeurs et uniquement pour eux, on utilise la liste
		// d'initialisation pour initialiser les attributs via le ':'.
		{}

		int getAttribut() const
		// Le mot clé const explicite le fait que l'on ne modifie rien
		// lors de l'execution de cette methode.
		{
			return mAttribut;
		}

	private:
		// Sauf exception, les attributs d'instance sont toujours privés
		int mAttribut = 0;
};

void exempleInstantiation2()
{
	ExempleAvecAttribut exempleAvecAttribut1(42);
	std::cout << exempleAvecAttribut1.getAttribut() << std::endl; // Affiche 42

	ExempleAvecAttribut exempleAvecAttribut2(39);
	std::cout << exempleAvecAttribut2.getAttribut() << std::endl; // Affiche 39
	std::cout << exempleAvecAttribut1.getAttribut() << std::endl; // Affiche 42
}



// ----
// Définition d'une classe avec un attribut de classe :
// ----
class ExempleAvecAttributDeClasse
{
	public:
		ExempleAvecAttributDeClasse()
		{
			++mNbInstancesEnVie;
			++mNbInstancesTotal;
		}

		// Ceci est le descructeur, il ne peut y en avoir qu'un par classe
		~ExempleAvecAttributDeClasse()
		{
			--mNbInstancesEnVie;
		}

		// Le mot clé static est utilisé pour définir les attributs et les méthodes de classe.
		static std::pair<int, int> getNbInstances()
		{
			return {mNbInstancesEnVie, mNbInstancesTotal};
		}

	private:
		static int mNbInstancesEnVie;
		static int mNbInstancesTotal;
};
int ExempleAvecAttributDeClasse::mNbInstancesEnVie = 0;
int ExempleAvecAttributDeClasse::mNbInstancesTotal = 0;

void displayNbInstances()
{
	std::cout << "En vie : " << ExempleAvecAttributDeClasse::getNbInstances().first
		<< " / Total : " << ExempleAvecAttributDeClasse::getNbInstances().second << std::endl;
}

void exempleInstantiation3()
{
	ExempleAvecAttributDeClasse ex1; // La memoire est libérée en sortie du scope automatiquement
	displayNbInstances(); // En vie : 1 / Total : 1
	{
		ExempleAvecAttributDeClasse ex2; // La memoire est libérée en sortie du scope automatiquement
		displayNbInstances(); // En vie : 2 / Total : 2
	} // Sortie du scope, ex2 est detruit
	displayNbInstances(); // En vie : 1 / Total : 2
	
	{
		[[maybe_unused]] auto* ex3 = new ExempleAvecAttributDeClasse; // La memoire n'est jamais libérée automatiquement
		displayNbInstances(); // En vie : 2 / Total : 3
	} // J'ai oublié le delete, le memoire est perdue : memory leak
	displayNbInstances(); // En vie : 2 / Total : 3
	{
		auto ex4 = std::make_unique<ExempleAvecAttributDeClasse>();
		displayNbInstances(); // En vie : 3 / Total : 4
	} // Sortie du scope, ex4 est detruit
	displayNbInstances(); // En vie : 2 / Total : 4
} // ex1 est detruit, En vie : 1 / Total : 4, ex2 est toujours la



// ----
// Définition d'une hierarchie de classe et polymorphisme :
// ----
class ExempleMere
{
	public:
		virtual void afficherPolymorphe() const // Le mot clé virtual permet le polymorphisme
		{ std::cout << "Je suis la classe mere" << std::endl; }
		void afficher() const
		{ std::cout << "Je suis peut etre la classe mere" << std::endl; }
};
class ExempleFille : public ExempleMere
{
	public:
		void afficherPolymorphe() const override // Le mot clé override rend explicit le polymorphisme
		{ std::cout << "Je suis la classe fille" << std::endl; }
		//void afficher() const override // Erreur de compil', la classe mere n'a pas afficher en virtual
		void afficher() const
		{ std::cout << "Je suis peut etre la classe fille" << std::endl; }
};

void exempleInstantiation4()
{
	ExempleMere exempleMere;
	ExempleFille exempleFille;

	// Quand je manipule un objet directement, il n'y a pas de polymorphisme possible
	// le resultat est donc tres logique :
	exempleMere.afficherPolymorphe(); // Affiche "Je suis la classe mere"
	exempleFille.afficherPolymorphe(); // Affiche "Je suis la classe fille"
	exempleMere.afficher(); // Affiche "Je suis peut etre la classe mere"
	exempleFille.afficher(); // Affiche "Je suis peut etre la classe fille"

	// Lorsaue l'on manipule un objet via un pointeur ou une reference, le polymorphisme est possible
	// On peut avoir une reference ou un pointeur vers la classe mere qui pointe vers un objet de la classe fille
	// C'est le cas dans l'exemple suivant. Sur des arbres d'heritage plus complexes, cela peut etre une classe mere
	// plusieurs niveaux au dessus.
	// Note : une reference est juste du sucre syntaxique pour un pointeur constant
	ExempleMere& refExempleMere = exempleFille; // Manipulation de exempleFille via une reference vers la classe mere
	refExempleMere.afficherPolymorphe(); // Affiche "Je suis la classe fille"
	refExempleMere.afficher(); // Affiche "Je suis peut etre la classe mere"
	ExempleMere* ptrExempleMere2 = &exempleMere; // Manipulation de exempleMere via un pointeur vers la classe mere
	ptrExempleMere2->afficherPolymorphe(); // Affiche "Je suis la classe mere"
	ptrExempleMere2->afficher(); // Affiche "Je suis peut etre la classe mere"
}
