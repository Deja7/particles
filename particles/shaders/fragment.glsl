#version 450 core

out vec4 FragColor;

void main(){
    FragColor = vec4(0.92, 0.09, 0.23, 0.3);

    //// Albo nada� kolor zale�ny od po�o�enia punktu (np. jako efekt)
    //vec2 uv = gl_PointCoord.xy; // wsp�rz�dne wewn�trz punktu (0..1)
    //float dist = distance(uv, vec2(0.5));
    //float alpha = smoothstep(0.5, 0.3, dist); // mi�kkie wygaszenie na kraw�dzi
    //FragColor = vec4(1.0, 0.8, 0.2, alpha);   // np. z�oto-��ta cz�steczka z przezroczysto�ci�
}
