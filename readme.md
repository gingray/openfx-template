## Davinci Resolve plugin bootstrap (build support only Mac version later add Windows)
This repo created with intention to have a working template/example to start writing plugins for Davinci Resolve.  
Under the hood Davinci Resolve user OpenFX plugins mean this plugin can work on multiple other apps. 
I've find very few information about plugin development for OpenFX and especialy for Davinci Resolve and want to  
fill this gap.  
OpenFX standard [http://openeffects.org/](http://openeffects.org/).  
[Official Documentation](https://github.com/ofxa/openfx/tree/master/Documentation/sources)

My personal intention was try to make plugin which work on Davinci Resolve. 
This template at the moment only build plugin for MacOS platform in future want to add Windows as well.
To build it you `CMake` and `Git`
I use submodules to fetch required cpp files/headers to build OpenFX plugin
Commands that I need to run to build it

```shell
git submodule update -i -r
cmake --build PATH_WHERE_TO_PUT_BUILD --target install -- -j 6
```

extension will be in a root of project in folder `install` need to copy it to `/Library/OFX/Plugins` on Mac OS  
it's default path where Davinci Resolve looking for a plugins 

### External
[https://github.com/rodlie/openfx-text](https://github.com/rodlie/openfx-text) interesting repo to take a look into