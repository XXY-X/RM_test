#ifndef _FILTER_H
#define _FILTER_H
/*
无限冲激响应滤波
一阶低通滤波
*/
void iir(float *raw_data, float new_data, float filter_value);
void rc_filter(float *raw_data, float new_data, float delta_t, float LPF_RC);

#endif // !_FILTER_H
