



float GetAttenuation(float constant, float linear, float quadratic, float distance)
{
    return 1.0 / (constant + distance * (linear + quadratic * distance));
}

float GetSepcularCoefficient(vec3 view_dir, vec3 half_vec, float shininess)
{
    return pow(max(dot(view_dir, half_vec), 0.0), shininess);
}