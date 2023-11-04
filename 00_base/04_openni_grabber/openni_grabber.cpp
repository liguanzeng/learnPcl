#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class SimpleOpenNIViewer
{
    public:
        SimpleOpenNIViewer (): viewer("PCL OpenNI Viewer!"){}

}