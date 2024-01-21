

class Repas : public IRepas {
  Repas(Plat platPrincipal)
    : mPlatPrincipal(platPrincipal) {}
  void preparer() override {
    mCuistot.preparer(mPlatPrincipal);
  }
  int cout() override {
    return Plat::getPrix(mPlatPrincipal);
  }
};

class DecorateurRepas : public IRepas {
  DecorateurRepas(const IRepas& repasADecorer)
    : mRepasADecorer(repasADecorer) {}
  void preparer() override {
    mRepasADecorer.preparer();
  }
  int cout() override {
    return mRepasADecorer.cout();
  }
};

class SurplusSoir : public DecorateurRepas {
  SurplusSoir(const IRepas& repasADecorer)
    : DecorateurRepas(repasADecorer) {}
  int cout() override {
    return mRepasADecorer.cout() * 1.5;
  }
};

class Boisson: public DecorateurRepas {
  Boisson(const IRepas& repasADecorer, BoissonId boissonId)
    : DecorateurRepas(repasADecorer), mBoisson(boisson) {}
  void preparer() override {
    mBarman.preparer(mBoisson);
  }
  int cout() override {
    return mRepasADecorer + Boisson::getPrix(mBoisson);
  }
};

class BoissonAlcoolisee: public Boisson {
  BoissonAlcoolisee(IRepas repasADecorer, BoissonId boissonId)
    : Boisson(repasADecorer, boisson) {}
  void preparer() override {
    mChefDeSalle.verifierAge();
    mBarman.preparer(mBoisson);
  }
};

  Repas repasSurLePousse(Plat::SteakFrite);
  std::cout << repasSurLePousse.cout() << std::endl;
  auto grosRepas =
    SurplusSoir(
      BoissonAlcoolisee(
        Dessert(
          Dessert(
            repasSurLePousse,
            DessertId::MousseAuChocolat),
          DessertId::Glace3Boules),
        BoissonId::PinteBiere)
      );
  std::cout << grosRepas.cout() << std::endl; 
  IRepas

class Repas : public IRepas{
   void setPlat(Plat platPrincipal) {
    mPlatPrincipal = platPrincipal;
  }
  void preparer() {
    mCuistot.preparer(mPlatPrincipal);
  }
  int cout() {
    return Plat::getPrix(mPlatPrincipal);
  }
};

};  void setPlat(Plat platPrincipal) {
    mPlatPrincipal = platPrincipal;
  }
  void preparer() {
    mCuistot.preparer(mPlatPrincipal);
  }
  int cout() {
    return Plat::getPrix(mPlatPrincipal);
  }
}


class PetitDej {
  void setItem(Item cereal) {
    assert(Item::isCereal(cereal));
    mCereal = cereal;
  }
  void preparer() {
    mServeur.verserLait();
    mServeur.verserCereal(mCereal);
  }
  void cout() {
    return Item::getPrix(mCereal);
  }
}

class PositionTracking {
  void onQuitterMaison() {
    mDomotique.arretHorsGel();
  }
}

class Domotique {
  void arretHorsGel() {
    for (auto& vollet : mGestionVollet.listeVollets()) {
      mGestionVollet.fermer(Vollet);
    }
    for (auto& terminalChauff : mChauffage.listeTerminal()) {
      mChauffage.setTemp(10);
    }
    mEau.couper();
  }
  void preAllumage() {
    for (auto& terminalChauff : mChauffage.listeTerminal()) {
      mChauffage.setTemp(17);
    }
  }
}


void ajouterBugs(const MaList<Ticket>& tickets) {
  Ticket* courant = tickets.head();
  while(courant) {
    mTousTickets.ajouter(courant);
    courant = courant->suivant();
  }
}

void ajouterBugs(const MonVecteur<Ticket>& tickets) {
  for (int i = 0; i < tickets.size(); ++i) {
    mTousTickets.ajouter(tickets[i]);
  }
}

for (auto& elementCourant: monConteneur) {
  traiter(elementCourant);
}

class MonApplicationGraphique
{
  public:
    void paint();

  private:
    Menu menuPrincipal;
    Fenetre fenetrePrincipale;
};

class Fenetre
{
  public:
    void paint();

  private:
    Menu menu;
    Widget widget;
};

