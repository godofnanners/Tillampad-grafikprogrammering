#pragma once
#include <array>
namespace InputKeys
{
	enum class eMouseButtons
	{
		eCONTROL,
		eLBUTTON,
		eMBUTTON,
		eRBUTTON,
		eSHIFT,
		eXBUTTON1,
		eXBUTTON2,
		Count
	};

	const std::array<int, 7> myListOfMouseButtons = { MK_CONTROL, MK_LBUTTON, MK_MBUTTON, MK_RBUTTON, MK_SHIFT, MK_XBUTTON1, MK_XBUTTON2 };
}