#include "levels/level01.hpp"

// Level01::Level01(Tyra::Engine* engine)
//      : Level("level01/level.obj", "level01/textures/", "level01/heightmap.png", Tyra::ObjLoaderOptions{}, 0.0F, 200.0F, Vec4(-454.7F, 0.0F, -326.2F, 1.0F), Vec4(392.8F, 0.0F, 326.8F, 1.0F), engine)
// {
//      Setup();
// }

Level01::Level01(Tyra::Engine* engine)
    : Level("level01/", "level01/level.obj", "level01/txtrs/", "level01/hmap.png", Tyra::ObjLoaderOptions{}, engine)
{
    Setup();
}

void Level01::Setup()
{
    StaticMeshComponent* trees = new StaticMeshComponent("level01/trees.obj", "level01/txtrs", Tyra::ObjLoaderOptions{});
    AddComponent(trees);

    StaticMeshComponent* road = new StaticMeshComponent("level01/road.obj", "level01/txtrs", Tyra::ObjLoaderOptions{});
    AddComponent(road);

    GetEngine()->renderer.setClearScreenColor(Tyra::Color(203.f, 239.f, 245.f));
    Car* car = new Car(engine);
    AddChild(car);

    std::stringstream ss;
    ss << "music/mus" << (rand() % 12) + 1 << ".wav";
    engine->audio.song.load(Helper::fromCwd(ss.str()));
    engine->audio.song.inLoop = true;
    engine->audio.song.setVolume(70);
    engine->audio.song.play();
}

void Level01::Update()
{
    
}

void Level01::Render()
{

}


TPE_Vec3 Level01::EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance)
{
    return TPE_envGround(position, 0);
    // return TPE_envHeightmap(position, TPE_vec3(0, 0, 0), TPE_F, height, maxDistance);
}