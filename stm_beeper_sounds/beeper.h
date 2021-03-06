#ifndef __BEEPER_H
#define __BEEPER_H

typedef struct {
	uint16_t frequency;
	uint8_t  duration;
} Tone_TypeDef;

// 도미솔도
static const Tone_TypeDef C_E_G_C[] = {
    {1048, 10}, { 0, 10},
    {1318, 10}, { 0, 10},
    {1568, 10}, { 0, 10},
    {2093, 10}, { 0, 10},
    {   0,  0}
};

// 도솔미도
static const Tone_TypeDef C_G_E_C[] = {
		{2093, 10}, { 0, 10},
		{1568, 10}, { 0, 10},
		{1318, 10}, { 0, 10},
		{1048, 10}, { 0, 10},
		{   0,  0}
};

// 엉금 엉금 기어서가자
static const Tone_TypeDef randomTone1[] = {
	{ 860,  8}, { 0, 16},
	{ 860,  8}, { 0, 16},
	{1319,  8}, { 0, 16},
	{1319,  8}, { 0, 16},
	{1175,  8}, { 0,  4},
	{1175,  8}, { 0,  4},
	{1047,  8}, { 0,  4},
	{ 988,  8}, { 0,  4},
	{ 860, 10},

	{   0,  0}    // <-- tones end
};

// 빙크스의 술 일부분 - 원피스 브룩
static const Tone_TypeDef randomTone4[] = {
	{3136,  8}, {   0, 24},
	{2637,  8}, {   0,  8},
	{2349,  8}, {   0, 24},
	{2093,  8}, {   0,  8},
	{1760,  8}, {   0, 24},
	{1976,  8}, {   0,  8},
	{2093,  8}, {   0, 40},

	{3136,  8}, {   0, 24},
	{2637,  8}, {   0,  8},
	{2349,  8}, {   0, 24},
	{2093,  8}, {   0,  8},
	{1760,  8}, {   0, 24},
	{2093,  8}, {   0,  8},
	{1568,  8}, 
	{   0,  0}    // <-- tones end
};

// 슈퍼마리오 일부분
static const Tone_TypeDef randomTone5[] = {
	{2637, 8}, { 0,  8},
	{2637, 8}, { 0, 24},

	{2637, 8}, { 0, 24},

	{2093, 8}, { 0,  8},
	{2637, 8}, { 0, 24},

	{3136, 8}, { 0, 40},
	{1568, 8},
	{   0,  0}    // <-- tones end
};

// 어릴 때 리코더 합주했던거 애드리브 부분인데 곡 제목 기억 안남..
static const Tone_TypeDef randomTone6[] = {
	{1568, 8}, { 0,  8},
	{1480, 8}, { 0,  8},
	{1396, 8}, { 0,  8},
	{1319,16}, { 0, 32},

	{1319, 8}, { 0,  8},
	{1245, 8}, { 0,  8},
	{1175, 8}, { 0,  8},
	{1047,16}, { 0, 32},

	{1047, 8}, { 0,  8},
	{ 988, 8}, { 0,  8},
	{ 932, 8}, { 0,  8},
	{ 860, 8},
	{   0,  0}    // <-- tones end
};

// 무슨 노래인데 기억 안남
static const Tone_TypeDef randomTone7[] = {
	{1568,10}, { 0, 20},

	{1480, 6}, { 0,  4},
	{1568, 6}, { 0,  4},
	{1319,10}, { 0, 20},

	{1245, 6}, { 0,  4},
	{1319, 6}, { 0,  4},
	{1047,10}, { 0, 20},

	{ 988, 6}, { 0,  4},
	{1047, 6}, { 0,  4},
	{ 784,10}, { 0, 40},

	
	{1396,10}, { 0, 20},
	{1319, 6}, { 0,  4},
	{1396, 6}, { 0,  4},
	{1175,10}, { 0, 20},

	{1109, 6}, { 0,  4},
	{1175, 6}, { 0,  4},
	{ 988,10}, { 0, 20},

	{ 932, 6}, { 0,  4},
	{ 988, 6}, { 0,  4},
	{1568,10}, { 0, 40},

	{   0,  0}    // <-- tones end
};

// 무궁화 꽃이 피었습니다.
static const Tone_TypeDef randomTone9[] = {
	{1319, 15}, { 0, 15},
	{1760, 15}, { 0, 15},
	{1760, 15}, { 0, 45},
	{1760, 15}, { 0, 45},
	{1568, 15}, { 0, 45},
	{1760, 15}, { 0, 15},
	{1760, 15}, { 0, 15},
	{1319, 15}, { 0, 15},
	{1319, 15}, { 0, 15},
	{1568, 25}, 
	{   0,  0}    // <-- tones end
};


// 루돌프 사슴코는 ~ 썰매를 끌어주렴
static const Tone_TypeDef christmas[] = {
	
		{1568, 5}, {0, 15},
		{1760,10}, {0, 30},
		{1568, 5}, {0, 15},
		{1318,10}, {0, 30},
		{2093,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{ 0,40}, {0, 40},

		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568,10}, {0, 30},
		{2093,10}, {0, 30},
		{1975,10}, {0, 30},
		{ 0,60}, {0, 60},

		{1396, 5}, {0, 15},
		{1568,10}, {0, 30},
		{1396, 5}, {0, 15},
		{1174,10}, {0, 30},
		{1975,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{ 0,40}, {0, 40},

		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568,10}, {0, 30},
		{1760,10}, {0, 30},
		{1318,10}, {0, 30},
		{ 0,60}, {0, 60},

//

		{1568, 5}, {0, 15},
		{1760,10}, {0, 30},
		{1568, 5}, {0, 15},
		{1318,10}, {0, 30},
		{2093,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{ 0,40}, {0, 40},

		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568,10}, {0, 30},
		{2093,10}, {0, 30},
		{1975,10}, {0, 30},
		{ 0,60}, {0, 60},

		{1396, 5}, {0, 15},
		{1568,10}, {0, 30},
		{1396, 5}, {0, 15},
		{1174,10}, {0, 30},
		{1975,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{ 0,40}, {0, 40},

		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568, 5}, {0, 15},
		{1760, 5}, {0, 15},
		{1568,10}, {0, 30},
		{2349,10}, {0, 30},
		{2093,10}, {0, 30},
		{ 0,60}, {0, 60},

//

		{1760,10}, {0, 30},
		{1760,10}, {0, 30},
		{2093,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{1318, 5}, {0, 15},
		{1568,10}, {0, 30},
		{ 0,40}, {0, 20},

		{1396,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{1396,10}, {0, 30},
		{1318,20}, {0, 40},
		{ 0,40}, {0, 40},

		{1174,10}, {0, 30},
		{1318,10}, {0, 30},
		{1568,10}, {0, 30},
		{1760,10}, {0, 30},
		{1975,10}, {0, 30},
		{1975, 5}, {0, 30},
		{1975,10}, {0, 30},
		{ 0,40}, {0, 20},

		{2093,10}, {0, 30},
		{2093,10}, {0, 30},
		{1975,10}, {0, 30},
		{1760,10}, {0, 30},
		{1568,10}, {0, 30},
		{1396, 5}, {0, 15},
		{1174,10}, {0, 30},
		{ 0,40}, {0, 20},

		{   0,  0}    // <-- tones end
	
};

#endif // __BEEPER_H
