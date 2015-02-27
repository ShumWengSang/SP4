#include "WeatherGenerator.h"
//
//void main()
//{
//	srand(NULL);
//	WeatherGenerator theWeather;
//
//	theWeather.PrintOutGraph();
//
//	for (int i = 0; i < theWeather.GetHazeAvg().size(); i++)
//	{
//		std::cout << " AVG Day " << i << " " << theWeather.GetHazeAvg()[i] << std::endl;
//	}
//
//	system("pause");
//}


//if (ParentTile != NULL)
//{
//	if (ParentTile->top != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			top = ParentTile->top->childs[ChildNum - 2];
//		else
//			top = ParentTile->childs[ChildNum + 2];
//	}
//	else
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			top = ParentTile->childs[ChildNum + 2];
//	}
//
//	if (ParentTile->bottom != NULL)
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			bottom = ParentTile->bottom->childs[ChildNum + 2];
//		else
//			bottom = ParentTile->childs[ChildNum - 2];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			bottom = ParentTile->childs[ChildNum - 2];
//	}
//
//	if (ParentTile->left != NULL)
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			left = ParentTile->left->childs[ChildNum + 1];
//		else
//			left = ParentTile->childs[ChildNum - 1];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			left = ParentTile->childs[ChildNum - 1];
//	}
//
//	if (ParentTile->right != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			right = ParentTile->right->childs[ChildNum - 1];
//		else
//			right = ParentTile->childs[ChildNum + 1];
//	}
//	else
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			right = ParentTile->childs[ChildNum + 1];
//	}
//}
//else if (ParentChildTile != NULL)
//{
//	if (ParentChildTile->top != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			top = ParentChildTile->top->childs[ChildNum - 2];
//		else
//			top = ParentChildTile->childs[ChildNum + 2];
//	}
//	else
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			top = ParentChildTile->childs[ChildNum + 2];
//	}
//
//	if (ParentChildTile->bottom != NULL)
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			bottom = ParentChildTile->bottom->childs[ChildNum + 2];
//		else
//			bottom = ParentChildTile->childs[ChildNum - 2];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			bottom = ParentChildTile->childs[ChildNum - 2];
//	}
//
//	if (ParentChildTile->left != NULL)
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			left = ParentChildTile->left->childs[ChildNum + 1];
//		else
//			left = ParentChildTile->childs[ChildNum - 1];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			left = ParentChildTile->childs[ChildNum - 1];
//	}
//
//	if (ParentChildTile->right != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			right = ParentChildTile->right->childs[ChildNum - 1];
//		else
//			right = ParentChildTile->childs[ChildNum + 1];
//	}
//	else
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			right = ParentChildTile->childs[ChildNum + 1];
//	}
//}




//if (ParentTile != NULL)
//{
//	if (ParentTile->top != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			top = ParentTile->childs[ChildNum + 2];
//		else
//			top = ParentTile->top->childs[ChildNum - 2];
//	}
//	else
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			top = ParentTile->childs[ChildNum + 2];
//	}
//
//	if (ParentTile->bottom != NULL)
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			bottom = ParentTile->childs[ChildNum - 2];
//		else
//			bottom = ParentTile->bottom->childs[ChildNum + 2];
//
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			bottom = ParentTile->childs[ChildNum - 2];
//	}
//
//	if (ParentTile->left != NULL)
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			left = ParentTile->childs[ChildNum - 1];
//		else
//			left = ParentTile->left->childs[ChildNum + 1];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			left = ParentTile->childs[ChildNum - 1];
//	}
//
//	if (ParentTile->right != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			right = ParentTile->childs[ChildNum + 1];
//		else
//			right = ParentTile->right->childs[ChildNum - 1];
//	}
//	else
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			right = ParentTile->childs[ChildNum + 1];
//	}
//}
//else if (ParentChildTile != NULL)
//{
//	if (ParentChildTile->top != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			top = ParentChildTile->childs[ChildNum + 2];
//		else
//			top = ParentChildTile->top->childs[ChildNum - 2];
//	}
//	else
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			top = ParentChildTile->childs[ChildNum + 2];
//	}
//
//	if (ParentChildTile->bottom != NULL)
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			bottom = ParentChildTile->childs[ChildNum - 2];
//		else
//			bottom = ParentChildTile->bottom->childs[ChildNum + 2];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			bottom = ParentChildTile->childs[ChildNum - 2];
//	}
//
//	if (ParentChildTile->left != NULL)
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			left = ParentChildTile->childs[ChildNum - 1];
//		else
//			left = ParentChildTile->left->childs[ChildNum + 1];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			left = ParentChildTile->childs[ChildNum - 1];
//	}
//
//	if (ParentChildTile->right != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			right = ParentChildTile->childs[ChildNum + 1];
//		else
//			right = ParentChildTile->right->childs[ChildNum - 1];
//	}
//	else
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			right = ParentChildTile->childs[ChildNum + 1];
//	}
//}

//int tempNum = ChildNum;
//if (ChildNum <= 1)
//ChildNum += 4;
//if (ParentTile != NULL)
//{
//	if (ParentTile->top != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			top = ParentTile->top->childs[ChildNum - 2];
//		else
//			top = ParentTile->childs[ChildNum + 2];
//	}
//	else
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			top = ParentTile->childs[ChildNum + 2];
//	}
//
//	if (ParentTile->bottom != NULL)
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			bottom = ParentTile->bottom->childs[ChildNum + 2];
//		else
//			bottom = ParentTile->childs[ChildNum - 2];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			bottom = ParentTile->childs[ChildNum - 2];
//	}
//
//	if (ParentTile->left != NULL)
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			left = ParentTile->left->childs[ChildNum + 1];
//		else
//			left = ParentTile->childs[ChildNum - 1];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			left = ParentTile->childs[ChildNum - 1];
//	}
//
//	if (ParentTile->right != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			right = ParentTile->right->childs[ChildNum - 1];
//		else
//			right = ParentTile->childs[ChildNum + 1];
//	}
//	else
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			right = ParentTile->childs[ChildNum + 1];
//	}
//}
//else if (ParentChildTile != NULL)
//{
//	if (ParentChildTile->top != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			top = ParentChildTile->top->childs[ChildNum - 2];
//		else
//			top = ParentChildTile->childs[ChildNum + 2];
//	}
//	else
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			top = ParentChildTile->childs[ChildNum + 2];
//	}
//
//	if (ParentChildTile->bottom != NULL)
//	{
//		if (ChildNum != 2 && ChildNum != 3)
//			bottom = ParentChildTile->bottom->childs[ChildNum + 2];
//		else
//			bottom = ParentChildTile->childs[ChildNum - 2];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 1)
//			bottom = ParentChildTile->childs[ChildNum - 2];
//	}
//
//	if (ParentChildTile->left != NULL)
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			left = ParentChildTile->left->childs[ChildNum + 1];
//		else
//			left = ParentChildTile->childs[ChildNum - 1];
//	}
//	else
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			left = ParentChildTile->childs[ChildNum - 1];
//	}
//
//	if (ParentChildTile->right != NULL)
//	{
//		if (ChildNum != 0 && ChildNum != 2)
//			right = ParentChildTile->right->childs[ChildNum - 1];
//		else
//			right = ParentChildTile->childs[ChildNum + 1];
//	}
//	else
//	{
//		if (ChildNum != 1 && ChildNum != 3)
//			right = ParentChildTile->childs[ChildNum + 1];
//	}
//}