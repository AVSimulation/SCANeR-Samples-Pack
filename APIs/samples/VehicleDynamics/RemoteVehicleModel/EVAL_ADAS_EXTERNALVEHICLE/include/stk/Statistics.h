#pragma once

#include "stk/STK.h"

#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

namespace stk 
{
	//---------------------------------------------------------------------------------------------------------------------------------
	//	A Statistical Analyzer allows to make statistics on a population of the given type
	template<typename PopulationType>
	class StatisticalAnalyzer
	{
	public:		//	Constructor - Destructor
		StatisticalAnalyzer() : myPopulationSize(0) {}
		virtual ~StatisticalAnalyzer() {}

	public:		//	Public Accessor
		inline size_t getPopulationSize() const;

	public:		//	Public Virtual Method
		virtual inline void initPopulationAnalysis();
		virtual void addPopulationSample(const PopulationType &sample);
		virtual void removePopulationSample(const PopulationType &sample);
		
	private:	//	Private Members
		size_t myPopulationSize;
	};

	template<typename PopulationType>
	size_t StatisticalAnalyzer<PopulationType>::getPopulationSize() const
	{
		return myPopulationSize;
	}

	template<typename PopulationType>
	void StatisticalAnalyzer<PopulationType>::initPopulationAnalysis() 
	{
		myPopulationSize = 0; 
	}

	template<typename PopulationType>
	void StatisticalAnalyzer<PopulationType>::addPopulationSample(const PopulationType &sample)
	{ 
		myPopulationSize += 1;
	}

	template<typename PopulationType>
	void StatisticalAnalyzer<PopulationType>::removePopulationSample(const PopulationType &sample)
	{
		myPopulationSize -= 1;
	}


	//---------------------------------------------------------------------------------------------------------------------------------
	//	Calculate the distribution of a categorized population via the index of the category they belong
	class PopulationDistributionAnalyzer : public StatisticalAnalyzer<size_t>
	{
	public:		//	Constructor - Destructor
		PopulationDistributionAnalyzer(size_t categoryNumber) :
			StatisticalAnalyzer(),
			myPopulationByCategory(categoryNumber, 0)
		{}

		virtual ~PopulationDistributionAnalyzer()
		{}

	public:		//	Public Accessors
		inline void getPopulationDistribution(/*out*/ std::vector<double> &populationDistribution) const
		{
			//	Fill the population 
			populationDistribution.reserve(myPopulationByCategory.size());
			size_t populationSize = getPopulationSize();
			for (size_t populationInCategory : myPopulationByCategory)
				populationDistribution.emplace_back(static_cast<double>(populationInCategory) / static_cast<double>(getPopulationSize()));
		}

	public:		//	Public Virtual Method
		virtual void initPopulationAnalysis() override
		{
			StatisticalAnalyzer::initPopulationAnalysis();
			std::fill(myPopulationByCategory.begin(), myPopulationByCategory.end(), 0);
		}

		virtual void addPopulationSample(const size_t &sample) override
		{
			StatisticalAnalyzer::addPopulationSample(sample);
			myPopulationByCategory[sample] += 1;
		}

		void removePopulationSample(const size_t &sample) override
		{
			StatisticalAnalyzer::removePopulationSample(sample);
			myPopulationByCategory[sample] = (myPopulationByCategory[sample] > 0) ? myPopulationByCategory[sample] - 1 : 0;
		}

	private:	//	Private Members
		std::vector<size_t> myPopulationByCategory;
	};


	//---------------------------------------------------------------------------------------------------------------------------------
	//	Calculate the mean and standard deviation of a population
	template<typename PopulationType>
	class StandardDeviationCalculator : public StatisticalAnalyzer<PopulationType>
	{
	public:		//	Constructor - Destructor
		StandardDeviationCalculator();
		virtual ~StandardDeviationCalculator();

	public:		//	Public Accessors
		inline double getMean() const;
		inline double getStandardDeviation() const;

	public:		//	Public Virtual Method
		virtual inline void initPopulationAnalysis() override;
		virtual void addPopulationSample(const PopulationType &sample) override;

	private:	//	Private Members
		double myCurrentMean;
		double myCurrentDeviationAcc;
	};

	template<typename PopulationType>
	StandardDeviationCalculator<PopulationType>::StandardDeviationCalculator() :
		StatisticalAnalyzer<PopulationType>(),
		myCurrentMean(std::numeric_limits<double>::quiet_NaN()),
		myCurrentDeviationAcc(0)
	{}

	template<typename PopulationType>
	StandardDeviationCalculator<PopulationType>::~StandardDeviationCalculator()
	{}

	template<typename PopulationType>
	double StandardDeviationCalculator<PopulationType>::getMean() const
	{
		return myCurrentMean;
	}

	template<typename PopulationType>
	double StandardDeviationCalculator<PopulationType>::getStandardDeviation() const 
	{
		return StatisticalAnalyzer<PopulationType>::getPopulationSize() > 1 ? std::sqrt(myCurrentDeviationAcc / (static_cast<double>(StatisticalAnalyzer<PopulationType>::getPopulationSize() - 1))) : 0;
	}

	template<typename PopulationType>
	void StandardDeviationCalculator<PopulationType>::initPopulationAnalysis()
	{
		StatisticalAnalyzer<PopulationType>::initPopulationAnalysis();
		myCurrentMean = std::numeric_limits<double>::quiet_NaN();
		myCurrentDeviationAcc = 0;
	}
	template<typename PopulationType>
	void StandardDeviationCalculator<PopulationType>::addPopulationSample(const PopulationType &sample)
	{
		const double sampleValue = static_cast<const double>(sample);
		StatisticalAnalyzer<PopulationType>::addPopulationSample(sample);
		if (StatisticalAnalyzer<PopulationType>::getPopulationSize() == 1)
		{
			myCurrentMean = sampleValue;
			myCurrentDeviationAcc = 0;
		}
		else
		{
			const double oldMean = myCurrentMean;
			const double oldDeviationAcc = myCurrentDeviationAcc;
			myCurrentMean = oldMean + (sampleValue - oldMean) / static_cast<double>(StatisticalAnalyzer<PopulationType>::getPopulationSize());
			myCurrentDeviationAcc = oldDeviationAcc + (sampleValue - oldMean) * (sampleValue - myCurrentMean);
		}
	}
}