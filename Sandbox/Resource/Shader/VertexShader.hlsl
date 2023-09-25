struct VSout
{
	float4 position : SV_Position;
	float4 normal : NORMAL;
};

VSout main(float3 position : Position, float3 normal : Normal) 
{
	VSout output;
	output.normal = float4(normal, 1.0f);
	output.position = float4(position, 1.0f);
	return output;
}