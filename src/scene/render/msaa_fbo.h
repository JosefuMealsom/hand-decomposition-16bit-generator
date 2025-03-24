
namespace Render
{
  class MSAAFbo
  {
  public:
    MSAAFbo(unsigned int w, unsigned int h);
    void bind();
    void unbind();

    unsigned int m_framebuffer;

  private:
    unsigned int m_fboTex;
    unsigned int m_rbo;
  };
}
