attribute highp vec4 a_Vertex;
attribute highp vec4 a_Color;
attribute highp vec3 a_Normal;
attribute highp vec2 a_TexCoord;

uniform bool u_LightingEnabled;
uniform bool u_ColorArrayEnabled;
uniform highp mat4 u_MvpMatrix;
uniform highp mat4 u_MvMatrix;
uniform highp mat3 u_NormalMatrix;
uniform highp vec3 u_LightDirection;
uniform highp vec3 u_HalfPlaneVector;
uniform highp vec4 u_AmbientAndDiffuseColor;
uniform highp float u_AmbientLightBrightness;
uniform int u_PointSize;

varying highp vec2 v_TexCoord;
varying highp vec4 v_AmbientAndDiffuseColor;
varying highp float v_AmbientLightBrightness;
varying highp float v_DiffuseBrightness;

const highp float c_one = 1.0;
const highp float c_Zero = 0.0;


void main(void)
{
    gl_Position = u_MvpMatrix * a_Vertex;
    v_TexCoord = a_TexCoord;
    if(u_ColorArrayEnabled)
       v_AmbientAndDiffuseColor = a_Color;
    else v_AmbientAndDiffuseColor = u_AmbientAndDiffuseColor;
    v_AmbientLightBrightness = u_AmbientLightBrightness;
    v_DiffuseBrightness = c_one;
}
