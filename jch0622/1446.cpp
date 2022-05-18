#include <iostream>
#include <map>
#include <set>

struct	NodeInfo
{
	int		start;
	int		end;
};

struct	RoadInfo
{
	int		loadEnd_;
	std::map<std::pair<int, int>, int>	mShortCut_;
	std::set<int>						sNode_;

	bool	is_shortcut(int &shortStart, int &shortEnd, int &shortLength)
	{
		if (loadEnd_ < shortEnd)
			return false;
		else if (shortEnd - shortStart <= shortLength)
			return false;
		return true;
	}

	void	mShortCutInit()
	{
		for (int node : sNode_)
		{
			std::pair<int, int> p = {0, node};
			if (mShortCut_[p] == 0)
			{
				mShortCut_[p] = node;
			}
		}
	}

	void	init()
	{
		int		shortNum, shortStart, shortEnd, shortLength;

		std::cin >> shortNum >> loadEnd_;
		sNode_.insert(0);
		sNode_.insert(loadEnd_);
		for (int i = 0; i < shortNum; i++)
		{
			std::cin >> shortStart >> shortEnd >> shortLength;
			std::pair<int, int>	p = {shortStart,shortEnd};
			if (is_shortcut(shortStart, shortEnd, shortLength) == true)
			{
				if (shortLength == 0)
				{
					--shortLength;
				}
				if (mShortCut_[p] == 0)
				{
					mShortCut_[p] = shortLength;
				}
				else if (mShortCut_[p] != 0 && mShortCut_[p] > shortLength)
				{
					mShortCut_[p] = shortLength;
				}
				sNode_.insert(shortStart);
				sNode_.insert(shortEnd);
			}
		}
		mShortCutInit();
	}
	
	int	getLoadLength()
	{
		int	lengthTmp;
		int	endPrev = 0;
		std::pair<int, int> p;
		std::pair<int, int>	pPrev = {0,0};
		for (int end : sNode_)
		{
			for (int start : sNode_)
			{
				if (start >= end)
				{
					break;
				}
				p = {start, end};
				if (mShortCut_[p] != 0)
				{
					if (mShortCut_[p] == -1)
					{
						++mShortCut_[p];
					}
					if (start == 0)
					{
						lengthTmp = mShortCut_[pPrev] + (end - endPrev);
					}
					else
					{
						lengthTmp = mShortCut_[std::make_pair(0, start)] + mShortCut_[p];
					}
					if (lengthTmp < mShortCut_[std::make_pair(0, end)])
					{
						mShortCut_[std::make_pair(0, end)] = lengthTmp;
					}
				}
			}
			endPrev = end;
			pPrev = std::make_pair(0, end);
		}
		return mShortCut_[std::make_pair(0, loadEnd_)];
	}
};

int main(void)
{
	RoadInfo	roadInfo;

	roadInfo.init();
	std::cout << roadInfo.getLoadLength();
}