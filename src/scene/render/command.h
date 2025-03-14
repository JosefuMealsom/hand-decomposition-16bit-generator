#include "scene/render/api/renderer_api.h"

namespace Render {

class Command {
private:
  static RendererAPI *s_renderer_api;

public:
  static RendererAPI *get_render_api() { return s_renderer_api; }
};

} // namespace Render
