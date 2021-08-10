#include "plugin.h"
#include "common_ofx.h"
#include "ofxsCopier.h"
#include <iostream>

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
    std::auto_ptr<Image> dst(_dstClip->fetchImage(args.time));

    if (!dst.get()) {
        OFX::throwSuiteStatusException(kOfxStatFailed);
    }

    OFX::BitDepthEnum dstBitDepth       = dst->getPixelDepth();
    OFX::PixelComponentEnum dstComponents  = dst->getPixelComponents();
    if (dstBitDepth != eBitDepthUByte && dstComponents != ePixelComponentRGB) {
        OFX::throwSuiteStatusException(kOfxStatErrUnsupported);
    }

    std::auto_ptr<Image> src(_srcClip->fetchImage(args.time));

    if (src.get()) {
        OFX::BitDepthEnum    srcBitDepth      = src->getPixelDepth();
        OFX::PixelComponentEnum srcComponents = src->getPixelComponents();

        // see if they have the same depths and bytes and all
        if (srcBitDepth != dstBitDepth || srcComponents != dstComponents) {
            OFX::throwSuiteStatusException(kOfxStatErrImageFormat);
        }
    }
    auto procWindow = args.renderWindow;
    for(int y=procWindow.y1; y < procWindow.y2;y++) {
        for(int x=procWindow.x1; x < procWindow.x2;x++) {
            unsigned char * srcPix = (unsigned char *) src->getPixelAddress(x, y);
            unsigned char * dstPix = (unsigned char *) dst->getPixelAddress(x, y);
            dstPix[0] = 10;
            dstPix[1] = 20;
            dstPix[2] = 10;
        }
    }
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
    srcClip->addSupportedComponent(ePixelComponentRGB);

    // create the mandated output clip
    ClipDescriptor *dstClip = desc.defineClip(kOfxImageEffectOutputClipName);
    srcClip->addSupportedComponent(ePixelComponentRGB);
    dstClip->setSupportsTiles(false);
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