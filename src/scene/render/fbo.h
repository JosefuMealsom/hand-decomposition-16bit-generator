
namespace Render
{
  class Fbo
  {
  public:
    Fbo(unsigned int w, unsigned int h);
    void bind();
    void unbind();

  private:
    unsigned int m_framebuffer;
    unsigned int m_fboTex;
    unsigned int m_rbo;
  };
}
