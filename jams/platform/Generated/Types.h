#pragma once

#include <platform/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <util/Generated/Types.h>
#include <core/Generated/Types.h>
#include <db/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <uio/Generated/Types.h>
#include <gfx/Generated/Types.h>
#include <visu/Generated/Types.h>
#include <edit/Generated/Types.h>
#include <block/Generated/Types.h>
#include <gen/Generated/Types.h>
#include <shell/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    
    template <> _EX_PLATFORM_EXPORT Prototype& proto<Worldblock>();
    template <> _EX_PLATFORM_EXPORT Type& type<Worldblock>();
    template <> _EX_PLATFORM_EXPORT Prototype& proto<TileWorld>();
    template <> _EX_PLATFORM_EXPORT Type& type<TileWorld>();
    template <> _EX_PLATFORM_EXPORT Prototype& proto<Human2>();
    template <> _EX_PLATFORM_EXPORT Type& type<Human2>();
}