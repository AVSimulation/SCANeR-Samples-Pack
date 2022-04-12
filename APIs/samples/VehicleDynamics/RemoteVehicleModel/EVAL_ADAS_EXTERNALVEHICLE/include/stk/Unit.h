
#pragma once

#include "stk/STK.h"

#include <iostream>

namespace stk {

enum t_dimension {
	TDimNone,
	TDimLength,
	TDimSurface,
	TDimVolume,
	TDimVolumeAngle,
	TDimAngle,
	TDimMass,
	TDimVolumetricMass,
	TDimInertia,
	TDimTime,
	TDimFrequency,
	TDimSpeed,
	TDimAccel,
	TDimSpeedAngle,
	TDimAccelAngle,
	TDimForce,
	TDimPressure,
	TDimEnergy,
	TDimTorque,
	TDimPower,
	TDimDynamicViscosity,
	TDimCinematicViscosity,
	TDimTemperature,
	TDimIntensity,
	TDimTension,
	TDimResistance,
	TDimQuantElec,
	TDimInductance,
	TDimVariationAngle,
	TDimVariationForce,
	TDimConstanteTorqueAngle,
	TDimConstanteTorqueElecMotor,
	TDimStiffness,
	TDimAngularStiffness,
	TDimAngularSpeedStiffness,
	TDimTorsionAngleStiffness,
	TDimSensLinPressureStiffness,
	TDimTorsionalFlexibility,
	TDimLinearDamping,
	TDimAngularTorsionDamping,
	TDimFuelConsumption,
	TDimSpecConsumption,
	TDimDistConsumption,
	TDimCurvature,
	TDimWeightPower,
	TDimFlexibility,
	TDimBrakeEfficiency,
	TDimThermicCapacity,
	TDimThermicConductivity,
	TDimThermicConvection,
	TDimInstPollution,
	TDimPollutionDist,
	TDimIlluminance,
	TDimLuminousIntensity,
	TDimOthers,
};

//NOTE la premiere est toujours la norme SI
enum t_unit {
// NOT FOUND
	TUnitNotFound,
// SANS
	TUnitNone,
	TUnitFraction,
	TUnitPercent,
	TUnitNewtonPerKiloNewton,
// LONGUEUR
	TUnitMetre,
	TUnitMilliMetre,
	TUnitCentiMetre,
	TUnitKiloMetre,
	TUnitInch,
	TUnitFeet,
	TUnitYard,
	TUnitMile,
// SURFACE
	TUnitMetre2,
	TUnitDeciMetre2,
	TUnitCentiMetre2,
	TUnitMilliMetre2,
// VOLUME
	TUnitMetre3,
	TUnitDeciMetre3,
	TUnitCentiMetre3,
	TUnitMilliMetre3,
	TUnitLitre,
	TUnitInch3,
	TUnitFeet3,
	TUnitGallonUK,
	TUnitGallonUS,
// VOLUME PAR UNITE ANGULAIRE
	TUnitMetre3PerRadian,
	TUnitCentiMetre3PerTurn,
// ANGLE
	TUnitRadian,
	TUnitDegre,
	TUnitDecaDegre,
	TUnitAngleMinute,
	TUnitMillieme,
	TUnitTurn,
// MASSE
	TUnitKiloGram,
	TUnitGram,
	TUnitTon,
	TUnitPound,
	TUnitOnce,
	TUnitStone,
// MASSE VOLUMIQUE
	TUnitKiloGramPerMetre3,
	TUnitKiloGramPerDeciMetre3,
// MOMENT D'INERTIE
	TUnitKiloGramMetre2,
	TUnitKiloGramMilliMetre2,
// TEMPS
	TUnitSecond,
	TUnitMilliSecond,
	TUnitMicroSecond,
	TUnitMinute,
	TUnitHour,
// FREQUENCE
	TUnitHertz,
	TUnitPerSecond,
	TUnitParMinute,
// VITESSE
	TUnitMetrePerSecond,
	TUnitKilometrePerHour,
	TUnitMilesPerHour,
	TUnitMilliMetrePerSecond,
// ACCELERATION
	TUnitMetrePerSecond2,
	TUnitG,
	TUnitMilliMetrePerSecond2,
// VITESSE ANGULAIRE
	TUnitRadianPerSecond,
	TUnitRevolutionPerMinute,
	TUnit1000RevolutionsPerMinute,
	TUnitDegrePerSecond,
// ACCELERATION ANGULAIRE
	TUnitRadianPerSecond2,
	TUnitDegrePerSecond2,
// FORCE
	TUnitNewton,
	TUnitDecaNewton,
	TUnitKiloNewton,
	TUnitKiloGrammeForce,
	TUnitDecaNewtonParPourcent,
	TUnitPoundForce,
// PRESSION
	TUnitPascal,
	TUnitKiloPascal,
	TUnitMegaPascal,
	TUnitBar,
	TUnitPsi,
	TUnitMilliBar,
// CONTRAINTE MÉCANIQUE
// ENERGIE
	TUnitJoule,
	TUnitKiloJoule,
// COUPLE
	TUnitNewtonMetre,
	TUnitDecaNewtonMetre,
	TUnitKiloGrammeMetre,
// PUISSANCE
	TUnitWatt,
	TUnitHP,
	TUnitPS,
	TUnitKiloWatt,
	TUnitMilliWatt,
// VISCOSITE DYNAMIQUE
	TUnitPoiseuille,
	TUnitPascalSecond,
	TUnitMilliPoiseuille,
	TUnitPoise,					
// VISCOSITE CINEMATIQUE
	TUnitMetre2PerSecond,	
	TUnitMilliMetre2ParSecond,
// TEMPERATURE
	TUnitKelvin,
	TUnitCelsius,
	TUnitFahrenheit,
// INTENSITE
	TUnitAmpere,
	TUnitMilliAmpere,
// TENSION
	TUnitVolt,
	TUnitMilliVolt,
// CONDUCTANCE (siemens : S )
// RESISTANCE
	TUnitOhm,
	TUnitKiloOhm,
	TUnitMegaOhm,
// QUANTITE D'ELECTRICITE
	TUnitCoulomb,
	TUnitAmpereSecond,
	TUnitAmpereHour,
// CAPACITÉ ÉLÉCTRIQUE (Farrad : F)									
// FLUX D'INDUCTION MAGNÉTIQUE (Weber : Wb)							
// INDUCTION MAGNÉTIQUE (Tesla : T)	
// INDUCTANCE
	TUnitHenry,
	TUnitMilliHenry,
// CHAMP MAGNÉTIQUE (A/m)
// VARIATION ANGULAIRE
	TUnitParRadian,
	TUnitParDegre,
// VARIATION DE FORCE
	TUnitParNewton,
	TUnitParDecaNewton,
// CONSTANTE DE COUPLAGE ANGULAIRE
	TUnitNewtonMetrePerRadian2PerSeconde2,
	TUnitDecaNewtonMetrePerTour2PerMinute2,
// CONSTANTE DE COUPLE DU MOTEUR ELECTRIQUE
	TUnitAmperePerNewtonMetre,
// RAIDEUR
	TUnitNewtonPerMetre,
	TUnitDecaNewtonPerMilliMetre,
	TUnitKiloNewtonPerMilliMetre,
// RAIDEUR ANGULAIRE : pour la rigidité de dérive (force Y obtenue par unité d'angle de dérive)
	TUnitNewtonPerRadian,  
	TUnitNewtonPerDegre,
	TUnitDecaNewtonPerDegre,
// RAIDEUR VITESSE ANGULAIRE : force proportionnelle à une vitesse de rotation
	TUnitNewtonPerRadianPerSecond,  
	TUnitNewtonPerDegrePerSecond,
	TUnitDecaNewtonPerTourPerMinute,
// RAIDEUR ANGULAIRE DE TORSION
	TUnitNewtonMetrePerRadian,
	TUnitDecaNewtonMetrePerDegre,
	TUnitNewtonMetrePerDegre,
// SENSIBILITE DE LA RAIDEUR LINEAIRE A LA PRESSION
	TUnitNewtonPerMetrePerPascal,
	TUnitDecaNewtonPerMilliMetrePerBar,
// FLEXIBILITE DE TORSION
	TUnitRadianPerNewtonMetre,
	TUnitDegrePerDecaNewtonMetre,
// AMORTISSEMENT LINEAIRE
	TUnitNewtonPerMetrePerSecond,
	TUnitDecaNewtonPerMetrePerSecond,
// AMORTISSEMENT ANGULAIRE DE TORSION
	TUnitNewtonMetrePerRadianPerSecond,
	TUnitDecaNewtonMetrePerDegrePerSecond,
	TUnitNewtonMetrePerDegrePerSecond,
	TUnitNewtonMetrePerRPM,
// CONSOMMATION INSTANTANNEE
	TUnitMetre3PerSecond,
	TUnitLitrePerSecond,
	TUnitLitrePerMinute,
	TUnitLitrePerHour,
	TUnitMilliLitrePerSecond,
// CONSOMMATION SPEC
	TUnitKiloGrammePerWattPerSecond,
	TUnitGramsPerKiloWattPerHour,
// CONSOMMATION / DIST
	TUnitMetre3PerMetre,
	TUnitLitrePer100KiloMeter,
// COURBURE
	TUnitPerMetre,
// RAPPORT POIDS PUISSANCE
	TUnitKiloGramPerWatt,
	TUnitKiloGramPerKiloWatt,
	TUnitKiloGrammePerPS,
// FLEXIBILITE
	TUnitMetrePerNewton,
	TUnitMilliMetrePerDecaNewton,
	TUnitMilliMetrePerKiloNewton,
// EFFICACITE DE FREIN
	TUnitNewtonMetrePerPascal,
	TUnitDecaNewtonMetrePerBar,
// CAPACITE THERMIQUE
	TUnitJoulePerKiloGramPerKelvin,
// CONDUCTIVITE THERMIQUE
	TUnitWattPerMetrePerKelvin,
// CONVECTION THERMIQUE
	TUnitWattPerMetre2PerKelvin,
// POLLUTION INSTANTANEE
	TUnitKiloGramPerSecond,
	TUnitGramPerSecond,
// POLLUTION DISTANCE
	TUnitKiloGramPerMetre,
	TUnitGramPerKiloMetre,
// INTENSITE LUMINEUSE
	TUnitCandela,
// ECLAIREMENT LUMINEUX
	TUnitLux,
// INTENSITE ENERGETIQUE
	TUnitWattPerSteradian,
// AUTRES
	TUnitDegrePerMilliMetre,
	TUnitDegrePerG,
	TUnitRPMPerRacinedaNMetre,
	TUnitMetrePerRadian,
	TUnitMillimetrePerDegre,
	TUnitBarPerDecaNewton
};

STK_API std::istream& operator>>(std::istream& in, t_unit &x);
//STK_API ostream& operator<<(ostream& out, t_unit x);
STK_API std::ostream& operator<<(std::ostream& out, const t_unit& x);

STK_API t_dimension getDimension(t_unit unite);
STK_API t_unit SIUnit(t_dimension dim);
STK_API t_unit commonlyUsedUnit(t_dimension dim);
STK_API t_unit toTUnit(const char* str);
STK_API double convToSI(t_unit unite, double value);
STK_API double convToUnit(t_unit unite, double value);

// Retourne le nom de l'unité correspondant à unite
STK_API const char* toText(t_unit unite);

struct STK_API DecritUnite
{
	const char* Nom;
	const char* NomAlt;
	double FacteurConv;
	double OffsetConv;
	t_dimension dim;
};

extern STK_API DecritUnite ToutesLesUnites[];
extern STK_API const int ToutesLesUnitessize;

}
