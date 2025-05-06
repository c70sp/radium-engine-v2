# TODO List

- More dynamic pipelines, so more than one vertex and one fragment shader can be linked
- TextureManager? MeshManager for loading 3D models and co?
- Camera stuff with proper keyboard and mouse support in the engine files, and then do the more broad, non-math shit in the game folder
  - Cameras would be entities as well?
  - Would have transformComponent and maybe cameraComponent for FOV and upVector / sideVector, etc.
  - System for the cameraCalculations and inputs (i.e. move to XYZ) for keys
  - Basically game dev retrieves pressed keys from engine, does a little math with them, creates a camera, calls cameraSystem for 
    controlling the camera

### Doing rn
- Hot-Reloading for shaders
  - modify unordered_map for shaders and pipelines to use strings and not ints as IDs, then remove strings from the structs, removes the bloat
  - reloadAll() and reloadShader()

### Finishes stuff

- ShaderManager
- Proper cleanUp and termination
- Hot-Reloading for everything but shaders