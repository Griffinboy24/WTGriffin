
#if defined (rspl_MipMapFlt_CURRENT_CODEHEADER)
	#error Recursive inclusion of MipMapFlt code header.
#endif
#define	rspl_MipMapFlt_CURRENT_CODEHEADER

#if ! defined (rspl_MipMapFlt_CODEHEADER_INCLUDED)
#define	rspl_MipMapFlt_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include	<cassert>



namespace rspl
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



long	MipMapFlt::get_sample_len () const
{
	assert (is_ready ());

	return (_len);
}



const int	MipMapFlt::get_nbr_tables () const
{
	assert (is_ready ());

	return (_nbr_tables);
}



long	MipMapFlt::get_lev_len (int level) const
{
	assert (_len >= 0);
	assert (level >= 0);
	assert (level < _nbr_tables);

	const long		scale = 1L << level;
	const long		lev_len = (_len + scale - 1) >> level;	// Ceil

	return (lev_len);
}



const float *	MipMapFlt::use_table (int table) const
{
	assert (is_ready ());
	assert (table >= 0);
	assert (table < _nbr_tables);

	return (_table_arr [table]._data_ptr);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}	// namespace rspl



#endif	// rspl_MipMapFlt_CODEHEADER_INCLUDED

#undef rspl_MipMapFlt_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
