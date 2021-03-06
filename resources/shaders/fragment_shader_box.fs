#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct SunLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_NUMBER_OF_LIGHTS 20

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

uniform int number_of_lights;
uniform vec3 viewPos;
uniform vec3 defaultColor;
uniform float alfa;
uniform PointLight pointLights[MAX_NUMBER_OF_LIGHTS];
uniform Material material;
uniform SunLight sunLight;

vec3 CalcSunLight(SunLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normals);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < number_of_lights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    result += CalcSunLight(sunLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0) * vec4(defaultColor, alfa);

    if((texture(material.diffuse, TexCoords)).a < 0.1)
        discard;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine ambinet, diffuse and specular
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSunLight(SunLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine ambient, diffuse and specular
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    return (ambient + diffuse + specular);

}