#pragma once

#include <visu/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <obj/Types.h>
#include <gfx/Types.h>
#include <util/Types.h>
#include <core/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> TOY_VISU_EXPORT Type& type<toy::PhysicDebugDraw>();
    export_ template <> TOY_VISU_EXPORT Type& type<toy::SoundSource>();
    export_ template <> TOY_VISU_EXPORT Type& type<toy::VisuScene>();
    export_ template <> TOY_VISU_EXPORT Type& type<toy::VisuSystem>();
    export_ template <> TOY_VISU_EXPORT Type& type<toy::VisuModule>();
    
	export_ template struct TOY_VISU_EXPORT Typed<std::vector<toy::PhysicDebugDraw*>>;
	export_ template struct TOY_VISU_EXPORT Typed<std::vector<toy::SoundSource*>>;
	export_ template struct TOY_VISU_EXPORT Typed<std::vector<toy::VisuScene*>>;
	export_ template struct TOY_VISU_EXPORT Typed<std::vector<toy::VisuSystem*>>;
	export_ template struct TOY_VISU_EXPORT Typed<std::vector<toy::VisuModule*>>;
}
