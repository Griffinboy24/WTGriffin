


#if ! defined (rspl_InterpFltPhase_HEADER_INCLUDED)
#define	rspl_InterpFltPhase_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma once
	#pragma warning (4 : 4250) // "Inherits via dominance."
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include	"rspl.hpp"



namespace rspl
{



template <int SC>
class InterpFltPhase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	enum {			SCALE				= SC	};
	enum {			FIR_LEN			= 12 * SCALE	};

						InterpFltPhase ();

	rspl_FORCEINLINE float
						convolve (const float data_ptr [], float q) const;

	float				_dif [FIR_LEN];	// Index inverted (Gd [FIR_LEN-1] first).
	float				_imp [FIR_LEN];	// Index inverted.



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	// Magic code for checking if impulse has been set or not in convolve().
	enum {			CHK_IMPULSE_NOT_SET	= 12345	};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

};	// class InterpFltPhase



}	// namespace rspl



#include	"InterpFltPhase.hpp"



#endif	// rspl_InterpFltPhase_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
