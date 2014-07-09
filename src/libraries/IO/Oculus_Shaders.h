// Oculus_Shaders.h

// From OculusSDK-0.2.2
static const char* PostProcessVertexShaderSrc = SHADERS_PATH "/Oculus_Shaders/PostProcessVert.vert";

// simple screen filling triangle vertex shader
//static const char* PostProcessVertexShaderSrc = SHADERS_PATH "/Oculus_Shaders/screenFill.vert";

// From OculusSDK-0.2.2
static const char* PostProcessFragShaderSrc = SHADERS_PATH "/Oculus_Shaders/PostProcessFrag.frag";

// Shader with lens distortion and chromatic aberration correction.
// From OculusSDK-0.2.2
static const char* PostProcessFullFragShaderSrc =
    "uniform vec2 LensCenter;\n"
    "uniform vec2 ScreenCenter;\n"
    "uniform vec2 Scale;\n"
    "uniform vec2 ScaleIn;\n"
    "uniform vec4 HmdWarpParam;\n"
    "uniform vec4 ChromAbParam;\n"
    "uniform sampler2D Texture0;\n"
    "varying vec2 oTexCoord;\n"
    "\n"
    // Scales input texture coordinates for distortion.
    // ScaleIn maps texture coordinates to Scales to ([-1, 1]), although top/bottom will be
    // larger due to aspect ratio.
    "void main()\n"
    "{\n"
    "   vec2  theta = (oTexCoord - LensCenter) * ScaleIn;\n" // Scales to [-1, 1]
    "   float rSq= theta.x * theta.x + theta.y * theta.y;\n"
    "   vec2  theta1 = theta * (HmdWarpParam.x + HmdWarpParam.y * rSq + "
    "                  HmdWarpParam.z * rSq * rSq + HmdWarpParam.w * rSq * rSq * rSq);\n"
    "   \n"
    "   // Detect whether blue texture coordinates are out of range since these will scaled out the furthest.\n"
    "   vec2 thetaBlue = theta1 * (ChromAbParam.z + ChromAbParam.w * rSq);\n"
    "   vec2 tcBlue = LensCenter + Scale * thetaBlue;\n"
    "   if (!all(equal(clamp(tcBlue, ScreenCenter-vec2(0.25,0.5), ScreenCenter+vec2(0.25,0.5)), tcBlue)))\n"
    "   {\n"
    "       gl_FragColor = vec4(0);\n"
    "       return;\n"
    "   }\n"
    "   \n"
    "   // Now do blue texture lookup.\n"
    "   float blue = texture2D(Texture0, tcBlue).b;\n"
    "   \n"
    "   // Do green lookup (no scaling).\n"
    "   vec2  tcGreen = LensCenter + Scale * theta1;\n"
    "   vec4  center = texture2D(Texture0, tcGreen);\n"
    "   \n"
    "   // Do red scale and lookup.\n"
    "   vec2  thetaRed = theta1 * (ChromAbParam.x + ChromAbParam.y * rSq);\n"
    "   vec2  tcRed = LensCenter + Scale * thetaRed;\n"
    "   float red = texture2D(Texture0, tcRed).r;\n"
    "   \n"
    "   gl_FragColor = vec4(red, center.g, blue, 1);\n"
    "}\n";

// static const char* PresentFboVertSrc = SHADERS_PATH "/Oculus_Shaders/PresentFboVert.vert";

// static const char* PresentFboFragSrc = SHADERS_PATH "/Oculus_Shaders/PresentFboFrag.frag";

 static const char* PresentFboVertSrc = SHADERS_PATH "/Oculus_Shaders/screenFill.vert";

 static const char* PresentFboFragSrc = SHADERS_PATH "/Oculus_Shaders/simpleTexture.frag";
