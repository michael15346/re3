const char *leedsDefault_vert_src =
"#ifdef ENVMAP\n"
"uniform mat4 u_texMatrix;\n"
"#endif\n"
"#ifdef SKIN\n"
"uniform mat4 u_boneMatrices[64];\n"
"#endif\n"

"VSIN(ATTRIB_POS)	vec3 in_pos;\n"

"VSOUT vec4 v_color;\n"
"VSOUT vec2 v_tex0;\n"
"#ifdef ENVMAP\n"
"VSOUT vec2 v_tex1;\n"
"#endif\n"
"VSOUT float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"#ifdef SKIN\n"
"	vec3 SkinVertex = vec3(0.0, 0.0, 0.0);\n"
"	vec3 SkinNormal = vec3(0.0, 0.0, 0.0);\n"
"	for(int i = 0; i < 4; i++){\n"
"		SkinVertex += (u_boneMatrices[int(in_indices[i])] * vec4(in_pos, 1.0)).xyz * in_weights[i];\n"
"		SkinNormal += (mat3(u_boneMatrices[int(in_indices[i])]) * in_normal) * in_weights[i];\n"
"	}\n"

"	vec4 Vertex = u_world * vec4(SkinVertex, 1.0);\n"
"	gl_Position = u_proj * u_view * Vertex;\n"
"	vec3 Normal = mat3(u_world) * SkinNormal;\n"
"#else\n"
"	vec4 Vertex = u_world * vec4(in_pos, 1.0);\n"
"	gl_Position = u_proj * u_view * Vertex;\n"
"	vec3 Normal = mat3(u_world) * in_normal;\n"
"#endif\n"

"	v_tex0 = in_tex0;\n"
"#ifdef ENVMAP\n"
"	v_tex1 = (u_texMatrix * vec4(Normal, 1.0)).xy;\n"
"#endif\n"

"	v_color = in_color;\n"
"	v_color.rgb += u_ambLight.rgb*surfAmbient;\n"
"	v_color.rgb += DoDynamicLight(Vertex.xyz, Normal)*surfDiffuse;\n"
"	// PS2 clamps before material color\n"
"	// PSP clamps after...maybe another constant for this?\n"
"	v_color = clamp(v_color, 0.0, 1.0);\n"
"	v_color *= u_matColor;\n"

"	v_fog = DoFog(gl_Position.w);\n"
"}\n"
;