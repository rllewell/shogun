/*
 * Restructuring Shogun's statistical hypothesis testing framework.
 * Copyright (C) 2016  Soumyajit De
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MMD_H_
#define MMD_H_

#include <memory>
#include <functional>
#include <shogun/statistical_testing/TwoSampleTest.h>

namespace shogun
{

class CKernel;
template <typename> class SGVector;
template <typename> class SGMatrix;

enum class EStatisticType
{
	UNBIASED_FULL,
	UNBIASED_INCOMPLETE,
	BIASED_FULL
};

enum class EVarianceEstimationMethod
{
	DIRECT,
	PERMUTATION
};

enum class ENullApproximationMethod
{
	PERMUTATION,
	MMD1_GAUSSIAN,
	MMD2_SPECTRUM,
	MMD2_GAMMA
};

class CMMD : public CTwoSampleTest
{
	using operation = std::function<float64_t(SGMatrix<float64_t>)>;
public:
	CMMD();
	virtual ~CMMD();

	virtual float64_t compute_statistic() override;
	SGVector<float64_t> compute_statistic(bool multiple_kernels);

	float64_t compute_variance();
	SGVector<float64_t> compute_variance(bool multiple_kernels);

	void set_statistic_type(EStatisticType stype);
	const EStatisticType get_statistic_type() const;

	void set_variance_estimation_method(EVarianceEstimationMethod vmethod);
	const EVarianceEstimationMethod get_variance_estimation_method() const;

	void set_simulate_null(bool simulate_null);
	void set_num_null_samples(index_t null_samples);
	const index_t get_num_null_samples() const;

	virtual SGVector<float64_t> sample_null() override;

	void set_null_approximation_method(ENullApproximationMethod nmethod);
	const ENullApproximationMethod get_null_approximation_method() const;

	void use_gpu(bool gpu);

	virtual const char* get_name() const;
protected:
	virtual const operation get_direct_estimation_method() const = 0;
	virtual const float64_t normalize_statistic(float64_t statistic) const = 0;
	virtual const float64_t normalize_variance(float64_t variance) const = 0;
private:
	struct Self;
	std::unique_ptr<Self> self;

};

}
#endif // MMD_H_
