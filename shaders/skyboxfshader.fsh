//precision highp float;
uniform mediump vec4 color;
varying highp vec4 v_AmbientAndDiffuseColor;
varying highp float v_AmbientLightBrightness;
varying highp float v_DiffuseBrightness;
varying highp vec2 v_TexCoord;
uniform highp vec2 u_viewPortCenter;
uniform highp float u_diameterSquare;

uniform bool u_TextureEnabled;
uniform sampler2D s_Texture;

//highp vec2 centerVec;


void main(void)
{
//    centerVec =  gl_FragCoord.xy - u_viewPortCenter;
//    if(dot(centerVec, centerVec) > u_diameterSquare)
//        discard;

    if(u_TextureEnabled)
    {
      gl_FragColor = texture2D(s_Texture, v_TexCoord) * (v_AmbientLightBrightness + v_DiffuseBrightness);
      gl_FragColor[3] = texture2D(s_Texture, v_TexCoord)[3]; //Do not modulate Alpha!
    }
    else
    {
      gl_FragColor = v_AmbientAndDiffuseColor * (v_AmbientLightBrightness + v_DiffuseBrightness);
      gl_FragColor[3] = v_AmbientAndDiffuseColor[3]; //Do not modulate Alpha!
    }

}
