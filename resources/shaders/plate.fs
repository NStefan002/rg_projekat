#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture_sampler;

uniform Material material;
uniform DirLight dirLight;

uniform vec3 viewPos;
uniform bool blinn;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    float spec = 0.0;
    if (blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    };

    vec3 ambient =
        light.ambient * vec3(texture(texture_sampler, TexCoords).rgb) * texture(texture_sampler, TexCoords).a;
    vec3 diffuse =
        light.diffuse * diff * vec3(texture(texture_sampler, TexCoords).rgb) * texture(texture_sampler, TexCoords).a;
    vec3 specular =
        light.specular * spec * vec3(texture(texture_sampler, TexCoords).rgb) * texture(texture_sampler, TexCoords).a;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    FragColor = vec4(result, texture(texture_sampler, TexCoords).a);
}
