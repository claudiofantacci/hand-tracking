/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef ICUBFWDKINMODEL_H
#define ICUBFWDKINMODEL_H

#include <FwdKinModel.h>

#include <iCub/iKin/iKinFwd.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IEncoders.h>
#include <yarp/os/ConstString.h>
#include <yarp/sig/Vector.h>


class iCubFwdKinModel : public FwdKinModel
{
public:
    iCubFwdKinModel(const yarp::os::ConstString& robot, const yarp::os::ConstString& laterality, const yarp::os::ConstString& port_prefix);

    ~iCubFwdKinModel() noexcept;

    bool setProperty(const std::string& property) override;

protected:
    Eigen::VectorXd   readPose() override;

    yarp::sig::Vector readTorso();

    yarp::sig::Vector readRootToEE();

    yarp::dev::PolyDriver  drv_arm_enc_;
    yarp::dev::PolyDriver  drv_torso_enc_;
    yarp::dev::IEncoders * itf_arm_enc_;
    yarp::dev::IEncoders * itf_torso_enc_;
    iCub::iKin::iCubArm    icub_kin_arm_;

private:
    yarp::os::ConstString  ID_     = "iCubFwdKinModel";
    yarp::os::ConstString  log_ID_ = "[" + ID_ + "]";

    yarp::os::ConstString  robot_;
    yarp::os::ConstString  laterality_;
    yarp::os::ConstString  port_prefix_;
};

#endif /* ICUBFWDKINMODEL_H */
