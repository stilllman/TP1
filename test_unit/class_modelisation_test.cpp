
#include <gtest/gtest.h>

#include <tp1_cpp/Arbre.hpp>
#include <tp1_cpp/FabriqueVegetaux.hpp>
#include <tp1_cpp/Fleur.hpp>
#include <tp1_cpp/Vegetal.hpp>

#include <iostream>
#include <memory>
#include <utility>
#include <vector>


// Modelisation de la classe Arbre

// Modeliser les classes Arbre et Vegetal
// Vegetal est une classe abstraite (instanciation impossible), c'est la classe mere
// Arbre est une classe concrete, c'est la classe fille de Vegetal

TEST(ClassModelisationTest, ExistanceArbre) {
	[[maybe_unused]] Arbre monArbre;
  SUCCEED();
}

TEST(ClassModelisationTest, ExistanceInterfaceVegetable) {
	Arbre monArbre;
  EXPECT_TRUE(dynamic_cast<Vegetal*>(&monArbre));
}

// Vegetal contient un champ mTaille qui represente la taille du vegetal.
// Ce champs est accessible en modication uniquement depuis les classes filles
// via un setter pour etre modifié.
// Note : Creer un getter et un setter public par default pour tous les
//        champs est une aberation a mes yeux.
// Note 2 : Le mot clé protected permet de rendre un champ accessible uniquement
//          aux classes filles.

TEST(ClassModelisationTest, GetterTaille) {
	Arbre monArbre;
	monArbre.getTaille();
	Vegetal* ptrVegetal = &monArbre;
	ptrVegetal->getTaille();
  SUCCEED();
}

// Vegetal possede une methode virtuelle pure croissance que ses classes filles
// doivent surcharger.
// Surcharger l'implemenation pour Arbre pour faire croitre la taille de
// l'arbre de 1 à chaque appel.
// Rappel : Les méthodes ne sont pas virtuelle par défaut en C++. Il faut le
//          spécifier via le mot clé virtual.
//          Une méthode virtuelle pure est une méthode que les classes concrètes
//          sont forcées de surcharger (à un niveau ou un autre de l'héritage).
//          En C++, on spécifie une méthode virtuelle pure via "= 0".
//          Lorsque l'on surcharge une méthode, on utilise le mot clé override à
//          la place de virtual. Cela permet d'avoir une erreur de compilation si
//          la méthode mère n'existe pas ou plus.

TEST(ClassModelisationTest, Croissance) {
	Arbre monArbre;
	monArbre.croissance();
	Vegetal* ptrVegetal = &monArbre;
	ptrVegetal->croissance();
  SUCCEED();
}

// Les flotants ne permettent pas de décrire l'ensemble des nombres réels.
// Lorsque l'on compare deux flotants, il faut donc utiliser une marge d'erreur.
constexpr float TP1_EPSILON = 0.00001f;

TEST(ClassModelisationTest, Quand_Croissante_Taille_Arbre_Augmente_1) {
	Arbre monArbre;
	EXPECT_NEAR(monArbre.getTaille(), 0.0, TP1_EPSILON);
	monArbre.croissance();
	EXPECT_NEAR(monArbre.getTaille(), 1.0, TP1_EPSILON);
	monArbre.croissance();
	EXPECT_NEAR(monArbre.getTaille(), 2.0, TP1_EPSILON);
}

std::vector<std::unique_ptr<Vegetal>> creerDeToutArbre()
{
	std::vector<std::unique_ptr<Vegetal>> vegetaux;
	vegetaux.push_back(std::make_unique<Arbre>());
	vegetaux.push_back(std::make_unique<Arbre>());
	vegetaux.push_back(std::make_unique<Arbre>());
	vegetaux.push_back(std::make_unique<Arbre>());
	vegetaux[0]->croissance();
	vegetaux[0]->croissance();
	vegetaux[1]->croissance();
	vegetaux[3]->croissance();
	vegetaux[3]->croissance();
	vegetaux[3]->croissance();
	vegetaux[3]->croissance();
	vegetaux[3]->croissance();
	return vegetaux;
}

TEST(ClassModelisationTest, Quand_Croissante_Arbre_Grandissent) {
	std::vector<std::unique_ptr<Vegetal>> vegetaux =
		creerDeToutArbre();
	for (auto& vegetal : vegetaux)
	{
		float taille = vegetal->getTaille();
		vegetal->croissance();
		EXPECT_GT(vegetal->getTaille(), taille);
	}
}

// Ajouter une classe fille a Vegetal : Fleur
// Fleur possede une taille maximale qu'elle ne peux depasser

TEST(ClassModelisationTest, Quand_Croissante_Fleur_Sous_Max_Taille_Augmente_0_point_1) {
	Fleur maFleur(/*tailleMax = */ 1.5);
	EXPECT_NEAR(maFleur.getTaille(), 0.0, TP1_EPSILON);
	maFleur.croissance();
	EXPECT_NEAR(maFleur.getTaille(), 0.1, TP1_EPSILON);
	maFleur.croissance();
	EXPECT_NEAR(maFleur.getTaille(), 0.2, TP1_EPSILON);
}

TEST(ClassModelisationTest, Quand_Croissante_Fleur_Depace_Max_Taille_Block_Max) {
	Fleur maFleur(/*tailleMax = */ 0.05);
	EXPECT_NEAR(maFleur.getTaille(), 0.0, TP1_EPSILON);
	maFleur.croissance();
	EXPECT_NEAR(maFleur.getTaille(), 0.05, TP1_EPSILON);
	maFleur.croissance();
	EXPECT_NEAR(maFleur.getTaille(), 0.05, TP1_EPSILON);
}


// Stratégie

// La classe arbre est simpliste. Elle croit toujours de 1.
// Pour rendre les choses plus réalistes, on va permettre aux arbres de croitre
// différement selon l'environnement.

// Dans l'application:
//   - Instancier un arbre.
//   - Proposer un prompt à l'utilisateur
//   - Selon le choix, changer potentiellement les conditions de croissance de l'arbre.
//   - Faire croitre l'arbre.
// Ex de prise en compte des input utilisateur :
//
// while (true)
// {
//    int choix = 0;
//    std::cout << "Choix : 0-Quitter, 1-Pas de changement, 2-Dormance, 3-CroissancePrintaniere, 4-CroissanceEstivale, 5-Secheresse" << std::endl
//    std::cin >> choix;
//    switch (choix)
//    {
//			case 0: break;
//			case 1: break;
//			case 2: [...] break;
//			[...]
//    }
//    if (choix == 0) break; // Quitte la boucle while (true)
//    [...] // Traitement tour à tour
// }


// Fabrique

// Pour manipuler d'avantage d'elements, créer une classe Terrain en charge de gérer
// un ensemble de Vegetal:
// - Stocket les Vegetal dans un std::vector<std::unique_ptr<Vegetal>>.
// - Faire croitre l'ensemble des Vegetal.
// Pour instancier rapidement les Vegetal, les Vegetal à créer sont stockés dans un
// fichier sous la forme:
// - Une ligne par Vegetal.
// - Ligne au format: "<type> [<tailleMax>]" où <type> est soit "Arbre" soit "Fleur" et
//   <tailleMax> est un flottant présent uniquement pour les fleurs.
//
// Ex de lecture dans un fichier :
// std::ifstream fichier("mon_fichier.txt");
// std::string ligne;
// while (std::getline(fichier, ligne))
// {
// 	  std::istringstream iss(ligne);
//    std::string type;
//    iss >> type;
//    [...]


// Adapteur

// Une classe Champignon est disponible dans les fichier Champignon.hpp et Champignon.cpp.
// Cette classe ne doit pas être modifiée.
// Rajouter quelques lignes avec un type "Champignon" dans le fichier de configuration.
// Faire en sorte qu'il soit possible de l'utiliser.
