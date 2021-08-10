//
// Created by Ivan L on 8/9/21.
//
#include "ofxsImageEffect.h"
#include "const.h"

using namespace OFX;

class TestOFXPlugin : public ImageEffect {
public:
    TestOFXPlugin(OfxImageEffectHandle handle);
    virtual void render(const RenderArguments &args) override final;
    virtual void changedParam(const InstanceChangedArgs &args,
                              const std::string &paramName) override final;
    virtual bool getTimeDomain(OfxRangeD &range) override final;
private:
    Clip *_dstClip;
    IntParam *_fps;
    Clip *_srcClip;

};

mDeclarePluginFactory(TextOFXPluginFactory, {}, {});

static TextOFXPluginFactory p(kPluginIdentifier,
                              kPluginVersionMajor,
                              kPluginVersionMinor);
mRegisterPluginFactoryInstance(p)
