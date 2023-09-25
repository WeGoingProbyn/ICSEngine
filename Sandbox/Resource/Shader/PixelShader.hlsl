struct PSin 
{
	float4 position : SV_Position;
	float4 normal : NORMAL;
};

float4 main(PSin input) : SV_Target 
{
	float4 colour = float4(1.0f, 1.0f, 1.0f, 1.0f);
	return colour;
}