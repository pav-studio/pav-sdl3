#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform float uTime;

float random(vec2 st)
{
    return fract(
        sin(dot(st.xy,
        vec2(12.9898,78.233)))
        * 43758.5453123
    );
}

float noise(vec2 st)
{
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u =
        f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x)
         + (c - a) * u.y * (1.0 - u.x)
         + (d - b) * u.x * u.y;
}

float fbm(vec2 st)
{
    float value = 0.0;
    float amplitude = 0.5;

    for(int i = 0; i < 6; i++)
    {
        value +=
            amplitude
            * noise(st);

        st *= 2.0;

        amplitude *= 0.5;
    }

    return value;
}

void main()
{
    vec2 uv = TexCoord;

    vec2 p =
        (uv - 0.5) * 3.0;

    float t =
        uTime * 0.03;

    // ======================
    // SPACE BACKGROUND
    // ======================

    vec3 color =
        vec3(0.01, 0.01, 0.03);

    // ======================
    // NEBULA LAYERS
    // ======================

    float n1 =
        fbm(
            p
            + vec2(t, 0.0)
        );

    float n2 =
        fbm(
            p * 1.8
            - vec2(0.0, t)
        );

    float n3 =
        fbm(
            p * 3.0
            + vec2(t * 0.5)
        );

    float nebula =
        n1 * 0.6
        + n2 * 0.3
        + n3 * 0.1;

    nebula =
        smoothstep(
            0.35,
            0.8,
            nebula
        );

    vec3 nebulaColorA =
        vec3(0.1, 0.4, 1.0);

    vec3 nebulaColorB =
        vec3(1.0, 0.2, 0.8);

    vec3 nebulaColorC =
        vec3(0.3, 0.9, 1.0);

    vec3 nebulaColor =
        mix(
            nebulaColorA,
            nebulaColorB,
            n1
        );

    nebulaColor =
        mix(
            nebulaColor,
            nebulaColorC,
            n2
        );

    color +=
        nebulaColor
        * nebula
        * 1.8;

    // ======================
    // BRIGHT GAS POCKETS
    // ======================

    float glow =
        pow(nebula, 3.0);

    color +=
        glow
        * vec3(0.6, 0.8, 1.0);

    // ======================
    // STARS
    // ======================

    vec2 starUV =
        floor(uv * 1200.0);

    float star =
        step(
            0.9985,
            random(starUV)
        );

    float twinkle =
        0.6 + 0.4 *
        sin(
            uTime * 4.0
            + random(starUV) * 20.0
        );

    vec3 starColor =
        mix(
            vec3(1.0),
            vec3(0.5, 0.7, 1.0),
            random(starUV + 3.14)
        );

    color +=
        star
        * starColor
        * twinkle
        * 2.0;

    // ======================
    // GIANT SUN
    // ======================

    vec2 sunPos =
        vec2(0.82, 0.18);

    float sunDist =
        distance(uv, sunPos);

    float sun =
        0.02 / sunDist;

    vec3 sunColor =
        vec3(1.0, 0.7, 0.2);

    color +=
        sunColor
        * sun;

    // ======================
    // PLANET
    // ======================

    vec2 planetPos =
        vec2(0.28, 0.72);

    float planetDist =
        distance(uv, planetPos);

    float planet =
        smoothstep(
            0.16,
            0.15,
            planetDist
        );

    vec3 planetColor =
        vec3(0.05, 0.2, 0.6);

    color =
        mix(
            color,
            planetColor,
            planet
        );

    // atmosphere

    float atmosphere =
        smoothstep(
            0.23,
            0.15,
            planetDist
        );

    color +=
        vec3(0.1, 0.6, 1.0)
        * atmosphere
        * 0.3;

    // ======================
    // FINAL
    // ======================

    color =
        pow(color, vec3(0.9));

    color =
        clamp(color, 0.0, 1.0);

    FragColor =
        vec4(color, 1.0);
}