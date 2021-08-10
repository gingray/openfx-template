#include "plugin.h"
#include "common_ofx.h"
#include "ofxsCopier.h"

static std::string ofxHostName;
static std::string ofxPath;


TestOFXPlugin::TestOFXPlugin(OfxImageEffectHandle handle) : ImageEffect(handle), _dstClip(nullptr), _fps(nullptr)
, _srcClip(nullptr)
 {
    _dstClip = fetchClip(kOfxImageEffectOutputClipName);
    _srcClip = getContext() == eContextGenerator ? nullptr : fetchClip(kOfxImageEffectSimpleSourceClipName);
    _fps = fetchIntParam(kParamFrameSpeed);
    assert(_dstClip && _fps);
}

void TestOFXPlugin::render(const RenderArguments &args) {
    if (!_dstClip) {
        throwSuiteStatusException(kOfxStatFailed);
        return;
    }
    const double time = args.time;
    double srcTime = time;


    auto_ptr<Image> dst( _dstClip->fetchImage(args.time) );
    if ( !dst.get() ) {
        throwSuiteStatusException(kOfxStatFailed);
    }
    checkBadRenderScaleOrField(dst, args);

    auto_ptr<const Image> src( (_srcClip && _srcClip->isConnected() ) ? _srcClip->fetchImage(srcTime) : 0 );
    if ( src.get() ) {
        checkBadRenderScaleOrField(src, args);
        BitDepthEnum dstBitDepth       = dst->getPixelDepth();
        PixelComponentEnum dstComponents  = dst->getPixelComponents();
        BitDepthEnum srcBitDepth      = src->getPixelDepth();
        PixelComponentEnum srcComponents = src->getPixelComponents();
        if ( (srcBitDepth != dstBitDepth) || (srcComponents != dstComponents) ) {
            throwSuiteStatusException(kOfxStatErrImageFormat);
        }
    }


    copyPixels( *this, args.renderWindow, args.renderScale, src.get(), dst.get() );
}

void TestOFXPlugin::changedParam(const InstanceChangedArgs &args, const std::string &paramName) {}

bool TestOFXPlugin::getTimeDomain(OfxRangeD &range) {
    return true;
}

void TextOFXPluginFactory::describe(ImageEffectDescriptor &desc) {
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
                                             ContextEnum context) {
    ofxPath = desc.getPropertySet().propGetString(kOfxPluginPropFilePath, false);
    ofxHostName = getImageEffectHostDescription()->hostName;

    // there has to be an input clip, even for generators
    ClipDescriptor *srcClip = desc.defineClip(kOfxImageEffectSimpleSourceClipName);
    srcClip->setOptional(true);

    // create the mandated output clip
    ClipDescriptor *dstClip = desc.defineClip(kOfxImageEffectOutputClipName);
    dstClip->addSupportedComponent(ePixelComponentRGBA);
    dstClip->setSupportsTiles(0);
    PageParamDescriptor *page = desc.definePageParam("Controls");
    {
        IntParamDescriptor *param = desc.defineIntParam(kParamFrameSpeed);
        param->setLabel(kParamFrameSpeedLabel);
        param->setHint(kParamFrameSpeedHint);
        param->setRange(1, 500);
        param->setDisplayRange(1, 500);
        param->setDefault(kParamFrameSpeedDefault);
        param->setAnimates(true);
        if (page) { page->addChild(*param); }
    }

}


ImageEffect *TextOFXPluginFactory::createInstance(OfxImageEffectHandle handle,
                                                  ContextEnum /* context */) {
    return new TestOFXPlugin(handle);
}