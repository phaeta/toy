//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/NonCopy.h>
#include <obj/Unique.h>
#include <core/Forward.h>
#include <geom/Primitive.h>

#ifndef MUD_CPP_20
#include <string>
#endif

class rcContext;

using namespace mud; namespace toy
{
	using string = std::string;

	static const int MAX_CONVEXVOL_PTS = 12;
	struct ConvexVolume
	{
		float verts[MAX_CONVEXVOL_PTS*3];
		float hmin, hmax;
		int nverts;
		int area;
	};

	class TOY_CORE_EXPORT NavGeom : public NonCopy
	{
	public:
		NavGeom(Geometry& geom, cstring name);
		~NavGeom();

		Geometry& m_geometry;
		string m_name;
		unique_ptr<rcChunkyTriMesh> m_chunkyMesh;

		bool build();

	public:
		bool raycastMesh(const vec3& src, const vec3& dst, float& tmin);

		// Off-Mesh connections.
		void addOffMeshConnection(const float* spos, const float* epos, const float rad, unsigned char bidir, unsigned char area, unsigned short flags);
		void deleteOffMeshConnection(int i);

		// Box Volumes.
		int getConvexVolumeCount() const { return m_volumeCount; }
		const ConvexVolume* getConvexVolumes() const { return m_volumes; }
		void addConvexVolume(const float* verts, const int nverts, const float minh, const float maxh, unsigned char area);
		void deleteConvexVolume(int i);

	protected:
		unique_ptr<rcContext> m_ctx;

	public:
		// Off-Mesh connections.
		static const int MAX_OFFMESH_CONNECTIONS = 256;

		float m_offMeshConVerts[MAX_OFFMESH_CONNECTIONS*3*2];
		float m_offMeshConRads[MAX_OFFMESH_CONNECTIONS];
		unsigned char m_offMeshConDirs[MAX_OFFMESH_CONNECTIONS];
		unsigned char m_offMeshConAreas[MAX_OFFMESH_CONNECTIONS];
		unsigned short m_offMeshConFlags[MAX_OFFMESH_CONNECTIONS];
		unsigned int m_offMeshConId[MAX_OFFMESH_CONNECTIONS];
		int m_offMeshConCount = 0;

		// Convex Volumes.
		static const int MAX_VOLUMES = 256;

		ConvexVolume m_volumes[MAX_VOLUMES];
		int m_volumeCount = 0;
	};
}
