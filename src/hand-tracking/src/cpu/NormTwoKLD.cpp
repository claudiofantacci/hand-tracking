/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#include <NormTwoKLD.h>

#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace bfl;
using namespace Eigen;



struct NormTwoKLD::ImplData
{
    double likelihood_gain_;

    std::size_t vector_size_;
};


NormTwoKLD::NormTwoKLD(const double likelihood_gain, const std::size_t vector_size) noexcept :
pImpl_(std::unique_ptr<ImplData>(new ImplData))
{
    pImpl_->likelihood_gain_ = likelihood_gain;

    pImpl_->vector_size_ = vector_size;
}


NormTwoKLD::~NormTwoKLD() noexcept
{ }


std::pair<bool, VectorXd> NormTwoKLD::likelihood(const MeasurementModel& measurement_model, const Ref<const MatrixXd>& pred_states)
{
    throw std::runtime_error("ERROR::NORMTWOKLD::LIKELIHOOD\nERROR: Unimplemented.");
}
