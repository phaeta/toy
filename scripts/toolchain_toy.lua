-- toy toolchain

TOY_DIR        = path.getabsolute("..")
MUD_DIR        = path.join(TOY_DIR, "mud")

TOY_SRC_DIR         = path.join(TOY_DIR, "src")
TOY_3RDPARTY_DIR    = path.join(TOY_DIR, "3rdparty")

dofile(path.join(MUD_DIR, "scripts/toolchain_mud.lua"))

function toy_binary(name)
    mud_binary(name)
    
    configuration { "not linux", "not asmjs" }
        defines {
            "TOY_RESOURCE_PATH=\"" .. path.join(TOY_DIR, "data") .. "/\"",
        }

    configuration { "linux", "not asmjs" }
        defines {
            "TOY_RESOURCE_PATH=\\\"" .. path.join(TOY_DIR, "data") .. "/\\\"",
        }

	configuration {}
end

configuration { "windows"}
    libdirs {
        "C:/Program Files (x86)/OpenAL/libs/Win32",
        "C:/Program Files/OpenAL/libs/Win32",
    }
    
    includedirs {
        "C:/Program Files (x86)/OpenAL/include",
        "C:/Program Files/OpenAL/include",
    }

configuration { "vs*-clang" }
    defines {
        "BT_NO_SIMD_OPERATOR_OVERLOADS"
    }
    
configuration {}