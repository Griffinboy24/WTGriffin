


#if defined (rspl_Downsampler2Flt_CURRENT_CODEHEADER)
	#error Recursive inclusion of Downsampler2Flt code header.
#endif
#define	rspl_Downsampler2Flt_CURRENT_CODEHEADER

#if ! defined (rspl_Downsampler2Flt_CODEHEADER_INCLUDED)
#define	rspl_Downsampler2Flt_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include	<cassert>



namespace rspl
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*
==============================================================================
Name: process_sample
Description:
	Filter and downsample a pair of samples. Gain is implicitly boosted by a
	factor two to save one multiplication.
Input parameters:
	- path_0: The *second* sample
	- path_1: The *first* sample
Returns: Downsampled sample
Throws: Nothing
==============================================================================
*/

rspl_FORCEINLINE float	Downsampler2Flt::process_sample (float path_0, float path_1)
{
	float				tmp_0 = _x_arr [0];
	float				tmp_1 = _x_arr [1];
	_x_arr [0] = path_0;
	_x_arr [1] = path_1;

	path_0 = (path_0 - _y_arr [0]) * _coef_arr [0] + tmp_0;
	path_1 = (path_1 - _y_arr [1]) * _coef_arr [1] + tmp_1;
	tmp_0 = _y_arr [0];
	tmp_1 = _y_arr [1];
	_y_arr [0] = path_0;
	_y_arr [1] = path_1;

	path_0 = (path_0 - _y_arr [2]) * _coef_arr [2] + tmp_0;
	path_1 = (path_1 - _y_arr [3]) * _coef_arr [3] + tmp_1;
	tmp_0 = _y_arr [2];
	tmp_1 = _y_arr [3];
	_y_arr [2] = path_0;
	_y_arr [3] = path_1;

	path_0 = (path_0 - _y_arr [4]) * _coef_arr [4] + tmp_0;
	path_1 = (path_1 - _y_arr [5]) * _coef_arr [5] + tmp_1;
	tmp_0 = _y_arr [4];
	_y_arr [4] = path_0;
	_y_arr [5] = path_1;

	path_0 = (path_0 - _y_arr [6]) * _coef_arr [6] + tmp_0;
	_y_arr [6] = path_0;
	assert (NBR_COEFS == 7);

	return (path_0 + path_1);
}



}	// namespace rspl



#endif	// rspl_Downsampler2Flt_CODEHEADER_INCLUDED

#undef rspl_Downsampler2Flt_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
