#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

float near = 1.0f;
float far = 100.f;
float LinearizeDepth(float depth);
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{

    // ambient
   vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

   // diffuse 
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
   
   // specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * (spec * material.specular);  
       
   vec3 result = ambient + diffuse + specular;
   FragColor = vec4(result, 1.0);

   


} 

float LinearizeDepth(float depth){
    float z = depth * 2.0 - 1.0f;
    return (2.0 * near * far)/(far + near - z*(far-near));
}
//glFragCoord为glsl内建变量，其z值就是片段的深度值
