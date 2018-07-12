//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <core/Path/Pathfinder.h>

#include <core/Entity/Entity.h>
#include <core/World/World.h>
#include <core/WorldPage/WorldPage.h>
#include <core/Path/DetourPath.h>
#include <core/Navmesh/Navmesh.h>

#include <DetourNavMeshQuery.h>

#include <core/Core.h>


using namespace mud; namespace toy
{
	Pathfinder::Pathfinder(Navmesh& navmesh)
		: m_navmesh(*navmesh.m_navmesh)
		, m_query(make_unique<dtNavMeshQuery>())
		, m_filter(make_unique<dtQueryFilter>())
	{
		m_filter->setIncludeFlags(0xFFFF);
		m_filter->setExcludeFlags(0);
		m_filter->setAreaCost(0, 1.0f);
		m_query->init(&m_navmesh, 65535);
	}

	Pathfinder::~Pathfinder()
	{}

	void Pathfinder::nearestValid(vec3& destination, float margin)
	{
		//m_world_page.ground_point(destination, true, destination);

		float extents[3] = { 0.f, margin, 0.f };
		dtPolyRef polyLref;
		m_query->findNearestPoly(&destination[0], extents, m_filter.get(), &polyLref, &destination[0]);
		//printf("navdestination : " << destination[0] << " , " << destination[1] << " , " << destination[2] << std::endl;

		//m_world_page.ground_point(destination, true, destination);

		//printf("destination : " << destination[0] << " , " << destination[1] << " , " << destination[2] << std::endl;
	}

	bool Pathfinder::validity(const vec3& pos)
	{
		float extents[3] = { 0.f, 2.f, 0.f };
		float result[3];
		dtPolyRef poly;
		m_query->findNearestPoly(&pos[0], extents, m_filter.get(), &poly, &result[0]);

		return (poly != 0);
	}

}
