/*****************************************************************************

FIR interpolator. This class is stateless and therefore can be used in "random
access" on the source sample.

Template parameters:

- SC: Scale of the FIR interpolator. Its length is 64 * 12 * SC.


*Tab=3***********************************************************************/



#if ! defined (rspl_InterpFlt_HEADER_INCLUDED)
#define	rspl_InterpFlt_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma once
	#pragma warning (4 : 4250) // "Inherits via dominance."
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include	"InterpFltPhase.h"
#include	"rspl.hpp"



namespace rspl
{



template <int SC = 1>
class InterpFlt
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef	InterpFltPhase <SC>	Phase;

	enum {			SCALE				= Phase::SCALE	};
	enum {			FIR_LEN			= Phase::FIR_LEN	};
	enum {			NBR_PHASES_L2	= 6	};

	enum {			NBR_PHASES		= 1 << NBR_PHASES_L2	};
	enum {			IMPULSE_LEN		= FIR_LEN * NBR_PHASES	};

						InterpFlt ();
	virtual			~InterpFlt () {}

	void				set_impulse (const double imp_ptr [IMPULSE_LEN]);
	rspl_FORCEINLINE float
						interpolate (const float data_ptr [], UInt32 frac_pos) const;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	Phase				_phase_arr [NBR_PHASES];



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

						InterpFlt (const InterpFlt &other);
	InterpFlt &		operator = (const InterpFlt &other);
	bool				operator == (const InterpFlt &other);
	bool				operator != (const InterpFlt &other);

};	// class InterpFlt



}	// namespace rspl



#include	"InterpFlt.hpp"



#endif	// rspl_InterpFlt_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
