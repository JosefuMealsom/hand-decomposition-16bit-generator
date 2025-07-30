# UV image reconstructor

Semi successful attempt to render 16-bit UV values of a mesh to a 16bit image file, as well
as the mesh itself.

### Why

Needed to find a way of creating a 2D hand silhouette that animators could animate into, which
could then be applied as a texture to the mesh.
The normal UV unwrapping process in Blender intelligently unwraps the mesh onto a 2D texture to
maximise the usage on that image file. Unfortunately, this makes it hard for an animator to animate
into as now all the vertices/faces are distributed amongst this image file.
I thought by rendering the hand image in the viewport with both the UVs applied and the silhouette,
I could create a mapping between a silhouette that the animator could animate into, and the vertices
that had been unwrapped on the UV texture.

### Results

It technically worked, but there were seams in between the each island of the mesh that had been split.
I tried using MSAA to fix this, but it didn't help.

### Actual solution

Later discovered you could project vertices onto a UV map from the current viewport in Blender, which 
worked a lot better, was simpler and solved the seam issue.
