#include "../../UnitTest++/UnitTest++.h"

#include "../RootDock.h"

TEST(RootDockConstructor)
{
	Tab tab("sample");
	RootDock root(10, 20, 50, 70, &tab);

	CHECK_EQUAL(10, root.GetPositionX());
	CHECK_EQUAL(20, root.GetPositionY());
	CHECK_EQUAL(50, root.GetWidth());
	CHECK_EQUAL(70, root.GetHeight());
}

TEST(RootDockAddLeftDock)
{
	Tab tab("sample");
	RootDock root(10, 20, 50, 70, &tab);

	Tab left("left");
	root[0].AddTabLeft(&left);

	// root
	//	- horizontal
	//		- tab -> left
	//		- tab -> sample

	CHECK_EQUAL(DockTypes::Root, root.GetType());
	CHECK_EQUAL(1, root.GetChildCount());
	CHECK_EQUAL(DockTypes::Horizontal, root[0].GetType());
	CHECK_EQUAL(2, root[0].GetChildCount());
	CHECK_EQUAL(DockTypes::Tab, root[0][0].GetType());
	CHECK_EQUAL(DockTypes::Tab, root[0][1].GetType());
	CHECK_EQUAL(&left, root[0][0].GetCurrentTab());
	CHECK_EQUAL(&tab, root[0][1].GetCurrentTab());
}

TEST(RootDockAddRightDock)
{
	Tab tab("sample");
	RootDock root(10, 20, 50, 70, &tab);

	Tab right("right");
	root[0].AddTabRight(&right);

	// root
	//	- horizontal
	//		- tab -> sample
	//		- tab -> right

	CHECK_EQUAL(DockTypes::Root, root.GetType());
	CHECK_EQUAL(1, root.GetChildCount());
	CHECK_EQUAL(DockTypes::Horizontal, root[0].GetType());
	CHECK_EQUAL(2, root[0].GetChildCount());
	CHECK_EQUAL(DockTypes::Tab, root[0][0].GetType());
	CHECK_EQUAL(DockTypes::Tab, root[0][1].GetType());
	CHECK_EQUAL(&tab, root[0][0].GetCurrentTab());
	CHECK_EQUAL(&right, root[0][1].GetCurrentTab());
}