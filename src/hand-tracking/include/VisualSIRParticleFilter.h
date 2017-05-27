#ifndef VISUALSIRPARTICLEFILTER_H
#define VISUALSIRPARTICLEFILTER_H

#include <memory>
#include <vector>

#include <BayesFiltersLib/FilteringAlgorithm.h>
#include <BayesFiltersLib/Initialization.h>
#include <BayesFiltersLib/StateModel.h>
#include <BayesFiltersLib/ParticleFilterPrediction.h>
#include <BayesFiltersLib/VisualObservationModel.h>
#include <BayesFiltersLib/VisualCorrection.h>
#include <BayesFiltersLib/Resampling.h>
#include <Eigen/Dense>
#include <iCub/iKin/iKinFwd.h>
#include <opencv2/cudaobjdetect.hpp>
#include <thrift/VisualSIRParticleFilterIDL.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IAnalogSensor.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/ConstString.h>
#include <yarp/os/Port.h>
#include <yarp/sig/Image.h>
#include <yarp/sig/Matrix.h>
#include <yarp/sig/Vector.h>


class VisualSIRParticleFilter: public bfl::FilteringAlgorithm,
                               public VisualSIRParticleFilterIDL
{
public:
    /* Default constructor, disabled */
    VisualSIRParticleFilter() = delete;

    /* VisualSIR complete constructor */
    VisualSIRParticleFilter(std::unique_ptr<bfl::Initialization> initialization,
                            std::unique_ptr<bfl::ParticleFilterPrediction> prediction, std::unique_ptr<bfl::VisualCorrection> correction,
                            std::unique_ptr<bfl::Resampling> resampling,
                            yarp::os::ConstString cam_sel, yarp::os::ConstString laterality, const int num_particles);

    /* Destructor */
    ~VisualSIRParticleFilter() noexcept override;

    /* Copy constructor */
    VisualSIRParticleFilter(const VisualSIRParticleFilter& vsir_pf) = delete;

    /* Move constructor */
    VisualSIRParticleFilter(VisualSIRParticleFilter&& vsir_pf) noexcept = delete;

    /* Copy assignment operator */
    VisualSIRParticleFilter& operator=(const VisualSIRParticleFilter& vsir_pf) = delete;

    /* Move assignment operator */
    VisualSIRParticleFilter& operator=(VisualSIRParticleFilter&& vsir_pf) noexcept = delete;

    void runFilter() override;

    void getResult() override;

protected:
    std::unique_ptr<bfl::Initialization>           initialization_;
    std::unique_ptr<bfl::ParticleFilterPrediction> prediction_;
    std::unique_ptr<bfl::VisualCorrection>         correction_;
    std::unique_ptr<bfl::Resampling>               resampling_;

    yarp::os::ConstString                          cam_sel_;
    yarp::os::ConstString                          laterality_;
    const int                                      num_particles_;

    cv::Ptr<cv::cuda::HOG>                         cuda_hog_;

    yarp::os::BufferedPort<yarp::sig::Vector>                       port_estimates_out_;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb>> port_image_in_;


    unsigned long int                              filtering_step_ = 0;
    bool                                           is_running_     = false;
    bool                                           use_mean_       = true;
    bool                                           use_mode_       = false;


    yarp::os::Port           port_rpc_command_;
    bool                     attach(yarp::os::Port &source);
    bool                     setCommandPort();

    bool                     use_analogs(const bool status) override;

    std::vector<std::string> get_info() override;

    bool                     set_estimates_extraction_method(const std::string& method) override;

    bool                     quit() override;

    /* EXPERIMENTAL */
    bool                     visual_correction(const bool status) override;
    bool                     do_visual_correction_ = true;
    /* ************ */


    Eigen::VectorXf mean(const Eigen::Ref<const Eigen::MatrixXf>& particles, const Eigen::Ref<const Eigen::VectorXf>& weights) const;

    Eigen::VectorXf mode(const Eigen::Ref<const Eigen::MatrixXf>& particles, const Eigen::Ref<const Eigen::VectorXf>& weights) const;

private:
    const int          block_size_        = 16;
    const int          img_width_         = 320;
    const int          img_height_        = 240;
    const int          bin_number_        = 9;
    const unsigned int descriptor_length_ = (img_width_/block_size_*2-1) * (img_height_/block_size_*2-1) * bin_number_ * 4;
};

#endif /* VISUALSIRPARTICLEFILTER_H */
