
#pragma once

#include "stk/STK.h"

#include <iostream>

namespace stk {

class STK_API PID
{
public:
	PID();
	PID(double kp, double ki, double kd, bool ResetIntegrale);
	
	double integre(double ValeurActuelle, double ValeurConsigne, double DeltaT);

	double integre(double ValeurActuelle, double VitesseActuelle, double ValeurConsigne, double VitesseConsigne, double DeltaT);

	bool isInitialised();

	/**
	* Set the PID instantly

	* \param	kp		the proportional coefficient
	* \param	ki		the integral coefficient
	* \param	kd		the derivatives coefficient
	*/

	void setPID(double kp, double ki, double kd);

	std::ostream& describeParams(std::ostream& out);
private:

	bool isInit;	//permet de voir si on a utilisé le constructeur complet

	bool isResetIntegrale;	//est ce qu on reinitialise le cumul d'erreur quand l'erreur change de signe

	double myKp;	//coeff proportionnel
	double myKi;	//coeff intégrateur
	double myKd;	//coeff dérivateur

	double myError;
	double myErrorCumulee;
	double myErrorDerivee;
};

}
