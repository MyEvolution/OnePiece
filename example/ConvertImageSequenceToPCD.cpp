#include "Geometry/Geometry.h"
#include "Geometry/PointCloud.h"
#include "Tool/IO.h"
using namespace one_piece;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "usage::MCGenerateMesh [dataset_path]" << std::endl;
        return 0;
    }
    //integration::InitializeVoxelCube();
    camera::PinholeCamera camera;
    std::vector<std::string> rgb_files, depth_files;
    tool::ReadImageSequence(argv[1],rgb_files, depth_files);
    for(size_t i = 0; i < rgb_files.size(); ++i)
    {
        if(i%1 == 0)
        {
            cv::Mat rgb = cv::imread(rgb_files[i]);
            cv::Mat depth = cv::imread(depth_files[i],-1);

            std::cout <<"Processing on "<<i <<"th image"<<std::endl;
            geometry::PointCloud pcd;
            pcd.LoadFromRGBD(rgb,depth,camera);
            pcd.WriteToPLY("./pcd/"+std::to_string(i)+".ply");
            //break;
        }   
    }
    return 0;
}