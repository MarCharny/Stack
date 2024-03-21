#include "gtest/gtest.h"
#include "../include/Stack.hpp"

template<typename T>
void Equal(const T* real, const T* required, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		ASSERT_EQ(real[i], required[i]);
	}
}

TEST(StackConstructor, DefaultConstructor) {
	Stack<int> st;
	ASSERT_EQ(st.IsEmpty(), true);
	ASSERT_EQ(st.Size(), 0);
	ASSERT_EQ(st.Capacity(), 1);
}

TEST(StackConstructor, CapacityConstructor) {
	Stack<int> st(5);
	ASSERT_EQ(st.IsEmpty(), true);
	ASSERT_EQ(st.Size(), 0);
	ASSERT_EQ(st.Capacity(), 5);
}

TEST(StackFunctions, PushFunction)
{
	Stack<int> st(5);
	st.Push(6);
	st.Push(7);
	int req[5] = { 6, 7 };
	Equal(st.GetData(), req, 2);
}

TEST(StackFunctions, PopFunction)
{
	Stack<int> st(5);
	st.Push(6);
	st.Push(7);
	st.Push(8);
	int req[5] = { 6, 7 };
	Equal(st.GetData(), req, 2);
}


TEST(StackFunctions, TopFunction)
{
	Stack<int> st(5);
	st.Push(6);
	st.Push(7);
	st.Push(8);
	int top = 8;
	ASSERT_EQ(st.Top(), 8);
}


TEST(StackFunctions, Resize)
{
	Stack<int> st(2);
	st.Push(6);
	st.Push(7);
	st.Push(8);
	int req[3] = { 6, 7, 8 };
	ASSERT_EQ(st.Size(), 3);
	ASSERT_EQ(st.Capacity(), 4);
	Equal(req, st.GetData(), 3);
}

TEST(StackConstructor, CopyConstructor)
{
	Stack<std::string> st1;
	st1.Push("al");
	st1.Push("go");
	st1.Push("rithms");
	Stack<std::string> st2(st1);

	ASSERT_EQ(st1.Size(), st2.Size());
	ASSERT_EQ(st1.Capacity(), st2.Capacity());
	Equal(st1.GetData(), st2.GetData(), st1.Size());

	{ //Independence
		st2.Pop();
		std::string req2[2] = { "al", "go" };
		Equal(st2.GetData(), req2, 2);
		std::string req1[3] = { "al", "go", "rithms" };
		Equal(st2.GetData(), req1, 3);
	}
}

TEST(StackConstructor, MoveConstructor)
{
	Stack<std::string> st1;
	st1.Push("al");
	st1.Push("go");
	st1.Push("rithms");

	Stack<std::string> st2;
	st2.Push("al");
	st2.Push("go");
	st2.Push("rithms");

	Stack<std::string> st3(std::move(st1));
	ASSERT_EQ(st3.Size(), st2.Size());
	Equal(st3.GetData(), st2.GetData(), st3.Size());
	ASSERT_EQ(st1.GetData(), nullptr);
}

TEST(StackOperands, CopyAssigment)
{
	Stack<std::string> st1;
	st1.Push("al");
	st1.Push("go");
	st1.Push("rithms");

	Stack<std::string> st2 = st1;

	ASSERT_EQ(st1.Size(), st2.Size());
	ASSERT_EQ(st1.Capacity(), st2.Capacity());
	Equal(st1.GetData(), st2.GetData(), st1.Size());
}

TEST(StackOperands, MoveAssigment)
{
	Stack<std::string> st1;
	st1.Push("al");
	st1.Push("go");
	st1.Push("rithms");

	Stack<std::string> st2;
	st2.Push("al");
	st2.Push("go");
	st2.Push("rithms");

	Stack<std::string> st3 = std::move(st1) ;
	ASSERT_EQ(st3.Size(), st2.Size());
	Equal(st3.GetData(), st2.GetData(), st3.Size());
	ASSERT_EQ(st1.GetData(), nullptr);
}