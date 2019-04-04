/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef GATEPOSE_H
#define GATEPOSE_H

#include <BayesFilters/ParticleSet.h>
#include <BayesFilters/PFCorrectionDecorator.h>
#include <BayesFilters/StateModel.h>


class GatePose : public bfl::PFCorrectionDecorator
{
public:
    GatePose(std::unique_ptr<PFCorrection> visual_correction,
             const double gate_x, const double gate_y, const double gate_z,
             const double gate_rotation,
             const double gate_aperture) noexcept;

    GatePose(std::unique_ptr<PFCorrection> visual_correction) noexcept;

    ~GatePose() noexcept;

protected:
    void correctStep(const bfl::ParticleSet& pred_particles, bfl::ParticleSet& corr_particles) override;

    virtual Eigen::VectorXd readPose() = 0;

    bool isInsideEllipsoid(const Eigen::Ref<const Eigen::VectorXd>& state);

    bool isWithinRotation(double rot_angle);

    bool isInsideCone(const Eigen::Ref<const Eigen::VectorXd>& state);

private:
    double gate_x_;

    double gate_y_;

    double gate_z_;

    double gate_aperture_;
    
    double gate_rotation_;

    Eigen::VectorXd ee_pose_;
};

#endif /* GATEPOSE_H */
