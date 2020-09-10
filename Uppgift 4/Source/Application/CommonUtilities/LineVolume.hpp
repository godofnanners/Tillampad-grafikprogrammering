#pragma once
#include <vector>
#include "Line.hpp"
namespace CommonUtilities 
{

	template<class T>
	class LineVolume
	{
	public:
		// Default constructor: empty LineVolume.
		LineVolume();
		// Constructor taking a list of Line that makes up the LineVolume.
		LineVolume(const std::vector<Line<T>>& aLineList);
		// Add a Line to the LineVolume.
		void AddLine(const Line<T>& aLine);
		// Returns whether a point is inside the LineVolume: it is inside when the point is
		// on the line or on the side the normal is pointing away from for all the lines in
		// the LineVolume.
		bool IsInside(const Vector2<T>& aPosition);
	private:
		std::vector<Line<T>> myLineList;
	};

	template<class T>
	inline LineVolume<T>::LineVolume()
	{
		myLineList.empty();
	}

	template<class T>
	inline LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLineList = aLineList;
	}

	template<class T>
	inline void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLineList.push_back(aLine);
	}

	template<class T>
	inline bool LineVolume<T>::IsInside(const Vector2<T>& aPosition)
	{
		for (std::vector<Line<T>>::iterator it = myLineList.begin(); it < myLineList.end(); ++it)
		{
			if (it->IsInside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}
}
