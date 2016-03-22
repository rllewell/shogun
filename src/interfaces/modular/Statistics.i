/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012-2013 Heiko Strathmann
 */

/* Remove C Prefix */
%rename(HypothesisTest) CHypothesisTest;
%rename(OneDistributionTest) COneDistributionTest;
%rename(TwoDistributionTest) CTwoDistributionTest;
%rename(IndependenceTest) CIndependenceTest;
%rename(TwoSampleTest) CTwoSampleTest;
%rename(MMD) CMMD;
%rename(LinearTimeMMD) CLinearTimeMMD;
%rename(BTestMMD) CBTestMMD;
%rename(QuadraticTimeMMD) CQuadraticTimeMMD;

/* Include Class Headers to make them visible from within the target language */
%include <shogun/statistical_testing/HypothesisTest.h>
%include <shogun/statistical_testing/OneDistributionTest.h>
%include <shogun/statistical_testing/TwoDistributionTest.h>
%include <shogun/statistical_testing/IndependenceTest.h>
%include <shogun/statistical_testing/TwoSampleTest.h>
%include <shogun/statistical_testing/MMD.h>
%include <shogun/statistical_testing/LinearTimeMMD.h>
%include <shogun/statistical_testing/BTestMMD.h>
%include <shogun/statistical_testing/QuadraticTimeMMD.h>
