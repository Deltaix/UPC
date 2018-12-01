#version 330 core

out vec4 FragColor;

void main() {
	if ((int(gl_FragCoord.y) % 30) <= 15) {
	    if (gl_FragCoord.y < 711/2 && gl_FragCoord.x < 711/2)
	    	FragColor = vec4(1, 1, 0, 1);
	    else if (gl_FragCoord.y < 711/2 && gl_FragCoord.x >= 711/2)
	    	FragColor = vec4(0, 1, 0, 1);
	    else if (gl_FragCoord.y >= 711/2 && gl_FragCoord.x < 711/2)
	    	FragColor = vec4(1, 0, 0, 0);
	    else
	    	FragColor = vec4(0, 0, 1, 1);
	}
	else
		FragColor = vec4(0.5, 0.7, 1.0, 1.0);
}

