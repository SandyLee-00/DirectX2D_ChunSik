#include "TextPersonData.h"

TextPersonData::TextPersonData(UINT64 _score, std::string _name, float _totalSec)
	: score(_score), name(_name), totalSec(_totalSec)
{

}

TextPersonData::TextPersonData()
{

}

TextPersonData::~TextPersonData()
{

}

bool TextPersonData::operator==(const TextPersonData& _other)
{
	if (this->GetScore() == _other.GetScore())
	{
		if (this->GetTotalSec() == _other.GetTotalSec())
		{
			if (this->GetName() == _other.GetName())
			{
				return true;
			}
		}
	}

	return false;
}
