#ifndef LVR_PIPELINE_HPP_
#define LVR_PIPELINE_HPP_

#include <reconstruction/FastReconstruction.hpp>
#include <reconstruction/TSDFGrid.hpp>
#include <reconstruction/PointsetSurface.hpp>
#include <reconstruction/FastBox.hpp>
#include <io/PointBuffer.hpp>
#include <io/DataStruct.hpp>
#include <io/Timestamp.hpp>
#include <geometry/HalfEdgeVertex.hpp>
#include <geometry/HalfEdgeMesh.hpp>
#include <geometry/BoundingBox.hpp>
#include <kfusion/types.hpp>
#include <kfusion/cuda/tsdf_volume.hpp>
#include <kfusion/cuda/projective_icp.hpp>
#include <kfusion/LinearPipeline.hpp>
#include <kfusion/GridStage.hpp>
#include <kfusion/MeshStage.hpp>
#include <kfusion/OptimizeStage.hpp>
#include <kfusion/FusionStage.hpp>


using namespace lvr;

typedef ColorVertex<float, unsigned char> cVertex;
typedef HalfEdgeMesh<cVertex, lvr::Normal<float> > HMesh;
typedef HMesh* MeshPtr;

namespace kfusion
{
    class LVRPipeline
    {
		public:

			LVRPipeline(double camera_target_distance, double voxel_size = 3.0/512.0, bool optimize = false, string mesh_name = "mesh_output.ply");
			
			~LVRPipeline();
        
			void addTSDFSlice(TSDFSlice slice,  const bool last_shift);
			
			void resetMesh();
			
			MeshPtr getMesh() {return pl_.GetResult();}
			
			double calcTimeStats();
			
			void setCameraDist(const double threshold) { camera_target_distance_ = threshold;} 
			
		private:
		    
		    MeshPtr meshPtr_;
		    size_t slice_count_;
			std::vector<double> timeStats_;
			double camera_target_distance_;
			LinearPipeline<pair<TSDFSlice, bool> , MeshPtr> pl_;
			
    };
}
#endif
