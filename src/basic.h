//
// Created by Ivan L on 8/9/21.
//
#include "ofxsImageEffect.h"

#define kPluginIdentifier "TestOpenFX"
#define kPluginVersionMajor 1 // Incrementing this number means that you have broken backwards compatibility of the plug-in.
#define kPluginVersionMinor 0 // Increment this when you have fixed a bug or made it faster.
#define kPluginDescription "Basic plugin demonstration"
#define kPluginName "Test OFX"


using namespace OFX;

class TestOFXPlugin : public ImageEffect {
public:
    TestOFXPlugin(OfxImageEffectHandle handle);
    virtual void render(const RenderArguments &args) override final;
    virtual void changedParam(const InstanceChangedArgs &args,
                              const std::string &paramName) override final;
    virtual bool getRegionOfDefinition(const RegionOfDefinitionArguments &args, OfxRectD &rod) override final;
    virtual bool getTimeDomain(OfxRangeD &range) override final;
private:
};

mDeclarePluginFactory(TextOFXPluginFactory, {}, {});

static TextOFXPluginFactory p(kPluginIdentifier,
                              kPluginVersionMajor,
                              kPluginVersionMinor);
mRegisterPluginFactoryInstance(p)
