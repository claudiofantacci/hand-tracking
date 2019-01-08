#ifndef PLAYWALKMANPOSEMODEL_H
#define PLAYWALKMANPOSEMODEL_H

#include <KinPoseModel.h>

#include <iCub/iKin/iKinFwd.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Vector.h>

#include <string>


class PlayWalkmanPoseModel : public KinPoseModel
{
public:
    PlayWalkmanPoseModel(const std::string& robot, const std::string& laterality, const std::string& port_prefix) noexcept;

    ~PlayWalkmanPoseModel() noexcept;

    bool setProperty(const std::string& property) override;

protected:
    Eigen::VectorXd readPose() override;

    yarp::sig::Vector readRootToEE();

    yarp::os::BufferedPort<yarp::os::Bottle> port_arm_pose_;

private:
    const std::string log_ID_ = "[PlayWalkmanPoseModel]";

    const std::string port_prefix_ = "PlayWalkmanPoseModel";

    const std::string robot_;

    const std::string laterality_;
};

#endif /* PLAYWALKMANPOSEMODEL_H */