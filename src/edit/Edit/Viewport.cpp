//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <edit/Edit/Viewport.h>

#include <gfx-ui/Viewport.h>
#include <gfx-ui/Viewer.h>
#include <gfx/Item.h>

#include <core/Camera/Camera.h>
#include <core/View/Vision.h>
#include <core/Selector/Selector.h>
#include <core/World/World.h>
#include <core/Physic/PhysicWorld.h>

#include <uio/Edit/Section.h>
#include <visu/VisuScene.h>

#include <edit/Controller/RTSCameraController.h>

using namespace mud; namespace toy
{
	vec3 pick_terrain(Viewer& viewer, World& world, vec2 position)
	{
		Ray ray = viewer.m_camera.ray(position);
		return world.part<PhysicWorld>().ground_point(ray);
	}

	Viewer& scene_viewport(Widget& parent, VisuScene& scene, Camera& camera, Selection& selection)
	{
		Widget& board = ui::widget(parent, styles().sheet, &scene);
		Viewer& viewer = board.child_args<Viewer, Scene&>(scene.m_scene);
		if(viewer.once())
		{
			viewer.m_controller = make_unique<RTSCameraController>(viewer, camera);
		}

		update_camera(camera, viewer.m_camera);

		viewer.m_controller->process(viewer);
		viewport_picker(viewer, viewer, selection);
		return viewer;
	}
}