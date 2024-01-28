
#include "Champignon.hpp"

// NE PAS MODIFIER

Champignon::Champignon(float vitessePousse) : mVitessePousse(vitessePousse)
{
}

// NE PAS MODIFIER

float Champignon::getHauteurChampignon() const
{
	return mHauteurChampignon;
}

// NE PAS MODIFIER

float Champignon::getSurfaceChampignon() const
{
	return mSurfaceChampignon;
}

// NE PAS MODIFIER

void Champignon::pousse(Meteo meteoDuJour)
{
	if (meteoDuJour == Meteo::Soleil)
	{
		mHauteurChampignon += mVitessePousse;
		mSurfaceChampignon += mVitessePousse * 10;
	}
	else
	{
		mSurfaceChampignon += mVitessePousse * 2;
	}
}
