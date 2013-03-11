#version 420


layout(std140) uniform ub_intA20_std140 {
	int intA20_std140[20];
};

layout(packed) uniform ub_intA20_packed {
	int intA20_packed[20];
};

layout(std140) uniform ub_str_intA20_std140 {
	struct {
		int int_arrays_std140[20];
	} s;
};

layout(std140) uniform ub_20int_std140 {
	int m1;
	int m2;
	int m3;
	int m4;
	int m5;
	int m6;
	int m7;
	int m8;
	int m9;
	int m10;
	int m11;
	int m12;
	int m13;
	int m14;
	int m15;
	int m16;
	int m17;
	int m18;
	int m19;
	int m20;
};

layout(std140) uniform ub_strA10_3int_std140 {
	struct {
		int a;
		int b;
		int c;
	} strA10_3int[10];
};

uniform int intA20_global[20];

out vec4 vtColor;

void main(void) {
	int i;
	int sum_std140 = 0;
	int sum_packed = 0;
	for(i = 0 ;i < 10 ; i++ ) {
		sum_std140 += intA20_std140[i];
		sum_std140 += s.int_arrays_std140[i];
		sum_packed += intA20_packed[i];
		sum_packed += intA20_global[i];
	}
	
	vtColor.r = sum_std140 * 10;
	vtColor.g = sum_packed * 10;
}