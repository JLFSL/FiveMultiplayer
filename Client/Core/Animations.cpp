#include "stdafx.h"


std::string Animations::GetAnimalAnimationDictionary(int modelhash)
{
#pragma region Animals
	switch (modelhash)
	{
	case -832573324:
		return "creatures@boar@move";
	case 1462895032:
		return "creatures@cat@move";
	case -1430839454:
		return "creatures@chickenhawk@move";
	case 51016938:
	case 1126154828:
		return "creatures@dog@move";
	case 1457690978:
		return "creatures@cormorant@move";
	case -50684386:
		return "creatures@cow@move";
	case 1682622302:
		return "creatures@coyote@move";
	case 402729631:
		return "creatures@crow@move";
	case -664053099:
		return "creatures@deer@move";
	case -1950698411:
		return "creatures@dolphin@move";
	case 802685111:
		return "creatures@fish@move";
	case 1794449327:
		return "creatures@hen@move";
	case 1193010354:
		return "creatures@humpback@move";
	case 1318032802:
		return "creatures@husky@move";
	case -1920284487:
		return "creatures@killerwhale@move";
	case -1323586730:
		return "creatures@pig@move";
	case 111281960:
		return "creatures@pigeon@move";
	case 1125994524:
	case 1832265812:
	case -1384627013:
		return "creatures@pug@move";
	case -541762431:
		return "creatures@rabbit@move";
	case -1011537562:
		return "creatures@rat@move";
	case 882848737:
		return "creatures@retriever@move";
	case -1788665315:
		return "creatures@rottweiler@move";
	case -745300483:
		return "creatures@pigeon@move";
	case 1015224100:
	case 113504370:
		return "creatures@shark@move";
	case -1589092019:
		return "creatures@stingray@move";
#pragma endregion Animals Animation Dictionaries
#pragma region Female
		
#pragma endregion Female Animation Dictionaries
	default:
		return NULL;
	}
}