cbuffer ConstBuffer
{
	float dtime;				
};

struct FireworkFragment
{
	float4 pos : SV_POSITION;
	float life : LIFE;
	float3 velocity : VELOCITY;
	float cluster : CLUSTER;
};

[maxvertexcount(3)]
void main(
	point FireworkFragment input[1],
	inout TriangleStream< FireworkFragment > output
)
{
	float3 g = float3(0.0f, -10.0f, 0.0f);
	FireworkFragment fragment;

	fragment.life = input[0].life - 1.0f;
	fragment.pos = input[0].pos + input[0].velocity * dtime;
	fragment.velocity = input[0].velocity + g * dtime;
	fragment.cluster = input[0].cluster;

	if (fragment.life > 0.0f)
	{
		output.Append(frame);
	}
	else
	{
		fragment.cluster -= 1.0f;
		if (fragment.cluster > 0)
		{
			float3 vDir [] = {	float3(1.0f, 1.0f, 1.0f),
								float3(-1.0f, -1.0f, 1.0f), 
								float3(-1.0f, 1.0f, 1.0f), 
								float3(1.0f, -1.0f, 1.0f)}

			for (uint i = 0; i < 4; i++)
			{
				FireworkFragment element;

				element.pos = fragment.pos;
				element.velocity = fragment.velocity * vDir[i];
				element.cluster = fragment.cluster;
				element.life = 10.0f;
				
				output.Append(element);
			}
		}
	}

}