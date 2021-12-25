#include "tutorial/sandBox/sandBox.h"
#include "igl/edge_flaps.h"
#include "igl/collapse_edge.h"
#include "Eigen/dense"
#include <functional>



SandBox::SandBox()
{
	

}

void SandBox::Init(const std::string &config)
{
	std::string item_name;
	std::ifstream nameFileout;
	doubleVariable = 0;
	nameFileout.open(config);
	if (!nameFileout.is_open())
	{
		std::cout << "Can't open file "<<config << std::endl;
	}
	else
	{
		Eigen::Vector3d initial_pos(5, 0, 0);
		while (nameFileout >> item_name)
		{
			std::cout << "openning " << item_name << std::endl;

			//parents.push_back(-1);
			load_mesh_from_file(item_name);
			

			
			data().add_points(Eigen::RowVector3d(0, 0, 0), Eigen::RowVector3d(0, 0, 1));
			data().show_overlay = false; //TPDO: make the overlay always displat on startup
			data().show_overlay_depth = true;
			data().point_size = 2;
			data().line_width = 2;
			data().set_visible(false, 1);
			if (item_name.find("sphere.obj") != std::string::npos) {
				spherePosition = initial_pos;
				data().MyTranslate(initial_pos, true);
			}
		}
		nameFileout.close();
	}
	MyTranslate(Eigen::Vector3d(0, 0, -1), true);
	
	data().set_colors(Eigen::RowVector3d(0.9, 0.1, 0.1));

}

SandBox::~SandBox()
{

}

void SandBox::Animate()
{
	if (isActive)
	{
		
		
		
	}
}


