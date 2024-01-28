
#pragma once

// NE PAS MODIFIER

class Champignon
{
	// NE PAS MODIFIER
	public:
		enum class Meteo { Soleil, PasSoleil };

		Champignon(float vitessePousse);

		float getHauteurChampignon() const;
		float getSurfaceChampignon() const;

		void pousse(Meteo meteoDuJour);

	// NE PAS MODIFIER
	private:
		float mHauteurChampignon = 0.0f;
		float mSurfaceChampignon = 0.0f;
		float mVitessePousse;
};

// NE PAS MODIFIER
