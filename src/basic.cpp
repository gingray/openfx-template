#include "basic.h"
static std::string ofxHostName;

TestOFXPlugin::TestOFXPlugin(OfxImageEffectHandle handle) : ImageEffect(handle) { }
void TestOFXPlugin::render(const RenderArguments &args) { }
void TestOFXPlugin::changedParam(const InstanceChangedArgs &args, const std::string &paramName) { }
bool TestOFXPlugin::getRegionOfDefinition(const RegionOfDefinitionArguments &args, OfxRectD &rod) {
    return true;
}

bool TestOFXPlugin::getTimeDomain(OfxRangeD &range)
{
    return true;
}

void TextOFXPluginFactory::describe(ImageEffectDescriptor &desc)
{
    ofxHostName = getImageEffectHostDescription()->hostName;

    desc.setLabel(kPluginName);
    desc.setPluginDescription(kPluginDescription);
    desc.addSupportedContext(eContextGeneral);
    desc.addSupportedContext(eContextGenerator);
    desc.addSupportedBitDepth(eBitDepthUByte);
    desc.addSupportedBitDepth(eBitDepthFloat);
    desc.setSupportsTiles(0);
    desc.setSupportsMultiResolution(0);
    desc.setRenderThreadSafety(eRenderFullySafe);

}
void TextOFXPluginFactory::describeInContext(ImageEffectDescriptor &desc,
                                             ContextEnum context)
                                             {
                                             }


ImageEffect *TextOFXPluginFactory::createInstance(OfxImageEffectHandle handle,
                                                  ContextEnum /* context */) {
    return new TestOFXPlugin(handle);
}