

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <math/Generated/Forward.h>
#include <geom/Generated/Forward.h>
#include <util/Generated/Forward.h>

#if defined TOY_CORE_LIB
#define TOY_CORE_EXPORT MUD_EXPORT
#else
#define TOY_CORE_EXPORT MUD_IMPORT
#endif


    
    
    class btCollisionWorld;
    class btDynamicsWorld;
    class btDiscreteDynamicsWorld;
    class btBroadphaseInterface;
    class btConstraintSolver;
    class btCollisionShape;
    class btStridingMeshInterface;
    class btCollisionObject;
    class btRigidBody;
    class btPersistentManifold;
    class btCollisionConfiguration;
    class btCollisionDispatcher;

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace bgfx {

    
    
}

namespace mud {
namespace gfx {

    
    
}
}

namespace mud {

    
    
}

namespace mud {
namespace detail {

    
    
}
}

namespace bimg {

    
    
}

namespace toy {

    enum class Task : unsigned int;
    enum SamplePolyAreas : unsigned int;
    enum SamplePolyFlags : unsigned int;
    enum CollisionGroup : short;
    
    template <class T> class Array;
    
    class Observer;
    class GenStoreObserver;
    class GenStore;
    class HookObserver;
    class Entity;
    class Action;
    class TaskSection;
    class QueueSection;
    class MonoSection;
    class ParallelSection;
    class Origin;
    class World;
    class SubPhysicWorld;
    class PhysicWorld;
    class SubBulletWorld;
    class BulletWorld;
    struct ConvexVolume;
    class NavGeom;
    class rcTileMesh;
    class Navmesh;
    class Navblock;
    class NavmeshShape;
    class Core;
    class DefaultWorld;
    class EffectCallback;
    class Effect;
    class State;
    class Active;
    class Actor;
    class CollisionShape;
    class MotionSource;
    class MotionState;
    class ColliderImpl;
    class ColliderObject;
    class Collider;
    class Solid;
    class Area;
    class BulletShape;
    class DispatchBulletShape;
    class BulletCollider;
    class BulletSolid;
    class Movable;
    class Signal;
    class PhysicScope;
    class EmitterScope;
    class ReceptorScope;
    class EmitterSphere;
    class ReceptorSphere;
    class Emitter;
    class Receptor;
    class CameraObserver;
    class Camera;
    class OCamera;
    class Atoll;
    struct Contact;
    class Belt;
    class Disq;
    class EventHandler_;
    class Event;
    class EventSubscriber;
    class EventFilter;
    class EventTube;
    class EventTubeEnd;
    class EventRelay;
    class EventEmitter;
    class EventReceptor;
    class LightReflector;
    class LightSource;
    class OLight;
    class MotionStrategy;
    class Manoeuvrable;
    class GroundMotion;
    class Medium;
    class SoundMedium;
    class VisualMedium;
    class MotionStateObserver;
    struct rcChunkyTriMeshNode;
    struct rcChunkyTriMesh;
    class OWaypoint;
    class DetourPath;
    class Pathfinder;
    class ObstacleBody;
    class Obstacle;
    class PhysicMedium;
    class Physic;
    class SolidMedium;
    class User;
    class Player;
    class Behavior;
    class Reactive;
    class TargetDispatcher;
    class Selector;
    class Symbolic;
    class RecursiveStore;
    class View;
    class StoreView;
    class ReceptorView;
    class Vision;
    class PlayerVision;
    class OmniVision;
    class WorldClock;
    class BufferPage;
    class WorldMedium;
    class WorldPage;
}

namespace bx {

    
    
}
