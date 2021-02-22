#shader vertex
#version 330 core

layout(location = 0) in vec3 _position;
layout(location = 1) in vec4 _color;
layout(location = 2) in vec2 _texCoord;
layout(location = 3) in float _texIndex;

uniform mat4 u_ProjectionView;

out vec4 v_color;
out vec2 v_texCoord;
out float v_texIndex;

void main()
{
	v_color = _color;
	v_texCoord = _texCoord;
	v_texIndex = _texIndex;
	gl_Position = u_ProjectionView * vec4(_position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_texIndex;

uniform sampler2D u_textures[32];

void main()
{
	color = texture(u_textures[int(v_texIndex)], v_texCoord) * v_color;
	//color = v_color;
}