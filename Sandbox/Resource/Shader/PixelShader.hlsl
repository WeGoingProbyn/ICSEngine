struct PSin 
{
	float4 position : SV_Position;
	float4 normal : NORMAL;
};

float4 main(PSin input) : SV_Target 
{
    float4 colour = normalize(input.normal + 1);
	return colour;
}